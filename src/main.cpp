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

#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "parse/parser.h"
#include "svg/placer.h"
#include "svg/svg_generator.h"

void display_usage();
std::string read_file_data(const char* file_name);
void generate_svg_file(const std::string& dir_name, const std::vector<RuleNode*>& nodes);
void generate_html_file(const std::string& file_name, const std::vector<RuleNode*>& nodes);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        display_usage();
        return EXIT_FAILURE;
    }

    const char* file_name = argv[1];
    std::string file_data = read_file_data(file_name);

    std::vector<RuleNode*> nodes;
    Parser parser(file_data);
    nodes = parser.parseSyntax();

    if (nodes.empty()) {
        std::cerr << parser.getErrorInfo() << "\n";
        return EXIT_FAILURE;
    }

    for (auto& n: nodes) {
        Placer::placeNode(n);
    }

    std::string dir_name = "grammar";
    mkdir(dir_name.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    generate_svg_file(dir_name, nodes);

    generate_html_file(dir_name + "/" + "all.html", nodes);

    return EXIT_SUCCESS;
}

void display_usage()
{
    std::cout << "\n"
              << "Usage:\n"
              << "railroad-diagram-generator grammar_file\n";
}

std::string read_file_data(const char* file_name)
{
    std::ifstream ifs(file_name);
    std::string file_data;
    if (ifs) {
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        file_data = buffer.str();
    } else {
        std::cerr << "Cannot open file: " << file_name << "\n\n";
        exit(EXIT_FAILURE);
    }
    ifs.close();
    return file_data;
}

void generate_svg_file(const std::string& dir_name, const std::vector<RuleNode*>& nodes)
{
    for (auto& n: nodes) {
        std::string file_name = dir_name + "/" + n->getNameString() + ".svg";
        std::ofstream ofs(file_name);
        if (!ofs) {
            std::cerr << "Cannot create svg file: " << file_name << "\n\n";
            exit(EXIT_FAILURE);
        }

        ofs << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
        SVGGenerator generator(n);
        for (auto& d: generator.getSVGCodes()) {
            ofs << d << "\n";
        }
    }
}

void generate_html_file(const std::string& file_name, const std::vector<RuleNode*>& nodes)
{
    std::ofstream ofs(file_name);
    if (!ofs) {
        std::cerr << "Cannot create html file: " << file_name << "\n\n";
        exit(EXIT_FAILURE);
    }

    ofs << "<!DOCTYPE html>\n"
        << "<html>\n"
        << "<body>\n";
    for (auto& n: nodes) {
        SVGGenerator generator(n);
        for (auto& d: generator.getSVGCodes()) {
            ofs << d << "\n";
        }
        ofs << "<br />\n"
            << "<br />\n";
    }
    ofs << "</body>\n"
        << "</html>\n";
}
