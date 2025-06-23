// StringDelimiter.h - Declares the StringDelimier class.
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

#ifndef STRING_DELIMITER_H
#define STRING_DELIMITER_H

#include <sstream>
#include "StringSegment.h"

class StringDelimiter : public StringSegment
{
public:
    StringDelimiter(std::string value) 
        : value{ value }, segmentType{ StringSegmentType::Delimiter }
    { }

    virtual int GetIndex(std::string text) const;

    virtual std::string Value() const override { return value; }

    virtual StringSegmentType SegmentType() const override 
    {
        return segmentType; 
    }

    //virtual void Parse(std::string& text) override;
private:
    std::string value;
    StringSegmentType segmentType;
};

#endif