cmake_minimum_required(VERSION 3.27)
project(my_interpret)

set(CMAKE_CXX_STANDARD 11)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(./)
file(GLOB_RECURSE SOURCE "token/*.cpp" "json/*.cpp" "lexer/*.cpp" "ast/*.cpp" "parser/*.cpp" "object/*.cpp" "evaluator/*.cpp")

add_executable(my_interpret ${SOURCE} main.cpp)
add_executable(ast ${SOURCE} ast.cpp)
add_executable(eval ${SOURCE} eval.cpp)
add_executable(eval_repl ${SOURCE} eval_repl.cpp)
