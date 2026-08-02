// Format.h - Declares functions for formatting SPC fields.
//
// Copyright (C) 2026 Stephen Bonar
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

#ifndef SPC_FORMAT_H
#define SPC_FORMAT_H

#include <iomanip>
#include <sstream>
#include "Field.h"

namespace Spc
{
    // This value is enough to fit all labels with at least one space after.
    inline constexpr int labelSize{ 26 };

    // This value perfectly wraps hexadecimal output.
    inline constexpr int valueChunkSize{ 51 };

    /// @brief The ASCII value of the '0' character.
    inline constexpr int asciiZero{ 0x30 };

    /// @brief The ASCII value of the '9' character.
    inline constexpr int asciiNine{ 0x39 };

    /// @brief Formats the specified value prefixed with the specified label.
    /// @param label The label to use.
    /// @param value The value to label.
    /// @return A string representing the formatted value.
    std::string FormatValue(const std::string& label,
                            const std::string& value);

    /// @brief Formats the specified field as as string in label: value format.
    /// @param field The field to output as a formatted string.
    /// @return The formatted string representation of the field.
    std::string FormatField(const Field& field);
}

#endif