// Lexer.cpp - Defines the Lexer class.
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

#include "Spc/Id666/Pattern/Lexer.h"

using namespace Spc::Id666::Pattern;

Token Lexer::Lex()
{
    if (position >= pattern.size())
    {
        // Blank tokens are automatically end tokens.
        return Token{ };
    }

    // We need to know when placeholders begin and end to properly tokenize 
    // the pattern.
    size_t nextPlaceholderChar = pattern.find(placeholderChar, position);
    bool startsWithPlaceholderChar{ false };
    bool endsWithPlaceholderChar{ false };

    if (nextPlaceholderChar == position)
    {
        // If the next placeholder character is at the current position, then 
        //this token starts with a placeholder character.
        startsWithPlaceholderChar = true;

        // See if this token ends with a placeholder character.
        nextPlaceholderChar = pattern.find(placeholderChar, position + 1);

        if (nextPlaceholderChar != std::string_view::npos)
        {
            endsWithPlaceholderChar = true;
        }
    }
    else if (nextPlaceholderChar != std::string_view::npos)
    {
        endsWithPlaceholderChar = true;
    }
    
    std::string_view tokenView;

    if (startsWithPlaceholderChar && endsWithPlaceholderChar)
    {
        // The token started with a placeholder character and we know it will 
        // end at the next placeholder character, so grab from the current
        // position to the next placeholder character, including the ending 
        // placeholder character itself.
        const size_t numChars{ nextPlaceholderChar - position + 1 };
        tokenView = pattern.substr(position, numChars);
        position = nextPlaceholderChar + 1;
    }
    else if (endsWithPlaceholderChar)
    {
        // The token didn't start with a placeholder character but ends with 
        // one, so grab from the current position to just before the next 
        // placeholder character.
        tokenView = pattern.substr(position, nextPlaceholderChar - position);
        position = nextPlaceholderChar;
    }
    else
    {
        // There are no more placeholder characters, so grab the rest of the 
        // pattern.
        tokenView = pattern.substr(position);
        position = pattern.size();
    }

    return Token{ tokenView };
}