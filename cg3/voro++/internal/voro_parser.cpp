/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "voro_parser.h"

#include <cg3/utilities/tokenizer.h>

namespace cg3 {
namespace voro {
namespace internal {

const uint SIZE = 4000000; //buffer sizes

/**
 * @brief cg3::internal::parseAllVertices
 * @param container
 * @return a vector of vertices for every cell of the voronoi diagram
 */
CG3_INLINE std::vector<std::vector<cg3::Point3d> > parseAllVertices(
		::voro::container& container)
{
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator
    std::vector<std::vector<cg3::Point3d>> vertices;

    std::vector<uint> ids;
    char bufferSitesIDs[SIZE];
    memset(bufferSitesIDs, '\0', SIZE);
    FILE *fsids = fopen("/dev/null", "w");
    setbuffer(fsids, bufferSitesIDs, SIZE);
    container.print_custom("%i", fsids); //all the stdout goes in buffer
    std::string sitesIds(bufferSitesIDs);
    fclose(fsids);
    uint nCells = std::count(sitesIds.begin(), sitesIds.end(), '\n');
    cg3::Tokenizer tids(sitesIds, '\n');
    for (const std::string& s : tids)
        ids.push_back(std::stoi(s));

    char bufferVCoord[SIZE];
    memset(bufferVCoord, '\0', SIZE);
    FILE *fv = fopen("/dev/null", "w");
    setbuffer(fv, bufferVCoord, SIZE);
    container.print_custom("%P", fv); //all the stdout goes in buffer

    std::string v_coords(bufferVCoord);
    fclose(fv);

    vertices.resize(nCells);

    for (uint i = 0; i < nCells; i++) {
        uint pos = v_coords.find("\n");
        std::string line(v_coords.begin(), v_coords.begin()+pos);
        v_coords = std::string(v_coords.begin()+pos+1, v_coords.end());

        cg3::Tokenizer tok(line, ' ');
        for (const std::string& v : tok) {

            cg3::Tokenizer t(v, ',');
            assert(t.size() == 3); //if this assert fails, voro++ didn't give a good output string
            cg3::Point3d p(
                        std::stod(std::string(t[0].begin()+1, t[0].end())),
                        std::stod(t[1]),
                        std::stod(t[2]));

            vertices[ids[i]].push_back(p);
        }
    }

    return vertices;
}

/**
 * @brief cg3::internal::parseAllFaces
 * @param container
 * @return a vector of faces for every cell of the voronoi diagram
 */
CG3_INLINE std::vector<std::vector<std::vector<uint> > > parseAllFaces(
		::voro::container& container)
{
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator
    std::vector<std::vector<std::vector<uint> > > cells;
    std::vector<uint> ids;
    char bufferSitesIDs[SIZE];
    memset(bufferSitesIDs, '\0', SIZE);
    FILE *fsids = fopen("/dev/null", "w");
    setbuffer(fsids, bufferSitesIDs, SIZE);
    container.print_custom("%i", fsids); //all the stdout goes in buffer
    std::string sitesIds(bufferSitesIDs);
    fclose(fsids);
    uint nCells = std::count(sitesIds.begin(), sitesIds.end(), '\n');
    cg3::Tokenizer tids(sitesIds, '\n');
    for (const std::string& s : tids)
        ids.push_back(std::stoi(s));


    char bufferFIds[SIZE];
    memset(bufferFIds, '\0', SIZE);
    FILE *ff = fopen("/dev/null", "w");
    setbuffer(ff, bufferFIds, SIZE);
    container.print_custom("%t", ff); //all the stdout goes in buffer
    std::string f_ids(bufferFIds);
    fclose(ff);

    cells.resize(nCells);
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

        cells[ids[i]] = cell;
    }

    return cells;
}

/**
 * @brief cg3::internal::parseAdjacences
 * @param container
 * @return a vector of adjacences for every cell of the voronoi diagram, parallel to the vector of faces
 * negative numbers are for the cells that are adjacent to the bounds of the box container
 */
CG3_INLINE std::vector<std::vector<int> > parseAdjacences(
		::voro::container &container)
{
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator
    std::vector<std::vector<int> > adjs;
    std::vector<uint> ids;
    char bufferSitesIDs[SIZE];
    memset(bufferSitesIDs, '\0', SIZE);
    FILE *fsids = fopen("/dev/null", "w");
    setbuffer(fsids, bufferSitesIDs, SIZE);
    container.print_custom("%i", fsids); //all the stdout goes in buffer
    std::string sitesIds(bufferSitesIDs);
    fclose(fsids);
    uint nCells = std::count(sitesIds.begin(), sitesIds.end(), '\n');
    cg3::Tokenizer tids(sitesIds, '\n');
    for (const std::string& s : tids)
        ids.push_back(std::stoi(s));

    char bufferFIds[SIZE];
    memset(bufferFIds, '\0', SIZE);
    FILE *ff = fopen("/dev/null", "w");
    setbuffer(ff, bufferFIds, SIZE);
    container.print_custom("%n", ff); //all the stdout goes in buffer

    std::string fadjs(bufferFIds);
    fclose(ff);

    adjs.resize(nCells);
    for (uint i = 0; i < nCells; i++) {
        uint pos = fadjs.find("\n");
        std::string line(fadjs.begin(), fadjs.begin()+pos);
        fadjs = std::string(fadjs.begin()+pos+1, fadjs.end());
        std::vector<int> fadj;
        cg3::Tokenizer tok(line, ' ');
        for (const std::string& f : tok) {
            fadj.push_back(std::stoi(f));
        }
        adjs[ids[i]] = fadj;
    }

    return adjs;
}

} //namespace cg3::voro::internal
} //namespace cg3::voro
} //namespace cg3
