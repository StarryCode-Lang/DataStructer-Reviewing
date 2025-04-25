#include <iostream>
using namespace std;
#include <memory>

typedef struct BiNode {
    int data;
    shared_ptr<BiNode> lclild, rclild;
} BiNode;

using BiTree = shared_ptr<BiNode>;


