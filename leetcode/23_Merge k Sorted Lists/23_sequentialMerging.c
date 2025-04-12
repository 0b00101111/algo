/**
* Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * APPROACH: SEQUENTIAL MERGING
 *
 * This approach iteratively merges lists one by one.
 *
 * Algorithm:
 * 1. Start with the first list as our result
 * 2. For each remaining list, merge it with our current result
 * 3. Return the final merged list
 *
 * Time Complexity: O(kN) where k is the number of lists and N is the total number of nodes
 * - We merge each list into our result, and in the worst case, each merge operation is O(N)
 * Space Complexity: O(1) as we're merging in-place
 */

/**
 * Helper function to merge two sorted linked lists.
 * This is a standard function for merging two sorted lists.
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
    // Handle edge cases
    if (listsSize == 0) return NULL;
    if (listsSize == 1) return lists[0];

    // Start with the first list
    struct ListNode* result = lists[0];

    // Sequentially merge each list into the result
    for (int i = 1; i < listsSize; i++) {
        result = mergeTwoLists(result, lists[i]);
    }

    return result;
}