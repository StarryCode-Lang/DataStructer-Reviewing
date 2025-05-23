cmake_minimum_required(VERSION 3.30)
project(DSCPP)

set(CMAKE_CXX_STANDARD 20)

# 共享的头文件
set(SHARED_HEADERS
        LinkQueue.h
        5-2UnionFindSet.h
        6-0GraphDefinition.h
)

# 共享的源文件（不包含main函数的实现文件）
set(SHARED_SOURCES
        3-2Queue.cpp
)

# 为每个包含main函数的源文件创建单独的可执行文件
add_executable(SmartPointer smart-point.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(SequentialList 2-2SequentialList.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(LinkedList 2-3LinkedList.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(Stack 3-1Stack.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(ExpressionStack 3-3-1ExpressionStack.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(FibonacciNonRecursive 3-3-2FibonacciNonRecursive.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(QueueBinaryTreeLevelTraversal 3-3-3QueueBinaryTreeLevelTraversal.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(StringKMP 4StringDefinitionAndKMP.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(BinaryTree 5-1BinaryTree.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(GraphOperations 6-1GraphOperations.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(GraphTraversal 6-2GraphTraversal.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(MinimumSpanningTree 6-3MinimumSpanningTree.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(ShortestPath 6-4ShortestPath.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(TopologicalSort 6-5TopologicalSort.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(Sort sort.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(AOECriticalPath 6-6AOECriticalPath.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(SequentialBinarySearch 7-1SequentialBinarySearch.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(BST 7-2BST.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
add_executable(SortAlgorithms 8sort.cpp ${SHARED_HEADERS} ${SHARED_SOURCES})
