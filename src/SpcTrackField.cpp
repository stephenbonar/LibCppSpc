// SpcTrackField.cpp - Defines the SpcTrackField class.
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
 
#include "SpcTrackField.h"

uint8_t SpcTrackField::Value() const
{
    return static_cast<uint8_t>(data[1]);
}

char SpcTrackField::Suffix() const
{
    return data[0];
}

std::string SpcTrackField::ToString() const
{
    std::stringstream stream;

    if (Suffix() != 0)
        stream << std::to_string(Value()) << Suffix();
    else
        stream << std::to_string(Value());
        
    return stream.str();
}

void SpcTrackField::SetValue(std::string value)
{
    std::istringstream stream{ value };
    int trackNo;
    char trackChar;

    stream >> trackNo;

    if (stream >> trackChar)
        data[0] = trackChar;

    data[1] = trackNo;
}