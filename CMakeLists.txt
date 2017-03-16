cmake_minimum_required(VERSION 3.6)
project(Project1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c structure/arrayList.h structure/arrayList.c structure/linkList.h structure/linkList.c structure/polynomial.h structure/polynomial.c functions/polyCalculation.c functions/polyCalculation.h common/errorHandler.h common/errorHandler.c functions/expressionCalculation.h functions/expressionCalculation.c structure/orthogonalList.h structure/orthogonalList.c)
add_executable(Project1 ${SOURCE_FILES})