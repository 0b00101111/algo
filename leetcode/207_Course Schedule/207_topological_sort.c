/**
 * Course Schedule problem using Kahn's algorithm (topological sort)
 * Returns true if all courses can be completed, false otherwise
 */
bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    // Create adjacency list
    int** graph = (int**)malloc(numCourses * sizeof(int*));
    int* outDegree = (int*)calloc(numCourses, sizeof(int));

    // Count outgoing edges for each node
    for (int i = 0; i < prerequisitesSize; i++) {
        outDegree[prerequisites[i][1]]++;
    }

    // Allocate memory for adjacency lists
    for (int i = 0; i < numCourses; i++) {
        graph[i] = (int*)malloc(outDegree[i] * sizeof(int));
        outDegree[i] = 0; // Reset to use as indexes
    }

    // Build the adjacency list
    for (int i = 0; i < prerequisitesSize; i++) {
        int from = prerequisites[i][1];
        int to = prerequisites[i][0];
        graph[from][outDegree[from]++] = to;
    }

    // Calculate in-degree (number of prerequisites) for each course
    int* inDegree = (int*)calloc(numCourses, sizeof(int));
    for (int i = 0; i < numCourses; i++) {
        for (int j = 0; j < outDegree[i]; j++) {
            inDegree[graph[i][j]]++;
        }
    }

    // Queue for courses with no prerequisites (in-degree = 0)
    int* queue = (int*)malloc(numCourses * sizeof(int));
    int front = 0, rear = 0;

    // Add all courses with no prerequisites to the queue
    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // Counter for visited courses
    int visitedCount = 0;

    // Process the queue (take courses with no prerequisites)
    while (front < rear) {
        int course = queue[front++];
        visitedCount++;

        // After taking this course, reduce in-degree of dependent courses
        for (int i = 0; i < outDegree[course]; i++) {
            int nextCourse = graph[course][i];
            inDegree[nextCourse]--;

            // If the course now has no prerequisites, add it to the queue
            if (inDegree[nextCourse] == 0) {
                queue[rear++] = nextCourse;
            }
        }
    }

    // Clean up memory
    for (int i = 0; i < numCourses; i++) {
        free(graph[i]);
    }
    free(graph);
    free(outDegree);
    free(inDegree);
    free(queue);

    // If all courses were visited, we can finish all courses
    return visitedCount == numCourses;
}