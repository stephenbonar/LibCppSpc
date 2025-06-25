// TagType.h - Declares the TagType enum.
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

#ifndef SPC_TAG_TYPE_H
#define SPC_TAG_TYPE_H

namespace Spc
{
    /// @brief Represents the type of the ID666 tag.
    enum class TagType
    {
        /// @brief The tag has binary representation of numeric values.
        Binary,

        /// @brief The tag has text representation of numeric values.
        Text,

        /// @brief The tag has text offsets, but some numeric values are binary.
        TextMixed
    };
}

#endif