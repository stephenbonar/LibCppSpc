// SpcFile.cpp - Declares the SpcFile class.
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

#include "SpcFile.h"

void PadItem(ID666ExtendedItem* item)
{
    auto size = std::static_pointer_cast<SpcNumericField>(item->data);

    if (size->Value() % 4 != 0)
    {
        size_t paddingSize = 1;

        while ((size->Value() + paddingSize) % 4 != 0)
            paddingSize++;

        item->padding = std::make_shared<SpcTextField>(
            "<padding>", extendedTagOffset, paddingSize);
    }
}

SpcTextField SpcFile::SongTitle() const
{
    return GetField<SpcTextField>(binaryTag.songTitle,
                                  textTag.songTitle, 
                                  extendedTag.songName.get());
}

SpcTextField SpcFile::GameTitle() const
{
    return GetField<SpcTextField>(binaryTag.gameTitle,
                                  textTag.gameTitle, 
                                  extendedTag.gameName.get());
}

SpcTextField SpcFile::DumperName() const
{
    return GetField<SpcTextField>(binaryTag.dumperName,
                                  textTag.dumperName, 
                                  extendedTag.dumperName.get());
}

SpcTextField SpcFile::Comments() const
{
    return GetField<SpcTextField>(binaryTag.comments,
                                  textTag.comments, 
                                  extendedTag.comments.get());
}

SpcDateField SpcFile::DateDumped() const
{
    return GetField<SpcDateField>(binaryTag.dateDumped,
                                  textTag.dateDumped, 
                                  extendedTag.dateDumped.get());
}

SpcNumericField SpcFile::SongLength() const
{
    return GetField<SpcNumericField>(binaryTag.songLength, textTag.songLength);
}

SpcNumericField SpcFile::FadeLength() const
{
    return GetField<SpcNumericField>(binaryTag.fadeLength, textTag.fadeLength);
}

SpcTextField SpcFile::SongArtist() const
{
    return GetField<SpcTextField>(binaryTag.songArtist, 
                                  textTag.songArtist, 
                                  extendedTag.artistName.get());
}

SpcNumericField SpcFile::DefaultChannelState() const
{
    return GetField<SpcNumericField>(binaryTag.defaultChannelState, 
                                     textTag.defaultChannelState);
}

SpcEmulatorField SpcFile::EmulatorUsed() const
{
    return GetField<SpcEmulatorField>(binaryTag.emulatorUsed, 
                                      textTag.emulatorUsed, 
                                      extendedTag.emulatorUsed.get());
}

SpcTextField SpcFile::OstTitle() const
{
    return GetField<SpcTextField>(extendedTag.ostTitle.get(), 
                                  extendedOSTTitleID, 
                                  1);
}

SpcNumericField SpcFile::OstDisc() const
{
    return GetField<SpcNumericField>(extendedTag.ostDisc.get(),
                                     extendedOSTDiscID,
                                     4);
}

SpcTrackField SpcFile::OstTrack() const
{
    return GetField<SpcTrackField>(extendedTag.ostTrack.get(), 
                                   extendedOSTTrackID, 
                                   1);
}

SpcTextField SpcFile::PublisherName() const
{
    return GetField<SpcTextField>(extendedTag.publisherName.get(), 
                                  extendedPublisherNameID, 
                                  1);
}

SpcNumericField SpcFile::CopyrightYear() const
{
    return GetField<SpcNumericField>(extendedTag.copyrightYear.get(), 
                                     extendedCopyrightYearID, 
                                     1);
}

SpcNumericField SpcFile::IntroLength() const
{
    return GetField<SpcNumericField>(extendedTag.introLength.get(), 
                                     extendedIntroLengthID, 
                                     1);
}

SpcNumericField SpcFile::LoopLength() const
{
    return GetField<SpcNumericField>(extendedTag.loopLength.get(), 
                                     extendedLoopLengthID, 
                                     1);
}

SpcNumericField SpcFile::EndLength() const
{
    return GetField<SpcNumericField>(extendedTag.endLength.get(), extendedEndLengthID, 1);
}

SpcBinaryField SpcFile::MutedVoices() const
{
    return GetField<SpcBinaryField>(extendedTag.mutedVoices.get(), 
                                    extendedMutedVoicesID, 
                                    1);
}

SpcNumericField SpcFile::LoopTimes() const
{
    return GetField<SpcNumericField>(extendedTag.loopTimes.get(), 
                                     extendedLoopLengthID, 
                                     1);
}

SpcNumericField SpcFile::PreampLevel() const
{
    return GetField<SpcNumericField>(extendedTag.preampLevel.get(), 
                                     extendedPreampLevelID, 
                                     1);
}

void SpcFile::SetSongTitle(std::string value)
{
    SetCommand<SpcTextField> command;
    command.binaryField = &binaryTag.songTitle;
    command.textField = &textTag.songTitle;
    command.extendedID = extendedSongNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<SpcTextField>(command, extendedTag.songName);
}

void SpcFile::SetGameTitle(std::string value)
{
    SetCommand<SpcTextField> command;
    command.binaryField = &binaryTag.gameTitle;
    command.textField = &textTag.gameTitle;
    command.extendedID = extendedGameNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<SpcTextField>(command, extendedTag.gameName);
}

void SpcFile::SetDumperName(std::string value)
{
    SetCommand<SpcTextField> command;
    command.binaryField = &binaryTag.dumperName;
    command.textField = &textTag.dumperName;
    command.extendedID = extendedDumperNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<SpcTextField>(command, extendedTag.dumperName);
}

void SpcFile::SetComments(std::string value)
{
    SetCommand<SpcTextField> command;
    command.binaryField = &binaryTag.comments;
    command.textField = &textTag.comments;
    command.extendedID = extendedCommentsID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<SpcTextField>(command, extendedTag.comments);
}

void SpcFile::SetDateDumped(std::string value)
{
    if (tagType == ID666TagType::Binary)
        binaryTag.dateDumped.SetBinaryValue(value);
    else
        textTag.dateDumped.SetTextValue(value);
}

void SpcFile::SetSongLength(std::string value)
{
    SetCommand<SpcNumericField> command;
    command.binaryField = &binaryTag.songLength;
    command.textField = &textTag.songLength;
    command.value = value;
    SpcNumericField* songLength;
    SetField<SpcNumericField>(command, songLength);
}

void SpcFile::SetFadeLength(std::string value)
{
    SetCommand<SpcNumericField> command;
    command.binaryField = &binaryTag.fadeLength;
    command.textField = &textTag.fadeLength;
    command.value = value;
    SpcNumericField* fadeLength;
    SetField<SpcNumericField>(command, fadeLength);
}

void SpcFile::SetSongArtist(std::string value)
{
    SetCommand<SpcTextField> command;
    command.binaryField = &binaryTag.songArtist;
    command.textField = &textTag.songArtist;
    command.extendedID = extendedArtistNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<SpcTextField>(command, extendedTag.artistName);
}

void SpcFile::SetDefaultChannelState(std::string value)
{
    SetCommand<SpcNumericField> command;
    command.binaryField = &binaryTag.defaultChannelState;
    command.textField = &textTag.defaultChannelState;
    command.value = value;
    SpcNumericField* defaultChannelState;
    SetField<SpcNumericField>(command, defaultChannelState);
}

void SpcFile::SetEmulatorUsed(std::string value)
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

    SetCommand<SpcNumericField> command;
    command.binaryField = &binaryTag.emulatorUsed;
    command.textField = &textTag.emulatorUsed;
    command.value = numericValue;
    SpcNumericField* emulatorUsed;
    SetField<SpcNumericField>(command, emulatorUsed);
}

void SpcFile::SetOstTitle(std::string value)
{
    SetCommand<SpcTextField> command;
    command.extendedID = extendedOSTTitleID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetExtendedItem<SpcTextField>(command, extendedTag.ostTitle);
}

void SpcFile::SetOstDisc(std::string value)
{
    SetCommand<SpcNumericField> command;
    command.extendedID = extendedOSTDiscID;
    command.extendedType = extendedTypeDataInHeader;
    command.value = value;
    SetExtendedItem<SpcNumericField>(command, extendedTag.ostDisc);
}

void SpcFile::SetOstTrack(std::string value)
{
    SetCommand<SpcTrackField> command;
    command.extendedID = extendedOSTTrackID;
    command.extendedType = extendedTypeDataInHeader;
    command.value = value;
    SetExtendedItem<SpcTrackField>(command, extendedTag.ostTrack);
}

void SpcFile::SetPublisherName(std::string value)
{
    SetCommand<SpcTextField> command;
    command.extendedID = extendedPublisherNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetExtendedItem<SpcTextField>(command, extendedTag.publisherName);
}

void SpcFile::SetCopyrightYear(std::string value)
{
    SetCommand<SpcNumericField> command;
    command.extendedID = extendedCopyrightYearID;
    command.extendedType = extendedTypeDataInHeader;
    command.value = value;
    SetExtendedItem<SpcNumericField>(command, extendedTag.copyrightYear);
}

void SpcFile::SetIntroLength(std::string value)
{
    SetCommand<SpcNumericField> command;
    command.extendedID = extendedIntroLengthID;
    command.extendedType = extendedTypeInteger;
    command.value = value;
    SetExtendedItem<SpcNumericField>(command, extendedTag.introLength);
}

void SpcFile::SetLoopLength(std::string value)
{
    SetCommand<SpcNumericField> command;
    command.extendedID = extendedLoopLengthID;
    command.extendedType = extendedTypeInteger;
    command.value = value;
    SetExtendedItem<SpcNumericField>(command, extendedTag.loopLength);
}

void SpcFile::SetEndLength(std::string value)
{
    SetCommand<SpcNumericField> command;
    command.extendedID = extendedEndLengthID;
    command.extendedType = extendedTypeInteger;
    command.value = value;
    SetExtendedItem<SpcNumericField>(command, extendedTag.endLength);
}

void SpcFile::SetMutedVoices(std::string value)
{
    SetCommand<SpcBinaryField> command;
    command.extendedID = extendedMutedVoicesID;
    command.extendedType = extendedTypeDataInHeader;
    command.value = value;
    SetExtendedItem<SpcBinaryField>(command, extendedTag.mutedVoices);
}

void SpcFile::SetLoopTimes(std::string value)
{
    SetCommand<SpcBinaryField> command;
    command.extendedID = extendedLoopTimesID;
    command.extendedType = extendedTypeDataInHeader;
    command.value = value;
    SetExtendedItem<SpcBinaryField>(command, extendedTag.loopTimes);
}

void SpcFile::SetPreampLevel(std::string value)
{
    SetCommand<SpcNumericField> command;
    command.extendedID = extendedPreampLevelID;
    command.extendedType = extendedTypeInteger;
    command.value = value;
    SetExtendedItem<SpcNumericField>(command, extendedTag.preampLevel);
}

bool SpcFile::Load()
{
    // Initialize the extended tag; sets all members to nulltpr.
    extendedTag = ID666ExtendedTag();

    SpcFileStream file{ fileName };
    file.Open(Binary::FileMode::Read);

    if (!file.IsOpen())
        return false;

    file.Read(&header);

    if (file.HeaderContainsTag())
    {
        headerContainsTag = true;
        tagType = file.TagType();

        if (tagType == ID666TagType::Binary)
        {
            file.Read(&binaryTag);
        }
        else
        {
            file.Read(&textTag);

            if (tagType == ID666TagType::TextMixed)
            {
                textTag.songLength.SetType(SpcNumericType::Binary);
                textTag.fadeLength.SetType(SpcNumericType::Binary);
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
            auto item = std::make_shared<ID666ExtendedItem>();
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
                    auto data = std::static_pointer_cast<SpcNumericField>(
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
                    auto data = std::static_pointer_cast<SpcNumericField>(
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

bool SpcFile::Save()
{
    return Save(fileName);
}

bool SpcFile::Save(std::string outFileName)
{
    if (!hasLoaded)
        return false;

    SpcFileStream stream{ outFileName };
    stream.Open(Binary::FileMode::Write);

    if (!stream.IsOpen())
        return false;

    stream.Write(&header);

    if (tagType == ID666TagType::Binary)
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

void SpcFile::LoadHeaderItem(std::shared_ptr<ID666ExtendedItem> item)
{
    switch (item->id->Value())
    {
        case extendedEmulatorUsedID:
        {
            std::string label = extendedFieldLabels.at(item->id->Value());
            auto data = std::make_shared<SpcEmulatorField>(
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
            auto data = std::make_shared<SpcTrackField>(label, 
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
            auto data = std::make_shared<SpcBinaryField>(label, 
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

void SpcFile::LoadTextItem(std::shared_ptr<ID666ExtendedItem> item, 
                           SpcFileStream& stream)
{
    auto data = std::static_pointer_cast<SpcNumericField>(item->data);
    const uintmax_t size{ data->Value() };
    const uintmax_t id{ item->id->Value() };

    switch (id)
    {
        case extendedSongNameID:
            item->extendedData = InitExtendedField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.songName = item;
            break;
        case extendedGameNameID:
            item->extendedData = InitExtendedField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.gameName = item;
            break;
        case extendedArtistNameID:
            item->extendedData = InitExtendedField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.artistName = item;
            break;
        case extendedDumperNameID:
            item->extendedData = InitExtendedField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.dumperName = item;
            break;
        case extendedCommentsID:
            item->extendedData = InitExtendedField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.comments = item;
            break;
        case extendedOSTTitleID:
            item->extendedData = InitExtendedField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.ostTitle = item;
            break;
        case extendedPublisherNameID:
            item->extendedData = InitExtendedField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.publisherName = item;
            break;
    }
}

void SpcFile::LoadNumericItem(std::shared_ptr<ID666ExtendedItem> item, 
                              SpcFileStream& stream)
{
    //constexpr uintmax_t offset{ extendedTagOffset };
    auto data = std::static_pointer_cast<SpcNumericField>(item->data);
    const uintmax_t size{ data->Value() };
    const uintmax_t id{ item->id->Value() };

    switch (id)
    {
        case extendedDateDumpedID:
            item->extendedData = InitExtendedField<SpcDateField>(id, size);
            extendedTag.dateDumped = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedIntroLengthID:
            item->extendedData = InitExtendedField<SpcNumericField>(id, size);
            extendedTag.introLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedLoopLengthID:
            item->extendedData = InitExtendedField<SpcNumericField>(id, size);
            extendedTag.loopLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedEndLengthID:
            item->extendedData = InitExtendedField<SpcNumericField>(id, size);
            extendedTag.endLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedFadeLengthID:
            item->extendedData = InitExtendedField<SpcNumericField>(id, size);
            extendedTag.fadeLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedPreampLevelID:
            item->extendedData = InitExtendedField<SpcNumericField>(id, size);
            extendedTag.preampLevel = item;
            stream.Read(item->extendedData.get());
            break;
    }
}

void SpcFile::FileNameToTag(std::string pattern)
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

void SpcFile::TagToFileName(std::string pattern)
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

std::string RemoveInvalidChars(std::string fileName)
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