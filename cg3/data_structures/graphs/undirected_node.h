#ifndef CG3_UNDIRECTED_NODE_H
#define CG3_UNDIRECTED_NODE_H

#include <set>

namespace cg3 {

namespace graphs {

template <class T>
class UndirectedNode {
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
        std::set<unsigned int>::iterator begin() const;
        std::set<unsigned int>::iterator end() const;
        unsigned int sizeAdjacentNodes() const;

    protected:
        T info;
        std::set<unsigned int> adjacentNodes;
};

template <class T>
UndirectedNode<T>::UndirectedNode() {
}

template <class T>
UndirectedNode<T>::UndirectedNode(const T& info) : info(info) {
}

template <class T>
void UndirectedNode<T>::setInfo(const T& i) {
    info = i;
}

template <class T>
const T& UndirectedNode<T>::getInfo() const {
    return info;
}

template <class T>
T& UndirectedNode<T>::getInfo() {
    return info;
}

template <class T>
void UndirectedNode<T>::addAdjacent(unsigned int node) {
    adjacentNodes.insert(node);
}

template <class T>
bool UndirectedNode<T>::isAdjacent(unsigned int node) const {
    return adjacentNodes.find(node) != adjacentNodes.end();
}

template <class T>
void UndirectedNode<T>::deleteAdjacent(unsigned int node) {
    adjacentNodes.erase(node);
}

template <class T>
void UndirectedNode<T>::clearAdjacentNodes() {
    adjacentNodes.clear();
}

template <class T>
std::set<unsigned int>::iterator UndirectedNode<T>::begin() const {
    return adjacentNodes.begin();
}

template <class T>
std::set<unsigned int>::iterator UndirectedNode<T>::end() const {
    return adjacentNodes.end();
}

template<class T>
unsigned int UndirectedNode<T>::sizeAdjacentNodes() const {
    return adjacentNodes.size();
}

}

}

#endif // CG3_UNDIRECTED_NODE_H
