// Header.h - Declares the Header struct.
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

#ifndef SPC_HEADER_H
#define SPC_HEADER_H

#include <vector>
#include "DataStructure.h"
#include "TextField.h"
#include "NumericField.h"

namespace Spc
{
    /// @brief Represents the file header in an SPC file.
    struct Header : public DataStructure
    {
        /// @brief The first bytes of the file that identify it as an SPC file.
        TextField ID{ "SPC Header ID", 0x0, 33 };

        /// @brief Separates the ID from the rest of the header. Purpose unclear.
        Field separator{ "Separator", 0x21, 2 };

        /// @brief A byte related to the separator that determines if a tag exists.
        NumericField containsTag
        {
            "Contains Tag", 0x23, 1, NumericType::Binary
        };

        /// @brief The minor version number of the SPC file format used.
        NumericField versionMinor
        { 
            "Version Minor", 0x24, 1, NumericType::Binary
        };

        /// @brief Saved state of the SPC700's program counter register.
        Field pcRegister{ "PC Register", 0x25, 2 };

        /// @brief Saved state of the SPC700's A register.
        Field aRegister{ "A Register", 0x27, 1 };

        /// @brief Saved state of the SPC700's X register.
        Field xRegister{ "X Register", 0x28, 1 };

        /// @brief Saved state of the SPC700's Y register.
        Field yRegister{ "Y Register", 0x29, 1 };

        /// @brief Saved state of the SPC700's program status word register.
        Field pswRegister{ "PSW Register", 0x2A, 1 };

        /// @brief Saved state of the SPC700's stack pointer register.
        Field spRegister{ "SP Register", 0x2B, 1 };

        /// @brief Reserved bytes for future use in the header.
        Field reserved{ "Reserved", 0x2C, 2 };

        /// @brief Default constructor; initalizes the labeled fields list.
        ///
        /// While this is a standard struct with public fields, it is also an 
        /// SpcStruct, which maintains an internal vector of labeled pointers to
        /// each public field accessible via the SpcFields() method. The 
        /// constructor initializes this internal vector.
        Header();

        /// @brief Gets list of pointers to this struct's fields paired w/ labels.
        ///
        /// This method will be called by the ToString() method to output each
        /// field as a formatted string on its own line of the format,
        ///
        /// label: value
        ///
        /// This method is also called by the Fields() method to get a pointer to
        /// each field so SpcFileStream can read this struct from and write it to
        /// an SPC file in a cross platform way, preserving the order, size, and
        /// endianness of each field no matter which architecture the program runs
        /// on.
        std::vector<Field*> SpcFields() const override { return spcFields; }
    private:
        std::vector<Field*> spcFields;
    };
}

#endif