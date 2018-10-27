class RingBuffer
{
	public:
	size_x size;
	size_x cur;
	char *buf;

	RingBuffer(size_x s):cur(0), size(s)
	{
#ifndef arduino
		size += size % align ? align : 0;
		size -= size % align;
#endif
		buf = new char[size];
	}

#ifndef cpp11
	template<class cl> cl* New(size_x skolko=1, bool con=standart)
#else
	template <class cl, bool con=!std::is_pod<cl>::value> cl * New(size_x skolko=1)
#endif	
	{
		size_x s = sizeof(cl)*skolko;
#ifndef arduino
	#ifndef cpp11
		cur += ((size_m)buf+cur) % align? align: 0;
		cur -= ((size_m)buf+cur) % align;
	#else
		cur += ((size_m)buf+cur) % alignof(cl)? align: 0;
		cur -= ((size_m)buf+cur) % alignof(cl);
	#endif
#endif
		cur = size-cur>=s? cur: 0; 
		cur+=s;

		if(con)
			return new((cl*)(buf+cur-s)) cl[skolko];
		else
			return (cl*)(buf+cur-s);	

	}

	~RingBuffer()
	{
		delete[] buf;
	}

};

#ifndef cpp11
template<class data, class S=size_x, bool nopod=true> class SpecRingBuffer{};
#else
template<class data, class S=size_x, bool nopod=!std::is_pod<data>::value> class SpecRingBuffer{};
#endif


template<class data, class S> class SpecRingBuffer<data, S, 1>
{
public:
	data *buf;
	S size;
	S cur;

	inline SpecRingBuffer(S skolko=1):cur(0), size(skolko)
	{
		//buf = (data*)new char[sizeof(data)*skolko];
		buf = new data[skolko];
	}

	inline data* New(S skolko=1)
	{
		cur = size-cur>=skolko? cur: 0;
		data *old = buf+cur;
		for(S i =0; i<skolko; i++)
			(*old++).~data();
		cur+=skolko; 
		return new(buf+cur-skolko) data[skolko];
	}

	inline ~SpecRingBuffer()
	{
		delete[] buf;
		/*
		data *p = (data*)buf;
		for(S i=0; i<size; i++)
			(*p++).~data();
		delete[] (char*)buf;
		*/
	}
};

template<class data, class S> class SpecRingBuffer<data, S,0>
{
public:
	data *buf;
	S size;
	S cur;

	inline SpecRingBuffer(S skolko=1):cur(0), size(skolko)
	{
		buf = (data*)new char[sizeof(data)*skolko];
	}

	inline data* New(S skolko=1)
	{
		cur = size-cur>=skolko? cur: 0;
		cur+=skolko; 
		return buf+cur-skolko;
	}

	inline ~SpecRingBuffer()
	{
		delete[] (char*)buf;
	}
};
