/**
* Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* deleteDuplicates(struct ListNode* head) {
  if (head == NULL) return NULL;

  // create a dummy node
  struct ListNode *dummy = (struct ListNode *)malloc(sizeof(struct ListNode));
  dummy->next = head;

  // set up current and prev pointer
  struct ListNode *prev = dummy;
  struct ListNode *current = head;


  //main loop
  while (current != NULL && current->next != NULL) {
      // check if the current is the start of duplicants
      if (current->val == current->next->val) {
        int duplicant = current->val;

      // remove duplicants
        while (current != NULL && current->val == duplicant) {
          struct ListNode *temp = current;
          current = current->next;
          free(temp);

          prev->next = current;
        }
      }

      // reconnect prev and current
      else {
        prev = current;
        current = current->next;
      }

  }
    return dummy->next;
}