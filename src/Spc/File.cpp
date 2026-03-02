// File.cpp - Defines the File class methods.
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

#include "Spc/File.h"

#include "Spc/Id666/Extended/FieldInfo.h"
#include "Spc/Id666/Extended/Item.h"
#include "Spc/TextField.h"

using namespace Spc;

void File::Load()
{
    if (fileStream == nullptr)
    {
        return;
    }

    fileStream->Open(Binary::FileMode::Read);

    if (!fileStream->IsOpen())
    {
        return;
    }

    fileStream->Read(&header);
    fileStream->Read(tag.FieldData().get());
    fileStream->Read(&ram);
    fileStream->Read(&dspRegisters);
    fileStream->Read(&unused);
    fileStream->Read(&extraRam);

    std::shared_ptr<Binary::ChunkHeader> extendedHeader =
        fileStream->FindNextChunk("xid6");

    if (extendedHeader != nullptr)
    {
        size_t sizeRemaining = extendedHeader->dataSize.Value();
        constexpr size_t extendedItemHeaderSize = 4;

        while (sizeRemaining >= extendedItemHeaderSize)
        {
            auto item = std::make_shared<Spc::Id666::Extended::Item>();
            fileStream->Read(item.get());

            const size_t itemSize = item->Size();

            if (itemSize > sizeRemaining)
            {
                throw FileCorruptException(
                    "Extended item size exceeds remaining chunk size.");
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
                throw FileCorruptException(
                    "Invalid extended item type detected");
            }
        }
    }

    fileStream->Close();
}

void File::Save()
{
    if (fileStream == nullptr)
    {
        return;
    }

    fileStream->Open(Binary::FileMode::Write);

    if (!fileStream->IsOpen())
    {
        return;
    }

    fileStream->Write(&header);
    fileStream->Write(tag.FieldData().get());
    fileStream->Write(&ram);
    fileStream->Write(&dspRegisters);
    fileStream->Write(&unused);
    fileStream->Write(&extraRam);

    std::shared_ptr<Id666::Extended::Data> extendedData = tag.ExtendedData();

    if (extendedData->Size() > 0)
    {
        Binary::ChunkHeader extendedHeader = extendedData->Header();
        fileStream->Write(&extendedHeader);
        fileStream->Write(extendedData.get());
    }

    fileStream->Close();
}

void File::LoadStringItem(std::shared_ptr<Id666::Extended::Item> item, 
                          size_t& sizeRemaining)
{
    const size_t itemDataSize = item->data->ToUInt32();
                
    // The data size should not exceed the remaining size of the
    // chunk.
    if (itemDataSize > sizeRemaining)
    {
        throw FileCorruptException(
            "Extended item data size exceeds remaining chunk size.");
    }

    Spc::FieldInfo itemDataInfo
    {
        Spc::Id666::Extended::dataOffset, itemDataSize 
    };
    item->extendedData = std::make_shared<Spc::TextField>(
        "Extended Data",
        itemDataInfo);
    fileStream->Read(item->extendedData.get());
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
            throw FileCorruptException(
                "Invalid extended item ID for string type detected");
    }
}

void File::LoadPadding(std::shared_ptr<Id666::Extended::Item> item, 
                       size_t& sizeRemaining)
{
    const size_t itemDataSize = item->data->ToUInt32();
    const size_t paddingSize = (4 - (itemDataSize % 4)) % 4;

    if (paddingSize > 0)
    {
        if (paddingSize > sizeRemaining)
        {
            throw FileCorruptException(
                "Extended item padding size exceeds remaining chunk size.");
        }

        Spc::FieldInfo paddingInfo{ Spc::Id666::Extended::dataOffset,
                                    paddingSize };
        item->padding = std::make_shared<Spc::TextField>("Padding",
                                                         paddingInfo);
        fileStream->Read(item->padding.get());
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
            throw FileCorruptException(
                "Invalid extended item ID for length/integer type detected");
    }
}

void File::LoadIntegerItem(std::shared_ptr<Id666::Extended::Item> item, 
                           size_t& sizeRemaining)
{
    constexpr uint8_t integerSize{ 4 };

    if (sizeRemaining < integerSize)
    {
        throw FileCorruptException(
            "Extended item integer data size exceeds remaining chunk size.");
    }

    auto extendedData = std::make_shared<NumericField>(
        "Extended Data", 
        Spc::FieldInfo{ Spc::Id666::Extended::dataOffset, integerSize },
        Spc::NumericType::Binary);
    fileStream->Read(extendedData.get());
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
            throw FileCorruptException(
                "Invalid extended item ID for length/integer type detected");
    }
}

void File::TagToFileName(std::string pattern)
{

}

void File::FileNameToTag(std::string pattern)
{

}