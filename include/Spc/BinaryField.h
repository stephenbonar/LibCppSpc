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
    /// @brief Represents an Spc::NumericField formatted as binary by default.
    ///
    /// This class is a specialization of Spc::NumericField that is always
    /// treated as containing a binary representation of a number. It provides
    /// methods for converting the field's data to and from a binary string
    /// representation such as "00100101". It is used for representing fields
    /// that should be interpreted as binary numbers, such as flags or bitmasks.
    class BinaryField : public NumericField
    {
    public:
        /// @brief Constructor; creates a new instance of Spc::BinaryField.
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

        /// @brief Sets value using a string representation of a binary number.
        /// @param value A string representation of the binary number to set.
        /// @pre The string must only contain '0' and '1' characters.
        /// @post The field's data is updated to represent the specified value.
        virtual void SetValue(std::string value) override;

        // In C++, base class methods are hidden by derived class methods with 
        // the same name. In order to call the base class version of SetValue,
        // we need to bring it into scope with a using declaration.
        using NumericField::SetValue;
    };
}

#endif