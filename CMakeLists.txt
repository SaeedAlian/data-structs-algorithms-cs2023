cmake_minimum_required(VERSION 3.5)
project(DataStructuresAndAlgorithms)
set(CMAKE_CXX_STANDARD 11) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Define the source files

set(DecimalNumber_SOURCES src/DecimalNumber/DecimalNumber.cpp)
set(Stack_SOURCES src/Stack/Stack.cpp)
set(Queue_SOURCES src/Queue/Queue.cpp)
set(Binary_tree_SOURCES src/BinaryTree/BinaryTree.cpp)
set(AVL_tree_SOURCES src/AVLTree/AVLTree.cpp)

set(Check_expression_balance_SOURCES src/check-expression-balance.cpp)
set(Evaluate_infix_SOURCES src/evaluate-infix.cpp)
set(Prefix_to_postfix_SOURCES src/prefix-to-postfix.cpp)
set(Stack_sequence_validation_SOURCES src/stack-sequence-validation.cpp)
set(Decimal_number_calc_SOURCES src/decimal-number-calc.cpp)
set(Binary_tree_test_SOURCES src/binary-tree-test.cpp)
set(Kmp_pattern_matching_SOURCES src/kmp-pattern-matching.cpp)

set(Magic_square_SOURCES src/main-apps/magic-square.cpp)
set(Calculator_SOURCES src/main-apps/calculator.cpp)
set(AVL_tree_test_SOURCES src/main-apps/avl-tree-test.cpp)
set(Strassen_matrix_mult_SOURCES  src/main-apps/strassen-matrix-mult.cpp)

# Create the executable targets
add_executable(check-expression-balance.o ${Check_expression_balance_SOURCES} ${Stack_SOURCES})
add_executable(evaluate-infix.o ${Evaluate_infix_SOURCES} ${Stack_SOURCES})
add_executable(prefix-to-postfix.o ${Prefix_to_postfix_SOURCES} ${Stack_SOURCES})
add_executable(stack-sequence-validation.o ${Stack_sequence_validation_SOURCES} ${Stack_SOURCES})
add_executable(decimal-number-calc.o ${Decimal_number_calc_SOURCES} ${DecimalNumber_SOURCES})
add_executable(binary-tree-test.o ${Binary_tree_test_SOURCES} ${Binary_tree_SOURCES} ${Queue_SOURCES})
add_executable(kmp-pattern-matching.o ${Kmp_pattern_matching_SOURCES})

add_executable(magic-square.o ${Magic_square_SOURCES})
add_executable(calculator.o ${Calculator_SOURCES} ${Stack_SOURCES} ${Queue_SOURCES})
add_executable(avl-tree-test.o ${AVL_tree_test_SOURCES} ${AVL_tree_SOURCES} ${Queue_SOURCES})
add_executable(strassen-matrix-mult.o ${Strassen_matrix_mult_SOURCES})
