// ID666ExtendedItem.h - Declares the ID666ExtendedItem class.
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

#include <string>
#include <memory>
#include <map>
#include "Spc/DataStructure.h"
#include "Spc/NumericField.h"
#include "Spc/TextField.h"
#include "Spc/Id666/Extended/FieldInfo.h"

#ifndef SPC_ID666_EXTENDED_ITEM_H
#define SPC_ID666_EXTENDED_ITEM_H

namespace Spc::Id666::Extended
{
    extern const std::map<int, std::string> fieldLabels;

    inline constexpr int dataOffset{ 0x10200 };
    
    /// @brief Represents an item in the extended ID666 tag.
    ///
    /// The extended ID666 tag is an IFF chunk that contains multiple 
    /// sub-chunks representing items in the tag. This struct represents those 
    /// sub-chunks.
    struct Item : public DataStructure
    {
        /// @brief Default constructor; creates new instance of Item.
        Item();
        
        /// @brief Determines which extended item this instance represents.
        std::shared_ptr<NumericField> id;

        /// @brief Determines the type of extended item.
        ///
        /// 0 = The value is contained in the data field.
        /// 1 = The value is in extendedData and represents a string.
        /// 4 = The value is in extendedData and represents a 32-bit integer.
        std::shared_ptr<NumericField> type;

        /// @brief Depending on type, represents either data length or value.
        std::shared_ptr<NumericField> data;

        /// @brief Contains the item value if type is not 0.
        std::shared_ptr<Field> extendedData;

        /// @brief Points to the padding bytes, if any.
        std::shared_ptr<TextField> padding;

        /// @brief Gets list of pointers to this struct's fields.
        ///
        /// This method will be called by the ToString() method to output each
        /// field as a formatted string on its own line of the format,
        ///
        /// label: value
        ///
        /// This method is also called by the Fields() method to get a pointer
        /// to each field so SpcFileStream can read this struct from and write
        /// it to each field so SpcFileStream can read this struct from and 
        /// write it to an SPC file in a cross platform way, preserving the 
        /// order, size, and endianness of each field no matter which 
        /// architecture the program runs on.
        std::vector<Field*> SpcFields() const override;
    };
}

#endif