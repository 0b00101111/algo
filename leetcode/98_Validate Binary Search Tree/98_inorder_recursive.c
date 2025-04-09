/**
* Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <limits.h>

// helper function to validate a BST
bool checkValidBST(struct TreeNode* root, long min, long max){
    if (root == NULL) return true;

    // check if the root is within boundaries
    if (root->val >= max || root->val <= min) {
        return false;
    }

    // recursively check left and right
    return checkValidBST(root->left, min, root->val) &&
           checkValidBST(root->right, root->val, max);
}

bool isValidBST(struct TreeNode* root) {
    return checkValidBST(root, LONG_MIN, LONG_MAX);
}