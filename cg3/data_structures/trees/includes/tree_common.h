#ifndef CG3_TREECOMMON_H
#define CG3_TREECOMMON_H

#include <utility>

namespace cg3 {

    /* Typedefs */

    typedef unsigned long long int TreeSize;

    template <class K>
    using LessComparatorType = bool(*)(const K& key1, const K& key2);


namespace internal {

    /* Default comparator for keys */

    template <class K>
    inline bool defaultComparator(const K& key1, const K& key2) {
        return key1 < key2;
    }



    /* Comparator functions */

    template <class K>
    inline bool isLess(
            const K& a,
            const K& b,
            LessComparatorType<K> lessComparator)
    {
        return lessComparator(a,b);
    }
    template <class K>
    inline bool isEqual(
            const K& a,
            const K& b,
            LessComparatorType<K> lessComparator)
    {
        return !(isLess(a,b,lessComparator) || isLess(b,a,lessComparator));
    }
    template <class K>
    inline bool isLessOrEqual(
            const K& a,
            const K& b,
            LessComparatorType<K> lessComparator)
    {
        return isLess(a,b,lessComparator) || isEqual(a,b,lessComparator);
    }
    template <class K>
    inline bool isGreater(
            const K& a,
            const K& b,
            LessComparatorType<K> lessComparator)
    {
        return isLess(b,a,lessComparator);
    }
    template <class K>
    inline bool isGreaterOrEqual(
            const K& a,
            const K& b,
            LessComparatorType<K> lessComparator)
    {
        return !isLess(a,b,lessComparator);
    }


    /* Utilities */

    /** Comparator for pairs (needed for std::sort) */
    template <class K, class T>
    class PairComparator {

    public:

        PairComparator(const LessComparatorType<K> lessComparator) :
            keyComparator(lessComparator)
        { }

        inline bool operator()(
                const std::pair<K,T>& a,
                const std::pair<K,T>& b) const
        {
            return isLess(a.first, b.first, keyComparator);
        }

    private:

        const LessComparatorType<K> keyComparator;

    };

}

}


#endif // CG3_TREECOMMON_H
