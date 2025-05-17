#ifndef STD_TYPE_H_
#define STD_TYPE_H_

#include <stdbool.h>

typedef unsigned char                   u8 ;
typedef unsigned short int              u16;
typedef unsigned long  int              u32;
typedef unsigned long long int          u64;


typedef signed char                   s8 ;
typedef signed short int              s16;
typedef signed long  int              s32;
typedef signed long long int          s64;

typedef float                         f32 ;
typedef double                        f64 ;

// typedef enum { FALSE , TRUE }BOOL ; // stdbool not working for some reason...


#define   null      ((void*)0)





#endif
