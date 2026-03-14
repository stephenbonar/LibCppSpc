// DateFieldTests.h - Declares the DateFieldTests class and tests.
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

#ifndef DATE_FIELD_TESTS_H
#define DATE_FIELD_TESTS_H

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <LibCppSpc.h>

class DateFieldTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Create a DateField instance for testing.
        Spc::FieldInfo dateInfo{ 0x9E, 11 };
        dateField = std::make_unique<Spc::DateField>("TestDate", dateInfo);
    }

    std::unique_ptr<Spc::DateField> dateField;
};

#endif