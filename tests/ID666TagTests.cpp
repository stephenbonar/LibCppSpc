// ID666TagTests.cpp - Defines the ID666TagTests class and tests.
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
    0x0F,
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
    0x0F,
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
    0x0F,
    // 0xD2: Emulator used (1 byte, little endian binary: 2)
    '2',
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
    TestGetParams<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedOffset = Spc::Id666::songTitleInfo.text.offset;
    params.expectedSize = Spc::Id666::songTitleInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::SongTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinarySongTitleProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedOffset = Spc::Id666::songTitleInfo.binary.offset;
    params.expectedSize = Spc::Id666::songTitleInfo.binary.size;
    params.getMethodPtr = &Spc::Id666::Tag::SongTitle;
    TestGet<Spc::TextField>(params); 
}

TEST_F(ID666TagTests, GetsMixedSongTitlePropely)
{
    TestGetParams<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Song Title";
    params.expectedValue = expectedSongTitle;
    params.expectedOffset = Spc::Id666::songTitleInfo.text.offset;
    params.expectedSize = Spc::Id666::songTitleInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::SongTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedSongTitleProperly)
{
    tag->ExtendedData()->songTitle = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::TextField> params;
    params.expectedLabel = "Song Title*";
    params.expectedValue = expectedSongTitle;
    params.expectedSize = expectedSongTitle.size();
    params.extendedID = Spc::Id666::Extended::songTitleInfo.id;
    params.extendedType = Spc::Id666::Extended::stringType;
    params.extendedValue = expectedSongTitle;
    params.item = tag->ExtendedData()->songTitle;
    params.getMethodPtr = &Spc::Id666::Tag::SongTitle;
    TestGetExtendedData<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextGameTitleProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedOffset = Spc::Id666::gameTitleInfo.text.offset;
    params.expectedSize = Spc::Id666::gameTitleInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::GameTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryGameTitleProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedOffset = Spc::Id666::gameTitleInfo.binary.offset;
    params.expectedSize = Spc::Id666::gameTitleInfo.binary.size;
    params.getMethodPtr = &Spc::Id666::Tag::GameTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedGameTitleProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Game Title";
    params.expectedValue = expectedGameTitle;
    params.expectedOffset = Spc::Id666::gameTitleInfo.text.offset;
    params.expectedSize = Spc::Id666::gameTitleInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::GameTitle;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedGameTitleProperly)
{
    tag->ExtendedData()->gameTitle = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::TextField> params;
    params.expectedLabel = "Game Title*";
    params.expectedValue = expectedGameTitle;
    params.expectedSize = expectedGameTitle.size();
    params.extendedID = Spc::Id666::Extended::gameTitleInfo.id;
    params.extendedType = Spc::Id666::Extended::stringType;
    params.extendedValue = expectedGameTitle;
    params.item = tag->ExtendedData()->gameTitle;
    params.getMethodPtr = &Spc::Id666::Tag::GameTitle;
    TestGetExtendedData<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextDumperNameProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedOffset = Spc::Id666::dumperNameInfo.text.offset;
    params.expectedSize = Spc::Id666::dumperNameInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::DumperName;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryDumperNameProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedOffset = Spc::Id666::dumperNameInfo.binary.offset;
    params.expectedSize = Spc::Id666::dumperNameInfo.binary.size;
    params.getMethodPtr = &Spc::Id666::Tag::DumperName;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedDumperNameProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Dumper Name";
    params.expectedValue = expectedDumperName;
    params.expectedOffset = Spc::Id666::dumperNameInfo.text.offset;
    params.expectedSize = Spc::Id666::dumperNameInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::DumperName;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedDumperProperly)
{
    tag->ExtendedData()->dumperName = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::TextField> params;
    params.expectedLabel = "Dumper Name*";
    params.expectedValue = expectedDumperName;
    params.expectedSize = expectedDumperName.size();
    params.extendedID = Spc::Id666::Extended::dumperNameInfo.id;
    params.extendedType = Spc::Id666::Extended::stringType;
    params.extendedValue = expectedDumperName;
    params.item = tag->ExtendedData()->dumperName;
    params.getMethodPtr = &Spc::Id666::Tag::DumperName;
    TestGetExtendedData<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextCommentsProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedOffset = Spc::Id666::commentsInfo.text.offset;
    params.expectedSize = Spc::Id666::commentsInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::Comments;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryCommentsProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedOffset = Spc::Id666::commentsInfo.binary.offset;
    params.expectedSize = Spc::Id666::commentsInfo.binary.size;
    params.getMethodPtr = &Spc::Id666::Tag::Comments;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedCommentsProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Comments";
    params.expectedValue = expectedComments;
    params.expectedOffset = Spc::Id666::commentsInfo.text.offset;
    params.expectedSize = Spc::Id666::commentsInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::Comments;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedCommentsProperly)
{
    tag->ExtendedData()->comments = 
    std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::TextField> params;
    params.expectedLabel = "Comments*";
    params.expectedValue = expectedComments;
    params.expectedSize = expectedComments.size();
    params.extendedID = Spc::Id666::Extended::commentsInfo.id;
    params.extendedType = Spc::Id666::Extended::stringType;
    params.extendedValue = expectedComments;
    params.item = tag->ExtendedData()->comments;
    params.getMethodPtr = &Spc::Id666::Tag::Comments;
    TestGetExtendedData<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextDateDumpedProperly)
{
    TestGetParams<Spc::DateField> params;
    params.testData = textData;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedOffset = Spc::Id666::dateDumpedInfo.text.offset;
    params.expectedSize = Spc::Id666::dateDumpedInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::DateDumped;
    bool isText{ true };
    TestNumericGet<Spc::DateField>(params, isText);
}

TEST_F(ID666TagTests, GetsBinaryDateDumpedProperly)
{
    TestGetParams<Spc::DateField> params;
    params.testData = binaryData;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedOffset = Spc::Id666::dateDumpedInfo.binary.offset;
    params.expectedSize = Spc::Id666::dateDumpedInfo.binary.size;
    bool isText{ false };
    params.getMethodPtr = &Spc::Id666::Tag::DateDumped;
    TestNumericGet<Spc::DateField>(params, isText);
}

TEST_F(ID666TagTests, GetsMixedDateDumpedProperly)
{
    TestGetParams<Spc::DateField> params;
    params.testData = mixedData;
    params.expectedLabel = "Date Dumped";
    params.expectedValue = expectedDateDumped;
    params.expectedOffset = Spc::Id666::dateDumpedInfo.text.offset;
    params.expectedSize = Spc::Id666::dateDumpedInfo.text.size;
    bool isText{ true };
    params.getMethodPtr = &Spc::Id666::Tag::DateDumped;
    TestNumericGet<Spc::DateField>(params, isText);
}

TEST_F(ID666TagTests, GetsExtendedDateDumpedProperly)
{
    tag->ExtendedData()->dateDumped = 
        std::make_shared<Spc::Id666::Extended::Item>();
    
    TestGetExtendedParams<Spc::DateField> params;
    params.expectedLabel = "Date Dumped*";
    params.expectedValue = expectedDateDumped;
    params.expectedSize = Spc::Id666::dateDumpedInfo.binary.size;
    params.extendedID = Spc::Id666::Extended::dateDumpedInfo.id;
    params.extendedType = Spc::Id666::Extended::integerType;

    // The decimal representation of the binary format date.
    params.extendedValue = "131072518"; 

    params.item = tag->ExtendedData()->dateDumped;
    params.getMethodPtr = &Spc::Id666::Tag::DateDumped;
    TestGetExtendedData<Spc::DateField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsTextSongLengthProperly)
{
    TestGetParams<Spc::NumericField> params;
    params.testData = textData;
    params.expectedLabel = "Song Length (seconds)";
    params.expectedValue = "123";
    params.expectedOffset = Spc::Id666::songLengthInfo.text.offset;
    params.expectedSize = Spc::Id666::songLengthInfo.text.size;
    bool isText{ true };
    params.getMethodPtr = &Spc::Id666::Tag::SongLength;
    TestNumericGet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, GetsBinarySongLengthProperly)
{
    TestGetParams<Spc::NumericField> params;
    params.testData = binaryData;
    params.expectedLabel = "Song Length (seconds)";
    params.expectedValue = "43";
    params.expectedOffset = Spc::Id666::songLengthInfo.binary.offset;
    params.expectedSize = Spc::Id666::songLengthInfo.binary.size;
    bool isText{ false };
    params.getMethodPtr = &Spc::Id666::Tag::SongLength;
    TestNumericGet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, GetsMixedSongLengthProperly)
{
    TestGetParams<Spc::NumericField> params;
    params.testData = mixedData;
    params.expectedLabel = "Song Length (seconds)";
    params.expectedValue = "123";
    params.expectedOffset = Spc::Id666::songLengthInfo.text.offset;
    params.expectedSize = Spc::Id666::songLengthInfo.text.size;
    bool isText{ false };
    params.getMethodPtr = &Spc::Id666::Tag::SongLength;
    TestNumericGet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, GetTextFadeLengthProperly)
{
    TestGetParams<Spc::NumericField> params;
    params.testData = textData;
    params.expectedLabel = "Fade Length (ms)";
    params.expectedValue = "05000";
    params.expectedOffset = Spc::Id666::fadeLengthInfo.text.offset;
    params.expectedSize = Spc::Id666::fadeLengthInfo.text.size;
    bool isText{ true };
    params.getMethodPtr = &Spc::Id666::Tag::FadeLength;
    TestNumericGet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, GetsBinaryFadeLengthProperly)
{
    TestGetParams<Spc::NumericField> params;
    params.testData = binaryData;
    params.expectedLabel = "Fade Length (ms)";
    params.expectedValue = "5000";
    params.expectedOffset = Spc::Id666::fadeLengthInfo.binary.offset;
    params.expectedSize = Spc::Id666::fadeLengthInfo.binary.size;
    bool isText{ false };
    params.getMethodPtr = &Spc::Id666::Tag::FadeLength;
    TestNumericGet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, GetsMixedFadeLengthProperly)
{
    TestGetParams<Spc::NumericField> params;
    params.testData = mixedData;
    params.expectedLabel = "Fade Length (ms)";
    params.expectedValue = "50000";
    params.expectedOffset = Spc::Id666::fadeLengthInfo.text.offset;
    params.expectedSize = Spc::Id666::fadeLengthInfo.text.size;
    bool isText{ false };
    params.getMethodPtr = &Spc::Id666::Tag::FadeLength;
    TestNumericGet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, GetsExtendedFadeLengthProperly)
{
    tag->ExtendedData()->fadeLength = 
        std::make_shared<Spc::Id666::Extended::Item>();
    
    TestGetExtendedParams<Spc::NumericField> params;
    params.expectedLabel = "Fade Length (ticks)*";
    params.expectedValue = "320000";
    params.expectedSize = Spc::Id666::fadeLengthInfo.binary.size;
    params.extendedID = Spc::Id666::Extended::fadeLengthInfo.id;
    params.extendedType = Spc::Id666::Extended::integerType;

    // The decimal representation of the binary format date.
    params.extendedValue = "320000"; 

    params.item = tag->ExtendedData()->fadeLength;
    params.getMethodPtr = &Spc::Id666::Tag::FadeLength;
    TestGetExtendedData<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsTextArtistProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = textData;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedOffset = Spc::Id666::songArtistInfo.text.offset;
    params.expectedSize = Spc::Id666::songArtistInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::SongArtist;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsBinaryArtistProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = binaryData;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedOffset = Spc::Id666::songArtistInfo.binary.offset;
    params.expectedSize = Spc::Id666::songArtistInfo.binary.size;
    params.getMethodPtr = &Spc::Id666::Tag::SongArtist;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsMixedArtistProperly)
{
    TestGetParams<Spc::TextField> params;
    params.testData = mixedData;
    params.expectedLabel = "Song Artist";
    params.expectedValue = expectedSongArtist;
    params.expectedOffset = Spc::Id666::songArtistInfo.text.offset;
    params.expectedSize = Spc::Id666::songArtistInfo.text.size;
    params.getMethodPtr = &Spc::Id666::Tag::SongArtist;
    TestGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsExtendedArtistProperly)
{
    tag->ExtendedData()->songArtist = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::TextField> params;
    params.expectedLabel = "Song Artist*";
    params.expectedValue = expectedSongArtist;
    params.expectedSize = expectedSongArtist.size();
    params.extendedID = Spc::Id666::Extended::songArtistInfo.id;
    params.extendedType = Spc::Id666::Extended::stringType;
    params.extendedValue = expectedSongArtist;
    params.item = tag->ExtendedData()->songArtist;
    params.getMethodPtr = &Spc::Id666::Tag::SongArtist;
    TestGetExtendedData<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsTextDefaultDisabledChannelsProperly)
{
    TestGetParams<Spc::BinaryField> params;
    params.testData = textData;
    params.expectedLabel = "Default Disabled Channels";
    params.expectedValue = "00001111";
    params.expectedOffset = Spc::Id666::defaultDisabledChannelsInfo.text.offset;
    params.expectedSize = Spc::Id666::defaultDisabledChannelsInfo.text.size;
    bool isText{ false };
    params.getMethodPtr = &Spc::Id666::Tag::DefaultDisabledChannels;
    TestNumericGet<Spc::BinaryField>(params, isText);
}

TEST_F(ID666TagTests, GetsBinaryDefaultDisabledChannelsProperly)
{
    TestGetParams<Spc::BinaryField> params;
    params.testData = binaryData;
    params.expectedLabel = "Default Disabled Channels";
    params.expectedValue = "00001111";
    params.expectedOffset = Spc::Id666::defaultDisabledChannelsInfo.binary.offset;
    params.expectedSize = Spc::Id666::defaultDisabledChannelsInfo.binary.size;
    bool isText{ false };
    params.getMethodPtr = &Spc::Id666::Tag::DefaultDisabledChannels;
    TestNumericGet<Spc::BinaryField>(params, isText);
}

TEST_F(ID666TagTests, GetsMixedDefaultDisabledChannelsProperly)
{
    TestGetParams<Spc::BinaryField> params;
    params.testData = mixedData;
    params.expectedLabel = "Default Disabled Channels";
    params.expectedValue = "00001111";
    params.expectedOffset = Spc::Id666::defaultDisabledChannelsInfo.text.offset;
    params.expectedSize = Spc::Id666::defaultDisabledChannelsInfo.text.size;
    bool isText{ false };
    params.getMethodPtr = &Spc::Id666::Tag::DefaultDisabledChannels;
    TestNumericGet<Spc::BinaryField>(params, isText);
}

TEST_F(ID666TagTests, GetsTextEmulatorUsedProperly)
{
    TestGetParams<Spc::EmulatorField> params;
    params.testData = textData;
    params.expectedLabel = "Emulator Used";
    params.expectedValue = "SNES9X";
    params.expectedOffset = Spc::Id666::emulatorUsedInfo.text.offset;
    params.expectedSize = Spc::Id666::emulatorUsedInfo.text.size;
    bool isText{ true };
    params.getMethodPtr = &Spc::Id666::Tag::EmulatorUsed;
    TestNumericGet<Spc::EmulatorField>(params, isText);
}

TEST_F(ID666TagTests, GetsBinaryEmulatorUsedProperly)
{
    TestGetParams<Spc::EmulatorField> params;
    params.testData = binaryData;
    params.expectedLabel = "Emulator Used";
    params.expectedValue = "SNES9X";
    params.expectedOffset = Spc::Id666::emulatorUsedInfo.binary.offset;
    params.expectedSize = Spc::Id666::emulatorUsedInfo.binary.size;
    bool isText{ false };
    params.getMethodPtr = &Spc::Id666::Tag::EmulatorUsed;
    TestNumericGet<Spc::EmulatorField>(params, isText);
}

TEST_F(ID666TagTests, GetsMixedEmulatorUsedProperly)
{
    TestGetParams<Spc::EmulatorField> params;
    params.testData = mixedData;
    params.expectedLabel = "Emulator Used";
    params.expectedValue = "SNES9X";
    params.expectedOffset = Spc::Id666::emulatorUsedInfo.text.offset;
    params.expectedSize = Spc::Id666::emulatorUsedInfo.text.size;
    bool isText{ true };
    params.getMethodPtr = &Spc::Id666::Tag::EmulatorUsed;
    TestNumericGet<Spc::EmulatorField>(params, isText);
}

TEST_F(ID666TagTests, GetsExtendedEmulatorUsedProperly)
{
    tag->ExtendedData()->emulatorUsed = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::EmulatorField> params;
    params.expectedLabel = "Emulator Used*";
    params.expectedValue = "SNES9X";
    params.expectedSize = Spc::Id666::emulatorUsedInfo.binary.size;
    params.extendedID = Spc::Id666::Extended::emulatorUsedInfo.id;
    params.extendedType = Spc::Id666::Extended::emulatorUsedInfo.type;
    params.extendedValue = "SNES9X";
    params.item = tag->ExtendedData()->emulatorUsed;
    params.getMethodPtr = &Spc::Id666::Tag::EmulatorUsed;
    TestGetExtended<Spc::EmulatorField, Spc::EmulatorField>(params);
}

TEST_F(ID666TagTests, GetsOstTitleProperly)
{
    tag->ExtendedData()->ostTitle = 
        std::make_shared<Spc::Id666::Extended::Item>();
    std::string expectedOstTitle = "Test Album Title ABCDEFGHIJ";
    TestGetExtendedParams<Spc::TextField> params;
    params.expectedLabel = "OST Title*";
    params.expectedValue = expectedOstTitle;
    params.expectedSize = expectedOstTitle.size();
    params.extendedID = Spc::Id666::Extended::ostTitleInfo.id;
    params.extendedType = Spc::Id666::Extended::ostTitleInfo.type;
    params.extendedValue = expectedOstTitle;
    params.item = tag->ExtendedData()->ostTitle;
    params.getMethodPtr = &Spc::Id666::Tag::OstTitle;
    TestGetExtendedData<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsOstDiscProperly)
{
    tag->ExtendedData()->ostDisc = 
        std::make_shared<Spc::Id666::Extended::Item>();

    // We need to explicity set the data type to binary or it will be
    // interpreted as text by default.
    /*
    std::shared_ptr<Spc::Id666::Extended::Item> ostDisc = 
        tag->ExtendedData()->ostDisc;
    auto ostDiscData = std::static_pointer_cast<Spc::NumericField>(
        ostDisc->data);
    ostDiscData->SetType(Spc::NumericType::Binary);
    */

    TestGetExtendedParams<Spc::NumericField> params;
    params.expectedLabel = "OST Disc*";
    params.expectedValue = "1";
    params.expectedSize = 2;
    params.extendedID = Spc::Id666::Extended::ostDiscInfo.id;
    params.extendedType = Spc::Id666::Extended::ostDiscInfo.type;
    params.extendedValue = "1";
    params.item = tag->ExtendedData()->ostDisc;
    params.getMethodPtr = &Spc::Id666::Tag::OstDisc;
    TestGetExtended<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsOstTrackProperly)
{
    tag->ExtendedData()->ostTrack = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::TrackField> params;
    params.expectedLabel = "OST Track*";
    params.expectedValue = "5b";
    params.expectedSize = 2;
    params.extendedID = Spc::Id666::Extended::ostTrackInfo.id;
    params.extendedType = Spc::Id666::Extended::ostTrackInfo.type;
    params.extendedValue = "5b";
    params.item = tag->ExtendedData()->ostTrack;
    params.getMethodPtr = &Spc::Id666::Tag::OstTrack;
    TestGetExtended<Spc::TrackField, Spc::TrackField>(params);
}

TEST_F(ID666TagTests, GetsPublisherNameProperly)
{
    tag->ExtendedData()->publisherName = 
        std::make_shared<Spc::Id666::Extended::Item>();
    std::string expectedPublisherName = "Test Publisher Name 123456";
    TestGetExtendedParams<Spc::TextField> params;
    params.expectedLabel = "Publisher Name*";
    params.expectedValue = expectedPublisherName;
    params.expectedSize = expectedPublisherName.size();
    params.extendedID = Spc::Id666::Extended::publisherNameInfo.id;
    params.extendedType = Spc::Id666::Extended::publisherNameInfo.type;
    params.extendedValue = expectedPublisherName;
    params.item = tag->ExtendedData()->publisherName;
    params.getMethodPtr = &Spc::Id666::Tag::PublisherName;
    TestGetExtendedData<Spc::TextField, Spc::TextField>(params);
}

TEST_F(ID666TagTests, GetsCopyrightYearProperly)
{
    tag->ExtendedData()->copyrightYear = 
        std::make_shared<Spc::Id666::Extended::Item>();

    TestGetExtendedParams<Spc::NumericField> params;
    params.expectedLabel = "Copyright Year*";
    params.expectedValue = "1995";
    params.expectedSize = 2;
    params.extendedID = Spc::Id666::Extended::copyrightYearInfo.id;
    params.extendedType = Spc::Id666::Extended::copyrightYearInfo.type;
    params.extendedValue = "1995";
    params.item = tag->ExtendedData()->copyrightYear;
    params.getMethodPtr = &Spc::Id666::Tag::CopyrightYear;
    TestGetExtended<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsIntroLengthProperly)
{
    tag->ExtendedData()->introLength = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::NumericField> params;
    params.expectedLabel = "Intro Length (ticks)*";
    params.expectedValue = "15000";
    params.expectedSize = 4;
    params.extendedID = Spc::Id666::Extended::introLengthInfo.id;
    params.extendedType = Spc::Id666::Extended::introLengthInfo.type;
    params.extendedValue = "15000";
    params.item = tag->ExtendedData()->introLength;
    params.getMethodPtr = &Spc::Id666::Tag::IntroLength;
    TestGetExtendedData<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsLoopLengthProperly)
{
    tag->ExtendedData()->loopLength = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::NumericField> params;
    params.expectedLabel = "Loop Length (ticks)*";
    params.expectedValue = "30000";
    params.expectedSize = 4;
    params.extendedID = Spc::Id666::Extended::loopLengthInfo.id;
    params.extendedType = Spc::Id666::Extended::loopLengthInfo.type;
    params.extendedValue = "30000";
    params.item = tag->ExtendedData()->loopLength;
    params.getMethodPtr = &Spc::Id666::Tag::LoopLength;
    TestGetExtendedData<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsEndLengthProperly)
{
    tag->ExtendedData()->endLength = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::NumericField> params;
    params.expectedLabel = "End Length (ticks)*";
    params.expectedValue = "20000";
    params.expectedSize = 4;
    params.extendedID = Spc::Id666::Extended::endLengthInfo.id;
    params.extendedType = Spc::Id666::Extended::endLengthInfo.type;
    params.extendedValue = "20000";
    params.item = tag->ExtendedData()->endLength;
    params.getMethodPtr = &Spc::Id666::Tag::EndLength;
    TestGetExtendedData<Spc::NumericField, Spc::NumericField>(params);
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
    TestGetExtendedParams<Spc::BinaryField> params;
    params.expectedLabel = "Muted Voices*";
    params.expectedValue = "00001111";
    params.expectedSize = 1;
    params.extendedID = Spc::Id666::Extended::mutedVoicesInfo.id;
    params.extendedType = Spc::Id666::Extended::mutedVoicesInfo.type;

    // 15 is 00001111 in binary.
    params.extendedValue = "00001111";

    params.item = item;

    params.getMethodPtr = &Spc::Id666::Tag::MutedVoices;
    TestGetExtended<Spc::BinaryField, Spc::BinaryField>(params);
}

TEST_F(ID666TagTests, GetLoopTimes)
{
    tag->ExtendedData()->loopTimes = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::NumericField> params;
    params.expectedLabel = "Loop Times*";
    params.expectedValue = "5";
    params.expectedSize = 2;
    params.extendedID = Spc::Id666::Extended::loopTimesInfo.id;
    params.extendedType = Spc::Id666::Extended::loopTimesInfo.type;
    params.extendedValue = "5";
    params.item = tag->ExtendedData()->loopTimes;
    params.getMethodPtr = &Spc::Id666::Tag::LoopTimes;
    TestGetExtended<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetPreampLevel)
{
    tag->ExtendedData()->preampLevel = 
        std::make_shared<Spc::Id666::Extended::Item>();
    TestGetExtendedParams<Spc::NumericField> params;
    params.expectedLabel = "Preamp Level*";
    params.expectedValue = "65536";
    params.expectedSize = 4;
    params.extendedID = Spc::Id666::Extended::preampLevelInfo.id;
    params.extendedType = Spc::Id666::Extended::preampLevelInfo.type;
    params.extendedValue = "65536";
    params.item = tag->ExtendedData()->preampLevel;
    params.getMethodPtr = &Spc::Id666::Tag::PreampLevel;
    TestGetExtendedData<Spc::NumericField, Spc::NumericField>(params);
}

TEST_F(ID666TagTests, GetsMissingExtendedOnlyFieldAsNotPresent)
{
    tag->ExtendedData()->ostTitle = nullptr;

    Spc::TextField ostTitle = tag->OstTitle();

    EXPECT_FALSE(ostTitle.IsPresent());
    EXPECT_EQ("", ostTitle.ToString());
}

TEST_F(ID666TagTests, SetsTextSongTitleProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = textData;
    params.offset = Spc::Id666::songTitleInfo.text.offset;
    params.size = Spc::Id666::songTitleInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongTitle;
    params.setValue = "Set Song Title";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsBinarySongTitleProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::songTitleInfo.binary.offset;
    params.size = Spc::Id666::songTitleInfo.binary.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongTitle;
    params.setValue = "Set Song Title";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsMixedSongTitleProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::songTitleInfo.text.offset;
    params.size = Spc::Id666::songTitleInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongTitle;
    params.setValue = "Set Song Title";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsNewExtendedSongTitleProperly)
{
    TestSetExtendedParams<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 33.
    extParams.setValue = "Set Song Title ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    extParams.expectedValue = "Set Song Title ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    extParams.extendedID = Spc::Id666::Extended::songTitleInfo.id;
    extParams.extendedType = Spc::Id666::Extended::songTitleInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->songTitle;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetSongTitle;

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::songTitleInfo.text.offset;
    params.size = Spc::Id666::songTitleInfo.text.size;

    // Set should also set the standard field to a truncated value (33 chars).
    params.expectedValue = "Set Song Title ABCDEFGHIJKLMNOPQ";

    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsExistingExtendedSongTitleProperly)
{
    tag->ExtendedData()->songTitle = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::songTitleInfo, 
        "Existing Song Title ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   
    TestSetExtendedParams<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 33.
    extParams.setValue = "Set Song Title ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    extParams.expectedValue = "Set Song Title ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    extParams.extendedID = Spc::Id666::Extended::songTitleInfo.id;
    extParams.extendedType = Spc::Id666::Extended::songTitleInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->songTitle;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetSongTitle;

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::songTitleInfo.text.offset;
    params.size = Spc::Id666::songTitleInfo.text.size;

    // Set should also set the standard field to a truncated value (33 chars).
    params.expectedValue = "Set Song Title ABCDEFGHIJKLMNOPQ";

    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetSongTitleEnforcesPreconditions)
{
    std::string tooLongString(257, 'T');

    EXPECT_THROW(tag->SetSongTitle(tooLongString), std::out_of_range);
}

TEST_F(ID666TagTests, SetSongTitleEmptyClearsStandardAndExtendedData)
{
    std::memcpy(tag->FieldData()->RawData(), textData, Spc::Id666::tagSize);
    tag->ExtendedData()->songTitle = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::songTitleInfo,
        "Extended Song Title Value");

    EXPECT_NO_THROW(tag->SetSongTitle(""));
    EXPECT_EQ(nullptr, tag->ExtendedData()->songTitle);

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::songTitleInfo.text.offset;
    params.size = Spc::Id666::songTitleInfo.text.size;
    params.expectedValue = "";
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsTextGameTitleProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = textData;
    params.offset = Spc::Id666::gameTitleInfo.text.offset;
    params.size = Spc::Id666::gameTitleInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetGameTitle;
    params.setValue = "Set Game Title";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsBinaryGameTitleProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::gameTitleInfo.binary.offset;
    params.size = Spc::Id666::gameTitleInfo.binary.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetGameTitle;
    params.setValue = "Set Game Title";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsMixedGameTitleProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::gameTitleInfo.text.offset;
    params.size = Spc::Id666::gameTitleInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetGameTitle;
    params.setValue = "Set Game Title";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsNewExtendedGameTitleProperly)
{
    TestSetExtendedParams<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 33.
    extParams.setValue = "Set Game Title ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    extParams.expectedValue = "Set Game Title ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    extParams.extendedID = Spc::Id666::Extended::gameTitleInfo.id;
    extParams.extendedType = Spc::Id666::Extended::gameTitleInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->gameTitle;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetGameTitle;

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::gameTitleInfo.text.offset;
    params.size = Spc::Id666::gameTitleInfo.text.size;

    // Set should also set the standard field to a truncated value (33 chars).
    params.expectedValue = "Set Game Title ABCDEFGHIJKLMNOPQ";

    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsExistingExtendedGameTitleProperly)
{
    tag->ExtendedData()->gameTitle = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::gameTitleInfo, 
        "Existing Game Title ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   
    TestSetExtendedParams<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 33.
    extParams.setValue = "Set Game Title ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    extParams.expectedValue = "Set Game Title ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    extParams.extendedID = Spc::Id666::Extended::gameTitleInfo.id;
    extParams.extendedType = Spc::Id666::Extended::gameTitleInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->gameTitle;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetGameTitle;

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::gameTitleInfo.text.offset;
    params.size = Spc::Id666::gameTitleInfo.text.size;

    // Set should also set the standard field to a truncated value (33 chars).
    params.expectedValue = "Set Game Title ABCDEFGHIJKLMNOPQ";

    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetGameTitleEnforcesPreconditions)
{
    std::string tooLongString(257, 'T');

    EXPECT_THROW(tag->SetGameTitle(tooLongString), std::out_of_range);
}

TEST_F(ID666TagTests, SetsTextDumperNameProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = textData;
    params.offset = Spc::Id666::dumperNameInfo.text.offset;
    params.size = Spc::Id666::dumperNameInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetDumperName;
    params.setValue = "Set Dumper Name";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsBinaryDumperNameProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::dumperNameInfo.binary.offset;
    params.size = Spc::Id666::dumperNameInfo.binary.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetDumperName;
    params.setValue = "Set Dumper Name";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsMixedDumperNameProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::dumperNameInfo.text.offset;
    params.size = Spc::Id666::dumperNameInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetDumperName;
    params.setValue = "Set Dumper Name";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsNewExtendedDumperNameProperly)
{
    TestSetExtendedParams<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 16.
    extParams.setValue = "Set Dumper Name ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    extParams.expectedValue = "Set Dumper Name ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    extParams.extendedID = Spc::Id666::Extended::dumperNameInfo.id;
    extParams.extendedType = Spc::Id666::Extended::dumperNameInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->dumperName;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetDumperName;

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::dumperNameInfo.text.offset;
    params.size = Spc::Id666::dumperNameInfo.text.size;

    // Set should also set the standard field to a truncated value (16 chars).
    params.expectedValue = "Set Dumper Name ";

    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsExistingExtendedDumperNameProperly)
{
    tag->ExtendedData()->dumperName = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::dumperNameInfo, 
        "Existing Dumper Name ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   
    TestSetExtendedParams<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 16.
    extParams.setValue = "Set Dumper Name ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    extParams.expectedValue = "Set Dumper Name ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    extParams.extendedID = Spc::Id666::Extended::dumperNameInfo.id;
    extParams.extendedType = Spc::Id666::Extended::dumperNameInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->dumperName;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetDumperName;

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::dumperNameInfo.text.offset;
    params.size = Spc::Id666::dumperNameInfo.text.size;

    // Set should also set the standard field to a truncated value (16 chars).
    params.expectedValue = "Set Dumper Name ";

    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetDumperNameEnforcesPreconditions)
{
    std::string tooLongString(257, 'T');

    EXPECT_THROW(tag->SetDumperName(tooLongString), std::out_of_range);
}

TEST_F(ID666TagTests, SetsTextCommentsProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = textData;
    params.offset = Spc::Id666::commentsInfo.text.offset;
    params.size = Spc::Id666::commentsInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetComments;
    params.setValue = "Set Comments";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsBinaryCommentsProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::commentsInfo.binary.offset;
    params.size = Spc::Id666::commentsInfo.binary.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetComments;
    params.setValue = "Set Comments";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsMixedCommentsProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::commentsInfo.text.offset;
    params.size = Spc::Id666::commentsInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetComments;
    params.setValue = "Set Comments";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsNewExtendedCommentsProperly)
{
    TestSetExtendedParams<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 32.
    extParams.setValue = "Set Comments ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    extParams.expectedValue = "Set Comments ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    extParams.extendedID = Spc::Id666::Extended::commentsInfo.id;
    extParams.extendedType = Spc::Id666::Extended::commentsInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->comments;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetComments;

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::commentsInfo.text.offset;
    params.size = Spc::Id666::commentsInfo.text.size;

    // Set should also set the standard field to a truncated value (32 chars).
    params.expectedValue = "Set Comments ABCDEFGHIJKLMNOPQRS";

    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsExistingExtendedCommentsProperly)
{
    tag->ExtendedData()->comments = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::commentsInfo, 
        "Existing Comments ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

    TestSetExtendedParams<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 32.
    extParams.setValue = "Set Comments ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    extParams.expectedValue = "Set Comments ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    extParams.extendedID = Spc::Id666::Extended::commentsInfo.id;
    extParams.extendedType = Spc::Id666::Extended::commentsInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->comments;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetComments;

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::commentsInfo.text.offset;
    params.size = Spc::Id666::commentsInfo.text.size;

    // Set should also set the standard field to a truncated value (32 chars).
    params.expectedValue = "Set Comments ABCDEFGHIJKLMNOPQRS";

    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetCommentsEnforcesPreconditions)
{
    std::string tooLongString(257, 'T');

    EXPECT_THROW(tag->SetComments(tooLongString), std::out_of_range);
}

TEST_F(ID666TagTests, SetsTextDateDumpedProperly)
{
    TestSetParams<Spc::DateField> params;
    params.testData = textData;
    params.offset = Spc::Id666::dateDumpedInfo.text.offset;
    params.size = Spc::Id666::dateDumpedInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetDateDumped;
    params.setValue = "01/11/2026";
    bool isText{ true };
    TestNumericSet<Spc::DateField>(params, isText);
}

TEST_F(ID666TagTests, SetsBinaryDateDumpedProperly)
{
    TestSetParams<Spc::DateField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::dateDumpedInfo.binary.offset;
    params.size = Spc::Id666::dateDumpedInfo.binary.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetDateDumped;
    params.setValue = "01/11/2026";
    bool isText{ false };

    /*
    std::cerr << "Inital ptr:" << static_cast<const void *>(params.testData) << std::endl;
    for (int i = 0; i < Spc::Id666::tagSize; ++i)
    {
        std::cerr << params.testData[i] << " ";
    }
    std::cerr << std::endl;*/

    TestNumericSet<Spc::DateField>(params, isText);
}

TEST_F(ID666TagTests, SetsMixedDateDumpedProperly)
{
    TestSetParams<Spc::DateField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::dateDumpedInfo.text.offset;
    params.size = Spc::Id666::dateDumpedInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetDateDumped;
    params.setValue = "01/11/2026";
    bool isText{ true };
    TestNumericSet<Spc::DateField>(params, isText);
}

TEST_F(ID666TagTests, SetDateDumpedEnforcesPreconditions)
{
    std::string invalidFormatString{ "2026-11-01" };
    std::string nonNumericString{ "aa/bb/cccc" };
    std::string nonDateString{ "Not a date" };

    EXPECT_THROW(tag->SetDateDumped(invalidFormatString), std::invalid_argument);
    EXPECT_THROW(tag->SetDateDumped(nonNumericString), std::invalid_argument);
    EXPECT_THROW(tag->SetDateDumped(nonDateString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetsTextSongLengthProperly)
{
    TestSetParams<Spc::NumericField> params;
    params.testData = textData;
    params.offset = Spc::Id666::songLengthInfo.text.offset;
    params.size = Spc::Id666::songLengthInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongLength;
    params.setValue = "321";
    bool isText{ true };
    TestNumericSet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, SetsBinarySongLengthProperly)
{
    TestSetParams<Spc::NumericField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::songLengthInfo.binary.offset;
    params.size = Spc::Id666::songLengthInfo.binary.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongLength;
    params.setValue = "321";
    bool isText{ false };
    TestNumericSet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, SetsMixedSongLengthProperly)
{
    TestSetParams<Spc::NumericField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::songLengthInfo.text.offset;
    params.size = Spc::Id666::songLengthInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongLength;
    params.setValue = "321";
    bool isText{ false };
    TestNumericSet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, SetSongLengthEnforcesPreconditions)
{
    std::string tooLowString{ "-1" };
    std::string tooHighString{ "960" };
    std::string nonNumericString{ "abc" };

    EXPECT_THROW(tag->SetSongLength(tooLowString), std::out_of_range);
    EXPECT_THROW(tag->SetSongLength(tooHighString), std::out_of_range);
    EXPECT_THROW(tag->SetSongLength(nonNumericString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetSongLengthAcceptsEmptyString)
{
    std::memcpy(tag->FieldData()->RawData(), textData, Spc::Id666::tagSize);

    EXPECT_NO_THROW(tag->SetSongLength(""));

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::songLengthInfo.text.offset;
    params.size = Spc::Id666::songLengthInfo.text.size;
    params.expectedValue = "0";
    TestFieldsWithoutGet<Spc::NumericField>(params);
}

TEST_F(ID666TagTests, SetsTextFadeLengthProperly)
{
    TestSetParams<Spc::NumericField> params;
    params.testData = textData;
    params.offset = Spc::Id666::fadeLengthInfo.text.offset;
    params.size = Spc::Id666::fadeLengthInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetFadeLength;
    params.setValue = "321";
    bool isText{ true };
    TestNumericSet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, SetsBinaryFadeLengthProperly)
{
    TestSetParams<Spc::NumericField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::fadeLengthInfo.binary.offset;
    params.size = Spc::Id666::fadeLengthInfo.binary.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetFadeLength;
    params.setValue = "321";
    bool isText{ false };
    TestNumericSet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, SetsMixedFadeLengthProperly)
{
    TestSetParams<Spc::NumericField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::fadeLengthInfo.text.offset;
    params.size = Spc::Id666::fadeLengthInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetFadeLength;
    params.setValue = "321";
    bool isText{ false };
    TestNumericSet<Spc::NumericField>(params, isText);
}

TEST_F(ID666TagTests, SetFadeLengthEnforcesPreconditions)
{
    std::string tooLowString{ "-1" };
    std::string tooHighString{ "60000" };
    std::string nonNumericString{ "abc" };

    EXPECT_THROW(tag->SetFadeLength(tooLowString), std::out_of_range);
    EXPECT_THROW(tag->SetFadeLength(tooHighString), std::out_of_range);
    EXPECT_THROW(tag->SetFadeLength(nonNumericString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetsTextSongArtistProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = textData;
    params.offset = Spc::Id666::songArtistInfo.text.offset;
    params.size = Spc::Id666::songArtistInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongArtist;
    params.setValue = "Set Song Artist";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsBinarySongArtistProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::songArtistInfo.binary.offset;
    params.size = Spc::Id666::songArtistInfo.binary.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongArtist;
    params.setValue = "Set Song Artist";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsMixedSongArtistProperly)
{
    TestSetParams<Spc::TextField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::songArtistInfo.text.offset;
    params.size = Spc::Id666::songArtistInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetSongArtist;
    params.setValue = "Set Song Artist";
    TestSet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsNewExtendedSongArtistProperly)
{
    TestSetExtendedParams<Spc::TextField> extParams;

    // Set should set the extended area value when the value size is > 32.
    extParams.setValue = "Set Song Artist ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    extParams.expectedValue = "Set Song Artist ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    extParams.extendedID = Spc::Id666::Extended::songArtistInfo.id;
    extParams.extendedType = Spc::Id666::Extended::songArtistInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->songArtist;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetSongArtist;

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::songArtistInfo.text.offset;
    params.size = Spc::Id666::songArtistInfo.text.size;

    // Set should also set the standard field to a truncated value (32 chars).
    params.expectedValue = "Set Song Artist ABCDEFGHIJKLMNOP";

    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetsExistingExtendedSongArtistProperly)
{
    tag->ExtendedData()->songArtist = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::songArtistInfo,
        "Existing Song Artist ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

    TestSetExtendedParams<Spc::TextField> extParams;
    extParams.setValue = "Set Song Artist ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    extParams.expectedValue = "Set Song Artist ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    extParams.extendedID = Spc::Id666::Extended::songArtistInfo.id;
    extParams.extendedType = Spc::Id666::Extended::songArtistInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->songArtist;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetSongArtist;

    TestFieldWithoutGetParams params;
    params.offset = Spc::Id666::songArtistInfo.text.offset;
    params.size = Spc::Id666::songArtistInfo.text.size;
    params.expectedValue = "Set Song Artist ABCDEFGHIJKLMNOP";

    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
    TestFieldsWithoutGet<Spc::TextField>(params);
}

TEST_F(ID666TagTests, SetSongArtistEnforcesPreconditions)
{
    std::string tooLongString(257, 'T');

    EXPECT_THROW(tag->SetSongArtist(tooLongString), std::out_of_range);
}

TEST_F(ID666TagTests, SetsTextDefaultDisabledChannelsProperly)
{
    TestSetParams<Spc::BinaryField> params;
    params.testData = textData;
    params.offset = Spc::Id666::defaultDisabledChannelsInfo.text.offset;
    params.size = Spc::Id666::defaultDisabledChannelsInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetDefaultDisabledChannels;
    params.setValue = "00000001";
    bool isText{ false };
    TestNumericSet<Spc::BinaryField>(params, isText);
}

TEST_F(ID666TagTests, SetsBinaryDefaultDisabledChannelsProperly)
{
    TestSetParams<Spc::BinaryField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::defaultDisabledChannelsInfo.binary.offset;
    params.size = Spc::Id666::defaultDisabledChannelsInfo.binary.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetDefaultDisabledChannels;
    params.setValue = "00000001";
    bool isText{ false };
    TestNumericSet<Spc::BinaryField>(params, isText);
}

TEST_F(ID666TagTests, SetsMixedDefaultDisabledChannelsProperly)
{
    TestSetParams<Spc::BinaryField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::defaultDisabledChannelsInfo.text.offset;
    params.size = Spc::Id666::defaultDisabledChannelsInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetDefaultDisabledChannels;
    params.setValue = "00000001";
    bool isText{ false };
    TestNumericSet<Spc::BinaryField>(params, isText);
}

TEST_F(ID666TagTests, SetDefaultDisabledChannelsEnforcesPreconditions)
{
    std::string tooShortString{ "0001" };
    std::string tooLongString{ "111111111" };
    std::string nonBinaryString{ "9" };

    EXPECT_THROW(tag->SetDefaultDisabledChannels(tooShortString), 
                 std::invalid_argument);
    EXPECT_THROW(tag->SetDefaultDisabledChannels(tooLongString), 
                 std::invalid_argument);
    EXPECT_THROW(tag->SetDefaultDisabledChannels(nonBinaryString), 
                 std::invalid_argument);
}

TEST_F(ID666TagTests, SetsTextEmulatorUsedProperly)
{
    TestSetParams<Spc::EmulatorField> params;
    params.testData = textData;
    params.offset = Spc::Id666::emulatorUsedInfo.text.offset;
    params.size = Spc::Id666::emulatorUsedInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetEmulatorUsed;
    params.setValue = "ZSNES";
    bool isText{ true };
    TestNumericSet<Spc::EmulatorField>(params, isText);
}

TEST_F(ID666TagTests, SetsBinaryEmulatorUsedProperly)
{
    TestSetParams<Spc::EmulatorField> params;
    params.testData = binaryData;
    params.offset = Spc::Id666::emulatorUsedInfo.binary.offset;
    params.size = Spc::Id666::emulatorUsedInfo.binary.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetEmulatorUsed;
    params.setValue = "ZSNES";
    bool isText{ false };
    TestNumericSet<Spc::EmulatorField>(params, isText);
}

TEST_F(ID666TagTests, SetsMixedEmulatorUsedProperly)
{
    TestSetParams<Spc::EmulatorField> params;
    params.testData = mixedData;
    params.offset = Spc::Id666::emulatorUsedInfo.text.offset;
    params.size = Spc::Id666::emulatorUsedInfo.text.size;
    params.setMethodPtr = &Spc::Id666::Tag::SetEmulatorUsed;
    params.setValue = "ZSNES";
    bool isText{ true };
    TestNumericSet<Spc::EmulatorField>(params, isText);
}

TEST_F(ID666TagTests, SetsNewExtendedOstTitleProperly)
{
    TestSetExtendedParams<Spc::TextField> extParams;
    extParams.setValue = "Set OST Title";
    extParams.expectedValue = "Set OST Title";
    extParams.extendedID = Spc::Id666::Extended::ostTitleInfo.id;
    extParams.extendedType = Spc::Id666::Extended::ostTitleInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->ostTitle;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetOstTitle;
    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingOstTitleProperly)
{
    tag->ExtendedData()->ostTitle = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::ostTitleInfo,
        "Existing OST Title");

    TestSetExtendedParams<Spc::TextField> extParams;
    extParams.setValue = "Set OST Title";
    extParams.expectedValue = "Set OST Title";
    extParams.extendedID = Spc::Id666::Extended::ostTitleInfo.id;
    extParams.extendedType = Spc::Id666::Extended::ostTitleInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->ostTitle;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetOstTitle;
    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
}

TEST_F(ID666TagTests, SetOstTitleEnforcesPreconditions)
{
    std::string tooLongString(257, 'T');

    EXPECT_THROW(tag->SetOstTitle(tooLongString), std::out_of_range);
}

TEST_F(ID666TagTests, SetOstTitleEmptyRemovesExtendedItem)
{
    tag->ExtendedData()->ostTitle = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::ostTitleInfo,
        "Extended OST");

    EXPECT_NO_THROW(tag->SetOstTitle(""));
    EXPECT_EQ(nullptr, tag->ExtendedData()->ostTitle);

    Spc::TextField ostTitle = tag->OstTitle();
    EXPECT_FALSE(ostTitle.IsPresent());
}

TEST_F(ID666TagTests, SetsNewOstDiscProperly)
{
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "2";
    extParams.expectedValue = "2";
    extParams.extendedID = Spc::Id666::Extended::ostDiscInfo.id;
    extParams.extendedType = Spc::Id666::Extended::ostDiscInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->ostDisc;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetOstDisc;
    TestSetExtended<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingOstDiscProperly)
{
    auto item = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::ostDiscInfo,
        "1");
    tag->ExtendedData()->ostDisc = item;
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "2";
    extParams.expectedValue = "2";
    extParams.extendedID = Spc::Id666::Extended::ostDiscInfo.id;
    extParams.extendedType = Spc::Id666::Extended::ostDiscInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->ostDisc;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetOstDisc;
    TestSetExtended<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetOstDiscEnforcesPreconditions)
{
    std::string tooLowString{ "-1" };
    std::string tooHighString{ "10" };
    std::string nonNumericString{ "abc" };

    EXPECT_THROW(tag->SetOstDisc(tooLowString), std::out_of_range);
    EXPECT_THROW(tag->SetOstDisc(tooHighString), std::out_of_range);
    EXPECT_THROW(tag->SetOstDisc(nonNumericString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetsNewOstTrackProperly)
{
    TestSetExtendedParams<Spc::TrackField> extParams;
    extParams.setValue = "5b";
    extParams.expectedValue = "5b";
    extParams.extendedID = Spc::Id666::Extended::ostTrackInfo.id;
    extParams.extendedType = Spc::Id666::Extended::ostTrackInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->ostTrack;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetOstTrack;
    TestSetExtended<Spc::TrackField, Spc::TrackField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingOstTrackProperly)
{
    auto item = InitNumericExtendedItem<Spc::TrackField>(
        Spc::Id666::Extended::ostTrackInfo,
        "4");
    tag->ExtendedData()->ostTrack = item;
    TestSetExtendedParams<Spc::TrackField> extParams;
    extParams.setValue = "5b";
    extParams.expectedValue = "5b";
    extParams.extendedID = Spc::Id666::Extended::ostTrackInfo.id;
    extParams.extendedType = Spc::Id666::Extended::ostTrackInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->ostTrack;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetOstTrack;
    TestSetExtended<Spc::TrackField, Spc::TrackField>(extParams);
}

TEST_F(ID666TagTests, SetOstTrackEnforcesPreconditions)
{
    std::string tooLowString{ "-1" };
    std::string tooHighString{ "100" };
    std::string nonNumericString{ "99abc" };

    EXPECT_THROW(tag->SetOstTrack(tooLowString), std::invalid_argument);
    EXPECT_THROW(tag->SetOstTrack(tooHighString), std::out_of_range);
    EXPECT_THROW(tag->SetOstTrack(nonNumericString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetsNewPublisherNameProperly)
{
    TestSetExtendedParams<Spc::TextField> extParams;
    extParams.setValue = "Set Publisher Name";
    extParams.expectedValue = "Set Publisher Name";
    extParams.extendedID = Spc::Id666::Extended::publisherNameInfo.id;
    extParams.extendedType = Spc::Id666::Extended::publisherNameInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->publisherName;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetPublisherName;
    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingPublisherNameProperly)
{
    tag->ExtendedData()->publisherName = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::publisherNameInfo,
        "Existing Publisher Name");
    TestSetExtendedParams<Spc::TextField> extParams;
    extParams.setValue = "Set Publisher Name";
    extParams.extendedID = Spc::Id666::Extended::publisherNameInfo.id;
    extParams.extendedType = Spc::Id666::Extended::publisherNameInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->publisherName;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetPublisherName;
    extParams.expectedValue = "Set Publisher Name";
    TestSetExtendedData<Spc::TextField, Spc::TextField>(extParams);
}

TEST_F(ID666TagTests, SetPublisherNameEnforcesPreconditions)
{
    std::string tooLongString(257, 'T');

    EXPECT_THROW(tag->SetPublisherName(tooLongString), std::out_of_range);
}

TEST_F(ID666TagTests, SetsNewCopyrightYearProperly)
{
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "1995";
    extParams.expectedValue = "1995";
    extParams.extendedID = Spc::Id666::Extended::copyrightYearInfo.id;
    extParams.extendedType = Spc::Id666::Extended::copyrightYearInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->copyrightYear;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetCopyrightYear;
    TestSetExtended<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingCopyrightYearProperly)
{
    auto item = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::copyrightYearInfo,
        "1995");
    tag->ExtendedData()->copyrightYear = item;
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "1996";
    extParams.expectedValue = "1996";
    extParams.extendedID = Spc::Id666::Extended::copyrightYearInfo.id;
    extParams.extendedType = Spc::Id666::Extended::copyrightYearInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->copyrightYear;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetCopyrightYear;
    TestSetExtended<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetCopyrightYearEnforcesPreconditions)
{
    std::string tooLowString{ "-1" };
    std::string nonNumericString{ "abc" };

    EXPECT_THROW(tag->SetCopyrightYear(tooLowString), std::invalid_argument);
    EXPECT_THROW(tag->SetCopyrightYear(nonNumericString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetsNewIntroLengthProperly)
{
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "320000";
    extParams.expectedValue = "320000";
    extParams.extendedID = Spc::Id666::Extended::introLengthInfo.id;
    extParams.extendedType = Spc::Id666::Extended::introLengthInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->introLength;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetIntroLength;
    TestSetExtendedData<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingIntroLengthProperly)
{
    auto item = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::introLengthInfo,
        "320000");
    tag->ExtendedData()->introLength = item;
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "640000";
    extParams.expectedValue = "640000";
    extParams.extendedID = Spc::Id666::Extended::introLengthInfo.id;
    extParams.extendedType = Spc::Id666::Extended::introLengthInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->introLength;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetIntroLength;
    TestSetExtendedData<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetIntroLengthEnforcesPreconditions)
{
    std::string tooLowString{ "-1" };
    std::string tooHighString{ "384000000" };
    std::string nonNumericString{ "abc" };

    EXPECT_THROW(tag->SetIntroLength(tooLowString), std::out_of_range);
    EXPECT_THROW(tag->SetIntroLength(tooHighString), std::out_of_range);
    EXPECT_THROW(tag->SetIntroLength(nonNumericString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetsNewLoopLengthProperly)
{
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "3200000";
    extParams.expectedValue = "3200000";
    extParams.extendedID = Spc::Id666::Extended::loopLengthInfo.id;
    extParams.extendedType = Spc::Id666::Extended::loopLengthInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->loopLength;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetLoopLength;
    TestSetExtendedData<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingLoopLengthProperly)
{
    auto item = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::loopLengthInfo,
        "3200000");
    tag->ExtendedData()->loopLength = item;
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "3840000";
    extParams.expectedValue = "3840000";
    extParams.extendedID = Spc::Id666::Extended::loopLengthInfo.id;
    extParams.extendedType = Spc::Id666::Extended::loopLengthInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->loopLength;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetLoopLength;
    TestSetExtendedData<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetLoopLengthEnforcesPreconditions)
{
    std::string tooLowString{ "-1" };
    std::string tooHighString{ "384000000" };
    std::string nonNumericString{ "abc" };

    EXPECT_THROW(tag->SetLoopLength(tooLowString), std::out_of_range);
    EXPECT_THROW(tag->SetLoopLength(tooHighString), std::out_of_range);
    EXPECT_THROW(tag->SetLoopLength(nonNumericString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetsNewEndLengthProperly)
{
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "320000";
    extParams.expectedValue = "320000";
    extParams.extendedID = Spc::Id666::Extended::endLengthInfo.id;
    extParams.extendedType = Spc::Id666::Extended::endLengthInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->endLength;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetEndLength;
    TestSetExtendedData<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingEndLengthProperly)
{
    auto item = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::endLengthInfo,
        "320000");
    tag->ExtendedData()->endLength = item;
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "640000";
    extParams.expectedValue = "640000";
    extParams.extendedID = Spc::Id666::Extended::endLengthInfo.id;
    extParams.extendedType = Spc::Id666::Extended::endLengthInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->endLength;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetEndLength;
    TestSetExtendedData<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetEndLengthEnforcesPreconditions)
{
    std::string tooLowString{ "-1" };
    std::string tooHighString{ "384000000" };
    std::string nonNumericString{ "abc" };

    EXPECT_THROW(tag->SetEndLength(tooLowString), std::out_of_range);
    EXPECT_THROW(tag->SetEndLength(tooHighString), std::out_of_range);
    EXPECT_THROW(tag->SetEndLength(nonNumericString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetsNewMutedVoicesProperly)
{
    TestSetExtendedParams<Spc::BinaryField> extParams;
    extParams.setValue = "00001111";
    extParams.expectedValue = "00001111 00000000";
    extParams.extendedID = Spc::Id666::Extended::mutedVoicesInfo.id;
    extParams.extendedType = Spc::Id666::Extended::mutedVoicesInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->mutedVoices;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetMutedVoices;
    TestSetExtended<Spc::BinaryField, Spc::BinaryField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingMutedVoicesProperly)
{
    auto item = InitNumericExtendedItem<Spc::BinaryField>(
        Spc::Id666::Extended::mutedVoicesInfo,
        "00001111");
    tag->ExtendedData()->mutedVoices = item;
    TestSetExtendedParams<Spc::BinaryField> extParams;
    extParams.setValue = "00000001";
    extParams.expectedValue = "00000001 00000000";
    extParams.extendedID = Spc::Id666::Extended::mutedVoicesInfo.id;
    extParams.extendedType = Spc::Id666::Extended::mutedVoicesInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->mutedVoices;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetMutedVoices;
    TestSetExtended<Spc::BinaryField, Spc::BinaryField>(extParams);
}

TEST_F(ID666TagTests, SetMutedVoicesEnforcesPreconditions)
{
    std::string tooShortString{ "0001" };
    std::string tooLongString{ "111111111" };
    std::string nonBinaryString{ "9" };

    EXPECT_THROW(tag->SetMutedVoices(tooShortString), std::invalid_argument);
    EXPECT_THROW(tag->SetMutedVoices(tooLongString), std::invalid_argument);
    EXPECT_THROW(tag->SetMutedVoices(nonBinaryString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetsNewLoopTimesProperly)
{
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "2";
    extParams.expectedValue = "2";
    extParams.extendedID = Spc::Id666::Extended::loopTimesInfo.id;
    extParams.extendedType = Spc::Id666::Extended::loopTimesInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->loopTimes;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetLoopTimes;
    TestSetExtended<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingLoopTimesProperly)
{
    auto item = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::loopTimesInfo,
        "2");
    tag->ExtendedData()->loopTimes = item;
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "3";
    extParams.expectedValue = "3";
    extParams.extendedID = Spc::Id666::Extended::loopTimesInfo.id;
    extParams.extendedType = Spc::Id666::Extended::loopTimesInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->loopTimes;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetLoopTimes;
    TestSetExtended<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetLoopTimesEnforcesPreconditions)
{
    std::string tooLowString{ "-1" };
    std::string tooHighString{ "10" };
    std::string nonNumericString{ "abc" };

    EXPECT_THROW(tag->SetLoopTimes(tooLowString), std::out_of_range);
    EXPECT_THROW(tag->SetLoopTimes(tooHighString), std::out_of_range);
    EXPECT_THROW(tag->SetLoopTimes(nonNumericString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetsNewPreampLevelProperly)
{
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "65536";
    extParams.expectedValue = "65536";
    extParams.extendedID = Spc::Id666::Extended::preampLevelInfo.id;
    extParams.extendedType = Spc::Id666::Extended::preampLevelInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->preampLevel;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetPreampLevel;
    TestSetExtendedData<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetsExistingPreampLevelProperly)
{
    auto item = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::preampLevelInfo,
        "65536");
    tag->ExtendedData()->preampLevel = item;
    TestSetExtendedParams<Spc::NumericField> extParams;
    extParams.setValue = "64000";
    extParams.expectedValue = "64000";
    extParams.extendedID = Spc::Id666::Extended::preampLevelInfo.id;
    extParams.extendedType = Spc::Id666::Extended::preampLevelInfo.type;
    extParams.itemPtrPtr = &tag->ExtendedData()->preampLevel;
    extParams.setMethodPtr = &Spc::Id666::Tag::SetPreampLevel;
    TestSetExtendedData<Spc::NumericField, Spc::NumericField>(extParams);
}

TEST_F(ID666TagTests, SetPreampLevelEnforcesPreconditions)
{
    std::string tooLowString{ "32767" };
    std::string tooHighString{ "524289" };
    std::string nonNumericString{ "abc" };

    EXPECT_THROW(tag->SetPreampLevel(tooLowString), std::out_of_range);
    EXPECT_THROW(tag->SetPreampLevel(tooHighString), std::out_of_range);
    EXPECT_THROW(tag->SetPreampLevel(nonNumericString), std::invalid_argument);
}

TEST_F(ID666TagTests, SetPreampLevelEmptyRemovesExtendedItem)
{
    auto item = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::preampLevelInfo,
        "65536");
    tag->ExtendedData()->preampLevel = item;

    EXPECT_NO_THROW(tag->SetPreampLevel(""));
    EXPECT_EQ(nullptr, tag->ExtendedData()->preampLevel);

    Spc::NumericField preampLevel = tag->PreampLevel();
    EXPECT_FALSE(preampLevel.IsPresent());
}

TEST_F(ID666TagTests, SetGameTitleEmptyClearsStandardAndExtendedData)
{
    tag->ExtendedData()->gameTitle = std::make_shared<Spc::Id666::Extended::Item>();

    SetEmptyAndExpectRawFieldCleared(&Spc::Id666::Tag::SetGameTitle,
                                     Spc::Id666::gameTitleInfo.text.offset,
                                     Spc::Id666::gameTitleInfo.text.size);
    EXPECT_EQ(nullptr, tag->ExtendedData()->gameTitle);
}

TEST_F(ID666TagTests, SetDumperNameEmptyClearsStandardAndExtendedData)
{
    tag->ExtendedData()->dumperName = std::make_shared<Spc::Id666::Extended::Item>();

    SetEmptyAndExpectRawFieldCleared(&Spc::Id666::Tag::SetDumperName,
                                     Spc::Id666::dumperNameInfo.text.offset,
                                     Spc::Id666::dumperNameInfo.text.size);
    EXPECT_EQ(nullptr, tag->ExtendedData()->dumperName);
}

TEST_F(ID666TagTests, SetCommentsEmptyClearsStandardAndExtendedData)
{
    tag->ExtendedData()->comments = std::make_shared<Spc::Id666::Extended::Item>();

    SetEmptyAndExpectRawFieldCleared(&Spc::Id666::Tag::SetComments,
                                     Spc::Id666::commentsInfo.text.offset,
                                     Spc::Id666::commentsInfo.text.size);
    EXPECT_EQ(nullptr, tag->ExtendedData()->comments);
}

TEST_F(ID666TagTests, SetDateDumpedEmptyClearsStandardAndExtendedData)
{
    tag->ExtendedData()->dateDumped = std::make_shared<Spc::Id666::Extended::Item>();

    SetEmptyAndExpectRawFieldCleared(&Spc::Id666::Tag::SetDateDumped,
                                     Spc::Id666::dateDumpedInfo.text.offset,
                                     Spc::Id666::dateDumpedInfo.text.size);
    EXPECT_EQ(nullptr, tag->ExtendedData()->dateDumped);
}

TEST_F(ID666TagTests, SetSongLengthEmptyClearsStandardFieldData)
{
    SetEmptyAndExpectRawFieldCleared(&Spc::Id666::Tag::SetSongLength,
                                     Spc::Id666::songLengthInfo.text.offset,
                                     Spc::Id666::songLengthInfo.text.size);
}

TEST_F(ID666TagTests, SetFadeLengthEmptyClearsStandardAndExtendedData)
{
    tag->ExtendedData()->fadeLength = std::make_shared<Spc::Id666::Extended::Item>();

    SetEmptyAndExpectRawFieldCleared(&Spc::Id666::Tag::SetFadeLength,
                                     Spc::Id666::fadeLengthInfo.text.offset,
                                     Spc::Id666::fadeLengthInfo.text.size);
    EXPECT_EQ(nullptr, tag->ExtendedData()->fadeLength);
}

TEST_F(ID666TagTests, SetSongArtistEmptyClearsStandardAndExtendedData)
{
    tag->ExtendedData()->songArtist = std::make_shared<Spc::Id666::Extended::Item>();

    SetEmptyAndExpectRawFieldCleared(&Spc::Id666::Tag::SetSongArtist,
                                     Spc::Id666::songArtistInfo.text.offset,
                                     Spc::Id666::songArtistInfo.text.size);
    EXPECT_EQ(nullptr, tag->ExtendedData()->songArtist);
}

TEST_F(ID666TagTests, SetDefaultDisabledChannelsEmptyClearsStandardFieldData)
{
    SetEmptyAndExpectRawFieldCleared(&Spc::Id666::Tag::SetDefaultDisabledChannels,
                                     Spc::Id666::defaultDisabledChannelsInfo.text.offset,
                                     Spc::Id666::defaultDisabledChannelsInfo.text.size);
}

TEST_F(ID666TagTests, SetEmulatorUsedEmptyClearsStandardAndExtendedData)
{
    tag->ExtendedData()->emulatorUsed = std::make_shared<Spc::Id666::Extended::Item>();

    SetEmptyAndExpectRawFieldCleared(&Spc::Id666::Tag::SetEmulatorUsed,
                                     Spc::Id666::emulatorUsedInfo.text.offset,
                                     Spc::Id666::emulatorUsedInfo.text.size);
    EXPECT_EQ(nullptr, tag->ExtendedData()->emulatorUsed);
}

TEST_F(ID666TagTests, SetOstDiscEmptyClearsExtendedDataAndMarksNotPresent)
{
    tag->ExtendedData()->ostDisc = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::ostDiscInfo,
        "1");

    SetEmptyAndExpectExtendedItemCleared(&Spc::Id666::Tag::SetOstDisc,
                                         &tag->ExtendedData()->ostDisc);

    Spc::NumericField ostDisc = tag->OstDisc();
    EXPECT_FALSE(ostDisc.IsPresent());
}

TEST_F(ID666TagTests, SetOstTrackEmptyClearsExtendedDataAndMarksNotPresent)
{
    tag->ExtendedData()->ostTrack = InitNumericExtendedItem<Spc::TrackField>(
        Spc::Id666::Extended::ostTrackInfo,
        "4");

    SetEmptyAndExpectExtendedItemCleared(&Spc::Id666::Tag::SetOstTrack,
                                         &tag->ExtendedData()->ostTrack);

    Spc::TrackField ostTrack = tag->OstTrack();
    EXPECT_FALSE(ostTrack.IsPresent());
}

TEST_F(ID666TagTests, SetPublisherNameEmptyClearsExtendedDataAndMarksNotPresent)
{
    tag->ExtendedData()->publisherName = InitExtendedItem<Spc::TextField>(
        Spc::Id666::Extended::publisherNameInfo,
        "Test Publisher");

    SetEmptyAndExpectExtendedItemCleared(&Spc::Id666::Tag::SetPublisherName,
                                         &tag->ExtendedData()->publisherName);

    Spc::TextField publisherName = tag->PublisherName();
    EXPECT_FALSE(publisherName.IsPresent());
}

TEST_F(ID666TagTests, SetCopyrightYearEmptyClearsExtendedDataAndMarksNotPresent)
{
    tag->ExtendedData()->copyrightYear = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::copyrightYearInfo,
        "1995");

    SetEmptyAndExpectExtendedItemCleared(&Spc::Id666::Tag::SetCopyrightYear,
                                         &tag->ExtendedData()->copyrightYear);

    Spc::NumericField copyrightYear = tag->CopyrightYear();
    EXPECT_FALSE(copyrightYear.IsPresent());
}

TEST_F(ID666TagTests, SetIntroLengthEmptyClearsExtendedDataAndMarksNotPresent)
{
    tag->ExtendedData()->introLength = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::introLengthInfo,
        "320000");

    SetEmptyAndExpectExtendedItemCleared(&Spc::Id666::Tag::SetIntroLength,
                                         &tag->ExtendedData()->introLength);

    Spc::NumericField introLength = tag->IntroLength();
    EXPECT_FALSE(introLength.IsPresent());
}

TEST_F(ID666TagTests, SetLoopLengthEmptyClearsExtendedDataAndMarksNotPresent)
{
    tag->ExtendedData()->loopLength = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::loopLengthInfo,
        "3200000");

    SetEmptyAndExpectExtendedItemCleared(&Spc::Id666::Tag::SetLoopLength,
                                         &tag->ExtendedData()->loopLength);

    Spc::NumericField loopLength = tag->LoopLength();
    EXPECT_FALSE(loopLength.IsPresent());
}

TEST_F(ID666TagTests, SetEndLengthEmptyClearsExtendedDataAndMarksNotPresent)
{
    tag->ExtendedData()->endLength = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::endLengthInfo,
        "320000");

    SetEmptyAndExpectExtendedItemCleared(&Spc::Id666::Tag::SetEndLength,
                                         &tag->ExtendedData()->endLength);

    Spc::NumericField endLength = tag->EndLength();
    EXPECT_FALSE(endLength.IsPresent());
}

TEST_F(ID666TagTests, SetMutedVoicesEmptyClearsExtendedDataAndMarksNotPresent)
{
    tag->ExtendedData()->mutedVoices = InitNumericExtendedItem<Spc::BinaryField>(
        Spc::Id666::Extended::mutedVoicesInfo,
        "00001111");

    SetEmptyAndExpectExtendedItemCleared(&Spc::Id666::Tag::SetMutedVoices,
                                         &tag->ExtendedData()->mutedVoices);

    Spc::BinaryField mutedVoices = tag->MutedVoices();
    EXPECT_FALSE(mutedVoices.IsPresent());
}

TEST_F(ID666TagTests, SetLoopTimesEmptyClearsExtendedDataAndMarksNotPresent)
{
    tag->ExtendedData()->loopTimes = InitNumericExtendedItem<Spc::NumericField>(
        Spc::Id666::Extended::loopTimesInfo,
        "2");

    SetEmptyAndExpectExtendedItemCleared(&Spc::Id666::Tag::SetLoopTimes,
                                         &tag->ExtendedData()->loopTimes);

    Spc::NumericField loopTimes = tag->LoopTimes();
    EXPECT_FALSE(loopTimes.IsPresent());
}

TEST_F(ID666TagTests, HasExtendedTagWorksProperly)
{
    EXPECT_FALSE(tag->HasExtendedData());

    tag->ExtendedData()->gameTitle = std::make_shared<Spc::Id666::Extended::Item>();
    EXPECT_TRUE(tag->HasExtendedData());
}