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

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <vector>
#include "../basic/rect.h"

class Node {

public:
    enum class NodeClass {
        EmptyNode,
        TerminalNode,
        SymbolNode,
        ParenNode,
        PlusNode,
        StarNode,
        AndNode,
        OrNode,
        RuleNode,
    };

public:
    explicit Node(NodeClass c)
        : node_class_(c) {}

    virtual ~Node() {}

    NodeClass getNodeClass()const { return node_class_; }

    void setNodeRect(const Rect& rect) { node_rect_ = rect; }
    const Rect& getNodeRect()const { return node_rect_; }

    void setHorizontalLine(int x) { horizontal_line_ = x; }
    int getHorizontalLine()const { return horizontal_line_; }

private:
    NodeClass node_class_;
    Rect node_rect_;
    int horizontal_line_;

private:
    Node(const Node&) = delete;
    void operator=(const Node&) = delete;

};


class EmptyNode: public Node {

public:
    EmptyNode()
        : Node(NodeClass::EmptyNode) {}

    virtual ~EmptyNode() {}

};


class TerminalNode: public Node {

public:
    explicit TerminalNode(const std::string& text)
        : Node(NodeClass::TerminalNode),
          text_(text) {}

    virtual ~TerminalNode() {}

    const std::string& getTextString()const { return text_; }

private:
    std::string text_;

};


class SymbolNode: public Node {

public:
    explicit SymbolNode(const std::string& id)
        : Node(NodeClass::SymbolNode),
          id_(id) {}

    virtual ~SymbolNode() {}

    const std::string& getIdString()const { return id_; }

private:
    std::string id_;

};


class ParenNode: public Node {

public:
    explicit ParenNode(Node* n)
        : Node(NodeClass::ParenNode),
          node_(n) {}

    virtual ~ParenNode() { delete node_; }

    Node* getNode() { return node_; }
    const Node* getNode()const { return node_; }

private:
    Node* node_;

};


class PlusNode: public Node {

public:
    explicit PlusNode(Node* n)
        : Node(NodeClass::PlusNode),
          node_(n) {}

    virtual ~PlusNode() { delete node_; }

    Node* getNode() { return node_; }
    const Node* getNode()const { return node_; }

private:
    Node* node_;

};


class StarNode: public Node {

public:
    explicit StarNode(PlusNode* n)
        : Node(NodeClass::StarNode),
          node_(n) {}

    virtual ~StarNode() { delete node_; }

    PlusNode* getPlusNode() { return node_; }
    const PlusNode* getPlusNode()const { return node_; }

private:
    PlusNode* node_;

};


class AndNode: public Node {

public:
    explicit AndNode(const std::vector<Node*>& nodes)
        : Node(NodeClass::AndNode),
          nodes_(nodes) {}

    virtual ~AndNode() { for (auto& n: nodes_) { delete n; } }

    const std::vector<Node*>& getNodes()const { return nodes_; }

private:
    std::vector<Node*> nodes_;

};


class OrNode: public Node {

public:
    explicit OrNode(const std::vector<Node*>& nodes)
        : Node(NodeClass::OrNode),
          nodes_(nodes) {}

    virtual ~OrNode() { for (auto& n: nodes_) { delete n; } }

    const std::vector<Node*>& getNodes()const { return nodes_; }

private:
    std::vector<Node*> nodes_;

};


class RuleNode: public Node {

public:
    RuleNode(const std::string& name, Node* n)
        : Node(NodeClass::RuleNode),
          name_(name), node_(n) {}

    virtual ~RuleNode() { delete node_; }

    const std::string& getNameString()const { return name_; }

    Node* getNode() { return node_; }
    const Node* getNode()const { return node_; }

private:
    std::string name_;
    Node* node_;

};

#endif // NODE_H_
