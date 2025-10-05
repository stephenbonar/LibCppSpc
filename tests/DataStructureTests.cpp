// DataStructureTests.cpp - Defines the DataStructureTests class and tests.
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

#include "DataStructureTests.h"
#include "Format.h" // for Spc::labelSize

void DataStructureTests::SetUp() 
{
    mockDataStructure = std::make_unique<MockDataStructure>();
    field1 = std::make_unique<Spc::TextField>("32-bit field", 0, 4);
    field2 = std::make_unique<Spc::TextField>("64-bit field", 4, 8);
    field1->SetValue("ABCD");
    field2->SetValue("ABCDEFGH");
}

TEST_F(DataStructureTests, SizeMethodAddsUpFieldSizes)
{ 
    std::vector<Spc::Field*> mockFields
    {
        field1.get(),
        field2.get()
    };
    
    EXPECT_CALL(*mockDataStructure, SpcFields())
        .Times(1)
        .WillOnce(::testing::Return(mockFields));
    
    size_t actualSize = mockDataStructure->Size();
    
    size_t expectedSize = field1->Size() + field2->Size();
    EXPECT_EQ(expectedSize, actualSize);
}

TEST_F(DataStructureTests, SizeMethodReturnsZeroForNoFields)
{
    std::vector<Spc::Field*> emptyFields;
    
    EXPECT_CALL(*mockDataStructure, SpcFields())
        .Times(1)
        .WillOnce(::testing::Return(emptyFields));
    
    EXPECT_EQ(0, mockDataStructure->Size());
}

TEST_F(DataStructureTests, SizeMethodHandlesSingleField)
{
    std::vector<Spc::Field*> singleFieldVector = { field1.get() };
    
    EXPECT_CALL(*mockDataStructure, SpcFields())
        .Times(1)
        .WillOnce(::testing::Return(singleFieldVector));
    
    EXPECT_EQ(field1->Size(), mockDataStructure->Size());
}

TEST_F(DataStructureTests, SizeMethodCallsSpcFieldsOnlyOnce)
{
    std::vector<Spc::Field*> fields = { field1.get() };
    
    EXPECT_CALL(*mockDataStructure, SpcFields())
        .Times(1)
        .WillOnce(::testing::Return(fields));
    
    size_t size = mockDataStructure->Size();
    
    EXPECT_EQ(field1->Size(), size);
}

TEST_F(DataStructureTests, ToStringMethodOutputsPaddedLabelsAndValues)
{
    std::vector<Spc::Field*> fields { field1.get(), field2.get() };
    EXPECT_CALL(*mockDataStructure, SpcFields())
        .Times(1)
        .WillOnce(::testing::Return(fields));

    std::string output = mockDataStructure->ToString();

    // Split into non-empty lines
    std::istringstream iss(output);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(iss, line))
        if (!line.empty()) lines.push_back(line);

    ASSERT_EQ(lines.size(), 2) << "Expected one line per field";

    // Helper to build expected line
    auto makeExpected = [](const std::string& label, const std::string& value) 
    {
        std::ostringstream oss;
        oss << std::setw(Spc::labelSize) << std::left << label << ": " << value;
        return oss.str();
    };

    // Expected lines
    std::string expected1 = makeExpected("32-bit field", "ABCD");
    std::string expected2 = makeExpected("64-bit field", "ABCDEFGH");

    EXPECT_EQ(lines[0], expected1);
    EXPECT_EQ(lines[1], expected2);

    // Additional structural checks
    for (const auto& l : lines)
    {
        ASSERT_GT(l.size(), Spc::labelSize + 2) << "Line too short";
        size_t colonPos = l.find(':');
        EXPECT_EQ(colonPos, Spc::labelSize) 
            << "Colon should appear at padded label width";
        EXPECT_EQ(l[colonPos + 1], ' ') << "Expected space after colon";
    }
}

