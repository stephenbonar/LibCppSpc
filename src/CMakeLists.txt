# CMakeLists.txt - Builds the LibCppSpc.
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

set(SOURCES 
    Spc/BinaryField.cpp
    Spc/Header.cpp
    Spc/Field.cpp
    Spc/Format.cpp
    Spc/DataStructure.cpp
    Spc/DateField.cpp
    Spc/NumericField.cpp
    Spc/FieldInfo.cpp
    Spc/EmulatorField.cpp
    Spc/TrackField.cpp
    Spc/TextField.cpp
    Spc/File.cpp
    Spc/Id666/Tag.cpp
    Spc/Id666/Pattern/Constants.cpp
    Spc/Id666/Pattern/Token.cpp
    Spc/Id666/Pattern/Lexer.cpp
    Spc/Id666/Pattern/Parser.cpp
    Spc/Id666/Extended/Item.cpp
    Spc/Id666/Extended/Data.cpp)

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
    URL https://github.com/stephenbonar/LibCppBinary/archive/e5a0774c46209ae7ca7d4ab9f22640dc2bd07e6a.zip
)

# Makes LibCppBinary available at configure time rather than build time.
FetchContent_MakeAvailable(LibCppBinary)

# Do not build dependency tests as part of this project's default build.
if(TARGET libcppbinarytests)
    set_target_properties(libcppbinarytests PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()

# Define the library target so a static library can be built from sources.
add_library(LibCppSpc ${SOURCES})

# Remove the default "lib" prefix from the library name to match the naming 
# convention of other libraries in this project.
set_target_properties(LibCppBinary PROPERTIES PREFIX "")
set_target_properties(LibCppSpc PROPERTIES PREFIX "")

# Configure the include directories so the compiler knows where to find the 
# header files.
target_include_directories(LibCppSpc PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Link the library target to the LibCppBinary dependency.
target_link_libraries(LibCppSpc ${LIBRARIES})