// SpcTextField.h - Declares the SpcTextField class.
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

#ifndef SPC_TEXT_FIELD_H
#define SPC_TEXT_FIELD_H

#include <string>
#include "SpcField.h"
#include "LibCppBinary.h"

/// @brief Represents a field containing text in an SPC file.
///
/// Texts fields are to be used for fields that are guaranteed to contain
/// strings of ASCII text. They should not be used for fields that can contain
/// text or binary representations of numbers.
class SpcTextField : public SpcField
{
public:
    /// @brief Constructor; creates a new instance of SpcField.
    /// @param label The label to use when outputing the field. 
    /// @param offset The offset where the field can be found in the file.
    /// @param size The size of the field, in bytes.
    SpcTextField(std::string label, uintmax_t offset, size_t size) :
        SpcField{ label, offset, size }
    { }

    /// @brief Gets the text value of the field.
    /// @return A string representing the text value of the field.
    std::string Value() const { return ToString(); }

    /// @brief Sets the text value of the field.
    /// @param value The value to set.
    void SetValue(std::string value);
    
    /// @brief Converts the field's data to a string representation.
    /// @return A string representation of the field's data.
    std::string ToString() const override
    {
        return Binary::RawField::ToString(Binary::StringFormat::Terminated);
    }
};

#endif