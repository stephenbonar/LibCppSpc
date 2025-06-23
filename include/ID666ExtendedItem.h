// ID666ExtendedItem.h - Declares the ID666ExtendedItem class.
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

#include <string>
#include <memory>
#include <map>
#include "SpcStruct.h"
#include "SpcNumericField.h"
#include "SpcTextField.h"

#ifndef ID666_EXTENDED_ITEM_H
#define ID666_EXTENDED_ITEM_H

extern const std::map<int, std::string> extendedFieldLabels;

inline constexpr uint8_t extendedSongNameID{ 0x1 };
inline constexpr uint8_t extendedGameNameID{ 0x2 };
inline constexpr uint8_t extendedArtistNameID{ 0x3 };
inline constexpr uint8_t extendedDumperNameID{ 0x4 };
inline constexpr uint8_t extendedDateDumpedID{ 0x5 };
inline constexpr uint8_t extendedEmulatorUsedID{ 0x6 };
inline constexpr uint8_t extendedCommentsID{ 0x7 };
inline constexpr uint8_t extendedOSTTitleID{ 0x10 };
inline constexpr uint8_t extendedOSTDiscID{ 0x11 };
inline constexpr uint8_t extendedOSTTrackID{ 0x12 };
inline constexpr uint8_t extendedPublisherNameID{ 0x13 };
inline constexpr uint8_t extendedCopyrightYearID{ 0x14 };
inline constexpr uint8_t extendedIntroLengthID{ 0x30 };
inline constexpr uint8_t extendedLoopLengthID{ 0x31 };
inline constexpr uint8_t extendedEndLengthID{ 0x32 };
inline constexpr uint8_t extendedFadeLengthID{ 0x33 };
inline constexpr uint8_t extendedMutedVoicesID{ 0x34 };
inline constexpr uint8_t extendedLoopTimesID{ 0x35 };
inline constexpr uint8_t extendedPreampLevelID{ 0x36 };
inline constexpr uint8_t extendedTypeDataInHeader{ 0 };
inline constexpr uint8_t extendedTypeString{ 1 };
inline constexpr uint8_t extendedTypeInteger{ 4 };
inline constexpr uint8_t extendedTagIDSize{ 1 };
inline constexpr uint8_t extendedTagTypeSize{ 1 };
inline constexpr uint8_t extendedTagDataSize{ 2 };
inline constexpr uint8_t extendedTagStringMaxSize{ 255 };
inline constexpr int extendedTagOffset{ 0x10200 };

/// @brief Represents an item in the extended ID666 tag.
///
/// The extended ID666 tag is an IFF chunk that contains multiple sub-chunks
/// representing items in the tag. This struct represents those sub-chunks.
struct ID666ExtendedItem : public SpcStruct
{
    /// @brief Default constructor; creates new instance of ID666ExtendedItem.
    ID666ExtendedItem();
    
    /// @brief Determines which extended item this instance represents.
    std::shared_ptr<SpcNumericField> id;

    /// @brief Determines the type of extended item.
    ///
    /// 0 = The value is contained in the data field.
    /// 1 = The value is in extendedData and represents a string.
    /// 4 = The value is in extendedData and represents a 32-bit integer.
    std::shared_ptr<SpcNumericField> type;

    /// @brief Depending on the type, represents either data length or value.
    std::shared_ptr<SpcField> data;

    /// @brief Contains the item value if type is not 0.
    std::shared_ptr<SpcField> extendedData;

    /// @brief Points to the padding bytes, if any.
    std::shared_ptr<SpcTextField> padding;

    /// @brief Gets list of pointers to this struct's fields.
    ///
    /// This method will be called by the ToString() method to output each
    /// field as a formatted string on its own line of the format,
    ///
    /// label: value
    ///
    /// This method is also called by the Fields() method to get a pointer to
    /// each field so SpcFileStream can read this struct from and write it to
    /// an SPC file in a cross platform way, preserving the order, size, and
    /// endianness of each field no matter which architecture the program runs
    /// on.
    std::vector<SpcField*> SpcFields() const override;
};

#endif