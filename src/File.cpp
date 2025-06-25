// File.cpp - Declares the File class.
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

#include "File.h"

using namespace Spc;

void Spc::PadItem(ExtendedTagItem* item)
{
    auto size = std::static_pointer_cast<NumericField>(item->data);

    if (size->Value() % 4 != 0)
    {
        size_t paddingSize = 1;

        while ((size->Value() + paddingSize) % 4 != 0)
            paddingSize++;

        item->padding = std::make_shared<TextField>(
            "<padding>", extendedTagOffset, paddingSize);
    }
}

TextField File::SongTitle() const
{
    return GetField<TextField>(binaryTag.songTitle,
                               textTag.songTitle, 
                               extendedTag.songName.get());
}

TextField File::GameTitle() const
{
    return GetField<TextField>(binaryTag.gameTitle,
                               textTag.gameTitle, 
                               extendedTag.gameName.get());
}

TextField File::DumperName() const
{
    return GetField<TextField>(binaryTag.dumperName,
                               textTag.dumperName, 
                               extendedTag.dumperName.get());
}

TextField File::Comments() const
{
    return GetField<TextField>(binaryTag.comments,
                               textTag.comments, 
                               extendedTag.comments.get());
}

DateField File::DateDumped() const
{
    return GetField<DateField>(binaryTag.dateDumped,
                               textTag.dateDumped, 
                               extendedTag.dateDumped.get());
}

NumericField File::SongLength() const
{
    return GetField<NumericField>(binaryTag.songLength, textTag.songLength);
}

NumericField File::FadeLength() const
{
    return GetField<NumericField>(binaryTag.fadeLength, textTag.fadeLength);
}

TextField File::SongArtist() const
{
    return GetField<TextField>(binaryTag.songArtist, 
                               textTag.songArtist, 
                               extendedTag.artistName.get());
}

NumericField File::DefaultChannelState() const
{
    return GetField<NumericField>(binaryTag.defaultChannelState, 
                                  textTag.defaultChannelState);
}

EmulatorField File::EmulatorUsed() const
{
    return GetField<EmulatorField>(binaryTag.emulatorUsed, 
                                   textTag.emulatorUsed, 
                                   extendedTag.emulatorUsed.get());
}

TextField File::OstTitle() const
{
    return GetField<TextField>(extendedTag.ostTitle.get(), 
                               extendedOSTTitleID, 
                               1);
}

NumericField File::OstDisc() const
{
    return GetField<NumericField>(extendedTag.ostDisc.get(),
                                  extendedOSTDiscID,
                                  4);
}

TrackField File::OstTrack() const
{
    return GetField<TrackField>(extendedTag.ostTrack.get(), 
                                extendedOSTTrackID, 
                                1);
}

TextField File::PublisherName() const
{
    return GetField<TextField>(extendedTag.publisherName.get(), 
                               extendedPublisherNameID, 
                               1);
}

NumericField File::CopyrightYear() const
{
    return GetField<NumericField>(extendedTag.copyrightYear.get(), 
                                  extendedCopyrightYearID, 
                                  1);
}

NumericField File::IntroLength() const
{
    return GetField<NumericField>(extendedTag.introLength.get(), 
                                  extendedIntroLengthID, 
                                  1);
}

NumericField File::LoopLength() const
{
    return GetField<NumericField>(extendedTag.loopLength.get(), 
                                  extendedLoopLengthID, 
                                  1);
}

NumericField File::EndLength() const
{
    return GetField<NumericField>(extendedTag.endLength.get(), 
                                  extendedEndLengthID, 1);
}

BinaryField File::MutedVoices() const
{
    return GetField<BinaryField>(extendedTag.mutedVoices.get(), 
                                 extendedMutedVoicesID, 
                                 1);
}

NumericField File::LoopTimes() const
{
    return GetField<NumericField>(extendedTag.loopTimes.get(), 
                                  extendedLoopTimesID, 
                                  1);
}

NumericField File::PreampLevel() const
{
    return GetField<NumericField>(extendedTag.preampLevel.get(), 
                                  extendedPreampLevelID, 
                                  1);
}

void File::SetSongTitle(std::string value)
{
    SetCommand<TextField> command;
    command.binaryField = &binaryTag.songTitle;
    command.textField = &textTag.songTitle;
    command.extendedID = extendedSongNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<TextField>(command, extendedTag.songName);
}

void File::SetGameTitle(std::string value)
{
    SetCommand<TextField> command;
    command.binaryField = &binaryTag.gameTitle;
    command.textField = &textTag.gameTitle;
    command.extendedID = extendedGameNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<TextField>(command, extendedTag.gameName);
}

void File::SetDumperName(std::string value)
{
    SetCommand<TextField> command;
    command.binaryField = &binaryTag.dumperName;
    command.textField = &textTag.dumperName;
    command.extendedID = extendedDumperNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<TextField>(command, extendedTag.dumperName);
}

void File::SetComments(std::string value)
{
    SetCommand<TextField> command;
    command.binaryField = &binaryTag.comments;
    command.textField = &textTag.comments;
    command.extendedID = extendedCommentsID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<TextField>(command, extendedTag.comments);
}

void File::SetDateDumped(std::string value)
{
    if (tagType == TagType::Binary)
        binaryTag.dateDumped.SetBinaryValue(value);
    else
        textTag.dateDumped.SetTextValue(value);
}

void File::SetSongLength(std::string value)
{
    SetCommand<NumericField> command;
    command.binaryField = &binaryTag.songLength;
    command.textField = &textTag.songLength;
    command.value = value;
    NumericField* songLength;
    SetField<NumericField>(command, songLength);
}

void File::SetFadeLength(std::string value)
{
    SetCommand<NumericField> command;
    command.binaryField = &binaryTag.fadeLength;
    command.textField = &textTag.fadeLength;
    command.value = value;
    NumericField* fadeLength;
    SetField<NumericField>(command, fadeLength);
}

void File::SetSongArtist(std::string value)
{
    SetCommand<TextField> command;
    command.binaryField = &binaryTag.songArtist;
    command.textField = &textTag.songArtist;
    command.extendedID = extendedArtistNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<TextField>(command, extendedTag.artistName);
}

void File::SetDefaultChannelState(std::string value)
{
    SetCommand<NumericField> command;
    command.binaryField = &binaryTag.defaultChannelState;
    command.textField = &textTag.defaultChannelState;
    command.value = value;
    NumericField* defaultChannelState;
    SetField<NumericField>(command, defaultChannelState);
}

void File::SetEmulatorUsed(std::string value)
{
    std::string numericValue{ "0" };
    std::string v{ value };
    std::transform(v.begin(), v.end(), v.begin(), [](char c)
    {
        return std::toupper(c);
    });

    if (v == "UNKNOWN")
        numericValue = "0";
    else if (v == "ZSNES")
        numericValue = "1";
    else if (v == "SNES9X")
        numericValue = "2";
    else
        return;

    SetCommand<NumericField> command;
    command.binaryField = &binaryTag.emulatorUsed;
    command.textField = &textTag.emulatorUsed;
    command.value = numericValue;
    NumericField* emulatorUsed;
    SetField<NumericField>(command, emulatorUsed);
}

void File::SetOstTitle(std::string value)
{
    SetCommand<TextField> command;
    command.extendedID = extendedOSTTitleID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetExtendedItem<TextField>(command, extendedTag.ostTitle);
}

void File::SetOstDisc(std::string value)
{
    SetCommand<NumericField> command;
    command.extendedID = extendedOSTDiscID;
    command.extendedType = extendedTypeDataInHeader;
    command.value = value;
    SetExtendedItem<NumericField>(command, extendedTag.ostDisc);
}

void File::SetOstTrack(std::string value)
{
    SetCommand<TrackField> command;
    command.extendedID = extendedOSTTrackID;
    command.extendedType = extendedTypeDataInHeader;
    command.value = value;
    SetExtendedItem<TrackField>(command, extendedTag.ostTrack);
}

void File::SetPublisherName(std::string value)
{
    SetCommand<TextField> command;
    command.extendedID = extendedPublisherNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetExtendedItem<TextField>(command, extendedTag.publisherName);
}

void File::SetCopyrightYear(std::string value)
{
    SetCommand<NumericField> command;
    command.extendedID = extendedCopyrightYearID;
    command.extendedType = extendedTypeDataInHeader;
    command.value = value;
    SetExtendedItem<NumericField>(command, extendedTag.copyrightYear);
}

void File::SetIntroLength(std::string value)
{
    SetCommand<NumericField> command;
    command.extendedID = extendedIntroLengthID;
    command.extendedType = extendedTypeInteger;
    command.value = value;
    SetExtendedItem<NumericField>(command, extendedTag.introLength);
}

void File::SetLoopLength(std::string value)
{
    SetCommand<NumericField> command;
    command.extendedID = extendedLoopLengthID;
    command.extendedType = extendedTypeInteger;
    command.value = value;
    SetExtendedItem<NumericField>(command, extendedTag.loopLength);
}

void File::SetEndLength(std::string value)
{
    SetCommand<NumericField> command;
    command.extendedID = extendedEndLengthID;
    command.extendedType = extendedTypeInteger;
    command.value = value;
    SetExtendedItem<NumericField>(command, extendedTag.endLength);
}

void File::SetMutedVoices(std::string value)
{
    SetCommand<BinaryField> command;
    command.extendedID = extendedMutedVoicesID;
    command.extendedType = extendedTypeDataInHeader;
    command.value = value;
    SetExtendedItem<BinaryField>(command, extendedTag.mutedVoices);
}

void File::SetLoopTimes(std::string value)
{
    SetCommand<BinaryField> command;
    command.extendedID = extendedLoopTimesID;
    command.extendedType = extendedTypeDataInHeader;
    command.value = value;
    SetExtendedItem<BinaryField>(command, extendedTag.loopTimes);
}

void File::SetPreampLevel(std::string value)
{
    SetCommand<NumericField> command;
    command.extendedID = extendedPreampLevelID;
    command.extendedType = extendedTypeInteger;
    command.value = value;
    SetExtendedItem<NumericField>(command, extendedTag.preampLevel);
}

bool File::Load()
{
    // Initialize the extended tag; sets all members to nulltpr.
    extendedTag = ExtendedTag();

    FileStream file{ fileName };
    file.Open(Binary::FileMode::Read);

    if (!file.IsOpen())
        return false;

    file.Read(&header);

    if (file.HeaderContainsTag())
    {
        headerContainsTag = true;
        tagType = file.TagType();

        if (tagType == TagType::Binary)
        {
            file.Read(&binaryTag);
        }
        else
        {
            file.Read(&textTag);

            if (tagType == TagType::TextMixed)
            {
                textTag.songLength.SetType(NumericType::Binary);
                textTag.fadeLength.SetType(NumericType::Binary);
            }
        }
    }

    file.Read(&spcRam);
    file.Read(&dspRegisters);
    file.Read(&unused);
    file.Read(&extraRam);

    if (file.HasExtendedTag())
    {
        hasExtendedTag = true;
        file.Read(&extendedTagHeader);
        std::string id = extendedTagHeader.id.Value();
        std::string size = extendedTagHeader.dataSize.ToString();
        size_t sizeRemaining = extendedTagHeader.dataSize.Value();

        while (sizeRemaining > 0)
        {
            auto item = std::make_shared<ExtendedTagItem>();
            file.Read(item.get());

            switch (item->type->Value())
            {
                case extendedTypeDataInHeader:
                    item->data->SetLabel(
                        extendedFieldLabels.at(item->id->Value()));
                    sizeRemaining -= item->Size();
                    LoadHeaderItem(item);
                    break;
                case extendedTypeString:
                {
                    item->data->SetLabel("Item Length");
                    auto data = std::static_pointer_cast<NumericField>(
                        item->data);
                    size_t dataSize = data->Value();
                    sizeRemaining -= item->Size();
                    sizeRemaining -= dataSize;
                    LoadTextItem(item, file);
                    PadItem(item.get());

                    if (item->padding != nullptr)
                    {
                        file.Read(item->padding.get());
                        sizeRemaining -= item->padding->Size();
                    }

                    break;
                }
                case extendedTypeInteger:
                {
                    item->data->SetLabel("Item Length");
                    sizeRemaining -= item->Size();
                    auto data = std::static_pointer_cast<NumericField>(
                        item->data);
                    sizeRemaining -= data->Value();
                    LoadNumericItem(item, file);                    
                    break;
                }
                default:
                    return false;
            }
        }
    }

    hasLoaded = true;
    return true;
}

bool File::Save()
{
    return Save(fileName);
}

bool File::Save(std::string outFileName)
{
    if (!hasLoaded)
        return false;

    FileStream stream{ outFileName };
    stream.Open(Binary::FileMode::Write);

    if (!stream.IsOpen())
        return false;

    stream.Write(&header);

    if (tagType == TagType::Binary)
        stream.Write(&binaryTag);
    else
        stream.Write(&textTag);

    stream.Write(&spcRam);
    stream.Write(&dspRegisters);
    stream.Write(&unused);
    stream.Write(&extraRam);

    if (hasExtendedTag)
    {
        extendedTagHeader.dataSize.SetValue(extendedTag.Size());
        stream.Write(&extendedTagHeader);
        stream.Write(&extendedTag);
    }

    return true;
}

void File::LoadHeaderItem(std::shared_ptr<ExtendedTagItem> item)
{
    switch (item->id->Value())
    {
        case extendedEmulatorUsedID:
        {
            std::string label = extendedFieldLabels.at(item->id->Value());
            auto data = std::make_shared<EmulatorField>(
                label, 
                extendedTagOffset, 
                extendedTagDataSize);
            std::memcpy(data->Data(), item->data->Data(), extendedTagDataSize); 
            item->data = data;
            extendedTag.emulatorUsed = item;
            break;
        }
        case extendedOSTDiscID:
            extendedTag.ostDisc = item;
            break;
        case extendedOSTTrackID:
        {
            std::string label = extendedFieldLabels.at(item->id->Value());
            auto data = std::make_shared<TrackField>(label, 
                                                        extendedTagOffset, 
                                                        extendedTagDataSize);
            std::memcpy(data->Data(), item->data->Data(), extendedTagDataSize); 
            item->data = data;
            extendedTag.ostTrack = item;
            break;
        }
        case extendedCopyrightYearID:
            extendedTag.copyrightYear = item;
            break;
        case extendedMutedVoicesID:
        {
            std::string label = extendedFieldLabels.at(item->id->Value());
            auto data = std::make_shared<BinaryField>(label, 
                                                         extendedTagOffset, 
                                                         extendedTagDataSize);
            std::memcpy(data->Data(), item->data->Data(), extendedTagDataSize); 
            item->data = data;
            extendedTag.mutedVoices = item;
            break;
        }
        case extendedLoopTimesID:
            extendedTag.loopTimes = item;
            break;
    }
}

void File::LoadTextItem(std::shared_ptr<ExtendedTagItem> item, 
                        FileStream& stream)
{
    auto data = std::static_pointer_cast<NumericField>(item->data);
    const uintmax_t size{ data->Value() };
    const uintmax_t id{ item->id->Value() };

    switch (id)
    {
        case extendedSongNameID:
            item->extendedData = InitExtendedField<TextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.songName = item;
            break;
        case extendedGameNameID:
            item->extendedData = InitExtendedField<TextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.gameName = item;
            break;
        case extendedArtistNameID:
            item->extendedData = InitExtendedField<TextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.artistName = item;
            break;
        case extendedDumperNameID:
            item->extendedData = InitExtendedField<TextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.dumperName = item;
            break;
        case extendedCommentsID:
            item->extendedData = InitExtendedField<TextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.comments = item;
            break;
        case extendedOSTTitleID:
            item->extendedData = InitExtendedField<TextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.ostTitle = item;
            break;
        case extendedPublisherNameID:
            item->extendedData = InitExtendedField<TextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.publisherName = item;
            break;
    }
}

void File::LoadNumericItem(std::shared_ptr<ExtendedTagItem> item, 
                           FileStream& stream)
{
    //constexpr uintmax_t offset{ extendedTagOffset };
    auto data = std::static_pointer_cast<NumericField>(item->data);
    const uintmax_t size{ data->Value() };
    const uintmax_t id{ item->id->Value() };

    switch (id)
    {
        case extendedDateDumpedID:
            item->extendedData = InitExtendedField<DateField>(id, size);
            extendedTag.dateDumped = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedIntroLengthID:
            item->extendedData = InitExtendedField<NumericField>(id, size);
            extendedTag.introLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedLoopLengthID:
            item->extendedData = InitExtendedField<NumericField>(id, size);
            extendedTag.loopLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedEndLengthID:
            item->extendedData = InitExtendedField<NumericField>(id, size);
            extendedTag.endLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedFadeLengthID:
            item->extendedData = InitExtendedField<NumericField>(id, size);
            extendedTag.fadeLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedPreampLevelID:
            item->extendedData = InitExtendedField<NumericField>(id, size);
            extendedTag.preampLevel = item;
            stream.Read(item->extendedData.get());
            break;
    }
}

void File::FileNameToTag(std::string pattern)
{
    if (pattern.find('%') == std::string::npos)
        throw std::invalid_argument{ "Pattern does not contain tokens" };

    StringTokenizer tokenizer{ pattern };
    std::vector<std::shared_ptr<StringToken>> tokens = 
        tokenizer.Tokenize(fileName);

    for (std::shared_ptr<StringToken> token : tokens)
    {
        if (token->Name() == "song")
            SetSongTitle(token->Value());
        else if (token->Name() == "game")
            SetGameTitle(token->Value());
        else if (token->Name() == "artist")
            SetSongArtist(token->Value());
        else if (token->Name() == "track")
            SetOstTrack(token->Value());
        else
            throw std::invalid_argument{ "Unrecognized token name" };
    }

    Save();
}

void File::TagToFileName(std::string pattern)
{
    if (pattern.find('%') == std::string::npos)
        throw std::invalid_argument{ "Pattern does not contain tokens" };

    StringTokenizer tokenizer{ pattern };
    std::vector<std::shared_ptr<StringSegment>> segs = tokenizer.Segments();
    std::stringstream fileNameStream;

    for (std::shared_ptr<StringSegment> seg : segs)
    {
        if (seg->SegmentType() == StringSegmentType::Delimiter)
        {
            auto delimeter = std::static_pointer_cast<StringDelimiter>(seg);
            fileNameStream << delimeter->Value();
        }
        else
        {
            auto token = std::static_pointer_cast<StringToken>(seg);
            
            if (token->Name() == "song")
            {
                fileNameStream << SongTitle().Value();
            }
            else if (token->Name() == "game")
            {
                fileNameStream << GameTitle().Value();
            }
            else if (token->Name() == "artist")
            {
                fileNameStream << SongArtist().Value();
            }
            else if (token->Name() == "track")
            {
                fileNameStream << std::setw(2) << std::setfill('0') 
                               << OstTrack().ToString();
            }
            else
            {
                throw std::invalid_argument{ "Unsupported token name" };
            }
        }
    }

    Save(RemoveInvalidChars(fileNameStream.str()));
}

std::string Spc::RemoveInvalidChars(std::string fileName)
{
    std::stringstream cleanFileName;

    for (int i = 0; i < fileName.length(); i++)
    {
        char c = fileName[i];

        if (c == '<' || c == '>' || c == ':' || c == '"' || c == '/' || 
            c == '\\' || c == '|' || c == '?' || c == '*')
        {
            continue;
        }
        else
        {
            cleanFileName << c;
        }
    }

    return cleanFileName.str();
}