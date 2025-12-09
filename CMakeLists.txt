cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(IS_HW FALSE)

project(lab-or-hw)

option(ENABLE_SANITIZERS "Enable sanitizers in Debug builds" ON)

if (ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Sanitizers enabled for Debug build!")
        set(SANITIZER_FLAGS "-fsanitize=address,undefined,leak -fno-omit-frame-pointer")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZER_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
    endif ()
endif ()

if (CMAKE_VERSION GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif ()

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 20)

# Source sets for targets
set(SRC_MAIN_FILES src/main/cpp/main.cpp
        src/main/cpp/expanded_templates.cpp)
set(SRC_DEMO_FILES src/main/cpp/demo.cpp
        src/main/cpp/expanded_templates.cpp)
set(SRC_TEST_TASK1 src/test/cpp/test_task1.cpp
        src/main/cpp/expanded_templates.cpp)
set(SRC_TEST_TASK2 src/test/cpp/test_task2.cpp
        src/main/cpp/expanded_templates.cpp)
set(SRC_TEST_TASK3 src/test/cpp/test_task3.cpp
        src/main/cpp/expanded_templates.cpp)

# Setup Google Test
set(GOOGLE_TEST_ARCHIVE "v1.17.0")
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/${GOOGLE_TEST_ARCHIVE}.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(main ${SRC_MAIN_FILES})
add_executable(demo ${SRC_DEMO_FILES})
add_executable(test_task1 ${SRC_TEST_TASK1})
add_executable(test_task2 ${SRC_TEST_TASK2})
add_executable(test_task3 ${SRC_TEST_TASK3})

# Now simply link against gtest or gtest_main as needed.
target_link_libraries(test_task1 GTest::gtest_main)
target_link_libraries(test_task2 GTest::gtest_main)
target_link_libraries(test_task3 GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_task1)
gtest_discover_tests(test_task2)
gtest_discover_tests(test_task3)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(demo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(test_task1 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(test_task2 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(test_task3 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)

# add custom commands that copy data input files to target working directories
add_custom_command(TARGET main POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/main_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET demo POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/demo_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET test_task1 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task1_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET test_task2 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task2_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET test_task3 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task3_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})

if (IS_HW)
    set(SRC_TASK4_TEST_FILES src/test/cpp/test_task4.cpp
            src/main/cpp/expanded_templates.cpp)
    set(SRC_TASK5_TEST_FILES src/test/cpp/test_task5.cpp
            src/main/cpp/expanded_templates.cpp)
    add_executable(test_task4 ${SRC_TASK4_TEST_FILES})
    add_executable(test_task5 ${SRC_TASK5_TEST_FILES})
    target_link_libraries(test_task4 GTest::gtest_main)
    target_link_libraries(test_task5 GTest::gtest_main)
    gtest_discover_tests(test_task4)
    gtest_discover_tests(test_task5)
    target_include_directories(test_task4 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
    target_include_directories(test_task5 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
    add_custom_command(TARGET test_task4 PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task4_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
    add_custom_command(TARGET test_task5 PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task5_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
endif ()

# first we can indicate the documentation build as an option and set it to OFF by default
option(BUILD_DOC "Build documentation" OFF)
find_package(Doxygen
        OPTIONAL_COMPONENTS dot mscgen dia)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/config/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the config together with the application
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
