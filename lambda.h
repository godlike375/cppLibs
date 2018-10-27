
template<class T>class func
{
public:
	virtual T operator()()=0;
};

template<class T, class P1>class func1
{
public:
	virtual T operator()(P1 p1)=0;
};

template<class T, class P1, class P2>class func2
{
public:
	virtual T operator()(P1 p1, P2 p2)=0;
};

template<class T, class P1, class P2, class P3>class func3
{
public:
	virtual T operator()(P1 p1, P2 p2, P3 p3)=0;
};

#define lambda(t,a,x) \
class:public func<t>\
{public: virtual t operator()(){ x ;}}a;

#define lambda1(t,a,x, p1) \
class:public func1<t, p1>\
{public: virtual t operator()(p1 arg1){ x ;}}a;


#define lambda2(t,a,x, p1, p2) \
class:public func2<t, p1, p2>\
{public: virtual t operator()(p1 arg1, p2 arg2){ x ;}}a;

#define lambda3(t,a,x, p1, p2, p3) \
class:public func3<t, p1, p2, p3>\
{public: virtual t operator()(p1 arg1, p2 arg2, p3 arg3){ x ;}}a;


#define fun1(t) func1(t,
#define fun2(t) func2(t,
#define fun3(t) func2(t,


#define fun(t) \
class:public func<t>\
{public: virtual t operator()()

#define func1(t, p1) \
class:public func1<t, p1>\
{public: virtual t operator()(p1 arg1)

#define func2(t, p1, p2) \
class:public func2<t, p1, p2>\
{public: virtual t operator()(p1 arg1, p2 arg2)

#define func3(t, p1, p2, p3) \
class:public func3<t, p1, p2, p3>\
{public: virtual t operator()(p1 arg1, p2 arg2, p3 arg3)


#define foreach(new_var, array)\
        for(size_m index = 0, f=1; index < (sizeof(array)/sizeof(*array)); ++index, f++)\
        	for(new_var = array[index]; f ; f--)
        	
#define for_each(new_var, array)\
        for(size_m index = 0, f=1; index < array.length(); ++index, f++)\
        	for(new_var = array[index]; f ; f--)
