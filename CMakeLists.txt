cmake_minimum_required(VERSION 3.30)
project(LoxLang)

set(CMAKE_CXX_STANDARD 23)

set(LLVM_INSTALL_DIR "" CACHE PATH "LLVM installation directory")
list(APPEND CMAKE_PREFIX_PATH "${LLVM_INSTALL_DIR}/lib/cmake/llvm/")

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM Include Directory: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM Library Directory: ${LLVM_LIBRARY_DIRS}")

include_directories(${LLVM_INCLUDE_DIRS})

link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(LLVM_LIBS core support irreader)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(lib)

add_executable(LoxLang main.cpp)

target_link_libraries(LoxLang PUBLIC LoxLangLib ${LLVM_LIBS})
