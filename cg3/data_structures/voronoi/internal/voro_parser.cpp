/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "voro_parser.h"

#include <cg3/utilities/tokenizer.h>

/**
 * @brief cg3::internal::parseAllVertices
 * @param container
 * @return a vector of vertices for every cell of the voronoi diagram
 */
std::vector<std::vector<cg3::Pointd> > cg3::internal::parseAllVertices(
        voro::container& container)
{
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator
    std::vector<std::vector<cg3::Pointd>> vertices;

    uint SIZE = 100000;
    char bufferVCoord[SIZE];
    memset(bufferVCoord, '\0', SIZE);
    FILE *fv = fopen("/dev/null", "w");
    setbuffer(fv, bufferVCoord, 100000);
    container.print_custom("%P", fv); //all the stdout goes in buffer

    std::string v_coords(bufferVCoord);

    //std::cerr << v_coords << "\n";

    uint nCells = std::count(v_coords.begin(), v_coords.end(), '\n');
    vertices.resize(nCells);

    for (uint i = 0; i < nCells; i++) {
        uint pos = v_coords.find("\n");
        std::string line(v_coords.begin(), v_coords.begin()+pos);
        v_coords = std::string(v_coords.begin()+pos+1, v_coords.end());

        cg3::Tokenizer tok(line, ' ');
        for (const std::string& v : tok) {

            cg3::Tokenizer t(v, ',');
            cg3::Pointd p(
                        std::stod(std::string(t[0].begin()+1, t[0].end())),
                        std::stod(t[1]),
                        std::stod(t[2]));

            vertices[i].push_back(p);
        }
    }

    return vertices;
}

/**
 * @brief cg3::internal::parseAllFaces
 * @param container
 * @return a vector of faces for every cell of the voronoi diagram
 */
std::vector<std::vector<std::vector<uint> > > cg3::internal::parseAllFaces(
        voro::container& container)
{
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator
    std::vector<std::vector<std::vector<uint> > > cells;
    uint SIZE = 100000;
    char bufferFIds[SIZE];
    memset(bufferFIds, '\0', SIZE);
    FILE *ff = fopen("/dev/null", "w");
    setbuffer(ff, bufferFIds, 100000);
    container.print_custom("%t", ff); //all the stdout goes in buffer
    std::string f_ids(bufferFIds);

    uint nCells = std::count(f_ids.begin(), f_ids.end(), '\n');

    for (uint i = 0; i < nCells; i++) {
        uint pos = f_ids.find("\n");
        std::string line(f_ids.begin(), f_ids.begin()+pos);
        f_ids = std::string(f_ids.begin()+pos+1, f_ids.end());
        std::vector<std::vector<uint>> cell;
        //parsing line and creating a cell
        cg3::Tokenizer tok(line, ' ');
        for (const std::string& f : tok) {
            std::vector<uint> face;

            cg3::Tokenizer t(f, ',');
            uint vid = std::stoi(std::string(t[0].begin()+1, t[0].end()));
            face.push_back(vid);
            for (uint k = 1; k < t.size(); ++k){
                vid = std::stoi(t[k]);
                face.push_back(vid);
            }
            std::reverse(face.begin(), face.end());

            cell.push_back(face);
        }

        cells.push_back(cell);
    }

    return cells;
}

/**
 * @brief cg3::internal::parseAdjacences
 * @param container
 * @return a vector of adjacences for every cell of the voronoi diagram, parallel to the vector of faces
 * negative numbers are for the cells that are adjacent to the bounds of the box container
 */
std::vector<std::vector<int> > cg3::internal::parseAdjacences(
        voro::container &container)
{
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator
    std::vector<std::vector<int> > adjs;
    uint SIZE = 100000;
    char bufferFIds[SIZE];
    memset(bufferFIds, '\0', SIZE);
    FILE *ff = fopen("/dev/null", "w");
    setbuffer(ff, bufferFIds, 100000);
    container.print_custom("%n", ff); //all the stdout goes in buffer

    std::string fadjs(bufferFIds);

    uint nCells = std::count(fadjs.begin(), fadjs.end(), '\n');

    for (uint i = 0; i < nCells; i++) {
        uint pos = fadjs.find("\n");
        std::string line(fadjs.begin(), fadjs.begin()+pos);
        fadjs = std::string(fadjs.begin()+pos+1, fadjs.end());
        std::vector<int> fadj;
        cg3::Tokenizer tok(line, ' ');
        for (const std::string& f : tok) {
            fadj.push_back(std::stoi(f));
        }
        adjs.push_back(fadj);
    }

    return adjs;
}
