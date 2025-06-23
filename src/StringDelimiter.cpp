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

#include "StringDelimiter.h"

int StringDelimiter::GetIndex(std::string text) const
{
    int index{ -1 };
    char nextValueChar;
    std::stringstream valueStream;

    for (int i = 0; i < text.length(); i++)
    {
        if (index == -1)
        {
            valueStream = std::stringstream{ value };
            nextValueChar = valueStream.get();

            if (text[i] == nextValueChar)
                index = i;
        }
        else
        {
            if (!valueStream.eof())
            {
                nextValueChar = valueStream.get();

                if (nextValueChar == -1)
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