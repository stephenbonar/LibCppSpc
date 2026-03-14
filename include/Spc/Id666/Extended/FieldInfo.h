// ExtendedFieldInfo.h - Declares the ExtendedFieldIInfo class.
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

#ifndef SPC_ID666_EXTENDED_FIELD_INFO_H
#define SPC_ID666_EXTENDED_FIELD_INFO_H

#include "Spc/FieldInfo.h"

namespace Spc::Id666::Extended
{
    struct FieldInfo
    {
        uint8_t id;
        uint8_t type;
    };

    inline constexpr uint8_t lengthType{ 0 };
    inline constexpr uint8_t stringType{ 1 };
    inline constexpr uint8_t integerType{ 4 };

    inline constexpr size_t dataOffset{ 0x10200 };

    inline constexpr Spc::FieldInfo idInfo{ dataOffset, 1 };
    inline constexpr Spc::FieldInfo typeInfo{ dataOffset, 1 };
    inline constexpr Spc::FieldInfo dataInfo{ dataOffset, 2 };

    /*
    inline constexpr int idSize{ 1 };
    inline constexpr int typeSize{ 1 };
    inline constexpr int dataSize{ 2 };
    */

    inline constexpr size_t integerSize{ 4 };
    inline constexpr size_t stringMaxSize{ 255 };

    inline constexpr FieldInfo songTitleInfo{ 0x1, stringType };
    inline constexpr FieldInfo gameTitleInfo{ 0x2, stringType };
    inline constexpr FieldInfo songArtistInfo{ 0x3, stringType };
    inline constexpr FieldInfo dumperNameInfo{ 0x4, stringType };
    inline constexpr FieldInfo dateDumpedInfo{ 0x5, integerType };
    inline constexpr FieldInfo emulatorUsedInfo{ 0x6, lengthType };
    inline constexpr FieldInfo commentsInfo{ 0x7, stringType };
    inline constexpr FieldInfo ostTitleInfo{ 0x10, stringType };
    inline constexpr FieldInfo ostDiscInfo{ 0x11, lengthType };
    inline constexpr FieldInfo ostTrackInfo{ 0x12, lengthType };
    inline constexpr FieldInfo publisherNameInfo{ 0x13, stringType };
    inline constexpr FieldInfo copyrightYearInfo{ 0x14, lengthType };
    inline constexpr FieldInfo introLengthInfo{ 0x30, integerType };
    inline constexpr FieldInfo loopLengthInfo{ 0x31, integerType };
    inline constexpr FieldInfo endLengthInfo{ 0x32, integerType };
    inline constexpr FieldInfo fadeLengthInfo{ 0x33, integerType };
    inline constexpr FieldInfo mutedVoicesInfo{ 0x34, lengthType };
    inline constexpr FieldInfo loopTimesInfo{ 0x35, lengthType };
    inline constexpr FieldInfo preampLevelInfo{ 0x36, integerType };
}

#endif