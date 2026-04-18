// TagFieldInfo.h - Declares the Spc::Id666::TagFieldInfo struct.
//
// Copyright (C) 2026 Stephen Bonar
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

#ifndef SPC_ID666_TAG_FIELD_INFO_H
#define SPC_ID666_TAG_FIELD_INFO_H

#include "Spc/FieldInfo.h"

namespace Spc::Id666
{
    /// @brief Used for defining tag fields.
    ///
    /// Provides the offsets and sizes for both the text and binary
    /// representations of the tag field.
    struct TagFieldInfo
    {
        /// @brief Defines the offsets and sizes of the text representation.
        Spc::FieldInfo text;

        /// @brief Defines the offsets and sizes of the binary representation.
        Spc::FieldInfo binary;
    };

    /// @brief Defines the song title tag field.
    constexpr TagFieldInfo songTitleInfo{ { 0x2E, 32 }, { 0x2E, 32 } };

    /// @brief Defines the game title tag field.
    constexpr TagFieldInfo gameTitleInfo{ { 0x4E, 32 }, { 0x4E, 32 } };

    /// @brief Defines the dumper name tag field.
    constexpr TagFieldInfo dumperNameInfo{ { 0x6E, 16 }, { 0x6E, 16 } };

    /// @brief Defines the comments tag field.
    constexpr TagFieldInfo commentsInfo{ { 0x7E, 32 }, { 0x7E, 32 } };

    /// @brief Defines the date dumped tag field.
    constexpr TagFieldInfo dateDumpedInfo{ { 0x9E, 11 }, { 0x9E, 11 } };

    /// @brief Defines the song length tag field.
    constexpr TagFieldInfo songLengthInfo{ { 0xA9, 3 }, { 0xA9, 3 } };

    /// @brief Defines the fade length tag field.
    constexpr TagFieldInfo fadeLengthInfo{ { 0xAC, 5 }, { 0xAC, 4 } };

    /// @brief Defines the song artist tag field.
    constexpr TagFieldInfo songArtistInfo{ { 0xB1, 32 }, { 0xB0, 32 } };

    /// @brief Defines the default disabled channels tag field.
    constexpr TagFieldInfo defaultDisabledChannelsInfo
    { 
        { 0xD1, 1 }, { 0xD0, 1 } 
    };

    /// @brief Defines the emulator used tag field.
    constexpr TagFieldInfo emulatorUsedInfo{ { 0xD2, 1 }, { 0xD1, 1 } };

    /// @brief Defines the tag reserved area.
    constexpr TagFieldInfo reservedInfo{ { 0xD3, 45 }, { 0xD2, 46 } };
}

#endif