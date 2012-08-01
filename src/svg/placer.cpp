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

#include "placer.h"
#include <cassert>
#include "../style/style.h"

static void adjustTopLeft(Node* node, const Point& position);
static void adjustTop(Node* node, int y);
static void adjustLeft(Node* node, int x);

Node* Placer::placeNode(RuleNode* node)
{
    placeNode(node->getNode());

    Rect rect = node->getNode()->getNodeRect();
    rect.setTop(rect.getTop() - BASIC_HEIGHT);
    rect.setLeft(rect.getLeft() - RULE_HORIZONTAL_PADDING);
    rect.setRight(rect.getRight() + RULE_HORIZONTAL_PADDING);
    node->setNodeRect(rect);
    node->setHorizontalLine(0);
    adjustLeft(node, 0);

    return node;
}

Node* Placer::placeNode(OrNode* node)
{
    for (auto& n: node->getNodes()) {
        placeNode(n);
    }

    if (node->getNodes().size() == 1) {
        Rect rect = node->getNodes()[0]->getNodeRect();
        node->setNodeRect(rect);
        node->setHorizontalLine(0);
        return node;
    }

    int max_top    = node->getNodes()[0]->getNodeRect().getTop();
    int max_bottom = max_top;
    int max_width  = 0;
    for (auto& n: node->getNodes()) {
        adjustTop(n, max_bottom);
        Rect rect  = n->getNodeRect();
        max_bottom+= rect.getHeight();
        max_width  = std::max(max_width, rect.getWidth());
    }
    node->setNodeRect(Rect(-BASIC_HORIZONTAL_PADDING * 3, max_top,
                           max_width + BASIC_HORIZONTAL_PADDING * 6, max_bottom - max_top));
    node->setHorizontalLine(0);
    adjustLeft(node, 0);

    return node;
}

Node* Placer::placeNode(AndNode* node)
{
    for (auto& n: node->getNodes()) {
        placeNode(n);
    }

    int max_top     = 0;
    int max_bottom  = 0;
    int total_width = 0;
    for (auto& n: node->getNodes()) {
        adjustLeft(n, total_width);
        Rect rect   = n->getNodeRect();
        max_top     = std::min(max_top, rect.getTop());
        max_bottom  = std::max(max_bottom, rect.getBottom());
        total_width+= rect.getWidth();
    }
    node->setNodeRect(Rect(0, max_top, total_width, max_bottom - max_top));
    node->setHorizontalLine(0);

    return node;
}

Node* Placer::placeNode(StarNode* node)
{
    placeNode(node->getPlusNode());

    Rect rect = node->getPlusNode()->getNodeRect();
    rect.setBottom(rect.getBottom() + BASIC_HEIGHT);
    rect.setLeft(rect.getLeft() - BASIC_HORIZONTAL_PADDING * 2);
    rect.setRight(rect.getRight() + BASIC_HORIZONTAL_PADDING * 2);
    node->setNodeRect(rect);
    node->setHorizontalLine(0);
    adjustLeft(node, 0);

    return node;
}

Node* Placer::placeNode(PlusNode* node)
{
    placeNode(node->getNode());

    Rect rect = node->getNode()->getNodeRect();
    rect.setTop(rect.getTop() - BASIC_HEIGHT);
    rect.setLeft(rect.getLeft() - BASIC_HORIZONTAL_PADDING * 2);
    rect.setRight(rect.getRight() + BASIC_HORIZONTAL_PADDING * 2);
    node->setNodeRect(rect);
    node->setHorizontalLine(0);
    adjustLeft(node, 0);

    return node;
}

Node* Placer::placeNode(ParenNode* node)
{
    placeNode(node->getNode());

    Rect rect = node->getNode()->getNodeRect();
    node->setNodeRect(rect);
    node->setHorizontalLine(0);

    return node;
}

Node* Placer::placeNode(SymbolNode* node)
{
    const int width  = SYMBOL_RECT_WIDTH(node->getIdString().size()) + BASIC_HORIZONTAL_PADDING * 2;
    const int height = SYMBOL_RECT_HEIGHT + BASIC_VERTICAL_PADDING * 2;
    node->setNodeRect(Rect(0, -height / 2, width, height));
    node->setHorizontalLine(0);

    return node;
}

Node* Placer::placeNode(TerminalNode* node)
{
    const int width  = TERMIANL_RECT_WIDTH(node->getTextString().size()) + BASIC_HORIZONTAL_PADDING * 2;
    const int height = TERMIANL_RECT_HEIGHT + BASIC_VERTICAL_PADDING * 2;
    node->setNodeRect(Rect(0, -height / 2, width, height));
    node->setHorizontalLine(0);

    return node;
}

Node* Placer::placeNode(EmptyNode* node)
{
    const int width  = BASIC_WIDTH + BASIC_HORIZONTAL_PADDING * 2;
    const int height = BASIC_HEIGHT + BASIC_VERTICAL_PADDING * 2;
    node->setNodeRect(Rect(0, -height / 2, width, height));
    node->setHorizontalLine(0);

    return node;
}

Node* Placer::placeNode(Node* node)
{
    switch (node->getNodeClass()) {
        case Node::NodeClass::EmptyNode:
            return placeNode(static_cast<EmptyNode*>(node));
        case Node::NodeClass::TerminalNode:
            return placeNode(static_cast<TerminalNode*>(node));
        case Node::NodeClass::SymbolNode:
            return placeNode(static_cast<SymbolNode*>(node));
        case Node::NodeClass::ParenNode:
            return placeNode(static_cast<ParenNode*>(node));
        case Node::NodeClass::PlusNode:
            return placeNode(static_cast<PlusNode*>(node));
        case Node::NodeClass::StarNode:
            return placeNode(static_cast<StarNode*>(node));
        case Node::NodeClass::AndNode:
            return placeNode(static_cast<AndNode*>(node));
        case Node::NodeClass::OrNode:
            return placeNode(static_cast<OrNode*>(node));
        case Node::NodeClass::RuleNode:
            return placeNode(static_cast<RuleNode*>(node));
        default:
            assert(false && "unknown node class");
            return 0;
    }
}

static void adjustTopLeft(Node* node, const Point& position)
{
    std::vector<Node*> sub_nodes;
    switch (node->getNodeClass()) {
        case Node::NodeClass::EmptyNode:
            break;
        case Node::NodeClass::TerminalNode:
            break;
        case Node::NodeClass::SymbolNode:
            break;
        case Node::NodeClass::ParenNode:
            sub_nodes.push_back(static_cast<ParenNode*>(node)->getNode());
            break;
        case Node::NodeClass::PlusNode:
            sub_nodes.push_back(static_cast<PlusNode*>(node)->getNode());
            break;
        case Node::NodeClass::StarNode:
            sub_nodes.push_back(static_cast<StarNode*>(node)->getPlusNode());
            break;
        case Node::NodeClass::AndNode:
            for (auto& n: static_cast<AndNode*>(node)->getNodes()) {
                sub_nodes.push_back(n);
            }
            break;
        case Node::NodeClass::OrNode:
            for (auto& n: static_cast<OrNode*>(node)->getNodes()) {
                sub_nodes.push_back(n);
            }
            break;
        case Node::NodeClass::RuleNode:
            sub_nodes.push_back(static_cast<RuleNode*>(node)->getNode());
            break;
        default:
            assert(false && "unknown node class");
            break;
    }

    Rect rect    = node->getNodeRect();
    int rect_top = rect.getTop();
    for (auto& sub_node: sub_nodes) {
        Rect sub_rect = sub_node->getNodeRect();
        adjustTopLeft(sub_node, position - rect.getTopLeft() + sub_rect.getTopLeft());
    }
    rect.moveTopLeftTo(position);
    node->setNodeRect(rect);
    node->setHorizontalLine(node->getHorizontalLine() - rect_top + position.getY());
}

static void adjustTop(Node* node, int y)
{
    adjustTopLeft(node, Point(node->getNodeRect().getLeft(), y));
}

static void adjustLeft(Node* node, int x)
{
    adjustTopLeft(node, Point(x, node->getNodeRect().getTop()));
}
