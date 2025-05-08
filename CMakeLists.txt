cmake_minimum_required(VERSION 3.30)
project(DSCPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(DSCPP 2-2线性表的顺序表示.cpp
        2-3线性表的链式表示.cpp
        smart-point.cpp 3-1栈.cpp
        3-2队列.cpp 3-3-1表达式栈.cpp
        3-3-2斐波那契非递归.cpp
        3-3-3队列二叉树层序遍历.cpp
        4串的定义和KMP.cpp
        5-1二叉树.cpp
        5-2并查集.cpp
        6-1图的定义和基本操作.cpp
        GraphOperation.h
        LinkQueue.h
        6-2图的遍历.cpp
)
