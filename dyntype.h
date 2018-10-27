
template <class T> struct type{};


//mypair<size_m, char*> size_name[11];

#define do_with(T, D)\


#define type(T, n) \
template<>struct type<T>\
{\
static const char * name;\
static const unsigned int id = n;\
};\
const char* type<T>::name=#T;

type(unsigned char, 1)
type(char, 2)
type(unsigned short, 3)
type(short, 4)
type(unsigned int, 5)
type(int, 6)
type(unsigned long, 7)
type(long, 8)
type(double, 9)
type(float, 10)
type(long long, 11)
type(unsigned long long, 12)

#define add_class(T) #T,

char* names_types[] = 
{
	"Custom",
	#include"user/classes.h"
};

#define add_class(T) sizeof(T),

size_x sizes_types[] = 
{
	0,
	#include"user/classes.h"
};

#define is(L, R)\
((L).id == type<R>::id)

#define as(L, R)\
((L).id == (R).id)

#define typeof(T)\
(type<T>::name)

#define nametype(T)\
(names_types[(T).id])

#define sizetype(T)\
(sizes_types[(T).id])