// TrackFieldTests.cpp - Defines the TrackFieldTests class and tests.
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

#include "TrackFieldTests.h"

void TrackFieldTests::SetUp()
{
    Spc::FieldInfo info{ 0xA0, 2 };
    trackField = std::make_unique<Spc::TrackField>("Test Track Field", info);
}

TEST_F(TrackFieldTests, EnsureSizeGreaterThanZero)
{
    Spc::FieldInfo info{ 0xA0, 0 };
    EXPECT_THROW(Spc::TrackField("Test Track Field", info), std::invalid_argument);
}

TEST_F(TrackFieldTests, ConstructorInitializesProperly)
{
    EXPECT_EQ(trackField->Label(), "Test Track Field");
    EXPECT_EQ(trackField->Offset(), 0xA0);
    EXPECT_EQ(trackField->Size(), 2);
    EXPECT_TRUE(trackField->IsPresent());
}

TEST_F(TrackFieldTests, ConstructorInitializesExplicitIsPresent)
{
    Spc::FieldInfo info{ 0xA0, 2 };
    Spc::TrackField notPresentField("Test Track Field", info, false);

    EXPECT_FALSE(notPresentField.IsPresent());
}

TEST_F(TrackFieldTests, SuffixReturnsNullCharByDefault)
{
    EXPECT_EQ(trackField->Suffix(), '\0');
}

TEST_F(TrackFieldTests, SetValueWithSuffixPopulatesSuffixAndStringValue)
{
    trackField->SetValue("2a");

    EXPECT_EQ(trackField->Suffix(), 'a');
    EXPECT_EQ(trackField->ToString(), "2a");
}

TEST_F(TrackFieldTests, SetValueWithoutSuffixPopulatesTrackOnly)
{
    trackField->SetValue("2");

    EXPECT_EQ(trackField->Suffix(), '\0');
    EXPECT_EQ(trackField->ToString(), "2");
}

TEST_F(TrackFieldTests, ToStringReflectsUnderlyingTrackAndSuffixBytes)
{
    trackField->RawData()[0] = 'b';
    trackField->RawData()[1] = '7';

    EXPECT_EQ(trackField->ToString(), "7b");
}
