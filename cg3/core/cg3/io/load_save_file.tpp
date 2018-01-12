/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "load_save_file.h"
#include "../utilities/tokenizer.h"

namespace cg3 {

inline void loadSave::ObjManager::manageColor(std::ofstream &fp, std::ofstream &fmtu, const Color &c, ColorMode colorMod, Color &actualColor, std::map<Color, std::string> &colors){
    std::string stringColor = "COLOR";
    if (c != actualColor) {
        std::map<Color, std::string>::iterator it = colors.find(c);
        if (it == colors.end()) {
            std::stringstream stm;
            stm << stringColor << colors.size();
            std::string mtlColor = stm.str();
            fmtu << "newmtl " << mtlColor << "\n";
            if (colorMod == RGB){
                fmtu << "Kd " << c.redF() << " " << c.greenF() << " " << c.blueF() << "\n";
            }
            else {
                ///TODO
                fmtu << "Kd " << c.redF() << " " << c.greenF() << " " << c.blueF() << "\n";
            }
            colors[c] = mtlColor;
            fp << "usemtl " << mtlColor << "\n";
            actualColor = c;
        }
        else {
            fp << "usemtl " << colors[c] << "\n";
            actualColor = c;
        }
    }
}

inline void loadSave::ObjManager::manageFileNames(const std::string &objfilename, std::string &mtufilename, std::string &mtufilenopath){
    size_t lastindex = objfilename.find_last_of(".");
    assert(lastindex != objfilename.size());
    mtufilename = objfilename.substr(0, lastindex);
    mtufilename += ".mtu";
    //removing global path for mtu file
    size_t lastSlash = mtufilename.find_last_of("/");
    if (lastSlash != mtufilename.size()){
        mtufilenopath = mtufilename.substr(lastSlash+1, mtufilename.size());
    }
    else{
        mtufilenopath = mtufilename;
    }
}

inline bool loadSave::ObjManager::loadMtlFile(const std::string &mtuFile, std::map<std::string, Color> &mapColors){
    std::ifstream mtufile(mtuFile.c_str());
    std::string line;
    if (mtufile.is_open()){
        while(std::getline(mtufile,line)) {
            cg3::Tokenizer spaceTokenizer(line, ' ');

            if (spaceTokenizer.begin() != spaceTokenizer.end()){

                cg3::Tokenizer::iterator token = spaceTokenizer.begin();
                if (*token == "newmtl"){
                    ++token;
                    std::string colorname = *token;
                    do {
                        std::getline(mtufile,line);
                        spaceTokenizer = Tokenizer(line, ' ');
                        token = spaceTokenizer.begin();
                    } while (*token != "Kd");
                    std::string r = *(++token);
                    std::string g = *(++token);
                    std::string b = *(++token);

                    std::istringstream rstr(r), gstr(g), bstr(b);
                    float  rf, gf, bf;
                    rstr >> rf;
                    gstr >> gf;
                    bstr >> bf;
                    mapColors[colorname] = Color(rf*255, gf*255, bf*255);
                }
            }
        }
        mtufile.close();
        return true;
    }
    return false;
}

template <typename T>
inline Color loadSave::getColor(size_t baseIndex, const T arrayColors[], ColorMode colorMod){
    Color c;
    if (std::is_same<T, int>::value || std::is_same<T, unsigned int>::value || std::is_same<T, char>::value || std::is_same<T, unsigned char>::value){
        if (colorMod == RGB){
            c = Color(arrayColors[baseIndex], arrayColors[baseIndex+1], arrayColors[baseIndex+2]);
        }
        else{
            c = Color(arrayColors[baseIndex], arrayColors[baseIndex+1], arrayColors[baseIndex+2], arrayColors[baseIndex+3]);
        }

    }
    else {
        if (colorMod == RGB){
            c = Color(arrayColors[baseIndex]*255, arrayColors[baseIndex+1]*255, arrayColors[baseIndex+2]*255);
        }
        else {
            c = Color(arrayColors[baseIndex]*255, arrayColors[baseIndex+1]*255, arrayColors[baseIndex+2]*255, arrayColors[baseIndex+3]*255);
        }
    }
    return c;
}

template <typename A, typename B, typename C , typename T , typename V , typename W>
bool loadSave::saveMeshOnObj(const std::string& filename, size_t nVertices, size_t nFaces, const A vertices[], const B faces[], MeshType meshType, int modality, const C verticesNormals[], ColorMode colorMod, const T verticesColors[], const V faceColors[], const W polygonSizes[]) {
    std::string objfilename, mtufilename, mtufilenopath;
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator
    std::ofstream fp, fmtu;
    bool color = false;
    std::map<Color, std::string> colors;
    Color actualColor;
    size_t lastindex = filename.find_last_of(".");
    if (lastindex != filename.size())
        objfilename = filename;
    else
        objfilename = filename + ".obj";

    //managing mtu filename
    if (modality & COLOR_FACES || modality & COLOR_VERTICES){
        color = true;
        ObjManager::manageFileNames(objfilename, mtufilename, mtufilenopath);
        fmtu.open(mtufilename.c_str());
        if (!fmtu)
            return false;
    }

    fp.open (objfilename);
    if(!fp) {
        return false;
    }
    fp.precision(6);
    fp.setf( std::ios::fixed, std:: ios::floatfield );

    if (color){
        fp << "mtllib " << mtufilenopath << "\n";

    }

    for(size_t i=0; i<nVertices*3; i+=3) {

        if (modality & NORMAL_VERTICES) {
            fp << "vn " << verticesNormals[i] << " " << verticesNormals[i+1] << " " << verticesNormals[i+2] << std::endl;
        }
        fp << "v " << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] ;
        if (modality & COLOR_VERTICES){
            Color c = getColor(colorMod == RGB ? i : (i/3)*4, verticesColors, colorMod);
            fp << " " << c.redF() << " " << c.blueF() << " " << c.greenF();
        }
        fp << std::endl;
    }

    if (meshType == TRIANGLE_MESH) {
        for(size_t i=0; i<nFaces*3; i+=3) {
            if (modality & COLOR_FACES){
                Color c = getColor(colorMod == RGB ? i : (i/3)*4, faceColors, colorMod);;
                ObjManager::manageColor(fp, fmtu, c, colorMod, actualColor, colors);
            }
            fp << "f " << faces[i]+1 << " " << faces[i+1]+1 << " " << faces[i+2]+1 << std::endl;
        }
    }
    else if (meshType ==  QUAD_MESH) {
        for(size_t i=0; i<nFaces*4; i+=4) {
            if (modality & COLOR_FACES){
                Color c = getColor(colorMod == RGB ? (i/4)*3 : i, faceColors, colorMod);;
                ObjManager::manageColor(fp, fmtu, c, colorMod, actualColor, colors);
            }
            fp << "f " << faces[i]+1 << " " << faces[i+1]+1 << " " << faces[i+2]+1<< " " << faces[i+3]+1 << std::endl;
        }
    }
    else if (meshType ==  POLYGON_MESH) {
        size_t j = 0;
        for (size_t i = 0; i < nFaces; i++){
            if (modality & COLOR_FACES){
                Color c = getColor(colorMod == RGB ? i*3 : i*4, faceColors, colorMod);
                ObjManager::manageColor(fp, fmtu, c, colorMod, actualColor, colors);
            }
            fp << "f ";
            for (size_t k = 0; k < polygonSizes[i]; k++)
                fp << faces[j+k]+1 << " ";
            fp << "\n";
            j += polygonSizes[i];
        }
    }
    else assert(0);

    fp.close();
    if (color)
        fmtu.close();
    return true;
}

template <typename A, typename B, typename C, typename T, typename V, typename W >
inline bool loadSave::saveMeshOnPly(const std::string& filename, size_t nVertices, size_t nFaces, const A vertices[], const B faces[], MeshType meshType, int modality, const C verticesNormals[], ColorMode colorMod, const T verticesColors[], const V faceColors[], const W polygonSizes[]) {
    std::string plyfilename;
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator
    std::ofstream fp;
    size_t lastindex = filename.find_last_of(".");
    if (lastindex != filename.size())
        plyfilename = filename;
    else
        plyfilename = filename + ".ply";

    fp.open (plyfilename);
    if(!fp) {
        return false;
    }
    fp.precision(6);
    fp.setf( std::ios::fixed, std:: ios::floatfield );

    //header
    fp << "ply\nformat ascii 1.0\n";
    fp << "element vertex " << nVertices << "\n";
    fp << "property float x\nproperty float y\nproperty float z\n";
    if (modality & NORMAL_VERTICES){
        fp << "property float nx\nproperty float ny\nproperty float nz\n";
    }
    if (modality & COLOR_VERTICES){
        if (colorMod == RGB)
            fp << "property uchar red\nproperty uchar green\nproperty uchar blue\n";
        else
            fp << "property uchar red\nproperty uchar green\nproperty uchar blue\nproperty uchar alpha\n";
    }
    fp << "element face " << nFaces << "\n";
    fp << "property list uchar int vertex_indices\n";
    if (modality & COLOR_FACES){
        if (colorMod == RGB)
            fp << "property uchar red\nproperty uchar green\nproperty uchar blue\n";
        else
            fp << "property uchar red\nproperty uchar green\nproperty uchar blue\nproperty uchar alpha\n";
    }
    fp << "end_header\n";
    //

    for(size_t i=0; i<nVertices*3; i+=3) {
        fp << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2];
        if (modality & NORMAL_VERTICES) {
            fp << " " << verticesNormals[i] << " " << verticesNormals[i+1] << " " << verticesNormals[i+2];
        }
        if (modality & COLOR_VERTICES){
            Color c = getColor(colorMod == RGB ? i : (i/3)*4, verticesColors, colorMod);
            fp << " " << c.red() << " " << c.green() << " " << c.blue();
            if (colorMod == RGBA)
                fp << " " << c.alpha();
        }
        fp << std::endl;
    }

    if (meshType ==  TRIANGLE_MESH) {
        for(size_t i=0; i<nFaces*3; i+=3) {
            fp << "3 " << faces[i] << " " << faces[i+1] << " " << faces[i+2];
            if (modality & COLOR_FACES){
                Color c = getColor(colorMod == RGB ? i : (i/3)*4, faceColors, colorMod);;
                fp << " " << c.red() << " " << c.green() << " " << c.blue();
                if (colorMod == RGBA)
                    fp << " " << c.alpha();
            }
            fp << std::endl;

        }
    }
    else if (meshType ==  QUAD_MESH) {
        for(size_t i=0; i<nFaces*4; i+=4) {
            fp << "4 " << faces[i] << " " << faces[i+1] << " " << faces[i+2]<< " " << faces[i+3];
            if (modality & COLOR_FACES){
                Color c = getColor(colorMod == RGB ? (i/4)*3 : i, verticesColors, colorMod);;
                fp << " " << c.red() << " " << c.green() << " " << c.blue();
                if (colorMod == RGBA)
                    fp << " " << c.alpha();
            }
            fp << std::endl;

        }
    }
    else if (meshType ==  POLYGON_MESH) {
        size_t j = 0;
        for (size_t i = 0; i < nFaces; i++){

            fp << polygonSizes[i] << " ";
            for (size_t k = 0; k < polygonSizes[i]; k++)
                fp << faces[j+k] << " ";
            j += polygonSizes[i];
            if (modality & COLOR_FACES){
                Color c = getColor(colorMod == RGB ? i*3 : i*4, faceColors, colorMod);
                fp << c.red() << " " << c.green() << " " << c.blue();
                if (colorMod == RGBA)
                    fp << " " << c.alpha();
            }
            fp << std::endl;
        }
    }
    else assert(0);

    fp.close();
    return true;
}

template <typename T, typename V, typename C, typename W>
bool loadSave::loadMeshFromObj(const std::string& filename, std::list<T>& coords, std::list<V>& faces, loadSave::MeshType & meshType, int &modality, std::list<C> &verticesNormals, std::list<Color> &verticesColors, std::list<Color> &faceColors, std::list<W> &faceSizes) {
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator

    static std::string vertex = "v";
    static std::string vertexNormal = "vn";
    static std::string face   = "f";

    std::ifstream file(filename.c_str());
    std::string   line;
    bool usemtu = false;
    bool first = true;
    std::map<std::string, Color> mapColors;
    Color actualColor;

    coords.clear();
    faces.clear();
    verticesNormals.clear();
    verticesColors.clear();
    faceColors.clear();
    modality = 0;

    if(!file.is_open()) {
        return false;
    }
    while(std::getline(file,line)) {

        cg3::Tokenizer spaceTokenizer(line, ' ');

        if (spaceTokenizer.begin() != spaceTokenizer.end()) {

            cg3::Tokenizer::iterator token = spaceTokenizer.begin();
            std::string header = *token;

            if (header == "mtllib"){
                modality |= COLOR_FACES;
                usemtu = true;
                std::string mtufilename = *(++token);
                size_t lastSlash = filename.find_last_of("/");
                if (lastSlash < filename.size()){
                    std::string path = filename.substr(0, lastSlash);
                    mtufilename = path + "/" + mtufilename;
                }
                if (! ObjManager::loadMtlFile(mtufilename, mapColors))
                    usemtu = false;
            }

            if (header == vertexNormal) {
                modality |= NORMAL_VERTICES;
                std::string x = *(++token);
                std::string y = *(++token);
                std::string z = *(++token);

                verticesNormals.push_back(std::stod(x));
                verticesNormals.push_back(std::stod(y));
                verticesNormals.push_back(std::stod(z));
            }

            // Handle
            //
            // v 0.123 0.234 0.345
            // v 0.123 0.234 0.345 1.0
            if (header == vertex) {
                std::string x = *(++token);
                std::string y = *(++token);
                std::string z = *(++token);

                coords.push_back(std::stod(x));
                coords.push_back(std::stod(y));
                coords.push_back(std::stod(z));

                ++token;

                if (token != spaceTokenizer.end()){
                    modality |= COLOR_VERTICES;
                    std::string r = *(token);
                    std::string g = *(++token);
                    std::string b = *(++token);
                    ++token;
                    double alpha = 255;
                    if (token != spaceTokenizer.end()){
                        alpha = std::stoi(*token);
                    }
                    Color c(std::stod(r)*255, std::stod(g)*255, std::stod(b)*255, alpha);
                    verticesColors.push_back(c);
                }
            }
            // Handle
            //
            // f 1 2 3
            // f 3/1 4/2 5/3
            // f 6/4/1 3/5/3 7/6/5

            else if (header == face) {
                std::vector<std::string> dummy;
                token++;
                for (unsigned int i = 0; token != spaceTokenizer.end(); i++) {
                    dummy.push_back(*(token));
                    token++;
                }
                unsigned int nVert = (unsigned int)dummy.size();
                faceSizes.push_back(nVert);

                if (first == true){
                    first = false;
                    if (nVert == 3)
                        meshType = TRIANGLE_MESH;
                    else if (nVert == 4)
                        meshType = QUAD_MESH;
                    else
                        meshType = POLYGON_MESH;
                }
                else {
                    if (meshType == TRIANGLE_MESH && nVert != 3)
                        meshType = POLYGON_MESH;
                    if (meshType == QUAD_MESH && nVert != 4)
                        meshType = POLYGON_MESH;
                }

                std::vector<cg3::Tokenizer> slashTokenizer;
                for (unsigned int i=0; i<dummy.size(); i++){
                    cg3::Tokenizer t(dummy[i], ' ');
                    slashTokenizer.push_back(t);
                }

                for (unsigned int i=0; i<dummy.size(); i++){
                    std::string ids = *(slashTokenizer[i].begin());
                    faces.push_back(std::stoi(ids)-1);
                }

                if (usemtu){
                    faceColors.push_back(actualColor);
                }
            }
            else if (header == "usemtl" && usemtu){
                std::string color = *(++token);
                assert(mapColors.find(color) != mapColors.end());
                actualColor = mapColors[color];
            }
        }
    }
    file.close();
    return true;
}

template <typename T, typename V, typename C>
bool loadSave::loadTriangleMeshFromObj(const std::string& filename, std::vector<T>& coords, std::vector<V>& triangles, int& modality, std::vector<C> &verticesNormals, std::vector<Color> &verticesColors, std::vector<Color> &triangleColors) {
    std::list<T> dummyc;
    std::list<V> dummyt;
    MeshType meshType;
    modality = 0;
    std::list<C> dummyvn;
    std::list<Color> dummycv;
    std::list<Color> dummyct;
    bool r = loadMeshFromObj(filename, dummyc, dummyt, meshType, modality, dummyvn, dummycv, dummyct);
    if (r == true && meshType != TRIANGLE_MESH){
        std::cerr << "Error: mesh contained on " << filename << " is not a triangle mesh\n";
        r = false;
    }
    if (r) {
        coords.clear();
        triangles.clear();
        coords = std::vector<T>{ std::make_move_iterator(std::begin(dummyc)),
                                      std::make_move_iterator(std::end(dummyc)) };
        triangles = std::vector<V>{ std::make_move_iterator(std::begin(dummyt)),
                                         std::make_move_iterator(std::end(dummyt)) };
        if (modality & NORMAL_VERTICES && dummyc.size() == dummyvn.size()){
            verticesNormals.clear();
            verticesNormals = std::vector<C>{ std::make_move_iterator(std::begin(dummyvn)),
                                          std::make_move_iterator(std::end(dummyvn)) };
        }
        else
            modality &= ~NORMAL_VERTICES;
        if (modality & COLOR_VERTICES && dummyc.size() == dummycv.size()*3){
            verticesColors.clear();
            verticesColors = std::vector<Color>{ std::make_move_iterator(std::begin(dummycv)),
                                                      std::make_move_iterator(std::end(dummycv)) };
        }
        else
            modality &= ~COLOR_VERTICES;
        if (modality & COLOR_FACES && dummyt.size() == dummyct.size()*3){
            triangleColors.clear();
            triangleColors = std::vector<Color>{ std::make_move_iterator(std::begin(dummyct)),
                                                      std::make_move_iterator(std::end(dummyct)) };
        }
        else
            modality &= ~COLOR_FACES;
    }
    return r;
}

#ifdef CG3_WITH_EIGEN
template <typename T, typename V>
bool loadSave::loadTriangleMeshFromObj(const std::string &filename, Eigen::PlainObjectBase<T>& coords, Eigen::PlainObjectBase<V>&triangles) {
    std::list<typename Eigen::PlainObjectBase<T>::Scalar> dummyc;
    std::list<typename Eigen::PlainObjectBase<V>::Scalar> dummyt;
    MeshType meshType;
    std::list<unsigned int> faceSizes;
    bool r = loadMeshFromObj(filename, dummyc, dummyt, meshType, dummies::dummyInt, dummies::dummyListDouble, dummies::dummyListColor, dummies::dummyListColor, faceSizes);
    if (r == true && meshType != TRIANGLE_MESH){
        std::cerr << "Warning: mesh contained on " << filename << " is not a triangle mesh\n";
    }
    if (r) {
        coords.resize(dummyc.size()/3, 3);
        triangles.resize(faceSizes.size(), 3);
        int v = 0;
        for (typename std::list<typename Eigen::PlainObjectBase<T>::Scalar>::iterator it = dummyc.begin(); it != dummyc.end();){
            coords(v,0) = *it++;
            coords(v,1) = *it++;
            coords(v,2) = *it++;
            v++;
        }
        int t = 0;
        std::list<unsigned int>::iterator fsit = faceSizes.begin();
        for (typename std::list<typename Eigen::PlainObjectBase<V>::Scalar>::iterator it = dummyt.begin(); it != dummyt.end(); ){
            for (unsigned int id = 0; id < *fsit; id++){
                if (id < 3)
                    triangles(t,id) = *it++;
                else it++;
            }
            t++;
            fsit++;
        }
    }
    return r;
}

template <typename T, typename V, typename C, typename W, typename X>
bool loadSave::loadTriangleMeshFromObj(const std::string &filename, Eigen::PlainObjectBase<T>& coords, Eigen::PlainObjectBase<V>&triangles, int &modality, Eigen::PlainObjectBase<C> &verticesNormals, Eigen::PlainObjectBase<W> &verticesColors, Eigen::PlainObjectBase<X> &triangleColors){
    std::list<typename Eigen::PlainObjectBase<T>::Scalar> dummyc;
    std::list<typename Eigen::PlainObjectBase<V>::Scalar> dummyt;
    modality = 0;
    MeshType meshType;
    std::list<typename Eigen::PlainObjectBase<C>::Scalar> dummyvn;
    std::list<Color> dummycv;
    std::list<Color> dummyct;
    std::list<unsigned int> faceSizes;
    bool r = loadMeshFromObj(filename, dummyc, dummyt, meshType, modality, dummyvn, dummycv, dummyct, faceSizes);
    if (r == true && meshType != TRIANGLE_MESH){
        std::cerr << "Warning: mesh contained on " << filename << " is not a triangle mesh\n";
    }
    if (r) {
        coords.resize(dummyc.size()/3, 3);
        triangles.resize(faceSizes.size(), 3);
        int v = 0;
        for (typename std::list<typename Eigen::PlainObjectBase<T>::Scalar>::iterator it = dummyc.begin(); it != dummyc.end(); ){
            coords(v,0) = *it++;
            coords(v,1) = *it++;
            coords(v,2) = *it++;
            v++;
        }
        int t = 0;
        std::list<unsigned int>::iterator fsit = faceSizes.begin();
        for (typename std::list<typename Eigen::PlainObjectBase<V>::Scalar>::iterator it = dummyt.begin(); it != dummyt.end(); ){
            for (unsigned int id = 0; id < *fsit; id++){
                if (id < 3)
                    triangles(t,id) = *it++;
                else it++;
            }
            t++;
            fsit++;
        }
        if (modality & NORMAL_VERTICES
                && dummyc.size() == dummyvn.size()) {
            verticesNormals.resize(dummyc.size()/3, 3);
            int vn = 0;
            for (typename std::list<typename Eigen::PlainObjectBase<C>::Scalar>::iterator it = dummyvn.begin(); it != dummyvn.end(); ){
                verticesNormals(vn, 0) = *it++;
                verticesNormals(vn, 1) = *it++;
                verticesNormals(vn, 2) = *it++;
                vn++;
            }
        }
        else
            modality &= ~NORMAL_VERTICES;
        if (modality & COLOR_VERTICES && dummyc.size() == dummycv.size()*3){
            verticesColors.resize(dummyc.size()/3, 3);
            int vc = 0;
            for (typename std::list<Color>::iterator it = dummycv.begin(); it != dummycv.end(); ++it){
                Color c = *it;
                if (typeid(W) == typeid(float) || typeid(W) == typeid(double)){
                    verticesColors(vc, 0) = c.redF();
                    verticesColors(vc, 1) = c.greenF();
                    verticesColors(vc, 2) = c.blueF();
                }
                else {
                    verticesColors(vc, 0) = c.red();
                    verticesColors(vc, 1) = c.green();
                    verticesColors(vc, 2) = c.blue();
                }
                vc++;
            }
        }
        else
            modality &= ~COLOR_VERTICES;
        if (modality & COLOR_FACES && faceSizes.size() == dummyct.size()){
            triangleColors.resize(faceSizes.size(), 3);
            int vc = 0;
            for (typename std::list<Color>::iterator it = dummyct.begin(); it != dummyct.end(); ++it){
                Color c = *it;
                if (typeid(X) == typeid(float) || typeid(X) == typeid(double)){
                    triangleColors(vc, 0) = c.redF();
                    triangleColors(vc, 1) = c.greenF();
                    triangleColors(vc, 2) = c.blueF();
                }
                else {
                    triangleColors(vc, 0) = c.red();
                    triangleColors(vc, 1) = c.green();
                    triangleColors(vc, 2) = c.blue();
                }
                vc++;
            }
        }
        else
            modality &= ~COLOR_FACES;

    }
    return r;
}
#endif

template <typename T, typename V, typename C, typename W>
bool loadSave::loadMeshFromPly(const std::string& filename, std::list<T>& coords, std::list<V>& faces, loadSave::MeshType& meshType, int& modality, std::list<C>& verticesNormals, std::list<Color>& verticesColors, std::list<Color>& faceColors, std::list<W>& faceSizes) {
    typedef enum {VERTEX, FACE, OTHER} ElementType;
    typedef enum {unknown = -1, x, y, z, nx, ny, nz, red, green, blue, alpha, list} PropertyName;
    typedef enum {UCHAR, FLOAT} PropertyType;
    typedef struct {
        PropertyName name;
        PropertyType type;
    } Property;

    std::ifstream file(filename.c_str());
    std::string   line;

    int nVer = -1, nFac = -1;
    int nv=0, nf=0;
    std::list<Property> vertexProperties;
    std::list<Property> faceProperties;

    bool first = true;


    if(!file.is_open()) {
        std::cerr << "ERROR : read() : could not open input file " << filename.c_str() << "\n";
        return false;
    }

    //reading header
    std::string headerLine;
    bool error;
    ElementType elementType = OTHER;
    do {
        error = !(std::getline(file,line));
        if (!error){
            cg3::Tokenizer spaceTokenizer(line, ' ');
            if (spaceTokenizer.begin() == spaceTokenizer.end()) continue;
            cg3::Tokenizer::iterator token = spaceTokenizer.begin();
            headerLine = *token;
            if (headerLine == "element") { //new type of element read
                std::string s = *(++token);
                if (s == "vertex"){
                    elementType = VERTEX;
                    nVer = std::stoi(*(++token));
                }
                else if (s == "face"){
                    elementType = FACE;
                    nFac = std::stoi(*(++token));
                }
                else elementType = OTHER;
            }
            else if (headerLine == "property"){
                Property p;
                std::string type = *(++token);
                std::string name = *(++token);
                p.name = unknown;
                if (name == "x") p.name = x;
                if (name == "y") p.name = y;
                if (name == "z") p.name = z;
                if (name == "nx") p.name = nx;
                if (name == "ny") p.name = ny;
                if (name == "nz") p.name = nz;
                if (name == "red") p.name = red;
                if (name == "green") p.name = green;
                if (name == "blue") p.name = blue;
                if (name == "alpha") p.name = alpha;
                if (type == "list") p.name = list;
                if (p.name != unknown){
                    if (type == "float" || type == "double") p.type = FLOAT;
                    else p.type = UCHAR;
                    if (elementType == VERTEX)
                        vertexProperties.push_back(p);
                    else if (elementType == FACE)
                        faceProperties.push_back(p);
                }
            }
        }

    } while (!error && headerLine != "end_header");
    modality = 0;
    std::array<bool, 11> vb{{false}};
    for (Property p : vertexProperties){
        if (p.name >= 0)
            vb[p.name] = true;
    }
    if (!vb[0] || !vb[1] || !vb[2])
        error = true;
    if (vb[3] && vb[4] && vb [5])
        modality |= NORMAL_VERTICES;
    if (vb[6] && vb[7] && vb[8])
        modality |= COLOR_VERTICES;
    std::array<bool, 11> fb{{false}};
    for (Property p : faceProperties){
        if (p.name >= 0)
            fb[p.name] = true;
    }
    if (!fb[10])
        error = true;
    if (fb[6] && fb[7] && fb[8])
        modality |= COLOR_FACES;

    if (error){ //error while reading header
        std::cerr << "Error while parsing ply file\n";
        return false;
    }


    while(std::getline(file,line)) {
        cg3::Tokenizer spaceTokenizer(line, ' ');

        if (spaceTokenizer.begin() == spaceTokenizer.end()) continue;

        if (nv < nVer){ //reading vertices
            cg3::Tokenizer::iterator token = spaceTokenizer.begin();
            std::array<double, 6> cnv;
            Color c;

            //manage properties of vertex
            for (Property p : vertexProperties){
                if (token == spaceTokenizer.end())
                    return false;
                if (p.name >= 0 && p.name < 6){
                    cnv[p.name] = std::stod(*token);
                }
                else if (p.name >= 6 && p.name < 10){
                    switch (p.name) {
                        case red:
                            if (p.type == UCHAR)
                                c.setRed(std::stoi(*token));
                            else
                                c.setRedF(std::stof(*token));
                            break;
                        case green:
                            if (p.type == UCHAR)
                                c.setGreen(std::stoi(*token));
                            else
                                c.setGreenF(std::stof(*token));
                            break;
                        case blue:
                            if (p.type == UCHAR)
                                c.setBlue(std::stoi(*token));
                            else
                                c.setBlueF(std::stof(*token));
                            break;
                        case alpha:
                            if (p.type == UCHAR)
                                c.setAlpha(std::stoi(*token));
                            else
                                c.setAlphaF(std::stof(*token));
                            break;
                        default:
                            ;
                    }
                }

                //move to next property
                token++;
            }

            //save properties to lists
            coords.push_back(cnv[0]);
            coords.push_back(cnv[1]);
            coords.push_back(cnv[2]);
            if (modality & NORMAL_VERTICES){
                verticesNormals.push_back(cnv[3]);
                verticesNormals.push_back(cnv[4]);
                verticesNormals.push_back(cnv[5]);
            }
            if (modality & COLOR_VERTICES){
                verticesColors.push_back(c);
            }

            //move to next face
            nv++;
        }
        else if (nf < nFac){ //reading faces
            cg3::Tokenizer::iterator token = spaceTokenizer.begin();
            std::vector<int> indices;
            Color c;

            //manage properties of face
            for (Property p : faceProperties){
                if (token == spaceTokenizer.end())
                    return false;
                if (p.name == list){
                    int size = std::stoi(*(token));
                    indices.resize(size);
                    for (int i = 0; i < size; i++){
                        token++;
                        if (token == spaceTokenizer.end())
                            return false;
                        indices[i] = std::stoi(*token);
                    }
                }
                else {
                    switch (p.name) {
                        case red:
                            if (p.type == UCHAR)
                                c.setRed(std::stoi(*token));
                            else
                                c.setRedF(std::stof(*token));
                            break;
                        case green:
                            if (p.type == UCHAR)
                                c.setGreen(std::stoi(*token));
                            else
                                c.setGreenF(std::stof(*token));
                            break;
                        case blue:
                            if (p.type == UCHAR)
                                c.setBlue(std::stoi(*token));
                            else
                                c.setBlueF(std::stof(*token));
                            break;
                        case alpha:
                            if (p.type == UCHAR)
                                c.setAlpha(std::stoi(*token));
                            else
                                c.setAlphaF(std::stof(*token));
                            break;
                        default:
                            ;
                    }
                }

                //move to next property
                token++;
            }

            //managing meshtype
            if (first == true){
                first = false;
                if (indices.size() == 3)
                    meshType = TRIANGLE_MESH;
                else if (indices.size() == 4)
                    meshType = QUAD_MESH;
                else
                    meshType = POLYGON_MESH;
            }
            else {
                if (meshType == TRIANGLE_MESH && indices.size() != 3)
                    meshType = POLYGON_MESH;
                if (meshType == QUAD_MESH && indices.size() != 4)
                    meshType = POLYGON_MESH;
            }
            //save properties to lists
            faceSizes.push_back((unsigned int)indices.size());
            for (unsigned int i = 0; i < indices.size(); i++)
                faces.push_back(indices[i]);
            if (modality & COLOR_FACES)
                faceColors.push_back(c);

            //move to next face
            nf++;

        }
    }
    file.close();
    return true;
}

#ifdef CG3_WITH_EIGEN
template <typename T, typename V>
bool loadSave::loadTriangleMeshFromPly(const std::string &filename, Eigen::PlainObjectBase<T>& coords, Eigen::PlainObjectBase<V>&triangles) {
    std::list<typename Eigen::PlainObjectBase<T>::Scalar> dummyc;
    std::list<typename Eigen::PlainObjectBase<V>::Scalar> dummyt;
    MeshType meshType;
    std::list<unsigned int> faceSizes;
    bool r = loadMeshFromPly(filename, dummyc, dummyt, meshType, dummies::dummyInt, dummies::dummyListDouble, dummies::dummyListColor, dummies::dummyListColor, faceSizes);
    if (r == true && meshType != TRIANGLE_MESH){
        std::cerr << "Warning: mesh contained on " << filename << " is not a triangle mesh\n";
    }
    if (r) {
        coords.resize(dummyc.size()/3, 3);
        triangles.resize(faceSizes.size(), 3);
        int v = 0;
        for (typename std::list<typename Eigen::PlainObjectBase<T>::Scalar>::iterator it = dummyc.begin(); it != dummyc.end();){
            coords(v,0) = *it++;
            coords(v,1) = *it++;
            coords(v,2) = *it++;
            v++;
        }
        int t = 0;
        std::list<unsigned int>::iterator fsit = faceSizes.begin();
        for (typename std::list<typename Eigen::PlainObjectBase<V>::Scalar>::iterator it = dummyt.begin(); it != dummyt.end(); ){
            for (unsigned int id = 0; id < *fsit; id++){
                if (id < 3)
                    triangles(t,id) = *it++;
                else it++;
            }
            t++;
            fsit++;
        }
    }
    return r;
}

template <typename T, typename V, typename C, typename W, typename X>
bool loadSave::loadTriangleMeshFromPly(const std::string &filename, Eigen::PlainObjectBase<T>& coords, Eigen::PlainObjectBase<V>&triangles, int &modality, Eigen::PlainObjectBase<C> &verticesNormals, Eigen::PlainObjectBase<W> &verticesColors, Eigen::PlainObjectBase<X> &triangleColors){
    std::list<typename Eigen::PlainObjectBase<T>::Scalar> dummyc;
    std::list<typename Eigen::PlainObjectBase<V>::Scalar> dummyt;
    modality = 0;
    MeshType meshType;
    std::list<typename Eigen::PlainObjectBase<C>::Scalar> dummyvn;
    std::list<Color> dummycv;
    std::list<Color> dummyct;
    std::list<unsigned int> faceSizes;
    bool r = loadMeshFromPly(filename, dummyc, dummyt, meshType, modality, dummyvn, dummycv, dummyct, faceSizes);
    if (r == true && meshType != TRIANGLE_MESH){
        std::cerr << "Warning: mesh contained on " << filename << " is not a triangle mesh\n";
    }
    if (r) {
        coords.resize(dummyc.size()/3, 3);
        triangles.resize(faceSizes.size(), 3);
        int v = 0;
        for (typename std::list<typename Eigen::PlainObjectBase<T>::Scalar>::iterator it = dummyc.begin(); it != dummyc.end(); ){
            coords(v,0) = *it++;
            coords(v,1) = *it++;
            coords(v,2) = *it++;
            v++;
        }
        int t = 0;
        std::list<unsigned int>::iterator fsit = faceSizes.begin();
        for (typename std::list<typename Eigen::PlainObjectBase<V>::Scalar>::iterator it = dummyt.begin(); it != dummyt.end(); ){
            for (unsigned int id = 0; id < *fsit; id++){
                if (id < 3)
                    triangles(t,id) = *it++;
                else it++;
            }
            t++;
            fsit++;
        }
        if (modality & NORMAL_VERTICES
                && dummyc.size() == dummyvn.size()) {
            verticesNormals.resize(dummyc.size()/3, 3);
            int vn = 0;
            for (typename std::list<typename Eigen::PlainObjectBase<C>::Scalar>::iterator it = dummyvn.begin(); it != dummyvn.end(); ){
                verticesNormals(vn, 0) = *it++;
                verticesNormals(vn, 1) = *it++;
                verticesNormals(vn, 2) = *it++;
                vn++;
            }
        }
        else
            modality &= ~NORMAL_VERTICES;
        if (modality & COLOR_VERTICES && dummyc.size() == dummycv.size()*3){
            verticesColors.resize(dummyc.size()/3, 3);
            int vc = 0;
            for (typename std::list<Color>::iterator it = dummycv.begin(); it != dummycv.end(); ++it){
                Color c = *it;
                if (typeid(W) == typeid(float) || typeid(W) == typeid(double)){
                    verticesColors(vc, 0) = c.redF();
                    verticesColors(vc, 1) = c.greenF();
                    verticesColors(vc, 2) = c.blueF();
                }
                else {
                    verticesColors(vc, 0) = c.red();
                    verticesColors(vc, 1) = c.green();
                    verticesColors(vc, 2) = c.blue();
                }
                vc++;
            }
        }
        else
            modality &= ~COLOR_VERTICES;
        if (modality & COLOR_FACES && faceSizes.size() == dummyct.size()){
            triangleColors.resize(faceSizes.size(), 3);
            int vc = 0;
            for (typename std::list<Color>::iterator it = dummyct.begin(); it != dummyct.end(); ++it){
                Color c = *it;
                if (typeid(X) == typeid(float) || typeid(X) == typeid(double)){
                    triangleColors(vc, 0) = c.redF();
                    triangleColors(vc, 1) = c.greenF();
                    triangleColors(vc, 2) = c.blueF();
                }
                else {
                    triangleColors(vc, 0) = c.red();
                    triangleColors(vc, 1) = c.green();
                    triangleColors(vc, 2) = c.blue();
                }
                vc++;
            }
        }
        else
            modality &= ~COLOR_FACES;

    }
    return r;
}
#endif

}
