// ID666TagTests.h - Declares the ID666TagTests class and tests.
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

#ifndef ID666_TAG_TESTS_H
#define ID666_TAG_TESTS_H

#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "ID666Tag.h"

template<typename T>
struct TestGetParameters
{
    const char* testData;
    std::string expectedLabel;
    std::string expectedValue;
    size_t expectedOffset;
    size_t expectedSize;
    T (Spc::ID666Tag::*getMethodPtr)() const;
};

template<typename T>
struct TestGetWithExtendedItemParameters
{
    std::string expectedLabel;
    std::string expectedValue;
    size_t expectedSize;
    int extendedID;
    int extendedType;
    std::string extendedValue;
    std::shared_ptr<Spc::ID666ExtendedItem> item;
    T (Spc::ID666Tag::*getMethodPtr)() const;
};

class ID666TagTests : public ::testing::Test 
{
protected:
    void SetUp() override;

    template<typename T>
    void TestGet(TestGetParameters<T> params)
    {
        ASSERT_NE(tag, nullptr);
        ASSERT_NE(tag->FieldData(), nullptr);
        ASSERT_NE(tag->FieldData()->RawData(), nullptr);
        ASSERT_GE(tag->FieldData()->Size(), Spc::id666TagSize);
        std::memcpy(tag->FieldData()->RawData(), 
                    params.testData, 
                    Spc::id666TagSize);
        T field = (tag.get()->*params.getMethodPtr)();

        EXPECT_EQ(params.expectedLabel, field.Label());
        EXPECT_EQ(params.expectedOffset, field.Offset());
        EXPECT_EQ(params.expectedSize, field.Size());
        EXPECT_EQ(params.expectedValue, field.ToString());
    }

    template<typename T, typename U>
    void TestGetWithExtendedItem(TestGetWithExtendedItemParameters<T> params)
    {
        auto extData = tag->ExtendedData();
        size_t offset = Spc::extendedTagOffset;

        if (params.extendedType == Spc::extendedTypeDataInHeader)
        {
            size_t size = params.item->data->Size();
            params.item->id->SetValue(params.extendedID);
            params.item->type->SetValue(params.extendedType);
        
            auto itemData = std::static_pointer_cast<Spc::NumericField>(
                params.item->data);
            itemData->SetLabel(params.expectedLabel);
            itemData->SetValue(params.extendedValue);

            TestGetParameters<T> getParams;
            getParams.testData = textData;
            getParams.expectedLabel = params.expectedLabel;
            getParams.expectedValue = itemData->ToString();
            getParams.expectedOffset = offset;
            getParams.expectedSize = size;
            getParams.getMethodPtr = params.getMethodPtr;
            TestGet<T>(getParams);
        }
        else
        {
            size_t size;
            
            if (params.extendedType == Spc::extendedTypeString)
                size = params.extendedValue.size();
            else
                size = 4; // 32-bit integer

            size_t offset = Spc::extendedTagOffset;

            auto itemExtData = std::make_shared<U>(params.expectedLabel, 
                                                   offset, 
                                                   size);
            itemExtData->SetValue(params.extendedValue);
            params.item->id->SetValue(params.extendedID);
            params.item->type->SetValue(params.extendedType);
            auto itemData = std::static_pointer_cast<Spc::NumericField>
                (params.item->data);
            itemData->SetValue(static_cast<int>(size));

            params.item->extendedData = itemExtData;

            TestGetParameters<T> getParams;
            getParams.testData = textData;
            getParams.expectedLabel = params.expectedLabel;
            getParams.expectedValue = itemExtData->ToString();
            getParams.expectedOffset = offset;
            getParams.expectedSize = params.expectedSize;
            getParams.getMethodPtr = params.getMethodPtr;
            TestGet<T>(getParams);
        }
    }

    std::unique_ptr<Spc::ID666Tag> tag;
    const char* textData;
    const char* binaryData;
    const char* mixedData;
    std::string expectedSongTitle{ "Test Song Title ABCDEFGHIJKLMNOP" };
    std::string expectedGameTitle{ "Test Game Title 1234567890XYZQRS" };
    std::string expectedDumperName{ "DumperName123456" };
    std::string expectedComments{ "Test Comments ABCDEFGHIJKLMNOPQR" };
    std::string expectedDateDumped{ "02/06/2000" };
    std::string expectedSongArtist{ "Artist Name Test ABCDEFGHIJKLMNO" };
};

#endif
