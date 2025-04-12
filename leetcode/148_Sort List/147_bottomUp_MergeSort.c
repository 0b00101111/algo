/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * Merges two sorted linked lists into one sorted list
 * @param left The head of the first sorted list
 * @param right The head of the second sorted list
 * @return The head of the merged sorted list
 */
struct ListNode* merge(struct ListNode* left, struct ListNode* right) {
    // Create a dummy head to simplify edge cases
    struct ListNode dummy;
    // Tail pointer to track the end of our merged list
    struct ListNode* tail = &dummy;

    // Merge while both lists have nodes
    while (left && right) {
        if (left->val <= right->val) {
            // Take from left list if smaller or equal
            tail->next = left;
            left = left->next;
        } else {
            // Take from right list if smaller
            tail->next = right;
            right = right->next;
        }
        // Move tail pointer to the latest node
        tail = tail->next;
    }

    // Attach any remaining nodes (only one of these will execute)
    tail->next = left ? left : right;

    // Return the merged list (excluding dummy node)
    return dummy.next;
}

/**
 * Splits the linked list after 'step' nodes
 * @param head The start of the list to split
 * @param step Number of nodes to keep in the first part
 * @return The head of the second part after splitting
 */
struct ListNode* split(struct ListNode* head, int step) {
    // Handle null pointer
    if (!head) return NULL;

    // Move 'step-1' nodes ahead to reach the split point
    for (int i = 1; head->next && i < step; i++) {
        head = head->next;
    }

    // Save the head of the second part
    struct ListNode* right = head->next;
    // Break the link between the two parts
    head->next = NULL;

    // Return the head of the second part
    return right;
}

/**
 * Sorts a linked list using bottom-up merge sort in O(n log n) time and O(1) space
 * @param head The head of the linked list to sort
 * @return The head of the sorted linked list
 */
struct ListNode* sortList(struct ListNode* head) {
    // Handle empty list and single node list
    if (!head || !head->next) return head;

    // Find the length of the linked list
    int length = 0;
    struct ListNode* curr = head;
    while (curr) {
        length++;
        curr = curr->next;
    }

    // Create a dummy head to simplify list manipulation
    struct ListNode dummy;
    dummy.next = head;

    // Bottom-up merge sort with increasing sublist sizes
    // Start with size 1, then 2, 4, 8, etc.
    for (int step = 1; step < length; step *= 2) {
        // prev points to the node before the current processing section
        struct ListNode* prev = &dummy;
        // current points to the start of the current processing section
        struct ListNode* current = dummy.next;

        // Process the entire list
        while (current) {
            // First sublist starts at current (size: step)
            struct ListNode* left = current;

            // Second sublist starts after 'step' nodes from left (size: step)
            struct ListNode* right = split(left, step);

            // Next processing section starts after 'step' nodes from right
            current = split(right, step);

            // Merge the two sublists and connect to the main list
            prev->next = merge(left, right);

            // Move prev to the end of the merged section
            while (prev->next) {
                prev = prev->next;
            }
        }
    }

    // Return the sorted list
    return dummy.next;
}