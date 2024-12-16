#include <stdio.h>
#include <stdlib.h>


struct bstNode {
    int data;
    struct bstNode* left;
    struct bstNode* right;
};

struct bstNode* insert(struct bstNode* root, int data) {
    if (root == NULL) {
        root = (struct bstNode*) malloc (sizeof(struct bstNode));
        root -> data = data;
        root -> left = NULL;
        root -> right = NULL;
    } else if (data < root -> data) { /// ভ্যালু যদি রুট নোড থেকে ছোট হয়
        root -> left = insert (root -> left, data);
    } else if (data > root -> data) { /// বড় হয়
        root -> right = insert (root -> right, data);
    } else {
        /// নারলাম না :)
    }
    return root;
}

struct bstNode* search(struct bstNode* root, int targetData) {
    if (root == NULL || root -> data == targetData) return root; /// টার্গেট পাওয়া গেলে রিটার্ন
    else if (targetData < root -> data) return search (root -> left, targetData); /// টার্গেট ছোট হলে বামে খুঁজতে থাকবো যতক্ষণ না পাবো
    else return search (root -> right, targetData); /// আর বোরো হলে ডানে
    /// এখন সমান হলে, ওই যে প্রথম কন্ডিশন যেটা দরকার
}

void inorder(struct bstNode* root){
    if (root == NULL) return;
    inorder (root -> left);
    printf("%d ", root -> data);
    inorder (root -> right);
    return; /// লজিক না বুঝলে মনে রাখো, in-pre-post এ মোটামুটি একটা সেইম প্যাটার্ন টাইপের কোড আছে
}

void preorder(struct bstNode* root) {
    if (root == NULL) return;
    printf("%d ", root -> data);
    preorder (root -> left);
    preorder (root -> right);
    return;
}

void postorder(struct bstNode* root) {
    if (root == NULL) return;
    postorder (root -> left);
    postorder (root -> right);
    printf("%d ", root -> data);
    return;
}

struct bstNode* findMin(struct bstNode* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

struct bstNode* delete(struct bstNode* root, int targetData){ /// ডিলিট আসবে না :|
    if (root == NULL) return root;
    if (targetData < root->data) {
        root->left = delete(root->left, targetData);
    } else if (targetData > root->data) {
        root->right = delete(root->right, targetData);
    } else {
        /// For no child:
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        /// For a child (right):
        } else if (root->left == NULL) {
            struct bstNode* temp = root->right;
            free(root);
            return temp;
        /// For a child (left):
        } else if (root->right == NULL) {
            struct bstNode* temp = root->left;
            free(root);
            return temp;
        /// For two children:
        } else {
            struct bstNode* temp = findMin(root->right);
            root->data = temp->data; /// Replace with successor's value
            root->right = delete(root->right, temp->data);
        }
    }
}

int main() {
    struct bstNode* root = NULL;

    root = insert (root, 100);
    root = insert (root, 50);
    root = insert (root, 150);
    root = insert (root, 120);
    root = insert (root, 5);
    root = insert (root, 51);
    root = insert (root, 170);
    
    printf("In-order Traversal: "); 
    inorder(root); 
    printf("\n");

    printf("Pre-order Traversal: "); 
    preorder(root); 
    printf("\n");

    printf("Post-order Traversal: "); 
    postorder(root); 
    printf("\n");

    struct bstNode* resutlt = search (root, 120);
    if (resutlt != NULL) printf("%d is found >-<\n", resutlt -> data);
    else printf("Not found -_-\n");

    root = delete (root, 150);
    printf("After Deletion,\n");
    printf("In-order Traversal: "); 
    inorder(root); 
    printf("\n");

    return ( 0 - 0);
}
