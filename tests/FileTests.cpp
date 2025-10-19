// FileTests.cpp - Defines the FileTests class and tests.
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

#include "FileTests.h"

void FileTests::SetUp() 
{
    testPath = "C:/test/file.spc";
    file = std::make_unique<Spc::File>(testPath);
}

TEST_F(FileTests, PathReflectsConstructorValue) 
{
    EXPECT_EQ(file->Path(), testPath);
}

TEST_F(FileTests, HasLoadedReturnsFalseInitially) 
{
    EXPECT_FALSE(file->HasLoaded());
}

TEST_F(FileTests, TagTypeReturnsTextInitially) 
{
    EXPECT_EQ(file->TagType(), Spc::TagType::Text);
}

TEST_F(FileTests, HasExtendedTagReturnsFalseInitially) 
{
    EXPECT_FALSE(file->HasExtendedTag());
}

TEST_F(FileTests, HeaderContainsTagReturnsFalseInitially) 
{
    EXPECT_FALSE(file->HeaderContainsTag());
}

TEST_F(FileTests, NameReturnsFilenameOnly) 
{
    EXPECT_EQ(file->Name(), "file.spc");
}

TEST_F(FileTests, SongNameReturnsBinaryVersionWhenTagTypeIsBinary) 
{
    
}