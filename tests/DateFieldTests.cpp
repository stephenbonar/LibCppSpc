// DateFieldTests.cpp - Defines the DateFieldTests class and tests.
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

#include "DateFieldTests.h"

TEST_F(DateFieldTests, IsTextReturnsTrueForValidTextRepresentation)
{
    //dateField->SetTextValue("02/06/2000");
    dateField->SetType(Spc::NumericType::Text);
    dateField->SetValue("02/06/2000");

    EXPECT_TRUE(dateField->IsText()) 
        << "IsText() should return true for text representation";
}

TEST_F(DateFieldTests, IsTextReturnsFalseForBinaryCharacters)
{
    //dateField->SetBinaryValue("02/06/2000"); 
    dateField->SetType(Spc::NumericType::Binary);
    dateField->SetValue("02/06/2000");

    EXPECT_FALSE(dateField->IsText())
        << "IsText() should return false for binary representation";
}

TEST_F(DateFieldTests, IsTextReturnsTrueForAllZeros)
{
    EXPECT_TRUE(dateField->IsText())
        << "IsText() should return true for all zeros";
}

TEST_F(DateFieldTests, ConstructorThrowsExceptionIfSizeLessThan11)
{
    EXPECT_THROW(Spc::DateField invalidDateField("InvalidDate", 0x00, 10), 
                 std::invalid_argument);
}

TEST_F(DateFieldTests, HasUnusedAreaReturnsTrueIfBytes4AndGreaterAreZero)
{
    //dateField->SetBinaryValue("02/06/2000");
    dateField->SetType(Spc::NumericType::Binary);
    dateField->SetValue("02/06/2000");

    EXPECT_TRUE(dateField->HasUnusedArea()) 
        << "HasUnusedArea() should return true if bytes 4 and greater are 0";
}

TEST_F(DateFieldTests, HasUnusedAreaReturnsFalseIfAnyByte4AndGreaterIsNonZero)
{
    //dateField->SetTextValue("02/06/2000");
    dateField->SetType(Spc::NumericType::Text);
    dateField->SetValue("02/06/2000");

    EXPECT_FALSE(dateField->HasUnusedArea()) 
        << "HasUnusedArea() should return false byte 4 and greater is non-zero";
}

TEST_F(DateFieldTests, IsSetReturnsTrueIfAnyByteIsNonZero)
{
    //dateField->SetBinaryValue("02/06/2000");
    dateField->SetType(Spc::NumericType::Binary);
    dateField->SetValue("02/06/2000");

    EXPECT_TRUE(dateField->IsSet()) 
        << "IsSet() should return true if at least one byte is non-zero";
}

TEST_F(DateFieldTests, IsSetReturnsFalseIfAllBytesAreZero)
{
    EXPECT_FALSE(dateField->IsSet()) 
        << "IsSet() should return false if all bytes are zero";
}

TEST_F(DateFieldTests, SetTextValueThrowsExceptionForInvalidFormats)
{
    //EXPECT_THROW(dateField->SetTextValue("12312025"), std::invalid_argument);
    //EXPECT_THROW(dateField->SetTextValue("MM/DD/YYYY"),std::invalid_argument);
    dateField->SetType(Spc::NumericType::Text);
    EXPECT_THROW(dateField->SetValue("12312025"), std::invalid_argument);
    EXPECT_THROW(dateField->SetValue("MM/DD/YYYY"),std::invalid_argument);
}

TEST_F(DateFieldTests, SetTextValueDoesNotThrowExceptionForValidFormats)
{
    //EXPECT_NO_THROW(dateField->SetTextValue("02/06/2000"));
    dateField->SetType(Spc::NumericType::Text);
    EXPECT_NO_THROW(dateField->SetValue("02/06/2000"));
}

TEST_F(DateFieldTests, SetBinaryValueThrowsExceptionForInvalidFormats)
{
    //EXPECT_THROW(dateField->SetBinaryValue("12312025"), std::invalid_argument);
    //EXPECT_THROW(dateField->SetBinaryValue("MM/DD/YYYY"),std::invalid_argument);
    dateField->SetType(Spc::NumericType::Binary);
    EXPECT_THROW(dateField->SetValue("12312025"), std::invalid_argument);
    EXPECT_THROW(dateField->SetValue("MM/DD/YYYY"),std::invalid_argument);
}

TEST_F(DateFieldTests, SetBinaryValueDoesNotThrowExceptionForValidFormats)
{
    //EXPECT_NO_THROW(dateField->SetBinaryValue("02/06/2000"));
    dateField->SetType(Spc::NumericType::Binary);
    EXPECT_NO_THROW(dateField->SetValue("02/06/2000"));
}

TEST_F(DateFieldTests, ToStringReturnsSameValueAsTextValue)
{
    //dateField->SetTextValue("02/06/2000");
    dateField->SetType(Spc::NumericType::Text);
    dateField->SetValue("02/06/2000");

    std::string valueResult = dateField->Value();
    std::string toStringResult = dateField->ToString();

    EXPECT_EQ(toStringResult, valueResult)
        << "ToString() should return the same value as Value()";
}

TEST_F(DateFieldTests, ToStringReturnsSameValueAsBinaryValue)
{
    //dateField->SetBinaryValue("02/06/2000");
    dateField->SetType(Spc::NumericType::Binary);
    dateField->SetValue("02/06/2000");

    std::string valueResult = dateField->Value();
    std::string toStringResult = dateField->ToString();

    EXPECT_EQ(toStringResult, valueResult)
        << "ToString() should return the same value as Value()";
}

TEST_F(DateFieldTests, ValueReturnsCorrectTextRepresentation)
{
    //dateField->SetTextValue("02/06/2000");
    dateField->SetType(Spc::NumericType::Text);
    dateField->SetValue("02/06/2000");

    EXPECT_EQ("02/06/2000", dateField->Value())
        << "Value() should return the correct text representation";
}

TEST_F(DateFieldTests, ValueReturnsCorrectBinaryRepresentation)
{
    //dateField->SetBinaryValue("02/06/2000");
    dateField->SetType(Spc::NumericType::Binary);
    dateField->SetValue("02/06/2000");

    EXPECT_EQ("02/06/2000", dateField->Value())
        << "Value() should return the correct binary representation";
}