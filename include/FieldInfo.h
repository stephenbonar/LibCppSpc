// Field.h - Declares the Field class.
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

#ifndef SPC_FIELD_INFO_H
#define SPC_FIELD_INFO_H

namespace Spc
{
    struct FieldInfo
    {
        int textOffset;
        int textSize;
        int binaryOffset;
        int binarySize;
    };

    constexpr FieldInfo songTitleInfo{ 0x2E, 32, 0x2E, 32 };
    constexpr FieldInfo gameTitleInfo{ 0x4E, 32, 0x4E, 32 };
    constexpr FieldInfo dumperNameInfo{ 0x6E, 16, 0x6E, 16 };
    constexpr FieldInfo commentsInfo{ 0x7E, 32, 0x7E, 32 };
    constexpr FieldInfo dateDumpedInfo{ 0x9E, 11, 0x9E, 4 };
}

#endif