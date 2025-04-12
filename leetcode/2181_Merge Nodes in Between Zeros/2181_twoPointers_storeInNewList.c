/**
* Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeNodes(struct ListNode* head) {
    struct ListNode dummy; // Dummy node to simplify handling the head
    struct ListNode* result = &dummy;
    struct ListNode* current = head->next; // Skip the first 0

    int sum = 0;

    while (current != NULL) {
        if (current->val == 0) {
            // We've reached the end of a segment
            // Create a new node with the accumulated sum
            result->next = malloc(sizeof(struct ListNode));
            result = result->next;
            result->val = sum;
            result->next = NULL;

            // Reset sum for the next segment
            sum = 0;
        } else {
            // Accumulate values
            sum += current->val;
        }

        current = current->next;
    }

    return dummy.next;
}