#ifndef CG3_CG3LIB_H
#define CG3_CG3LIB_H

#if __cplusplus >= 201300
#define CG3_CPP14
#endif

/**
  * @link: https://stackoverflow.com/questions/11124895/suppress-compiler-warning-function-declared-never-referenced
  */
#define CG3_SUPPRESS_WARNING(a) (void)a

/**
  * @link: https://stackoverflow.com/questions/20631922/expand-macro-inside-string-literal
  */
#define CG3_STRINGIFY2(X) #X
#define CG3_STRINGIFY(X) CG3_STRINGIFY2(X)

#endif // CG3_CG3LIB_H
