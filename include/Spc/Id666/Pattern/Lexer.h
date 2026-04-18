// Lexer.h - Declares the Spc::Id666::Pattern::Lexer class.
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

#ifndef SPC_ID666_PATTERN_LEXER_H
#define SPC_ID666_PATTERN_LEXER_H

#include <string>
#include "Token.h"
#include "Constants.h"

namespace Spc::Id666::Pattern
{
    /// @brief Responsible for tokenizing pattern strings.
    ///
    /// The Lexer class takes a file name pattern string and breaks it 
    /// down into individual tokens for further processing.
    ///
    /// @invariant Tokens returned in sequential order.
    /// @invariant Tokens never skip or repeat.
    /// @invariant End token is returned when the end of the pattern is reached.
    class Lexer
    {
    public:
        /// @brief Constructs a Lexer with the given pattern string.
        /// @param pattern The pattern string to tokenize.
        Lexer(std::string_view pattern) 
            : pattern{ pattern }, position{ 0 } 
        { }

        /// @brief Lexes the next token from the pattern string.
        /// @return The next Token.
        /// @pre The pattern string must remain valid when calling this method.
        /// @post The position is advanced to the next token.
        /// @post If the end is reached, subsequent calls return an End token.
        Token Lex();
    private:
        std::string_view pattern;
        size_t position;
    };
}

#endif