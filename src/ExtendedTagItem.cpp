// ExtendedTagItem.cpp - Defines the ExtendedTagItem class.
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

#include "ExtendedTagItem.h"

using namespace Spc;

const std::map<int, std::string> extendedFieldLabels
{
    { extendedSongNameID, "Song Title*" },
    { extendedGameNameID, "Game Title*" },
    { extendedArtistNameID, "Song Artist*" }, 
    { extendedDumperNameID, "Dumper Name*" },
    { extendedDateDumpedID, "Date Dumped*" },
    { extendedEmulatorUsedID, "Emulator Used*" },
    { extendedCommentsID, "Comments*" },
    { extendedOSTTitleID, "OST Title*" },
    { extendedOSTDiscID, "OST Disc*" },
    { extendedOSTTrackID, "OST Track*" },
    { extendedPublisherNameID, "Publisher Name*" },
    { extendedCopyrightYearID, "Copyright Year*" },
    { extendedIntroLengthID, "Intro Length*" },
    { extendedLoopLengthID, "Loop Length*" },
    { extendedEndLengthID, "End Length*" },
    { extendedFadeLengthID, "Fade Length*" },
    { extendedMutedVoicesID, "Muted Voices*" },
    { extendedLoopTimesID, "Loop Times*" },
    { extendedPreampLevelID, "Preamp Level*" }
};

ExtendedTagItem::ExtendedTagItem()
{
    id = std::make_shared<NumericField>("Item ID", 
                                        extendedTagOffset, 
                                        extendedTagIDSize);
    type = std::make_shared<NumericField>("Item Type",
                                          extendedTagOffset,
                                          extendedTagTypeSize);
    data = std::make_shared<NumericField>("Item Data",
                                          extendedTagOffset,
                                          extendedTagDataSize);
}

std::vector<Field*> ExtendedTagItem::SpcFields() const
{
    std::vector<Field*> fields;
    fields.push_back(id.get());
    fields.push_back(type.get());
    fields.push_back(data.get());

    if (extendedData != nullptr && type->Value() != extendedTypeDataInHeader)
    {
        fields.push_back(extendedData.get());

        if (padding != nullptr)
            fields.push_back(padding.get());
    }

    return fields;
}