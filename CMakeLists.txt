cmake_minimum_required(VERSION 2.8.12)
project(jax)

#
# Configures the compiler, regardless of the build type.
#
if("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  add_definitions(-std=c++11
                  -stdlib=libc++
                  -Weverything
                  -Wno-c++98-compat
                  )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  add_definitions(-std=c++11
                  -Wall
                  -Wextra
                  -Wpedantic)
endif()

#
# If `git` is installed locally, perform an automatic update of submodules.
#
find_package(Git)
if(GIT_FOUND)
  message("Updating Git submodules with ${GIT_EXECUTABLE} ${GIT_VERSION_STRING}")
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive)
endif(GIT_FOUND)

#
# Use `make doc` to generate API documentation.
#
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html
          DESTINATION doc)
endif(DOXYGEN_FOUND)

#
# Adds the include directory to the compiler's search path.
#
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

#
# Builds the test driver. This can be launched with either `make test` or `ctest`
#
enable_testing()

add_executable(test_json_parser_null ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_null.cpp)
add_test(test_json_parser_null test_json_parser_null)

add_executable(test_json_parser_false ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_false.cpp)
add_test(test_json_parser_false test_json_parser_false)

add_executable(test_json_parser_true ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_true.cpp)
add_test(test_json_parser_true test_json_parser_true)

add_executable(test_json_parser_int ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_int.cpp)
add_test(test_json_parser_int test_json_parser_int)

add_executable(test_json_parser_float ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_float.cpp)
add_test(test_json_parser_float test_json_parser_float)

add_executable(test_json_parser_string ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_string.cpp)
add_test(test_json_parser_string test_json_parser_string)

add_executable(test_json_parser_empty_array ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_empty_array.cpp)
add_test(test_json_parser_empty_array test_json_parser_empty_array)

add_executable(test_json_parser_single_element_array ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_single_element_array.cpp)
add_test(test_json_parser_single_element_array test_json_parser_single_element_array)

add_executable(test_json_parser_multi_element_array ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_multi_element_array.cpp)
add_test(test_json_parser_multi_element_array test_json_parser_multi_element_array)

add_executable(test_json_parser_empty_object ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_empty_object.cpp)
add_test(test_json_parser_empty_object test_json_parser_empty_object)

add_executable(test_json_parser_single_element_object ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_single_element_object.cpp)
add_test(test_json_parser_single_element_object test_json_parser_single_element_object)

add_executable(test_json_parser_multi_element_object ${CMAKE_CURRENT_SOURCE_DIR}/test/test_json_parser_multi_element_object.cpp)
add_test(test_json_parser_multi_element_object test_json_parser_multi_element_object)

#add_executable(TEST ${CMAKE_CURRENT_SOURCE_DIR}/test/TEST.cpp)
#add_test(TEST TEST)

