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
    std::shared_ptr<Spc::ID666ExtendedItem>& item, 
    std::string value)
{
    // Create the song name item to ensure Size() is non-zero.
    item = std::make_shared<Spc::ID666ExtendedItem>();
    item->id->SetValue(Spc::extendedSongNameID);
    item->type->SetValue(Spc::extendedTypeString);

    // Data is a pointer to the base class, so we need to cast it to 
    // NumericField since we know it is numeric when extended type is string.
    auto data = std::static_pointer_cast<Spc::NumericField>(
        item->data);

    // We're going to do a string that's 4 bytes long.
    data->SetValue(value.size());

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
    Binary::ChunkHeader header = id666ExtendedData.Header();

    EXPECT_EQ(header.id.Value(), "xid6");
}

TEST_F(ID666ExtendedDataTests, HeaderDataSizeMatchesTagSize)
{
    // Initalize song name properly to ensure Size() is non-zero.
    InitStringItem(id666ExtendedData.songName, "TST ");

    Binary::ChunkHeader header = id666ExtendedData.Header();
    
    EXPECT_EQ(header.dataSize.Value(), id666ExtendedData.Size());
}

TEST_F(ID666ExtendedDataTests, EnsureSpcFieldsReturnTagItemFieldsInCorrectOrder)
{
    // Here we're not initalizing these realistically, just ensuring the fields
    // are returned in the correct order.
    id666ExtendedData.songName = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.gameName = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.artistName = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.dumperName = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.dateDumped = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.emulatorUsed = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.comments = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.ostTitle = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.ostDisc = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.ostTrack = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.publisherName = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.copyrightYear = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.introLength = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.loopLength = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.endLength = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.fadeLength = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.mutedVoices = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.loopTimes = std::make_shared<Spc::ID666ExtendedItem>();
    id666ExtendedData.preampLevel = std::make_shared<Spc::ID666ExtendedItem>();

    std::vector<Spc::Field*> fields = id666ExtendedData.SpcFields();

    // Each ID666ExtendedItem has 3 fields: id, type, data by default. There will
    // be more for those that have extendedData and padding, but we're not
    // testing that here as all were initalized without them.
    ASSERT_EQ(fields.size(), 19 * 3);

    std::vector<std::shared_ptr<Spc::ID666ExtendedItem>> items = 
    {
        id666ExtendedData.songName,
        id666ExtendedData.gameName,
        id666ExtendedData.artistName,
        id666ExtendedData.dumperName,
        id666ExtendedData.dateDumped,
        id666ExtendedData.emulatorUsed,
        id666ExtendedData.comments,
        id666ExtendedData.ostTitle,
        id666ExtendedData.ostDisc,
        id666ExtendedData.ostTrack,
        id666ExtendedData.publisherName,
        id666ExtendedData.copyrightYear,
        id666ExtendedData.introLength,
        id666ExtendedData.loopLength,
        id666ExtendedData.endLength,
        id666ExtendedData.fadeLength,
        id666ExtendedData.mutedVoices,
        id666ExtendedData.loopTimes,
        id666ExtendedData.preampLevel
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
    InitStringItem(id666ExtendedData.songName, "TST ");
    InitStringItem(id666ExtendedData.gameName, "TEST ");

    std::vector<Spc::Field*> fields = id666ExtendedData.SpcFields();

    ASSERT_EQ(fields.size(), 9);
    EXPECT_EQ(fields[0], id666ExtendedData.songName->id.get());
    EXPECT_EQ(fields[1], id666ExtendedData.songName->type.get());
    EXPECT_EQ(fields[2], id666ExtendedData.songName->data.get());
    EXPECT_EQ(fields[3], id666ExtendedData.songName->extendedData.get());
    EXPECT_EQ(fields[4], id666ExtendedData.gameName->id.get());
    EXPECT_EQ(fields[5], id666ExtendedData.gameName->type.get());
    EXPECT_EQ(fields[6], id666ExtendedData.gameName->data.get());
    EXPECT_EQ(fields[7], id666ExtendedData.gameName->extendedData.get());
    EXPECT_EQ(fields[8], id666ExtendedData.gameName->padding.get());
}
