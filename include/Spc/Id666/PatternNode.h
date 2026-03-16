// PatternNode.h - Declares the PatternNode class.
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

#ifndef SPC_ID666_PATTERN_NODE_H
#define SPC_ID666_PATTERN_NODE_H

#include <string>
#include "PatternNodeType.h"

namespace Spc::Id666
{
    /// @brief Represents a node in the syntax tree parsed from a pattern.
    ///
    /// A file name pattern is parsed into a syntax tree of PatternNode objects. 
    /// Each node represents a portion of the pattern, such as a literal string
    /// or a placeholder.
    struct PatternNode
    {
        /// @brief The portion of the pattern that this node represents.
        std::string_view lexeme;

        /// @brief The type of syntax node this is (e.g., literal, placeholder).
        PatternNodeType type;
    };
}

#endif