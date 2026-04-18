// NodeType.h - Declares the Spc::Id666::Pattern::NodeType class.
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

#ifndef SPC_ID666_PATTERN_NODE_TYPE_H
#define SPC_ID666_PATTERN_NODE_TYPE_H

namespace Spc::Id666::Pattern
{
    /// @brief The type of node in the syntax tree parsed from a pattern.
    ///
    /// The syntax of a file name pattern can be represented as literals or
    /// placeholders of various types. 
    enum class NodeType
    {
        /// @brief A literal portion of the pattern that should be output as is.
        Literal,

        /// @brief A placeholder that should be replaced with a text value.
        TextPlaceholder,

        /// @brief A placeholder that should be replaced with a numeric value.
        NumericPlaceholder,

        /// @brief Marks the end of the pattern.
        End
    };
}

#endif