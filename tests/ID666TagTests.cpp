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
    tag = std::make_unique<Spc::Id666::Tag>();
    textData = reinterpret_cast<const char*>(rawTextData);
    binaryData = reinterpret_cast<const char*>(rawBinaryData);
    mixedData = reinterpret_cast<const char*>(rawMixedData);
}

TEST_F(ID666TagTests, InitializesProperly)
{
    std::shared_ptr<Binary::BufferStream> fieldData = tag->FieldData();
    std::shared_ptr<Spc::Id666::Extended::Data> extendedData = 
        tag->ExtendedData();

    ASSERT_NE(nullptr, fieldData);
    ASSERT_NE(nullptr, extendedData);
    EXPECT_EQ(Spc::Id666::tagSize, fieldData->Size());
}

TEST_F(ID666TagTests, GetsTextSongTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedOffset = Spc::Id666::songTitleInfo.textOffset;
    params.expectedSize = Spc::Id666::songTitleInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::SongTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinarySongTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedOffset = Spc::Id666::songTitleInfo.binaryOffset;
    params.expectedSize = Spc::Id666::songTitleInfo.binarySize;
    params.getMethodPtr = &Spc::Id666::Tag::SongTitle;
    TestGet<Spc::TextField>(params); 
}

TEST_F(ID666TagTests, GetsMixedSongTitlePropely)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedOffset = Spc::Id666::songTitleInfo.textOffset;
    params.expectedSize = Spc::Id666::songTitleInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::SongTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedSongTitleProperly)
{
    tag->ExtendedData()->songTitle = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedSize = expectedSongTitle.size();
    params.extendedID = Spc::Id666::Extended::songTitleInfo.id;
    params.extendedType = Spc::Id666::Extended::stringType;
    params.extendedValue = expectedSongTitle;
    params.item = tag->ExtendedData()->songTitle;
    params.getMethodPtr = &Spc::Id666::Tag::SongTitle;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextGameTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedOffset = Spc::Id666::gameTitleInfo.textOffset;
    params.expectedSize = Spc::Id666::gameTitleInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::GameTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryGameTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedOffset = Spc::Id666::gameTitleInfo.binaryOffset;
    params.expectedSize = Spc::Id666::gameTitleInfo.binarySize;
    params.getMethodPtr = &Spc::Id666::Tag::GameTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedGameTitleProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedOffset = Spc::Id666::gameTitleInfo.textOffset;
    params.expectedSize = Spc::Id666::gameTitleInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::GameTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedGameTitleProperly)
{
    tag->ExtendedData()->gameTitle = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedSize = expectedGameTitle.size();
    params.extendedID = Spc::Id666::Extended::gameTitleInfo.id;
    params.extendedType = Spc::Id666::Extended::stringType;
    params.extendedValue = expectedGameTitle;
    params.item = tag->ExtendedData()->gameTitle;
    params.getMethodPtr = &Spc::Id666::Tag::GameTitle;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextDumperNameProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedOffset = Spc::Id666::dumperNameInfo.textOffset;
    params.expectedSize = Spc::Id666::dumperNameInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::DumperName;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryDumperNameProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedOffset = Spc::Id666::dumperNameInfo.binaryOffset;
    params.expectedSize = Spc::Id666::dumperNameInfo.binarySize;
    params.getMethodPtr = &Spc::Id666::Tag::DumperName;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedDumperNameProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedOffset = Spc::Id666::dumperNameInfo.textOffset;
    params.expectedSize = Spc::Id666::dumperNameInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::DumperName;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedDumperProperly)
{
    tag->ExtendedData()->dumperName = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedSize = expectedDumperName.size();
    params.extendedID = Spc::Id666::Extended::dumperNameInfo.id;
    params.extendedType = Spc::Id666::Extended::stringType;
    params.extendedValue = expectedDumperName;
    params.item = tag->ExtendedData()->dumperName;
    params.getMethodPtr = &Spc::Id666::Tag::DumperName;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextCommentsProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedOffset = Spc::Id666::commentsInfo.textOffset;
    params.expectedSize = Spc::Id666::commentsInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::Comments;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryCommentsProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedOffset = Spc::Id666::commentsInfo.binaryOffset;
    params.expectedSize = Spc::Id666::commentsInfo.binarySize;
    params.getMethodPtr = &Spc::Id666::Tag::Comments;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedCommentsProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedOffset = Spc::Id666::commentsInfo.textOffset;
    params.expectedSize = Spc::Id666::commentsInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::Comments;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedCommentsProperly)
{
    tag->ExtendedData()->comments = 
    std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedSize = expectedComments.size();
    params.extendedID = Spc::Id666::Extended::commentsInfo.id;
    params.extendedType = Spc::Id666::Extended::stringType;
    params.extendedValue = expectedComments;
    params.item = tag->ExtendedData()->comments;
    params.getMethodPtr = &Spc::Id666::Tag::Comments;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextDateDumpedProperly)
{
    TestGetParameters<Spc::DateField> params;
    params.testData = textData;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedOffset = Spc::Id666::dateDumpedInfo.textOffset;
    params.expectedSize = Spc::Id666::dateDumpedInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::DateDumped;
    TestGet<Spc::DateField>(params);
}

TEST_F(ID666TagTests, GetsBinaryDateDumpedProperly)
{
    TestGetParameters<Spc::DateField> params;
    params.testData = binaryData;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedOffset = Spc::Id666::dateDumpedInfo.binaryOffset;
    params.expectedSize = Spc::Id666::dateDumpedInfo.binarySize;
    params.getMethodPtr = &Spc::Id666::Tag::DateDumped;
    TestGet<Spc::DateField>(params);
}

TEST_F(ID666TagTests, GetsMixedDateDumpedProperly)
{
    TestGetParameters<Spc::DateField> params;
    params.testData = mixedData;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedOffset = Spc::Id666::dateDumpedInfo.textOffset;
    params.expectedSize = Spc::Id666::dateDumpedInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::DateDumped;
    TestGet<Spc::DateField>(params);
}

TEST_F(ID666TagTests, GetsExtendedDateDumpedProperly)
{
    tag->ExtendedData()->dateDumped = 
        std::make_shared<Spc::Id666::Extended::Item>();
    
    TestGetWithExtendedItemParameters<Spc::DateField> params;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedSize = Spc::Id666::dateDumpedInfo.binarySize;
    params.extendedID = Spc::Id666::Extended::dateDumpedInfo.id;
    params.extendedType = Spc::Id666::Extended::integerType;

    // The decimal representation of the binary format date.
    params.extendedValue = "131072518"; 

    params.item = tag->ExtendedData()->dateDumped;
    params.getMethodPtr = &Spc::Id666::Tag::DateDumped;
    TestGetWithExtendedItem<Spc::DateField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsTextSongLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = textData;
    params.expectedLabel = "Song Length (seconds)";
    params.expectedValue = "123";
    params.expectedOffset = Spc::Id666::songLengthInfo.textOffset;
    params.expectedSize = Spc::Id666::songLengthInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::SongLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsBinarySongLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = binaryData;
    params.expectedLabel = "Song Length (seconds)";
    params.expectedValue = "43";
    params.expectedOffset = Spc::Id666::songLengthInfo.binaryOffset;
    params.expectedSize = Spc::Id666::songLengthInfo.binarySize;
    params.getMethodPtr = &Spc::Id666::Tag::SongLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsMixedSongLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = mixedData;
    params.expectedLabel = "Song Length (seconds)";
    params.expectedValue = "123";
    params.expectedOffset = Spc::Id666::songLengthInfo.textOffset;
    params.expectedSize = Spc::Id666::songLengthInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::SongLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetTextFadeLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = textData;
    params.expectedLabel = "Fade Length (ms)";
    params.expectedValue = "05000";
    params.expectedOffset = Spc::Id666::fadeLengthInfo.textOffset;
    params.expectedSize = Spc::Id666::fadeLengthInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::FadeLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsBinaryFadeLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = binaryData;
    params.expectedLabel = "Fade Length (ms)";
    params.expectedValue = "5000";
    params.expectedOffset = Spc::Id666::fadeLengthInfo.binaryOffset;
    params.expectedSize = Spc::Id666::fadeLengthInfo.binarySize;
    params.getMethodPtr = &Spc::Id666::Tag::FadeLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsMixedFadeLengthProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = mixedData;
    params.expectedLabel = "Fade Length (ms)";
    params.expectedValue = "50000";
    params.expectedOffset = Spc::Id666::fadeLengthInfo.textOffset;
    params.expectedSize = Spc::Id666::fadeLengthInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::FadeLength;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsTextArtistProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedOffset = Spc::Id666::songArtistInfo.textOffset;
    params.expectedSize = Spc::Id666::songArtistInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::SongArtist;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryArtistProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedOffset = Spc::Id666::songArtistInfo.binaryOffset;
    params.expectedSize = Spc::Id666::songArtistInfo.binarySize;
    params.getMethodPtr = &Spc::Id666::Tag::SongArtist;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedArtistProperly)
{
    TestGetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedOffset = Spc::Id666::songArtistInfo.textOffset;
    params.expectedSize = Spc::Id666::songArtistInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::SongArtist;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedArtistProperly)
{
    tag->ExtendedData()->songArtist = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedSize = expectedSongArtist.size();
    params.extendedID = Spc::Id666::Extended::songArtistInfo.id;
    params.extendedType = Spc::Id666::Extended::stringType;
    params.extendedValue = expectedSongArtist;
    params.item = tag->ExtendedData()->songArtist;
    params.getMethodPtr = &Spc::Id666::Tag::SongArtist;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextDefaultChannelStateProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = textData;
    params.expectedLabel = "Default Channel State";
    params.expectedValue = "0";
    params.expectedOffset = Spc::Id666::defaultChannelStateInfo.textOffset;
    params.expectedSize = Spc::Id666::defaultChannelStateInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::DefaultChannelState;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsBinaryDefaultChannelStateProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = binaryData;
    params.expectedLabel = "Default Channel State";
    params.expectedValue = "0";
    params.expectedOffset = Spc::Id666::defaultChannelStateInfo.binaryOffset;
    params.expectedSize = Spc::Id666::defaultChannelStateInfo.binarySize;
    params.getMethodPtr = &Spc::Id666::Tag::DefaultChannelState;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsMixedDefaultChannelStateProperly)
{
    TestGetParameters<Spc::NumericField> params;
    params.testData = mixedData;
    params.expectedLabel = "Default Channel State";
    params.expectedValue = "0";
    params.expectedOffset = Spc::Id666::defaultChannelStateInfo.textOffset;
    params.expectedSize = Spc::Id666::defaultChannelStateInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::DefaultChannelState;
    TestGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsTextEmulatorUsedProperly)
{
    TestGetParameters<Spc::EmulatorField> params;
    params.testData = textData;
    params.expectedLabel = "Emulator Used";
    params.expectedValue = "SNES9X";
    params.expectedOffset = Spc::Id666::emulatorUsedInfo.textOffset;
    params.expectedSize = Spc::Id666::emulatorUsedInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::EmulatorUsed;
    TestGet<Spc::EmulatorField>(params);
}

TEST_F(ID666TagTests, GetsBinaryEmulatorUsedProperly)
{
    TestGetParameters<Spc::EmulatorField> params;
    params.testData = binaryData;
    params.expectedLabel = "Emulator Used";
    params.expectedValue = "SNES9X";
    params.expectedOffset = Spc::Id666::emulatorUsedInfo.binaryOffset;
    params.expectedSize = Spc::Id666::emulatorUsedInfo.binarySize;
    params.getMethodPtr = &Spc::Id666::Tag::EmulatorUsed;
    TestGet<Spc::EmulatorField>(params);
}

TEST_F(ID666TagTests, GetsMixedEmulatorUsedProperly)
{
    TestGetParameters<Spc::EmulatorField> params;
    params.testData = mixedData;
    params.expectedLabel = "Emulator Used";
    params.expectedValue = "SNES9X";
    params.expectedOffset = Spc::Id666::emulatorUsedInfo.textOffset;
    params.expectedSize = Spc::Id666::emulatorUsedInfo.textSize;
    params.getMethodPtr = &Spc::Id666::Tag::EmulatorUsed;
    TestGet<Spc::EmulatorField>(params);
}

TEST_F(ID666TagTests, GetsExtendedEmulatorUsedProperly)
{
    tag->ExtendedData()->emulatorUsed = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::EmulatorField> params;
    params.expectedLabel = "Emulator Used";
    params.expectedValue = "SNES9X";
    params.expectedSize = Spc::Id666::emulatorUsedInfo.binarySize;
    params.extendedID = Spc::Id666::Extended::emulatorUsedInfo.id;
    params.extendedType = Spc::Id666::Extended::emulatorUsedInfo.type;
    params.extendedValue = "2";
    params.item = tag->ExtendedData()->emulatorUsed;
    params.getMethodPtr = &Spc::Id666::Tag::EmulatorUsed;
    TestGetWithExtendedItem<Spc::EmulatorField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsOstTitleProperly)
{
    tag->ExtendedData()->ostTitle = 
        std::make_shared<Spc::Id666::Extended::Item>();
    std::string expectedOstTitle = "Test Album Title ABCDEFGHIJ";
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "OST Title";
    params.expectedValue = expectedOstTitle;
    params.expectedSize = expectedOstTitle.size();
    params.extendedID = Spc::Id666::Extended::ostTitleInfo.id;
    params.extendedType = Spc::Id666::Extended::ostTitleInfo.type;
    params.extendedValue = expectedOstTitle;
    params.item = tag->ExtendedData()->ostTitle;
    params.getMethodPtr = &Spc::Id666::Tag::OstTitle;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsOstDiscProperly)
{
    tag->ExtendedData()->ostDisc = 
        std::make_shared<Spc::Id666::Extended::Item>();

    // We need to explicity set the data type to binary or it will be
    // interpreted as text by default.
    std::shared_ptr<Spc::Id666::Extended::Item> ostDisc = 
        tag->ExtendedData()->ostDisc;
    auto ostDiscData = std::static_pointer_cast<Spc::NumericField>(
        ostDisc->data);
    ostDiscData->SetType(Spc::NumericType::Binary);

    TestGetWithExtendedItemParameters<Spc::NumericField> params;
    params.expectedLabel = "OST Disc";
    params.expectedValue = "1";
    params.expectedSize = 2;
    params.extendedID = Spc::Id666::Extended::ostDiscInfo.id;
    params.extendedType = Spc::Id666::Extended::ostDiscInfo.type;
    params.extendedValue = "1";
    params.item = tag->ExtendedData()->ostDisc;
    params.getMethodPtr = &Spc::Id666::Tag::OstDisc;
    TestGetWithExtendedItem<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsOstTrackProperly)
{
    tag->ExtendedData()->ostTrack = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::TrackField> params;
    params.expectedLabel = "OST Track";
    params.expectedValue = "5b";
    params.expectedSize = 2;
    params.extendedID = Spc::Id666::Extended::ostTrackInfo.id;
    params.extendedType = Spc::Id666::Extended::ostTrackInfo.type;
    params.extendedValue = "5b";
    params.item = tag->ExtendedData()->ostTrack;
    params.getMethodPtr = &Spc::Id666::Tag::OstTrack;
    TestGetWithExtendedItem<Spc::TrackField, Spc::TrackField>(params);
}

TEST_F(ID666TagTests, GetsPublisherNameProperly)
{
    tag->ExtendedData()->publisherName = 
        std::make_shared<Spc::Id666::Extended::Item>();
    std::string expectedPublisherName = "Test Publisher Name 123456";
    TestGetWithExtendedItemParameters<Spc::TextField> params;
    params.expectedLabel = "Publisher Name";
    params.expectedValue = expectedPublisherName;
    params.expectedSize = expectedPublisherName.size();
    params.extendedID = Spc::Id666::Extended::publisherNameInfo.id;
    params.extendedType = Spc::Id666::Extended::publisherNameInfo.type;
    params.extendedValue = expectedPublisherName;
    params.item = tag->ExtendedData()->publisherName;
    params.getMethodPtr = &Spc::Id666::Tag::PublisherName;
    TestGetWithExtendedItem<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsCopyrightYearProperly)
{
    tag->ExtendedData()->copyrightYear = 
        std::make_shared<Spc::Id666::Extended::Item>();

    // We need to explicity set the data type to binary or it will be
    // interpreted as text by default.
    std::shared_ptr<Spc::Id666::Extended::Item> copyrightYear = 
        tag->ExtendedData()->copyrightYear;
    auto copyrightYearData = std::static_pointer_cast<Spc::NumericField>(
        copyrightYear->data);
    copyrightYearData->SetType(Spc::NumericType::Binary);

    TestGetWithExtendedItemParameters<Spc::NumericField> params;
    params.expectedLabel = "Copyright Year";
    params.expectedValue = "1995";
    params.expectedSize = 2;
    params.extendedID = Spc::Id666::Extended::copyrightYearInfo.id;
    params.extendedType = Spc::Id666::Extended::copyrightYearInfo.type;
    params.extendedValue = "1995";
    params.item = tag->ExtendedData()->copyrightYear;
    params.getMethodPtr = &Spc::Id666::Tag::CopyrightYear;
    TestGetWithExtendedItem<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsIntroLengthProperly)
{
    tag->ExtendedData()->introLength = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::NumericField> params;
    params.expectedLabel = "Intro Length (ticks)";
    params.expectedValue = "15000";
    params.expectedSize = 4;
    params.extendedID = Spc::Id666::Extended::introLengthInfo.id;
    params.extendedType = Spc::Id666::Extended::introLengthInfo.type;
    params.extendedValue = "15000";
    params.item = tag->ExtendedData()->introLength;
    params.getMethodPtr = &Spc::Id666::Tag::IntroLength;
    TestGetWithExtendedItem<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsLoopLengthProperly)
{
    tag->ExtendedData()->loopLength = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::NumericField> params;
    params.expectedLabel = "Loop Length (ticks)";
    params.expectedValue = "30000";
    params.expectedSize = 4;
    params.extendedID = Spc::Id666::Extended::loopLengthInfo.id;
    params.extendedType = Spc::Id666::Extended::loopLengthInfo.type;
    params.extendedValue = "30000";
    params.item = tag->ExtendedData()->loopLength;
    params.getMethodPtr = &Spc::Id666::Tag::LoopLength;
    TestGetWithExtendedItem<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsEndLengthProperly)
{
    tag->ExtendedData()->endLength = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::NumericField> params;
    params.expectedLabel = "End Length (ticks)";
    params.expectedValue = "20000";
    params.expectedSize = 4;
    params.extendedID = Spc::Id666::Extended::endLengthInfo.id;
    params.extendedType = Spc::Id666::Extended::endLengthInfo.type;
    params.extendedValue = "20000";
    params.item = tag->ExtendedData()->endLength;
    params.getMethodPtr = &Spc::Id666::Tag::EndLength;
    TestGetWithExtendedItem<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsMutedVoicesProperly)
{
    auto item = std::make_shared<Spc::Id666::Extended::Item>();

    // item->data is created as a Spc::NumericField by default. We have to
    // set our test data as a numeric field even though it will be read in as
    // a Spc::BinaryField.
    auto itemData = std::static_pointer_cast<Spc::NumericField>(item->data);

    // We need to explicity set the data type of our test item data to binary 
    // or it will be interpreted as text by default when we set the expected
    // value, which will attempt to set it as ASCII characters.
    itemData->SetType(Spc::NumericType::Binary);

    tag->ExtendedData()->mutedVoices = item;
    TestGetWithExtendedItemParameters<Spc::BinaryField> params;
    params.expectedLabel = "Muted Voices";
    params.expectedValue = "00001111";
    params.expectedSize = 1;
    params.extendedID = Spc::Id666::Extended::mutedVoicesInfo.id;
    params.extendedType = Spc::Id666::Extended::mutedVoicesInfo.type;

    // 15 is 00001111 in binary.
    params.extendedValue = "15";

    params.item = item;

    params.getMethodPtr = &Spc::Id666::Tag::MutedVoices;
    TestGetWithExtendedItem<Spc::BinaryField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetLoopTimes)
{
    tag->ExtendedData()->loopTimes = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::NumericField> params;
    params.expectedLabel = "Loop Times";
    params.expectedValue = "5";
    params.expectedSize = 2;
    params.extendedID = Spc::Id666::Extended::loopTimesInfo.id;
    params.extendedType = Spc::Id666::Extended::loopTimesInfo.type;
    params.extendedValue = "5";
    params.item = tag->ExtendedData()->loopTimes;
    params.getMethodPtr = &Spc::Id666::Tag::LoopTimes;
    TestGetWithExtendedItem<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetPreampLevel)
{
    tag->ExtendedData()->preampLevel = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetWithExtendedItemParameters<Spc::NumericField> params;
    params.expectedLabel = "Preamp Level";
    params.expectedValue = "65536";
    params.expectedSize = 4;
    params.extendedID = Spc::Id666::Extended::preampLevelInfo.id;
    params.extendedType = Spc::Id666::Extended::preampLevelInfo.type;
    params.extendedValue = "65536";
    params.item = tag->ExtendedData()->preampLevel;
    params.getMethodPtr = &Spc::Id666::Tag::PreampLevel;
    TestGetWithExtendedItem<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, SetsTextSongTitleProperly)
{
    TestSetParameters<Spc::TextField> params;
    params.testData = textData;
    params.offset = Spc::Id666::songTitleInfo.textOffset;
    params.size = Spc::Id666::songTitleInfo.textSize;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongTitle;
    params.setValue = "Set Song Title";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsBinarySongTitleProperly)
{
    TestSetParameters<Spc::TextField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::songTitleInfo.binaryOffset;
    params.size = Spc::Id666::songTitleInfo.binarySize;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongTitle;
    params.setValue = "Set Song Title";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsMixedSongTitleProperly)
{
    TestSetParameters<Spc::TextField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::songTitleInfo.textOffset;
    params.size = Spc::Id666::songTitleInfo.textSize;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongTitle;
    params.setValue = "Set Song Title";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsNewExtendedSongTitleProperly)
{
    TestSetWithExtendedItemParameters<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 33.
    extParams.setValue = "Set Song Title ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    extParams.extendedID = Spc::Id666::Extended::songTitleInfo.id;
    extParams.extendedType = Spc::Id666::Extended::songTitleInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->songTitle;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetSongTitle;

    TestFieldWithoutGetParameters params;
    params.offset = Spc::Id666::songTitleInfo.textOffset;
    params.size = Spc::Id666::songTitleInfo.textSize;

    // Set should also set the standard field to a truncated value (33 chars).
    params.expectedValue = "Set Song Title ABCDEFGHIJKLMNOPQ";

    TestSetWithExtendedItem<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsExistingExtendedSongTitleProperly)
{
    std::string setValue = "Set Song Title ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    tag->ExtendedData()->songTitle = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::songTitleInfo, 
        setValue);
   
    TestSetWithExtendedItemParameters<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 33.
    extParams.setValue = setValue;

    extParams.extendedID = Spc::Id666::Extended::songTitleInfo.id;
    extParams.extendedType = Spc::Id666::Extended::songTitleInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->songTitle;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetSongTitle;

    TestFieldWithoutGetParameters params;
    params.offset = Spc::Id666::songTitleInfo.textOffset;
    params.size = Spc::Id666::songTitleInfo.textSize;

    // Set should also set the standard field to a truncated value (33 chars).
    params.expectedValue = "Set Song Title ABCDEFGHIJKLMNOPQ";

    TestSetWithExtendedItem<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}
