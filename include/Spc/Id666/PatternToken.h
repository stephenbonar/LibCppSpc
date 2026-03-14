// PatternToken.h - Declares the PatternToken class.
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
#include "PatternTokenType.h"

namespace Spc::Id666
{
    class PatternToken
    {
    public:
        PatternToken() { }

        PatternToken(std::string_view lexeme) : lexeme{ lexeme }
        { }
        
        PatternTokenType Type() const;

        std::string_view Lexeme() const { return lexeme; }
    private:
        std::string_view lexeme;
    };
}

#endif