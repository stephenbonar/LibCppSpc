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

constexpr unsigned char rawBinaryData[] = {
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
    textData = reinterpret_cast<const char*>(rawTextData);
    binaryData = reinterpret_cast<const char*>(rawBinaryData);
    mixedData = reinterpret_cast<const char*>(rawMixedData);
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
    std::memcpy(tag->Data()->Data(), textData, Spc::id666TagSize);
    Spc::TextField songTitle = tag->SongTitle();

    EXPECT_EQ("Song Title", songTitle.Label());
    EXPECT_EQ(Spc::songTitleInfo.textOffset, songTitle.Offset());
    EXPECT_EQ(Spc::songTitleInfo.textSize, songTitle.Size());
    EXPECT_EQ("Test Song Title ABCDEFGHIJKLMNOP", songTitle.Value());
}

TEST_F(ID666TagTests, GetsBinarySongTitleProperly)
{
    std::memcpy(tag->Data()->Data(), binaryData, Spc::id666TagSize);
    Spc::TextField songTitle = tag->SongTitle();

    EXPECT_EQ("Song Title", songTitle.Label());
    EXPECT_EQ(Spc::songTitleInfo.binaryOffset, songTitle.Offset());
    EXPECT_EQ(Spc::songTitleInfo.binarySize, songTitle.Size());
    EXPECT_EQ("Test Song Title ABCDEFGHIJKLMNOP", songTitle.Value());
}

TEST_F(ID666TagTests, GetsMixedSongTitleProperly)
{
    std::memcpy(tag->Data()->Data(), mixedData, Spc::id666TagSize);
    Spc::TextField songTitle = tag->SongTitle();

    EXPECT_EQ("Song Title", songTitle.Label());
    EXPECT_EQ(Spc::songTitleInfo.textOffset, songTitle.Offset());
    EXPECT_EQ(Spc::songTitleInfo.textSize, songTitle.Size());
    EXPECT_EQ("Test Song Title ABCDEFGHIJKLMNOP", songTitle.Value());
}

TEST_F(ID666TagTests, GetsExtendedSongTitleProperly)
{
    std::memcpy(tag->Data()->Data(), textData, Spc::id666TagSize);
    std::shared_ptr<Spc::ID666ExtendedData> extData = tag->ExtendedData();

    auto itemExtData = std::make_shared<Spc::TextField>(
        "Test Song Title ABCDEFGHIJKLMNOP Extended", 
        Spc::extendedTagOffset, 
        42);
    auto item = std::make_shared<Spc::ID666ExtendedItem>();
    item->id->SetValue(Spc::extendedSongNameID);
    item->type->SetValue(Spc::extendedTypeString);
    item->data = std::make_shared<Spc::NumericField>("Data", 0, 42);
    item->extendedData = itemExtData;
    extData->songName = item;

    Spc::TextField songTitle = tag->SongTitle();

    EXPECT_EQ("Song Title", songTitle.Label());
    EXPECT_EQ(Spc::extendedTagOffset, songTitle.Offset());
    EXPECT_EQ(42, songTitle.Size());
    EXPECT_EQ(itemExtData->Value(), songTitle.Value());
}

// --- GameTitle tests ---

TEST_F(ID666TagTests, GetsTextGameTitleProperly)
{
    std::memcpy(tag->Data()->Data(), textData, Spc::id666TagSize);
    Spc::TextField gameTitle = tag->GameTitle();

    EXPECT_EQ("Game Title", gameTitle.Label());
    EXPECT_EQ(Spc::gameTitleInfo.textOffset, gameTitle.Offset());
    EXPECT_EQ(Spc::gameTitleInfo.textSize, gameTitle.Size());
    EXPECT_EQ("Test Game Title 1234567890XYZQRS", gameTitle.Value());
}

TEST_F(ID666TagTests, GetsBinaryGameTitleProperly)
{
    std::memcpy(tag->Data()->Data(), binaryData, Spc::id666TagSize);
    Spc::TextField gameTitle = tag->GameTitle();

    EXPECT_EQ("Game Title", gameTitle.Label());
    EXPECT_EQ(Spc::gameTitleInfo.binaryOffset, gameTitle.Offset());
    EXPECT_EQ(Spc::gameTitleInfo.binarySize, gameTitle.Size());
    EXPECT_EQ("Test Game Title 1234567890XYZQRS", gameTitle.Value());
}

TEST_F(ID666TagTests, GetsMixedGameTitleProperly)
{
    std::memcpy(tag->Data()->Data(), mixedData, Spc::id666TagSize);
    Spc::TextField gameTitle = tag->GameTitle();

    EXPECT_EQ("Game Title", gameTitle.Label());
    EXPECT_EQ(Spc::gameTitleInfo.textOffset, gameTitle.Offset());
    EXPECT_EQ(Spc::gameTitleInfo.textSize, gameTitle.Size());
    EXPECT_EQ("Test Game Title 1234567890XYZQRS", gameTitle.Value());
}

TEST_F(ID666TagTests, GetsExtendedGameTitleProperly)
{
    std::memcpy(tag->Data()->Data(), textData, Spc::id666TagSize);
    auto extData = tag->ExtendedData();

    auto itemExtData = std::make_shared<Spc::TextField>(
        "Test Game Title 1234567890XYZQRS Extended",
        Spc::extendedTagOffset,
        40);
    auto item = std::make_shared<Spc::ID666ExtendedItem>();
    item->id->SetValue(Spc::extendedGameNameID);
    item->type->SetValue(Spc::extendedTypeString);
    item->data = std::make_shared<Spc::NumericField>("Data", 0, 40);
    item->extendedData = itemExtData; 
    extData->gameName = item;

    Spc::TextField gameTitle = tag->GameTitle();

    EXPECT_EQ("Game Title", gameTitle.Label());
    EXPECT_EQ(Spc::extendedTagOffset, gameTitle.Offset());
    EXPECT_EQ(40, gameTitle.Size());
    EXPECT_EQ(itemExtData->Value(), gameTitle.Value());
}

// --- Dumper tests ---

TEST_F(ID666TagTests, GetsTextDumperNameProperly)
{
    std::memcpy(tag->Data()->Data(), textData, Spc::id666TagSize);
    Spc::TextField dumperName = tag->DumperName();

    EXPECT_EQ("Dumper Name", dumperName.Label());
    EXPECT_EQ(Spc::dumperNameInfo.textOffset, dumperName.Offset());
    EXPECT_EQ(Spc::dumperNameInfo.textSize, dumperName.Size());
    EXPECT_EQ("DumperName123456", dumperName.Value());
}

TEST_F(ID666TagTests, GetsBinaryDumperNameProperly)
{
    std::memcpy(tag->Data()->Data(), binaryData, Spc::id666TagSize);
    Spc::TextField dumperName = tag->DumperName();

    EXPECT_EQ("Dumper Name", dumperName.Label());
    EXPECT_EQ(Spc::dumperNameInfo.binaryOffset, dumperName.Offset());
    EXPECT_EQ(Spc::dumperNameInfo.binarySize, dumperName.Size());
    EXPECT_EQ("DumperName123456", dumperName.Value());
}

TEST_F(ID666TagTests, GetsMixedDumperNameProperly)
{
    std::memcpy(tag->Data()->Data(), mixedData, Spc::id666TagSize);
    Spc::TextField dumperName = tag->DumperName();

    EXPECT_EQ("Dumper Name", dumperName.Label());
    EXPECT_EQ(Spc::dumperNameInfo.textOffset, dumperName.Offset());
    EXPECT_EQ(Spc::dumperNameInfo.textSize, dumperName.Size());
    EXPECT_EQ("DumperName123456", dumperName.Value());
}

TEST_F(ID666TagTests, GetsExtendedDumperProperly)
{
    std::memcpy(tag->Data()->Data(), textData, Spc::id666TagSize);
    auto extData = tag->ExtendedData();

    auto itemExtData = std::make_shared<Spc::TextField>(
        "DumperName123456 Extended",
        Spc::extendedTagOffset,
        24);
    auto item = std::make_shared<Spc::ID666ExtendedItem>();
    item->id->SetValue(Spc::extendedDumperNameID);
    item->type->SetValue(Spc::extendedTypeString);
    item->data = std::make_shared<Spc::NumericField>("Data", 0, 24);
    item->extendedData = itemExtData;
    extData->dumperName = item;

    Spc::TextField dumperName = tag->DumperName();

    EXPECT_EQ("Dumper Name", dumperName.Label());
    EXPECT_EQ(Spc::extendedTagOffset, dumperName.Offset());
    EXPECT_EQ(24, dumperName.Size());
    EXPECT_EQ(itemExtData->Value(), dumperName.Value());
}

// --- Comments tests ---

TEST_F(ID666TagTests, GetsTextCommentsProperly)
{
    std::memcpy(tag->Data()->Data(), textData, Spc::id666TagSize);
    Spc::TextField comments = tag->Comments();

    EXPECT_EQ("Comments", comments.Label());
    EXPECT_EQ(Spc::commentsInfo.textOffset, comments.Offset());
    EXPECT_EQ(Spc::commentsInfo.textSize, comments.Size());
    EXPECT_EQ("Test Comments ABCDEFGHIJKLMNOPQR", comments.Value());
}

TEST_F(ID666TagTests, GetsBinaryCommentsProperly)
{
    std::memcpy(tag->Data()->Data(), binaryData, Spc::id666TagSize);
    Spc::TextField comments = tag->Comments();

    EXPECT_EQ("Comments", comments.Label());
    EXPECT_EQ(Spc::commentsInfo.binaryOffset, comments.Offset());
    EXPECT_EQ(Spc::commentsInfo.binarySize, comments.Size());
    EXPECT_EQ("Test Comments ABCDEFGHIJKLMNOPQR", comments.Value());
}

TEST_F(ID666TagTests, GetsMixedCommentsProperly)
{
    std::memcpy(tag->Data()->Data(), mixedData, Spc::id666TagSize);
    Spc::TextField comments = tag->Comments();

    EXPECT_EQ("Comments", comments.Label());
    EXPECT_EQ(Spc::commentsInfo.textOffset, comments.Offset());
    EXPECT_EQ(Spc::commentsInfo.textSize, comments.Size());
    EXPECT_EQ("Test Comments ABCDEFGHIJKLMNOPQR", comments.Value());
}

TEST_F(ID666TagTests, GetsExtendedCommentsProperly)
{
    std::memcpy(tag->Data()->Data(), textData, Spc::id666TagSize);
    auto extData = tag->ExtendedData();

    auto extItemData = std::make_shared<Spc::TextField>(
        "Test Comments ABCDEFGHIJKLMNOPQR Extended",
        Spc::extendedTagOffset,
        48);
    auto item = std::make_shared<Spc::ID666ExtendedItem>();
    item->id->SetValue(Spc::extendedCommentsID);
    item->type->SetValue(Spc::extendedTypeString);
    item->data = std::make_shared<Spc::NumericField>("Data", 0, 48);
    item->extendedData = extItemData;
    extData->comments = item;

    Spc::TextField tagComments = tag->Comments();

    EXPECT_EQ("Comments", tagComments.Label());
    EXPECT_EQ(Spc::extendedTagOffset, tagComments.Offset());
    EXPECT_EQ(48, tagComments.Size());
    EXPECT_EQ(extItemData->Value(), tagComments.Value());
}

// --- DateDumped tests ---

TEST_F(ID666TagTests, GetsTextDateDumpedProperly)
{
    std::memcpy(tag->Data()->Data(), textData, Spc::id666TagSize);
    Spc::DateField dateDumped = tag->DateDumped();

    EXPECT_EQ("Date Dumped", dateDumped.Label());
    EXPECT_EQ(Spc::dateDumpedInfo.textOffset, dateDumped.Offset());
    EXPECT_EQ(Spc::dateDumpedInfo.textSize, dateDumped.Size());
    EXPECT_EQ("01/23/2025", dateDumped.Value());
}

TEST_F(ID666TagTests, GetsBinaryDateDumpedProperly)
{
    std::memcpy(tag->Data()->Data(), binaryData, Spc::id666TagSize);
    Spc::DateField dateDumped = tag->DateDumped();

    EXPECT_EQ("Date Dumped", dateDumped.Label());
    EXPECT_EQ(Spc::dateDumpedInfo.binaryOffset, dateDumped.Offset());
    EXPECT_EQ(Spc::dateDumpedInfo.binarySize, dateDumped.Size());
    EXPECT_EQ("06/01/2024", dateDumped.Value());
}

TEST_F(ID666TagTests, GetsMixedDateDumpedProperly)
{
    std::memcpy(tag->Data()->Data(), mixedData, Spc::id666TagSize);
    Spc::DateField dateDumped = tag->DateDumped();

    EXPECT_EQ("Date Dumped", dateDumped.Label());
    EXPECT_EQ(Spc::dateDumpedInfo.textOffset, dateDumped.Offset());
    EXPECT_EQ(Spc::dateDumpedInfo.textSize, dateDumped.Size());
    EXPECT_EQ("01/23/2025", dateDumped.Value());
}

TEST_F(ID666TagTests, GetsExtendedDateDumpedProperly)
{
    std::memcpy(tag->Data()->Data(), textData, Spc::id666TagSize);
    auto extData = tag->ExtendedData();

    auto extItemData = std::make_shared<Spc::DateField>(
        "01/23/2025",
        Spc::extendedTagOffset,
        12);
    auto item = std::make_shared<Spc::ID666ExtendedItem>();
    item->id->SetValue(Spc::extendedDateDumpedID);
    item->type->SetValue(Spc::extendedTypeString);
    item->data = std::make_shared<Spc::NumericField>("Data", 0, 12);
    item->extendedData = extItemData;
    extData->dateDumped = item;

    Spc::DateField dateDumped = tag->DateDumped();

    EXPECT_EQ("Date Dumped", dateDumped.Label());
    EXPECT_EQ(Spc::extendedTagOffset, dateDumped.Offset());
    EXPECT_EQ(12, dateDumped.Size());
    EXPECT_EQ(extItemData->Value(), dateDumped.Value());
}