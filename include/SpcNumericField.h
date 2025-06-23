// SpcNumericField.h - Declares the SpcNumericField class.
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

#ifndef SPC_NUMERIC_FIELD_H
#define SPC_NUMERIC_FIELD_H

#include <string>
#include "LibCppBinary.h"
#include "SpcField.h"
#include "SpcNumericType.h"

/// @brief Represents a field containing a number in an SPC file.
///
/// Numeric fields can contain either a text or binary representation of a
/// number and have some detetion capabilities to determine what kind of
/// representation is contained within. It also provides different methods
/// of retrieving the value depending on if the field should always interpret
/// the data as binary or if it could possibly contain both. 
class SpcNumericField : public SpcField
{
public:
    /// @brief Constructor; creates a new instance of SpcNumericField.
    /// @param label The label to use when outputing the field. 
    /// @param offset The offset where the field can be found in the file.
    /// @param size The size of the field, in bytes.
    SpcNumericField(std::string label, 
                    uintmax_t offset, 
                    size_t size) 
        : SpcField{ label, offset, size }, type{ SpcNumericType::Either }
    { };

    /// @brief Constructor; creates a new instance of SpcNumericField.
    /// @param label The label to use when outputing the field. 
    /// @param offset The offset where the field can be found in the file.
    /// @param size The size of the field, in bytes.
    /// @param type Determines the numeric type of the field.
    SpcNumericField(std::string label, 
                    uintmax_t offset, 
                    size_t size, 
                    SpcNumericType type) 
        : SpcField{ label, offset, size }, type{ type }
    { };

    /// @brief Determines if all bytes in the field contain zeros. 
    /// @return True if the field contains only zeros, otherwise false.
    bool IsZero() const;

    /// @brief Determines if all of the bytes in the field are ASCII numbers.
    ///
    /// The field is most likely to contain a text representation if all bytes
    /// contain the ASCII characters '0' - '9' or binary 0. This is not 100%
    /// accurate detection as a binary value could conincidentally be the same
    /// as the ASCII codes for '0' - '9'. However, if this method returns
    /// false, it is almost a guarantee the field contains binary data.
    ///
    /// @return True if no non-ASCII characters are found, otherwise false.
    bool IsText() const;

    /// @brief Detects the correct value based on if the field is text or not.
    ///
    /// Because a numeric field could contain either a text or binary
    /// representation of the value, this method attempts to determine the
    /// correct value based on the detected type. Note that this may be
    /// incorrect due to ambiguous values. See IsText() for more details. 
    ///
    /// @return The detected value.
    unsigned long long DetectValue() const;

    /// @brief Gets the value assuming the field always is binary.
    /// @return The value of the field.
    unsigned long long Value() const;

    /// @brief Converts the field's data to a string representation.
    /// @return A string representation of the field's data.
    std::string ToString() const override;

    /// @brief Converts the field's data to a string representation.
    /// @param format The format to use for the string conversion.
    /// @return A string representation of the field's data.
    std::string ToString(Binary::StringFormat format) const override
    {
        return Binary::RawField::ToString(format);
    }

    virtual void SetValue(int value);
    
    virtual void SetValue(std::string value);

    void SetType(SpcNumericType type) { this->type = type; }
private:
    SpcNumericType type;
};

#endif