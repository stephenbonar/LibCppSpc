// ID666ExtendedItem.cpp - Defines the ID666ExtendedItem class.
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

#include "Spc/Id666/Extended/Item.h"

using namespace Spc;
using namespace Spc::Id666::Extended;

const std::map<int, std::string> extendedFieldLabels
{
    { songTitleInfo.id, "Song Title*" },
    { gameTitleInfo.id, "Game Title*" },
    { songArtistInfo.id, "Song Artist*" }, 
    { dumperNameInfo.id, "Dumper Name*" },
    { dateDumpedInfo.id, "Date Dumped*" },
    { emulatorUsedInfo.id, "Emulator Used*" },
    { commentsInfo.id, "Comments*" },
    { ostTitleInfo.id, "OST Title*" },
    { ostDiscInfo.id, "OST Disc*" },
    { ostTrackInfo.id, "OST Track*" },
    { publisherNameInfo.id, "Publisher Name*" },
    { copyrightYearInfo.id, "Copyright Year*" },
    { introLengthInfo.id, "Intro Length*" },
    { loopLengthInfo.id, "Loop Length*" },
    { endLengthInfo.id, "End Length*" },
    { fadeLengthInfo.id, "Fade Length*" },
    { mutedVoicesInfo.id, "Muted Voices*" },
    { loopTimesInfo.id, "Loop Times*" },
    { preampLevelInfo.id, "Preamp Level*" }
};

Item::Item()
{
    id = std::make_shared<NumericField>("Item ID", 
                                        idInfo,
                                        Spc::NumericType::Binary);
    type = std::make_shared<NumericField>("Item Type",
                                          typeInfo,
                                          Spc::NumericType::Binary);
    data = std::make_shared<NumericField>("Item Data",
                                          dataInfo,
                                          Spc::NumericType::Binary);
}

std::vector<Field*> Item::SpcFields() const
{
    std::vector<Field*> fields;
    fields.push_back(id.get());
    fields.push_back(type.get());
    fields.push_back(data.get());

    if (extendedData != nullptr && type->ToInt32() != lengthType)
    {
        fields.push_back(extendedData.get());

        if (padding != nullptr)
            fields.push_back(padding.get());
    }

    return fields;
}