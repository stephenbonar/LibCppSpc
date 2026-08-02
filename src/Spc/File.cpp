// File.cpp - Defines the Spc::File class methods.
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

#include "Spc/File.h"

#include "Spc/Id666/Extended/ItemInfo.h"
#include "Spc/Id666/Extended/Item.h"
#include "Spc/TextField.h"

using namespace Spc;

const char* extSizeError{ "Extended item size exceeds remaining chunk size." };
const char* invalidTypeError{ "Invalid extended item type detected." };
const char* unopenedFileError{ "File is not open." };
const char* nullStreamError{ "File stream not initialized." };
const char* invalidIdError{ "Invalid extended item ID detected." };

namespace
{
    void TryCloseStream(Binary::FileStream* stream) noexcept
    {
        if (stream == nullptr || !stream->IsOpen())
        {
            return;
        }

        try
        {
            stream->Close();
        }
        catch (...)
        {
            // Never mask the original exception with a close failure.
        }
    }

    bool IsSafeFileName(std::string_view fileName)
    {
        if (fileName.empty() || fileName == "." || fileName == "..")
        {
            return false;
        }

        if (fileName.find('/') != std::string_view::npos ||
            fileName.find('\\') != std::string_view::npos ||
            fileName.find(':') != std::string_view::npos)
        {
            return false;
        }

        std::filesystem::path p{ fileName };

        if (p.has_parent_path() || p.has_root_path() || p.is_absolute())
        {
            return false;
        }

        return true;
    }
}

void File::Load()
{
    if (fileStream == nullptr)
    {
        throw FileOperationException(nullStreamError);
    }

    fileStream->Open(Binary::FileMode::Read);

    if (!fileStream->IsOpen())
    {
        throw FileOperationException(unopenedFileError);
    }

    try
    {
        fileStream->Read(header);
        fileStream->Read(*tag.FieldData());
        fileStream->Read(ram);
        fileStream->Read(dspRegisters);
        fileStream->Read(unused);
        fileStream->Read(extraRam);

        std::shared_ptr<Binary::ChunkHeader> extendedHeader =
            fileStream->FindNextChunk(Id666::Extended::chunkId);

        if (extendedHeader != nullptr)
        {
            // The value of the chunk's dataSize field is the size of all items
            // (sub-chunks) contained within the chunk, minus the size of the
            // chunk header itself.
            size_t sizeRemaining = extendedHeader->dataSize.Value();

            // When sizeRemaining is less than the minimum size of an item
            // (the header), we know we're done reading items from the chunk,
            // but until then, keep reading items from the chunk.
            while (sizeRemaining >= Id666::Extended::itemHeaderSize)
            {
                auto item = std::make_shared<Spc::Id666::Extended::Item>();
                fileStream->Read(*item);

                const size_t itemSize = item->Size();

                // If the item size exceeds the remaining size of the chunk,
                // then we know the file is corrupt because the last item's
                // size should fit within the remaining size.
                if (itemSize > sizeRemaining)
                {
                    throw FileCorruptException(extSizeError);
                }

                sizeRemaining -= itemSize;

                const uint32_t type = item->type->ToUInt32();

                if (type == Spc::Id666::Extended::stringType)
                {
                    LoadStringItem(item, sizeRemaining);
                }
                else if (type == Spc::Id666::Extended::lengthType)
                {
                    LoadLengthItem(item);
                }
                else if (type == Spc::Id666::Extended::integerType)
                {
                    LoadIntegerItem(item, sizeRemaining);
                }
                else
                {
                    throw FileCorruptException(invalidTypeError);
                }
            }
        }

        fileStream->Close();
    }
    catch (...)
    {
        TryCloseStream(fileStream.get());
        throw;
    }
}

void File::Save()
{
    if (fileStream == nullptr)
    {
        throw FileOperationException(nullStreamError);
    }

    fileStream->Open(Binary::FileMode::Write);

    if (!fileStream->IsOpen())
    {
        throw FileOperationException(unopenedFileError);
    }

    try
    {
        fileStream->Write(header);
        fileStream->Write(*tag.FieldData());
        fileStream->Write(ram);
        fileStream->Write(dspRegisters);
        fileStream->Write(unused);
        fileStream->Write(extraRam);

        std::shared_ptr<Id666::Extended::Data> extendedData = tag.ExtendedData();

        if (extendedData->Size() > 0)
        {
            Binary::ChunkHeader extendedHeader = extendedData->Header();
            fileStream->Write(extendedHeader);
            fileStream->Write(*extendedData);
        }

        fileStream->Close();
    }
    catch (...)
    {
        TryCloseStream(fileStream.get());
        throw;
    }
}

void File::LoadStringItem(std::shared_ptr<Id666::Extended::Item> item, 
                          size_t& sizeRemaining)
{
    const size_t itemDataSize = item->data->ToUInt32();
                
    // The data size should not exceed the remaining size of the
    // chunk.
    if (itemDataSize > sizeRemaining)
    {
        throw FileCorruptException(extSizeError);
    }

    Spc::FieldInfo itemDataInfo
    {
        Spc::Id666::Extended::dataOffset, itemDataSize 
    };
    item->extendedData = std::make_shared<Spc::TextField>("Extended Data",
                                                          itemDataInfo);
    fileStream->Read(*item->extendedData);
    sizeRemaining -= itemDataSize;
    LoadPadding(item, sizeRemaining);

    switch (item->id->ToUInt32())
    {
        case Spc::Id666::Extended::songTitleInfo.id:
            tag.ExtendedData()->songTitle = item;
            break;
        case Spc::Id666::Extended::gameTitleInfo.id:
            tag.ExtendedData()->gameTitle = item;
            break;
        case Spc::Id666::Extended::songArtistInfo.id:
            tag.ExtendedData()->songArtist = item;
            break;
        case Spc::Id666::Extended::dumperNameInfo.id:
            tag.ExtendedData()->dumperName = item;
            break;
        case Spc::Id666::Extended::commentsInfo.id:
            tag.ExtendedData()->comments = item;
            break;
        case Spc::Id666::Extended::ostTitleInfo.id:
            tag.ExtendedData()->ostTitle = item;
            break;
        case Spc::Id666::Extended::publisherNameInfo.id:
            tag.ExtendedData()->publisherName = item;
            break;
        default:
            throw FileCorruptException(invalidIdError);
    }
}

void File::LoadPadding(std::shared_ptr<Id666::Extended::Item> item, 
                       size_t& sizeRemaining)
{

    const size_t itemDataSize = item->data->ToUInt32();

    // Calculate the number of padding bytes needed to align the data on a 
    // 4-byte boundary. If itemDataSize is already a multiple of 4, no padding 
    // is needed (result is 0). Otherwise, subtract the remainder from 4 to get 
    // the required padding. The final % 4 ensures that if itemDataSize % 4 == 0
    // the result is 0, not 4.
    const size_t paddingSize = (4 - (itemDataSize % 4)) % 4;

    if (paddingSize > 0)
    {
        if (paddingSize > sizeRemaining)
        {
            throw FileCorruptException(extSizeError);
        }

        Spc::FieldInfo paddingInfo{ Spc::Id666::Extended::dataOffset,
                                    paddingSize };
        item->padding = std::make_shared<Spc::TextField>("Padding",
                                                         paddingInfo);
        fileStream->Read(*item->padding);
        sizeRemaining -= paddingSize;
    }
}

void File::LoadLengthItem(std::shared_ptr<Id666::Extended::Item> item)
{
    switch (item->id->ToUInt32())
    {
        case Spc::Id666::Extended::emulatorUsedInfo.id:
            tag.ExtendedData()->emulatorUsed = item;
            break;
        case Spc::Id666::Extended::ostDiscInfo.id:
            tag.ExtendedData()->ostDisc = item;
            break;
        case Spc::Id666::Extended::ostTrackInfo.id:
            tag.ExtendedData()->ostTrack = item;
            break;
        case Spc::Id666::Extended::copyrightYearInfo.id:
            tag.ExtendedData()->copyrightYear = item;
            break;
        case Spc::Id666::Extended::mutedVoicesInfo.id:
            tag.ExtendedData()->mutedVoices = item;
            break;
        case Spc::Id666::Extended::loopTimesInfo.id:
            tag.ExtendedData()->loopTimes = item;
            break;
        default:
            throw FileCorruptException(invalidIdError);
    }
}

void File::LoadIntegerItem(std::shared_ptr<Id666::Extended::Item> item, 
                           size_t& sizeRemaining)
{
    constexpr uint8_t integerSize{ 4 };

    if (sizeRemaining < integerSize)
    {
        throw FileCorruptException(extSizeError);
    }

    auto extendedData = std::make_shared<NumericField>(
        "Extended Data", 
        Spc::FieldInfo{ Spc::Id666::Extended::dataOffset, integerSize },
        Spc::NumericType::Binary);
    fileStream->Read(*extendedData);
    item->extendedData = extendedData;
    sizeRemaining -= integerSize;

    switch (item->id->ToUInt32())
    {
        case Spc::Id666::Extended::dateDumpedInfo.id:
            tag.ExtendedData()->dateDumped = item;
            break;
        case Spc::Id666::Extended::introLengthInfo.id:
            tag.ExtendedData()->introLength = item;
            break;
        case Spc::Id666::Extended::loopLengthInfo.id:
            tag.ExtendedData()->loopLength = item;
            break;
        case Spc::Id666::Extended::endLengthInfo.id:
            tag.ExtendedData()->endLength = item;
            break;
        case Spc::Id666::Extended::fadeLengthInfo.id:
            tag.ExtendedData()->fadeLength = item;
            break;
        case Spc::Id666::Extended::preampLevelInfo.id:
            tag.ExtendedData()->preampLevel = item;
            break;
        default:
            throw FileCorruptException(invalidIdError);
    }
}

bool File::TagToFileName(const std::string& pattern)
{
    std::vector<Id666::Pattern::Node> nodes = ParsePattern(pattern);
    std::stringstream stream;

    for (Id666::Pattern::Node node : nodes)
    {
        switch (node.type)
        {
            case Id666::Pattern::NodeType::Literal:
                stream << node.lexeme;
                break;
            case Id666::Pattern::NodeType::TextPlaceholder:
                if (node.lexeme == Id666::Pattern::songPlaceholder)
                {
                    stream << tag.SongTitle().Value();
                }
                else if (node.lexeme == Id666::Pattern::artistPlaceholder)
                {
                    stream << tag.SongArtist().Value();
                }
                else if (node.lexeme == Id666::Pattern::gamePlaceholder)
                {
                    stream << tag.GameTitle().Value();
                }
                else
                {
                    return false;
                }

                break;
            case Id666::Pattern::NodeType::NumericPlaceholder:
                if (node.lexeme == Id666::Pattern::discPlaceholder)
                {
                    stream << tag.OstDisc().Value();
                }
                else if (node.lexeme == Id666::Pattern::trackPlaceholder)
                {
                    stream << tag.OstTrack().Value();
                }
                else
                {
                    return false;
                }
                
                break;
            case Id666::Pattern::NodeType::End:
                break;
        }
    }

    std::filesystem::path sourcePath(path);
    std::filesystem::path destinationPath(sourcePath);
    std::string fileName = stream.str();

    if (!IsSafeFileName(fileName))
    {
        return false;
    }

    destinationPath.replace_filename(fileName);

    if (sourcePath == destinationPath)
    {
        return false;
    }

    std::error_code error;
    const bool copied = std::filesystem::copy_file(
        sourcePath,
        destinationPath,
        std::filesystem::copy_options::none,
        error);

    return copied && !error;
}

bool File::FileNameToTag(const std::string& pattern)
{
    std::vector<Id666::Pattern::Node> nodes = ParsePattern(pattern);
    std::filesystem::path p(path);
    std::string filename = p.filename().string();
    std::stringstream stream{ filename };
    bool success{ true };
    std::string songTitle;
    std::string songArtist;
    std::string gameTitle;
    std::string ostDisc;
    std::string ostTrack;
    bool hasSongTitle{ false };
    bool hasSongArtist{ false };
    bool hasGameTitle{ false };
    bool hasOstDisc{ false };
    bool hasOstTrack{ false };
    
    for (int i = 0; i < nodes.size(); i++)
    {
        Id666::Pattern::Node* nextNode{ nullptr};
        Id666::Pattern::Node node = nodes[i];

        if (i + 1 < nodes.size())
        {
            nextNode = &nodes[i + 1];
        }

        switch (node.type)
        {
            case Id666::Pattern::NodeType::Literal:
                success = MatchLiteral(stream, node);
                break;
            case Id666::Pattern::NodeType::TextPlaceholder:
            {
                std::string parsedText;
                success = MatchText(stream,
                                    filename,
                                    node,
                                    nextNode,
                                    parsedText);

                if (success)
                {
                    if (node.lexeme == Id666::Pattern::songPlaceholder)
                    {
                        songTitle = parsedText;
                        hasSongTitle = true;
                    }
                    else if (node.lexeme == Id666::Pattern::artistPlaceholder)
                    {
                        songArtist = parsedText;
                        hasSongArtist = true;
                    }
                    else if (node.lexeme == Id666::Pattern::gamePlaceholder)
                    {
                        gameTitle = parsedText;
                        hasGameTitle = true;
                    }
                }

                break;
            }
            case Id666::Pattern::NodeType::NumericPlaceholder:
            {
                std::string parsedNumeric;
                success = MatchNumeric(stream,
                                       filename,
                                       node,
                                       nextNode,
                                       parsedNumeric);

                if (success)
                {
                    if (node.lexeme == Id666::Pattern::discPlaceholder)
                    {
                        ostDisc = parsedNumeric;
                        hasOstDisc = true;
                    }
                    else if (node.lexeme == Id666::Pattern::trackPlaceholder)
                    {
                        ostTrack = parsedNumeric;
                        hasOstTrack = true;
                    }
                }

                break;
            }
            case Id666::Pattern::NodeType::End:
                success = MatchEnd(stream);
                break;
        }

        if (!success)
        {
            return false;
        }
    }

    auto applyParsedValues =
        [&](Spc::Id666::Tag& targetTag)
        {
            if (hasSongTitle)
            {
                targetTag.SetSongTitle(songTitle);
            }

            if (hasSongArtist)
            {
                targetTag.SetSongArtist(songArtist);
            }

            if (hasGameTitle)
            {
                targetTag.SetGameTitle(gameTitle);
            }

            if (hasOstDisc)
            {
                targetTag.SetOstDisc(ostDisc);
            }

            if (hasOstTrack)
            {
                targetTag.SetOstTrack(ostTrack);
            }
        };

    try
    {
        // Validate first so we don't partially mutate the file's tag.
        Spc::Id666::Tag validationTag;
        applyParsedValues(validationTag);

        applyParsedValues(tag);
    }
    catch (const std::invalid_argument&)
    {
        return false;
    }
    catch (const std::out_of_range&)
    {
        return false;
    }

    Save();

    return true;
}

bool File::MatchNumeric(std::stringstream& stream, 
                        const std::string& fileName,
                        Id666::Pattern::Node node,
                        Id666::Pattern::Node* nextNode,
                        std::string& numericString)
{
    if (nextNode == nullptr)
    {
        return false;
    }

    size_t numericStringSize{ 0 };
    std::streampos currentPos = stream.tellg();

    if (currentPos == -1)
    {
        return false;
    }

    const size_t startIndex = static_cast<size_t>(currentPos);

    if (startIndex > fileName.size())
    {
        return false;
    }

    std::string_view contentView{ fileName };
    contentView = contentView.substr(startIndex);

    if (nextNode->type == Id666::Pattern::NodeType::Literal)
    {
        size_t index = contentView.find(nextNode->lexeme);

        if (index == std::string::npos)
        {
            return false;
        }

        numericStringSize = index;
    }
    else if (nextNode->type == Id666::Pattern::NodeType::End)
    {
        numericStringSize = contentView.size();
    }
    else
    {
        return false;
    }

    if (node.lexeme != Id666::Pattern::discPlaceholder &&
        node.lexeme != Id666::Pattern::trackPlaceholder)
    {
        return false;
    }

    numericString.assign(numericStringSize, '\0');
    stream.read(numericString.data(), numericStringSize);

    if (stream.gcount() != static_cast<std::streamsize>(numericStringSize))
    {
        return false;
    }

    return true;
}

bool File::MatchText(std::stringstream& stream,
                     const std::string& fileName,
                     Id666::Pattern::Node node,
                     Id666::Pattern::Node* nextNode,
                     std::string& textString)
{
    if (nextNode == nullptr)
    {
        return false;
    }

    size_t textStringSize{ 0 };
    std::streampos currentPos = stream.tellg();

    if (currentPos == -1)
    {
        return false;
    }

    const size_t startIndex = static_cast<size_t>(currentPos);

    if (startIndex > fileName.size())
    {
        return false;
    }

    std::string_view contentView{ fileName };
    contentView = contentView.substr(startIndex);

    if (nextNode->type == Id666::Pattern::NodeType::Literal)
    {
        size_t index = contentView.find(nextNode->lexeme);

        if (index == std::string::npos)
        {
            return false;
        }

        textStringSize = index;
    }
    else if (nextNode->type == Id666::Pattern::NodeType::End)
    {
        textStringSize = contentView.size();
    }
    else
    {
        return false;
    }

    if (node.lexeme != Id666::Pattern::songPlaceholder &&
        node.lexeme != Id666::Pattern::artistPlaceholder &&
        node.lexeme != Id666::Pattern::gamePlaceholder)
    {
        return false;
    }

    textString.assign(textStringSize, '\0');
    stream.read(textString.data(), textStringSize);

    if (stream.gcount() != static_cast<std::streamsize>(textStringSize))
    {
        return false;
    }

    return true;
}

bool Spc::MatchEnd(std::stringstream& stream)
{
    if (stream.tellg() == -1 || 
        stream.tellg() == static_cast<std::streampos>(stream.str().size()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Spc::MatchLiteral(std::stringstream& stream, Id666::Pattern::Node node)
{
    if (node.type != Id666::Pattern::NodeType::Literal)
    {
        return false;
    }
    else
    {
        std::streampos currentPos = stream.tellg();
        size_t remaining{ 0 };

        if (currentPos == -1)
        {
            return false;
        }
        else
        {
            remaining = stream.str().size() - static_cast<size_t>(currentPos);
        }

        if (remaining < node.lexeme.size())
        {
            return false;
        }
        else
        {
            std::string literalString(node.lexeme.size(), '\0');
            stream.read(literalString.data(), node.lexeme.size());

            if (literalString == node.lexeme)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

std::vector<Id666::Pattern::Node> Spc::ParsePattern(std::string_view pattern)
{
    Id666::Pattern::Lexer lexer{ pattern };
    std::vector<Id666::Pattern::Token> tokens;

    do
    {
        Id666::Pattern::Token token = lexer.Lex();
        tokens.push_back(token); 
    }
    while (tokens.back().Type() != Id666::Pattern::TokenType::End);
    
    Id666::Pattern::Parser parser{ tokens };
    return parser.Parse();
}