// PatternParserTests.cpp - Defines the PatternParserTests class and tests.
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

#include "PatternParserTests.h"

void PatternParserTests::SetUp()
{
    // No setup needed for these tests.
}

TEST_F(PatternParserTests, ParsesPatternProperly)
{
    std::vector<Spc::Id666::PatternToken> tokens{
        Spc::Id666::PatternToken{ "%disc%" },
        Spc::Id666::PatternToken{ "." },
        Spc::Id666::PatternToken{ "%track%" },
        Spc::Id666::PatternToken{ " - " },
        Spc::Id666::PatternToken{ "%game%" },
        Spc::Id666::PatternToken{ " - " },
        Spc::Id666::PatternToken{ "%artist%" },
        Spc::Id666::PatternToken{ " - " },
        Spc::Id666::PatternToken{ "%song%" },
        Spc::Id666::PatternToken{ ".spc" },
        Spc::Id666::PatternToken{ }
    };

    Spc::Id666::PatternParser parser{ tokens };
    std::vector<Spc::Id666::PatternNode> nodes = parser.Parse();

    ASSERT_EQ(nodes.size(), 11);
    EXPECT_EQ(nodes[0].type, Spc::Id666::PatternNodeType::NumericPlaceholder);
    EXPECT_EQ(nodes[0].lexeme, "%disc%");
    EXPECT_EQ(nodes[1].type, Spc::Id666::PatternNodeType::Literal);
    EXPECT_EQ(nodes[1].lexeme, ".");
    EXPECT_EQ(nodes[2].type, Spc::Id666::PatternNodeType::NumericPlaceholder);
    EXPECT_EQ(nodes[2].lexeme, "%track%");
    EXPECT_EQ(nodes[3].type, Spc::Id666::PatternNodeType::Literal);
    EXPECT_EQ(nodes[3].lexeme, " - ");
    EXPECT_EQ(nodes[4].type, Spc::Id666::PatternNodeType::TextPlaceholder);
    EXPECT_EQ(nodes[4].lexeme, "%game%");
    EXPECT_EQ(nodes[5].type, Spc::Id666::PatternNodeType::Literal);
    EXPECT_EQ(nodes[5].lexeme, " - ");
    EXPECT_EQ(nodes[6].type, Spc::Id666::PatternNodeType::TextPlaceholder);
    EXPECT_EQ(nodes[6].lexeme, "%artist%");
    EXPECT_EQ(nodes[7].type, Spc::Id666::PatternNodeType::Literal);
    EXPECT_EQ(nodes[7].lexeme, " - ");
    EXPECT_EQ(nodes[8].type, Spc::Id666::PatternNodeType::TextPlaceholder);
    EXPECT_EQ(nodes[8].lexeme, "%song%");
    EXPECT_EQ(nodes[9].type, Spc::Id666::PatternNodeType::Literal);
    EXPECT_EQ(nodes[9].lexeme, ".spc");
    EXPECT_EQ(nodes[10].type, Spc::Id666::PatternNodeType::End);
    EXPECT_EQ(nodes[10].lexeme, "");
}