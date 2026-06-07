// TextFieldTests.cpp - Defines the TextFieldTests class and tests.
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

#include "TextFieldTests.h"

void TextFieldTests::SetUp()
{
    // No setup needed for these tests.
}

TEST_F(TextFieldTests, EnsureSizeGreaterThanZero)
{
    Spc::FieldInfo info{ 4, 0 };
    std::string label{ "Test Text Field" };

    EXPECT_THROW(Spc::TextField(label, info), std::invalid_argument);
}

TEST_F(TextFieldTests, ConstructorInitializesProperly)
{
    Spc::FieldInfo info{ 4, 4 };
    std::string label{ "Test Text Field" };
    Spc::TextField textField(label, info);

    EXPECT_EQ(textField.Label(), label);
    EXPECT_EQ(textField.Offset(), info.offset);
    EXPECT_EQ(textField.Size(), info.size);
    EXPECT_TRUE(textField.IsPresent());
}

TEST_F(TextFieldTests, ConstructorInitializesExplicitIsPresent)
{
    Spc::FieldInfo info{ 4, 4 };
    Spc::TextField textField("Test Text Field", info, false);

    EXPECT_FALSE(textField.IsPresent());
}

TEST_F(TextFieldTests, SetValueSetsStringValueCorrectly)
{
    Spc::FieldInfo info{ 4, 4 };
    Spc::TextField textField("Test Text Field", info);

    textField.SetValue("ABCD");

    EXPECT_EQ(textField.Value(), "ABCD");
    EXPECT_EQ(textField.ToString(), "ABCD");
}

TEST_F(TextFieldTests, SetValueTruncatesValuesLongerThanFieldSize)
{
    Spc::FieldInfo info{ 4, 4 };
    Spc::TextField textField("Test Text Field", info);

    textField.SetValue("ABCDE");

    EXPECT_EQ(textField.Value(), "ABCD");
}

TEST_F(TextFieldTests, SetValueZeroFillsRemainingBytesWhenValueIsShorter)
{
    Spc::FieldInfo info{ 4, 4 };
    Spc::TextField textField("Test Text Field", info);

    textField.SetValue("AB");

    EXPECT_EQ(textField.RawData()[0], 'A');
    EXPECT_EQ(textField.RawData()[1], 'B');
    EXPECT_EQ(textField.RawData()[2], '\0');
    EXPECT_EQ(textField.RawData()[3], '\0');
    EXPECT_EQ(textField.Value(), "AB");
}
