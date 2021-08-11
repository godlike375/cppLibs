#include<iostream>
#include<typeinfo>
#include<type_traits>
using namespace std;

template<class T> string&& ToString(T& value)
{
	return move(to_string(value));
}
template<> string&& ToString(string& value)
{
	return move(value);
}
class Object
{
	public:
	virtual const char* type()
	{return typeid(*this).name();}
	virtual Object&& operator+(Object*)
	{return Object();}
	virtual operator const char*()
	{return type();}
	virtual bool operator==(Object* o)
	{return this==o;}
};


template<class T> class obj: public Object
{
	public:
	T value;
	obj(T v):value(v){}
	Object&& operator+(Object* o)
	{
		if(o->type()==type())
		{
			return move( obj<T>(value+((obj<T>* )o)->value));
		}
		throw("incorrect type");
	}
	
	obj<T>  operator+(obj<T>& o)
	{
			return obj<T>(value+o.value);
	}
	
	template<class Y> obj<T>  operator+(obj<Y>& o)
	{
		static_assert(is_same<Y,T>::value,"incorrect type");
	}
	
	const char* type()
	{
		return typeid(T).name();
	}
	operator const char*()
	{
		return ToString(value).c_str();
	}
	operator T&()
	{
		return value;
	}
	
	explicit operator Object*()
	{
		return (Object*)this;
	}
	
};

class Kek: public Object
{ public:
	operator const char*(){return "lol";}
};

#define is(obj, T) is_same<decltype(obj), T>::value
#define typeof(obj, T) (typeid(obj).name()==typeid(T).name())

template<class X> bool is_type(Object* o)
{
	return dynamic_cast<X*>(o);
}

int main()
{
	try{
	Kek k;
	obj<string> o("1"), c("2");
	obj<int> i(10);
	Object* b = &c;
	cout<<(o+b);
	}
	catch(const char* e)
	{cout<<e;}
	return 0;
}