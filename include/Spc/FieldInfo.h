// FieldInfo.h - Declares the FieldInfo struct.
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

#ifndef SPC_FIELD_INFO_H
#define SPC_FIELD_INFO_H

#include <cstdint>
#include <cstddef>

namespace Spc
{
    struct FieldInfo
    {
        size_t offset;
        size_t size;
    };

    inline constexpr FieldInfo headerIdInfo{ 0x0, 33 };
    inline constexpr FieldInfo headerSeparatorInfo{ 0x21, 2 };
    inline constexpr FieldInfo headerContainsTagInfo{ 0x23, 1 };
    inline constexpr FieldInfo headerVersionMinorInfo{ 0x24, 1 };
    inline constexpr FieldInfo headerPcRegisterInfo{ 0x25, 2 };
    inline constexpr FieldInfo headerARegisterInfo{ 0x27, 1 };
    inline constexpr FieldInfo headerXRegisterInfo{ 0x28, 1 };
    inline constexpr FieldInfo headerYRegisterInfo{ 0x29, 1 };
    inline constexpr FieldInfo headerPswRegisterInfo{ 0x2A, 1 };
    inline constexpr FieldInfo headerSpRegisterInfo{ 0x2B, 1 };
    inline constexpr FieldInfo headerReservedInfo{ 0x2C, 2 };
    inline constexpr FieldInfo ramInfo{ 0x100, 65536 };
    inline constexpr FieldInfo dspRegistersInfo{ 0x10100, 128 };
    inline constexpr FieldInfo unusedInfo{ 0x10180, 64 };
    inline constexpr FieldInfo extraRamInfo{ 0x101C0, 64 };

    extern const char* headerId;
    inline constexpr char separatorChar{ 0x1A };
    inline constexpr uint8_t headerContainsTag{ 0x1A };
    inline constexpr uint8_t headerContainsNoTag{ 0x1B };
    inline constexpr uint8_t currentVersionMinor{ 30 };
}

#endif