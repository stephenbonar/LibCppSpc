// DateField.cpp - Defines the DateField class.
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

#include "DateField.h"

using namespace Spc;

DateField::DateField(std::string label, uintmax_t offset, size_t size)
    : Field{ label, offset, size }
{
    if (size < 11)
        throw std::invalid_argument{ "DateField size must be at least 11." };
}

bool DateField::IsText() const
{
    for (int i = 0; i < size; i++)
    {
        bool isAsciiNum = rawData[i] >= 0x30 && rawData[i] <= 0x39;
        bool isZero = rawData[i] == 0x0;
        bool isDateSlash = rawData[i] == 0x2F;

        if (!isAsciiNum && !isZero && !isDateSlash)
            return false;
    }

    return true;
}

bool DateField::HasUnusedArea() const
{
    constexpr int unusedAreaIndex{ 4 };

    for (int i = unusedAreaIndex; i < size; i++)
    {
        if (rawData[i] != 0)
            return false;
    }

    return true;
}

bool DateField::IsSet() const
{
    for (int i = 0; i < size; i++)
    {
        if (rawData[i] != 0)
            return true;
    }

    return false;
}

std::string DateField::Value() const
{
    if (IsText())
        return Binary::RawField::ToString(Binary::StringFormat::Terminated);

    Binary::UInt8Field day{ Binary::FieldEndianness::Little };
    Binary::UInt8Field month{ Binary::FieldEndianness::Little };
    Binary::UInt16Field year{ Binary::FieldEndianness::Little };

    day.RawData()[0] = rawData[0];
    month.RawData()[0] = rawData[1];
    year.RawData()[0] = rawData[2];
    year.RawData()[1] = rawData[3];

    std::stringstream stream;
    stream << std::setw(2) << std::setfill('0') << month.ToString() << '/'
           << std::setw(2) << std::setfill('0') << day.ToString() << '/'
           << std::setw(4) << std::setfill('0') << year.ToString();
    return stream.str();
}

void DateField::SetTextValue(std::string value)
{
    std::istringstream valueStream{ value };
    std::tm date{};

    valueStream >> std::get_time(&date, "%m/%d/%Y");

    if (!valueStream.fail())
    {
        std::stringstream dateStream;

        // We add 1 to date.tm_mon because January is stored as month 0, etc.
        dateStream << std::setw(2) << std::setfill('0') << date.tm_mon + 1;
        dateStream << "/";

        dateStream << std::setw(2) << std::setfill('0') << date.tm_mday;
        dateStream << "/";

        // We add 1900 because years are stored as years since 1900.
        dateStream << std::setw(4) << std::setfill('0') << date.tm_year + 1900;

        std::memcpy(rawData.get(), dateStream.str().c_str(), 10);

        // The last byte of the 11 byte date field should always be null.
        rawData[10] = 0;
    }
    else
    {
        throw std::invalid_argument
        {
            "Date value must be in MM/DD/YYYY format." 
        };
    }
}

void DateField::SetBinaryValue(std::string value)
{
    std::istringstream valueStream{ value };
    std::tm date;

    valueStream >> std::get_time(&date, "%m/%d/%Y");

    if (!valueStream.fail())
    {
        Binary::UInt8Field day{ date.tm_mday };

        // We add 1 to date.tm_mon because January is stored as month 0, etc.
        Binary::UInt8Field month{ date.tm_mon + 1 };

        // We add 1900 because years are stored as years since 1900.
        Binary::UInt16Field year{ date.tm_year + 1900 };

        rawData[0] = day.RawData()[0];
        rawData[1] = month.RawData()[0];
        std::memcpy(rawData.get() + 2, year.RawData(), 2);

        // The remaining bytes should all be unused in a binary formatted date.
        for (int i = 4; i < 11; i++)
            rawData[i] = 0;
    }
    else
    {
        throw std::invalid_argument
        {
            "Date value must be in MM/DD/YYYY format." 
        };
    }
}