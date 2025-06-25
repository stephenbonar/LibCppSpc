// BinaryTag.h - Declares the BinaryTag class.
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

#ifndef SPC_BINARY_TAG_H
#define SPC_BINARY_TAG_H

#include "DataStructure.h"
#include "Field.h"
#include "DateField.h"
#include "NumericField.h"
#include "EmulatorField.h"
#include "TextField.h"

namespace Spc
{
    /// @brief Represents a binary format ID666 tag.
    ///
    /// ID666 tags are the metadata tags stored in the header of an SPC file and
    /// come in two formats: text or binary. Binary formatted tags tend to store 
    /// numeric values as unsigned binary integers, although some SCP dumps
    /// use a mixture of text and binary numbers. That said, text and binary tags
    /// have slightly different offsets, and dumps that mix text and binary still
    /// tend to use the offsets of one format or the other.
    struct BinaryTag : public DataStructure
    {
        /// @brief The title of the song.
        TextField songTitle{ "Song Title", 0x2E, 32 };
        
        /// @brief The name of the game the song is from. 
        TextField gameTitle{ "Game Title", 0x4E, 32 };

        /// @brief The person who dumped the SPC file.
        TextField dumperName{ "Dumper", 0x6E, 16 };

        /// @brief Comments the dumper or tagger provided with the song.
        TextField comments{ "Comments", 0x7E, 32 };

        /// @brief The date the song was dumped.
        DateField dateDumped{ "Date Dumped", 0x9E, 11 };

        /// @brief The length of the song before fading out, in seconds.
        NumericField songLength
        {
            "Song Length (sec)", 0xA9, 3, NumericType::Binary 
        };

        /// @brief The length of fade out, in milliseconds.
        NumericField fadeLength
        {
            "Fade Length (ms)", 0xAC, 4, NumericType::Binary
        };

        /// @brief The composer of the song.
        TextField songArtist{ "Song Artist", 0xB0, 32 };

        /// @brief Determines the default state of each of the channels.
        ///
        /// The exact purpose of this field is unclear from the documentation
        /// and other source code availabe. In the file format documentation, 
        /// this field is called "default channel disables". The best I can 
        /// gather is it
        /// determines if the default state of each channel, where 0 = channels
        /// are all enabled by default, and 1 = channels are disabled by default
        NumericField defaultChannelState
        {
            "Default Channel State", 0xD0, 1, NumericType::Binary
        };

        /// @brief Determines which emulator was used to dump the SPC file.
        EmulatorField emulatorUsed
        { 
            "Emulator Used", 0xD1, 1, NumericType::Binary
        };

        /// @brief Bytes reserved for use in future versions of the SPC format.
        Field reserved{ "Reserved", 0xD2, 45 };

        /// @brief Default constructor; initalizes the labeled fields list.
        ///
        /// While this is a standard struct with public fields, it is also an 
        /// SpcStruct, which maintains an internal vector of labeled pointers to
        /// each public field accessible via the SpcFields() method. The 
        /// constructor initializes this internal vector.
        BinaryTag();

        /// @brief Gets list of pointers to this struct's fields.
        ///
        /// This method will be called by the ToString() method to output each
        /// field as a formatted string on its own line of the format,
        ///
        /// label: value
        ///
        /// This method is also called by the Fields() method to get a pointer 
        /// to each field so SpcFileStream can read this struct from and write 
        /// it to an SPC file in a cross platform way, preserving the order, 
        /// size, and endianness of each field no matter which architecture the 
        /// program runs on.
        std::vector<Field*> SpcFields() const override { return spcFields; }
    private:
        std::vector<Field*> spcFields;
    };
}

#endif