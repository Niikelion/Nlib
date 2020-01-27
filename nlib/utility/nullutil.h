#ifndef NULLUTIL_H_INCLUDED
#define NULLUTIL_H_INCLUDED

                            //define pointer to null if needed
#ifndef NULL_PTR
#if __cplusplus < 201103L   ///NULL for cpp 98
#define NULL_PTR __null
#else                       ///null_ptr for cpp 11+
#define NULL_PTR nullptr
#endif // __cplusplus
#endif // NULL_PTR

#endif // NULLUTIL_H_INCLUDED
