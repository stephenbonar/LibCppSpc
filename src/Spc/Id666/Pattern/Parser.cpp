// Parser.cpp - Defines the Spc::Id666::Pattern::Parser class.
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

#include "Spc/Id666/Pattern/Parser.h"

using namespace Spc::Id666::Pattern;

std::vector<Node> Parser::Parse() const
{
    std::vector<Node> nodes;

    for (const Token& token : tokens)
    {
        Node node;

        switch (token.Type())
        {
        case TokenType::Literal:
            node.type = NodeType::Literal;
            node.lexeme = token.Lexeme();
            break;
        case TokenType::Placeholder:
            if (token.Lexeme() == discPlaceholder || 
                token.Lexeme() == trackPlaceholder)
            {
                node.type = NodeType::NumericPlaceholder;
            }
            else
            {
                node.type = NodeType::TextPlaceholder;
            }
            
            node.lexeme = token.Lexeme();
            break;
        case TokenType::End:
            node.type = NodeType::End;
            break;
        }

        nodes.push_back(node);
    }

    return nodes;
}