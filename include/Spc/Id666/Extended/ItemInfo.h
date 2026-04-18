// ItemInfo.h - Declares the Spc::Id666::Extended::ItemInfo struct.
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

#ifndef SPC_ID666_EXTENDED_ITEM_INFO_H
#define SPC_ID666_EXTENDED_ITEM_INFO_H

#include "Spc/FieldInfo.h"

namespace Spc::Id666::Extended
{
    /// @brief Used for defining extended tag items.
    ///
    /// This struct is used to define the extended tag items that the SPC file
    /// format supports.
    struct ItemInfo
    {
        /// @brief The integer representing the ID of the extended item.
        uint8_t id;
        
        /// @brief The integer representing the type of the extended item.
        ///
        /// Possible types are defined as the following constants:
        ///
        /// @see lengthType
        /// @see stringType
        /// @see integerType
        uint8_t type;
    };

    /// @brief The unsigned integer value indicating extended item length type.
    inline constexpr uint8_t lengthType{ 0 };

    /// @brief The unsigned integer value indicating extended item string type.
    inline constexpr uint8_t stringType{ 1 };

    /// @brief The unsigned integer value indicating extended item integer type.
    inline constexpr uint8_t integerType{ 4 };

    /// @brief The offset in the file where extended item data begins.
    inline constexpr size_t dataOffset{ 0x10200 };

    /// @brief The ID field info for the extended item sub-chunk header.
    inline constexpr Spc::FieldInfo idInfo{ dataOffset, 1 };

    /// @brief The type field info for the extended item sub-chunk header.
    inline constexpr Spc::FieldInfo typeInfo{ dataOffset, 1 };

    /// @brief The data field info for the extended item sub-chunk header.
    inline constexpr Spc::FieldInfo dataInfo{ dataOffset, 2 };

    /// @brief The size of an integer in the extended item data.
    inline constexpr size_t integerSize{ 4 };

    /// @brief The maximum size of a string in the extended item data.
    inline constexpr size_t stringMaxSize{ 255 };

    /// @brief The extended item info that defines the song title field.
    inline constexpr ItemInfo songTitleInfo{ 0x1, stringType };

    /// @brief The extended item info that defines the game title field.
    inline constexpr ItemInfo gameTitleInfo{ 0x2, stringType };

    /// @brief The extended item info that defines the song artist field.
    inline constexpr ItemInfo songArtistInfo{ 0x3, stringType };

    /// @brief The extended item info that defines the dumper name field.
    inline constexpr ItemInfo dumperNameInfo{ 0x4, stringType };

    /// @brief The extended item info that defines the date dumped field.
    inline constexpr ItemInfo dateDumpedInfo{ 0x5, integerType };

    /// @brief The extended item info that defines the emulator used field.
    inline constexpr ItemInfo emulatorUsedInfo{ 0x6, lengthType };

    /// @brief The extended item info that defines the comments field.
    inline constexpr ItemInfo commentsInfo{ 0x7, stringType };

    /// @brief The extended item info that defines the OST title field.
    inline constexpr ItemInfo ostTitleInfo{ 0x10, stringType };

    /// @brief The extended item info that defines the OST disc field.
    inline constexpr ItemInfo ostDiscInfo{ 0x11, lengthType };

    /// @brief The extended item info that defines the OST track field.
    inline constexpr ItemInfo ostTrackInfo{ 0x12, lengthType };

    /// @brief The extended item info that defines the publisher name field.
    inline constexpr ItemInfo publisherNameInfo{ 0x13, stringType };

    /// @brief The extended item info that defines the copyright year field.
    inline constexpr ItemInfo copyrightYearInfo{ 0x14, lengthType };

    /// @brief The extended item info that defines the intro length field.
    inline constexpr ItemInfo introLengthInfo{ 0x30, integerType };

    /// @brief The extended item info that defines the loop length field.
    inline constexpr ItemInfo loopLengthInfo{ 0x31, integerType };

    /// @brief The extended item info that defines the end length field.
    inline constexpr ItemInfo endLengthInfo{ 0x32, integerType };

    /// @brief The extended item info that defines the fade length field.
    inline constexpr ItemInfo fadeLengthInfo{ 0x33, integerType };

    /// @brief The extended item info that defines the muted voices field.
    inline constexpr ItemInfo mutedVoicesInfo{ 0x34, lengthType };

    /// @brief The extended item info that defines the loop times field.
    inline constexpr ItemInfo loopTimesInfo{ 0x35, lengthType };

    /// @brief The extended item info that defines the preamp level field.
    inline constexpr ItemInfo preampLevelInfo{ 0x36, integerType };
}

#endif