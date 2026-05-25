# CMakeLists.txt - Builds the LibCppSpc library tests.
#
# Copyright (C) 2026 Stephen Bonar
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http ://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Resolve DOWNLOAD_EXTRACT_TIMESTAMP warning policy by using new behavior.
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# Using FetchContent as opposed to submodules ensures if multiple projects use
# GoogleTest, CMake will only use one, avoiding conflicts. 
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Makes GoogleTest available at configure time rather than build time. 
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Defines the test executable target.
add_executable(libcppspctests
               BinaryFieldTests.cpp
               DataStructureTests.cpp
               DateFieldTests.cpp
               EmulatorFieldTests.cpp
               FileTests.cpp
               FormatTests.cpp
               HeaderTests.cpp
               ID666ExtendedDataTests.cpp
               ID666ExtendedItemTests.cpp
               ID666TagTests.cpp
               FieldTests.cpp
               NumericFieldTests.cpp
               TextFieldTests.cpp
               TrackFieldTests.cpp
               PatternTokenTests.cpp
               PatternLexerTests.cpp
               PatternParserTests.cpp)

# Links the libraries to the test executable target.
target_link_libraries(libcppspctests
                      LibCppSpc
                      gmock_main)

# Sets the include directories the exectable target needs for linking.
target_include_directories(libcppspctests 
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}/include
                           ${CMAKE_CURRENT_SOURCE_DIR}) # Ensure MockEmulatorField.h is included

# Register all TEST/TEST_F cases in the executable as CTest tests.
gtest_discover_tests(libcppspctests)