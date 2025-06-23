// SpcDateField.h - Declares the SpcDateField class.
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

#ifndef SPC_DATE_FIELD_H
#define SPC_DATE_FIELD_H

#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "SpcField.h"

/// @brief Represents a field containing a date in an SPC file.
///
/// Date dumped can either have a text or binary representation. This field
/// can determine which representation is used and output the date in the
/// correct format based on the representation.
class SpcDateField : public SpcField
{
public:
    /// @brief Constructor; creates a new instance of SpcDateField.
    /// @param label The label to use when outputing the field. 
    /// @param offset The offset where the field can be found in the file.
    /// @param size The size of the field, in bytes.
    SpcDateField(std::string label, uintmax_t offset, size_t size) 
        : SpcField{ label, offset, size }
    { }

    /// @brief Determines if the field has a text representation of date.
    /// @return True if it has a text representation or false if binary.
    bool IsText() const;

    /// @brief Determines if bytes 4 - 7 are unused, which indicates binary.
    /// @return True if 4 - 7 are 0, otherwise false. 
    bool HasUnusedArea() const;

    /// @brief Determines if the date is set.
    /// @return Returns true if it is set, otherwise false.
    bool IsSet() const;

    std::string Value() const;

    void SetTextValue(std::string value);

    void SetBinaryValue(std::string value);

    /// @brief Converts the field's data to a string representation.
    /// @return A string representation of the field's data.
    std::string ToString() const override { return Value(); }
};

#endif