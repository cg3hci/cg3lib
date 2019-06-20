/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "load_save_obj.h"
#include "../utilities/tokenizer.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <clocale>

namespace cg3 {
namespace internal {

inline void manageObjFileColor(
		std::ofstream &fp,
		std::ofstream &fmtu,
		const Color &c,
		io::FileColorMode colorMod,
		Color &actualColor,
		std::map<Color,
		std::string> &colors)
{
	std::string stringColor = "COLOR";
	if (c != actualColor) {
		std::map<Color, std::string>::iterator it = colors.find(c);
		if (it == colors.end()) {
			std::stringstream stm;
			stm << stringColor << colors.size();
			std::string mtlColor = stm.str();
			fmtu << "newmtl " << mtlColor << "\n";
			if (colorMod == io::RGB){
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

inline void manageObjFileNames(
		const std::string &objfilename,
		std::string &mtufilename,
		std::string &mtufilenopath)
{
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

inline bool loadMtlFile(
		const std::string &mtuFile,
		std::map<std::string, Color> &mapColors)
{
	std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator
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

} //namespace cg3::internal

/**
 * @ingroup cg3core
 * @brief loadMeshFromObj
 * @param filename
 * @param coords
 * @param faces
 * @param meshType
 * @param modality
 * @param verticesNormals
 * @param verticesColors
 * @param faceColors
 * @param faceSizes
 * @return
 */
template <typename T, typename V, typename C, typename W>
bool loadMeshFromObj(
		const std::string& filename,
		std::list<T>& coords,
		std::list<V>& faces,
		io::FileMeshMode& modality,
		std::list<C> &verticesNormals,
		std::list<Color> &verticesColors,
		std::list<Color> &faceColors,
		std::list<W> &faceSizes)
{
	std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator

	static const std::string vertex = "v";
	static const std::string vertexNormal = "vn";
	static const std::string face   = "f";

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
	modality.reset();

	if(!file.is_open()) {
		return false;
	}
	while(std::getline(file,line)) {

		cg3::Tokenizer spaceTokenizer(line, ' ');

		if (spaceTokenizer.begin() != spaceTokenizer.end()) {

			cg3::Tokenizer::iterator token = spaceTokenizer.begin();
			std::string header = *token;

			if (header == "mtllib"){
				modality.setFaceColors();
				usemtu = true;
				std::string mtufilename = *(++token);
				size_t lastSlash = filename.find_last_of("/");
				if (lastSlash < filename.size()){
					std::string path = filename.substr(0, lastSlash);
					mtufilename = path + "/" + mtufilename;
				}
				if (! internal::loadMtlFile(mtufilename, mapColors))
					usemtu = false;
			}

			if (header == vertexNormal) {
				modality.setVertexNormals();
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
					modality.setVertexColors();
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
						modality.setTriangleMesh();
					else if (nVert == 4)
						modality.setQuadMesh();
					else
						modality.setPolygonMesh();
				}
				else {
					if (modality.isTriangleMesh() && nVert != 3)
						modality.setPolygonMesh();
					if (modality.isQuadMesh() && nVert != 4)
						modality.setPolygonMesh();
				}

				std::vector<cg3::Tokenizer> slashTokenizer;
				for (unsigned int i=0; i<dummy.size(); i++){
					cg3::Tokenizer t(dummy[i], '/');
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
				if (mapColors.find(color) == mapColors.end()) {
					actualColor = cg3::Color(128,128,128);
				}
				else
					actualColor = mapColors[color];
			}
		}
	}
	file.close();
	return true;
}

/**
 * @ingroup cg3core
 * @brief loadTriangleMeshFromObj
 * @param filename
 * @param coords
 * @param triangles
 * @param modality
 * @param verticesNormals
 * @param verticesColors
 * @param triangleColors
 * @return
 */
template <typename T, typename V, typename C>
bool loadTriangleMeshFromObj(
		const std::string& filename,
		std::vector<T>& coords,
		std::vector<V>& triangles,
		io::FileMeshMode& modality,
		std::vector<C> &verticesNormals,
		std::vector<Color> &verticesColors,
		std::vector<Color> &triangleColors)
{
	std::list<T> dummyc;
	std::list<V> dummyt;
	modality.reset();
	std::list<C> dummyvn;
	std::list<Color> dummycv;
	std::list<Color> dummyct;
	bool r = loadMeshFromObj(filename, dummyc, dummyt, modality, dummyvn, dummycv, dummyct);
	if (r == true && dummyt.size() > 0 && !modality.isTriangleMesh()){
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
		if (modality.hasVertexNormals() && dummyc.size() == dummyvn.size()){
			verticesNormals.clear();
			verticesNormals = std::vector<C>{ std::make_move_iterator(std::begin(dummyvn)),
										  std::make_move_iterator(std::end(dummyvn)) };
		}
		if (modality.hasVertexColors() && dummyc.size() == dummycv.size()*3){
			verticesColors.clear();
			verticesColors = std::vector<Color>{ std::make_move_iterator(std::begin(dummycv)),
													  std::make_move_iterator(std::end(dummycv)) };
		}
		if (modality.hasFaceColors() && dummyt.size() == dummyct.size()*3){
			triangleColors.clear();
			triangleColors = std::vector<Color>{ std::make_move_iterator(std::begin(dummyct)),
													  std::make_move_iterator(std::end(dummyct)) };
		}
	}
	return r;
}

#ifdef CG3_WITH_EIGEN
/**
 * @ingroup cg3core
 * @brief loadTriangleMeshFromObj
 * @param filename
 * @param coords
 * @param triangles
 * @return
 */
template <typename T, typename V>
bool loadTriangleMeshFromObj(
		const std::string &filename,
		Eigen::PlainObjectBase<T>& coords,
		Eigen::PlainObjectBase<V>& triangles)
{
	std::list<typename Eigen::PlainObjectBase<T>::Scalar> dummyc;
	std::list<typename Eigen::PlainObjectBase<V>::Scalar> dummyt;
	io::FileMeshMode modality;
	std::list<unsigned int> faceSizes;
	bool r = loadMeshFromObj(filename, dummyc, dummyt, modality,
							 internal::dummyListDouble,
							 internal::dummyListColor, internal::dummyListColor, faceSizes);
    if (r == true && dummyt.size() > 0 && !modality.isTriangleMesh()){
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
		for (typename std::list<typename Eigen::PlainObjectBase<V>::Scalar>::iterator it = dummyt.begin(); it != dummyt.end();){
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

/**
 * @ingroup cg3core
 * @brief loadTriangleMeshFromObj
 * @param filename
 * @param coords
 * @param triangles
 * @param modality
 * @param verticesNormals
 * @param verticesColors
 * @param triangleColors
 * @return
 */
template <typename T, typename V, typename C, typename W, typename X>
bool loadTriangleMeshFromObj(
		const std::string &filename,
		Eigen::PlainObjectBase<T>& coords,
		Eigen::PlainObjectBase<V>&triangles,
		io::FileMeshMode &modality,
		Eigen::PlainObjectBase<C> &verticesNormals,
		Eigen::PlainObjectBase<W> &verticesColors,
		Eigen::PlainObjectBase<X> &triangleColors)
{
	std::list<typename Eigen::PlainObjectBase<T>::Scalar> dummyc;
	std::list<typename Eigen::PlainObjectBase<V>::Scalar> dummyt;
	modality.reset();
	std::list<typename Eigen::PlainObjectBase<C>::Scalar> dummyvn;
	std::list<Color> dummycv;
	std::list<Color> dummyct;
	std::list<unsigned int> faceSizes;
	bool r = loadMeshFromObj(filename, dummyc, dummyt, modality, dummyvn, dummycv, dummyct, faceSizes);
    if (r == true && dummyt.size() > 0 && !modality.isTriangleMesh()){
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
		if (modality.hasVertexNormals()
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
		if (modality.hasVertexColors() && dummyc.size() == dummycv.size()*3){
			verticesColors.resize(dummyc.size()/3, 3);
			int vc = 0;
			for (typename std::list<Color>::iterator it = dummycv.begin(); it != dummycv.end(); ++it) {
				Color c = *it;
				if (typeid(typename Eigen::PlainObjectBase<W>::Scalar) == typeid(float) ||
						typeid(typename Eigen::PlainObjectBase<W>::Scalar) == typeid(double)) {
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
		if (modality.hasFaceColors() && faceSizes.size() == dummyct.size()){
			triangleColors.resize(faceSizes.size(), 3);
			int vc = 0;
			for (typename std::list<Color>::iterator it = dummyct.begin(); it != dummyct.end(); ++it) {
				Color c = *it;
				if (typeid(typename Eigen::PlainObjectBase<X>::Scalar) == typeid(float) ||
						typeid(typename Eigen::PlainObjectBase<X>::Scalar) == typeid(double)) {
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
	}
	return r;
}
#endif

/**
 * @ingroup cg3core
 * @brief saveMeshOnObj
 * @param filename The name of the file
 * @param nVertices number of vertices contained in the array vertices
 * @param nFaces number of faces contained in the array faces
 * @param vertices A vector of nVertices*3 elements, that are the
 * coordinates x, y, z of every vertex
 * @param faces A vector of N (nFaces*3 if it is a triangle mesh,
 * n*4 if quad mesh, etc.. depends on the modality parameter) elements
 * that are the vertex indices of every face
 * @param modality indicates the modality of the mesh
 * (see cg3::io::FileMeshMode class). Default is a triangle mesh with
 * just vertex coordinates and face indices
 * @param verticesNormals A vector of nVertices*3 elements, that are
 * the normal coordinates x, y, z of every vertex. Can be omitted.
 * @param colorMod Mode of storing colors in the obj file: RGB or RGBA.
 * Can be omitted.
 * @param verticesColors: array of nV*3 or nV*4 (depending on colorMod)
 * indicating the colors of the vertices
 * @param faceColors
 * @param polygonSizes
 * @return
 */
template <typename A, typename B, typename C , typename T , typename V , typename W>
bool saveMeshOnObj(
		const std::string& filename,
		size_t nVertices,
		size_t nFaces,
		const A vertices[],
		const B faces[],
		io::FileMeshMode modality,
		const C verticesNormals[],
		io::FileColorMode colorMod,
		const T verticesColors[],
		const V faceColors[],
		const W polygonSizes[])
{
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
	if (modality.hasFaceColors() || modality.hasVertexColors()){
		color = true;
		internal::manageObjFileNames(objfilename, mtufilename, mtufilenopath);
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

		if (modality.hasVertexNormals()) {
			fp << "vn " << verticesNormals[i] <<
				  " " << verticesNormals[i+1] <<
				  " " << verticesNormals[i+2] << std::endl;
		}
		fp << "v " << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2];
		if (modality.hasVertexColors()){
			Color c = internal::colorFromArray(colorMod == io::RGB ? i : (i/3)*4, verticesColors, colorMod);
			fp << " " << c.redF() << " " << c.blueF() << " " << c.greenF();
		}
		fp << std::endl;
	}

	if (modality.isTriangleMesh()) {
		for(size_t i=0; i<nFaces*3; i+=3) {
			if (modality.hasFaceColors()){
				Color c = internal::colorFromArray(colorMod == io::RGB ? i : (i/3)*4, faceColors, colorMod);
				internal::manageObjFileColor(fp, fmtu, c, colorMod, actualColor, colors);
			}
			fp << "f " << faces[i]+1 << " " << faces[i+1]+1 << " " << faces[i+2]+1 << std::endl;
		}
	}
	else if (modality.isQuadMesh()) {
		for(size_t i=0; i<nFaces*4; i+=4) {
			if (modality.hasFaceColors()){
				Color c = internal::colorFromArray(colorMod == io::RGB ? (i/4)*3 : i, faceColors, colorMod);
				internal::manageObjFileColor(fp, fmtu, c, colorMod, actualColor, colors);
			}
			fp << "f " << faces[i]+1 <<
				  " " << faces[i+1]+1 <<
				  " " << faces[i+2]+1<<
				  " " << faces[i+3]+1 << std::endl;
		}
	}
	else if (modality.isPolygonMesh()) {
		size_t j = 0;
		for (size_t i = 0; i < nFaces; i++){
			if (modality.hasFaceColors()){
				Color c = internal::colorFromArray(colorMod == io::RGB ? i*3 : i*4, faceColors, colorMod);
				internal::manageObjFileColor(fp, fmtu, c, colorMod, actualColor, colors);
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

} //namespace cg3
