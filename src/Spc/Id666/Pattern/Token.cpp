// Token.cpp - Defines the Token class.
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

#include "Spc/Id666/Pattern/Token.h"

using namespace Spc::Id666::Pattern;

TokenType Token::Type() const 
{
    if (lexeme.empty())
    {
        return TokenType::End;
    }
    else if (lexeme.front() == placeholderChar && 
             lexeme.back() == placeholderChar)
    {
        return TokenType::Placeholder;
    }
    else
    {
        return TokenType::Literal;
    }
}