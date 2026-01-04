// ID666TagTests.cpp - Defines the ID666TagTests class and tests.
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

#include "ID666TagTests.h"

// The raw data needs to be unsigned char arrays to avoid sign extension issues
// on certain platforms. They are then cast to const char* for copying into the 
// tag data.
constexpr unsigned char rawTextData[] = {
    // 0x2E: Song title (32 bytes)
    'T','e','s','t',' ','S','o','n','g',' ','T','i','t','l','e',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    // 0x4E: Game title (32 bytes)
    'T','e','s','t',' ','G','a','m','e',' ','T','i','t','l','e',' ','1','2','3','4','5','6','7','8','9','0','X','Y','Z','Q','R','S',
    // 0x6E: Name of dumper (16 bytes)
    'D','u','m','p','e','r','N','a','m','e','1','2','3','4','5','6',
    // 0x7E: Comments (32 bytes)
    'T','e','s','t',' ','C','o','m','m','e','n','t','s',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
    // 0x9E: Date dumped (11 bytes, MM/DD/YYYY)
    '0','2','/','0','6','/','2','0','0','0','\0',
    // 0xA9: Seconds before fade (3 bytes, ASCII)
    '1','2','3',
    // 0xAC: Fade length ms (5 bytes, ASCII)
    '0','5','0','0','0',
    // 0xB1: Artist (32 bytes)
    'A','r','t','i','s','t',' ','N','a','m','e',' ','T','e','s','t',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
    // 0xD1: Default channel disables (1 byte, ASCII '0')
    '0',
    // 0xD2: Emulator used (1 byte, ASCII '2' for Snes9x)
    '2',
    // 0xD3: Reserved (45 bytes, all 0)
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0
};

constexpr unsigned char rawBinaryData[] = {
    // 0x2E: Song title (32 bytes)
    'T','e','s','t',' ','S','o','n','g',' ','T','i','t','l','e',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    // 0x4E: Game title (32 bytes)
    'T','e','s','t',' ','G','a','m','e',' ','T','i','t','l','e',' ','1','2','3','4','5','6','7','8','9','0','X','Y','Z','Q','R','S',
    // 0x6E: Name of dumper (16 bytes)
    'D','u','m','p','e','r','N','a','m','e','1','2','3','4','5','6',
    // 0x7E: Comments (32 bytes)
    'T','e','s','t',' ','C','o','m','m','e','n','t','s',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
    // 0x9E: Date dumped (4 bytes, YYYYMMDD, which is DDMMYYYY little endian)
    0x06, 0x02, 0xD0, 0x07, // 0x0602D007 = 2000-02-06
    // 0xA2: unused (7 bytes)
    0,0,0,0,0,0,0,
    // 0xA9: Seconds before fade (3 bytes, little endian)
    0x2B, 0x00, 0x00, // 43 seconds (0x2B)
    // 0xAC: Fade length ms (4 bytes, little endian)
    0x88, 0x13, 0x00, 0x00, // 5000 ms (0x1388)
    // 0xB0: Artist (32 bytes)
    'A','r','t','i','s','t',' ','N','a','m','e',' ','T','e','s','t',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
    // 0xD0: Default channel disables (1 byte, binary)
    0x00,
    // 0xD1: Emulator used (1 byte, binary: 2 = Snes9x)
    0x02,
    // 0xD2: Reserved (46 bytes, all 0)
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0
};

constexpr unsigned char rawMixedData[] = {
    // 0x2E: Song title (32 bytes)
    'T','e','s','t',' ','S','o','n','g',' ','T','i','t','l','e',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    // 0x4E: Game title (32 bytes)
    'T','e','s','t',' ','G','a','m','e',' ','T','i','t','l','e',' ','1','2','3','4','5','6','7','8','9','0','X','Y','Z','Q','R','S',
    // 0x6E: Name of dumper (16 bytes)
    'D','u','m','p','e','r','N','a','m','e','1','2','3','4','5','6',
    // 0x7E: Comments (32 bytes)
    'T','e','s','t',' ','C','o','m','m','e','n','t','s',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
    // 0x9E: Date dumped (11 bytes, MM/DD/YYYY)
    '0','2','/','0','6','/','2','0','0','0','\0',
    // 0xA9: Seconds before fade (3 bytes, little endian binary: 123)
    0x7B, 0x00, 0x00,
    // 0xAC: Fade length ms (5 bytes, first 4 bytes little endian binary: 50000, last byte ASCII '0')
    0x50, 0xC3, 0x00, 0x00, 0x00,
    // 0xB1: Artist (32 bytes)
    'A','r','t','i','s','t',' ','N','a','m','e',' ','T','e','s','t',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
    // 0xD1: Default channel disables (1 byte, little endian binary: 0)
    0x00,
    // 0xD2: Emulator used (1 byte, little endian binary: 2)
    0x02,
    // 0xD3: Reserved (45 bytes, all 0)
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0
};

void ID666TagTests::SetUp() 
{
    tag = std::make_unique<Spc::ID666Tag>();
    textData = reinterpret_cast<const char*>(rawTextData);
    binaryData = reinterpret_cast<const char*>(rawBinaryData);
    mixedData = reinterpret_cast<const char*>(rawMixedData);
}

TEST_F(ID666TagTests, InitializesProperly)
{
    std::shared_ptr<Binary::BufferStream> fieldData = tag->FieldData();
    std::shared_ptr<Spc::ID666ExtendedData> extendedData = tag->ExtendedData();

    ASSERT_NE(nullptr, fieldData);
    ASSERT_NE(nullptr, extendedData);
    EXPECT_EQ(Spc::id666TagSize, fieldData->Size());
}

TEST_F(ID666TagTests, GetsTextSongTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedOffset = Spc::songTitleInfo.textOffset;
    params.expectedSize = Spc::songTitleInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::SongTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinarySongTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedOffset = Spc::songTitleInfo.binaryOffset;
    params.expectedSize = Spc::songTitleInfo.binarySize;
    params.getMethodPtr = &Spc::ID666Tag::SongTitle;
    TestGet<Spc::TextField>(params); 
}

TEST_F(ID666TagTests, GetsMixedSongTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedOffset = Spc::songTitleInfo.textOffset;
    params.expectedSize = Spc::songTitleInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::SongTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedSongTitleProperly)
{
    tag->ExtendedData()->songName = std::make_shared<Spc::ID666ExtendedItem>();
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedSize = expectedSongTitle.size();
    params.extendedID = Spc::extendedSongNameID;
    params.extendedType = Spc::extendedTypeString;
    params.extendedValue = expectedSongTitle;
    params.item = tag->ExtendedData()->songName;
    params.getMethodPtr = &Spc::ID666Tag::SongTitle;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextGameTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedOffset = Spc::gameTitleInfo.textOffset;
    params.expectedSize = Spc::gameTitleInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::GameTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryGameTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedOffset = Spc::gameTitleInfo.binaryOffset;
    params.expectedSize = Spc::gameTitleInfo.binarySize;
    params.getMethodPtr = &Spc::ID666Tag::GameTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedGameTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedOffset = Spc::gameTitleInfo.textOffset;
    params.expectedSize = Spc::gameTitleInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::GameTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedGameTitleProperly)
{
    tag->ExtendedData()->gameName = std::make_shared<Spc::ID666ExtendedItem>();
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedSize = expectedGameTitle.size();
    params.extendedID = Spc::extendedGameNameID;
    params.extendedType = Spc::extendedTypeString;
    params.extendedValue = expectedGameTitle;
    params.item = tag->ExtendedData()->gameName;
    params.getMethodPtr = &Spc::ID666Tag::GameTitle;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextDumperNameProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedOffset = Spc::dumperNameInfo.textOffset;
    params.expectedSize = Spc::dumperNameInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::DumperName;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryDumperNameProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedOffset = Spc::dumperNameInfo.binaryOffset;
    params.expectedSize = Spc::dumperNameInfo.binarySize;
    params.getMethodPtr = &Spc::ID666Tag::DumperName;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedDumperNameProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedOffset = Spc::dumperNameInfo.textOffset;
    params.expectedSize = Spc::dumperNameInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::DumperName;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedDumperProperly)
{
    tag->ExtendedData()->dumperName = 
        std::make_shared<Spc::ID666ExtendedItem>();
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedSize = expectedDumperName.size();
    params.extendedID = Spc::extendedDumperNameID;
    params.extendedType = Spc::extendedTypeString;
    params.extendedValue = expectedDumperName;
    params.item = tag->ExtendedData()->dumperName;
    params.getMethodPtr = &Spc::ID666Tag::DumperName;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextCommentsProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedOffset = Spc::commentsInfo.textOffset;
    params.expectedSize = Spc::commentsInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::Comments;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryCommentsProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedOffset = Spc::commentsInfo.binaryOffset;
    params.expectedSize = Spc::commentsInfo.binarySize;
    params.getMethodPtr = &Spc::ID666Tag::Comments;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedCommentsProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedOffset = Spc::commentsInfo.textOffset;
    params.expectedSize = Spc::commentsInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::Comments;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedCommentsProperly)
{
    tag->ExtendedData()->comments = std::make_shared<Spc::ID666ExtendedItem>();
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedSize = expectedComments.size();
    params.extendedID = Spc::extendedCommentsID;
    params.extendedType = Spc::extendedTypeString;
    params.extendedValue = expectedComments;
    params.item = tag->ExtendedData()->comments;
    params.getMethodPtr = &Spc::ID666Tag::Comments;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextDateDumpedProperly)
{
    TestGetParameters<Spc::DateField> params;
    params.testData = textData;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedOffset = Spc::dateDumpedInfo.textOffset;
    params.expectedSize = Spc::dateDumpedInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::DateDumped;
    TestGet<Spc::DateField>(params);
}

TEST_F(ID666TagTests, GetsBinaryDateDumpedProperly)
{
    TestGetParameters<Spc::DateField> params;
    params.testData = binaryData;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedOffset = Spc::dateDumpedInfo.binaryOffset;
    params.expectedSize = Spc::dateDumpedInfo.binarySize;
    params.getMethodPtr = &Spc::ID666Tag::DateDumped;
    TestGet<Spc::DateField>(params);
}

TEST_F(ID666TagTests, GetsMixedDateDumpedProperly)
{
    TestGetParameters<Spc::DateField> params;
    params.testData = mixedData;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedOffset = Spc::dateDumpedInfo.textOffset;
    params.expectedSize = Spc::dateDumpedInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::DateDumped;
    TestGet<Spc::DateField>(params);
}

TEST_F(ID666TagTests, GetsExtendedDateDumpedProperly)
{
    tag->ExtendedData()->dateDumped = 
        std::make_shared<Spc::ID666ExtendedItem>();
    
    TestGetWithExtendedItemParameters<Spc::DateField> params;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedSize = Spc::dateDumpedInfo.binarySize;
    params.extendedID = Spc::extendedDateDumpedID;
    params.extendedType = Spc::extendedTypeInteger;

    // The decimal representation of the binary format date.
    params.extendedValue = "131072518"; 

    params.item = tag->ExtendedData()->dateDumped;
    params.getMethodPtr = &Spc::ID666Tag::DateDumped;
    TestGetWithExtendedItem<Spc::DateField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsTextSongLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = textData;
    params.expectedLabel = "Song Length (seconds)";
    params.expectedValue = "123";
    params.expectedOffset = Spc::songLengthInfo.textOffset;
    params.expectedSize = Spc::songLengthInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::SongLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsBinarySongLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = binaryData;
    params.expectedLabel = "Song Length (seconds)";
    params.expectedValue = "43";
    params.expectedOffset = Spc::songLengthInfo.binaryOffset;
    params.expectedSize = Spc::songLengthInfo.binarySize;
    params.getMethodPtr = &Spc::ID666Tag::SongLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsMixedSongLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = mixedData;
    params.expectedLabel = "Song Length (seconds)";
    params.expectedValue = "123";
    params.expectedOffset = Spc::songLengthInfo.textOffset;
    params.expectedSize = Spc::songLengthInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::SongLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetTextFadeLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = textData;
    params.expectedLabel = "Fade Length (ms)";
    params.expectedValue = "05000";
    params.expectedOffset = Spc::fadeLengthInfo.textOffset;
    params.expectedSize = Spc::fadeLengthInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::FadeLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsBinaryFadeLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = binaryData;
    params.expectedLabel = "Fade Length (ms)";
    params.expectedValue = "5000";
    params.expectedOffset = Spc::fadeLengthInfo.binaryOffset;
    params.expectedSize = Spc::fadeLengthInfo.binarySize;
    params.getMethodPtr = &Spc::ID666Tag::FadeLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsMixedFadeLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = mixedData;
    params.expectedLabel = "Fade Length (ms)";
    params.expectedValue = "50000";
    params.expectedOffset = Spc::fadeLengthInfo.textOffset;
    params.expectedSize = Spc::fadeLengthInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::FadeLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsTextArtistProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedOffset = Spc::songArtistInfo.textOffset;
    params.expectedSize = Spc::songArtistInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::SongArtist;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryArtistProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedOffset = Spc::songArtistInfo.binaryOffset;
    params.expectedSize = Spc::songArtistInfo.binarySize;
    params.getMethodPtr = &Spc::ID666Tag::SongArtist;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedArtistProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedOffset = Spc::songArtistInfo.textOffset;
    params.expectedSize = Spc::songArtistInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::SongArtist;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedArtistProperly)
{
    tag->ExtendedData()->artistName = 
        std::make_shared<Spc::ID666ExtendedItem>();
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedSize = expectedSongArtist.size();
    params.extendedID = Spc::extendedArtistNameID;
    params.extendedType = Spc::extendedTypeString;
    params.extendedValue = expectedSongArtist;
    params.item = tag->ExtendedData()->artistName;
    params.getMethodPtr = &Spc::ID666Tag::SongArtist;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextDefaultChannelStateProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = textData;
    params.expectedLabel = "Default Channel State";
    params.expectedValue = "0";
    params.expectedOffset = Spc::defaultChannelStateInfo.textOffset;
    params.expectedSize = Spc::defaultChannelStateInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::DefaultChannelState;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsBinaryDefaultChannelStateProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = binaryData;
    params.expectedLabel = "Default Channel State";
    params.expectedValue = "0";
    params.expectedOffset = Spc::defaultChannelStateInfo.binaryOffset;
    params.expectedSize = Spc::defaultChannelStateInfo.binarySize;
    params.getMethodPtr = &Spc::ID666Tag::DefaultChannelState;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsMixedDefaultChannelStateProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = mixedData;
    params.expectedLabel = "Default Channel State";
    params.expectedValue = "0";
    params.expectedOffset = Spc::defaultChannelStateInfo.textOffset;
    params.expectedSize = Spc::defaultChannelStateInfo.textSize;
    params.getMethodPtr = &Spc::ID666Tag::DefaultChannelState;
    TestGet<Spc::NumericField>(params);
}
