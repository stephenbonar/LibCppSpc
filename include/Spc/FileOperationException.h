// FileOperationException.h - Declares the Spc::FileOperationException class.
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

#ifndef SPC_FILE_OPERATION_EXCEPTION_H
#define SPC_FILE_OPERATION_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace Spc
{
    /// @brief Exception thrown when an error occurs during file operations.
    class FileOperationException : public std::runtime_error {
    public:
        /// @brief Constructor; creates new instance of FileOperationException.
        /// @param msg The error message to include with the exception.
        explicit FileOperationException(const std::string& msg)
            : std::runtime_error(msg) {}
    };
}

#endif