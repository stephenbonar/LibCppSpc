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

#ifndef SPC_FIELD_H
#define SPC_FIELD_H

#include <string>
#include "LibCppBinary.h"

namespace Spc
{
    /// @brief Represents a binary data field in an SPC file.
    ///
    /// The Spc::Field is meant for reading and writing individual fields from
    /// and to an SPC file. It is an extension of Binary::RawField that adds
    /// labels and offsets for formatting and locating the field. All fields
    /// in an Spc::DataStructure are expected to inherit from this class.
    class Field : public Binary::RawField
    {
    public:
        /// @brief Constructor; creates a new instance of SpcField.
        /// @param label The label to use when outputing the field. 
        /// @param offset The offset where the field can be found in the file.
        /// @param size The size of the field, in bytes.
        Field(std::string label, uintmax_t offset, size_t size) 
            : label{ label }, offset{ offset }, Binary::RawField{ size }
        { }
        
        /// @brief Gets the field label used to describe the field.
        /// @return A string representing the field label.
        std::string Label() const { return label; }

        /// @brief Gets the offset where the field can be found in the SPC file.
        /// @return The offset of the field,.
        uintmax_t Offset() const { return offset; }

        /// @brief Sets the field label to the specified value.
        /// @param value The value to set the label to.
        void SetLabel(std::string value) { label = value; }
    private:
        std::string label;
        uintmax_t offset;
    };
}

#endif