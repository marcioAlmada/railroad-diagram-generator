/*
 * This file is a part of railroad-diagram-generator
 *
 * Copyright (C) 2012 xStone <chen_fu_hua@126.com>
 *
 * This program is free software; you can redestribute it and/or modify it
 * under terms of GNU General Public License by Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY. See GPL for more details.
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <memory>
#include <string>
#include <vector>
#include "../ast/ast.h"
#include "../lex/lexer.h"

class Parser {

public:
    explicit Parser(const std::string& file_data);

    void setFileData(const std::string& file_data);
    std::string getFileData()const;

    std::vector<RuleNode*> parseSyntax();

    const std::string& getErrorInfo()const;

private:
    RuleNode* parseRule();

    Node* parseExpression();
    Node* parseTerm();
    Node* parseFactor();

private:
    void consumeToken();
    Node* errorNode(const char* message);

private:
    Lexer lexer_;

    Lexer::Token token_;
    std::string token_value_;
    std::pair<unsigned, unsigned> token_location_;

    Lexer::Token peek_token_;

    std::vector<std::shared_ptr<RuleNode>> nodes_;
    std::string error_info_;

private:
    Parser(const Parser&) = delete;
    void operator=(const Parser&) = delete;

};

#endif // PARSER_H_
