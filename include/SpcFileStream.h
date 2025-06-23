// SpcFileStream.h - Declares the SpcFileStream class.
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

#ifndef SPC_FILE_STREAM_H
#define SPC_FILE_STREAM_H

#include <string>
#include "LibCppBinary.h"
#include "SpcHeader.h"
#include "ID666TextTag.h"
#include "ID666BinaryTag.h"
#include "ID666ExtendedItem.h"
#include "ID666TagType.h"
#include "SpcDateField.h"
#include "SpcNumericField.h"

inline constexpr int headerContainsTag{ 26 };
inline constexpr int tagOffset{ 0x2E };

/// @brief Represents an SPC file stream.
///
/// Provides methods for reading from, writing to, and analyzing an SPC file.
/// Adds SPC specific functionality to Binary::RawFileStream.
class SpcFileStream : public Binary::RawFileStream
{
public:
    /// @brief Constructor; creates a new SPC file using a file name.
    /// @param fileName The name of the SPC file to use.
    SpcFileStream(std::string fileName) : Binary::RawFileStream{ fileName }
    { }

    /// @brief Sets the stream position to the extended tag, if available.
    void SeekExtendedTag();

    /// @brief Determines the type of ID666 tag the file uses.
    /// @return The type of ID666 tag.
    ID666TagType TagType();

    /// @brief Determines if the SPC file's header contains an ID666 tag.
    /// @return Returns true if it contains a tag, otherwise false.
    bool HeaderContainsTag();

    /// @brief Determines if the SPC file contains an extended ID666 tag.
    /// @return Returns true if it has an extended tag, otherwise false.
    bool HasExtendedTag();
};

#endif