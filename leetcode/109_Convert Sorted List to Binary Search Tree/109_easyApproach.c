/**
* Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* buildBST(int* nums, int start, int end) {
    if (start > end) return NULL;

    // Find the middle element and make it the root
    int mid = start + (end - start) / 2;
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = nums[mid];

    // Recursively build left and right subtrees
    root->left = buildBST(nums, start, mid - 1);
    root->right = buildBST(nums, mid + 1, end);

    return root;
}

struct TreeNode* sortedListToBST(struct ListNode* head) {
    // Count the number of nodes in the linked list
    int count = 0;
    struct ListNode* current = head;
    while (current) {
        count++;
        current = current->next;
    }

    // Convert linked list to array
    int* nums = malloc(count * sizeof(int));
    current = head;
    for (int i = 0; i < count; i++) {
        nums[i] = current->val;
        current = current->next;
    }

    // Build BST from array
    struct TreeNode* result = buildBST(nums, 0, count - 1);

    // Clean up
    free(nums);

    return result;
}