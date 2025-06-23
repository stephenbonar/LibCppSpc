// StringToken.h - Declares the StringToken class.
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

#ifndef STRING_TOKEN_H
#define STRING_TOKEN_H

#include "StringSegment.h"
#include "StringSegmentType.h"
#include "StringDelimiter.h"
#include "StringValueType.h"

class StringToken : public StringSegment
{
public:
    StringToken(std::string name, StringValueType valueType) :
        name{ name },
        valueType{ valueType }, 
        segmentType{ StringSegmentType::Token }
    { }

    virtual std::string Name() const { return name; }

    virtual StringValueType ValueType() const { return valueType; }

    /*
    virtual void SetDelimiter(std::shared_ptr<StringDelimiter> delimiter) 
    {
        this->delimiter = delimiter; 
    }
    */
    virtual void SetValue(std::string value) { this->value = value; }

    virtual std::string Value() const override { return value; }

    virtual StringSegmentType SegmentType() const override 
    {
        return segmentType; 
    }

    //virtual void Parse(std::string& text) override;
private:
    std::string name;
    std::string value;
    StringValueType valueType;
    StringSegmentType segmentType;
    std::shared_ptr<StringDelimiter> delimiter;
};

#endif