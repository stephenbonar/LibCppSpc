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

#ifndef FILE_TESTS_H
#define FILE_TESTS_H

#include <gtest/gtest.h>
#include <LibCppSpc.h>
#include <memory>
#include "MockFileStream.h"

class FileTests : public ::testing::Test 
{
protected:
    Spc::Header expectedHeader;
    Spc::Id666::Tag expectedTag;
    Binary::BufferStream expectedRam{ Spc::ramInfo.size };
    Binary::BufferStream expectedDspRegisters{ Spc::dspRegistersInfo.size };
    Binary::BufferStream expectedUnused{ Spc::unusedInfo.size };
    Binary::BufferStream expectedExtraRam{ Spc::extraRamInfo.size };
    std::string expectedSongTitle = "Test Song";
    std::string expectedGameTitle = "Test Game";
    std::string expectedDumperName = "Test Dumper";
    std::string expectedComments = "Test Comments";
    std::string expectedDateDumped = "01/01/2025";
    std::string expectedSongLength = "120";
    std::string expectedFadeLength = "5000";
    std::string expectedSongArtist = "Test Artist";
    std::string expectedDefaultChannelState = "1";
    std::string expectedEmulatorUsed = "ZSNES";
    std::string expectedOstTitle = "Test OST Title";
    std::string expectedOstDisc = "1";
    std::string expectedOstTrack = "1b";
    std::string expectedPublisherName = "Test Publisher";
    std::string expectedCopyrightYear = "2025";
    std::string expectedIntroLength = "320000";
    std::string expectedLoopLength = "1920000";
    std::string expectedEndLength = "640000";
    std::string expectedMutedVoices = "00001111";
    std::string expectedLoopTimes = "3";
    std::string expectedPreampLevel = "65536";

    // Create alternate values to modify the tag with when testing saving,
    // focusing on values that can't simply be incremented or appended with a 
    // character to create a different value.
    std::string alternateExpectedDateDumped = "01/02/2025";
    std::string alternateExpectedEmulatorUsed = "SNES9X";
    std::string alternateExpectedDefaultChannelState = "0";
    std::string alternateExpectedOstTrack = "1c";
    std::string alternateExpectedMutedVoices = "11110000";

    void SetUp() override;

    void MockHeaderRead();

    void MockHeaderWrite();

    void MockBufferStreamRead(Binary::BufferStream* stream);

    void MockBufferStreamWrite(Binary::BufferStream* stream);

    void MockStringRead(uint8_t id, std::string expectedValue);

    void MockStringWrite(uint8_t id, std::string value);

    void MockLengthRead(uint8_t id, Spc::NumericField expectedField);

    void MockLengthWrite(uint8_t id, Spc::NumericField value);

    void MockIntRead(uint8_t id, Spc::NumericField expectedField);

    void MockIntWrite(uint8_t id, Spc::NumericField value);

    void MockNonExtendedDataReads();

    void MockNonExtendedDataWrites();

    void MockLongTagValueReads();

    void MockLongTagValueWrites();

    void MockExtendedTagValueReads();

    void MockExtendedTagValueWrites();

    void MockFileReads(bool useLongTagValues);

    void MockFileWrites(bool useLongTagValues);

    bool AllBytesMatch(Binary::BufferStream& expected, 
                       Binary::BufferStream& actual);

    size_t CalculateSizeWithPadding(std::string value) const;

    size_t CalculateExpectedChunkSize(bool useLongTagValues) const;

    void TestFileLoadsProperly(Spc::File& file, bool useLongTagValues);

    void TestFileLoadsAndSavesProperly(bool useLongTagValues);

    std::shared_ptr<MockFileStream> mockFileStream;
};

#endif