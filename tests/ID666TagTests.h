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
#include <LibCppSpc.h>

template<typename T>
struct TestGetParams
{
    const char* testData;
    std::string expectedLabel;
    std::string expectedValue;
    size_t expectedOffset;
    size_t expectedSize;
    T (Spc::Id666::Tag::*getMethodPtr)() const;
};

struct TestFieldWithoutGetParams
{
    size_t offset;
    size_t size;
    std::string expectedValue;
};

template<typename T>
struct TestGetExtendedParams
{
    std::string expectedLabel;
    std::string expectedValue;
    size_t expectedSize;
    int extendedID;
    int extendedType;
    std::string extendedValue;
    std::shared_ptr<Spc::Id666::Extended::Item> item;
    T (Spc::Id666::Tag::*getMethodPtr)() const;
};

template<typename T>
struct TestSetParams
{
    const char* testData;
    size_t offset;
    size_t size;
    std::string setValue;
    void (Spc::Id666::Tag::*setMethodPtr)(std::string value);
};

template<typename T>
struct TestSetExtendedParams
{
    int extendedID;
    int extendedType;
    std::string setValue;
    std::string expectedValue;
    std::shared_ptr<Spc::Id666::Extended::Item>* itemPtrPtr;
    void (Spc::Id666::Tag::*setMethodPtr)(std::string value);
};

class ID666TagTests : public ::testing::Test 
{
protected:
    void SetUp() override;

    template<typename T>
    void TestGet(TestGetParams<T> params)
    {
        ASSERT_NE(tag, nullptr);
        ASSERT_NE(tag->FieldData(), nullptr);
        ASSERT_NE(tag->FieldData()->RawData(), nullptr);
        ASSERT_GE(tag->FieldData()->Size(), Spc::Id666::tagSize);
        std::memcpy(tag->FieldData()->RawData(), 
                    params.testData, 
                    Spc::Id666::tagSize);
        T field = (tag.get()->*params.getMethodPtr)();

        EXPECT_EQ(params.expectedLabel, field.Label());
        EXPECT_EQ(params.expectedOffset, field.Offset());
        EXPECT_EQ(params.expectedSize, field.Size());
        EXPECT_EQ(params.expectedValue, field.ToString());
    }

    template<typename T>
    std::shared_ptr<Spc::Id666::Extended::Item> InitExtendedItem(
        Spc::Id666::Extended::FieldInfo extendedInfo, 
        std::string setValue)
    {
        auto item = std::make_shared<Spc::Id666::Extended::Item>();
        item->id->SetInt32(extendedInfo.id);
        item->type->SetInt32(extendedInfo.type);
        std::shared_ptr<Spc::NumericField> itemData = item->data;
        itemData->SetInt32(setValue.size());

        auto itemExtData = std::make_shared<T>(
            "Test", 
            Spc::Id666::Extended::dataOffset, 
            setValue.size());
        itemExtData->SetValue(setValue);
        item->extendedData = itemExtData;

        return item;
    }

    template<typename T>
    std::shared_ptr<Spc::Id666::Extended::Item> InitNumericExtendedItem(
        Spc::Id666::Extended::FieldInfo extendedInfo, 
        std::string setValue)
    {
        auto item = std::make_shared<Spc::Id666::Extended::Item>();
        item->id->SetInt32(extendedInfo.id);
        item->type->SetInt32(extendedInfo.type);
        std::shared_ptr<Spc::NumericField> itemData = item->data;

        if (extendedInfo.type == Spc::Id666::Extended::integerType)
        {
            itemData->SetInt32(Spc::Id666::Extended::integerSize);
        }
        else
        {
            itemData->SetType(Spc::NumericType::Binary);
            itemData->SetValue(setValue);
        }

        if (extendedInfo.type != Spc::Id666::Extended::lengthType)
        {
            auto itemExtData = std::make_shared<T>(
                "Test", 
                Spc::Id666::Extended::dataOffset, 
                setValue.size());
            itemExtData->SetType(Spc::NumericType::Binary);
            itemExtData->SetValue(setValue);
            item->extendedData = itemExtData;
        }

        return item;
    }

    template<typename T, typename U>
    void TestGetExtended(TestGetExtendedParams<T> params)
    {
        auto extData = tag->ExtendedData();
        size_t offset = Spc::Id666::Extended::dataOffset;

        size_t size = params.item->data->Size();
        params.item->id->SetInt32(params.extendedID);
        params.item->type->SetInt32(params.extendedType);
    
        auto itemData = std::make_shared<U>(
            params.expectedLabel, 
            offset, 
            size);
        itemData->SetType(Spc::NumericType::Binary);
        itemData->SetValue(params.extendedValue);
        std::memcpy(params.item->data->RawData(), 
                    itemData->RawData(), 
                    itemData->Size());

        TestGetParams<T> getParams;
        getParams.testData = textData;
        getParams.expectedLabel = params.expectedLabel;
        getParams.expectedValue = params.expectedValue;
        getParams.expectedOffset = offset;
        getParams.expectedSize = params.expectedSize;
        getParams.getMethodPtr = params.getMethodPtr;
        TestGet<T>(getParams);
    }

    template<typename T, typename U>
    void TestGetExtendedData(TestGetExtendedParams<T> params)
    {
        auto extData = tag->ExtendedData();
        size_t offset = Spc::Id666::Extended::dataOffset;

        size_t size;
            
        if (params.extendedType == Spc::Id666::Extended::stringType)
            size = params.extendedValue.size();
        else
            size = 4; // 32-bit integer

        //size_t offset = Spc::Id666::Extended::dataOffset;

        auto itemExtData = std::make_shared<U>(params.expectedLabel, 
                                               offset, 
                                               size);

        // We need to ensure the data type is correct for integer types.
        if (params.extendedType == Spc::Id666::Extended::integerType)
        {
            auto numericExtData = 
                std::reinterpret_pointer_cast<Spc::NumericField>(
                    itemExtData);
            numericExtData->SetType(Spc::NumericType::Binary);
        }

        itemExtData->SetValue(params.extendedValue);
        params.item->id->SetInt32(params.extendedID);
        params.item->type->SetInt32(params.extendedType);
        auto itemData = std::static_pointer_cast<Spc::NumericField>
            (params.item->data);
        itemData->SetInt32(static_cast<int>(size));

        params.item->extendedData = itemExtData;

        TestGetParams<T> getParams;
        getParams.testData = textData;
        getParams.expectedLabel = params.expectedLabel;
        getParams.expectedValue = params.expectedValue;
        getParams.expectedOffset = offset;
        getParams.expectedSize = params.expectedSize;
        getParams.getMethodPtr = params.getMethodPtr;
        TestGet<T>(getParams);
    }

    template<typename T>
    void TestSet(TestSetParams<T> params)
    {
        ASSERT_NE(tag, nullptr);
        ASSERT_NE(tag->FieldData(), nullptr);
        ASSERT_NE(tag->FieldData()->RawData(), nullptr);
        ASSERT_GE(tag->FieldData()->Size(), Spc::Id666::tagSize);
        std::memcpy(tag->FieldData()->RawData(), 
                    params.testData, 
                    Spc::Id666::tagSize);
        (tag.get()->*params.setMethodPtr)(params.setValue);

        T field{ "Test Field", params.offset, params.size };
        tag->FieldData()->SetPosition(params.offset - Spc::Id666::tagOffset);
        tag->FieldData()->Read(&field);

        EXPECT_EQ(params.setValue, field.ToString());
    }

    template<typename T, typename U>
    void TestSetExtended(TestSetExtendedParams<T> params)
    {
        auto extData = tag->ExtendedData();
        size_t offset = Spc::Id666::Extended::dataOffset;

        (tag.get()->*params.setMethodPtr)(params.setValue);
        std::shared_ptr<Spc::Id666::Extended::Item> item = *(params.itemPtrPtr);
        ASSERT_NE(item, nullptr);

        //auto itemData = std::static_pointer_cast<U>(item->data);
        auto itemData = std::make_shared<U>(
            "Test", 
            offset, 
            Spc::Id666::Extended::dataSize);
        std::memcpy(itemData->RawData(), 
                    item->data->RawData(), 
                    item->data->Size());

        EXPECT_EQ(item->id->ToInt32(), params.extendedID);
        EXPECT_EQ(item->type->ToInt32(), params.extendedType);
        EXPECT_EQ(params.expectedValue, itemData->ToString());
    }

    template<typename T, typename U>
    void TestSetExtendedData(TestSetExtendedParams<T> params)
    {
        auto extData = tag->ExtendedData();
        size_t offset = Spc::Id666::Extended::dataOffset;

        (tag.get()->*params.setMethodPtr)(params.setValue);
        std::shared_ptr<Spc::Id666::Extended::Item> item = *(params.itemPtrPtr);
        ASSERT_NE(item, nullptr);
        ASSERT_NE(item->extendedData, nullptr);
        
        // When the data is not in the header, then item-data contains the
        // extended data size. Ensure it matches the size of the extended
        // data before proceeding with any additional checks as we don't
        // want any buffer overflows.
        auto extendedDataSize = std::static_pointer_cast<Spc::NumericField>(
            item->data);
        ASSERT_EQ(extendedDataSize->ToInt32(), item->extendedData->Size());

        EXPECT_EQ(item->id->ToInt32(), params.extendedID);
        EXPECT_EQ(item->type->ToInt32(), params.extendedType); 
        EXPECT_EQ(params.expectedValue, item->extendedData->ToString());
    }

    /*
    template<typename T, typename U>
    void TestSetExtended(TestSetExtendedParams<T> params)
    {
        auto extData = tag->ExtendedData();
        size_t offset = Spc::Id666::Extended::dataOffset;

        (tag.get()->*params.setMethodPtr)(params.setValue);
        std::shared_ptr<Spc::Id666::Extended::Item> item = *(params.itemPtrPtr);
        ASSERT_NE(item, nullptr);

        if (params.extendedType == Spc::Id666::Extended::lengthType)
        {
            //auto itemData = std::static_pointer_cast<U>(item->data);
            auto itemData = std::make_shared<U>(
                "Test", 
                offset, 
                Spc::Id666::Extended::dataSize);
            std::memcpy(itemData->RawData(), 
                        item->data->RawData(), 
                        item->data->Size());

            EXPECT_EQ(item->id->ToInt32(), params.extendedID);
            EXPECT_EQ(item->type->ToInt32(), params.extendedType);
            EXPECT_EQ(params.setValue, itemData->ToString());
        }
        else
        {
            // When the data is not in the header, then item-data contains the
            // extended data size. Ensure it matches the size of the extended
            // data before proceeding with any additional checks as we don't
            // want any buffer overflows.
            auto extendedDataSize = std::static_pointer_cast<Spc::NumericField>(
                item->data);
            ASSERT_EQ(extendedDataSize->ToInt32(), item->extendedData->Size());

            EXPECT_EQ(item->id->ToInt32(), params.extendedID);
            EXPECT_EQ(item->type->ToInt32(), params.extendedType); 
            EXPECT_EQ(params.setValue, item->extendedData->ToString());
        }
    }
    */

    template<typename T>
    void TestFieldsWithoutGet(TestFieldWithoutGetParams params)
    {
        ASSERT_NE(tag, nullptr);
        ASSERT_NE(tag->FieldData(), nullptr);
        ASSERT_NE(tag->FieldData()->RawData(), nullptr);
        ASSERT_GE(tag->FieldData()->Size(), Spc::Id666::tagSize);
          
        std::shared_ptr<Binary::BufferStream> fieldData = tag->FieldData();            

        T field{ "Test Field", params.offset, params.size };
        size_t position = fieldData->Position();
        fieldData->SetPosition(params.offset - Spc::Id666::tagOffset);
        fieldData->Read(&field);

        EXPECT_EQ(params.expectedValue, field.ToString());
    }

    std::unique_ptr<Spc::Id666::Tag> tag;
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
