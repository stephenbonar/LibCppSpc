// Format.cpp - Defines functions for formatting SPC fields.
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

#include "Format.h"

using namespace Spc;

std::string Spc::FormatValue(std::string label, std::string value)
{
    // This value is enough to fit all labels with at least one space after.
    constexpr int labelSize{ 22 };

    // This value perfectly wraps hexadecimal output.
    constexpr int valueChunkSize{ 54 };

    std::stringstream stream;
    stream << std::setw(labelSize) << std::left << label << ": ";
    
    // If the value is long enough that it will wrap in an 80 column terminal,
    // then we split the value into chunks to cleanly wrap it, otherwise we
    // simply output the value as-is.
    if (value.length() > valueChunkSize)
    {
        for (int i = 0; i < value.length(); i += valueChunkSize)
        {
            // Write the next chunk.
            stream << value.substr(i, valueChunkSize);

            // If there's still enough to wrap another line, we do so to keep
            // the output format aligned.
            if (i + valueChunkSize < value.length())
                stream << std::endl << std::setw(labelSize) << " " << "  ";
        }
    }
    else
    {
        stream << value;
    }

    return stream.str();
}

std::string Spc::FormatField(Field* field)
{
    return Spc::FormatValue(field->Label(), field->ToString());
}