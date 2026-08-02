// EmulatorField.cpp - Defines the Spc::EmulatorField class.
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

#include "Spc/EmulatorField.h"

using namespace Spc;

constexpr int asciiZero{ 0x30 };
constexpr int asciiOne{ 0x31 };
constexpr int asciiTwo{ 0x32 };

std::string EmulatorField::ToString() const
{
    switch (DetectInt32())
    {
        case 1:
            return "ZSNES";
        case 2:
            return "SNES9X";
        default:
            return "Unknown";
    }
}

void EmulatorField::SetValue(const std::string& value)
{
    if (Type() == NumericType::Binary)
    {
        if (value == "ZSNES")
        {
            SetInt32(1);
        }
        else if (value == "SNES9X")
        {
            SetInt32(2);
        }
        else
        {
            SetInt32(0);
        }
    }
    else
    {
        if (value == "ZSNES")
        {
            rawData[0] = asciiOne;
        }
        else if (value == "SNES9X")
        {
            rawData[0] = asciiTwo;
        }
        else
        {
            rawData[0] = asciiZero;
        }
    }
}   