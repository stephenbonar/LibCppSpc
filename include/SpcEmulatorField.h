// SpcEmulatorField.h - Declares the SpcEmulatorField class.
//
// Copyright (C) 2025 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SPC_EMULATOR_FIELD_H
#define SPC_EMULATOR_FIELD_H

#include <string>
#include "SpcNumericField.h"
#include "SpcNumericType.h"

/// @brief Represents a numeric field that indicates emulator used.
///
/// The same a SpcNumericField but with ToString() adjusted to interpret the
/// value to determine which emulator was used to dump the SPC file.
class SpcEmulatorField : public SpcNumericField
{
public:
    /// @brief Constructor; creates a new instance of SpcEmulatorField.
    /// @param label The label to use when outputing the field. 
    /// @param offset The offset where the field can be found in the file.
    /// @param size The size of the field, in bytes.
    SpcEmulatorField(std::string label, 
                     uintmax_t offset,
                     size_t size) 
    : SpcNumericField{ label, offset, size }
    { }

    /// @brief Constructor; creates a new instance of SpcEmulatorField.
    /// @param label The label to use when outputing the field. 
    /// @param offset The offset where the field can be found in the file.
    /// @param size The size of the field, in bytes.
    /// @param type Determines the numeric type of the field.
    SpcEmulatorField(std::string label, 
                     uintmax_t offset,
                     size_t size, 
                     SpcNumericType type) 
        : SpcNumericField{ label, offset, size, type }
    { }
    
    /// @brief Converts the field's data to a string representation.
    /// @return A string representation of the field's data.
    std::string ToString() const override;
};

#endif