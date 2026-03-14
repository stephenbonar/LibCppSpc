// MockDataStructure.h - Declares the MockDataDataStructure class.
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

#ifndef MOCK_DATA_STRUCTURE_H
#define MOCK_DATA_STRUCTURE_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include "DataStructure.h"

class MockDataStructure : public Spc::DataStructure 
{
public:
    MOCK_METHOD(std::vector<Spc::Field*>, SpcFields, (), (const, override));
};

#endif