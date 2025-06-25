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

#include "NumericField.h"

using namespace Spc;

bool NumericField::IsZero() const
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] != 0)
            return false;
    }

    return true;
}

bool NumericField::IsText() const
{
    for (int i = 0; i < size; i++)
    {
        bool isAsciiNum = data[i] >= 0x30 && data[i] <= 0x39;
        bool isZero = data[i] == 0x0;

        if (!isAsciiNum && !isZero)
            return false;
    }

    return true;
}

unsigned long long NumericField::DetectValue() const
{
    if (IsZero())
    {
        return 0;
    }
    else if (IsText())
    {
        return std::stoull(
            Binary::RawField::ToString(Binary::StringFormat::Terminated));
    }
    else
    {
        return Value();
    }
}

unsigned long long NumericField::Value() const
{
    Binary::UInt64Field value{ Binary::FieldEndianness::Little };

    for (int i = 0; i < size; i++)
        value.Data()[i] = data[i];

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

    Binary::UInt64Field value{ Binary::FieldEndianness::Little };

    for (int i = 0; i < size; i++)
        value.Data()[i] = data[i];

    return value.ToString();
}

void NumericField::SetValue(int value)
{
    if (type == NumericType::Text)
    {
        std::stringstream stream;
        stream << value;
        std::string stringValue{ stream.str() };

        for (int i = 0; i < size; i++)
            data[i] = stringValue[i];
    }

    Binary::UInt32Field field{ value };
    
    for (int i = 0; i < size; i++)
        data[i] = field.Data()[i];
}

void NumericField::SetValue(std::string value)
{
    if (type == NumericType::Binary)
    {
        Binary::UInt32Field field{ std::stoi(value) };

        for (int i = 0; i < size; i++)
            data[i] = field.Data()[i];
    }
    else
    {
        for (int i = 0; i < size; i++)
            data[i] = value[i];
    }
}