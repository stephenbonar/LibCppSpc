// PatternParser.h - Declares the PatternParser class.
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

#ifndef SPC_ID666_PATTERN_PARSER_H
#define SPC_ID666_PATTERN_PARSER_H

#include <string>
#include <vector>
#include "PatternToken.h"
#include "PatternNode.h"
#include "PatternNodeType.h"

namespace Spc::Id666
{
    /// @brief Parses pattern tokens into a syntax tree of pattern nodes.
    ///
    /// A file name pattern is first tokenized by the PatternLexer into a 
    /// sequence of tokens. The PatternParser takes those tokens and parses
    /// them into a syntax tree of PatternNode objects. The Spc::File class can
    /// then use the syntax tree to generate file names according to the 
    /// pattern or extract values from the file name into the tag fields.
    ///
    /// @invariant The parser does not modify the tokens or their order.
    class PatternParser
    {
    public:
        /// @brief Constructs a PatternParser with the given tokens.
        /// @param tokens The tokens to parse into a syntax tree.
        PatternParser(std::vector<PatternToken> tokens) 
            : tokens{ tokens }
        { }

        /// @brief Parses the tokens into a syntax tree of pattern nodes.
        /// @return A vector of pattern nodes representing the syntax tree.
        std::vector<PatternNode> Parse() const;
    private:
        std::vector<PatternToken> tokens;
    };
}

#endif