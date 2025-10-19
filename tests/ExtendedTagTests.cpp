// ExtendedTagTests.cpp - Defines the ExtendedTagTests class and tests.
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

#include "ExtendedTagTests.h"

void ExtendedTagTests::InitStringItem(
    std::shared_ptr<Spc::ExtendedTagItem>& item, 
    std::string value)
{
    // Create the song name item to ensure Size() is non-zero.
    item = std::make_shared<Spc::ExtendedTagItem>();
    item->id->SetValue(extendedSongNameID);
    item->type->SetValue(extendedTypeString);

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

TEST_F(ExtendedTagTests, HeaderReturnsCorrectId)
{
    Binary::ChunkHeader header = extendedTag.Header();

    EXPECT_EQ(header.id.Value(), "xid6");
}

TEST_F(ExtendedTagTests, HeaderDataSizeMatchesTagSize)
{
    // Initalize song name properly to ensure Size() is non-zero.
    InitStringItem(extendedTag.songName, "TST ");

    Binary::ChunkHeader header = extendedTag.Header();
    
    EXPECT_EQ(header.dataSize.Value(), extendedTag.Size());
}

TEST_F(ExtendedTagTests, EnsureSpcFieldsReturnTagItemFieldsInCorrectOrder)
{
    // Here we're not initalizing these realistically, just ensuring the fields
    // are returned in the correct order.
    extendedTag.songName = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.gameName = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.artistName = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.dumperName = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.dateDumped = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.emulatorUsed = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.comments = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.ostTitle = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.ostDisc = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.ostTrack = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.publisherName = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.copyrightYear = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.introLength = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.loopLength = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.endLength = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.fadeLength = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.mutedVoices = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.loopTimes = std::make_shared<Spc::ExtendedTagItem>();
    extendedTag.preampLevel = std::make_shared<Spc::ExtendedTagItem>();

    std::vector<Spc::Field*> fields = extendedTag.SpcFields();

    // Each ExtendedTagItem has 3 fields: id, type, data by default. There will
    // be more for those that have extendedData and padding, but we're not
    // testing that here as all were initalized without them.
    ASSERT_EQ(fields.size(), 19 * 3);

    std::vector<std::shared_ptr<Spc::ExtendedTagItem>> items = 
    {
        extendedTag.songName,
        extendedTag.gameName,
        extendedTag.artistName,
        extendedTag.dumperName,
        extendedTag.dateDumped,
        extendedTag.emulatorUsed,
        extendedTag.comments,
        extendedTag.ostTitle,
        extendedTag.ostDisc,
        extendedTag.ostTrack,
        extendedTag.publisherName,
        extendedTag.copyrightYear,
        extendedTag.introLength,
        extendedTag.loopLength,
        extendedTag.endLength,
        extendedTag.fadeLength,
        extendedTag.mutedVoices,
        extendedTag.loopTimes,
        extendedTag.preampLevel
    };

    for (size_t i = 0; i < items.size(); ++i) 
    {
        EXPECT_EQ(fields[i * 3 + 0], items[i]->id.get());
        EXPECT_EQ(fields[i * 3 + 1], items[i]->type.get());
        EXPECT_EQ(fields[i * 3 + 2], items[i]->data.get());
    }
}

TEST_F(ExtendedTagTests, EnsureOnlyInitializedTagItemsFieldsAreReturned)
{
    InitStringItem(extendedTag.songName, "TST ");
    InitStringItem(extendedTag.gameName, "TEST ");

    std::vector<Spc::Field*> fields = extendedTag.SpcFields();

    ASSERT_EQ(fields.size(), 9);
    EXPECT_EQ(fields[0], extendedTag.songName->id.get());
    EXPECT_EQ(fields[1], extendedTag.songName->type.get());
    EXPECT_EQ(fields[2], extendedTag.songName->data.get());
    EXPECT_EQ(fields[3], extendedTag.songName->extendedData.get());
    EXPECT_EQ(fields[4], extendedTag.gameName->id.get());
    EXPECT_EQ(fields[5], extendedTag.gameName->type.get());
    EXPECT_EQ(fields[6], extendedTag.gameName->data.get());
    EXPECT_EQ(fields[7], extendedTag.gameName->extendedData.get());
    EXPECT_EQ(fields[8], extendedTag.gameName->padding.get());
}
