/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */

#ifndef CG3_UNDIRECTED_NODE_H
#define CG3_UNDIRECTED_NODE_H

#include <unordered_set>
#include <cg3/io/serialize.h>

namespace cg3 {

template <class T>
class UndirectedNode : public SerializableObject
{
public:
    UndirectedNode();
    UndirectedNode(const T& info);
    void setInfo(const T& i);
    const T& getInfo() const;
    T& getInfo();
    void addAdjacent(unsigned int node);
    bool isAdjacent(unsigned int node) const;
    void deleteAdjacent(unsigned int node);
    void clearAdjacentNodes();
    std::unordered_set<unsigned int>::const_iterator begin() const;
    std::unordered_set<unsigned int>::const_iterator end() const;
    unsigned int sizeAdjacentNodes() const;

    // SerializableObject interface
    void serialize(std::ofstream &binaryFile) const;
    void deserialize(std::ifstream &binaryFile);

protected:
    T info;
    std::unordered_set<unsigned int> adjacentNodes;
};

template <class T>
UndirectedNode<T>::UndirectedNode()
{
}

template <class T>
UndirectedNode<T>::UndirectedNode(const T& info) : info(info)
{
}

template <class T>
void UndirectedNode<T>::setInfo(const T& i)
{
    info = i;
}

template <class T>
const T& UndirectedNode<T>::getInfo() const
{
    return info;
}

template <class T>
T& UndirectedNode<T>::getInfo()
{
    return info;
}

template <class T>
void UndirectedNode<T>::addAdjacent(unsigned int node)
{
    adjacentNodes.insert(node);
}

template <class T>
bool UndirectedNode<T>::isAdjacent(unsigned int node) const
{
    return adjacentNodes.find(node) != adjacentNodes.end();
}

template <class T>
void UndirectedNode<T>::deleteAdjacent(unsigned int node)
{
    adjacentNodes.erase(node);
}

template <class T>
void UndirectedNode<T>::clearAdjacentNodes()
{
    adjacentNodes.clear();
}

template <class T>
std::unordered_set<unsigned int>::const_iterator UndirectedNode<T>::begin() const
{
    return adjacentNodes.begin();
}

template <class T>
std::unordered_set<unsigned int>::const_iterator UndirectedNode<T>::end() const
{
    return adjacentNodes.end();
}

template<class T>
unsigned int UndirectedNode<T>::sizeAdjacentNodes() const
{
    return (unsigned int)adjacentNodes.size();
}

template<class T>
void UndirectedNode<T>::serialize(std::ofstream &binaryFile) const
{
    cg3::serializeObjectAttributes("cg3UndirectedNode", binaryFile, info, adjacentNodes);
}

template<class T>
void UndirectedNode<T>::deserialize(std::ifstream &binaryFile)
{
    cg3::deserializeObjectAttributes("cg3UndirectedNode", binaryFile, info, adjacentNodes);
}

} //namespace cg3

#endif // CG3_UNDIRECTED_NODE_H
