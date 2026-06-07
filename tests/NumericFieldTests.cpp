// NumericFieldTests.cpp - Defines the NumericFieldTests class and tests.
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

#include "NumericFieldTests.h"

void NumericFieldTests::SetUp()
{
    // No setup needed for these tests.
}

TEST_F(NumericFieldTests, EnsureSizeGreaterThanZero)
{
    Spc::FieldInfo info{ 4, 0 };
    std::string label{ "Test Numeric Field" };
    EXPECT_THROW(Spc::NumericField(label, info), std::invalid_argument);
}

TEST_F(NumericFieldTests, ConstructorsInitializesProperly)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info);
    Spc::NumericField numericFieldWithType(label, info, Spc::NumericType::Text);
    Spc::NumericField notPresentField(label, info, false);
    Spc::NumericField notPresentFieldWithType(label, info,
                                              Spc::NumericType::Text, false);

    EXPECT_EQ(numericField.Label(), label);
    EXPECT_EQ(numericField.Offset(), info.offset);
    EXPECT_EQ(numericField.Size(), info.size);
    EXPECT_TRUE(numericField.IsPresent());
    EXPECT_EQ(numericFieldWithType.Label(), label);
    EXPECT_EQ(numericFieldWithType.Offset(), info.offset);
    EXPECT_EQ(numericFieldWithType.Size(), info.size);
    EXPECT_EQ(numericFieldWithType.Type(), Spc::NumericType::Text);
    EXPECT_TRUE(numericFieldWithType.IsPresent());
    EXPECT_FALSE(notPresentField.IsPresent());
    EXPECT_FALSE(notPresentFieldWithType.IsPresent());
}

TEST_F(NumericFieldTests, IsZeroReturnsTrueForAllZeroBytes)
{
    Spc::FieldInfo info{ 4, 4 };
    Spc::NumericField numericField("Test Numeric Field", info);
    std::fill_n(numericField.RawData(), numericField.Size(), 0);

    EXPECT_TRUE(numericField.IsZero());
}

TEST_F(NumericFieldTests, IsZeroReturnsFalseForNonZeroBytes)
{
    Spc::FieldInfo info{ 4, 4 };
    Spc::NumericField numericField("Test Numeric Field", info);
    numericField.SetValue("1");

    EXPECT_FALSE(numericField.IsZero());
}

TEST_F(NumericFieldTests, IsTextReturnsTrueForAsciiDigits)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Text);
    numericField.SetValue("1234");

    EXPECT_TRUE(numericField.IsText());
}

TEST_F(NumericFieldTests, IsTextReturnsFalseForNonAsciiDigits)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Binary);
    numericField.SetValue("1234");

    EXPECT_FALSE(numericField.IsText());
}

TEST_F(NumericFieldTests, DetectInt32ReturnsCorrectValueForTextType)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Text);
    
    numericField.SetValue("1234");
    numericField.SetType(Spc::NumericType::Either);

    EXPECT_EQ(numericField.DetectInt32(), 1234);
}

TEST_F(NumericFieldTests, DetectInt32ReturnsCorrectValueForBinaryType)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Binary);
    
    numericField.SetValue("1234");
    numericField.SetType(Spc::NumericType::Either);

    EXPECT_EQ(numericField.DetectInt32(), 1234);
}

TEST_F(NumericFieldTests, ToInt32ReturnsCorrectValue)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Binary);
    
    numericField.SetValue("-1234");

    EXPECT_EQ(numericField.ToInt32(), -1234);
}

TEST_F(NumericFieldTests, ToUInt32ReturnsCorrectValue)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Binary);
    
    numericField.SetValue("1234");

    EXPECT_EQ(numericField.ToUInt32(), 1234);
}

TEST_F(NumericFieldTests, ToStringReturnsCorrectValueForTextType)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Text);
    
    numericField.SetValue("1234");

    EXPECT_EQ(numericField.ToString(), "1234");
}

TEST_F(NumericFieldTests, ToStringReturnsCorrectValueForBinaryType)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Binary);
    
    numericField.SetValue("1234");

    EXPECT_EQ(numericField.ToString(), "1234");
}

TEST_F(NumericFieldTests, ToStringReturnsCorrectValueForEitherType)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Either);
    
    numericField.SetValue("1234");

    EXPECT_EQ(numericField.ToString(), "1234");
}

TEST_F(NumericFieldTests, SetInt32SetsValueCorrectly)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Binary);
    
    numericField.SetInt32(-1234);

    EXPECT_EQ(numericField.ToInt32(), -1234);
}

TEST_F(NumericFieldTests, SetUInt32SetsValueCorrectly)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Binary);
    
    numericField.SetUInt32(1234);

    EXPECT_EQ(numericField.ToUInt32(), 1234);
}

TEST_F(NumericFieldTests, SetValueSetsValueCorrectlyForTextType)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Text);
    
    numericField.SetValue("1234");

    EXPECT_EQ(numericField.Value(), "1234");
}

TEST_F(NumericFieldTests, SetValueSetsValueCorrectlyForBinaryType)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Binary);
    
    numericField.SetValue("1234");

    EXPECT_EQ(numericField.ToInt32(), 1234);
}

TEST_F(NumericFieldTests, SetValueSetsValueCorrectlyForEitherType)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Either);
    
    numericField.SetValue("1234");

    EXPECT_EQ(numericField.Value(), "1234");
}

TEST_F(NumericFieldTests, SetsTypeCorrectly)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Numeric Field" };
    Spc::NumericField numericField(label, info, Spc::NumericType::Either);
    
    numericField.SetType(Spc::NumericType::Text);

    EXPECT_EQ(numericField.Type(), Spc::NumericType::Text);
}