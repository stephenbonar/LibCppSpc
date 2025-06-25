// StringSegment.h - Declares the StringSegment class.
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

#ifndef SPC_STRING_SEGMENT_H
#define SPC_STRING_SEGMENT_H

#include <string>
#include <sstream>
#include "StringSegmentType.h"

namespace Spc
{
    class StringSegment
    {
    public:
        virtual ~StringSegment() = default;

        virtual std::string Value() const = 0;

        virtual StringSegmentType SegmentType() const = 0;

        //virtual void Parse(std::string& text) = 0;
    };
}

#endif