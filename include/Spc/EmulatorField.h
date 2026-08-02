// EmulatorField.h - Declares the Spc::EmulatorField class.
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

#ifndef SPC_EMULATOR_FIELD_H
#define SPC_EMULATOR_FIELD_H

#include <string>
#include "NumericField.h"
#include "NumericType.h"
#include "FieldInfo.h"

namespace Spc
{
    /// @brief Represents a numeric field that indicates emulator used.
    ///
    /// A Spc::NumericField with ToString() adjusted to interpret 
    /// the value to determine which emulator was used to dump the SPC file.
    ///
    /// @invariant The field's value always represents a valid emulator.
    class EmulatorField : public NumericField
    {
    public:
        /// @brief Constructor; creates a new instance of Spc::EmulatorField.
        /// @param label The label to use when outputing the field. 
        /// @param info Sets offset and size of the field.
        /// @param isPresent Indicates whether field is present in the SPC file.
        EmulatorField(const std::string& label, FieldInfo info, 
                      bool isPresent = true)
            : NumericField{ label, info, isPresent }
        { }

        /// @brief Constructor; creates a new instance of Spc::EmulatorField.
        /// @param label The label to use when outputing the field. 
        /// @param info Sets offset and size of the field.
        /// @param type Determines the numeric type of the field.
        /// @param isPresent Indicates whether field is present in the SPC file.
        EmulatorField(const std::string& label, FieldInfo info, 
                      NumericType type, bool isPresent = true)
            : NumericField{ label, info, type, isPresent }
        { }
        
        /// @copydoc Field::ToString()
        virtual std::string ToString() const override;

        /// @brief Sets the emulator used value.
        /// @param value A string representation of the value.
        /// @post The value is updated to match the specified value.
        /// @post The value is set to Unknown if specified value not recognized.
        virtual void SetValue(const std::string& value) override;
    };
}

#endif