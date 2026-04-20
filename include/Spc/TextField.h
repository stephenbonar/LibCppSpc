// TextField.h - Declares the Spc::TextField class.
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

#ifndef SPC_TEXT_FIELD_H
#define SPC_TEXT_FIELD_H

#include <string>
#include "Field.h"
#include "LibCppBinary.h"
#include "FieldInfo.h"

namespace Spc
{
    /// @brief Represents a field containing text in an SPC file.
    ///
    /// Texts fields are to be used for fields that are guaranteed to contain
    /// strings of ASCII text. They should not be used for fields that can 
    /// contain text or binary representations of numbers.
    ///
    /// @invariant Size > 0.
    /// @invariant The field's data is always treated as a string of text.
    /// @invariant Setting string values will always fit the available size.
    /// @invariant ToString() always returns a null terminated string. 
    class TextField : public Field
    {
    public:
        /// @brief Constructor; creates a new instance of TextField.
        /// @param label The label to use when outputing the field. 
        /// @param info Sets offset and size of the field.
        TextField(std::string label, FieldInfo info) : Field{ label, info }
        { }

        /// @brief Sets the text value of the field.
        /// @param value The value to set.
        /// @post The field's data is updated to match the specified value.
        /// @post If the value is shorter than size, remaining bytes are 0.
        /// @post If the value is longer than size, it is truncated to fit.
        void SetValue(std::string value) override;
        
        /// @brief Converts the field's data to a string representation.
        /// @return A string representation of the field's data.
        std::string ToString() const override
        {
            return Binary::RawField::ToString(Binary::StringFormat::Terminated);
        }
    };
}

#endif