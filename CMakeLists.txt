cmake_minimum_required(VERSION 3.30)
project(DSCPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(DSCPP
        LinkQueue.h
        smart-point.cpp
        2-2SequentialList.cpp
        2-3LinkedList.cpp
        3-1Stack.cpp
        3-2Queue.cpp
        3-3-1ExpressionStack.cpp
        3-3-2FibonacciNonRecursive.cpp
        3-3-3QueueBinaryTreeLevelTraversal.cpp
        4StringDefinitionAndKMP.cpp
        5-1BinaryTree.cpp
        5-2UnionFindSet.h
        6-0GraphDefinition.h
        6-1GraphOperations.cpp
        6-2GraphTraversal.cpp
        6-3MinimumSpanningTree.cpp
        6-4ShortestPath.cpp
        6-5TopologicalSort.cpp
        sort.cpp
)
