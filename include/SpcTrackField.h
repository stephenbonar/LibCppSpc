// SpcTrackField.h - Declares the SpcTrackField class.
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

#ifndef SPC_TRACK_FIELD_H
#define SPC_TRACK_FIELD_H

#include <sstream>
#include "SpcField.h"

class SpcTrackField : public SpcField
{
public:
    /// @brief Constructor; creates a new instance of SpcTrackField.
    /// @param label The label to use when outputing the field. 
    /// @param offset The offset where the field can be found in the file.
    /// @param size The size of the field, in bytes.
    SpcTrackField(std::string label, uintmax_t offset, size_t size) :
        SpcField{ label, offset, size }
    { }

    uint8_t Value() const;

    char Suffix() const;

    std::string ToString() const override;

    void SetValue(std::string value);
};

#endif