#ifndef CG3_ARRAY_H
#define CG3_ARRAY_H

#include <vector>
#include <assert.h>
#include <iomanip>
#include <cg3/io/serialize.h>

#ifdef _WIN32
#undef min
#undef max
#endif

namespace cg3 {

template <class T, size_t N>
class Array : SerializableObject {
        static_assert(N > 0, "Array dimension must be > 0.");

    public:
        Array();
        template<typename... Sizes>
        Array(Sizes... sizes);
        unsigned long int dimensions() const;
        template<typename... I>
        T& operator () (I... indices);
        template<typename... I>
        T operator () (I... indices) const;
        template<typename... I>
        const T* cArray(I... indices) const;

        void fill (const T& t);
        unsigned long int size(unsigned long int dim) const;

        T& min();
        const T& min() const;
        T& max();
        const T& max() const;

        template<typename... Sizes>
        void resize (Sizes... s);

        template<typename... Sizes>
        void conservativeResize (Sizes... s);

        void clear();

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        void deserialize(std::ifstream& binaryFile);

    private:
        unsigned long int getIndex(const unsigned long int indices[]) const;
        std::array<unsigned long int, N> reverseIndex(unsigned int index);
        static unsigned long int getIndex(const unsigned long int indices[], const unsigned long int sizes[]);

        std::array<unsigned long int, N> sizes;
        std::vector<T> v;
};

}

#include "array.tpp"

#endif // CG3_ARRAY_H
