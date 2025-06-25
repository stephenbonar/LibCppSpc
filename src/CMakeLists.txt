# CMakeLists.txt - Builds the LibCppSpc.
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

set(SOURCES 
    Header.cpp
    BinaryTag.cpp
    TextTag.cpp
    ExtendedTag.cpp
    FileStream.cpp
    Format.cpp
    DataStructure.cpp
    ExtendedTagItem.cpp
    DateField.cpp
    NumericField.cpp
    EmulatorField.cpp
    File.cpp
    TrackField.cpp
    TextField.cpp
    StringDelimiter.cpp
    StringTokenizer.cpp)

set(LIBRARIES LibCppBinary)

# Resolve DOWNLOAD_EXTRACT_TIMESTAMP warning policy by using new behavior.
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# Using FetchContent as opposed to submodules ensures if multiple projects use
# LibCppBinary, CMake will only use one, avoiding conflicts. 
include(FetchContent)
FetchContent_Declare(
    LibCppBinary
    URL https://github.com/stephenbonar/LibCppBinary/archive/a9b8210d7e73072335df960a8081e368877fb1a2.zip
)

# Makes GoogleTest available at configure time rather than build time. 
FetchContent_MakeAvailable(LibCppBinary)

add_library(LibCppSpc ${SOURCES})

set_target_properties(LibCppBinary PROPERTIES PREFIX "")
set_target_properties(LibCppSpc PROPERTIES PREFIX "")

target_include_directories(LibCppSpc PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(LibCppSpc ${LIBRARIES})