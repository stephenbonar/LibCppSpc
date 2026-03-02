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

TEST_F(PatternTokenTests, IdentifiesSongPlaceholderToken)
{
    Spc::Id666::PatternToken token{ "%song%" };

    EXPECT_EQ(token.Type(), Spc::Id666::PatternTokenType::SongPlaceholder);
}

TEST_F(PatternTokenTests, IdentifiesGamePlaceholderToken)
{
    Spc::Id666::PatternToken token{ "%game%" };

    EXPECT_EQ(token.Type(), Spc::Id666::PatternTokenType::GamePlaceholder);
}

TEST_F(PatternTokenTests, IdentifiesArtistPlaceholderToken)
{
    Spc::Id666::PatternToken token{ "%artist%" };

    EXPECT_EQ(token.Type(), Spc::Id666::PatternTokenType::ArtistPlaceholder);
}

TEST_F(PatternTokenTests, IdentifiesDiscPlaceholderToken)
{
    Spc::Id666::PatternToken token{ "%disc%" };

    EXPECT_EQ(token.Type(), Spc::Id666::PatternTokenType::DiscPlaceholder);
}

TEST_F(PatternTokenTests, IdentifiesTrackPlaceholderToken)
{
    Spc::Id666::PatternToken token{ "%track%" };

    EXPECT_EQ(token.Type(), Spc::Id666::PatternTokenType::TrackPlaceholder);
}

TEST_F(PatternTokenTests, IdentifiesLiteralToken)
{
    Spc::Id666::PatternToken token{ "literal" };

    EXPECT_EQ(token.Type(), Spc::Id666::PatternTokenType::Literal);
}

TEST_F(PatternTokenTests, IdentifiesInvalidTokens)
{
    Spc::Id666::PatternToken token{ "%invalid%" };
    Spc::Id666::PatternToken token2{ "%song" };

    EXPECT_EQ(token.Type(), Spc::Id666::PatternTokenType::Invalid);
    EXPECT_EQ(token2.Type(), Spc::Id666::PatternTokenType::Invalid);
}