// PatternLexerTests.cpp - Defines the PatternLexerTests class and tests.
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

#include "PatternLexerTests.h"

void PatternLexerTests::SetUp()
{
    // No setup needed for these tests.
}

TEST_F(PatternLexerTests, LexesPatternProperly)
{
    std::string pattern{ "test-%test%.spc"};

    Spc::Id666::Pattern::Lexer lexer{ pattern };
    Spc::Id666::Pattern::Token literalToken = lexer.Lex();
    Spc::Id666::Pattern::Token placeholderToken = lexer.Lex();
    Spc::Id666::Pattern::Token literalToken2 = lexer.Lex();
    Spc::Id666::Pattern::Token endOfPatternToken = lexer.Lex();

    EXPECT_EQ(literalToken.Type(), Spc::Id666::Pattern::TokenType::Literal);
    EXPECT_EQ(literalToken.Lexeme(), "test-");
    EXPECT_EQ(placeholderToken.Type(), Spc::Id666::Pattern::TokenType::Placeholder);
    EXPECT_EQ(placeholderToken.Lexeme(), "%test%");
    EXPECT_EQ(literalToken2.Type(), Spc::Id666::Pattern::TokenType::Literal);
    EXPECT_EQ(literalToken2.Lexeme(), ".spc");
    EXPECT_EQ(endOfPatternToken.Type(), Spc::Id666::Pattern::TokenType::End);
    EXPECT_EQ(endOfPatternToken.Lexeme(), "");
}