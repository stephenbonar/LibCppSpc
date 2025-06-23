// ID666ExtendedTag.h - Defines the ID666ExtendedTag class.
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

#include "ID666ExtendedTag.h"

/*
ID666ExtendedTag::ID666ExtendedTag()
{
    fields.push_back(songName.get());
    fields.push_back(gameName.get());
    fields.push_back(artistName.get());
    fields.push_back(dumperName.get());
    fields.push_back(dateDumped.get());
    fields.push_back(emulatorUsed.get());
    fields.push_back(comments.get());
    fields.push_back(ostTitle.get());
    fields.push_back(ostDisc.get());
    fields.push_back(ostTrack.get());
    fields.push_back(publisherName.get());
    fields.push_back(copyrightYear.get());
    fields.push_back(introLength.get());
    fields.push_back(loopLength.get());
    fields.push_back(endLength.get());
    fields.push_back(fadeLength.get());
    fields.push_back(mutedVoices.get());
    fields.push_back(loopTimes.get());
    fields.push_back(preampLevel.get());
}*/

Binary::ChunkHeader ID666ExtendedTag::Header() const
{
    Binary::ChunkHeader header;
    header.id.SetValue("xid6");
    header.dataSize.SetValue(Size());
    return header;
}

std::vector<SpcField*> ID666ExtendedTag::SpcFields() const
{
    std::vector<SpcField*> nonNullFields;
    std::vector<ID666ExtendedItem*> items;

    items.push_back(songName.get());
    items.push_back(gameName.get());
    items.push_back(artistName.get());
    items.push_back(dumperName.get());
    items.push_back(dateDumped.get());
    items.push_back(emulatorUsed.get());
    items.push_back(comments.get());
    items.push_back(ostTitle.get());
    items.push_back(ostDisc.get());
    items.push_back(ostTrack.get());
    items.push_back(publisherName.get());
    items.push_back(copyrightYear.get());
    items.push_back(introLength.get());
    items.push_back(loopLength.get());
    items.push_back(endLength.get());
    items.push_back(fadeLength.get());
    items.push_back(mutedVoices.get());
    items.push_back(loopTimes.get());
    items.push_back(preampLevel.get());

    for (ID666ExtendedItem* item : items)
    {
        if (item != nullptr)
        {
            std::vector<SpcField*> fields = item->SpcFields();

            for (SpcField* field : fields)
                nonNullFields.push_back(field);
        }
    }

    return nonNullFields;
}

/*
void ID666ExtendedTag::PadFields()
{
    constexpr int boundary32Bits{ 4 };
    paddedFields.clear();

    for (SpcField* field : fields)
    {
        paddedFields.push_back(field);

        if (field != nullptr)
        {  
            if (field->Size() % boundary32Bits != 0)
            {
                size_t newSize{ field->Size() };
                size_t padSize{ 0 };

                while (newSize % boundary32Bits != 0)
                {
                    newSize++;
                    padSize++;
                }

                auto pad = std::make_shared<SpcTextField>("<padding>", 
                                                          extendedTagOffset,
                                                          padSize);
                paddedFields.push_back(pad);
            }
        }
    }

    fields = paddedFields;
}
*/

/*
void AddFieldPadded(std::vector<SpcField*>& fields, SpcField* field)
{
    constexpr int boundary32bits{ 4 };

    fields.push_back(field);

    if (field != nullptr)
    {
        if (field->Size() % boundary32bits != 0)
        {
            size_t newSize{ field->Size() };
            size_t padSize{ 0 };

            while (newSize % boundary32bits != 0)
            {
                newSize++;
                padSize++;
            }

            SpcTextField padding{ "<padding>", extendedTagOffset, padSize };
            fields.push_back(&padding);
        }
    }
}
*/