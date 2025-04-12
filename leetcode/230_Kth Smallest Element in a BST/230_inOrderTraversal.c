//Time complexity: O(n) where n is the number of nodes (though we'll stop early once we find the kth element)
//Space complexity: O(h) where h is the height of the tree (due to the recursion stack)

/**
* Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void inorder(struct TreeNode* root, int* count, int k, int* result) {
    if (root == NULL || *count >= k) return;

    // Traverse left subtree
    inorder(root->left, count, k, result);

    // Process current node
    (*count)++;
    if (*count == k) {
        *result = root->val;
        return;
    }

    // Traverse right subtree
    inorder(root->right, count, k, result);
}

int kthSmallest(struct TreeNode* root, int k) {
    int count = 0;
    int result = 0;
    inorder(root, &count, k, &result);
    return result;
}