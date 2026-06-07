// EmulatorFieldTests.cpp - Defines the EmulatorFieldTests class and tests.
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

#include "EmulatorFieldTests.h"

void EmulatorFieldTests::SetUp() 
{
    Spc::FieldInfo emulatorInfo{ 0xD1, 1 };
    textField = std::make_unique<Spc::EmulatorField>("Text", emulatorInfo);
    textField->SetType(Spc::NumericType::Text);
    binaryField = std::make_unique<Spc::EmulatorField>("Binary", emulatorInfo);
    binaryField->SetType(Spc::NumericType::Binary);
}

TEST_F(EmulatorFieldTests, ConstructorsInitializeIsPresentProperly)
{
    Spc::FieldInfo emulatorInfo{ 0xD1, 1 };
    Spc::EmulatorField defaultPresence("Default", emulatorInfo);
    Spc::EmulatorField notPresent("Missing", emulatorInfo, false);
    Spc::EmulatorField typedDefaultPresence(
        "TypedDefault", emulatorInfo, Spc::NumericType::Text);
    Spc::EmulatorField typedNotPresent(
        "TypedMissing", emulatorInfo, Spc::NumericType::Text, false);

    EXPECT_TRUE(defaultPresence.IsPresent());
    EXPECT_FALSE(notPresent.IsPresent());
    EXPECT_TRUE(typedDefaultPresence.IsPresent());
    EXPECT_FALSE(typedNotPresent.IsPresent());
}

TEST_F(EmulatorFieldTests, ToStringReturnsZSNESIfValue1) 
{
    textField->SetInt32(1);
    binaryField->SetInt32(1);

    EXPECT_EQ(textField->ToString(), "ZSNES");
    EXPECT_EQ(binaryField->ToString(), "ZSNES");
}

TEST_F(EmulatorFieldTests, ToStringReturnsSNES9XForValue2) 
{
    textField->SetInt32(2);
    binaryField->SetInt32(2);

    EXPECT_EQ(textField->ToString(), "SNES9X");
    EXPECT_EQ(binaryField->ToString(), "SNES9X");
}

TEST_F(EmulatorFieldTests, ToStringReturnsUnknownForOtherValues) 
{
    textField->SetInt32(0);
    binaryField->SetInt32(0);

    EXPECT_EQ(textField->ToString(), "Unknown");
    EXPECT_EQ(binaryField->ToString(), "Unknown");
}