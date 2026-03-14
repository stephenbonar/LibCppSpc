// TrackField.cpp - Defines the TrackField class.
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
 
#include "Spc/TrackField.h"

using namespace Spc;

/*
uint8_t TrackField::Value() const
{
    return static_cast<uint8_t>(rawData[1]);
}
*/

char TrackField::Suffix() const
{
    return rawData[0];
}

std::string TrackField::ToString() const
{
    std::stringstream stream;

    auto trackNum = static_cast<uint8_t>(rawData[1]);

    if (Suffix() != 0)
        stream << trackNum << Suffix();
    else
        stream << trackNum;
        
    return stream.str();
}

void TrackField::SetValue(std::string value)
{
    std::istringstream stream{ value };
    uint8_t trackNo;
    char trackChar;

    stream >> trackNo;

    if (stream >> trackChar)
        rawData[0] = trackChar;

    rawData[1] = trackNo;
}