// ExtendedTag.h - Defines the ExtendedTag class.
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

#include "ExtendedTag.h"

using namespace Spc;

Binary::ChunkHeader ExtendedTag::Header() const
{
    Binary::ChunkHeader header;
    header.id.SetValue("xid6");
    header.dataSize.SetValue(Size());
    return header;
}

std::vector<Field*> ExtendedTag::SpcFields() const
{
    std::vector<Field*> nonNullFields;
    std::vector<ExtendedTagItem*> items;

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

    for (ExtendedTagItem* item : items)
    {
        if (item != nullptr)
        {
            std::vector<Field*> fields = item->SpcFields();

            for (Field* field : fields)
                nonNullFields.push_back(field);
        }
    }

    return nonNullFields;
}
