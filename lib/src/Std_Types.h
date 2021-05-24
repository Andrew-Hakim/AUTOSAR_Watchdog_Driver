#ifndef _STD_TYPES_H
#define _STD_TYPES_H

typedef signed char sint8_t;
typedef short int   sint16_t;
typedef long int    sint32_t;
typedef long long   sint64_t;

typedef unsigned char      uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long int  uint32_t;
typedef unsigned long long uint64_t;

typedef signed char* psint8_t;
typedef short int*   psint16_t;
typedef long int*    psint32_t;
typedef long long*   psint64_t;

typedef unsigned char*      puint8_t;
typedef unsigned short int* puint16_t;
typedef unsigned long int*  puint32_t;
typedef unsigned long long* puint64_t;

typedef float  f32;
typedef double f64;

typedef float*  pf32;
typedef double* pf64;

#define NULL ((void *)0)

typedef void (*pfun)(void)  ;

#endif
