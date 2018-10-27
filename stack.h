
#ifndef cpp11
	template<class T, bool nopod=standart> class hStack{};
#else
	template<class T, bool nopod=!std::is_pod<T>::value> class hStack{};
#endif


template<class T> class hStack<T, 0>
{
public:
	T *end;
	T *data;
	T *cur;

	inline hStack(unsigned int size):data((T*) new char[sizeof(T)*size])
	{
		end=(data+size-1);
		cur=data-1;
	};

	inline void push(const T &p)
	{
#ifndef safe
		*++cur=p;
#else
		if(cur<end)
			*++cur=p;
		else
			throw("stack already full, can't push in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
	}

	inline T& pop()
	{
#ifndef safe
		return *cur--;
#else
		if(cur>data)
			return *cur--;
		else
			throw("stack is empty, can't pop in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif		
	}

	inline ~hStack()
	{
		delete[] (char*)data;
	}
};

template<class T> class hStack<T, 1>
{
public:
	T *end;
	T *data;
	T *cur;

	inline hStack(unsigned int size):data((T*) new char[sizeof(T)*size])
	{
		end=(data+size-1);
		cur=data-1;
	};

	inline void push(const T &p)
	{
#ifndef safe
		new(++cur) T(p);
#else
		if(cur<end)
			new(++cur) T(p);
		else
			throw("stack already full, can't push in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
	}

	inline T& pop()
	{
#ifndef safe
		return *cur--;
#else
		if(cur>data)
			return *cur--;
		else
			throw("stack is empty, can't pop in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif		
	}

	inline void destr_last()
	{
#ifndef safe
		return *cur--;
#else
		if(cur+1>data)
			(cur+1)->~T();
		else
			throw("stack is empty, can't destruct object in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif	
		
	}
	
	inline ~hStack()
	{
		for(; cur>data; cur--)
			cur->~T();
		delete[] (char*)data;
	}
};
/*
template<class T, unsigned int size, bool nopod=1> class Stack
{};

template<class T, unsigned int size> class Stack<T, size, 0>
{
public:
	T *end;
	char data[size*sizeof(T)];
	T *cur;
	inline Stack():end(((T*)data)+(size-1)),cur(((T*) &data[0])-1){};

	inline void push(const T &p)
	{
		*++cur=p;
	}

	inline T& pop()
	{
		return *cur--;
	}	
};


template<class T, unsigned int size> class Stack<T, size, 1>
{
public:
	T *end;
	char data[size*sizeof(T)];
	T *cur;
	inline Stack():end(((T*)data)+(size-1)),cur(((T*) &data[0])-1){};

	inline void push(const T &p)
	{
		new(++cur) T(p);
	}

	inline T& pop()
	{
		return *cur--;
	}

	inline void destr_last()
	{
		(cur+1)->~T();
	}

	inline ~Stack()
	{
		for(; cur>data; cur--)
			cur->~T();
	}
};
*/
