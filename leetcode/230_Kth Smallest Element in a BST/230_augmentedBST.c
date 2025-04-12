/**
 * Original LeetCode TreeNode structure (already defined in their environment)
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Our augmented node structure with a different name
 */
typedef struct AugmentedNode {
    int val;
    int leftSize;  // Number of nodes in left subtree
    struct AugmentedNode *left;
    struct AugmentedNode *right;
} AugmentedNode;

/**
 * Create a new augmented node
 */
AugmentedNode* createAugmentedNode(int val) {
    AugmentedNode* node = (AugmentedNode*)malloc(sizeof(AugmentedNode));
    node->val = val;
    node->leftSize = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Helper function to count nodes in a subtree
 */
void countNodes(AugmentedNode* root, int* count) {
    if (root == NULL) return;
    (*count)++;
    countNodes(root->left, count);
    countNodes(root->right, count);
}

/**
 * Convert a regular TreeNode tree to our augmented tree
 * This would be done once when we first receive the BST
 */
AugmentedNode* convertToAugmented(struct TreeNode* root) {
    if (root == NULL) return NULL;

    // Create new augmented node
    AugmentedNode* augmentedRoot = createAugmentedNode(root->val);

    // Recursively convert left and right subtrees
    augmentedRoot->left = convertToAugmented(root->left);
    augmentedRoot->right = convertToAugmented(root->right);

    // Calculate left subtree size
    int count = 0;
    countNodes(augmentedRoot->left, &count);
    augmentedRoot->leftSize = count;

    return augmentedRoot;
}

/**
 * Insert a value into our augmented BST
 */
AugmentedNode* insertAugmented(AugmentedNode* root, int val) {
    if (root == NULL) {
        return createAugmentedNode(val);
    }

    if (val < root->val) {
        root->left = insertAugmented(root->left, val);
        root->leftSize++; // Increment left subtree size
    } else {
        root->right = insertAugmented(root->right, val);
    }

    return root;
}

/**
 * Delete a value from our augmented BST
 */
AugmentedNode* deleteAugmented(AugmentedNode* root, int val) {
    if (root == NULL) return NULL;

    if (val < root->val) {
        root->left = deleteAugmented(root->left, val);
        root->leftSize--; // Decrement left subtree size
    }
    else if (val > root->val) {
        root->right = deleteAugmented(root->right, val);
    }
    else {
        // Node found - handle deletion cases
        if (root->left == NULL) {
            AugmentedNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            AugmentedNode* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        AugmentedNode* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        // Replace with successor value
        root->val = temp->val;

        // Delete successor
        root->right = deleteAugmented(root->right, temp->val);
    }

    return root;
}

/**
 * Find kth smallest in our augmented BST - O(h) time
 */
int findKthSmallest(AugmentedNode* root, int k) {
    if (root == NULL) return -1;

    int leftSize = root->leftSize + 1; // +1 for current node

    if (k == leftSize) {
        return root->val;
    }
    else if (k < leftSize) {
        return findKthSmallest(root->left, k);
    }
    else {
        return findKthSmallest(root->right, k - leftSize);
    }
}

/**
 * Main function for LeetCode's kthSmallest problem
 * For the follow-up part, we'd convert the tree once, then maintain it
 */
int kthSmallest(struct TreeNode* root, int k) {
    // For a single query, simple in-order traversal is fine
    int count = 0;
    int result = 0;

    void inorder(struct TreeNode* node) {
        if (node == NULL || count >= k) return;
        inorder(node->left);
        count++;
        if (count == k) {
            result = node->val;
            return;
        }
        inorder(node->right);
    }

    inorder(root);
    return result;

    // For the follow-up with frequent operations:
    // 1. Convert the tree once: AugmentedNode* augTree = convertToAugmented(root);
    // 2. Use the augmented tree for future operations
    // return findKthSmallest(augTree, k);
}