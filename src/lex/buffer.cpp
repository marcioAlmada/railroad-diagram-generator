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

#include "buffer.h"
#include <cstring>

Buffer::Buffer(const std::string& data)
{
    buffer_begin_ = 0;
    setBufferData(data);
}

Buffer::~Buffer()
{
    delete[] buffer_begin_;
}

void Buffer::setBufferData(const std::string& data)
{
    if (buffer_begin_ != 0) {
        delete[] buffer_begin_;
    }

    const size_t size   = data.size();
    buffer_begin_       = new char[size + 1];
    std::memcpy(buffer_begin_, data.data(), size);
    buffer_begin_[size] = 0;
    buffer_end_         = buffer_begin_ + size;
}

std::string Buffer::getBufferData()const
{
    return std::string(buffer_begin_, buffer_end_);
}

const char* Buffer::getBufferBegin()const
{
    return buffer_begin_;
}

const char* Buffer::getBufferEnd()const
{
    return buffer_end_;
}

size_t Buffer::getBufferSize()const
{
    return buffer_end_ - buffer_begin_;
}
