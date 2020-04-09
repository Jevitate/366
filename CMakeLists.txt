cmake_minimum_required(VERSION 3.6)

project(Battleship)
enable_language(ASM_NASM)

#set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

set(CMAKE_CXX_STANDARD 14)


add_subdirectory(googletest)

add_subdirectory(src)

add_subdirectory(test)



