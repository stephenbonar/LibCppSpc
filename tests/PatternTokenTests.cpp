// PatternTokenTests.cpp - Implements the PatternTokenTests class and tests.
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

#include "PatternTokenTests.h"

void PatternTokenTests::SetUp()
{
}

TEST_F(PatternTokenTests, InitializesProperly)
{
    Spc::Id666::PatternToken token{ "test" };

    EXPECT_EQ(token.Lexeme(), "test");
}

TEST_F(PatternTokenTests, IdentifiesPlaceholderToken)
{
    Spc::Id666::PatternToken token{ "%test%" };

    EXPECT_EQ(token.Type(), Spc::Id666::PatternTokenType::Placeholder);
}

TEST_F(PatternTokenTests, IdentifiesLiteralTokens)
{
    Spc::Id666::PatternToken token1{ "literal" };
    Spc::Id666::PatternToken token2{ "%literal" };
    Spc::Id666::PatternToken token3{ "literal%" };

    EXPECT_EQ(token1.Type(), Spc::Id666::PatternTokenType::Literal);
    EXPECT_EQ(token2.Type(), Spc::Id666::PatternTokenType::Literal);
    EXPECT_EQ(token3.Type(), Spc::Id666::PatternTokenType::Literal);
}

TEST_F(PatternTokenTests, IdentifiesEndOfPatternToken)
{
    Spc::Id666::PatternToken token;

    EXPECT_EQ(token.Type(), Spc::Id666::PatternTokenType::End);
}