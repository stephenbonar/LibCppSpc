// PatternParser.h - Declares the PatternParser class.
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

#ifndef SPC_ID666_PATTERN_PARSER_H
#define SPC_ID666_PATTERN_H

#include <string>
#include <vector>
#include "PatternToken.h"

namespace Spc::Id666
{
    class PatternParser
    {
    public:
        PatternParser();

        bool Parse(std::string pattern);

        std::vector<PatternToken> Tokens() const { return tokens; }
    private:
        std::vector<PatternToken> tokens;
    };
}

#endif