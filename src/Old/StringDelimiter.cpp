// StringDelimiter.cpp - Defines the StringDelimier class.
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

#include "Spc/StringDelimiter.h"

using namespace Spc;

int StringDelimiter::GetIndex(std::string text) const
{
    constexpr int eof{ -1 };
    int index{ -1 };

    // the get() method on stringstream returns characters as int values.
    int nextValueCharInt;
    char nextValueChar;

    std::stringstream valueStream;

    for (int i = 0; i < text.length(); i++)
    {
        if (index == -1)
        {
            valueStream = std::stringstream{ value };
            nextValueCharInt = valueStream.get();
            nextValueChar = static_cast<char>(nextValueCharInt);

            if (text[i] == nextValueChar)
                index = i;
        }
        else
        {
            if (!valueStream.eof())
            {
                nextValueCharInt = valueStream.get();
                nextValueChar = static_cast<char>(nextValueCharInt);

                if (nextValueChar == eof)
                    return index;
                else if (text[i] != nextValueChar)
                    index = -1;
            }
            else
            {
                return index;
            }
        }
    }

    return index;
}