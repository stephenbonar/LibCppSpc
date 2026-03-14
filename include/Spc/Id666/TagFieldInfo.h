// TagFieldInfo.h - Declares the TagFieldInfo struct.
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

#ifndef SPC_ID666_TAG_FIELD_INFO_H
#define SPC_ID666_TAG_FIELD_INFO_H

#include "Spc/FieldInfo.h"

namespace Spc::Id666
{
    struct TagFieldInfo
    {
        Spc::FieldInfo text;
        Spc::FieldInfo binary;
    };

    constexpr TagFieldInfo songTitleInfo{ { 0x2E, 32 }, { 0x2E, 32 } };
    constexpr TagFieldInfo gameTitleInfo{ { 0x4E, 32 }, { 0x4E, 32 } };
    constexpr TagFieldInfo dumperNameInfo{ { 0x6E, 16 }, { 0x6E, 16 } };
    constexpr TagFieldInfo commentsInfo{ { 0x7E, 32 }, { 0x7E, 32 } };
    constexpr TagFieldInfo dateDumpedInfo{ { 0x9E, 11 }, { 0x9E, 11 } };
    constexpr TagFieldInfo songLengthInfo{ { 0xA9, 3 }, { 0xA9, 3 } };
    constexpr TagFieldInfo fadeLengthInfo{ { 0xAC, 5 }, { 0xAC, 4 } };
    constexpr TagFieldInfo songArtistInfo{ { 0xB1, 32 }, { 0xB0, 32 } };
    constexpr TagFieldInfo defaultChannelStateInfo{ { 0xD1, 1 }, { 0xD0, 1 } };
    constexpr TagFieldInfo emulatorUsedInfo{ { 0xD2, 1 }, { 0xD1, 1 } };
    constexpr TagFieldInfo reservedInfo{ { 0xD3, 45 }, { 0xD2, 46 } };
}

#endif