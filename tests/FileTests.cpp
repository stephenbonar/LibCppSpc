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

#include <cstring>

constexpr size_t headerSize{ 4 };
constexpr size_t intSize{ 4 };

void FileTests::SetUp()
{
    mockFileStream = std::make_shared<MockFileStream>();

    expectedHeader.id.SetValue(Spc::headerId);
    expectedHeader.separator.RawData()[0] = Spc::separatorChar;
    expectedHeader.separator.RawData()[1] = Spc::separatorChar;
    expectedHeader.containsTag.SetUInt32(Spc::headerContainsTag);
    expectedHeader.versionMinor.SetUInt32(Spc::currentVersionMinor);
    expectedHeader.pcRegister.RawData()[0] = 0x34;
    expectedHeader.pcRegister.RawData()[1] = 0x12;
    expectedHeader.aRegister.RawData()[0] = 0x56;
    expectedHeader.xRegister.RawData()[0] = 0x78;
    expectedHeader.yRegister.RawData()[0] = static_cast<char>(0x9A);
    expectedHeader.pswRegister.RawData()[0] = static_cast<char>(0xBC);
    expectedHeader.spRegister.RawData()[0] = static_cast<char>(0xDE);
    expectedTag.SetSongTitle(expectedSongTitle);
    expectedTag.SetGameTitle(expectedGameTitle);
    expectedTag.SetDumperName(expectedDumperName);
    expectedTag.SetComments(expectedComments);
    expectedTag.SetDateDumped(expectedDateDumped);
    expectedTag.SetSongLength(expectedSongLength);
    expectedTag.SetFadeLength(expectedFadeLength);
    expectedTag.SetSongArtist(expectedSongArtist);
    expectedTag.SetDefaultChannelState(expectedDefaultChannelState);
    expectedTag.SetEmulatorUsed(expectedEmulatorUsed);
    expectedTag.SetOstTitle(expectedOstTitle);
    expectedTag.SetOstDisc(expectedOstDisc);
    expectedTag.SetOstTrack(expectedOstTrack);
    expectedTag.SetPublisherName(expectedPublisherName);
    expectedTag.SetCopyrightYear(expectedCopyrightYear);
    expectedTag.SetIntroLength(expectedIntroLength);
    expectedTag.SetLoopLength(expectedLoopLength);
    expectedTag.SetEndLength(expectedEndLength);
    expectedTag.SetMutedVoices(expectedMutedVoices);
    expectedTag.SetLoopTimes(expectedLoopTimes);
    expectedTag.SetPreampLevel(expectedPreampLevel);

    for (size_t i = 0; i < expectedRam.Size(); i++)
        expectedRam.RawData()[i] = static_cast<char>(i % 256);

    for (size_t i = 0; i < expectedDspRegisters.Size(); i++)
        expectedDspRegisters.RawData()[i] = static_cast<char>((i + 1) % 256);

    for (size_t i = 0; i < expectedUnused.Size(); i++)
        expectedUnused.RawData()[i] = static_cast<char>((i + 2) % 256);

    for (size_t i = 0; i < expectedExtraRam.Size(); i++)
        expectedExtraRam.RawData()[i] = static_cast<char>((i + 3) % 256);
}

void FileTests::MockHeaderRead()
{
    EXPECT_CALL(*mockFileStream, Write(testing::A<Binary::DataStructure*>()))
        .WillOnce(testing::Invoke([this](Binary::DataStructure* structure)
        {
            auto header = static_cast<Spc::Header*>(structure);
            *header = this->expectedHeader;
        }));
}

void FileTests::MockHeaderWrite()
{
    EXPECT_CALL(*mockFileStream, Write(testing::A<Binary::DataStructure*>()))
        .WillOnce(testing::Invoke([this](Binary::DataStructure* structure)
        {
            auto header = static_cast<Spc::Header*>(structure);

            EXPECT_EQ(header->id.Value(), this->expectedHeader.id.Value());
            EXPECT_EQ(header->separator.RawData()[0],
                      this->expectedHeader.separator.RawData()[0]);
            EXPECT_EQ(header->separator.RawData()[1],
                      this->expectedHeader.separator.RawData()[1]);
            EXPECT_EQ(header->containsTag.ToUInt32(),
                      this->expectedHeader.containsTag.ToUInt32());
            EXPECT_EQ(header->versionMinor.ToUInt32(),
                      this->expectedHeader.versionMinor.ToUInt32());
            EXPECT_EQ(header->pcRegister.RawData()[0],
                      this->expectedHeader.pcRegister.RawData()[0]);
            EXPECT_EQ(header->pcRegister.RawData()[1],
                      this->expectedHeader.pcRegister.RawData()[1]);
            EXPECT_EQ(header->aRegister.RawData()[0],
                      this->expectedHeader.aRegister.RawData()[0]);
            EXPECT_EQ(header->xRegister.RawData()[0],
                      this->expectedHeader.xRegister.RawData()[0]);
            EXPECT_EQ(header->yRegister.RawData()[0],
                      this->expectedHeader.yRegister.RawData()[0]);
            EXPECT_EQ(header->pswRegister.RawData()[0],
                      this->expectedHeader.pswRegister.RawData()[0]);
            EXPECT_EQ(header->spRegister.RawData()[0],
                      this->expectedHeader.spRegister.RawData()[0]);
        }));
}

void FileTests::MockBufferStreamRead(Binary::BufferStream* stream)
{
    EXPECT_CALL(*mockFileStream, Read(testing::A<Binary::DataField*>()))
        .WillOnce(testing::Invoke([stream](Binary::DataField* field)
        {
            stream->CopyRawDataTo(field);
        }));
}

void FileTests::MockBufferStreamWrite(Binary::BufferStream* stream)
{
    EXPECT_CALL(*mockFileStream, Write(testing::A<Binary::DataField*>()))
        .Times(1)
        .WillOnce(testing::Invoke([stream](Binary::DataField* field)
        {
            EXPECT_EQ(field, stream);
        }));
}

void FileTests::MockNonExtendedDataReads()
{
    EXPECT_CALL(*mockFileStream, Open(Binary::FileMode::Read));
    EXPECT_CALL(*mockFileStream, IsOpen()).WillOnce(testing::Return(true));
    MockHeaderRead();
    MockBufferStreamRead(expectedTag.FieldData().get());
    MockBufferStreamRead(&expectedRam);
    MockBufferStreamRead(&expectedDspRegisters);
    MockBufferStreamRead(&expectedUnused);
    MockBufferStreamRead(&expectedExtraRam);
}

void FileTests::MockNonExtendedDataWrites()
{
    EXPECT_CALL(*mockFileStream, Open(Binary::FileMode::Write));
    EXPECT_CALL(*mockFileStream, IsOpen()).WillOnce(testing::Return(true));
    
    MockBufferStreamWrite(expectedTag.FieldData().get());
    MockBufferStreamWrite(&expectedRam);
    MockBufferStreamWrite(&expectedDspRegisters);
    MockBufferStreamWrite(&expectedUnused);
    MockBufferStreamWrite(&expectedExtraRam);
}

void FileTests::MockStringRead(uint8_t id, std::string expectedValue)
{
    auto needsPadding = [](size_t valueSize)
    {
        return (valueSize % 4) != 0;
    };

    EXPECT_CALL(*mockFileStream, Read(testing::A<Binary::DataStructure*>()))
        .WillOnce(testing::Invoke([id, expectedValue](Binary::DataStructure* structure)
        {
            auto item = static_cast<Spc::Id666::Extended::Item*>(structure);
            item->id->SetUInt32(id);
            item->type->SetUInt32(Spc::Id666::Extended::stringType);
            item->data->SetUInt32(
                static_cast<uint32_t>(expectedValue.size()));
        }));
    EXPECT_CALL(*mockFileStream, Read(testing::A<Binary::DataField*>()))
        .WillOnce(testing::Invoke([expectedValue](
            Binary::DataField* field)
        {
            std::memset(field->RawData(), 0, field->Size());
            std::memcpy(field->RawData(),
                        expectedValue.c_str(),
                        expectedValue.size());
        }));
    if (needsPadding(expectedValue.size()))
    {
        EXPECT_CALL(*mockFileStream, Read(testing::A<Binary::DataField*>()))
            .WillOnce(testing::Invoke([](
                Binary::DataField* field)
            {
                std::memset(field->RawData(), 0, field->Size());
            }));
    }
}

void FileTests::MockLongTagValueReads()
{
    MockStringRead(Spc::Id666::Extended::songTitleInfo.id, expectedSongTitle);
    MockStringRead(Spc::Id666::Extended::gameTitleInfo.id, expectedGameTitle);
    MockStringRead(Spc::Id666::Extended::songArtistInfo.id, expectedSongArtist);
    MockStringRead(Spc::Id666::Extended::dumperNameInfo.id, expectedDumperName);
    MockStringRead(Spc::Id666::Extended::commentsInfo.id, expectedComments);
}

void FileTests::MockLongTagValueWrites()
{

}

void FileTests::MockLengthRead(uint8_t id, Spc::NumericField expectedField)
{
    EXPECT_CALL(*mockFileStream, Read(testing::A<Binary::DataStructure*>()))
        .WillOnce(testing::Invoke([id, expectedField](
            Binary::DataStructure* structure)
        {
            auto item = static_cast<Spc::Id666::Extended::Item*>(structure);
            item->id->SetUInt32(id);
            item->type->SetUInt32(Spc::Id666::Extended::lengthType);
            item->data->SetUInt32(expectedField.ToUInt32());
        }));
}

void FileTests::MockIntRead(uint8_t id, Spc::NumericField expectedField)
{
    EXPECT_CALL(*mockFileStream, Read(testing::A<Binary::DataStructure*>()))
        .WillOnce(testing::Invoke([id](Binary::DataStructure* structure)
        {
            auto item = static_cast<Spc::Id666::Extended::Item*>(structure);
            item->id->SetUInt32(id);
            item->type->SetUInt32(Spc::Id666::Extended::integerType);
            item->data->SetUInt32(intSize);
        }));
    EXPECT_CALL(*mockFileStream, Read(testing::A<Binary::DataField*>()))
        .WillOnce(testing::Invoke([expectedField](
            Binary::DataField* field)
        {
            auto introField = static_cast<Spc::NumericField*>(field);
            introField->SetUInt32(expectedField.ToUInt32());
        }));
}

void FileTests::MockExtendedTagValueReads()
{
    MockStringRead(Spc::Id666::Extended::ostTitleInfo.id, expectedOstTitle);
    MockLengthRead(Spc::Id666::Extended::ostDiscInfo.id, expectedTag.OstDisc());

    // Do not use the generic MockLenghtRead here as we need the specialty
    // Spc::TrackField for the track to set properly. 
    EXPECT_CALL(*mockFileStream, Read(testing::A<Binary::DataStructure*>()))
        .WillOnce(testing::Invoke([ostTrack = expectedTag.OstTrack()](
            Binary::DataStructure* structure)
        {
            auto item = static_cast<Spc::Id666::Extended::Item*>(structure);
            item->id->SetUInt32(Spc::Id666::Extended::ostTrackInfo.id);
            item->type->SetUInt32(Spc::Id666::Extended::lengthType);
            item->data->SetUInt32(ostTrack.ToUInt32());
        }));

    MockStringRead(Spc::Id666::Extended::publisherNameInfo.id, 
                   expectedPublisherName);
    MockLengthRead(Spc::Id666::Extended::copyrightYearInfo.id, 
                   expectedTag.CopyrightYear());
    MockIntRead(Spc::Id666::Extended::introLengthInfo.id, 
                expectedTag.IntroLength());
    MockIntRead(Spc::Id666::Extended::loopLengthInfo.id, 
                expectedTag.LoopLength());
    MockIntRead(Spc::Id666::Extended::endLengthInfo.id, 
                expectedTag.EndLength());
    MockLengthRead(Spc::Id666::Extended::loopTimesInfo.id, 
                   expectedTag.LoopTimes());
    
    EXPECT_CALL(*mockFileStream, Read(testing::A<Binary::DataStructure*>()))
        .WillOnce(testing::Invoke([muted = expectedTag.MutedVoices()](
            Binary::DataStructure* structure)
        {
            auto item = static_cast<Spc::Id666::Extended::Item*>(structure);
            item->id->SetUInt32(Spc::Id666::Extended::mutedVoicesInfo.id);
            item->type->SetUInt32(Spc::Id666::Extended::lengthType);
            item->data->SetUInt32(muted.ToUInt32());
        }));

    MockIntRead(Spc::Id666::Extended::preampLevelInfo.id, 
                expectedTag.PreampLevel());
}

void FileTests::MockExtendedTagValueWrites()
{

}

void FileTests::MockFileReads(bool useLongTagValues)
{
    size_t expectedChunkSize = CalculateExpectedChunkSize(useLongTagValues);

    {
        testing::InSequence sequence;

        MockNonExtendedDataReads();

        EXPECT_CALL(*mockFileStream, FindNextChunk("xid6"))
            .WillOnce(testing::Invoke([expectedChunkSize](std::string)
            {
                auto header = std::make_shared<Binary::ChunkHeader>();
                header->id.SetValue("xid6");
                header->dataSize.SetValue(
                    static_cast<uint32_t>(expectedChunkSize));
                return header;
            }));

        if (useLongTagValues)
        {
            MockLongTagValueReads();
        }

        MockExtendedTagValueReads();

        EXPECT_CALL(*mockFileStream, Close());
    }
}

void FileTests::MockFileWrites(bool useLongTagValues)
{
    size_t expectedChunkSize = CalculateExpectedChunkSize(useLongTagValues);

    {
        testing::InSequence sequence;

        MockNonExtendedDataWrites();

        /*
        EXPECT_CALL(*mockFileStream, FindNextChunk("xid6"))
            .WillOnce(testing::Invoke([expectedChunkSize](std::string)
            {
                auto header = std::make_shared<Binary::ChunkHeader>();
                header->id.SetValue("xid6");
                header->dataSize.SetValue(
                    static_cast<uint32_t>(expectedChunkSize));
                return header;
            }));
        */

        if (useLongTagValues)
        {
            MockLongTagValueWrites();
        }

        MockExtendedTagValueWrites();

        EXPECT_CALL(*mockFileStream, Close());
    }
}

size_t FileTests::CalculateSizeWithPadding(std::string value) const
{
    constexpr size_t alignment{ 4 };
    size_t remainder{ value.size() % alignment };
    size_t padding{ (alignment - remainder) % alignment };
    return value.size() + padding + headerSize;
}

size_t FileTests::CalculateExpectedChunkSize(bool useLongTagValues) const
{
    size_t ostTitleSize = CalculateSizeWithPadding(expectedOstTitle);
    size_t publisherNameSize = CalculateSizeWithPadding(expectedPublisherName);
    size_t ostDiscSize{ headerSize };
    size_t ostTrackSize{ headerSize };
    size_t copyrightYearSize{ headerSize };
    size_t mutedVoicesSize{ headerSize };
    size_t loopTimesSize{ headerSize };
    size_t introLengthSize{ headerSize + intSize };
    size_t loopLengthSize{ headerSize + intSize };
    size_t endLengthSize{ headerSize + intSize };
    size_t preampLevelSize{ headerSize + intSize };
    
    size_t expectedChunkSize = ostTitleSize + publisherNameSize + ostDiscSize + 
                               ostTrackSize + copyrightYearSize + 
                               mutedVoicesSize + loopTimesSize + 
                               introLengthSize + loopLengthSize + 
                               endLengthSize + preampLevelSize;

    if (useLongTagValues)
    {
        size_t songTitleSize = CalculateSizeWithPadding(expectedSongTitle);
        size_t gameTitleSize = CalculateSizeWithPadding(expectedGameTitle);
        size_t dumperNameSize = CalculateSizeWithPadding(expectedDumperName);
        size_t songArtistSize = CalculateSizeWithPadding(expectedSongArtist);
        size_t commentsSize = CalculateSizeWithPadding(expectedComments);

        expectedChunkSize += songTitleSize + gameTitleSize + dumperNameSize +
                             songArtistSize + commentsSize;
    }

    return expectedChunkSize;
}

bool FileTests::AllBytesMatch(Binary::BufferStream& expected, 
                              Binary::BufferStream& actual)
{
    if (expected.Size() != actual.Size())
        return false;

    for (size_t i = 0; i < expected.Size(); i++)
    {
        if (expected.RawData()[i] != actual.RawData()[i])
            return false;
    }

    return true;
}

void FileTests::TestFileLoadsProperly(Spc::File& file, bool useLongTagValues)
{
    if (useLongTagValues)
    {
        expectedSongTitle = "Long Test Song Title That Exceeds Normal Length";
        expectedGameTitle = "Long Test Game Title That Exceeds Normal Length";
        expectedDumperName = "Long Test Dumper Name That Exceeds Normal Length";
        expectedSongArtist = "Long Test Song Artist That Exceeds Normal Length";
        expectedComments = "Long Test Comments That Exceed Normal Length";
    }

    MockFileReads(useLongTagValues);

    file.Load();

    Spc::Header retrievedHeader = file.Header();
    Spc::Id666::Tag retrievedTag = file.Tag();
    Binary::BufferStream retrievedRam = file.Ram();
    Binary::BufferStream retrievedDspRegisters = file.DspRegisters();
    Binary::BufferStream retrievedUnused = file.Unused();
    Binary::BufferStream retrievedExtraRam = file.ExtraRam();

    EXPECT_EQ(retrievedHeader.id.Value(), Spc::headerId);
    EXPECT_EQ(retrievedHeader.separator.RawData()[0], Spc::separatorChar);
    EXPECT_EQ(retrievedHeader.separator.RawData()[1], Spc::separatorChar);
    EXPECT_EQ(retrievedHeader.containsTag.ToUInt32(), Spc::headerContainsTag);
    EXPECT_EQ(retrievedHeader.versionMinor.ToUInt32(), 
              Spc::currentVersionMinor);
    EXPECT_EQ(retrievedHeader.pcRegister.RawData()[0], 0x34);
    EXPECT_EQ(retrievedHeader.pcRegister.RawData()[1], 0x12);
    EXPECT_EQ(static_cast<uint8_t>(retrievedHeader.aRegister.RawData()[0]), 
              0x56);
    EXPECT_EQ(static_cast<uint8_t>(retrievedHeader.xRegister.RawData()[0]), 
              0x78);
    EXPECT_EQ(static_cast<uint8_t>(retrievedHeader.yRegister.RawData()[0]),
              0x9A);
    EXPECT_EQ(static_cast<uint8_t>(retrievedHeader.pswRegister.RawData()[0]), 
              0xBC);
    EXPECT_EQ(static_cast<uint8_t>(retrievedHeader.spRegister.RawData()[0]), 
              0xDE);

    EXPECT_EQ(retrievedTag.SongTitle().Value(), expectedSongTitle);
    EXPECT_EQ(retrievedTag.GameTitle().Value(), expectedGameTitle);
    EXPECT_EQ(retrievedTag.DumperName().Value(), expectedDumperName);
    EXPECT_EQ(retrievedTag.Comments().Value(), expectedComments);
    EXPECT_EQ(retrievedTag.DateDumped().Value(), expectedDateDumped);
    EXPECT_EQ(retrievedTag.SongLength().Value(), expectedSongLength);
    EXPECT_EQ(retrievedTag.FadeLength().Value(), expectedFadeLength);
    EXPECT_EQ(retrievedTag.SongArtist().Value(), expectedSongArtist);
    EXPECT_EQ(retrievedTag.DefaultChannelState().Value(), 
              expectedDefaultChannelState);
    EXPECT_EQ(retrievedTag.EmulatorUsed().Value(), expectedEmulatorUsed);
    EXPECT_EQ(retrievedTag.OstTitle().Value(), expectedOstTitle);
    EXPECT_EQ(retrievedTag.OstDisc().Value(), expectedOstDisc);
    EXPECT_EQ(retrievedTag.OstTrack().Value(), expectedOstTrack);
    EXPECT_EQ(retrievedTag.PublisherName().Value(), expectedPublisherName);
    EXPECT_EQ(retrievedTag.CopyrightYear().Value(), expectedCopyrightYear);
    EXPECT_EQ(retrievedTag.IntroLength().Value(), expectedIntroLength);
    EXPECT_EQ(retrievedTag.LoopLength().Value(), expectedLoopLength);
    EXPECT_EQ(retrievedTag.EndLength().Value(), expectedEndLength);
    EXPECT_EQ(retrievedTag.MutedVoices().Value(), expectedMutedVoices);
    EXPECT_EQ(retrievedTag.LoopTimes().Value(), expectedLoopTimes);
    EXPECT_EQ(retrievedTag.PreampLevel().Value(), expectedPreampLevel);

    EXPECT_EQ(retrievedRam.Size(), expectedRam.Size());
    EXPECT_EQ(retrievedDspRegisters.Size(), expectedDspRegisters.Size());
    EXPECT_EQ(retrievedUnused.Size(), expectedUnused.Size());
    EXPECT_EQ(retrievedExtraRam.Size(), expectedExtraRam.Size());

    bool allRamBytesMatch = AllBytesMatch(expectedRam, retrievedRam);
    bool allDspBytesMatch = AllBytesMatch(expectedDspRegisters, 
                                          retrievedDspRegisters);
    bool allUnusedBytesMatch = AllBytesMatch(expectedUnused, retrievedUnused);
    bool allExtraRamBytesMatch = AllBytesMatch(expectedExtraRam, 
                                               retrievedExtraRam);

    EXPECT_EQ(allRamBytesMatch, true);
    EXPECT_EQ(allDspBytesMatch, true);
    EXPECT_EQ(allUnusedBytesMatch, true);
    EXPECT_EQ(allExtraRamBytesMatch, true);
}

void FileTests::TestFileLoadsAndSavesProperly(bool useLongTagValues)
{
    const std::string appendValue{ " (MOD)" };

    Spc::File file("test.spc", mockFileStream);

    // We need to first simulate loading the file to populate the File's fields, 
    // then we can test modifying the data and saving it properly.
    TestFileLoadsProperly(file, useLongTagValues);

    Spc::Id666::Tag tag = file.Tag();
    expectedSongTitle = expectedSongTitle + appendValue;
    expectedGameTitle = expectedGameTitle + appendValue;
    expectedDumperName = expectedDumperName + appendValue;
    expectedComments = expectedComments + appendValue;
    expectedDateDumped = alternateExpectedDateDumped;
    expectedSongLength = std::to_string(std::stoi(expectedSongLength) + 1);
    expectedFadeLength = std::to_string(std::stoi(expectedFadeLength) + 1);
    expectedSongArtist = expectedSongArtist + appendValue;
    expectedDefaultChannelState = alternateExpectedDefaultChannelState;
    expectedEmulatorUsed = alternateExpectedEmulatorUsed;
    expectedOstTitle = expectedOstTitle + appendValue;
    expectedOstDisc = std::to_string(std::stoi(expectedOstDisc) + 1);
    expectedOstTrack = alternateExpectedOstTrack;
    expectedPublisherName = expectedPublisherName + appendValue;
    expectedCopyrightYear = std::to_string(std::stoi(expectedCopyrightYear) + 1);
    expectedIntroLength = std::to_string(std::stoi(expectedIntroLength) + 1);
    expectedLoopLength = std::to_string(std::stoi(expectedLoopLength) + 1);
    expectedEndLength = std::to_string(std::stoi(expectedEndLength) + 1);
    expectedMutedVoices = alternateExpectedMutedVoices;
    expectedLoopTimes = std::to_string(std::stoi(expectedLoopTimes) + 1);
    expectedPreampLevel = std::to_string(std::stoi(expectedPreampLevel) + 1);
    tag.SetSongTitle(expectedSongTitle);
    tag.SetGameTitle(expectedGameTitle);
    tag.SetDumperName(expectedDumperName);
    tag.SetComments(expectedComments);
    tag.SetDateDumped(expectedDateDumped);
    tag.SetSongLength(expectedSongLength);
    tag.SetFadeLength(expectedFadeLength);
    tag.SetSongArtist(expectedSongArtist);
    tag.SetDefaultChannelState(expectedDefaultChannelState);
    tag.SetEmulatorUsed(expectedEmulatorUsed);
    tag.SetOstTitle(expectedOstTitle);
    tag.SetOstDisc(expectedOstDisc);
    tag.SetOstTrack(expectedOstTrack);
    tag.SetPublisherName(expectedPublisherName);
    tag.SetCopyrightYear(expectedCopyrightYear);
    tag.SetIntroLength(expectedIntroLength);
    tag.SetLoopLength(expectedLoopLength);
    tag.SetEndLength(expectedEndLength);
    tag.SetMutedVoices(expectedMutedVoices);
    tag.SetLoopTimes(expectedLoopTimes);
    tag.SetPreampLevel(expectedPreampLevel);
    file.SetTag(tag);

    MockFileWrites(useLongTagValues);

    file.Save();
}

TEST_F(FileTests, InitializesFileProperly)
{
    Spc::File file("test.spc", mockFileStream);

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
    Spc::File file("test.spc", mockFileStream);
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

TEST_F(FileTests, SetsAndRetrievesTagProperly)
{
    Spc::File file("test.spc", mockFileStream);
    Spc::Id666::Tag tag;

    tag.SetSongTitle(expectedSongTitle);
    tag.SetGameTitle(expectedGameTitle);
    tag.SetDumperName(expectedDumperName);
    tag.SetComments(expectedComments);
    tag.SetDateDumped(expectedDateDumped);
    tag.SetSongLength(expectedSongLength);
    tag.SetFadeLength(expectedFadeLength);
    tag.SetSongArtist(expectedSongArtist);
    tag.SetDefaultChannelState(expectedDefaultChannelState);
    tag.SetEmulatorUsed(expectedEmulatorUsed);
    tag.SetOstTitle(expectedOstTitle);

    file.SetTag(tag);
    Spc::Id666::Tag retrievedTag = file.Tag();

    EXPECT_EQ(retrievedTag.SongTitle().Value(), expectedSongTitle);
    EXPECT_EQ(retrievedTag.GameTitle().Value(), expectedGameTitle);
    EXPECT_EQ(retrievedTag.DumperName().Value(), expectedDumperName);
    EXPECT_EQ(retrievedTag.Comments().Value(), expectedComments);
    EXPECT_EQ(retrievedTag.DateDumped().Value(), expectedDateDumped);
    EXPECT_EQ(retrievedTag.SongLength().Value(), expectedSongLength);
    EXPECT_EQ(retrievedTag.FadeLength().Value(), expectedFadeLength);
    EXPECT_EQ(retrievedTag.SongArtist().Value(), expectedSongArtist);
    EXPECT_EQ(retrievedTag.DefaultChannelState().Value(), 
              expectedDefaultChannelState);
    EXPECT_EQ(retrievedTag.EmulatorUsed().Value(), expectedEmulatorUsed);

    // We set at least one field that is part of the extended data, so ensure
    // it's there.
    EXPECT_EQ(retrievedTag.OstTitle().Value(), expectedOstTitle);
}

TEST_F(FileTests, SetsAndRetrievesRamProperly)
{
    Spc::File file("test.spc", mockFileStream);
    Binary::BufferStream ram{ Spc::ramInfo.size };

    for (size_t i = 0; i < Spc::ramInfo.size; i++)
    {
        ram.RawData()[i] = static_cast<char>(i % 256);
    }

    file.SetRam(ram);
    Binary::BufferStream retrievedRam = file.Ram();

    ASSERT_EQ(retrievedRam.Size(), Spc::ramInfo.size);

    bool allBytesMatch = true;

    for (size_t i = 0; i < Spc::ramInfo.size; i++)
    {
        if (retrievedRam.RawData()[i] != static_cast<char>(i % 256))
        {
            allBytesMatch = false;
            break;
        }
    }

    EXPECT_EQ(allBytesMatch, true);
}

TEST_F(FileTests, SetsAndRetrievesDspRegistersProperly)
{
    Spc::File file("test.spc", mockFileStream);
    Binary::BufferStream dspRegisters{ Spc::dspRegistersInfo.size };

    for (size_t i = 0; i < Spc::dspRegistersInfo.size; i++)
    {
        dspRegisters.RawData()[i] = static_cast<char>(i % 256);
    }

    file.SetDspRegisters(dspRegisters);
    Binary::BufferStream retrievedDspRegisters = file.DspRegisters();

    ASSERT_EQ(retrievedDspRegisters.Size(), Spc::dspRegistersInfo.size);

    bool allBytesMatch = true;

    for (size_t i = 0; i < Spc::dspRegistersInfo.size; i++)
    {
        if (retrievedDspRegisters.RawData()[i] != static_cast<char>(i % 256))
        {
            allBytesMatch = false;
            break;
        }
    }

    EXPECT_EQ(allBytesMatch, true);
}

TEST_F(FileTests, SetsAndRetrievesUnusedProperly)
{
    Spc::File file("test.spc", mockFileStream);
    Binary::BufferStream unused{ Spc::unusedInfo.size };

    for (size_t i = 0; i < Spc::unusedInfo.size; i++)
    {
        unused.RawData()[i] = static_cast<char>(i % 256);
    }

    file.SetUnused(unused);
    Binary::BufferStream retrievedUnused = file.Unused();

    ASSERT_EQ(retrievedUnused.Size(), Spc::unusedInfo.size);

    bool allBytesMatch = true;

    for (size_t i = 0; i < Spc::unusedInfo.size; i++)
    {
        if (retrievedUnused.RawData()[i] != static_cast<char>(i % 256))
        {
            allBytesMatch = false;
            break;
        }
    }

    EXPECT_EQ(allBytesMatch, true);
}

TEST_F(FileTests, SetsAndRetrievesExtraRamProperly)
{
    Spc::File file("test.spc", mockFileStream);
    Binary::BufferStream extraRam{ Spc::extraRamInfo.size };

    for (size_t i = 0; i < Spc::extraRamInfo.size; i++)
    {
        extraRam.RawData()[i] = static_cast<char>(i % 256);
    }

    file.SetExtraRam(extraRam);
    Binary::BufferStream retrievedExtraRam = file.ExtraRam();

    ASSERT_EQ(retrievedExtraRam.Size(), Spc::extraRamInfo.size);

    bool allBytesMatch = true;

    for (size_t i = 0; i < Spc::extraRamInfo.size; i++)
    {
        if (retrievedExtraRam.RawData()[i] != static_cast<char>(i % 256))
        {
            allBytesMatch = false;
            break;
        }
    }

    EXPECT_EQ(allBytesMatch, true);
}

TEST_F(FileTests, LoadsAndSavesFileProperly)
{
    TestFileLoadsAndSavesProperly(false);
}

TEST_F(FileTests, LoadsAndSavesFileProperlyWithLongTagValues)
{
    TestFileLoadsAndSavesProperly(true);
}