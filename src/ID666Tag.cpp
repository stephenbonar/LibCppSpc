// ID666Tag.cpp - Defines the ID666Tag class.
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

#include "ID666Tag.h"

using namespace Spc;

ID666Tag::ID666Tag()
{
    fieldData = std::make_shared<Binary::BufferStream>(id666TagSize);
    extendedData = std::make_shared<ID666ExtendedData>();
}

TagType ID666Tag::DetermineType() const
{
    // Preserve the existing position as we have to jump around the tag data to
    // determine if the tag is binary and we need to get back to where we were.
    uintmax_t previousPosition = fieldData->Position();


    // Read in the fields that will help us determine the tag type.
    fieldData->SetPosition(0);
    Spc::DateField dateDumped{ "Date Dumped", 
                               Spc::dateDumpedInfo.binaryOffset, 
                               Spc::dateDumpedInfo.binarySize };
    Spc::NumericField songLength{ "Song Length (seconds)", 
                                  Spc::songLengthInfo.binaryOffset, 
                                  Spc::songLengthInfo.binarySize };
    Spc::NumericField fadeLength{ "Fade Length (ms)", 
                                  Spc::fadeLengthInfo.binaryOffset,
                                  Spc::fadeLengthInfo.binarySize };
    Spc::TextField songArtist{ "Song Artist",
                                  Spc::songArtistInfo.binaryOffset,
                                  Spc::songArtistInfo.binarySize };
    Spc::TextField reserved{ "Reserved", 
                             Spc::reservedInfo.binaryOffset,
                             Spc::reservedInfo.binarySize };
    fieldData->SetPosition(
        Spc::dateDumpedInfo.binaryOffset - Spc::id666TagOffset);
    fieldData->Read(&dateDumped);
    fieldData->SetPosition(
        Spc::songLengthInfo.binaryOffset - Spc::id666TagOffset);
    fieldData->Read(&songLength);
    fieldData->SetPosition(
        Spc::fadeLengthInfo.binaryOffset - Spc::id666TagOffset);
    fieldData->Read(&fadeLength);
    fieldData->SetPosition(
        Spc::songArtistInfo.binaryOffset - Spc::id666TagOffset);
    fieldData->Read(&songArtist);
    fieldData->SetPosition(
        Spc::reservedInfo.binaryOffset - Spc::id666TagOffset);
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

TextField ID666Tag::SongTitle() const 
{
    return *ReadField<TextField>("Song Title", 
                                Spc::songTitleInfo, 
                                extendedData->songName.get());
}

TextField ID666Tag::GameTitle() const 
{
    return *ReadField<TextField>("Game Title", 
                                Spc::gameTitleInfo, 
                                extendedData->gameName.get());
}

TextField ID666Tag::DumperName() const 
{
    return *ReadField<TextField>("Dumper Name", 
                                Spc::dumperNameInfo, 
                                extendedData->dumperName.get());
}

TextField ID666Tag::Comments() const 
{
    return *ReadField<TextField>("Comments", 
                                Spc::commentsInfo, 
                                extendedData->comments.get());
}

DateField ID666Tag::DateDumped() const 
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
            Spc::extendedTagOffset, 
            Spc::dateDumpedInfo.binarySize 
        };
        std::memcpy(dateDumped.RawData(), 
                    dateDumpedInt->RawData(), 
                    dateDumpedInt->Size());
        return dateDumped;
    }
    else
    {
        return *ReadField<DateField>("Date Dumped", 
                                    Spc::dateDumpedInfo);
    }
}

NumericField ID666Tag::SongLength() const 
{   
    return *ReadField<NumericField>("Song Length (seconds)", 
                                    Spc::songLengthInfo);
}

NumericField ID666Tag::FadeLength() const 
{
    return *ReadField<NumericField>("Fade Length (ms)", 
                                    Spc::fadeLengthInfo);
}

TextField ID666Tag::SongArtist() const 
{
    return *ReadField<TextField>("Song Artist", 
                                Spc::songArtistInfo, 
                                extendedData->artistName.get());
}

NumericField ID666Tag::DefaultChannelState() const 
{
    return *ReadField<NumericField>("Default Channel State", 
                                    Spc::defaultChannelStateInfo);
}

EmulatorField ID666Tag::EmulatorUsed() const
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
            Spc::extendedTagOffset, 
            Spc::emulatorUsedInfo.binarySize 
        };
        std::memcpy(emulatorUsed.RawData(), 
                    emulatorUsedInt->RawData(), 
                    emulatorUsed.Size());
        return emulatorUsed;
    }
    else
    {
        return *ReadField<EmulatorField>("Emulator Used", 
                                         Spc::emulatorUsedInfo);
    }
}

TextField ID666Tag::OstTitle() const 
{
    return *ReadField<TextField>("OST Title", 
                                 extendedData->ostTitle.get());
}

NumericField ID666Tag::OstDisc() const
{
    return *ReadField<NumericField>("OST Disc", 
                                    extendedData->ostDisc.get());
}

TrackField ID666Tag::OstTrack() const
{
    return *ReadField<TrackField>("OST Track", 
                                  extendedData->ostTrack.get());
}

TextField ID666Tag::PublisherName() const 
{
    return *ReadField<TextField>("Publisher Name", 
                                 extendedData->publisherName.get());
}

NumericField ID666Tag::CopyrightYear() const
{
    return *ReadField<NumericField>("Copyright Year", 
                                    extendedData->copyrightYear.get());
}

NumericField ID666Tag::IntroLength() const 
{
    return *ReadField<NumericField>("Intro Length (ticks)", 
                                    extendedData->introLength.get());
}

NumericField ID666Tag::LoopLength() const 
{
    return *ReadField<NumericField>("Loop Length (ticks)", 
                                    extendedData->loopLength.get());
}

NumericField ID666Tag::EndLength() const 
{
    return *ReadField<NumericField>("End Length (ticks)", 
                                    extendedData->endLength.get());
}

BinaryField ID666Tag::MutedVoices() const 
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
            Spc::extendedTagOffset, 
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

NumericField ID666Tag::LoopTimes() const 
{
    return *ReadField<NumericField>("Loop Times", 
                                    extendedData->loopTimes.get());
}

NumericField ID666Tag::PreampLevel() const 
{
    return *ReadField<NumericField>("Preamp Level", 
                                    extendedData->preampLevel.get());
}

void ID666Tag::SetSongTitle(std::string value) {}

void ID666Tag::SetGameTitle(std::string value) {}

void ID666Tag::SetDumperName(std::string value) {}

void ID666Tag::SetComments(std::string value) {}

void ID666Tag::SetDateDumped(std::string value) {}

void ID666Tag::SetSongLength(std::string value) {}

void ID666Tag::SetFadeLength(std::string value) {}

void ID666Tag::SetSongArtist(std::string value) {}

void ID666Tag::SetDefaultChannelState(std::string value) {}

void ID666Tag::SetEmulatorUsed(std::string value) {}

void ID666Tag::SetOstTitle(std::string value) {}

void ID666Tag::SetOstDisc(std::string value) {}

void ID666Tag::SetOstTrack(std::string value) {}

void ID666Tag::SetPublisherName(std::string value) {}

void ID666Tag::SetCopyrightYear(std::string value) {}

void ID666Tag::SetIntroLength(std::string value) {}

void ID666Tag::SetLoopLength(std::string value) {}

void ID666Tag::SetEndLength(std::string value) {}

void ID666Tag::SetMutedVoices(std::string value) {}

void ID666Tag::SetLoopTimes(std::string value) {}

void ID666Tag::SetPreampLevel(std::string value) {}