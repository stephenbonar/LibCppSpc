// ID666ExtendedDataTests.cpp - Defines the ID666ExtendedDataTests class and tests.
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
    data->SetInt32(value.size());

    // Create the extended data field as a TextField since it should be string.
    auto extendedData = std::make_shared<Spc::TextField>("ExtendedData", 
                                                         0, 
                                                         value.size());

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

        item->padding = std::make_shared<Spc::TextField>(
            "Padding", 0, sizeWithPadding - value.size());
    }
}

TEST_F(ID666ExtendedDataTests, HeaderReturnsCorrectId)
{
    Binary::ChunkHeader header = data.Header();

    EXPECT_EQ(header.id.Value(), "xid6");
}

TEST_F(ID666ExtendedDataTests, HeaderDataSizeMatchesTagSize)
{
    // Initalize song title properly to ensure Size() is non-zero.
    InitStringItem(data.songTitle, "TST ");

    Binary::ChunkHeader header = data.Header();
    
    EXPECT_EQ(header.dataSize.Value(), data.Size());
}

TEST_F(ID666ExtendedDataTests, EnsureSpcFieldsReturnTagItemFieldsInCorrectOrder)
{
    // Here we're not initalizing these realistically, just ensuring the fields
    // are returned in the correct order.
    data.songTitle = std::make_shared<Spc::Id666::Extended::Item>();
    data.gameTitle = std::make_shared<Spc::Id666::Extended::Item>();
    data.songArtist = std::make_shared<Spc::Id666::Extended::Item>();
    data.dumperName = std::make_shared<Spc::Id666::Extended::Item>();
    data.dateDumped = std::make_shared<Spc::Id666::Extended::Item>();
    data.emulatorUsed = std::make_shared<Spc::Id666::Extended::Item>();
    data.comments = std::make_shared<Spc::Id666::Extended::Item>();
    data.ostTitle = std::make_shared<Spc::Id666::Extended::Item>();
    data.ostDisc = std::make_shared<Spc::Id666::Extended::Item>();
    data.ostTrack = std::make_shared<Spc::Id666::Extended::Item>();
    data.publisherName = std::make_shared<Spc::Id666::Extended::Item>();
    data.copyrightYear = std::make_shared<Spc::Id666::Extended::Item>();
    data.introLength = std::make_shared<Spc::Id666::Extended::Item>();
    data.loopLength = std::make_shared<Spc::Id666::Extended::Item>();
    data.endLength = std::make_shared<Spc::Id666::Extended::Item>();
    data.fadeLength = std::make_shared<Spc::Id666::Extended::Item>();
    data.mutedVoices = std::make_shared<Spc::Id666::Extended::Item>();
    data.loopTimes = std::make_shared<Spc::Id666::Extended::Item>();
    data.preampLevel = std::make_shared<Spc::Id666::Extended::Item>();

    std::vector<Spc::Field*> fields = data.SpcFields();

    // Each ID666ExtendedItem has 3 fields: id, type, data by default. There will
    // be more for those that have extendedData and padding, but we're not
    // testing that here as all were initalized without them.
    ASSERT_EQ(fields.size(), 19 * 3);

    std::vector<std::shared_ptr<Spc::Id666::Extended::Item>> items = 
    {
        data.songTitle,
        data.gameTitle,
        data.songArtist,
        data.dumperName,
        data.dateDumped,
        data.emulatorUsed,
        data.comments,
        data.ostTitle,
        data.ostDisc,
        data.ostTrack,
        data.publisherName,
        data.copyrightYear,
        data.introLength,
        data.loopLength,
        data.endLength,
        data.fadeLength,
        data.mutedVoices,
        data.loopTimes,
        data.preampLevel
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
    InitStringItem(data.songTitle, "TST ");
    InitStringItem(data.gameTitle, "TEST ");

    std::vector<Spc::Field*> fields = data.SpcFields();

    ASSERT_EQ(fields.size(), 9);
    EXPECT_EQ(fields[0], data.songTitle->id.get());
    EXPECT_EQ(fields[1], data.songTitle->type.get());
    EXPECT_EQ(fields[2], data.songTitle->data.get());
    EXPECT_EQ(fields[3], data.songTitle->extendedData.get());
    EXPECT_EQ(fields[4], data.gameTitle->id.get());
    EXPECT_EQ(fields[5], data.gameTitle->type.get());
    EXPECT_EQ(fields[6], data.gameTitle->data.get());
    EXPECT_EQ(fields[7], data.gameTitle->extendedData.get());
    EXPECT_EQ(fields[8], data.gameTitle->padding.get());
}
