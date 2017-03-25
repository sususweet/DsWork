cmake_minimum_required(VERSION 3.6)
project(Project1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c structure/arrayList.h structure/arrayList.c structure/linkList.h structure/linkList.c structure/polynomial.h structure/polynomial.c functions/polyCalculation.c functions/polyCalculation.h common/errorHandler.h common/errorHandler.c functions/expressionCalculation.h functions/expressionCalculation.c structure/orthogonalList.h structure/orthogonalList.c functions/matrixCalculation.h functions/matrixCalculation.c structure/hashTable.h structure/hashTable.c functions/hashTableOperation.h functions/hashTableOperation.c test/alloc-testing.h test/alloc-testing.c test/framework.c test/framework.h test/test-arrayList.c test/test-arrayList.h test/test-linkList.c test/test-linkList.h)
add_executable(Project1 ${SOURCE_FILES})