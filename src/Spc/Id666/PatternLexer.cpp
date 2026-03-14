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
        return PatternToken{ };
    }

    size_t nextPercent = pattern.find('%', position);
    bool startsWithPercent{ false };
    bool endsWithPercent{ false };

    if (nextPercent == position)
    {
        startsWithPercent = true;
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
        tokenView = pattern.substr(position, nextPercent - position + 1);
        position = nextPercent + 1;
    }
    else if (endsWithPercent)
    {
        tokenView = pattern.substr(position, nextPercent - position);
        position = nextPercent;
    }
    else
    {
        tokenView = pattern.substr(position);
        position = pattern.size();
    }

    return PatternToken{ tokenView };
}