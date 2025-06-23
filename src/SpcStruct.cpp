// SpcStruct.cpp - Defines the SpcStruct struct.
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

#include "SpcStruct.h"

std::vector<Binary::DataField*> SpcStruct::Fields()
{
    std::vector<Binary::DataField*> fields;
    std::vector<SpcField*> spcFields = SpcFields();

    for (int i = 0; i < spcFields.size(); ++i)
        fields.push_back(spcFields[i]);

    return fields;
}


size_t SpcStruct::Size() const
{
    size_t size{ 0 };
    std::vector<SpcField*> spcFields = SpcFields();

    for (int i = 0; i < spcFields.size(); i++)
        size += spcFields[i]->Size();

    return size;
}

std::string SpcStruct::ToString() const
{
    std::stringstream stream;
    std::vector<SpcField*> spcFields = SpcFields();

    for (int i = 0; i < spcFields.size(); i++)
    {
        std::string label = spcFields[i]->Label();
        std::string value = spcFields[i]->ToString();
        stream << FormatValue(label, value) << std::endl;
    }
    
    return stream.str();
}