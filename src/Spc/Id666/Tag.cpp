// Tag.cpp - Defines the Tag class.
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

#include "Spc/Id666/Tag.h"

using namespace Spc;
using namespace Spc::Id666;

Tag::Tag()
{
    fieldData = std::make_shared<Binary::BufferStream>(tagSize);
    extendedData = std::make_shared<Extended::Data>();
}

TagType Tag::DetermineType() const
{
    // Preserve the existing position as we have to jump around the tag data to
    // determine if the tag is binary and we need to get back to where we were.
    uintmax_t previousPosition = fieldData->Position();


    // Read in the fields that will help us determine the tag type.
    fieldData->SetPosition(0);
    DateField dateDumped{ "Date Dumped", 
                          dateDumpedInfo.binaryOffset, 
                          dateDumpedInfo.binarySize };
    NumericField songLength{ "Song Length (seconds)", 
                             songLengthInfo.binaryOffset, 
                             songLengthInfo.binarySize };
    NumericField fadeLength{ "Fade Length (ms)", 
                             fadeLengthInfo.binaryOffset,
                             fadeLengthInfo.binarySize };
    TextField songArtist{ "Song Artist",
                           songArtistInfo.binaryOffset,
                           songArtistInfo.binarySize };
    TextField reserved{ "Reserved", 
                        reservedInfo.binaryOffset,
                        reservedInfo.binarySize };
    fieldData->SetPosition(dateDumpedInfo.binaryOffset - tagOffset);
    fieldData->Read(&dateDumped);
    fieldData->SetPosition(songLengthInfo.binaryOffset - tagOffset);
    fieldData->Read(&songLength);
    fieldData->SetPosition(fadeLengthInfo.binaryOffset - tagOffset);
    fieldData->Read(&fadeLength);
    fieldData->SetPosition(songArtistInfo.binaryOffset - tagOffset);
    fieldData->Read(&songArtist);
    fieldData->SetPosition(reservedInfo.binaryOffset - tagOffset);
    fieldData->Read(&reserved);

    if (!dateDumped.IsText() || 
        !songLength.IsText() || 
        !fadeLength.IsText())
    {
        // While we're pretty sure we're binary at this point, let's make 
        // absolutely sure. Some older dumps use text offsets but still store
        // times as binary. Let's check the bytes that are normally unused in
        // a binary tag for any non-zero values.
        if (dateDumped.IsSet())
        {
            if (!dateDumped.HasUnusedArea())
            {
                fieldData->SetPosition(previousPosition);
                return TagType::TextMixed;
            }
        }

        // If the first byte of artist is 0 but the byte immediately
        // following is non-zero, this suggests the artist value was shifted
        // over by 1, which means we're using text tag offsets.
        if (songArtist.RawData()[0] == 0 && songArtist.RawData()[1] != 0)
        {
            fieldData->SetPosition(previousPosition);
            return TagType::TextMixed;
        }

        // The reserved bytes should also be empty if the offsets are
        // for a binary tag.
        for (int i = 0; i < reserved.Size(); i++)
        {
            if (reserved.RawData()[i] != 0)
            {
                fieldData->SetPosition(previousPosition);
                return TagType::TextMixed;
            }
        }

        // If we've made it this far, we can be pretty sure we're using
        // binary offsets.
        fieldData->SetPosition(previousPosition);
        return TagType::Binary;
    }

    fieldData->SetPosition(previousPosition);
    return TagType::Text;
}

TextField Tag::SongTitle() const 
{
    return *ReadField<TextField>("Song Title", 
                                songTitleInfo, 
                                extendedData->songTitle.get());
}

TextField Tag::GameTitle() const 
{
    return *ReadField<TextField>("Game Title", 
                                gameTitleInfo, 
                                extendedData->gameTitle.get());
}

TextField Tag::DumperName() const 
{
    return *ReadField<TextField>("Dumper Name", 
                                dumperNameInfo, 
                                extendedData->dumperName.get());
}

TextField Tag::Comments() const 
{
    return *ReadField<TextField>("Comments", 
                                commentsInfo, 
                                extendedData->comments.get());
}

DateField Tag::DateDumped() const 
{
    // Date Dumped is stored as an 32-bit integer in the extended area, so
    // we need to read it differently from the standard date dumped field.
    std::shared_ptr<NumericField> dateDumpedInt = ReadField<NumericField>(
        "Date Dumped", extendedData->dateDumped.get());

    if (dateDumpedInt != nullptr)
    {
        // Since a date dumped was found in the extended area, convert it to
        // a standard DateField to return.
        DateField dateDumped
        { 
            "Date Dumped", 
            Extended::dataOffset, 
            dateDumpedInfo.binarySize 
        };
        std::memcpy(dateDumped.RawData(), 
                    dateDumpedInt->RawData(), 
                    dateDumpedInt->Size());
        return dateDumped;
    }
    else
    {
        return *ReadField<DateField>("Date Dumped", 
                                    dateDumpedInfo);
    }
}

NumericField Tag::SongLength() const 
{   
    return *ReadField<NumericField>("Song Length (seconds)", songLengthInfo);
}

NumericField Tag::FadeLength() const 
{
    return *ReadField<NumericField>("Fade Length (ms)", fadeLengthInfo);
}

TextField Tag::SongArtist() const 
{
    return *ReadField<TextField>("Song Artist", 
                                songArtistInfo, 
                                extendedData->songArtist.get());
}

NumericField Tag::DefaultChannelState() const 
{
    return *ReadField<NumericField>("Default Channel State", 
                                    defaultChannelStateInfo);
}

EmulatorField Tag::EmulatorUsed() const
{
    // Emulator used is stored as an 16-bit integer in the extended area, so
    // we need to read it differently from the standard emulator used field.
    std::shared_ptr<NumericField> emulatorUsedInt = ReadField<NumericField>(
        "Emulator Used", extendedData->emulatorUsed.get());

    if (emulatorUsedInt != nullptr)
    {
        // Since emulator used was found in the extended area, convert it to
        // a standard EmulatorField to return.
        EmulatorField emulatorUsed
        { 
            "Emulator Used", 
            Extended::dataOffset, 
            emulatorUsedInfo.binarySize 
        };
        std::memcpy(emulatorUsed.RawData(), 
                    emulatorUsedInt->RawData(), 
                    emulatorUsed.Size());
        return emulatorUsed;
    }
    else
    {
        return *ReadField<EmulatorField>("Emulator Used", 
                                         emulatorUsedInfo);
    }
}

TextField Tag::OstTitle() const 
{
    return *ReadField<TextField>("OST Title", 
                                 extendedData->ostTitle.get());
}

NumericField Tag::OstDisc() const
{
    return *ReadField<NumericField>("OST Disc", 
                                    extendedData->ostDisc.get());
}

TrackField Tag::OstTrack() const
{
    return *ReadField<TrackField>("OST Track", 
                                  extendedData->ostTrack.get());
}

TextField Tag::PublisherName() const 
{
    return *ReadField<TextField>("Publisher Name", 
                                 extendedData->publisherName.get());
}

NumericField Tag::CopyrightYear() const
{
    return *ReadField<NumericField>("Copyright Year", 
                                    extendedData->copyrightYear.get());
}

NumericField Tag::IntroLength() const 
{
    return *ReadField<NumericField>("Intro Length (ticks)", 
                                    extendedData->introLength.get());
}

NumericField Tag::LoopLength() const 
{
    return *ReadField<NumericField>("Loop Length (ticks)", 
                                    extendedData->loopLength.get());
}

NumericField Tag::EndLength() const 
{
    return *ReadField<NumericField>("End Length (ticks)", 
                                    extendedData->endLength.get());
}

BinaryField Tag::MutedVoices() const 
{
    // Muted voices is stored as an 16-bit integer in the extended area, so
    // we need to read it differently from the standard BinaryField field.
    std::shared_ptr<NumericField> mutedVoicesInt = ReadField<NumericField>(
        "Muted Voices", extendedData->mutedVoices.get());

    if (mutedVoicesInt != nullptr)
    {
        // Since muted voices was found in the extended area, convert it to
        // a standard BinaryField to return.
        BinaryField mutedVoices
        { 
            "Muted Voices", 
            Extended::dataOffset, 
            1 
        };
        std::memcpy(mutedVoices.RawData(), 
                    mutedVoicesInt->RawData(), 
                    mutedVoices.Size());
        return mutedVoices;
    }
    else
    {
        return BinaryField{ "Muted Voices (ERROR)", 0, 1 };
    }
}

NumericField Tag::LoopTimes() const 
{
    return *ReadField<NumericField>("Loop Times", 
                                    extendedData->loopTimes.get());
}

NumericField Tag::PreampLevel() const 
{
    return *ReadField<NumericField>("Preamp Level", 
                                    extendedData->preampLevel.get());
}

void Tag::SetSongTitle(std::string value) 
{
    WriteField<TextField>(songTitleInfo,
                          Extended::songTitleInfo, 
                          &extendedData->songTitle,
                          value);
}

void Tag::SetGameTitle(std::string value) 
{
    WriteField<TextField>(gameTitleInfo,
                          Extended::gameTitleInfo, 
                          &extendedData->gameTitle,
                          value);
}

void Tag::SetDumperName(std::string value) 
{
    WriteField<TextField>(dumperNameInfo,
                          Extended::dumperNameInfo, 
                          &extendedData->dumperName,
                          value);
}

void Tag::SetComments(std::string value) 
{
    WriteField<TextField>(commentsInfo,
                          Extended::commentsInfo, 
                          &extendedData->comments,
                          value);
}

void Tag::SetDateDumped(std::string value) 
{
    if (DetermineType() == TagType::Binary)
    {
        DateField dateDumped{ "Date Dumped", 
                              dateDumpedInfo.binaryOffset, 
                              dateDumpedInfo.binarySize };
        dateDumped.SetBinaryValue(value);

        size_t previousPosition = fieldData->Position();
        fieldData->SetPosition(dateDumpedInfo.binaryOffset - tagOffset);
        fieldData->Write(&dateDumped);
        fieldData->SetPosition(previousPosition);
    }
    else
    {
        DateField dateDumped{ "Date Dumped", 
                              dateDumpedInfo.textOffset, 
                              dateDumpedInfo.textSize };
        dateDumped.SetTextValue(value);
        size_t previousPosition = fieldData->Position();
        fieldData->SetPosition(dateDumpedInfo.textOffset - tagOffset);
        fieldData->Write(&dateDumped);
        fieldData->SetPosition(previousPosition);
    }
}

void Tag::SetSongLength(std::string value) {}

void Tag::SetFadeLength(std::string value) {}

void Tag::SetSongArtist(std::string value) {}

void Tag::SetDefaultChannelState(std::string value) {}

void Tag::SetEmulatorUsed(std::string value) {}

void Tag::SetOstTitle(std::string value) {}

void Tag::SetOstDisc(std::string value) {}

void Tag::SetOstTrack(std::string value) {}

void Tag::SetPublisherName(std::string value) {}

void Tag::SetCopyrightYear(std::string value) {}

void Tag::SetIntroLength(std::string value) {}

void Tag::SetLoopLength(std::string value) {}

void Tag::SetEndLength(std::string value) {}

void Tag::SetMutedVoices(std::string value) {}

void Tag::SetLoopTimes(std::string value) {}

void Tag::SetPreampLevel(std::string value) {}