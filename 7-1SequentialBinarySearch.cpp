#include <iostream>
using namespace std;

typedef struct {
    int *elem;
    int TableLen;
} SSTable;

typedef struct BSTNode {
    int data;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
} BSTNode;

int Search_Seq(const SSTable ST, const int key) {
    int i;
    ST.elem[0] = key;
    for (i = ST.TableLen; ST.elem[i] != key; --i) {
    }
    return i;
}
int Binary_Seq(const SSTable ST, const int key) {
    int low = 0, high = ST.TableLen;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (ST.elem[mid] == key) {
            return mid;
        }
        if (ST.elem[mid] > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}


const BSTNode *BSTSearch(const BSTNode *BST, const int key) {
    while (BST != nullptr && key != BST->data) {
        if (key < BST->data)
            BST = BST->lchild;
        else
            BST = BST->rchild;
    }
    return BST;
}

int BST_insert(BSTNode *&BST, const int k) {
    if (BST == nullptr) {
        BST = new BSTNode;
        BST->data = k;
        BST->lchild = BST->rchild = nullptr;
        return 1;
    } else if (k == BST->data) {
        return 0;
    } else if (k < BST->data) {
        return BST_insert(BST->lchild, k);
    } else {
        return BST_insert(BST->rchild, k);
    }
}

void Creat_BST(BSTNode *&BST, int str[], int n) {
    BST = nullptr;
    int i = 0;
    while (i < n) {
        BST_insert(BST, str[i]);
        i++;
    }
}

void Delete_BST(BSTNode *&BST, const int key) {
    if (BST == nullptr)
        return;
    if (key < BST->data) {
        Delete_BST(BST->lchild, key);
    } else if (key > BST->data) {
        Delete_BST(BST->rchild, key);
    } else {
        if (BST->lchild == nullptr || BST->rchild == nullptr) {
            BSTNode *tmp = BST;
            BST = (BST->lchild != nullptr) ? BST->lchild : BST->rchild;
            delete tmp;
        } else {
            BSTNode *succ = BST->rchild;
            while (succ->lchild)
                succ = succ->lchild;
            BST->data = succ->data;
            Delete_BST(BST->rchild, succ->data);
        }
    }
}
