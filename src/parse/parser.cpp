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

#include "parser.h"
#include <cassert>

Parser::Parser(const std::string& file_data)
    : lexer_(file_data)
{
    consumeToken();
    consumeToken();
}

void Parser::setFileData(const std::string& file_data)
{
    lexer_.setFileData(file_data);
    consumeToken();
    consumeToken();
    nodes_.clear();
    error_info_.clear();
}

std::string Parser::getFileData()const
{
    return lexer_.getFileData();
}

/*!
 *  syntax ::= ( rule )+
 */
std::vector<RuleNode*> Parser::parseSyntax()
{
    std::vector<RuleNode*> v;

    // parsed but an error occurred
    if (!error_info_.empty()) {
        return v;
    }

    // parsed and ok
    if (!nodes_.empty()) {
        for (auto& n: nodes_) {
            v.push_back(n.get());
        }
        return v;
    }

    // not parsed, let's start
    v.push_back(parseRule());
    while (token_ == Lexer::Token::identifier) {
        v.push_back(parseRule());
    }

    if (token_ != Lexer::Token::eof) {
        errorNode("too much token");
    }

    // an error occurred while parsing
    if (!error_info_.empty()) {
        for (auto& n: v) {
            delete n;
        }
        v.clear();
    }

    for (auto& n: v) {
        nodes_.push_back(std::shared_ptr<RuleNode>(n));
    }

    return v;
}

const std::string& Parser::getErrorInfo()const
{
    return error_info_;
}

/*!
 *  rule ::= 'id' ( '::=' | '->' ) expression
 */
RuleNode* Parser::parseRule()
{
    std::string name = token_value_;
    consumeToken();

    if (token_ != Lexer::Token::coloncolonequal &&
        token_ != Lexer::Token::minusgreater) {
        return static_cast<RuleNode*>(errorNode("missing terminating character \"::=\" or\" ->\""));
    }
    consumeToken();

    Node* node = parseExpression();

    return new RuleNode(name, node);
}

/*!
 *  expression ::= term ( '|' term )* ( '|' | )
 */
Node* Parser::parseExpression()
{
    std::vector<Node*> v;
    v.push_back(parseTerm());
    while (token_ == Lexer::Token::bar) {
        consumeToken();

        if ((token_ == Lexer::Token::identifier &&
             peek_token_ != Lexer::Token::coloncolonequal &&
             peek_token_ != Lexer::Token::minusgreater) ||
            token_ == Lexer::Token::text ||
            token_ == Lexer::Token::l_paren) {
            v.push_back(parseTerm());
        } else{
            v.push_back(new EmptyNode());
            break;
        }
    }

    return new OrNode(v);
}

/*!
 *  term ::= ( factor )+
 */
Node* Parser::parseTerm()
{
    std::vector<Node*> v;
    v.push_back(parseFactor());
    while ((token_ == Lexer::Token::identifier &&
            peek_token_ != Lexer::Token::coloncolonequal &&
            peek_token_ != Lexer::Token::minusgreater) ||
           token_ == Lexer::Token::text ||
           token_ == Lexer::Token::l_paren) {
        v.push_back(parseFactor());
    }

    return new AndNode(v);
}

/*!
 *  factor ::= ( 'id' | 'text' | '(' expression ')' ) ( '+' | '*' | )
 */
Node* Parser::parseFactor()
{
    Node* n = 0;
    switch (token_) {
        case Lexer::Token::identifier:
            n = new SymbolNode(token_value_);
            consumeToken();
            break;
        case Lexer::Token::text:
            n = new TerminalNode(token_value_.substr(1, token_value_.size() - 2));
            consumeToken();
            break;
        case Lexer::Token::l_paren:
            consumeToken();

            n = new ParenNode(parseExpression());

            if (token_ != Lexer::Token::r_paren) {
                return errorNode("missing terminating character \")\"");
            }
            consumeToken();
            break;
        default:
            assert(false && "unexpected token");
            break;
    }

    switch (token_) {
        case Lexer::Token::plus:
            consumeToken();
            n = new PlusNode(n);
            break;
        case Lexer::Token::star:
            consumeToken();
            n = new StarNode(new PlusNode(n));
            break;
        default:
            break;
    }

    return n;
}

void Parser::consumeToken()
{
    token_          = peek_token_;
    token_value_    = lexer_.getTokenValue();
    token_location_ = lexer_.getTokenLocation();
    lexer_.lex(peek_token_);
}

Node* Parser::errorNode(const char* message)
{
    if (error_info_.empty()) {
        error_info_ = std::to_string(token_location_.first) + std::string(":") +
                      std::to_string(token_location_.second) + std::string(":") +
                      std::string("   error: ") + std::string(message) +
                      std::string("   unexpected token value: \"") + token_value_ + std::string("\"");
    }

    while (token_ != Lexer::Token::eof) {
        consumeToken();
    }

    return 0;
}
