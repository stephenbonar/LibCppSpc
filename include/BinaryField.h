// BinaryField.h - Declares the BinaryField class.
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

#ifndef SPC_BINARY_FIELD_H
#define SPC_BINARY_FIELD_H

#include <string>
#include "NumericField.h"

namespace Spc
{
    /// @brief Represents a field that should be formatted as binary by default.
    class BinaryField : public NumericField
    {
    public:
        /// @brief Constructor; creates a new instance of SpcBinaryField.
        /// @param label The label to use when outputing the field. 
        /// @param offset The offset where the field can be found in the file.
        /// @param size The size of the field, in bytes.
        BinaryField(std::string label, uintmax_t offset, size_t size) :
            NumericField{ label, offset, size }
        {
            SetType(NumericType::Binary);
        }

        /// @brief Converts the field's data to a string representation.
        /// @return A string representation of the field's data.
        std::string ToString() const override
        {
            return Binary::RawField::ToString(Binary::StringFormat::Bin);
        }

        virtual void SetValue(std::string value) override
        {
            int binaryValue = std::stoi(value, nullptr, 2);
            NumericField::SetValue(binaryValue);
        }

        using NumericField::SetValue;
    };
}

#endif