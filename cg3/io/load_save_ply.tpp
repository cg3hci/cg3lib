/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "load_save_ply.h"
#include "../utilities/tokenizer.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <clocale>

namespace cg3 {

/**
 * @ingroup cg3core
 * @brief loadMeshFromPly
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
bool loadMeshFromPly(
		const std::string& filename,
		std::list<T>& coords,
		std::list<V>& faces,
		io::MeshType& meshType,
		int& modality,
		std::list<C>& verticesNormals,
		std::list<Color>& verticesColors,
		std::list<Color>& faceColors,
		std::list<W>& faceSizes)
{
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
					if (elementType == VERTEX) //reading vertex properties
						vertexProperties.push_back(p);
					else if (elementType == FACE) //reading face properties
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
		modality |= io::NORMAL_VERTICES;
	if (vb[6] && vb[7] && vb[8])
		modality |= io::COLOR_VERTICES;
	std::array<bool, 11> fb{{false}};
	for (Property p : faceProperties){
		if (p.name >= 0)
			fb[p.name] = true;
	}
	if (!fb[10])
		error = true;
	if (fb[6] && fb[7] && fb[8])
		modality |= io::COLOR_FACES;

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
			if (modality & io::NORMAL_VERTICES){
				verticesNormals.push_back(cnv[3]);
				verticesNormals.push_back(cnv[4]);
				verticesNormals.push_back(cnv[5]);
			}
			if (modality & io::COLOR_VERTICES){
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
					meshType = io::TRIANGLE_MESH;
				else if (indices.size() == 4)
					meshType = io::QUAD_MESH;
				else
					meshType = io::POLYGON_MESH;
			}
			else {
				if (meshType == io::TRIANGLE_MESH && indices.size() != 3)
					meshType = io::POLYGON_MESH;
				if (meshType == io::QUAD_MESH && indices.size() != 4)
					meshType = io::POLYGON_MESH;
			}
			//save properties to lists
			faceSizes.push_back((unsigned int)indices.size());
			for (unsigned int i = 0; i < indices.size(); i++)
				faces.push_back(indices[i]);
			if (modality & io::COLOR_FACES)
				faceColors.push_back(c);

			//move to next face
			nf++;

		}
	}
	file.close();
	return true;
}

#ifdef CG3_WITH_EIGEN
/**
 * @ingroup cg3core
 * @brief loadTriangleMeshFromPly
 * @param filename
 * @param coords
 * @param triangles
 * @return
 */
template <typename T, typename V>
bool loadTriangleMeshFromPly(
		const std::string &filename,
		Eigen::PlainObjectBase<T>& coords,
		Eigen::PlainObjectBase<V>&triangles)
{
	std::list<typename Eigen::PlainObjectBase<T>::Scalar> dummyc;
	std::list<typename Eigen::PlainObjectBase<V>::Scalar> dummyt;
	io::MeshType meshType;
	std::list<unsigned int> faceSizes;
	bool r = loadMeshFromPly(filename, dummyc, dummyt, meshType,
							 internal::dummyInt, internal::dummyListDouble,
							 internal::dummyListColor, internal::dummyListColor, faceSizes);
	if (r == true && meshType != io::TRIANGLE_MESH){
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

/**
 * @ingroup cg3core
 * @brief loadTriangleMeshFromPly
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
bool loadTriangleMeshFromPly(
		const std::string &filename,
		Eigen::PlainObjectBase<T>& coords,
		Eigen::PlainObjectBase<V>&triangles,
		int &modality,
		Eigen::PlainObjectBase<C> &verticesNormals,
		Eigen::PlainObjectBase<W> &verticesColors,
		Eigen::PlainObjectBase<X> &triangleColors)
{
	std::list<typename Eigen::PlainObjectBase<T>::Scalar> dummyc;
	std::list<typename Eigen::PlainObjectBase<V>::Scalar> dummyt;
	modality = 0;
	io::MeshType meshType;
	std::list<typename Eigen::PlainObjectBase<C>::Scalar> dummyvn;
	std::list<Color> dummycv;
	std::list<Color> dummyct;
	std::list<unsigned int> faceSizes;
	bool r = loadMeshFromPly(filename, dummyc, dummyt, meshType, modality, dummyvn, dummycv, dummyct, faceSizes);
	if (r == true && meshType != io::TRIANGLE_MESH){
		std::cerr << "Warning: mesh contained on " << filename << " is not a triangle mesh\n";
	}
	if (r) {
		coords.resize(dummyc.size()/3, 3);
		triangles.resize(faceSizes.size(), 3);
		int v = 0;
		for (typename std::list<typename Eigen::PlainObjectBase<T>::Scalar>::iterator it = dummyc.begin(); it != dummyc.end();) {
			coords(v,0) = *it++;
			coords(v,1) = *it++;
			coords(v,2) = *it++;
			v++;
		}
		int t = 0;
		std::list<unsigned int>::iterator fsit = faceSizes.begin();
		for (typename std::list<typename Eigen::PlainObjectBase<V>::Scalar>::iterator it = dummyt.begin(); it != dummyt.end();) {
			for (unsigned int id = 0; id < *fsit; id++){
				if (id < 3)
					triangles(t,id) = *it++;
				else it++;
			}
			t++;
			fsit++;
		}
		if (modality & io::NORMAL_VERTICES
				&& dummyc.size() == dummyvn.size()) {
			verticesNormals.resize(dummyc.size()/3, 3);
			int vn = 0;
			for (typename std::list<typename Eigen::PlainObjectBase<C>::Scalar>::iterator it = dummyvn.begin(); it != dummyvn.end();) {
				verticesNormals(vn, 0) = *it++;
				verticesNormals(vn, 1) = *it++;
				verticesNormals(vn, 2) = *it++;
				vn++;
			}
		}
		else
			modality &= ~io::NORMAL_VERTICES;
		if (modality & io::COLOR_VERTICES && dummyc.size() == dummycv.size()*3) {
			verticesColors.resize(dummyc.size()/3, 3);
			int vc = 0;
			for (typename std::list<Color>::iterator it = dummycv.begin(); it != dummycv.end(); ++it){
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
		else
			modality &= ~io::COLOR_VERTICES;
		if (modality & io::COLOR_FACES && faceSizes.size() == dummyct.size()){
			triangleColors.resize(faceSizes.size(), 3);
			int vc = 0;
			for (typename std::list<Color>::iterator it = dummyct.begin(); it != dummyct.end(); ++it){
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
		else
			modality &= ~io::COLOR_FACES;

	}
	return r;
}

/**
 * @ingroup cg3core
 * @brief saveMeshOnPly
 * @param filename
 * @param nVertices
 * @param nFaces
 * @param vertices
 * @param faces
 * @param meshType
 * @param modality
 * @param verticesNormals
 * @param colorMod
 * @param verticesColors
 * @param faceColors
 * @param polygonSizes
 * @return
 */
template <typename A, typename B, typename C, typename T, typename V, typename W >
inline bool saveMeshOnPly(
		const std::string& filename,
		size_t nVertices,
		size_t nFaces,
		const A vertices[],
		const B faces[],
		io::MeshType meshType,
		int modality,
		const C verticesNormals[],
		io::ColorMode colorMod,
		const T verticesColors[],
		const V faceColors[],
		const W polygonSizes[])
{
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
	if (modality & io::NORMAL_VERTICES){
		fp << "property float nx\nproperty float ny\nproperty float nz\n";
	}
	if (modality & io::COLOR_VERTICES){
		if (colorMod == io::RGB)
			fp << "property uchar red\nproperty uchar green\nproperty uchar blue\n";
		else
			fp << "property uchar red\nproperty uchar green\nproperty uchar blue\nproperty uchar alpha\n";
	}
	fp << "element face " << nFaces << "\n";
	fp << "property list uchar int vertex_indices\n";
	if (modality & io::COLOR_FACES){
		if (colorMod == io::RGB)
			fp << "property uchar red\nproperty uchar green\nproperty uchar blue\n";
		else
			fp << "property uchar red\nproperty uchar green\nproperty uchar blue\nproperty uchar alpha\n";
	}
	fp << "end_header\n";
	//

	for(size_t i=0; i<nVertices*3; i+=3) {
		fp << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2];
		if (modality & io::NORMAL_VERTICES) {
			fp << " " << verticesNormals[i] <<
				  " " << verticesNormals[i+1] <<
				  " " << verticesNormals[i+2];
		}
		if (modality & io::COLOR_VERTICES){
			Color c = internal::colorFromArray(colorMod == io::RGB ?
													  i : (i/3)*4, verticesColors, colorMod);
			fp << " " << c.red() << " " << c.green() << " " << c.blue();
			if (colorMod == io::RGBA)
				fp << " " << c.alpha();
		}
		fp << std::endl;
	}

	if (meshType == io::TRIANGLE_MESH) {
		for(size_t i=0; i<nFaces*3; i+=3) {
			fp << "3 " << faces[i] << " " << faces[i+1] << " " << faces[i+2];
			if (modality & io::COLOR_FACES){
				Color c = internal::colorFromArray(colorMod == io::RGB ?
														  i : (i/3)*4, faceColors, colorMod);;
				fp << " " << c.red() << " " << c.green() << " " << c.blue();
				if (colorMod == io::RGBA)
					fp << " " << c.alpha();
			}
			fp << std::endl;

		}
	}
	else if (meshType == io::QUAD_MESH) {
		for(size_t i=0; i<nFaces*4; i+=4) {
			fp << "4 " << faces[i] << " " << faces[i+1] << " " << faces[i+2]<< " " << faces[i+3];
			if (modality & io::COLOR_FACES){
				Color c = internal::colorFromArray(colorMod == io::RGB ?
														  (i/4)*3 : i, verticesColors, colorMod);;
				fp << " " << c.red() << " " << c.green() << " " << c.blue();
				if (colorMod == io::RGBA)
					fp << " " << c.alpha();
			}
			fp << std::endl;

		}
	}
	else if (meshType == io::POLYGON_MESH) {
		size_t j = 0;
		for (size_t i = 0; i < nFaces; i++){

			fp << polygonSizes[i] << " ";
			for (size_t k = 0; k < polygonSizes[i]; k++)
				fp << faces[j+k] << " ";
			j += polygonSizes[i];
			if (modality & io::COLOR_FACES){
				Color c = internal::colorFromArray(colorMod == io::RGB ?
														  i*3 : i*4, faceColors, colorMod);
				fp << c.red() << " " << c.green() << " " << c.blue();
				if (colorMod == io::RGBA)
					fp << " " << c.alpha();
			}
			fp << std::endl;
		}
	}
	else assert(0);

	fp.close();
	return true;
}

#endif

} //namespace std
