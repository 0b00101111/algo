/**
* Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeNodes(struct ListNode* head) {
    struct ListNode* output = head; // This will be our first output node
    struct ListNode* current = head->next; // Skip the first 0

    int sum = 0;

    while (current != NULL) {
        if (current->val == 0) {
            // We've reached a 0, complete the current segment
            output = output->next; // Move to the next position for output
            output->val = sum; // Store the sum in this node
            sum = 0; // Reset for next segment
        } else {
            // Accumulate values
            sum += current->val;
        }

        current = current->next;
    }

    // Cut off the rest of the list
    output->next = NULL;

    return head->next; // Skip the first 0 in our result
}