// ID666TagTests.h - Declares the ID666TagTests class and tests.
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
    void TestNumericGet(TestGetParams<T> params, bool isText)
    {
        ASSERT_NE(tag, nullptr);
        ASSERT_NE(tag->FieldData(), nullptr);
        ASSERT_NE(tag->FieldData()->RawData(), nullptr);
        ASSERT_GE(tag->FieldData()->Size(), Spc::Id666::tagSize);
        std::memcpy(tag->FieldData()->RawData(), 
                    params.testData, 
                    Spc::Id666::tagSize);
        T field = (tag.get()->*params.getMethodPtr)();

        EXPECT_EQ(isText, field.IsText());
        EXPECT_EQ(params.expectedLabel, field.Label());
        EXPECT_EQ(params.expectedOffset, field.Offset());
        EXPECT_EQ(params.expectedSize, field.Size());
        EXPECT_EQ(params.expectedValue, field.ToString());
    }

    template<typename T>
    std::shared_ptr<Spc::Id666::Extended::Item> InitExtendedItem(
        Spc::Id666::Extended::ItemInfo extendedInfo, 
        std::string setValue)
    {
        auto item = std::make_shared<Spc::Id666::Extended::Item>();
        item->id->SetInt32(extendedInfo.id);
        item->type->SetInt32(extendedInfo.type);
        std::shared_ptr<Spc::NumericField> itemData = item->data;
        itemData->SetUInt32(static_cast<uint32_t>(setValue.size()));

        Spc::FieldInfo info{ Spc::Id666::Extended::dataOffset, 
                             setValue.size() };
        auto itemExtData = std::make_shared<T>("Test", info);
        itemExtData->SetValue(setValue);
        item->extendedData = itemExtData;

        return item;
    }

    template<typename T>
    std::shared_ptr<Spc::Id666::Extended::Item> InitNumericExtendedItem(
        Spc::Id666::Extended::ItemInfo extendedInfo, 
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
            Spc::FieldInfo info{ Spc::Id666::Extended::dataOffset, 
                                 setValue.size() };
            auto itemExtData = std::make_shared<T>("Test", info);
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
    
        Spc::FieldInfo info{ offset, size };
        auto itemData = std::make_shared<U>(params.expectedLabel, info);
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

        Spc::FieldInfo info{ offset, size };
        auto itemExtData = std::make_shared<U>(params.expectedLabel, info);

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

        /*
        std::cerr << "Copy ptr:" << static_cast<const void*>(params.testData) << std::endl;  
        for (int i = 0; i < Spc::Id666::tagSize; ++i)
        {
            std::cerr << params.testData[i] << " ";
        }
        std::cerr << std::endl;*/

        std::memcpy(tag->FieldData()->RawData(), 
                    params.testData, 
                    Spc::Id666::tagSize);

        /*
        std::cerr << "Tag after copy:" << std::endl;
        for (int i = 0; i < Spc::Id666::tagSize; ++i)
        {
            std::cerr << tag->FieldData()->RawData()[i] << " ";
        }
        std::cerr << std::endl;
        */

        (tag.get()->*params.setMethodPtr)(params.setValue);

        /*
        std::cerr << "Tag after set:" << std::endl;
        for (int i = 0; i < Spc::Id666::tagSize; ++i)
        {
            std::cerr << tag->FieldData()->RawData()[i] << " ";
        }
        std::cerr << std::endl;
        */

        Spc::FieldInfo info{ params.offset, params.size };
        T field{ "Test Field", info };
        tag->FieldData()->SetPosition(params.offset - Spc::Id666::tagOffset);
        tag->FieldData()->Read(&field);

        /*
        for (size_t i = 0; i < field.Size(); i++)
        {
            std::cerr << field.RawData()[i] << " ";
        }
        std::cerr << std::endl;*/
        EXPECT_EQ(params.setValue, field.ToString());
    }

    template<typename T>
    void TestNumericSet(TestSetParams<T> params, bool isText)
    {
        ASSERT_NE(tag, nullptr);
        ASSERT_NE(tag->FieldData(), nullptr);
        ASSERT_NE(tag->FieldData()->RawData(), nullptr);
        ASSERT_GE(tag->FieldData()->Size(), Spc::Id666::tagSize);

        /*
        std::cerr << "Copy ptr:" << static_cast<const void*>(params.testData) << std::endl;  
        for (int i = 0; i < Spc::Id666::tagSize; ++i)
        {
            std::cerr << params.testData[i] << " ";
        }
        std::cerr << std::endl;*/

        std::memcpy(tag->FieldData()->RawData(), 
                    params.testData, 
                    Spc::Id666::tagSize);

        /*
        std::cerr << "Tag after copy:" << std::endl;
        for (int i = 0; i < Spc::Id666::tagSize; ++i)
        {
            std::cerr << tag->FieldData()->RawData()[i] << " ";
        }
        std::cerr << std::endl;
        */

        (tag.get()->*params.setMethodPtr)(params.setValue);

        /*
        std::cerr << "Tag after set:" << std::endl;
        for (int i = 0; i < Spc::Id666::tagSize; ++i)
        {
            std::cerr << tag->FieldData()->RawData()[i] << " ";
        }
        std::cerr << std::endl;
        */

        Spc::FieldInfo info{ params.offset, params.size };
        T field{ "Test Field", info };
        tag->FieldData()->SetPosition(params.offset - Spc::Id666::tagOffset);
        tag->FieldData()->Read(&field);

        /*
        for (size_t i = 0; i < field.Size(); i++)
        {
            std::cerr << field.RawData()[i] << " ";
        }
        std::cerr << std::endl;*/
        EXPECT_EQ(isText, field.IsText());
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
        Spc::FieldInfo info{ offset, Spc::Id666::Extended::dataInfo.size };
        auto itemData = std::make_shared<U>("Test", info);
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
        //size_t offset = Spc::Id666::Extended::dataOffset;

        (tag.get()->*params.setMethodPtr)(params.setValue);
        std::shared_ptr<Spc::Id666::Extended::Item> item = *(params.itemPtrPtr);
        ASSERT_NE(item, nullptr);
        ASSERT_NE(item->extendedData, nullptr);
        
        auto extendedDataSize = std::static_pointer_cast<Spc::NumericField>(
            item->data);

        const auto actualExtendedSize = item->extendedData->Size();
        ASSERT_EQ(actualExtendedSize, extendedDataSize->ToUInt32());

        if (params.extendedType == Spc::Id666::Extended::stringType)
        {
            const auto expectedPadding =
                (4 - (actualExtendedSize % 4)) % 4;

            if (expectedPadding > 0)
            {
                EXPECT_NE(item->padding, nullptr);
                EXPECT_EQ(expectedPadding, item->padding->Size());
            }
            else
            {
                EXPECT_EQ(item->padding, nullptr);
            }
        }

        // When the data is not in the header, then item-data contains the
        // extended data size. Ensure it matches the size of the extended
        // data before proceeding with any additional checks as we don't
        // want any buffer overflows.
        ASSERT_EQ(actualExtendedSize, item->extendedData->Size());

        EXPECT_EQ(item->id->ToInt32(), params.extendedID);
        EXPECT_EQ(item->type->ToInt32(), params.extendedType);
        EXPECT_EQ(params.expectedValue, item->extendedData->ToString());   
    }

    template<typename T>
    void TestFieldsWithoutGet(TestFieldWithoutGetParams params)
    {
        ASSERT_NE(tag, nullptr);
        ASSERT_NE(tag->FieldData(), nullptr);
        ASSERT_NE(tag->FieldData()->RawData(), nullptr);
        ASSERT_GE(tag->FieldData()->Size(), Spc::Id666::tagSize);
          
        std::shared_ptr<Binary::BufferStream> fieldData = tag->FieldData();            

        Spc::FieldInfo info{ params.offset, params.size };
        T field{ "Test Field", info };
        size_t existingPosition = fieldData->Position();
        fieldData->SetPosition(params.offset - Spc::Id666::tagOffset);
        fieldData->Read(&field);
        fieldData->SetPosition(existingPosition);

        EXPECT_EQ(params.expectedValue, field.ToString());
    }

    void SetEmptyAndExpectRawFieldCleared(
        void (Spc::Id666::Tag::*setMethodPtr)(std::string value),
        size_t offset,
        size_t size)
    {
        ASSERT_NE(tag, nullptr);
        ASSERT_NE(tag->FieldData(), nullptr);
        ASSERT_NE(tag->FieldData()->RawData(), nullptr);
        ASSERT_GE(tag->FieldData()->Size(), Spc::Id666::tagSize);

        std::memcpy(tag->FieldData()->RawData(),
                    textData,
                    Spc::Id666::tagSize);

        EXPECT_NO_THROW((tag.get()->*setMethodPtr)(""));

        const size_t start = offset - Spc::Id666::tagOffset;

        for (size_t i = 0; i < size; i++)
        {
            EXPECT_EQ(0, tag->FieldData()->RawData()[start + i]);
        }
    }

    void SetEmptyAndExpectExtendedItemCleared(
        void (Spc::Id666::Tag::*setMethodPtr)(std::string value),
        std::shared_ptr<Spc::Id666::Extended::Item>* itemPtr)
    {
        ASSERT_NE(tag, nullptr);
        ASSERT_NE(itemPtr, nullptr);
        ASSERT_NE(*itemPtr, nullptr);

        EXPECT_NO_THROW((tag.get()->*setMethodPtr)(""));
        EXPECT_EQ(nullptr, *itemPtr);
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
