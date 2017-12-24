/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */
#ifndef CG3_TRAITS_H
#define CG3_TRAITS_H

#include <type_traits>
#ifdef CG3_WITH_EIGEN
#include <Eigen/Core>
#endif

/**
  * @link https://stackoverflow.com/questions/22725867/eigen-type-deduction-in-template-specialization-of-base-class
  */
namespace cg3 {
#ifdef CG3_WITH_EIGEN
    namespace isEigenPlainBaseObjectDetail {
        // These functions are never defined.
        template <typename T>
        std::true_type test(const Eigen::PlainObjectBase<T>);
        std::false_type test(...);
    }
    template <typename T>
    struct isEigenPlainBaseObject : public decltype(cg3::isEigenPlainBaseObjectDetail::test(std::declval<T>())) {};
#endif
}

#endif // CG3_TRAITS_H
