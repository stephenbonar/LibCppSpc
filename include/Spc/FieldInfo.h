// FieldInfo.h - Declares the Spc::FieldInfo struct.
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
    /// @brief Defines the offset and size of a field in an SPC file.
    struct FieldInfo
    {
        /// @brief The offset where the field can be found in the SPC file.
        size_t offset;

        /// @brief The size of the field in bytes.
        size_t size;
    };

    /// @brief Defines the file header ID offset and size.
    inline constexpr FieldInfo headerIdInfo{ 0x0, 33 };

    /// @brief Defines the header separator offset and size.
    inline constexpr FieldInfo headerSeparatorInfo{ 0x21, 2 };

    /// @brief Defines the offset / size of the field indicating tag presence.
    inline constexpr FieldInfo headerContainsTagInfo{ 0x23, 1 };

    /// @brief Defines the offset and size of the version minor field.
    inline constexpr FieldInfo headerVersionMinorInfo{ 0x24, 1 };

    /// @brief Defines the offset and size of the PC register field.
    inline constexpr FieldInfo headerPcRegisterInfo{ 0x25, 2 };

    /// @brief Defines the offset and size of the A register field.
    inline constexpr FieldInfo headerARegisterInfo{ 0x27, 1 };

    /// @brief Defines the offset and size of the X register field.
    inline constexpr FieldInfo headerXRegisterInfo{ 0x28, 1 };

    /// @brief Defines the offset and size of the Y register field.
    inline constexpr FieldInfo headerYRegisterInfo{ 0x29, 1 };

    /// @brief Defines the offset and size of the P register field.
    inline constexpr FieldInfo headerPswRegisterInfo{ 0x2A, 1 };

    /// @brief Defines the offset and size of the SP register field.
    inline constexpr FieldInfo headerSpRegisterInfo{ 0x2B, 1 };

    /// @brief Defines the offset and size of the reserved header area.
    inline constexpr FieldInfo headerReservedInfo{ 0x2C, 2 };

    /// @brief Defines the offset and size of the SPC RAM dump.
    inline constexpr FieldInfo ramInfo{ 0x100, 65536 };

    /// @brief Defines the offset and size of the DSP registers.
    inline constexpr FieldInfo dspRegistersInfo{ 0x10100, 128 };

    /// @brief Defines the offset and size of the unused area.
    inline constexpr FieldInfo unusedInfo{ 0x10180, 64 };

    /// @brief Defines the offset and size of the extra RAM dump.
    inline constexpr FieldInfo extraRamInfo{ 0x101C0, 64 };

    /// @brief The string that should be found at the start of an SPC file.
    extern const char* headerId;

    /// @brief The character used to separate the header ID from rest of header.
    inline constexpr char separatorChar{ 0x1A };

    /// @brief The value used to determine if header contains tag.
    inline constexpr uint8_t headerContainsTag{ 0x1A };

    /// @brief The value used to determine if header contains no tag.
    inline constexpr uint8_t headerContainsNoTag{ 0x1B };

    /// @brief The current version minor of the SPC file format.
    inline constexpr uint8_t currentVersionMinor{ 30 };
}

#endif