/**
* Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insertionSortList(struct ListNode* head) {
    //validate head
    if (head == NULL) return NULL;

    // edge case when head is the only one node
    if (head->next == NULL) return head;

    // create a dummy node for the sorted list
    struct ListNode* dummy = (struct ListNode *)malloc(sizeof(struct ListNode));
    dummy->next = NULL;

    // current node
    struct ListNode* curr = head;

    // outer loop to iterate each node form the original list
    while (curr) {
        // save next node before curr is modified
        struct ListNode *temp = curr->next;

        // reset prev to dummy for each iteration
        struct ListNode *prev = dummy;

        // inner loop to find the correct location
        while (prev->next != NULL && prev->next->val < curr->val) {
            prev = prev->next;
        }

        // insert curr between prev and prev->next
        curr->next = prev->next;
        prev->next = curr;

        // move curr to next node from the oginal list
        curr = temp;
    }
    return dummy->next;
}