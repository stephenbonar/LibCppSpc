# CMakeLists.txt - Builds the LibCppSpc library examples.
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

# Defines the example executable target.
add_executable(example example.cpp)

# Links the libraries to the example executable target.
target_link_libraries(example LibCppSpc)

# Sets the include directories the exectable target needs for linking.
target_include_directories(example 
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}/include)