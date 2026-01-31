// FileTests.h - Declares the FileTests class and tests.
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
    mockFileStream = std::make_shared<MockFileStream>();
}

TEST_F(FileTests, InitializesFileProperly)
{
    Spc::File file("test.spc");

    std::string fileName = file.Path();
    Binary::BufferStream ram = file.Ram();
    Binary::BufferStream dspRegisters = file.DspRegisters();
    Binary::BufferStream unused = file.Unused();
    Binary::BufferStream extraRam = file.ExtraRam();

    EXPECT_EQ(fileName, "test.spc");
    EXPECT_EQ(ram.Size(), Spc::ramInfo.size);
    EXPECT_EQ(dspRegisters.Size(), Spc::dspRegistersInfo.size);
    EXPECT_EQ(unused.Size(), Spc::unusedInfo.size);
    EXPECT_EQ(extraRam.Size(), Spc::extraRamInfo.size);
}

TEST_F(FileTests, SetsHeaderProperly)
{
    Spc::File file("test.spc");
    Spc::Header header;

    header.id.SetValue(Spc::headerId);
    header.separator.RawData()[0] = Spc::separatorChar;
    header.separator.RawData()[1] = Spc::separatorChar;
    header.versionMinor.SetUInt32(Spc::currentVersionMinor);
    header.pcRegister.RawData()[0] = 1;
    header.pcRegister.RawData()[1] = 1;
    header.aRegister.RawData()[0] = 1;
    header.xRegister.RawData()[0] = 1;
    header.yRegister.RawData()[0] = 1;
    header.pswRegister.RawData()[0] = 1;
    header.spRegister.RawData()[0] = 1;

    file.SetHeader(header);
    Spc::Header retrievedHeader = file.Header();

    EXPECT_EQ(retrievedHeader.id.Value(), Spc::headerId);
    EXPECT_EQ(retrievedHeader.separator.RawData()[0], Spc::separatorChar);
    EXPECT_EQ(retrievedHeader.separator.RawData()[1], Spc::separatorChar);
    EXPECT_EQ(retrievedHeader.versionMinor.ToUInt32(), Spc::currentVersionMinor);
    EXPECT_EQ(retrievedHeader.pcRegister.RawData()[0], 1);
    EXPECT_EQ(retrievedHeader.pcRegister.RawData()[1], 1);
    EXPECT_EQ(retrievedHeader.aRegister.RawData()[0], 1);
    EXPECT_EQ(retrievedHeader.xRegister.RawData()[0], 1);
    EXPECT_EQ(retrievedHeader.yRegister.RawData()[0], 1);
    EXPECT_EQ(retrievedHeader.pswRegister.RawData()[0], 1);
    EXPECT_EQ(retrievedHeader.spRegister.RawData()[0], 1);
}