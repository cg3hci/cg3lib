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

#include "ply/ply_vertex.h"
#include "ply/ply_face.h"

namespace cg3 {

template <typename T, typename V, typename C, typename W>
bool loadMeshFromPly(
		const std::string& filename,
		std::vector<T>& coords,
		std::vector<V>& faces,
		io::FileMeshMode& modality,
		std::vector<C>& verticesNormals,
		std::vector<Color>& verticesColors,
		std::vector<Color>& facesColors,
		std::vector<W>& faceSizes)
{
	std::ifstream file(filename.c_str());
	if(!file.is_open()) {
		std::cerr << "ERROR : read() : could not open input file " << filename.c_str() << "\n";
		return false;
	}
	cg3::ply::PlyHeader header(file);
	if (header.errorWhileLoading())
		return false;

	modality = header.modality();
	io::FileMeshType meshType;

	uint nV = header.numberVertices();
	uint nF = header.numberFaces();
	std::vector<uint> vc, fc; //v and f colors
	std::vector<double> fn; //f normals
	coords.resize(nV*3);
	faces.clear();
	verticesNormals.resize(nV*3);
	vc.resize(nV*4); //also alpha
	fc.resize(nF*4); //also alpha
	fn.resize(nF*3);
	faceSizes.resize(nF);

	bool loadOk = true;
	for (ply::Element el : header){
		switch (el.type) {
			case ply::VERTEX:
				loadOk = ply::loadVertices(file, header, coords.data(), verticesNormals.data(), io::RGBA, vc.data());
				break;
			case ply::FACE:
				loadOk = ply::loadFaces(file, header, faces, meshType, fn.data(), io::RGBA, fc.data(), faceSizes.data());
				modality.setMeshType(meshType);
				break;
			default:
				break;
		}
		if (!loadOk)
			return false;
	}
	verticesColors.clear();
	verticesColors.reserve(nV);
	for (uint i = 0; i < vc.size(); i+=4){
		verticesColors.push_back(Color(vc[i], vc[i+1], vc[i+2], vc[i+3]));
	}
	facesColors.clear();
	facesColors.reserve(nF);
	for (uint i = 0; i < fc.size(); i+=4){
		facesColors.push_back(Color(fc[i], fc[i+1], fc[i+2], fc[i+3]));
	}
	file.close();
	return loadOk;
}

template <template <class ... > class Con1, template <class ... > class Con2,
          template <class ... > class Con3, template <class ... > class Con4,
          template <class ... > class Con5, template <class ... > class Con6,
          class T, class V, class C, class W,
          class ... ArgsT, class ... ArgsV, class ... ArgsC, class ... ArgsColor, class ... ArgsW>
bool loadMeshFromPly(
		const std::string& filename,
        Con1<T, ArgsT...>& coords,
        Con2<V, ArgsV...>& faces,
		io::FileMeshMode& modality,
        Con3<C, ArgsC...>& verticesNormals,
        Con4<Color, ArgsColor...>& verticesColors,
        Con5<Color, ArgsColor...>& facesColors,
        Con6<W, ArgsW...>& faceSizes)
{
	std::vector<T> vcoords;
	std::vector<V> vfaces;
	std::vector<C> vverticesNormals;
	std::vector<Color> vverticesColors, vfacesColors;
	std::vector<W> vfaceSizes;
	bool b = loadMeshFromPly(filename, vcoords, vfaces, modality, vverticesNormals, vverticesColors, vfacesColors, vfaceSizes);
	if (b){
		coords = Con1<T>(vcoords.begin(), vcoords.end());
		faces = Con2<V>(vfaces.begin(), vfaces.end());
		verticesNormals = Con3<C>(vverticesNormals.begin(), vverticesNormals.end());
		verticesColors = Con4<Color>(vverticesColors.begin(), vverticesColors.end());
		facesColors = Con5<Color>(vfacesColors.begin(), vfacesColors.end());
		faceSizes = Con6<W>(vfaceSizes.begin(), vfaceSizes.end());
	}
	return b;
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
	std::vector<typename Eigen::PlainObjectBase<T>::Scalar> dummyc;
	std::vector<typename Eigen::PlainObjectBase<V>::Scalar> dummyt;
	io::FileMeshMode meshType;
	std::vector<unsigned int> faceSizes;
	bool r = loadMeshFromPly(filename, dummyc, dummyt, meshType,
							 internal::dummyVectorDouble,
							 internal::dummyVectorColor, internal::dummyVectorColor, faceSizes);
	if (r == true && meshType.isTriangleMesh()){
		std::cerr << "Warning: mesh contained on " << filename << " is not a triangle mesh\n";
	}
	if (r) {
		coords.resize(dummyc.size()/3, 3);
		triangles.resize(faceSizes.size(), 3);
		int v = 0;
		for (typename std::vector<typename Eigen::PlainObjectBase<T>::Scalar>::iterator it = dummyc.begin(); it != dummyc.end();){
			coords(v,0) = *it++;
			coords(v,1) = *it++;
			coords(v,2) = *it++;
			v++;
		}
		int t = 0;
		std::vector<unsigned int>::iterator fsit = faceSizes.begin();
		for (typename std::vector<typename Eigen::PlainObjectBase<V>::Scalar>::iterator it = dummyt.begin(); it != dummyt.end(); ){
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
		io::FileMeshMode &modality,
		Eigen::PlainObjectBase<C> &verticesNormals,
		Eigen::PlainObjectBase<W> &verticesColors,
		Eigen::PlainObjectBase<X> &triangleColors)
{
	std::vector<typename Eigen::PlainObjectBase<T>::Scalar> dummyc;
	std::vector<typename Eigen::PlainObjectBase<V>::Scalar> dummyt;
	modality.reset();
	std::vector<typename Eigen::PlainObjectBase<C>::Scalar> dummyvn;
	std::vector<Color> dummycv;
	std::vector<Color> dummyct;
	std::vector<unsigned int> faceSizes;
	bool r = loadMeshFromPly(filename, dummyc, dummyt, modality, dummyvn, dummycv, dummyct, faceSizes);
	if (r == true && !modality.isTriangleMesh()){
		std::cerr << "Warning: mesh contained on " << filename << " is not a triangle mesh\n";
	}
	if (r) {
		coords.resize(dummyc.size()/3, 3);
		triangles.resize(faceSizes.size(), 3);
		int v = 0;
		for (typename std::vector<typename Eigen::PlainObjectBase<T>::Scalar>::iterator it = dummyc.begin(); it != dummyc.end();) {
			coords(v,0) = *it++;
			coords(v,1) = *it++;
			coords(v,2) = *it++;
			v++;
		}
		int t = 0;
		std::vector<unsigned int>::iterator fsit = faceSizes.begin();
		for (typename std::vector<typename Eigen::PlainObjectBase<V>::Scalar>::iterator it = dummyt.begin(); it != dummyt.end();) {
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
			for (typename std::vector<typename Eigen::PlainObjectBase<C>::Scalar>::iterator it = dummyvn.begin(); it != dummyvn.end();) {
				verticesNormals(vn, 0) = *it++;
				verticesNormals(vn, 1) = *it++;
				verticesNormals(vn, 2) = *it++;
				vn++;
			}
		}
		if (modality.hasVertexColors() && dummyc.size() == dummycv.size()*3) {
			verticesColors.resize(dummyc.size()/3, 3);
			int vc = 0;
			for (typename std::vector<Color>::iterator it = dummycv.begin(); it != dummycv.end(); ++it){
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
			for (typename std::vector<Color>::iterator it = dummyct.begin(); it != dummyct.end(); ++it){
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
template <typename A, typename B, typename C,typename D, typename T, typename V, typename W>
inline bool saveMeshOnPly(
		const std::string& filename,
		size_t nVertices,
		size_t nFaces,
		const A vertices[],
		const B faces[],
		bool binary,
		io::FileMeshMode modality,
		const C verticesNormals[],
		const D facesNormals[],
		io::FileColorMode colorMod,
		const T verticesColors[],
		const V faceColors[],
		const W polygonSizes[]
		)
{
	std::string plyfilename;
	std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // makes sure "." is the decimal separator
	std::ofstream fp;
	size_t lastindex = filename.find_last_of(".");
	if (lastindex != filename.size())
		plyfilename = filename;
	else
		plyfilename = filename + ".ply";

	ply::PlyHeader header;
	header.setModality(modality, binary);
        header.setNumberVertices((unsigned long int)nVertices);
        header.setNumberFaces((unsigned long int)nFaces);
	fp.open (plyfilename);
	if(!fp) {
		return false;
	}
	fp << header.toString();
	ply::saveVertices(fp, header, vertices, verticesNormals, colorMod, verticesColors);
	ply::saveFaces(fp, header, faces, modality, facesNormals, colorMod, faceColors, polygonSizes);
	fp.close();
	return true;
}

#endif

} //namespace std
