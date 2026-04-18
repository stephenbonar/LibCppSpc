// Token.h - Declares the Spc::Id666::Pattern::Token class.
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

#ifndef SPC_ID666_PATTERN_TOKEN_H
#define SPC_ID666_PATTERN_TOKEN_H

#include <string>
#include "TokenType.h"
#include "Constants.h"

namespace Spc::Id666::Pattern
{
    /// @brief Represents a token in the pattern string.
    ///
    /// A file name pattern is first tokenized by the Lexer into a 
    /// sequence of Token objects. Each token represents a portion of the
    /// pattern, such as a literal string or a placeholder. The Parser
    /// then takes these tokens and parses them into a syntax tree of 
    /// Node objects.
    ///
    /// @invariant The lexeme must reference a valid string for token lifetime.
    /// @invariant The lexeme does not change after the token is created.
    /// @invariant The token type is determined solely by the lexeme content.
    class Token
    {
    public:
        /// @brief Default constructor; creates an empty (end) token.
        Token() { }

        /// @brief Constructs a Token with the given lexeme.
        /// @param lexeme The portion of the pattern that this token represents.
        /// @pre The lexeme string_view must reference a valid string.
        Token(std::string_view lexeme) : lexeme{ lexeme }
        { }
        
        /// @brief Determines the type of the token based on its lexeme.
        ///
        /// This method determines the type of the token by analyzing its 
        /// lexeme. If the lexeme is empty, it is an End token. If it matches
        /// a known placeholder, it is a Placeholder token. Otherwise,
        /// it is a Literal token.
        ///
        /// @return The TokenType of this token.
        TokenType Type() const;

        /// @brief Returns the portion of the pattern this token represents.
        /// @return The lexeme of this token.
        std::string_view Lexeme() const { return lexeme; }
    private:
        std::string_view lexeme;
    };
}

#endif