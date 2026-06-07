// TrackField.cpp - Defines the Spc::TrackField class.
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
#include <stdexcept>

using namespace Spc;

char TrackField::Suffix() const
{
    return rawData[0];
}

std::string TrackField::ToString() const
{
    std::stringstream stream;

    // Convert first to an int so it is not accidentally interpreted
    // as an ASCII value when converting to a string. But cast the byte to 
    // unsigned char first to avoid sign extension issues on certain platforms.
    const unsigned int trackByte = static_cast<unsigned char>(rawData[1]);

    stream << trackByte;

    if (Suffix() != 0)
    {
        stream << Suffix();
    }

    return stream.str();
}

void TrackField::SetValue(std::string value)
{
    if (value.empty())
    {
        throw std::invalid_argument("Track value cannot be empty");
    }

    size_t numericEnd{ 0 };
    while (numericEnd < value.size() &&
           std::isdigit(static_cast<unsigned char>(value[numericEnd])))
    {
        ++numericEnd;
    }

    if (numericEnd == 0)
    {
        throw std::invalid_argument("Track value must start with digits");
    }

    if (value.size() - numericEnd > 1)
    {
        throw std::invalid_argument(
            "Track value can only contain one suffix character");
    }

    const int trackNo = std::stoi(value.substr(0, numericEnd));
    if (trackNo < 0 || trackNo > 99)
    {
        throw std::out_of_range("Track number must be between 0 and 99");
    }

    rawData[0] = numericEnd < value.size() ? value[numericEnd] : '\0';
    rawData[1] = static_cast<char>(trackNo);
}