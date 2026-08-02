// FormatTests.cpp - Defines the FormatTests class and tests.
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

#include "FormatTests.h"

void FormatTests::SetUp()
{
    // No setup needed for these tests.
}

TEST_F(FormatTests, FormatValuePrefixesValueWithPaddedLabel)
{
    std::string label{ "Track" };
    std::string value{ "2a" };

    std::string expected =
        label + std::string(Spc::labelSize - label.size(), ' ') + ": " + value;

    EXPECT_EQ(Spc::FormatValue(label, value), expected);
}

TEST_F(FormatTests, FormatValueDoesNotWrapAtValueChunkBoundary)
{
    std::string label{ "Chunk" };
    std::string value(Spc::valueChunkSize, 'x');

    std::string formatted = Spc::FormatValue(label, value);

    EXPECT_EQ(formatted.find('\n'), std::string::npos);
}

TEST_F(FormatTests, FormatValueWrapsAndAlignsContinuationLines)
{
    std::string label{ "Chunk" };
    std::string value(Spc::valueChunkSize + 1, 'x');

    std::string firstChunk(Spc::valueChunkSize, 'x');
    std::string secondChunk{ "x" };
    std::string continuationIndent(Spc::labelSize + 2, ' ');

    std::string expected =
        label + std::string(Spc::labelSize - label.size(), ' ') + ": " +
        firstChunk + "\n" + continuationIndent + secondChunk;

    EXPECT_EQ(Spc::FormatValue(label, value), expected);
}

TEST_F(FormatTests, FormatFieldUsesFieldLabelAndStringValue)
{
    Spc::FieldInfo info{ 0x00, 2 };
    Spc::Field field("Header", info);
    field.SetValue("AA BB");

    std::string expected =
        std::string("Header") +
        std::string(Spc::labelSize - std::string("Header").size(), ' ') +
        ": AA BB";

    EXPECT_EQ(Spc::FormatField(field), expected);
}

TEST_F(FormatTests, FormatFieldOutputsDashWhenFieldIsNotPresent)
{
    Spc::FieldInfo info{ 0x00, 2 };
    Spc::Field field("Header", info, false);

    std::string expected =
        std::string("Header") +
        std::string(Spc::labelSize - std::string("Header").size(), ' ') +
        ": -";

    EXPECT_EQ(Spc::FormatField(field), expected);
}
