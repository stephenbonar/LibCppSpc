// StringTokenizer.h - Declares the StringTokenizer class.
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

#ifndef SPC_STRING_TOKENIZER_H
#define SPC_STRING_TOKENIZER_H

#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "StringDelimiter.h"
#include "StringToken.h"
#include "StringSegment.h"

namespace Spc
{
    class StringTokenizer
    {
    public:
        StringTokenizer(std::string pattern) { ParsePattern(pattern); }

        std::vector<std::shared_ptr<StringToken>> Tokenize(std::string text);

        std::vector<std::shared_ptr<StringSegment>> Segments()
        {
            return segments; 
        }
    private:
        std::vector<std::shared_ptr<StringSegment>> segments;

        void AddDelimiter(std::stringstream& stream);

        void AddToken(std::stringstream& stream);

        std::shared_ptr<StringToken> InitToken(std::string name);

        void ParsePattern(std::string pattern);

        void ParseToken(std::shared_ptr<StringToken> token, std::string& text);

        void ParseToken(std::shared_ptr<StringToken> token, 
                        std::shared_ptr<StringSegment> next,
                        std::string& text);

        void ParseDelimiter(std::shared_ptr<StringDelimiter>, 
                            std::string& text);
    };
}

#endif