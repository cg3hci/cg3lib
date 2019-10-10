/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "ply_edge.h"

namespace cg3 {
namespace ply {

namespace internal {

template <typename A, typename B>
bool loadEdgesTxt(
		std::ifstream& file,
		const PlyHeader& header,
		A edges[], //container with push_back method
		io::FileColorMode colorMod ,
		B edgeColors[])
{
	bool error = false;
	uint colorStep = 3;
	if (colorMod == io::RGBA)
		colorStep = 4;
	cg3::Tokenizer spaceTokenizer;
	error = internal::nextLine(file, spaceTokenizer);
	cg3::Tokenizer::iterator token = spaceTokenizer.begin();
	for(uint e = 0; e < header.numberEdges(); ++e) {
		for (ply::Property p : header.faceProperties()) {
			if (token == spaceTokenizer.end()){
				error = nextLine(file, spaceTokenizer);
				token = spaceTokenizer.begin();
			}
			if (error) return false;
			switch (p.name) {
			case ply::red :
				edgeColors[e*colorStep] = internal::readProperty<B>(token, p.type, true); break;
			case ply::green :
				edgeColors[e*colorStep+1] = internal::readProperty<B>(token, p.type, true); break;
			case ply::blue :
				edgeColors[e*colorStep+2] = internal::readProperty<B>(token, p.type, true); break;
			case ply::alpha :
				if (colorStep == 4){ // alpha in file that will be saved
					edgeColors[e*colorStep+3] = internal::readProperty<B>(token, p.type, true);
				}
				else { // alpha in file that will not be saved
					++token;
				}
				break;
			case ply::vertex1 :
				edges[e*2] = internal::readProperty<A>(token, p.type, true); break;
			case ply::vertex2 :
				edges[e*2+1] = internal::readProperty<A>(token, p.type, true); break;
			default: //reading everything else with non-recognised name
				if (p.list){
					uint s = internal::readProperty<int>(token, p.listSizeType);
					for (uint i = 0; i < s; ++i)
						internal::readProperty<int>(token, p.type);
				}
				else {
					internal::readProperty<int>(token, p.type);
				}
			}

			if (error)
				return false;
		}
	}
	return true;
}

template <typename A, typename B>
bool loadEdgesBin(
		std::ifstream& file,
		const PlyHeader& header,
		A edges[], //container with push_back method
		io::FileColorMode colorMod ,
		B edgeColors[])
{
	uint colorStep = 3;
	if (colorMod == io::RGBA)
		colorStep = 4;
	for(uint e = 0; e < header.numberEdges(); ++e) {
		for (ply::Property p : header.faceProperties()) {
			switch (p.name) {
			case ply::red :
				edgeColors[e*colorStep] = internal::readProperty<B>(file, p.type); break;
			case ply::green :
				edgeColors[e*colorStep+1] = internal::readProperty<B>(file, p.type); break;
			case ply::blue :
				edgeColors[e*colorStep+2] = internal::readProperty<B>(file, p.type); break;
			case ply::alpha :
				if (colorStep == 4)
					edgeColors[e*colorStep+3] = internal::readProperty<B>(file, p.type);
				else
					internal::readProperty<B>(file, p.type);
					;
				break;
			case ply::vertex1:
				edges[e*2] = internal::readProperty<A>(file, p.type); break;
			case ply::vertex2:
				edges[e*2+1] = internal::readProperty<A>(file, p.type); break;
			case ply::unknown :
			default:
				if (p.list){
					uint s = internal::readProperty<int>(file, p.listSizeType);
					for (uint i = 0; i < s; ++i)
						internal::readProperty<int>(file, p.type);
				}
				else {
					internal::readProperty<int>(file, p.type);
				}
			}
		}
	}
	return true;
}

} //namespace cg3::ply::internal

template <typename A, typename B>
void saveEdges(
		std::ofstream& file,
		const PlyHeader& header,
		const A edges[],
		io::FileColorMode colorMod ,
		const B edgeColors[])
{
	bool bin = header.format() == ply::BINARY;
	uint colorStep = 3;
	if (colorMod == io::RGBA)
		colorStep = 4;
	for(uint e = 0; e < header.numberEdges(); ++e) {
		for (ply::Property p : header.edgeProperties()) {
			switch (p.name) {
			case ply::red :
				internal::writeProperty(file, edgeColors[e*colorStep], p.type, bin, true); break;
			case ply::green :
				internal::writeProperty(file, edgeColors[e*colorStep+1], p.type, bin, true); break;
			case ply::blue :
				internal::writeProperty(file, edgeColors[e*colorStep+2], p.type, bin, true); break;
			case ply::alpha :
				if (colorStep == 4)
					internal::writeProperty(file, edgeColors[e*colorStep+3], p.type, bin, true);
				else
					internal::writeProperty(file, (p.type < 6 ? 255 : 1), p.type, bin, true);
					;
				break;
			case ply::vertex1 :
				internal::writeProperty(file, edges[e*2], p.type, bin, true); break;
			case ply::vertex2 :
				internal::writeProperty(file, edges[e*2+1], p.type, bin, true); break;
			case ply::unknown :
			default:
				internal::writeProperty(file, 0, p.type, bin); break;
			}
		}
	}
}

template <typename A, typename B>
bool loadEdges(
		std::ifstream& file,
		const PlyHeader& header,
		A edges[],
		io::FileColorMode colorMod ,
		B edgeColors[])
{
	if(header.format() == ply::ASCII) {
		return internal::loadEdgesTxt(file, header, edges, colorMod, edgeColors);
	}
	else {
		return internal::loadEdgesBin(file, header, edges, colorMod, edgeColors);
	}
}

} //namespace cg3::ply
} //namespace cg3
