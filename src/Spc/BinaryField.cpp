// BinaryField.cpp - Defines the BinaryField class.
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

#include "Spc/BinaryField.h"

using namespace Spc;

const char* emptyError{ "Value must not be empty."};
const char* binError{ "Value must only contain '0' and '1' characters." };

void BinaryField::SetValue(std::string value)
{
    constexpr int base{ 2 };
    constexpr size_t* nonNumericPos{ nullptr };

    if (value.empty())
        throw std::invalid_argument{ emptyError };
    
    if (value.find_first_not_of("01") != std::string::npos)
        throw std::invalid_argument{ binError };

    int dec = std::stoi(value, nonNumericPos, base);
    NumericField::SetInt32(dec);
}