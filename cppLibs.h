#ifndef mylibs
#define mylibs

#if __cplusplus >= 201103L
	#define cpp11
#endif

#ifndef custom
	#define custom 0
	#ifndef arduino
		#include <memory.h>
	#endif
#endif

//#define safe

#ifdef safe
	#define stringize(x) #x
	#define str(x) stringize(x)
#endif


#ifndef arduino
#define align 8
	#if _WIN32 || _WIN64
		#if _WIN64
			#define bits 8
		#else
			#define bits 4
		#endif
	#endif

	#if __GNUC__
		#if __x86_64__ || __ppc64__
			#define bits 8
		#else
			#define bits 4
		#endif
	#endif

#else

	#define bits 2

#endif


#if bits==4
	typedef unsigned int size_m;
	typedef unsigned short size_x;
#elif bits==8
	typedef unsigned long long size_m;
	typedef unsigned int size_x;
#elif bits==2
	typedef unsigned short size_m;
	typedef unsigned char size_x;
#endif



#ifndef cpp11
	#ifndef standart
		#define standart 1
	#endif
#else
	#ifndef arduino
		#include<type_traits>
	#endif
#endif


#ifndef _IOSTREAM_H_
	#ifndef _IOSTREAM_
		#if _GLIBCXX_IOSTREAM == 0
			#ifndef noplacnew
				#include "placnew.h"
			#endif
		#endif
	#endif
#else
	#define iostr
#endif

#if bits == 8
  typedef size_x size_c;
#else
  typedef size_m size_c;
#endif

//#include <fstream>

#include "move.h"

//#include "lambda.h"

#include "ring.h"

#include "packing.h"

#include "dynstr.h"
#include "dynarr.h"

#include "stack.h"
#include "list.h"

#include "funcstr.h"

#include "myparser.h"
#include "neuro.h"

#include "myalloc.h"

#include "mypair.h"

//#include "dyntype.h"

//#include "uni.h"

#include "3bytes.h"


#include "smartptr.h"



//#include "database.h"


#undef stringize
#undef str
#undef align


#endif