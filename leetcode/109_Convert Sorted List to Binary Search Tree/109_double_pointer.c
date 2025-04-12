#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list node
struct ListNode {
    int val;
    struct ListNode *next;
};

// Definition for binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new list node
struct ListNode* createListNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new tree node
struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to convert sorted linked list to height-balanced BST
struct TreeNode* sortedListToBST(struct ListNode* head) {
    // Base cases
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        return createTreeNode(head->val);
    }

    // Find the middle node using slow and fast pointers
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    struct ListNode* prev = NULL;

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    // slow is now the middle node
    // Disconnect the left half from the middle
    if (prev != NULL) {
        prev->next = NULL;
    }

    // Create root node using the middle value
    struct TreeNode* root = createTreeNode(slow->val);

    // Recursively build left subtree using nodes before middle
    root->left = (slow == head) ? NULL : sortedListToBST(head);

    // Recursively build right subtree using nodes after middle
    root->right = sortedListToBST(slow->next);

    return root;
}

// Helper function for in-order traversal (for verification)
void inOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->val);
        inOrderTraversal(root->right);
    }
}

// Helper function to free the BST memory
void freeTree(struct TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Helper function to free the linked list memory
void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // Create a sample sorted linked list: 1->2->3->4->5->6->7
    struct ListNode* head = createListNode(1);
    head->next = createListNode(2);
    head->next->next = createListNode(3);
    head->next->next->next = createListNode(4);
    head->next->next->next->next = createListNode(5);
    head->next->next->next->next->next = createListNode(6);
    head->next->next->next->next->next->next = createListNode(7);

    // Convert to balanced BST
    struct TreeNode* root = sortedListToBST(head);

    // Verify with in-order traversal (should print sorted array)
    printf("In-order traversal of the constructed BST: ");
    inOrderTraversal(root);
    printf("\n");

    // Free memory
    freeTree(root);

    // Note: The list has been modified during the algorithm
    // so we don't need to free it here

    return 0;
}