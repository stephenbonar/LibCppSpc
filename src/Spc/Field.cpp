// Field.cpp - Defines the Field class.
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

#include "Spc/Field.h"

using namespace Spc;

void Field::SetValue(std::string value)
{
    std::istringstream hexStream{ value };
    std::string token;
    int index{ 0 };

    while (hexStream >> token)
    {
        if (token.length() != 2)
        {
            throw std::invalid_argument{ 
                "Each byte must be represented by exactly two hex digits." };
        }

        uint8_t byte = static_cast<uint8_t>(std::stoul(token, nullptr, 16));
        
        if (index < size)
        {
            rawData[index] = byte;
            index++;
        }
        else
        {
            break;
        }
    }
}
