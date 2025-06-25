// DataStruct.h - Declares the DataStruct struct.
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

#ifndef SPC_DATA_STRUCTURE_H
#define SPC_DATA_STRUCTURE_H

#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include "Format.h"
#include "Field.h"
#include "LibCppBinary.h"

namespace Spc
{
    /// @brief Abstract base struct representing a binary data structure in an SPC.
    ///
    /// Adds a ToString() method to the original Binary::DataStructure for
    /// displaying SPC file data. Each field in the structure is labeled so when
    /// ToString() is called, the resulting string lists each field in the format,
    ///
    /// label: value
    ///
    /// Any struct representing a data structure in an SPC file should inherit from
    /// this struct. It provides a default implementation for the Fields(), Size(),
    /// and ToString() methods so all the inheriting struct needs to provide is
    /// an implementation for SpcFields(). 
    struct DataStructure : Binary::DataStructure
    {
        /// @brief Provides a vector of raw pointers to the structure's fields.
        ///
        /// This method is primarily intended for use by Binary::Stream and its
        /// derivatives for reading the fields from and to those streams.
        /// Access the fields directly rather than via this method.
        ///
        /// @return The vector containing the raw pointers for the field.
        std::vector<Binary::DataField*> Fields() override;

        /// @brief Gets the total size of all fields in the structure.
        /// @return The total size of the structure.
        size_t Size() const override;

        /// @brief Provides a string representation of the struct.
        ///
        /// The string representation lists all of the fields in the format,
        ///
        /// label: value
        ///
        /// with each field on its own line.
        ///
        /// @return The string representation of the struct.
        std::string ToString() const;

        /// @brief Gets list of pointers to this struct's fields.
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
        ///
        /// Structs that inherit from this struct should provide an implementation
        /// for this method that generates the vector in the correct order.
        ///
        /// @return A vector containing pointers to the SpcFields.
        virtual std::vector<Field*> SpcFields() const = 0;
    };
}

#endif