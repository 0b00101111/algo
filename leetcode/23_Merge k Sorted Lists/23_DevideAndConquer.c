/**
* Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * APPROACH: DIVIDE AND CONQUER
 *
 * This approach uses recursion to merge lists in a divide-and-conquer fashion.
 *
 * Algorithm:
 * 1. Divide the list of lists into two halves
 * 2. Recursively merge each half
 * 3. Merge the two halves together
 *
 * Time Complexity: O(N log k) where k is the number of lists and N is the total number of nodes
 * - The divide and conquer approach ensures we have log k levels of merging
 * - At each level, we process all N nodes total across all lists
 * Space Complexity: O(log k) due to recursion stack
 */

/**
 * Helper function to merge two sorted linked lists.
 */
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;

    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // Attach remaining nodes
    tail->next = l1 ? l1 : l2;

    return dummy.next;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    // Base cases
    if (listsSize == 0) return NULL;
    if (listsSize == 1) return lists[0];

    // Divide the lists into two halves
    int mid = listsSize / 2;

    // Recursively merge each half
    struct ListNode* left = mergeKLists(lists, mid);
    struct ListNode* right = mergeKLists(lists + mid, listsSize - mid);

    // Combine the two halves
    return mergeTwoLists(left, right);
}