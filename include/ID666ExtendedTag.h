// ID666ExtendedTag.h - Declares the ID666ExtendedTag class.
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

#ifndef ID666_EXTENDED_TAG_H
#define ID666_EXTENDED_TAG_H

#include <memory>
#include <vector>
#include "SpcStruct.h"
#include "SpcTextField.h"
#include "SpcEmulatorField.h"
#include "SpcDateField.h"
#include "SpcNumericField.h"
#include "SpcTrackField.h"
#include "SpcBinaryField.h"
#include "ID666ExtendedItem.h"

/// @brief Represents the extended ID666 tag data.
///
/// The extended ID666 tag items are typically used when a value, such as the
/// song name, is too large to store in the header of the SPC file. For
/// instance, song title is only 32 bytes long in the header. If the song
/// title is greater than 32 bytes, the song name extended item should be used
/// to store the complete value while song title in the header should store a
/// truncated version according to the SPC file format specification.
///
/// That said, there is some information that is exclusive to the extended tag,
/// such as the OST album title or track numbers, as well as some song length,
/// loop, and timing information.
///
/// Finally, there are some extended items where, according to the 
/// specification, should never be used like emulator used. This is because
/// the corresponding field in the SPC file header will always be large enough.
/// It is not clear why such fields were included in the extended tag data.
///
/// All fields are ID666ExtendedItem pointers. Any pointers that are null
/// indicate that extended item does not exist in the tag.
struct ID666ExtendedTag : public SpcStruct
{
    /// @brief The extended version of song title, which can be 4 - 256 bytes.
    std::shared_ptr<ID666ExtendedItem> songName;
    
    /// @brief The extended version of game title, which can be 4 - 256 bytes.
    std::shared_ptr<ID666ExtendedItem> gameName;

    /// @brief The extended version of song artist, which can be 4 - 256 bytes.
    std::shared_ptr<ID666ExtendedItem> artistName;

    /// @brief The extended version of dumper name, which can be 4 - 256 bytes.
    std::shared_ptr<ID666ExtendedItem> dumperName;

    /// @brief The extended version of date dumped, which is 4 bytes.
    ///
    /// In theory, this tag will never be set if strictly following the spec.
    std::shared_ptr<ID666ExtendedItem> dateDumped;

    /// @brief The extended version of emulator used, which is 1 byte.
    ///
    /// In theory, this tag will never be set if strictly following the spec.
    std::shared_ptr<ID666ExtendedItem> emulatorUsed;

    /// @brief The extended version of comments, which is 4 - 256 bytes.
    std::shared_ptr<ID666ExtendedItem> comments;

    /// @brief The title of the original soundtrack, which is 4 - 256 bytes.
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> ostTitle;

    /// @brief The original soundtrack disc number, which is 1 byte.
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> ostDisc;

    /// @brief The original soundtrack track number, which is 2 bytes.
    ///
    /// Upper byte is 0 - 99, lower byte is an optional ASCII character.
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> ostTrack;

    /// @brief The publisher of the game, which is 4 - 256 bytes. 
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> publisherName;

    /// @brief The copyright year of the game, which is 2 bytes.
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> copyrightYear;

    /// @brief The length of the song intro, in ticks (4 bytes).
    ///
    /// The intro is the beginning portion of the song before the looped
    /// portion begins.
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> introLength;

    /// @brief The length of looped portion of the song, in ticks (4 bytes).
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> loopLength;

    /// @brief The length of the song end, in ticks (4 bytes).
    ///
    /// The length of the end portion of the song after the looped portion
    /// ends but before fade out begins.
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> endLength;

    /// @brief The length of the song fade out, in ticks (4 bytes).
    ///
    /// The amount of time to fade out the song.
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> fadeLength;

    /// @brief Mutes specific voices using bit flags (1 byte).
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> mutedVoices;

    /// @brief Determines the number of times to loop the melody (1 byte).
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> loopTimes;

    /// @brief The amplification value to apply (4 bytes).
    ///
    /// 65536 = Normal SNES.
    ///
    /// This field is exclusive to the extended tag.
    std::shared_ptr<ID666ExtendedItem> preampLevel;

    /// @brief Gets the IFF chunk header of the extended tag data.
    /// @return The IFF chunk header.
    Binary::ChunkHeader Header() const;

    /// @brief Provides a vector of raw pointers to the structure's fields.
    ///
    /// This method is primarily intended for use by Binary::Stream and its
    /// derivatives for reading the fields from and to those streams.
    /// Access the fields directly rather than via this method.
    ///
    /// @return The vector containing the raw pointers for the field.
    //std::vector<Binary::DataField*> Fields() override;

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
    ///
    /// Structs that inherit from this struct should provide an implementation
    /// for this method that generates the vector in the correct order.
    ///
    /// @return A vector containing pointers to the SpcFields.
    std::vector<SpcField*> SpcFields() const override;
};

#endif
