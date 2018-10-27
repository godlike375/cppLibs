class var
{
public:
long long p;
size_m id;
inline var(){p=0;};

template<class t> var(const t& temp)
{
	*((t*)&p)=temp;
	id = type<t>::id;
};

#define add_class(T)\
case type<T>::id : ((T&)*this)++; break;

void operator++(int)
{
	switch(id)
	{
		#include "user/classes.h"
	}
}

#define add_class(T)\
case type<T>::id : ((T&)*this)--; break;

void operator--(int)
{
	switch(id)
	{
		#include "user/classes.h"
	}	
}

#define add_class(T)\
case type<T>::id : ++((T&)*this); break;

void operator++()
{
	switch(id)
	{
		#include "user/classes.h"
	}
}

#define add_class(T)\
case type<T>::id : --((T&)*this); break;

void operator--()
{
	switch(id)
	{
		#include "user/classes.h"
	}	
}

#define add_class(T)\
case type<T>::id :\ 
if(sizetype(r)<sizetype(*this))\
{\
	switch(r.id)\
	{\
		case type<unsigned int>::id : (T&)(*this)+=(unsigned int&)r; break;\
		case type<int>::id : (T&)(*this)+=(int&)r; break;\
		case type<unsigned long>::id : (T&)(*this)+=(unsigned long&)r; break;\
		case type<long>::id : (T&)(*this)+=(long&)r; break;\
		case type<double>::id : (T&)(*this)+=(double&)r; break;\
		case type<float>::id : (T&)(*this)+=(float&)r; break;\
		case type<unsigned long long>::id : (T&)(*this)+=(unsigned long long&)r; break;\
		case type<long long>::id : (T&)(*this)+=(long long&)r; break;\
	}\
}break;

void operator+=(const var& r)
{
	switch(id)
	{
		#include "user/classes.h"
	}	
}


#define add_class(T)\
case type<T>::id :\ 
if(sizetype(r)<sizetype(*this))\
{\
	switch(r.id)\
	{\
		case type<unsigned int>::id : (T&)(*this)-=(unsigned int&)r; break;\
		case type<int>::id : (T&)(*this)-=(int&)r; break;\
		case type<unsigned long>::id : (T&)(*this)-=(unsigned long&)r; break;\
		case type<long>::id : (T&)(*this)-=(long&)r; break;\
		case type<double>::id : (T&)(*this)-=(double&)r; break;\
		case type<float>::id : (T&)(*this)-=(float&)r; break;\
		case type<unsigned long long>::id : (T&)(*this)-=(unsigned long long&)r; break;\
		case type<long long>::id : (T&)(*this)-=(long long&)r; break;\
	}\
}break;

void operator-=(const var& r)
{
	switch(id)
	{
		#include "user/classes.h"
	}	
}

#define add_class(T)\
case type<T>::id :\ 
if(sizetype(r)<sizetype(*this))\
{\
	switch(r.id)\
	{\
		case type<unsigned int>::id : (T&)(*this)*=(unsigned int&)r; break;\
		case type<int>::id : (T&)(*this)*=(int&)r; break;\
		case type<unsigned long>::id : (T&)(*this)*=(unsigned long&)r; break;\
		case type<long>::id : (T&)(*this)*=(long&)r; break;\
		case type<double>::id : (T&)(*this)*=(double&)r; break;\
		case type<float>::id : (T&)(*this)*=(float&)r; break;\
		case type<unsigned long long>::id : (T&)(*this)*=(unsigned long long&)r; break;\
		case type<long long>::id : (T&)(*this)*=(long long&)r; break;\
	}\
}break;

void operator*=(const var& r)
{
	switch(id)
	{
		#include "user/classes.h"
	}	
}


#define add_class(T)\
case type<T>::id :\ 
if(sizetype(r)<sizetype(*this))\
{\
	switch(r.id)\
	{\
		case type<unsigned int>::id : (T&)(*this)/=(unsigned int&)r; break;\
		case type<int>::id : (T&)(*this)/=(int&)r; break;\
		case type<unsigned long>::id : (T&)(*this)/=(unsigned long&)r; break;\
		case type<long>::id : (T&)(*this)/=(long&)r; break;\
		case type<double>::id : (T&)(*this)/=(double&)r; break;\
		case type<float>::id : (T&)(*this)/=(float&)r; break;\
		case type<unsigned long long>::id : (T&)(*this)/=(unsigned long long&)r; break;\
		case type<long long>::id : (T&)(*this)/=(long long&)r; break;\
	}\
}break;


void operator/=(const var& r)
{
	switch(id)
	{
		#include "user/classes.h"
	}	
}


template<class t> operator t&()
{
#ifdef safe
	if(id!=type<t>::id)
		throw("inner type isn't same as in converting in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
	return *((t*)&p);
}

template<class t> void operator=(const t &temp)
{
	*((t*)&p)=temp;
	id = type<t>::id;
}

void operator=(const var& v)
{
	p=v.p;
	id=v.id;
}


template<class t> void clear()
{
	((t*)p)->~t();
	*((unsigned long long*)&p)=0;
}

template<class t> t& get()
{
	return *(t*)p;
}

/*
inline ~var()
{
	delete p;
}
*/

};


#define type_assign(T) case type<T>::id: (T &)l=(T &)r; break;

void assign(var &l, var &r)
{
	if(l.id==r.id)
		switch(l.id)
		{
			type_assign(int)
			type_assign(double)	
		}
}


type(DynArr<var>, 12)

#define add_class(T) type_print(T)

#define type_print(T) case type<T>::id: cout<<(T &)v; break;

void print(var& v)
{
	cout.precision(10);
	switch(v.id)
	{
		#include"user/classes.h"
		/*
		type_print(int)
		case type<double>::id: {cout.precision(10); cout<<(double &)v; break;}
		type_print(float)
		type_print(short)
		*/
	}
}
