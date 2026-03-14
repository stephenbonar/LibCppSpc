// ID666ExtendedItemTests.cpp - Defines the ID666ExtendedItemTests class and tests.
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

#include "ID666ExtendedItemTests.h"

void ID666ExtendedItemTests::SetUp() 
{
    item = std::make_unique<Spc::Id666::Extended::Item>();
}

TEST_F(ID666ExtendedItemTests, IdFieldIsInitializedProperly) 
{
    EXPECT_EQ(item->id->Label(), "Item ID");
    EXPECT_EQ(item->id->Offset(), Spc::Id666::Extended::dataOffset);
    EXPECT_EQ(item->id->Size(), Spc::Id666::Extended::idInfo.size);
}

TEST_F(ID666ExtendedItemTests, TypeFieldIsInitializedProperly)
{
    EXPECT_EQ(item->type->Label(), "Item Type");
    EXPECT_EQ(item->type->Offset(), Spc::Id666::Extended::dataOffset);
    EXPECT_EQ(item->type->Size(), Spc::Id666::Extended::typeInfo.size);
}

TEST_F(ID666ExtendedItemTests, DataFieldIsInitializedProperly) 
{
    EXPECT_EQ(item->data->Label(), "Item Data");
    EXPECT_EQ(item->data->Offset(), Spc::Id666::Extended::dataOffset);
    EXPECT_EQ(item->data->Size(), Spc::Id666::Extended::dataInfo.size);
}

TEST_F(ID666ExtendedItemTests, SpcFieldsMethodReturnsAllFields)
{
    std::vector<Spc::Field*> fields = item->SpcFields();
    
    ASSERT_EQ(3, fields.size());
    EXPECT_EQ(item->id.get(), fields[0]);
    EXPECT_EQ(item->type.get(), fields[1]);
    EXPECT_EQ(item->data.get(), fields[2]);
}

TEST_F(ID666ExtendedItemTests, SpcFieldsMethodReturnsAdditionalFieldsIfNotNull)
{
    item->id->SetInt32(Spc::Id666::Extended::songTitleInfo.id);
    item->type->SetInt32(Spc::Id666::Extended::stringType);

    // Data is a pointer to the base class, so we need to cast it to 
    // NumericField since we know it is numeric when extended type is string.
    auto data = std::static_pointer_cast<Spc::NumericField>(item->data);

    // We're going to do a string that's 5 bytes long as that would need 
    // padding, and we want to test that the padding field is included.
    data->SetInt32(5);

    // Create the extended data field as a TextField since it should be string.
    Spc::FieldInfo extendedInfo{ Spc::Id666::Extended::dataOffset, 5 };
    auto extendedData = std::make_shared<Spc::TextField>("Extended Data", 
                                                         extendedInfo);
     
    extendedData->SetValue("Test ");

    item->extendedData = extendedData;

    // Create the padding field to align on a 4-byte boundary.
    Spc::FieldInfo paddingInfo{ Spc::Id666::Extended::dataOffset, 3 };
    item->padding = std::make_shared<Spc::TextField>("Padding", paddingInfo);

    std::vector<Spc::Field*> fields = item->SpcFields();

    ASSERT_EQ(5, fields.size());
    EXPECT_EQ(item->id.get(), fields[0]);
    EXPECT_EQ(item->type.get(), fields[1]);
    EXPECT_EQ(item->data.get(), fields[2]);
    EXPECT_EQ(item->extendedData.get(), fields[3]);
    EXPECT_EQ(item->padding.get(), fields[4]);
}