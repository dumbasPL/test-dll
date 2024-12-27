cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(test_dll VERSION 1.0.0)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_language("RC")

set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/.cache/cpm")
include(cmake/get_cpm.cmake)

CPMAddPackage(
    NAME minhook
    GITHUB_REPOSITORY TsudaKageyu/minhook
    GIT_TAG master
)

add_executable(victim src/victim.c src/victim.rc)

add_library(hook SHARED src/hook.c)
target_link_libraries(hook PRIVATE minhook)
target_compile_options(hook PRIVATE /Zc:threadSafeInit- /sdl- /GS- /guard:cf-)