// Tag.cpp - Defines the Spc::Id666::Tag class.
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
    DateField dateDumped{ "Date Dumped", dateDumpedInfo.binary };
    NumericField songLength{ "Song Length (seconds)", songLengthInfo.binary };
    NumericField fadeLength{ "Fade Length (ms)", fadeLengthInfo.binary };
    TextField songArtist{ "Song Artist", songArtistInfo.binary };
    TextField reserved{ "Reserved", reservedInfo.binary };
    fieldData->SetPosition(dateDumpedInfo.binary.offset - tagOffset);
    fieldData->Read(&dateDumped);
    fieldData->SetPosition(songLengthInfo.binary.offset - tagOffset);
    fieldData->Read(&songLength);
    fieldData->SetPosition(fadeLengthInfo.binary.offset - tagOffset);
    fieldData->Read(&fadeLength);
    fieldData->SetPosition(songArtistInfo.binary.offset - tagOffset);
    fieldData->Read(&songArtist);
    fieldData->SetPosition(reservedInfo.binary.offset - tagOffset);
    fieldData->Read(&reserved);

    if (!dateDumped.IsText() || !songLength.IsText() || !fadeLength.IsText())
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
    return *ReadExtendedTextField<TextField>("Song Title", 
                                             songTitleInfo, 
                                             extendedData->songTitle.get());
}

TextField Tag::GameTitle() const 
{
    return *ReadExtendedTextField<TextField>("Game Title", 
                                             gameTitleInfo, 
                                             extendedData->gameTitle.get());
}

TextField Tag::DumperName() const 
{
    return *ReadExtendedTextField<TextField>("Dumper Name", 
                                             dumperNameInfo, 
                                             extendedData->dumperName.get());
}

TextField Tag::Comments() const 
{
    return *ReadExtendedTextField<TextField>("Comments", 
                                             commentsInfo, 
                                             extendedData->comments.get());
}

DateField Tag::DateDumped() const 
{
    std::shared_ptr<Extended::Item> item = extendedData->dateDumped;

    // Date Dumped is stored as an 32-bit integer in the extended area, so
    // we need to read it differently from the standard date dumped field.
    std::shared_ptr<NumericField> dateDumpedInt;
    dateDumpedInt = ReadExtendedField<NumericField>("Date Dumped", item.get());

    if (item != nullptr)
    {
        // Since a date dumped was found in the extended area, convert it to
        // a standard DateField to return.
        Spc::FieldInfo extendedInfo;
        extendedInfo.offset = Extended::dataOffset;
        extendedInfo.size = dateDumpedInfo.binary.size;
        DateField dateDumped{ "Date Dumped", extendedInfo };
        dateDumpedInt->CopyRawDataTo(&dateDumped);
        return dateDumped;
    }
    else
    {
        return *ReadNumericField<DateField>("Date Dumped", dateDumpedInfo);
    }
}

NumericField Tag::SongLength() const 
{   
    return *ReadNumericField<NumericField>("Song Length (seconds)", 
                                           songLengthInfo);
}

NumericField Tag::FadeLength() const 
{
    std::shared_ptr<Extended::Item> item = extendedData->fadeLength;
    
    // Fade length is stored as an 32-bit integer in the extended area, so
    // we need to read it differently from the standard fade length field.
    std::shared_ptr<NumericField> fadeLengthInt;
    fadeLengthInt = ReadExtendedField<NumericField>("Fade Length (ticks)", 
                                                    item.get());

    if (item != nullptr)
    {
        return *fadeLengthInt;
    }
    else
    {
        return *ReadNumericField<NumericField>("Fade Length (ms)", 
                                               fadeLengthInfo);
    }
}

TextField Tag::SongArtist() const 
{
    return *ReadExtendedTextField<TextField>("Song Artist", 
                                             songArtistInfo, 
                                             extendedData->songArtist.get());
}

BinaryField Tag::DefaultDisabledChannels() const 
{
    return *ReadTextField<BinaryField>("Default Disabled Channels", 
                                       defaultDisabledChannelsInfo);
}

EmulatorField Tag::EmulatorUsed() const
{
    std::shared_ptr<Extended::Item> item = extendedData->emulatorUsed;
    
    // Emulator used is stored as an 16-bit integer in the extended area, so
    // we need to read it differently from the standard emulator used field.
    std::shared_ptr<NumericField> emulatorUsedInt;
    emulatorUsedInt = ReadExtendedField<NumericField>("Emulator Used", 
                                                      item.get());

    if (item != nullptr)
    {
        // Since emulator used was found in the extended area, convert it to
        // a standard EmulatorField to return.
        Spc::FieldInfo extendedInfo;
        extendedInfo.offset = Extended::dataOffset;
        extendedInfo.size = emulatorUsedInfo.binary.size;
        EmulatorField emulatorUsed{ "Emulator Used", extendedInfo };
        emulatorUsedInt->CopyRawDataTo(&emulatorUsed);
        return emulatorUsed;
    }
    else
    {
        return *ReadNumericField<EmulatorField>("Emulator Used", 
                                                emulatorUsedInfo);
    }
}

TextField Tag::OstTitle() const 
{
    return *ReadExtendedField<TextField>("OST Title", 
                                         extendedData->ostTitle.get());
}

NumericField Tag::OstDisc() const
{
    return *ReadExtendedField<NumericField>("OST Disc", 
                                            extendedData->ostDisc.get());
}

TrackField Tag::OstTrack() const
{
    return *ReadExtendedField<TrackField>("OST Track", 
                                          extendedData->ostTrack.get());
}

TextField Tag::PublisherName() const 
{
    return *ReadExtendedField<TextField>("Publisher Name", 
                                         extendedData->publisherName.get());
}

NumericField Tag::CopyrightYear() const
{
    return *ReadExtendedField<NumericField>("Copyright Year", 
                                            extendedData->copyrightYear.get());
}

NumericField Tag::IntroLength() const 
{
    return *ReadExtendedField<NumericField>("Intro Length (ticks)", 
                                            extendedData->introLength.get());
}

NumericField Tag::LoopLength() const 
{
    return *ReadExtendedField<NumericField>("Loop Length (ticks)", 
                                            extendedData->loopLength.get());
}

NumericField Tag::EndLength() const 
{
    return *ReadExtendedField<NumericField>("End Length (ticks)", 
                                            extendedData->endLength.get());
}

BinaryField Tag::MutedVoices() const 
{
    std::shared_ptr<Extended::Item> item = extendedData->mutedVoices;
    
    // Muted voices is stored as an 16-bit integer in the extended area, so
    // we need to read it differently from the standard BinaryField field.
    std::shared_ptr<NumericField> mutedVoicesInt;
    mutedVoicesInt = ReadExtendedField<NumericField>("Muted Voices*", 
                                                     item.get());

    if (item != nullptr)
    {
        // Since muted voices was found in the extended area, convert it to
        // a standard BinaryField to return.
        Spc::FieldInfo extendedInfo{ Extended::dataOffset, 1 };
        BinaryField mutedVoices{ "Muted Voices*", extendedInfo };
        mutedVoicesInt->CopyRawDataTo(&mutedVoices);
        return mutedVoices;
    }
    else
    {
        Spc::FieldInfo errorInfo{ 0, 1 };
        return BinaryField{ "Muted Voices*", errorInfo };
    }
}

NumericField Tag::LoopTimes() const 
{
    return *ReadExtendedField<NumericField>("Loop Times", 
                                            extendedData->loopTimes.get());
}

NumericField Tag::PreampLevel() const 
{
    return *ReadExtendedField<NumericField>("Preamp Level", 
                                            extendedData->preampLevel.get());
}

void Tag::SetSongTitle(std::string value) 
{
    WriteExtendedTextField<TextField>(songTitleInfo,
                                      Extended::songTitleInfo, 
                                      &extendedData->songTitle,
                                      value);
}

void Tag::SetGameTitle(std::string value) 
{
    WriteExtendedTextField<TextField>(gameTitleInfo,
                                      Extended::gameTitleInfo, 
                                      &extendedData->gameTitle,
                                      value);
}

void Tag::SetDumperName(std::string value) 
{
    WriteExtendedTextField<TextField>(dumperNameInfo,
                                      Extended::dumperNameInfo, 
                                      &extendedData->dumperName,
                                      value);
}

void Tag::SetComments(std::string value) 
{
    WriteExtendedTextField<TextField>(commentsInfo,
                                      Extended::commentsInfo, 
                                      &extendedData->comments,
                                      value);
}

void Tag::SetDateDumped(std::string value) 
{
    WriteNumericField<DateField>(dateDumpedInfo,
                                 value);
}

void Tag::SetSongLength(std::string value) 
{
    constexpr int min{ 0 };
    constexpr int max{ 959 };
    CheckRange(value, min, max);
    WriteNumericField<NumericField>(songLengthInfo, value);
}

void Tag::SetFadeLength(std::string value)
{
    // TODO: Consider adding logic to write to the extended area. It is not yet
    // clear under what conditions this field would be used
    // as opposed to the standard one. Would need to know the maximum number of
    // ticks vs milliseconds.
    constexpr int min{ 0 };
    constexpr int max{ 59999 };
    CheckRange(value, min, max);
    WriteNumericField<NumericField>(fadeLengthInfo, value);
}

void Tag::SetSongArtist(std::string value) 
{
    WriteExtendedTextField<TextField>(songArtistInfo,
                                      Extended::songArtistInfo, 
                                      &extendedData->songArtist,
                                      value);
}

void Tag::SetDefaultDisabledChannels(std::string value) 
{
    if (value.size() != bitsPerByte)
    {
        throw std::invalid_argument(
            "Default disabled channels value must be 8 bits");
    }

    WriteNumericField<BinaryField>(defaultDisabledChannelsInfo, value);
}

void Tag::SetEmulatorUsed(std::string value) 
{
    WriteNumericField<EmulatorField>(emulatorUsedInfo, value);
}

void Tag::SetOstTitle(std::string value) 
{
    WriteExtendedStringField<TextField>(Extended::ostTitleInfo, 
                                        &extendedData->ostTitle,
                                        value);
}

void Tag::SetOstDisc(std::string value) 
{
    constexpr int min{ 0 };
    constexpr int max{ 9 };
    CheckRange(value, min, max);
    WriteExtendedLengthField<NumericField>(Extended::ostDiscInfo, 
                                           &extendedData->ostDisc,
                                           value);
}

void Tag::SetOstTrack(std::string value)
{
    std::string numericPart;
    std::string charSuffix;

    size_t i = 0;
    
    while (i < value.size() && isdigit(value[i])) 
    {
        numericPart += value[i];
        ++i;
    }

    if (i < value.size()) 
    {
        charSuffix = value.substr(i);
    }

    constexpr int min{ 0 };
    constexpr int max{ 99 };
    CheckRange(numericPart, min, max);

    if (charSuffix.size() > 1)
    {
        throw std::invalid_argument("Invalid OST track value: " + value);
    }

    WriteExtendedLengthField<TrackField>(Extended::ostTrackInfo, 
                                         &extendedData->ostTrack,
                                         value);
}

void Tag::SetPublisherName(std::string value)
{
    WriteExtendedStringField<TextField>(Extended::publisherNameInfo, 
                                        &extendedData->publisherName,
                                        value);
}

void Tag::SetCopyrightYear(std::string value) 
{
    int intValue = std::stoi(value);

    if (intValue < 0)
    {
        throw std::invalid_argument("Value " + value + " must be >= 0");
    }
    
    WriteExtendedLengthField<NumericField>(Extended::copyrightYearInfo, 
                                           &extendedData->copyrightYear,
                                           value);
}

void Tag::SetIntroLength(std::string value) 
{
    CheckRange(value, 0, maxTicks);
    WriteExtendedIntField<NumericField>(Extended::introLengthInfo, 
                                        &extendedData->introLength,
                                        value);
}

void Tag::SetLoopLength(std::string value) 
{
    CheckRange(value, 0, maxTicks);
    WriteExtendedIntField<NumericField>(Extended::loopLengthInfo, 
                                        &extendedData->loopLength,
                                        value);
}

void Tag::SetEndLength(std::string value) 
{
    CheckRange(value, 0, maxTicks);
    WriteExtendedIntField<NumericField>(Extended::endLengthInfo, 
                                        &extendedData->endLength,
                                        value);
}

void Tag::SetMutedVoices(std::string value)
{
    if (value.size() != bitsPerByte)
    {
        throw std::invalid_argument("Muted voices value must be 8 bits");
    }

    WriteExtendedLengthField<BinaryField>(Extended::mutedVoicesInfo, 
                                          &extendedData->mutedVoices,
                                          value);
}

void Tag::SetLoopTimes(std::string value) 
{
    CheckRange(value, 0, maxLoopTimes);
    WriteExtendedLengthField<NumericField>(Extended::loopTimesInfo, 
                                           &extendedData->loopTimes,
                                           value);
}

void Tag::SetPreampLevel(std::string value) 
{
    CheckRange(value, minPreampLevel, maxPreampLevel);
    WriteExtendedIntField<NumericField>(Extended::preampLevelInfo, 
                                        &extendedData->preampLevel,
                                        value);
}

void Tag::ReadField(Field* field) const
{
    size_t originalPosition = fieldData->Position();
    fieldData->SetPosition(field->Offset() - tagOffset);
    fieldData->Read(field);
    fieldData->SetPosition(originalPosition);
}

void Tag::WriteField(Field* field)
{
    size_t originalPosition = fieldData->Position();
    fieldData->SetPosition(field->Offset() - tagOffset);
    fieldData->Write(field);
    fieldData->SetPosition(originalPosition);
}

void Spc::Id666::CheckRange(std::string value, int min, int max)
{
    int intValue = std::stoi(value);

    if (intValue < min || intValue > max)
    {
        throw std::out_of_range("Value " + value + 
                                " is out of range [" + 
                                std::to_string(min) + ", " + 
                                std::to_string(max) + "]");
    }
}