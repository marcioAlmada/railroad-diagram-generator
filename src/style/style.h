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

#ifndef STYLE_H_
#define STYLE_H_

#define TERMIANL_RECT_CLASS         "terminal_rect"
#define TERMIANL_TEXT_CLASS         "terminal_text"
#define SYMBOL_RECT_CLASS           "symbol_rect"
#define SYMBOL_TEXT_CLASS           "symbol_text"
#define PATH_CLASS                  "path"
#define RULE_TEXT_CLASS             "rule_text"
#define RULE_PATH_EDGE_CLASS        "rule_path_edge"

#define BASIC_WIDTH                 16
#define BASIC_HEIGHT                28
#define BASIC_HORIZONTAL_PADDING    12
#define BASIC_VERTICAL_PADDING      8

#define TERMIANL_RECT_WIDTH(SIZE)   (SIZE * 10 + BASIC_WIDTH)
#define TERMIANL_RECT_HEIGHT        (BASIC_HEIGHT)
#define TERMIANL_RECT_RX            (BASIC_HEIGHT)
#define TERMIANL_RECT_STYLE         "fill:rgb(206,255,206);stroke:black;stroke-width:2;"
#define TERMIANL_TEXT_STYLE         "fill:black;font-family:Verdana,Sans-serif;"
#define TERMIANL_FONT_SIZE          14

#define SYMBOL_RECT_WIDTH(SIZE)     (SIZE * 10 + BASIC_WIDTH)
#define SYMBOL_RECT_HEIGHT          (BASIC_HEIGHT)
#define SYMBOL_RECT_RX              1
#define SYMBOL_RECT_STYLE           "fill:rgb(206,255,206);stroke:black;stroke-width:2;"
#define SYMBOL_TEXT_STYLE           "fill:black;font-family:Verdana,Sans-serif;font-weight:bold;font-style:italic;"
#define SYMBOL_FONT_SIZE            14

#define PATH_STYLE                  "fill:none;stroke:black;stroke-width:2;"

#define RULE_HORIZONTAL_PADDING     18
#define RULE_PATH_EDGE_LENGTH       12
#define RULE_TEXT_STYLE             "fill:black;font-family:Verdana,Sans-serif;font-weight:bold;"
#define RULE_FONT_SIZE              14
#define RULE_PATH_EDGE_STYLE        "fill:none;stroke:black;stroke-width:3;"

#define SVG_HORIZONTAL_PADDING      8
#define SVG_VERTICAL_PADDING        8

#endif // STYLE_H_
