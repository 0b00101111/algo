/**
 * Helper function to detect cycles using DFS
 * Returns true if a cycle is found, false otherwise
 */
bool hasCycle(int node, int** graph, int* counts, bool* visited, bool* inStack) {
    // Mark current node as visited and part of current recursion stack
    visited[node] = true;
    inStack[node] = true;

    // Visit all neighbors
    for (int i = 0; i < counts[node]; i++) {
        int neighbor = graph[node][i];

        // If not visited, recurse
        if (!visited[neighbor]) {
            if (hasCycle(neighbor, graph, counts, visited, inStack)) {
                return true; // Propagate cycle detection
            }
        }
        // If the neighbor is in current recursion stack, we found a cycle
        else if (inStack[neighbor]) {
            return true;
        }
    }

    // Remove current node from recursion stack before returning
    inStack[node] = false;
    return false;
}

/**
 * Detects whether it's possible to complete all courses
 * Returns true if possible, false if there's a cycle
 */
bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    // Create adjacency list representation of the graph
    int** graph = (int**)malloc(numCourses * sizeof(int*));
    int* counts = (int*)calloc(numCourses, sizeof(int));

    // First, count outgoing edges for each node
    for (int i = 0; i < prerequisitesSize; i++) {
        counts[prerequisites[i][1]]++;
    }

    // Allocate memory for adjacency lists
    for (int i = 0; i < numCourses; i++) {
        graph[i] = (int*)malloc(counts[i] * sizeof(int));
        counts[i] = 0; // Reset counts to use as indices
    }

    // Build the adjacency list
    for (int i = 0; i < prerequisitesSize; i++) {
        int from = prerequisites[i][1];
        int to = prerequisites[i][0];
        graph[from][counts[from]++] = to;
    }

    // Arrays for DFS cycle detection
    bool* visited = (bool*)calloc(numCourses, sizeof(bool));
    bool* inStack = (bool*)calloc(numCourses, sizeof(bool)); // Tracks current DFS path

    // Perform DFS from each unvisited node
    for (int i = 0; i < numCourses; i++) {
        if (!visited[i]) {
            if (hasCycle(i, graph, counts, visited, inStack)) {
                // Clean up memory
                for (int j = 0; j < numCourses; j++) {
                    free(graph[j]);
                }
                free(graph);
                free(counts);
                free(visited);
                free(inStack);
                return false; // Cycle detected, can't complete all courses
            }
        }
    }

    // Clean up memory
    for (int i = 0; i < numCourses; i++) {
        free(graph[i]);
    }
    free(graph);
    free(counts);
    free(visited);
    free(inStack);

    return true; // No cycle detected, can complete all courses
}