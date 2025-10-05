# CMakeLists.txt - Builds the LibCppSpc library tests.
#
# Copyright (C) 2025 Stephen Bonar
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
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Makes GoogleTest available at configure time rather than build time. 
FetchContent_MakeAvailable(googletest)

# Defines the test executable target.
add_executable(libcppspctests
               BinaryFieldTests.cpp
               BinaryTagTests.cpp
               DataStructureTests.cpp
               DateFieldTests.cpp)

# Links the libraries to the test executable target.
target_link_libraries(libcppspctests
                      LibCppSpc
                      gtest
                      gtest_main
                      gmock)

# Sets the include directories the exectable target needs for linking.
target_include_directories(libcppspctests 
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}/include)