// NumericField.h - Declares the Spc::NumericField class.
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

#ifndef SPC_NUMERIC_FIELD_H
#define SPC_NUMERIC_FIELD_H

#include <string>
#include "LibCppBinary.h"
#include "Field.h"
#include "NumericType.h"
#include "FieldInfo.h"
#include "Format.h"

namespace Spc
{
    /// @brief Represents a field containing a number in an SPC file.
    ///
    /// Depending on the format of the SPC file, numeric fields can either have
    /// a text or binary representation of the number. This class represents 
    /// a numeric field that can contain either a text or binary representation
    /// of a number and have some detetion capabilities to determine what kind 
    /// of representation is contained within. It also provides different 
    /// methods of retrieving the value depending on if the field should always 
    /// interpret the data as binary or if it could possibly contain both.
    ///
    /// @invariant Size must be > 0.
    /// @invariant The field data must always represent a valid number.
    /// @invariant Setting value will always use correct format based on type.
    /// @invariant ToString() will always format correctly based on type.
    class NumericField : public Field
    {
    public:
        /// @brief Constructor; creates a new instance of NumericField.
        /// @param label The label to use when outputing the field. 
        /// @param info Sets offset and size of the field.
        /// @param isPresent Indicates whether field is present in the SPC file.
        NumericField(std::string label, FieldInfo info, bool isPresent = true)
            : Field{ label, info, isPresent }, type{ NumericType::Either }
        { };

        /// @brief Constructor; creates a new instance of NumericField.
        /// @param label The label to use when outputing the field. 
        /// @param info Sets offset and size of the field.
        /// @param type Determines the numeric type of the field.
        /// @param isPresent Indicates whether field is present in the SPC file.
        NumericField(std::string label, FieldInfo info, NumericType type,
                     bool isPresent = true)
            : Field{ label, info, isPresent }, type{ type }
        { };

        /// @brief Determines if all bytes in the field contain zeros. 
        /// @return True if the field contains only zeros, otherwise false.
        virtual bool IsZero() const;

        /// @brief Determines if all bytes in the field are ASCII numbers.
        ///
        /// The field is most likely to contain a text representation if all 
        /// bytes contain the ASCII characters '0' - '9' or binary 0. This is 
        /// not 100% accurate detection as a binary value could conincidentally 
        /// be the same as the ASCII codes for '0' - '9'. However, if this 
        /// method returns false, it is almost a guarantee the field contains 
        /// binary data.
        ///
        /// @return True if no non-ASCII characters are found, otherwise false.
        virtual bool IsText() const;

        /// @brief Gets the 32-bit int value based on the detected type.
        ///
        /// Because a numeric field could contain either a text or binary
        /// representation of the value, this method attempts to determine the
        /// correct value based on the detected type. Note that this may be
        /// incorrect due to ambiguous values. See IsText() for more details. 
        ///
        /// @return The detected value.
        virtual int32_t DetectInt32() const;

        /// @brief Gets the 32-bit int representation of the field.
        ///
        /// This method assumes the field contains a binary representation of
        /// the value. If this field could potentially contain a text 
        /// representation, use DetectInt32() instead.
        ///
        /// @pre The field contains a binary representation of the value.
        /// @return The int32_t representation of the field value.
        virtual int32_t ToInt32() const;

        /// @brief Gets the 32-bit unsigned int representation of the field.
        ///
        /// This method assumes the field contains a binary representation of
        /// the value. If this field could potentially contain a text 
        /// representation, use DetectInt32() instead.
        ///
        /// @pre The field contains a binary representation of the value.
        /// @return The uint32_t representation of the field value.
        virtual uint32_t ToUInt32() const;

        /// @copydoc Field::ToString() 
        virtual std::string ToString() const override;

        /// @brief Gets the numeric type of the field.
        /// @return The NumericType of the field.
        virtual NumericType Type() const { return type; }

        /// @brief Sets the value of the field as a signed 32-bit integer.
        /// @param value The int32_t value to set.
        /// @pre The field contains a binary representation of the value.
        /// @post The field's data is updated to represent the provided value.
        /// @post Value is truncated if it exceeds the field size. 
        virtual void SetInt32(int32_t value);

        /// @brief Sets the value of the field as an unsigned 32-bit integer.
        /// @param value The uint32_t value to set.
        /// @pre The field contains a binary representation of the value.
        /// @post The field's data is updated to represent the provided value.
        /// @post Value is truncated if it exceeds the field size.
        virtual void SetUInt32(uint32_t value);

        /// @brief Sets the value of the field from a string representation.
        /// @param value The string value to set.
        /// @pre The value represents a valid number.
        /// @post The field's data is updated to represent the provided value.
        /// @post Value is truncated if it exceeds the field size.
        virtual void SetValue(std::string value) override;

        /// @brief Sets the numeric type of the field.
        /// @param t The NumericType to set.
        virtual void SetType(NumericType t) { type = t; }
    private:
        NumericType type;
    };
}

#endif