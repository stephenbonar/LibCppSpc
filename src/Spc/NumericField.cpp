// NumericField.cpp - Defines the NumericField class.
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

#include "Spc/NumericField.h"

using namespace Spc;

bool NumericField::IsZero() const
{
    for (int i = 0; i < size; i++)
    {
        if (rawData[i] != 0)
            return false;
    }

    return true;
}

bool NumericField::IsText() const
{
    for (int i = 0; i < size; i++)
    {
        bool isAsciiNum = rawData[i] >= 0x30 && rawData[i] <= 0x39;
        bool isZero = rawData[i] == 0x0;

        if (!isAsciiNum && !isZero)
            return false;
    }

    return true;
}

int32_t NumericField::DetectInt32() const
{
    if (IsZero())
    {
        return 0;
    }
    else if (IsText())
    {
        return std::stoi(
            Binary::RawField::ToString(Binary::StringFormat::Terminated));
    }
    else
    {
        return ToInt32();
    }
}

int32_t NumericField::ToInt32() const
{
    Binary::Int32Field value{ Binary::FieldEndianness::Little };

    for (int i = 0; i < size && i < value.Size(); i++)
        value.RawData()[i] = rawData[i];

    return value.Value();
}

uint32_t NumericField::ToUInt32() const
{
    Binary::UInt32Field value{ Binary::FieldEndianness::Little };

    for (int i = 0; i < size && i < value.Size(); i++)
        value.RawData()[i] = rawData[i];

    return value.Value();
}

std::string NumericField::ToString() const
{
    if (type == NumericType::Either)
    {
        if (IsZero())
            return "0";

        if (IsText())
        {
            return Binary::RawField::ToString(
                Binary::StringFormat::Terminated);
        }  
    }
    
    if (type == NumericType::Text)
        return Binary::RawField::ToString(Binary::StringFormat::Terminated);

    Binary::Int32Field value{ Binary::FieldEndianness::Little };

    for (int i = 0; i < size && i < value.Size(); i++)
        value.RawData()[i] = rawData[i];

    return value.ToString();
}

void NumericField::SetInt32(int32_t value)
{
    if (type == NumericType::Text)
    {
        std::stringstream stream;
        stream << value;
        std::string stringValue{ stream.str() };

        for (int i = 0; i < size && i < stringValue.size(); i++)
            rawData[i] = stringValue[i];
    }

    Binary::Int32Field field{ value };
    
    for (int i = 0; i < size && i < field.Size(); i++)
        rawData[i] = field.RawData()[i];
}

void NumericField::SetUInt32(uint32_t value)
{
    if (type == NumericType::Text)
    {
        std::stringstream stream;
        stream << value;
        std::string stringValue{ stream.str() };

        for (int i = 0; i < size && i < stringValue.size(); i++)
            rawData[i] = stringValue[i];
    }

    Binary::UInt32Field field{ value };
    
    for (int i = 0; i < size && i < field.Size(); i++)
        rawData[i] = field.RawData()[i];
}

void NumericField::SetValue(std::string value)
{
    if (type == NumericType::Binary)
    {
        Binary::Int32Field field{ std::stoi(value) };

        for (int i = 0; i < size && i < field.Size(); i++)
            rawData[i] = field.RawData()[i];
    }
    else
    {
        for (int i = 0; i < size && i < value.size(); i++)
            rawData[i] = value[i];
    }
}