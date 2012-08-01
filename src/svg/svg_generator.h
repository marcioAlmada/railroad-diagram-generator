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

#ifndef SVG_GENERATOR_H_
#define SVG_GENERATOR_H_

#include <string>
#include <vector>
#include "../ast/ast.h"

class SVGGenerator {

public:
    explicit SVGGenerator(RuleNode* node);

    RuleNode* getRuleNode()const;

    std::vector<std::string> getSVGCodes();

private:
    void genNodeSVG(RuleNode* node);
    void genNodeSVG(OrNode* node);
    void genNodeSVG(AndNode* node);
    void genNodeSVG(StarNode* node);
    void genNodeSVG(PlusNode* node);
    void genNodeSVG(ParenNode* node);
    void genNodeSVG(SymbolNode* node);
    void genNodeSVG(TerminalNode* node);
    void genNodeSVG(EmptyNode* node);
    void genNodeSVG(Node* node);

private:
    void genSVGDirectly(const std::string& data);
    void genSVGStyle(const std::string& style);
    void genSVGRect(const std::string& rect_class, int x, int y, int width, int height, int rx);
    void genSVGText(const std::string& text_class, int x, int y, const std::string& text);
    void genSVGPath(const std::string& path_class, const std::string& path);

private:
    RuleNode* rule_node_;
    std::vector<std::string> SVG_codes_;

private:
    SVGGenerator(const SVGGenerator&) = delete;
    void operator=(const SVGGenerator&) = delete;

};

#endif // SVG_GENERATOR_H_
