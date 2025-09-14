// BinaryTagTests.cpp - Defines the BinaryTagTests class and tests.
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

#include "BinaryTagTests.h"

BinaryTagTests::BinaryTagTests()
{
}

TEST_F(BinaryTagTests, FieldsHaveCorrectOffsets)
{
    Spc::BinaryTag tag;

    EXPECT_EQ(tag.songTitle.Offset(), 0x2E);
    EXPECT_EQ(tag.gameTitle.Offset(), 0x4E);
    EXPECT_EQ(tag.dumperName.Offset(), 0x6E);
    EXPECT_EQ(tag.comments.Offset(), 0x7E);
    EXPECT_EQ(tag.dateDumped.Offset(), 0x9E);
    EXPECT_EQ(tag.songLength.Offset(), 0xA9);
    EXPECT_EQ(tag.fadeLength.Offset(), 0xAC);
    EXPECT_EQ(tag.songArtist.Offset(), 0xB0);
    EXPECT_EQ(tag.defaultChannelState.Offset(), 0xD0);
    EXPECT_EQ(tag.emulatorUsed.Offset(), 0xD1);
    EXPECT_EQ(tag.reserved.Offset(), 0xD2);
}

TEST_F(BinaryTagTests, NumericFieldsAreBinaryType)
{
    Spc::BinaryTag tag;

    EXPECT_EQ(tag.songLength.Type(), Spc::NumericType::Binary);
    EXPECT_EQ(tag.fadeLength.Type(), Spc::NumericType::Binary);
    EXPECT_EQ(tag.defaultChannelState.Type(), Spc::NumericType::Binary);
    EXPECT_EQ(tag.emulatorUsed.Type(), Spc::NumericType::Binary);
}

TEST_F(BinaryTagTests, FieldsHaveCorrectSizes)
{
    Spc::BinaryTag tag;

    EXPECT_EQ(tag.songTitle.Size(), 32);
    EXPECT_EQ(tag.gameTitle.Size(), 32);
    EXPECT_EQ(tag.dumperName.Size(), 16);
    EXPECT_EQ(tag.comments.Size(), 32);
    EXPECT_EQ(tag.dateDumped.Size(), 11);
    EXPECT_EQ(tag.songLength.Size(), 3);
    EXPECT_EQ(tag.fadeLength.Size(), 4);
    EXPECT_EQ(tag.songArtist.Size(), 32);
    EXPECT_EQ(tag.defaultChannelState.Size(), 1);
    EXPECT_EQ(tag.emulatorUsed.Size(), 1);
    EXPECT_EQ(tag.reserved.Size(), 46);
}

TEST_F(BinaryTagTests, DataStructureSizeIsCorrect)
{
    Spc::BinaryTag tag;

    EXPECT_EQ(tag.Size(), 210);
}

TEST_F(BinaryTagTests, DataStructureFieldsCountIsCorrect)
{
    Spc::BinaryTag tag;

    EXPECT_EQ(tag.Fields().size(), 11);
}

TEST_F(BinaryTagTests, FieldsHaveCorrectLabels)
{
    Spc::BinaryTag tag;

    EXPECT_EQ(tag.songTitle.Label(), "Song Title");
    EXPECT_EQ(tag.gameTitle.Label(), "Game Title");
    EXPECT_EQ(tag.dumperName.Label(), "Dumper");
    EXPECT_EQ(tag.comments.Label(), "Comments");
    EXPECT_EQ(tag.dateDumped.Label(), "Date Dumped");
    EXPECT_EQ(tag.songLength.Label(), "Song Length (sec)");
    EXPECT_EQ(tag.fadeLength.Label(), "Fade Length (ms)");
    EXPECT_EQ(tag.songArtist.Label(), "Song Artist");
    EXPECT_EQ(tag.emulatorUsed.Label(), "Emulator Used");
    EXPECT_EQ(tag.defaultChannelState.Label(), "Default Channel State");
    EXPECT_EQ(tag.reserved.Label(), "Reserved");
}

TEST_F(BinaryTagTests, FieldsAreInitiallyEmpty)
{
    Spc::BinaryTag tag;

    EXPECT_EQ(tag.songTitle.Value(), "");
    EXPECT_EQ(tag.gameTitle.Value(), "");
    EXPECT_EQ(tag.dumperName.Value(), "");
    EXPECT_EQ(tag.comments.Value(), "");
    EXPECT_EQ(tag.dateDumped.Value(), "");
    EXPECT_EQ(tag.songLength.Value(), 0);
    EXPECT_EQ(tag.fadeLength.Value(), 0);
    EXPECT_EQ(tag.songArtist.Value(), "");
    EXPECT_EQ(tag.emulatorUsed.ToString(), "Unknown");
    EXPECT_EQ(tag.defaultChannelState.Value(), 0);

    char* reserved = tag.reserved.Data();

    for (int i = 0; i < tag.reserved.Size(); i++)
        EXPECT_EQ(reserved[i], 0);
}

TEST_F(BinaryTagTests, FieldsListInitializedProperly)
{
    Spc::BinaryTag tag;
    auto fields = tag.Fields();

    EXPECT_EQ(fields.size(), 11);
    EXPECT_EQ(fields[0], &tag.songTitle);
    EXPECT_EQ(fields[1], &tag.gameTitle);
    EXPECT_EQ(fields[2], &tag.dumperName);
    EXPECT_EQ(fields[3], &tag.comments);
    EXPECT_EQ(fields[4], &tag.dateDumped);
    EXPECT_EQ(fields[5], &tag.songLength);
    EXPECT_EQ(fields[6], &tag.fadeLength);
    EXPECT_EQ(fields[7], &tag.songArtist);
    EXPECT_EQ(fields[8], &tag.defaultChannelState);
    EXPECT_EQ(fields[9], &tag.emulatorUsed);
    EXPECT_EQ(fields[10], &tag.reserved);
}