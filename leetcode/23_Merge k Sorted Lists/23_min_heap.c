/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// Min Heap implementation for ListNode pointers
typedef struct {
    struct ListNode** nodes;  // Array to store node pointers
    int size;                // Current size of heap
    int capacity;            // Maximum capacity
} MinHeap;

// Create a new min heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->nodes = (struct ListNode**)malloc(sizeof(struct ListNode*) * capacity);
    return heap;
}

// Helper functions for navigating the heap
int parent(int i) { return (i - 1) / 2; }
int leftChild(int i) { return 2 * i + 1; }
int rightChild(int i) { return 2 * i + 2; }

// Insert a node into the heap
void insertNode(MinHeap* heap, struct ListNode* node) {
    if (heap->size == heap->capacity) {
        return;  // Heap is full
    }

    // Insert at the end
    int i = heap->size++;
    heap->nodes[i] = node;


    // Bubble up based on node values
    while (i != 0 && heap->nodes[i]->val < heap->nodes[parent(i)]->val) {
        // Swap with parent
        struct ListNode* temp = heap->nodes[i];
        heap->nodes[i] = heap->nodes[parent(i)];
        heap->nodes[parent(i)] = temp;

        // Move up to parent index
        i = parent(i);
    }
}

// Heapify (bubble down)
void heapify(MinHeap* heap, int i) {
    int left = leftChild(i);
    int right = rightChild(i);
    int smallest = i;

    // Find the smallest among root, left child and right child
    if (left < heap->size && heap->nodes[left]->val < heap->nodes[smallest]->val)
        smallest = left;

    if (right < heap->size && heap->nodes[right]->val < heap->nodes[smallest]->val)
        smallest = right;

    // If root is not smallest, swap and continue heapifying
    if (smallest != i) {
        struct ListNode* temp = heap->nodes[i];
        heap->nodes[i] = heap->nodes[smallest];
        heap->nodes[smallest] = temp;

        heapify(heap, smallest);
    }
}

// Extract the minimum node
struct ListNode* extractMinNode(MinHeap* heap) {
    if (heap->size <= 0) {
        return NULL;  // Heap is empty
    }

    // Store the minimum node
    struct ListNode* min = heap->nodes[0];

    // Replace root with last element and heapify
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return min;
}

// Free the heap
void freeMinHeap(MinHeap* heap) {
    free(heap->nodes);
    free(heap);
}

// Main function
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    // Handle edge cases
    if (listsSize == 0) return NULL;

    // Create a min heap of size 'listsSize'
    MinHeap* heap = createMinHeap(listsSize);

    // Insert the first node from each list into the heap
    for (int i = 0; i < listsSize; i++) {
        if (lists[i] != NULL) {
            insertNode(heap, lists[i]);
        }
    }

    // Initialize result list pointers
    struct ListNode* head = NULL;  // Head of result list
    struct ListNode* tail = NULL;  // Tail of result list

    // Extract nodes from heap one by one
    while (heap->size > 0) {
        // Get the minimum value node
        struct ListNode* current = extractMinNode(heap);

        // Special case for first node
        if (head == NULL) {
            head = current;
            tail = current;
        } else {
            // Add to the end of result list
            tail->next = current;
            tail = current;
        }

        // Add the next node from the same list to the heap
        if (current->next != NULL) {
            insertNode(heap, current->next);
        }
    }

    // Make sure the list is terminated
    if (tail != NULL) {
        tail->next = NULL;
    }

    // Free the heap
    freeMinHeap(heap);

    return head;
}