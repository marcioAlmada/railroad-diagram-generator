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

#ifndef LEXER_H_
#define LEXER_H_

#include <string>
#include <utility>
#include "buffer.h"

class Lexer {

public:
    enum class Token {
        eof,
        text,
        identifier,
        unknown,
        minusgreater,
        coloncolonequal,
        bar,
        plus,
        star,
        l_paren,
        r_paren
    };

public:
    explicit Lexer(const std::string& file_data);

    void lex(Token& tok);

    const std::string& getTokenValue()const;
    std::pair<unsigned, unsigned> getTokenLocation()const;

    void setFileData(const std::string& file_data);
    std::string getFileData()const;

private:
    void formTokenValueWithChars(const char* tok_end);

private:
    Buffer buffer_;
    const char* buffer_ptr_;

    std::string token_value_;
    unsigned line_location_;
    unsigned column_location_;
    const char* new_line_location_;

private:
    Lexer(const Lexer&) = delete;
    void operator=(const Lexer&) = delete;

};

#endif // LEXER_H_
