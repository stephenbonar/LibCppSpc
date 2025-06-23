// SetCommand.h - Declares the SetCommand struct.
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

#ifndef SET_COMMAND_H
#define SET_COMMAND_H

#include <memory>
#include <string>
#include "ID666ExtendedItem.h"

/// @brief Represents the parameters of a set operation.
/// @tparam T The type of SPC field being set.
template<typename T>
struct SetCommand
{
    /// @brief A pointer to the field on the binary tag.
    T* binaryField;

    /// @brief A pointer to the field on the text tag.
    T* textField;

    /// @brief The extended item ID.
    int extendedID;

    /// @brief The extended item type.
    int extendedType;

    /// @brief The value to set on the field.
    std::string value;
};

#endif