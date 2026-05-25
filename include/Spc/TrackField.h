// TrackField.h - Declares the Spc::TrackField class.
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

#ifndef SPC_TRACK_FIELD_H
#define SPC_TRACK_FIELD_H

#include <sstream>
#include "NumericField.h"
#include "FieldInfo.h"

namespace Spc
{
    /// @brief Represents a field containing the track number in an SPC file.
    ///
    /// The track field is a special type of numeric field that contains the
    /// track number of the song. It is unique in that it can contain a suffix
    /// character in addition to the track number. For example, a track field
    /// could contain the value "2a", where '2' is the track number and 'a' is 
    /// the suffix.
    ///
    /// @invariant Field data is a valid track number with optional suffix.
    /// @invariant The track number is between 0 and 99.
    /// @invariant The first byte of data is the suffix character.
    /// @invariant The second byte of data is the track number.
    /// @invariant ToString() returns the track number followed by the suffix
    class TrackField : public NumericField
    {
    public:
        /// @brief Constructor; creates a new instance of TrackField.
        /// @param label The label to use when outputing the field. 
        /// @param info Sets offset and size of the field.
        TrackField(std::string label, FieldInfo info) :
            NumericField{ label, info }
        { }

        /// @brief Gets the suffix character of the track field.
        /// @return The suffix character.
        char Suffix() const;

        /// @copydoc Field::ToString()
        virtual std::string ToString() const override;

        /// @brief Sets the track number and optional suffix.
        /// @param value A string representation of the track number w/ suffix.
        /// @pre The numeric portion should be a value between 0 and 99.
        /// @pre The suffix should be a single character or not included at all.
        /// @post The first data byte will be set to the suffix character.
        /// @post The second data byte will be set to the track number.
        virtual void SetValue(std::string value) override;
    };
}

#endif