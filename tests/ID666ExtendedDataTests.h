// ID666ExtendedDataTests.h - Declares the ID666ExtendedDataTests class and tests.
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

#ifndef ID666_EXTENDED_DATA_TESTS_H
#define ID666_EXTENDED_DATA_TESTS_H

#include <memory>
#include <gtest/gtest.h>
#include "ID666ExtendedData.h"
#include "ID666ExtendedItem.h"

class ID666ExtendedDataTests : public ::testing::Test
{
protected:
    void InitStringItem(std::shared_ptr<Spc::ID666ExtendedItem>& item, 
                        std::string value);

    Spc::ID666ExtendedData id666ExtendedData;
};

#endif