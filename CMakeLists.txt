cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(IS_HW FALSE)

project(lab-or-hw)

if (CMAKE_VERSION GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif ()

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 20)

# Source sets for targets
set(SRC_MAIN_FILES src/main/cpp/main.cpp
        src/main/cpp/expanded_templates.cpp)
set(SRC_DEMO_FILES src/main/cpp/demo.cpp
        src/main/cpp/expanded_templates.cpp
)
set(SRC_UNIT_TESTS src/test/cpp/unit_tests.cpp
        src/main/cpp/expanded_templates.cpp)

add_executable(main ${SRC_MAIN_FILES})
add_executable(demo ${SRC_DEMO_FILES})

# Setup Google Test
set(GOOGLE_TEST_ARCHIVE "v1.17.0")
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/${GOOGLE_TEST_ARCHIVE}.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)
add_executable(unit_tests ${SRC_UNIT_TESTS})
target_link_libraries(unit_tests PRIVATE GTest::gtest) # NOTE: not gtest_main
target_link_libraries(unit_tests PRIVATE GTest::gmock GTest::gtest)
gtest_discover_tests(unit_tests)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(demo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(unit_tests PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)

# add custom commands that copy data input files to target working directories
add_custom_command(TARGET main POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/main_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET demo POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/demo_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET unit_tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task1_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET unit_tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task2_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET unit_tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task3_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})

if (IS_HW)
    add_custom_command(TARGET unit_tests PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task4_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
    add_custom_command(TARGET unit_tests PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/task5_test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
endif ()



# --- Doxygen integration that uses config/Doxyfile.in ---

# Ask CMake to find doxygen and (optionally) Graphviz's 'dot' for diagrams.
find_package(Doxygen OPTIONAL_COMPONENTS dot)  # 'dot' is used for diagrams if present. [1](https://cmake.org/cmake/help/latest/module/FindDoxygen.html)

if (Doxygen_FOUND)
  # Where the configured Doxyfile will be written
  set(DOXYFILE_CFG            "${CMAKE_BINARY_DIR}/Doxyfile")

  # These variables can be substituted into Doxyfile.in with @VAR@.
  # Feel free to tweak the INPUT paths to match your project’s sources.
  set(PROJECT_SOURCE_DIR_ESC  "${CMAKE_SOURCE_DIR}")
  set(PROJECT_BINARY_DIR_ESC  "${CMAKE_BINARY_DIR}")

  # Where you want the generated HTML to land → api/html (per your requirement)
  set(DOXY_OUTPUT_DIR         "${CMAKE_SOURCE_DIR}/api")
  set(DOXY_HTML_OUTPUT        "html")

  # Optional: If you want diagrams and Graphviz is present, set HAVE_DOT=YES via Doxyfile.in.
  if (TARGET Doxygen::dot)
    set(HAVE_DOT_DEFAULT "YES")  # honored only if Doxyfile.in uses @HAVE_DOT_DEFAULT@
  else()
    set(HAVE_DOT_DEFAULT "NO")
  endif()

  # Configure your template (no variable expansion other than @VAR@).
  configure_file(
    "${CMAKE_SOURCE_DIR}/config/Doxyfile.in"
    "${DOXYFILE_CFG}"
    @ONLY
  )  # This is the standard pattern to drive Doxygen from a Doxyfile template. [2](https://vicrucann.github.io/tutorials/quick-cmake-doxygen/)

  message(STATUS "Doxygen configured → ${DOXYFILE_CFG}")

  # Create a build target to generate docs
  add_custom_target(doc_doxygen
    COMMAND ${Doxygen_EXECUTABLE} "${DOXYFILE_CFG}"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"   # So relative INPUT in Doxyfile works from the repo root. [3](https://stackoverflow.com/questions/60955881/cmake-for-doxygen)
    COMMENT "Generating API documentation with Doxygen (output: ${DOXY_OUTPUT_DIR}/${DOXY_HTML_OUTPUT})"
    VERBATIM
  )
else()
  message(STATUS "Doxygen not found; 'doc_doxygen' target will be unavailable.")
endif()
