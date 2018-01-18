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

#include "svg_generator.h"
#include <cassert>
#include "../style/style.h"

SVGGenerator::SVGGenerator(RuleNode* node)
    : rule_node_(node)
{}

RuleNode* SVGGenerator::getRuleNode()const
{
    return rule_node_;
}

std::vector<std::string> SVGGenerator::getSVGCodes()
{
    if (SVG_codes_.empty()) {
        genNodeSVG(rule_node_);
    }

    return SVG_codes_;
}

void SVGGenerator::genNodeSVG(RuleNode* node)
{
    Rect rect = node->getNodeRect();

    genSVGDirectly(std::string("<svg ") +
                   std::string("width=\"") + std::to_string(rect.getWidth() + SVG_HORIZONTAL_PADDING * 2) + "\" " +
                   std::string("height=\"") + std::to_string(rect.getHeight() + SVG_VERTICAL_PADDING * 2) + "\" " +
                   std::string("viewBox=\"") + std::to_string(rect.getLeft() - SVG_HORIZONTAL_PADDING) + " " +
                                               std::to_string(rect.getTop() - SVG_VERTICAL_PADDING) + " " +
                                               std::to_string(rect.getWidth() + SVG_HORIZONTAL_PADDING * 2) + " " +
                                               std::to_string(rect.getHeight() + SVG_VERTICAL_PADDING * 2) + " " + "\" " +
                   std::string("xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\">"));

    genSVGStyle(std::string(".") + TERMIANL_RECT_CLASS + std::string("{") +
                                   TERMIANL_RECT_STYLE + std::string("}") +
                std::string(".") + TERMIANL_TEXT_CLASS + std::string("{") +
                                   TERMIANL_TEXT_STYLE +
                                   std::string("text-anchor:middle;") +
                                   std::string("font-size:") + std::to_string(TERMIANL_FONT_SIZE) + std::string("px;}") +
                std::string(".") + SYMBOL_RECT_CLASS + std::string("{") +
                                   SYMBOL_RECT_STYLE + std::string("}") +
                std::string(".") + SYMBOL_TEXT_CLASS + std::string("{") +
                                   SYMBOL_TEXT_STYLE +
                                   std::string("text-anchor:middle;") +
                                   std::string("font-size:") + std::to_string(SYMBOL_FONT_SIZE) + std::string("px;}") +
                std::string(".") + PATH_CLASS + std::string("{") +
                                   PATH_STYLE + std::string("}") +
                std::string(".") + RULE_TEXT_CLASS + std::string("{") +
                                   RULE_TEXT_STYLE +
                                   std::string("font-size:") + std::to_string(RULE_FONT_SIZE) + std::string("px;}") +
                std::string(".") + RULE_PATH_EDGE_CLASS + std::string("{") +
                                   RULE_PATH_EDGE_STYLE + std::string("}"));

    genSVGText(RULE_TEXT_CLASS,
               rect.getLeft(), rect.getTop() + BASIC_HEIGHT / 2,
               node->getNameString() + ":");

    genNodeSVG(node->getNode());

    int x1 = rect.getLeft();
    int x2 = rect.getLeft() + RULE_HORIZONTAL_PADDING + BASIC_HORIZONTAL_PADDING;

    int x3 = rect.getRight() - RULE_HORIZONTAL_PADDING - BASIC_HORIZONTAL_PADDING;
    int x4 = rect.getRight();

    int y0 = node->getHorizontalLine();

    genSVGPath(PATH_CLASS, std::string("M") + std::to_string(x1) + " " +
                                              std::to_string(y0) + " " +
                           std::string("L") + std::to_string(x2) + " " +
                                              std::to_string(y0) + " " +
                           std::string("M") + std::to_string(x4) + " " +
                                              std::to_string(y0) + " " +
                           std::string("L") + std::to_string(x3) + " " +
                                              std::to_string(y0));

    genSVGPath(RULE_PATH_EDGE_CLASS, std::string("M") + std::to_string(x1) + " " +
                                                        std::to_string(y0 - RULE_PATH_EDGE_LENGTH / 2) + " " +
                                     std::string("L") + std::to_string(x1) + " " +
                                                        std::to_string(y0 + RULE_PATH_EDGE_LENGTH / 2) + " " +
                                     std::string("M") + std::to_string(x4) + " " +
                                                        std::to_string(y0 - RULE_PATH_EDGE_LENGTH / 2) + " " +
                                     std::string("L") + std::to_string(x4) + " " +
                                                        std::to_string(y0 + RULE_PATH_EDGE_LENGTH / 2));

    genSVGDirectly("</svg>");
}

void SVGGenerator::genNodeSVG(OrNode* node)
{
    for (auto& n: node->getNodes()) {
        genNodeSVG(n);
    }

    if (node->getNodes().size() == 1) {
        return;
    }

    Rect rect = node->getNodeRect();

    int x01 = rect.getLeft() + BASIC_HORIZONTAL_PADDING;
    int x02 = rect.getLeft() + BASIC_HORIZONTAL_PADDING + BASIC_HORIZONTAL_PADDING;
    int x03 = node->getNodes()[0]->getNodeRect().getLeft() + BASIC_HORIZONTAL_PADDING;

    int x04 = node->getNodes()[0]->getNodeRect().getRight() - BASIC_HORIZONTAL_PADDING;
    int x05 = rect.getRight() - BASIC_HORIZONTAL_PADDING - BASIC_HORIZONTAL_PADDING;
    int x06 = rect.getRight() - BASIC_HORIZONTAL_PADDING;

    int y01 = node->getHorizontalLine();
    int y02 = node->getHorizontalLine() + BASIC_HORIZONTAL_PADDING;

    std::string path;
    path = std::string("M") + std::to_string(x01) + " " +
                              std::to_string(y01) + " " +
           std::string("L") + std::to_string(x03) + " " +
                              std::to_string(y01) + " " +
           std::string("M") + std::to_string(x01) + " " +
                              std::to_string(y01) + " " +
           std::string("Q") + std::to_string(x02) + " " +
                              std::to_string(y01) + " " +
                              std::to_string(x02) + " " +
                              std::to_string(y02) + " " +
           std::string("M") + std::to_string(x06) + " " +
                              std::to_string(y01) + " " +
           std::string("L") + std::to_string(x04) + " " +
                              std::to_string(y01) + " " +
           std::string("M") + std::to_string(x06) + " " +
                              std::to_string(y01) + " " +
           std::string("Q") + std::to_string(x05) + " " +
                              std::to_string(y01) + " " +
                              std::to_string(x05) + " " +
                              std::to_string(y02);
    genSVGPath(PATH_CLASS, path);

    int y0 = y02;
    for (int idx = 1, idx_end = node->getNodes().size(); idx != idx_end; idx++) {
        Node* sub_node = node->getNodes()[idx];
        Rect sub_rect  = sub_node->getNodeRect();

        int x1 = x02;
        int x2 = x02 + BASIC_HORIZONTAL_PADDING;
        int x3 = sub_rect.getLeft() + BASIC_HORIZONTAL_PADDING;

        int x4 = sub_rect.getRight() - BASIC_HORIZONTAL_PADDING;
        int x5 = x05 - BASIC_HORIZONTAL_PADDING;
        int x6 = x05;

        int y1 = sub_node->getHorizontalLine() - BASIC_HORIZONTAL_PADDING;
        int y2 = sub_node->getHorizontalLine();

        path = std::string("M") + std::to_string(x2) + " " +
                                  std::to_string(y2) + " " +
               std::string("L") + std::to_string(x3) + " " +
                                  std::to_string(y2) + " " +
               std::string("M") + std::to_string(x2) + " " +
                                  std::to_string(y2) + " " +
               std::string("Q") + std::to_string(x1) + " " +
                                  std::to_string(y2) + " " +
                                  std::to_string(x1) + " " +
                                  std::to_string(y1) + " " +
               std::string("L") + std::to_string(x1) + " " +
                                  std::to_string(y0) + " " +
               std::string("M") + std::to_string(x5) + " " +
                                  std::to_string(y2) + " " +
               std::string("L") + std::to_string(x4) + " " +
                                  std::to_string(y2) + " " +
               std::string("M") + std::to_string(x5) + " " +
                                  std::to_string(y2) + " " +
               std::string("Q") + std::to_string(x6) + " " +
                                  std::to_string(y2) + " " +
                                  std::to_string(x6) + " " +
                                  std::to_string(y1) + " " +
               std::string("L") + std::to_string(x6) + " " +
                                  std::to_string(y0);
        genSVGPath(PATH_CLASS, path);

        y0 = y1;
    }
}

void SVGGenerator::genNodeSVG(AndNode* node)
{
    for (auto& n: node->getNodes()) {
        genNodeSVG(n);
    }

    std::vector<int> x_start_vector;
    std::vector<int> x_end_vector;
    for (auto& n: node->getNodes()) {
        Rect sub_rect = n->getNodeRect();
        x_end_vector.push_back(sub_rect.getLeft() + BASIC_HORIZONTAL_PADDING);
        x_start_vector.push_back(sub_rect.getRight() - BASIC_HORIZONTAL_PADDING);
    }

    x_start_vector.pop_back();
    x_end_vector.erase(x_end_vector.begin());

    int y1 = node->getHorizontalLine();

    for (int idx = 0, idx_end = x_start_vector.size(); idx != idx_end; idx++) {
        genSVGPath(PATH_CLASS, std::string("M") + std::to_string(x_start_vector[idx]) + " " +
                                                  std::to_string(y1) + " " +
                               std::string("L") + std::to_string(x_end_vector[idx]) + " " +
                                                  std::to_string(y1));
    }
}

void SVGGenerator::genNodeSVG(StarNode* node)
{
    genNodeSVG(node->getPlusNode());

    Rect rect = node->getNodeRect();

    int x1 = rect.getLeft() + BASIC_HORIZONTAL_PADDING;
    int x2 = rect.getLeft() + BASIC_HORIZONTAL_PADDING + BASIC_HORIZONTAL_PADDING;
    int x3 = rect.getLeft() + BASIC_HORIZONTAL_PADDING + BASIC_HORIZONTAL_PADDING * 2;

    int x4 = rect.getRight() - BASIC_HORIZONTAL_PADDING - BASIC_HORIZONTAL_PADDING * 2;
    int x5 = rect.getRight() - BASIC_HORIZONTAL_PADDING - BASIC_HORIZONTAL_PADDING;
    int x6 = rect.getRight() - BASIC_HORIZONTAL_PADDING;

    int x0 = rect.getLeft() + BASIC_HORIZONTAL_PADDING + BASIC_HORIZONTAL_PADDING * 4;
    int x7 = rect.getRight() - BASIC_HORIZONTAL_PADDING - BASIC_HORIZONTAL_PADDING * 4;

    int y1 = node->getHorizontalLine();
    int y2 = node->getHorizontalLine() + BASIC_HORIZONTAL_PADDING;

    int y3 = rect.getBottom() - BASIC_HEIGHT / 2 - BASIC_HORIZONTAL_PADDING;
    int y4 = rect.getBottom() - BASIC_HEIGHT / 2;

    std::string path;
    path = std::string("M") + std::to_string(x0) + " " +
                              std::to_string(y1) + " " +
           std::string("L") + std::to_string(x1) + " " +
                              std::to_string(y1) + " " +
           std::string("Q") + std::to_string(x2) + " " +
                              std::to_string(y1) + " " +
                              std::to_string(x2) + " " +
                              std::to_string(y2) + " " +
           std::string("L") + std::to_string(x2) + " " +
                              std::to_string(y3) + " " +
           std::string("Q") + std::to_string(x2) + " " +
                              std::to_string(y4) + " " +
                              std::to_string(x3) + " " +
                              std::to_string(y4) + " " +
           std::string("L") + std::to_string(x4) + " " +
                              std::to_string(y4) + " " +
           std::string("Q") + std::to_string(x5) + " " +
                              std::to_string(y4) + " " +
                              std::to_string(x5) + " " +
                              std::to_string(y3) + " " +
           std::string("L") + std::to_string(x5) + " " +
                              std::to_string(y2) + " " +
           std::string("Q") + std::to_string(x5) + " " +
                              std::to_string(y1) + " " +
                              std::to_string(x6) + " " +
                              std::to_string(y1) + " " +
           std::string("L") + std::to_string(x7) + " " +
                              std::to_string(y1) + " " +
           std::string("M") + std::to_string(x1) + " " +
                              std::to_string(y1) + " " +
           std::string("L") + std::to_string(x3) + " " +
                              std::to_string(y1) + " " +
           std::string("M") + std::to_string(x4) + " " +
                              std::to_string(y1) + " " +
           std::string("L") + std::to_string(x6) + " " +
                              std::to_string(y1);
    genSVGPath(PATH_CLASS, path);
}

void SVGGenerator::genNodeSVG(PlusNode* node)
{
    genNodeSVG(node->getNode());

    Rect rect = node->getNodeRect();

    int x1 = rect.getLeft() + BASIC_HORIZONTAL_PADDING;
    int x2 = rect.getLeft() + BASIC_HORIZONTAL_PADDING * 2;
    int x3 = rect.getLeft() + BASIC_HORIZONTAL_PADDING * 3;

    int x4 = rect.getRight() - BASIC_HORIZONTAL_PADDING * 3;
    int x5 = rect.getRight() - BASIC_HORIZONTAL_PADDING * 2;
    int x6 = rect.getRight() - BASIC_HORIZONTAL_PADDING;

    int y1 = node->getHorizontalLine();
    int y2 = node->getHorizontalLine() - BASIC_HORIZONTAL_PADDING;

    int y3 = rect.getTop() + BASIC_HEIGHT / 2;
    int y4 = rect.getTop() + BASIC_HEIGHT / 2 - BASIC_HORIZONTAL_PADDING;

    std::string path;
    path = std::string("M") + std::to_string(x3) + " " +
                              std::to_string(y1) + " " +
           std::string("L") + std::to_string(x1) + " " +
                              std::to_string(y1) + " " +
           std::string("M") + std::to_string(x2) + " " +
                              std::to_string(y1) + " " +
           std::string("Q") + std::to_string(x1) + " " +
                              std::to_string(y1) + " " +
                              std::to_string(x1) + " " +
                              std::to_string(y2) + " " +
           std::string("L") + std::to_string(x1) + " " +
                              std::to_string(y3) + " " +
           std::string("Q") + std::to_string(x1) + " " +
                              std::to_string(y4) + " " +
                              std::to_string(x2) + " " +
                              std::to_string(y4) + " " +
           std::string("L") + std::to_string(x5) + " " +
                              std::to_string(y4) + " " +
           std::string("Q") + std::to_string(x6) + " " +
                              std::to_string(y4) + " " +
                              std::to_string(x6) + " " +
                              std::to_string(y3) + " " +
           std::string("L") + std::to_string(x6) + " " +
                              std::to_string(y2) + " " +
           std::string("Q") + std::to_string(x6) + " " +
                              std::to_string(y1) + " " +
                              std::to_string(x5) + " " +
                              std::to_string(y1) + " " +
           std::string("L") + std::to_string(x4) + " " +
                              std::to_string(y1) + " " +
           std::string("L") + std::to_string(x6) + " " +
                              std::to_string(y1);
    genSVGPath(PATH_CLASS, path);
}

void SVGGenerator::genNodeSVG(ParenNode* node)
{
    genNodeSVG(node->getNode());
}

void SVGGenerator::genNodeSVG(SymbolNode* node)
{
    Rect rect = node->getNodeRect();
    genSVGRect(SYMBOL_RECT_CLASS,
               rect.getLeft() + BASIC_HORIZONTAL_PADDING, rect.getTop() + BASIC_VERTICAL_PADDING,
               rect.getWidth() - BASIC_HORIZONTAL_PADDING * 2, rect.getHeight() - BASIC_VERTICAL_PADDING * 2,
               SYMBOL_RECT_RX);
    genSVGText(SYMBOL_TEXT_CLASS,
               rect.getLeft() + rect.getWidth() / 2, node->getHorizontalLine() + SYMBOL_FONT_SIZE / 3,
               node->getIdString());
}

void SVGGenerator::genNodeSVG(TerminalNode* node)
{
    Rect rect = node->getNodeRect();
    genSVGRect(TERMIANL_RECT_CLASS,
               rect.getLeft() + BASIC_HORIZONTAL_PADDING, rect.getTop() + BASIC_VERTICAL_PADDING,
               rect.getWidth() -  BASIC_HORIZONTAL_PADDING * 2, rect.getHeight() - BASIC_VERTICAL_PADDING * 2,
               TERMIANL_RECT_RX);
    genSVGText(TERMIANL_TEXT_CLASS,
               rect.getLeft() + rect.getWidth() / 2, node->getHorizontalLine() + TERMIANL_FONT_SIZE / 3,
               node->getTextString());
}

void SVGGenerator::genNodeSVG(EmptyNode* node)
{
    Rect rect = node->getNodeRect();
    std::string path = std::string("M") + std::to_string(rect.getLeft() + BASIC_HORIZONTAL_PADDING) + " " +
                                          std::to_string(node->getHorizontalLine()) + " " +
                       std::string("L") + std::to_string(rect.getRight() - BASIC_HORIZONTAL_PADDING) + " " +
                                          std::to_string(node->getHorizontalLine());
    genSVGPath(PATH_CLASS, path);
}

void SVGGenerator::genNodeSVG(Node* node)
{
    switch (node->getNodeClass()) {
        case Node::NodeClass::EmptyNode:
            genNodeSVG(static_cast<EmptyNode*>(node));
            break;
        case Node::NodeClass::TerminalNode:
            genNodeSVG(static_cast<TerminalNode*>(node));
            break;
        case Node::NodeClass::SymbolNode:
            genNodeSVG(static_cast<SymbolNode*>(node));
            break;
        case Node::NodeClass::ParenNode:
            genNodeSVG(static_cast<ParenNode*>(node));
            break;
        case Node::NodeClass::PlusNode:
            genNodeSVG(static_cast<PlusNode*>(node));
            break;
        case Node::NodeClass::StarNode:
            genNodeSVG(static_cast<StarNode*>(node));
            break;
        case Node::NodeClass::AndNode:
            genNodeSVG(static_cast<AndNode*>(node));
            break;
        case Node::NodeClass::OrNode:
            genNodeSVG(static_cast<OrNode*>(node));
            break;
        case Node::NodeClass::RuleNode:
            assert(false && "should not arrive");
            break;
        default:
            assert(false && "unknown node class");
            break;
    }
}

void SVGGenerator::genSVGDirectly(const std::string& data)
{
    SVG_codes_.push_back(data);
}

void SVGGenerator::genSVGStyle(const std::string& style)
{
    SVG_codes_.push_back(std::string("<defs>") +
                         std::string("<style type=\"text/css\">") +
                         style +
                         std::string("</style>") +
                         std::string("</defs>"));
}

void SVGGenerator::genSVGRect(const std::string& rect_class, int x, int y, int width, int height, int rx)
{
    SVG_codes_.push_back(std::string("<rect ") +
                         std::string("class=\"") + rect_class + "\" " +
                         std::string("x=\"") + std::to_string(x) + "\" " +
                         std::string("y=\"") + std::to_string(y) + "\" " +
                         std::string("width=\"") + std::to_string(width) + "\" " +
                         std::string("height=\"") + std::to_string(height) + "\" " +
                         std::string("rx=\"") + std::to_string(rx) + "\" " +
                         std::string("/>"));
}

void SVGGenerator::genSVGText(const std::string& text_class, int x, int y, const std::string& text)
{
    std::string data;
    for (auto& ch: text) {
        switch (ch) {
            case '&':
                data += "&amp;";
                break;
            case '<':
                data += "&lt;";
                break;
            case '>':
                data += "&gt;";
                break;
            case '"':
                data += "&quot;";
                break;
            case '\'':
                data += "&apos;";
                break;
            default:
                data += ch;
                break;
        }
    }
    std::string text_block = std::string("<text ") +
                         std::string("class=\"") + text_class + "\" " +
                         std::string("x=\"") + std::to_string(x) + "\" " +
                         std::string("y=\"") + std::to_string(y) + "\" " +
                         std::string(">") +
                         data +
                         std::string("</text>");
    if (text_class.compare("rule_text") == 0) {
        text_block = std::string("<a id=\"") +
                            data.substr(0, data.length() - 1) +
                            std::string("\">") +
                            text_block +
                            std::string("</a>");
    } else if (text_class.compare("symbol_text") == 0) {
        text_block = std::string("<a xlink:href=\"#") +
                            data +
                            std::string("\">") +
                            text_block +
                            std::string("</a>");
    }
    SVG_codes_.push_back(text_block);
}

void SVGGenerator::genSVGPath(const std::string& path_class, const std::string& path)
{
    SVG_codes_.push_back(std::string("<path ") +
                         std::string("class=\"") + path_class + "\" " +
                         std::string("d=\"") + path + "\" " +
                         std::string("/>"));
}
