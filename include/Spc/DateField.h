// DateField.h - Declares the Spc::DateField class.
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

#ifndef SPC_DATE_FIELD_H
#define SPC_DATE_FIELD_H

#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>
#include "NumericField.h"
#include "FieldInfo.h"
#include "Format.h"

namespace Spc
{
    /// @brief Represents a field containing a date in an SPC file.
    ///
    /// Date dumped can either have a text or binary representation. This field
    /// can determine which representation is used and output the date in the
    /// correct format based on the representation.
    ///
    /// @invariant The field's data is always treated as a date representation.
    /// @invariant The field's data is always 11 bytes in size.
    class DateField : public NumericField
    {
    public:
        /// @brief Constructor; creates a new instance of DateField.
        /// @param label The label to use when outputing the field. 
        /// @param info Sets offset and size of the field.
        DateField(std::string label, FieldInfo info);
            
        /// @copydoc NumericField::IsText()
        virtual bool IsText() const override;

        /// @brief Determines if bytes 4 - 7 are unused, which indicates binary.
        /// @return True if 4 - 7 are 0, otherwise false. 
        bool HasUnusedArea() const;

        /// @brief Determines if the date is set.
        /// @return Returns true if it is set, otherwise false.
        bool IsSet() const;

        /// @brief Sets the date value using a string representation of date.
        /// @param value The date value as a string.
        /// @pre The value should be in MM/DD/YYYY format.
        /// @post The field's data is updated to represent the specified value.
        virtual void SetValue(std::string value) override;

        /// @copydoc Field::ToString()
        virtual std::string ToString() const override;
    private:
        /// @brief Sets the date value and stores it in text format.
        /// @param value The date value as a string.
        /// @pre The value should be in MM/DD/YYYY format.
        /// @post The field's data is updated to represent the specified value.
        void SetTextValue(std::string value);

        /// @brief Sets the date value and stores it in binary format.
        /// @param value The date value as a string.
        /// @pre The value should be in MM/DD/YYYY format.
        /// @post The field's data is updated to represent the specified value.
        void SetBinaryValue(std::string value);
    };
}

#endif