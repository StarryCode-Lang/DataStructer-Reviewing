#include <iostream>
using namespace std;

typedef struct {
    int *elem;
    int TableLen;
} SSTable;

struct BSTNode {
    int data;
    BSTNode *lchild;
    BSTNode *rchild;
    BSTNode(int K) {
        data = K;
        lchild = rchild = nullptr;
    }
};

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
        else if (key > BST->data)
            BST = BST->rchild;
        else
            return BST;
    }
    return nullptr;
}

BSTNode *BST_Rsearch(BSTNode *BST, const int key) {
    if (BST == nullptr || BST->data == key)
        return BST;
    if (key < BST->data)
        return BST_Rsearch(BST->lchild, key);
    else if (key > BST->data)
        return BST_Rsearch(BST->rchild, key);
}

void BST_Insert(BSTNode *&BST, const int key) {
    if (BST == nullptr) {
        BST = new BSTNode(key);
    } else if (key < BST->data) {
        BST->lchild = BST_Rsearch(BST->lchild, key);
    } else if (key > BST->data) {
        BST->rchild = BST_Rsearch(BST->rchild, key);
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
    } else if (BST->lchild != nullptr && BST->rchild != nullptr) {
        BSTNode *s = BST->rchild;
        while (s->lchild != nullptr)
            s = s->lchild;
        BST->data = s->data;
        Delete_BST(BST->lchild, key);
    } else {
        BSTNode *oldroot = BST;
        BST = (BST->lchild == nullptr) ? BST->rchild : BST->lchild;
        delete oldroot;
    }
}
