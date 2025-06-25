// Format.h - Declares functions for formatting SPC fields.
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

#ifndef SPC_FORMAT_H
#define SPC_FORMAT_H

#include <iomanip>
#include <sstream>
#include "Field.h"

namespace Spc
{
    /// @brief Formats the specified value prefixed with the specified label.
    /// @param label The label to use.
    /// @param value The value to label.
    /// @return A string representing the formatted value.
    std::string FormatValue(std::string label, std::string value);

    /// @brief Formats the specified field as as string in label: value format.
    /// @param field The field to output as a formatted string.
    /// @return The formatted string representation of the field.
    std::string FormatField(Field* field);
}

#endif