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

constexpr char testTextData[] = {
    // 0x2E: Song title (32 bytes)
    'T','e','s','t',' ','S','o','n','g',' ','T','i','t','l','e',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    // 0x4E: Game title (32 bytes)
    'T','e','s','t',' ','G','a','m','e',' ','T','i','t','l','e',' ','1','2','3','4','5','6','7','8','9','0','X','Y','Z','Q','R','S',
    // 0x6E: Name of dumper (16 bytes)
    'D','u','m','p','e','r','N','a','m','e','1','2','3','4','5','6',
    // 0x7E: Comments (32 bytes)
    'T','e','s','t',' ','C','o','m','m','e','n','t','s',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
    // 0x9E: Date dumped (11 bytes, MM/DD/YYYY)
    '0','1','/','2','3','/','2','0','2','5','\0',
    // 0xA9: Seconds before fade (3 bytes, ASCII)
    '1','2','3',
    // 0xAC: Fade length ms (5 bytes, ASCII)
    '0','5','0','0','0',
    // 0xB1: Artist (32 bytes)
    'A','r','t','i','s','t',' ','N','a','m','e',' ','T','e','s','t',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
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

constexpr char testBinaryData[] = {
    // 0x2E: Song title (32 bytes)
    'T','e','s','t',' ','S','o','n','g',' ','T','i','t','l','e',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    // 0x4E: Game title (32 bytes)
    'T','e','s','t',' ','G','a','m','e',' ','T','i','t','l','e',' ','1','2','3','4','5','6','7','8','9','0','X','Y','Z','Q','R','S',
    // 0x6E: Name of dumper (16 bytes)
    'D','u','m','p','e','r','N','a','m','e','1','2','3','4','5','6',
    // 0x7E: Comments (32 bytes)
    'T','e','s','t',' ','C','o','m','m','e','n','t','s',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
    // 0x9E: Date dumped (4 bytes, YYYYMMDD, little endian)
    0xE9, 0x07, 0x06, 0x20, // 0x200607E9 = 2024-06-01 (example: 20240601, little endian)
    // 0xA2: unused (7 bytes)
    0,0,0,0,0,0,0,
    // 0xA9: Seconds before fade (3 bytes, little endian)
    0x2B, 0x00, 0x00, // 43 seconds (0x2B)
    // 0xAC: Fade length ms (4 bytes, little endian)
    0x88, 0x13, 0x00, 0x00, // 5000 ms (0x1388)
    // 0xB0: Artist (32 bytes)
    'A','r','t','i','s','t',' ','N','a','m','e',' ','T','e','s','t',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
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

constexpr char testMixedData[] = {
    // 0x2E: Song title (32 bytes)
    'T','e','s','t',' ','S','o','n','g',' ','T','i','t','l','e',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    // 0x4E: Game title (32 bytes)
    'T','e','s','t',' ','G','a','m','e',' ','T','i','t','l','e',' ','1','2','3','4','5','6','7','8','9','0','X','Y','Z','Q','R','S',
    // 0x6E: Name of dumper (16 bytes)
    'D','u','m','p','e','r','N','a','m','e','1','2','3','4','5','6',
    // 0x7E: Comments (32 bytes)
    'T','e','s','t',' ','C','o','m','m','e','n','t','s',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
    // 0x9E: Date dumped (11 bytes, MM/DD/YYYY)
    '0','1','/','2','3','/','2','0','2','5','\0',
    // 0xA9: Seconds before fade (3 bytes, little endian binary: 123)
    0x7B, 0x00, 0x00,
    // 0xAC: Fade length ms (5 bytes, first 4 bytes little endian binary: 50000, last byte ASCII '0')
    0x50, 0xC3, 0x00, 0x00, '0',
    // 0xB1: Artist (32 bytes)
    'A','r','t','i','s','t',' ','N','a','m','e',' ','T','e','s','t',' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
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
}

TEST_F(ID666TagTests, InitializesProperly)
{
    std::shared_ptr<Binary::BufferStream> data = tag->Data();
    std::shared_ptr<Spc::ID666ExtendedData> extendedData = tag->ExtendedData();

    ASSERT_NE(nullptr, data);
    ASSERT_NE(nullptr, extendedData);
    EXPECT_EQ(Spc::id666TagSize, data->Size());
}

TEST_F(ID666TagTests, GetsTextSongTitleProperly)
{
    std::memcpy(tag->Data()->Data(), testTextData, Spc::id666TagSize);

    EXPECT_EQ("Song Title", tag->SongTitle().Label());
    EXPECT_EQ(Spc::songTitleInfo.textOffset, tag->SongTitle().Offset());
    EXPECT_EQ(Spc::songTitleInfo.textSize, tag->SongTitle().Size());
    EXPECT_EQ("Test Song Title ABCDEFGHIJKLMNOP", tag->SongTitle().Value());
}

TEST_F(ID666TagTests, GetsBinarySongTitleProperly)
{
    std::memcpy(tag->Data()->Data(), testBinaryData, Spc::id666TagSize);

    EXPECT_EQ("Song Title", tag->SongTitle().Label());
    EXPECT_EQ(Spc::songTitleInfo.binaryOffset, tag->SongTitle().Offset());
    EXPECT_EQ(Spc::songTitleInfo.binarySize, tag->SongTitle().Size());
    EXPECT_EQ("Test Song Title ABCDEFGHIJKLMNOP", tag->SongTitle().Value());
}

TEST_F(ID666TagTests, GetsMixedSongTitleProperly)
{
    std::memcpy(tag->Data()->Data(), testMixedData, Spc::id666TagSize);

    EXPECT_EQ("Song Title", tag->SongTitle().Label());
    EXPECT_EQ(Spc::songTitleInfo.textOffset, tag->SongTitle().Offset());
    EXPECT_EQ(Spc::songTitleInfo.textSize, tag->SongTitle().Size());
    EXPECT_EQ("Test Song Title ABCDEFGHIJKLMNOP", tag->SongTitle().Value());
}

TEST_F(ID666TagTests, GetsExtendedSongTitleProperly)
{
    std::memcpy(tag->Data()->Data(), testTextData, Spc::id666TagSize);
    tag->ExtendedData()->songName = std::make_shared<Spc::ID666ExtendedItem>();
    tag->ExtendedData()->songName->id->SetValue(Spc::extendedSongNameID);
    tag->ExtendedData()->songName->type->SetValue(Spc::extendedTypeString);
    auto extendedSongTile = std::make_shared<Spc::TextField>(
        "Test Song Title ABCDEFGHIJKLMNOP Extended", 
        Spc::extendedTagOffset, 
        42);
    tag->ExtendedData()->songName->data = std::make_shared<Spc::NumericField>(
        "Data", 
        0, 
        42);
    tag->ExtendedData()->songName->extendedData = extendedSongTile;

    EXPECT_EQ("Song Title", tag->SongTitle().Label());
    EXPECT_EQ(Spc::extendedTagOffset, tag->SongTitle().Offset());
    EXPECT_EQ(42, tag->SongTitle().Size());
    EXPECT_EQ(extendedSongTile->Value(), tag->SongTitle().Value());
}

// --- GameTitle tests ---

TEST_F(ID666TagTests, GetsTextGameTitleProperly)
{
    std::memcpy(tag->Data()->Data(), testTextData, Spc::id666TagSize);

    EXPECT_EQ("Game Title", tag->GameTitle().Label());
    EXPECT_EQ(Spc::gameTitleInfo.textOffset, tag->GameTitle().Offset());
    EXPECT_EQ(Spc::gameTitleInfo.textSize, tag->GameTitle().Size());
    EXPECT_EQ("Test Game Title 1234567890XYZQRS", tag->GameTitle().Value());
}

TEST_F(ID666TagTests, GetsBinaryGameTitleProperly)
{
    std::memcpy(tag->Data()->Data(), testBinaryData, Spc::id666TagSize);

    EXPECT_EQ("Game Title", tag->GameTitle().Label());
    EXPECT_EQ(Spc::gameTitleInfo.binaryOffset, tag->GameTitle().Offset());
    EXPECT_EQ(Spc::gameTitleInfo.binarySize, tag->GameTitle().Size());
    EXPECT_EQ("Test Game Title 1234567890XYZQRS", tag->GameTitle().Value());
}

TEST_F(ID666TagTests, GetsMixedGameTitleProperly)
{
    std::memcpy(tag->Data()->Data(), testMixedData, Spc::id666TagSize);

    EXPECT_EQ("Game Title", tag->GameTitle().Label());
    EXPECT_EQ(Spc::gameTitleInfo.textOffset, tag->GameTitle().Offset());
    EXPECT_EQ(Spc::gameTitleInfo.textSize, tag->GameTitle().Size());
    EXPECT_EQ("Test Game Title 1234567890XYZQRS", tag->GameTitle().Value());
}

TEST_F(ID666TagTests, GetsExtendedGameTitleProperly)
{
    std::memcpy(tag->Data()->Data(), testTextData, Spc::id666TagSize);
    tag->ExtendedData()->gameName = std::make_shared<Spc::ID666ExtendedItem>();
    tag->ExtendedData()->gameName->id->SetValue(Spc::extendedGameNameID);
    tag->ExtendedData()->gameName->type->SetValue(Spc::extendedTypeString);
    auto extendedGameTitle = std::make_shared<Spc::TextField>(
        "Test Game Title 1234567890XYZQRS Extended",
        Spc::extendedTagOffset,
        40);
    tag->ExtendedData()->gameName->data = std::make_shared<Spc::NumericField>(
        "Data",
        0,
        40);
    tag->ExtendedData()->gameName->extendedData = extendedGameTitle;   
    EXPECT_EQ("Game Title", tag->GameTitle().Label());
    EXPECT_EQ(Spc::extendedTagOffset, tag->GameTitle().Offset());
    EXPECT_EQ(40, tag->GameTitle().Size());
    EXPECT_EQ(extendedGameTitle->Value(), tag->GameTitle().Value());
}

// --- Dumper tests ---

TEST_F(ID666TagTests, GetsTextDumperNameProperly)
{
    std::memcpy(tag->Data()->Data(), testTextData, Spc::id666TagSize);

    EXPECT_EQ("Dumper Name", tag->DumperName().Label());
    EXPECT_EQ(Spc::dumperNameInfo.textOffset, tag->DumperName().Offset());
    EXPECT_EQ(Spc::dumperNameInfo.textSize, tag->DumperName().Size());
    EXPECT_EQ("DumperName123456", tag->DumperName().Value());
}

TEST_F(ID666TagTests, GetsBinaryDumperNameProperly)
{
    std::memcpy(tag->Data()->Data(), testBinaryData, Spc::id666TagSize);

    EXPECT_EQ("Dumper Name", tag->DumperName().Label());
    EXPECT_EQ(Spc::dumperNameInfo.binaryOffset, tag->DumperName().Offset());
    EXPECT_EQ(Spc::dumperNameInfo.binarySize, tag->DumperName().Size());
    EXPECT_EQ("DumperName123456", tag->DumperName().Value());
}

TEST_F(ID666TagTests, GetsMixedDumperNameProperly)
{
    std::memcpy(tag->Data()->Data(), testMixedData, Spc::id666TagSize);

    EXPECT_EQ("Dumper Name", tag->DumperName().Label());
    EXPECT_EQ(Spc::dumperNameInfo.textOffset, tag->DumperName().Offset());
    EXPECT_EQ(Spc::dumperNameInfo.textSize, tag->DumperName().Size());
    EXPECT_EQ("DumperName123456", tag->DumperName().Value());
}

TEST_F(ID666TagTests, GetsExtendedDumperProperly)
{
    std::memcpy(tag->Data()->Data(), testTextData, Spc::id666TagSize);
    tag->ExtendedData()->dumperName = std::make_shared<Spc::ID666ExtendedItem>();
    tag->ExtendedData()->dumperName->id->SetValue(Spc::extendedDumperNameID);
    tag->ExtendedData()->dumperName->type->SetValue(Spc::extendedTypeString);
    auto extendedDumperName = std::make_shared<Spc::TextField>(
        "DumperName123456 Extended",
        Spc::extendedTagOffset,
        24);
    tag->ExtendedData()->dumperName->data = std::make_shared<Spc::NumericField>(
        "Data",
        0,
        24);
    tag->ExtendedData()->dumperName->extendedData = extendedDumperName;

    EXPECT_EQ("Dumper Name", tag->DumperName().Label());
    EXPECT_EQ(Spc::extendedTagOffset, tag->DumperName().Offset());
    EXPECT_EQ(24, tag->DumperName().Size());
    EXPECT_EQ(extendedDumperName->Value(), tag->DumperName().Value());
}

// --- Comments tests ---

TEST_F(ID666TagTests, GetsTextCommentsProperly)
{
    std::memcpy(tag->Data()->Data(), testTextData, Spc::id666TagSize);

    EXPECT_EQ("Comments", tag->Comments().Label());
    EXPECT_EQ(Spc::commentsInfo.textOffset, tag->Comments().Offset());
    EXPECT_EQ(Spc::commentsInfo.textSize, tag->Comments().Size());
    EXPECT_EQ("Test Comments ABCDEFGHIJKLMNOPQR", tag->Comments().Value());
}

TEST_F(ID666TagTests, GetsBinaryCommentsProperly)
{
    std::memcpy(tag->Data()->Data(), testBinaryData, Spc::id666TagSize);

    EXPECT_EQ("Comments", tag->Comments().Label());
    EXPECT_EQ(Spc::commentsInfo.binaryOffset, tag->Comments().Offset());
    EXPECT_EQ(Spc::commentsInfo.binarySize, tag->Comments().Size());
    EXPECT_EQ("Test Comments ABCDEFGHIJKLMNOPQR", tag->Comments().Value());
}

TEST_F(ID666TagTests, GetsMixedCommentsProperly)
{
    std::memcpy(tag->Data()->Data(), testMixedData, Spc::id666TagSize);

    EXPECT_EQ("Comments", tag->Comments().Label());
    EXPECT_EQ(Spc::commentsInfo.textOffset, tag->Comments().Offset());
    EXPECT_EQ(Spc::commentsInfo.textSize, tag->Comments().Size());
    EXPECT_EQ("Test Comments ABCDEFGHIJKLMNOPQR", tag->Comments().Value());
}

TEST_F(ID666TagTests, GetsExtendedCommentsProperly)
{
    std::memcpy(tag->Data()->Data(), testTextData, Spc::id666TagSize);
    tag->ExtendedData()->comments = std::make_shared<Spc::ID666ExtendedItem>();
    tag->ExtendedData()->comments->id->SetValue(Spc::extendedCommentsID);
    tag->ExtendedData()->comments->type->SetValue(Spc::extendedTypeString);
    auto extendedComments = std::make_shared<Spc::TextField>(
        "Test Comments ABCDEFGHIJKLMNOPQR Extended",
        Spc::extendedTagOffset,
        48);
    tag->ExtendedData()->comments->data = std::make_shared<Spc::NumericField>(
        "Data",
        0,
        48);
    tag->ExtendedData()->comments->extendedData = extendedComments;

    EXPECT_EQ("Comments", tag->Comments().Label());
    EXPECT_EQ(Spc::extendedTagOffset, tag->Comments().Offset());
    EXPECT_EQ(48, tag->Comments().Size());
    EXPECT_EQ(extendedComments->Value(), tag->Comments().Value());
}