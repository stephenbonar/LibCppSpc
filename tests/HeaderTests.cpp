// HeaderTests.cpp - Defines the HeaderTests class and tests.
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

#include "HeaderTests.h"

void HeaderTests::SetUp()
{
    header = std::make_unique<Spc::Header>();
}

TEST_F(HeaderTests, ContainsTagWorksCorrectly)
{
    header->containsTag.SetValue(std::to_string(Spc::headerContainsTag));
    EXPECT_TRUE(header->ContainsTag());

    header->containsTag.SetValue(std::to_string(Spc::headerContainsNoTag));
    EXPECT_FALSE(header->ContainsTag());
}

TEST_F(HeaderTests, SpcFieldsReturnsAllHeaderFieldsInCorrectOrder)
{
    std::vector<Spc::Field*> fields = header->SpcFields();

    ASSERT_EQ(fields.size(), 11);

    EXPECT_EQ(fields[0], &header->id);
    EXPECT_EQ(fields[1], &header->separator);
    EXPECT_EQ(fields[2], &header->containsTag);
    EXPECT_EQ(fields[3], &header->versionMinor);
    EXPECT_EQ(fields[4], &header->pcRegister);
    EXPECT_EQ(fields[5], &header->aRegister);
    EXPECT_EQ(fields[6], &header->xRegister);
    EXPECT_EQ(fields[7], &header->yRegister);
    EXPECT_EQ(fields[8], &header->pswRegister);
    EXPECT_EQ(fields[9], &header->spRegister);
    EXPECT_EQ(fields[10], &header->reserved);
}
