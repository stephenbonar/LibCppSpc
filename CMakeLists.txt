# CMakeLists.txt - Builds the LibCppSpc project.
#
# Copyright (C) 2026 Stephen Bonar
#
# Lice nsed under the Apache License, Version 2.0 (the "License");
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

cmake_minimum_required(VERSION 3.10.0)

project(LibCppSpc VERSION 1.0.0 LANGUAGES C CXX)

if (WIN32)
    # By default, GoogleTest expects to statically link to the C++ runtime on 
    # the MSVC compiler. So if we run on Windows, we need to set our compiler 
    # flags to statically link the rest of the project to the runtime to match.
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

    if (MSVC)
        # Compiler warnings can intermittently appear and disappear. Set these
        # to see them consistently and enforce C++ standards.
        add_compile_options(/W4 /permissive-)
        add_compile_options(/external:W4)
    endif()
endif()

# Specify the C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

add_subdirectory(tests)
