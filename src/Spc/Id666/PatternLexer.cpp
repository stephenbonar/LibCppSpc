// PatternLexer.cpp - Defines the PatternLexer class.
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

#include "Spc/Id666/PatternLexer.h"

using namespace Spc::Id666;

PatternToken PatternLexer::Lex()
{
    if (position >= pattern.size())
    {
        // Blank tokens are automatically end tokens.
        return PatternToken{ };
    }

    // We need to know when placeholders begin and end to properly tokenize 
    // the pattern.
    size_t nextPercent = pattern.find('%', position);
    bool startsWithPercent{ false };
    bool endsWithPercent{ false };

    if (nextPercent == position)
    {
        // If the next percent is at the current position, then this token 
        // starts with a percent sign.
        startsWithPercent = true;

        // See if this token ends with a percent sign.
        nextPercent = pattern.find('%', position + 1);

        if (nextPercent != std::string_view::npos)
        {
            endsWithPercent = true;
        }
    }
    else if (nextPercent != std::string_view::npos)
    {
        endsWithPercent = true;
    }
    
    std::string_view tokenView;

    if (startsWithPercent && endsWithPercent)
    {
        // The token started with a percent and we know it will end at the next
        // percent, so grab from the current position to the next percent,
        // including the ending percent sign itself.
        tokenView = pattern.substr(position, nextPercent - position + 1);
        position = nextPercent + 1;
    }
    else if (endsWithPercent)
    {
        // The token didn't start with a percent but ends with one, so grab
        // from the current position to just before the next percent.
        tokenView = pattern.substr(position, nextPercent - position);
        position = nextPercent;
    }
    else
    {
        // There are no more percent signs, so grab the rest of the pattern.
        tokenView = pattern.substr(position);
        position = pattern.size();
    }

    return PatternToken{ tokenView };
}