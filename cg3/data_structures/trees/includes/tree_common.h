#ifndef CG3_TREECOMMON_H
#define CG3_TREECOMMON_H

#include <utility>

namespace cg3 {

    /* Typedefs */

    typedef unsigned long long int TreeSize;

    template <class K>
    using DefaultComparatorType = bool(*)(const K& key1, const K& key2);


namespace internal {

    /* Default comparator for keys */

    template <class K>
    inline bool defaultComparator(const K& key1, const K& key2) {
        return key1 < key2;
    }



    /* Comparator functions */

    template <class K, class C>
    inline bool isLess(
            const K& a,
            const K& b,
            C& comparator)
    {
        return comparator(a,b);
    }
    template <class K, class C>
    inline bool isEqual(
            const K& a,
            const K& b,
            C& comparator)
    {
        return !(isLess(a,b,comparator) || isLess(b,a,comparator));
    }
    template <class K, class C>
    inline bool isLessOrEqual(
            const K& a,
            const K& b,
            C& comparator)
    {
        return isLess(a,b,comparator) || isEqual(a,b,comparator);
    }
    template <class K, class C>
    inline bool isGreater(
            const K& a,
            const K& b,
            C& comparator)
    {
        return isLess(b,a,comparator);
    }
    template <class K, class C>
    inline bool isGreaterOrEqual(
            const K& a,
            const K& b,
            C& comparator)
    {
        return !isLess(a,b,comparator);
    }


    /* Utilities */

    /** Comparator for pairs (needed for std::sort) */
    template <class K, class T, class C = DefaultComparatorType<K>>
    class PairComparator {

    public:

        PairComparator(const C& comparator) :
            keyComparator(comparator)
        { }

        inline bool operator()(
                const std::pair<K,T>& a,
                const std::pair<K,T>& b) const
        {
            return isLess(a.first, b.first, keyComparator);
        }

    private:

        const C keyComparator;

    };

}

}


#endif // CG3_TREECOMMON_H
