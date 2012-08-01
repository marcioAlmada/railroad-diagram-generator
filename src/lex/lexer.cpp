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

#include "lexer.h"

Lexer::Lexer(const std::string& file_data)
    : buffer_(file_data), buffer_ptr_(0),
      token_value_(),
      line_location_(1), column_location_(1)
{
    buffer_ptr_         = buffer_.getBufferBegin();
    new_line_location_  = buffer_ptr_;
}

void Lexer::lex(Token& tok)
{
    const char* cur_ptr = buffer_ptr_;

    while (*cur_ptr == ' ' || *cur_ptr == '\t' || *cur_ptr == '\n') {
        if (*cur_ptr == '\n') {
            line_location_++;
            new_line_location_ = cur_ptr + 1;
        }
        cur_ptr++;
    }
    buffer_ptr_ = cur_ptr;

    tok = Token::unknown;
    switch (*cur_ptr++) {
        case 0:
            if (cur_ptr - 1 == buffer_.getBufferEnd()) {
                tok = Token::eof;
                formTokenValueWithChars(cur_ptr);
                buffer_ptr_ = cur_ptr - 1;
                return;
            }
        case ':':
            if (*cur_ptr == ':' && *(cur_ptr + 1) == '=') {
                cur_ptr += 2;
                tok = Token::coloncolonequal;
            } else {
                tok = Token::unknown;
            }
            break;
        case '-':
            if (*cur_ptr == '>') {
                cur_ptr++;
                tok = Token::minusgreater;
            } else {
                tok = Token::unknown;
            }
            break;
        case '|':
            tok = Token::bar;
            break;
        case '+':
            tok = Token::plus;
            break;
        case '*':
            tok = Token::star;
            break;
        case '\'':
            while (*cur_ptr != '\'' &&
                   *cur_ptr != '\n' &&
                    cur_ptr != buffer_.getBufferEnd()) {
                cur_ptr++;
            }
            if (*cur_ptr == '\'') {
                cur_ptr++;
                tok = Token::text;
            } else {
                tok = Token::unknown;
            }
            break;
        case '"':
            while (*cur_ptr != '"'  &&
                   *cur_ptr != '\n' &&
                    cur_ptr != buffer_.getBufferEnd()) {
                cur_ptr++;
            }
            if (*cur_ptr == '"') {
                cur_ptr++;
                tok = Token::text;
            } else {
                tok = Token::unknown;
            }
            break;
        case '(':
            tok = Token::l_paren;
            break;
        case ')':
            tok = Token::r_paren;
            break;
        case 'A': case 'B': case 'C': case 'D': case 'E':
        case 'F': case 'G': case 'H': case 'I': case 'J':
        case 'K': case 'L': case 'M': case 'N': case 'O':
        case 'P': case 'Q': case 'R': case 'S': case 'T':
        case 'U': case 'V': case 'W': case 'X': case 'Y':
        case 'Z':
        case 'a': case 'b': case 'c': case 'd': case 'e':
        case 'f': case 'g': case 'h': case 'i': case 'j':
        case 'k': case 'l': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y':
        case 'z':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '_':
            while (std::isalnum(*cur_ptr) || *cur_ptr == '_') {
                cur_ptr++;
            }
            tok = Token::identifier;
            break;
        default:
            tok = Token::unknown;
            break;
    }

    formTokenValueWithChars(cur_ptr);
}

const std::string& Lexer::getTokenValue()const
{
    return token_value_;
}

std::pair<unsigned, unsigned> Lexer::getTokenLocation()const
{
    return std::make_pair(line_location_, column_location_);
}

void Lexer::setFileData(const std::string& file_data)
{
    buffer_.setBufferData(file_data);
    buffer_ptr_         = buffer_.getBufferBegin();
    token_value_.clear();
    line_location_      = 1;
    column_location_    = 1;
    new_line_location_  = buffer_ptr_;
}

std::string Lexer::getFileData()const
{
    return buffer_.getBufferData();
}

void Lexer::formTokenValueWithChars(const char* tok_end)
{
    token_value_.assign(buffer_ptr_, tok_end);
    line_location_   = line_location_;
    column_location_ = buffer_ptr_ - new_line_location_ + 1;
    buffer_ptr_      = tok_end;
}
