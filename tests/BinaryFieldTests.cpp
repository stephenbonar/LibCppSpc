// BinaryFieldTests.cpp - Defines the BinaryFieldTests class and tests.
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

#include "BinaryFieldTests.h"

void BinaryFieldTests::SetUp()
{
    oneByteFieldInfo = std::make_shared<Spc::FieldInfo>();
    oneByteFieldInfo->offset = 0;
    oneByteFieldInfo->size = 1;
    twoByteFieldInfo = std::make_shared<Spc::FieldInfo>();
    twoByteFieldInfo->offset = 0;
    twoByteFieldInfo->size = 2;
}

TEST_F(BinaryFieldTests, ConstructorInitializesIsPresentProperly)
{
    Spc::BinaryField defaultPresence("Test Binary Field", *oneByteFieldInfo);
    Spc::BinaryField notPresent("Test Binary Field", *oneByteFieldInfo, false);

    EXPECT_TRUE(defaultPresence.IsPresent());
    EXPECT_FALSE(notPresent.IsPresent());
}

TEST_F(BinaryFieldTests, SetValueAccceptsBinaryString)
{
    Spc::BinaryField binaryField("Test Binary Field", *oneByteFieldInfo);
    EXPECT_NO_THROW(binaryField.SetValue("10101010"));
}

TEST_F(BinaryFieldTests, SetValueThrowsOnInvalidString)
{
    Spc::BinaryField binaryField("Test Binary Field", *oneByteFieldInfo);
    EXPECT_THROW(binaryField.SetValue("10201010"), std::invalid_argument);
    EXPECT_THROW(binaryField.SetValue("abcdefg"), std::invalid_argument);
    EXPECT_THROW(binaryField.SetValue(""), std::invalid_argument);
}

TEST_F(BinaryFieldTests, ToStringReturnsCorrectString)
{
    Spc::BinaryField binaryField("Test Binary Field", *oneByteFieldInfo);
    binaryField.SetValue("00001111");
    EXPECT_EQ(binaryField.ToString(), "00001111");
}

TEST_F(BinaryFieldTests, SetValueSetsCorrectValue)
{
    Spc::BinaryField binaryField("Test Binary Field", *oneByteFieldInfo);
    binaryField.SetValue("00001111");
    EXPECT_EQ(binaryField.ToInt32(), 15);
}

TEST_F(BinaryFieldTests, SetValueReturnsCorrectValueForMorethan1Byte)
{
    Spc::BinaryField binaryField("Test Binary Field", *twoByteFieldInfo);
    binaryField.SetValue("00001111");
    EXPECT_EQ(binaryField.ToString(), "00001111 00000000");
}
