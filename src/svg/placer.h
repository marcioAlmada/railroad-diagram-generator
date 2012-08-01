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

#ifndef PLACER_H_
#define PLACER_H_

#include "../ast/ast.h"

class Placer {

public:
    static Node* placeNode(RuleNode* node);
    static Node* placeNode(OrNode* node);
    static Node* placeNode(AndNode* node);
    static Node* placeNode(StarNode* node);
    static Node* placeNode(PlusNode* node);
    static Node* placeNode(ParenNode* node);
    static Node* placeNode(SymbolNode* node);
    static Node* placeNode(TerminalNode* node);
    static Node* placeNode(EmptyNode* node);
    static Node* placeNode(Node* node);

private:
    Placer() = delete;
    Placer(const Placer&) = delete;
    void operator=(const Placer&) = delete;

};

#endif // PLACER_H_
