// ID666ExtendedDataTests.cpp - Defines the ID666ExtendedDataTests class and tests.
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

#include "ID666ExtendedDataTests.h"

void ID666ExtendedDataTests::InitStringItem(
    std::shared_ptr<Spc::Id666::Extended::Item>& item, 
    std::string value)
{
    // Create the song name item to ensure Size() is non-zero.
    item = std::make_shared<Spc::Id666::Extended::Item>();
    item->id->SetInt32(Spc::Id666::Extended::songTitleInfo.id);
    item->type->SetInt32(Spc::Id666::Extended::stringType);

    // Data is a pointer to the base class, so we need to cast it to 
    // NumericField since we know it is numeric when extended type is string.
    auto data = std::static_pointer_cast<Spc::NumericField>(
        item->data);

    // We're going to do a string that's 4 bytes long.
    data->SetUInt32(static_cast<uint32_t>(value.size()));

    // Create the extended data field as a TextField since it should be string.
    Spc::FieldInfo extendedInfo{ 0, value.size() };
    auto extendedData = std::make_shared<Spc::TextField>("ExtendedData", 
                                                         extendedInfo);

    // Assign the pointer to to the extended tag item.
    item->extendedData = extendedData;

    // But set the value using the extendedData variable as it is the correct
    // type whereas tag.songName->extendedData is a base class pointer.
    extendedData->SetValue("TST ");

    if (value.size() % 4 != 0)
    {
        size_t sizeWithPadding = value.size();

        while (sizeWithPadding % 4 != 0)
            ++sizeWithPadding;

        Spc::FieldInfo paddingInfo{ 0, sizeWithPadding - value.size() };
        item->padding = std::make_shared<Spc::TextField>("Padding", 
                                                         paddingInfo);
    }
}

TEST_F(ID666ExtendedDataTests, HeaderReturnsCorrectId)
{
    Binary::ChunkHeader header = testExtendedData.Header();

    EXPECT_EQ(header.id.Value(), "xid6");
}

TEST_F(ID666ExtendedDataTests, HeaderDataSizeMatchesTagSize)
{
    // Initalize song title properly to ensure Size() is non-zero.
    InitStringItem(testExtendedData.songTitle, "TST ");

    Binary::ChunkHeader header = testExtendedData.Header();
    
    EXPECT_EQ(header.dataSize.Value(), testExtendedData.Size());
}

TEST_F(ID666ExtendedDataTests, EnsureSpcFieldsReturnTagItemFieldsInCorrectOrder)
{
    // Here we're not initalizing these realistically, just ensuring the fields
    // are returned in the correct order.
    testExtendedData.songTitle = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.gameTitle = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.songArtist = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.dumperName = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.dateDumped = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.emulatorUsed = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.comments = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.ostTitle = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.ostDisc = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.ostTrack = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.publisherName = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.copyrightYear = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.introLength = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.loopLength = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.endLength = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.fadeLength = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.mutedVoices = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.loopTimes = std::make_shared<Spc::Id666::Extended::Item>();
    testExtendedData.preampLevel = std::make_shared<Spc::Id666::Extended::Item>();

    std::vector<Spc::Field*> fields = testExtendedData.SpcFields();

    // Each ID666ExtendedItem has 3 fields: id, type, data by default. There will
    // be more for those that have extendedData and padding, but we're not
    // testing that here as all were initalized without them.
    ASSERT_EQ(fields.size(), 19 * 3);

    std::vector<std::shared_ptr<Spc::Id666::Extended::Item>> items = 
    {
        testExtendedData.songTitle,
        testExtendedData.gameTitle,
        testExtendedData.songArtist,
        testExtendedData.dumperName,
        testExtendedData.dateDumped,
        testExtendedData.emulatorUsed,
        testExtendedData.comments,
        testExtendedData.ostTitle,
        testExtendedData.ostDisc,
        testExtendedData.ostTrack,
        testExtendedData.publisherName,
        testExtendedData.copyrightYear,
        testExtendedData.introLength,
        testExtendedData.loopLength,
        testExtendedData.endLength,
        testExtendedData.fadeLength,
        testExtendedData.mutedVoices,
        testExtendedData.loopTimes,
        testExtendedData.preampLevel
    };

    for (size_t i = 0; i < items.size(); ++i) 
    {
        EXPECT_EQ(fields[i * 3 + 0], items[i]->id.get());
        EXPECT_EQ(fields[i * 3 + 1], items[i]->type.get());
        EXPECT_EQ(fields[i * 3 + 2], items[i]->data.get());
    }
}

TEST_F(ID666ExtendedDataTests, EnsureOnlyInitializedTagItemsFieldsAreReturned)
{
    InitStringItem(testExtendedData.songTitle, "TST ");
    InitStringItem(testExtendedData.gameTitle, "TEST ");

    std::vector<Spc::Field*> fields = testExtendedData.SpcFields();

    ASSERT_EQ(fields.size(), 9);
    EXPECT_EQ(fields[0], testExtendedData.songTitle->id.get());
    EXPECT_EQ(fields[1], testExtendedData.songTitle->type.get());
    EXPECT_EQ(fields[2], testExtendedData.songTitle->data.get());
    EXPECT_EQ(fields[3], testExtendedData.songTitle->extendedData.get());
    EXPECT_EQ(fields[4], testExtendedData.gameTitle->id.get());
    EXPECT_EQ(fields[5], testExtendedData.gameTitle->type.get());
    EXPECT_EQ(fields[6], testExtendedData.gameTitle->data.get());
    EXPECT_EQ(fields[7], testExtendedData.gameTitle->extendedData.get());
    EXPECT_EQ(fields[8], testExtendedData.gameTitle->padding.get());
}
