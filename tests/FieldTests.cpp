// FieldTests.cpp - Defines the FieldTests class and tests.
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

#include "FieldTests.h"

void FieldTests::SetUp() 
{
    Spc::FieldInfo info{ 100, 5 };
    field = std::make_unique<Spc::Field>("TestLabel", info);
}

TEST_F(FieldTests, LabelReflectsConstructorValue) 
{
    EXPECT_EQ(field->Label(), "TestLabel");
}

TEST_F(FieldTests, OffsetReflectsConstructorValue) 
{
    EXPECT_EQ(field->Offset(), 100);
}

TEST_F(FieldTests, SizeReflectsConstructorValue) 
{
    EXPECT_EQ(field->Size(), 5);
}

TEST_F(FieldTests, SetValuePopulatesRawDataCorrectly)
{
    // Use the hex values for "TEST "
    field->SetValue("54 45 53 54 20");

    EXPECT_EQ(std::string(field->RawData(), field->Size()), "TEST ");
}

TEST_F(FieldTests, ToStringReturnsHexFormattedString)
{
    // Use the hex values for "TEST "
    field->SetValue("54 45 53 54 20");

    EXPECT_EQ(field->ToString(), "54 45 53 54 20");
}

TEST_F(FieldTests, ValueMatchesToString)
{
    // Use the hex values for "TEST "
    field->SetValue("54 45 53 54 20");

    EXPECT_EQ(field->Value(), field->ToString());
}
