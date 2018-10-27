#if __cplusplus < 201103L
#define align 16
template<class some, bool nopod=standart> class economptr
#else
#define align alignof(size_c)>alignof(some)?alignof(size_c):alignof(some)
template<class some, bool nopod=!is_pod<some>::value> class economptr
#endif
{
	public:
	some * p; //pointer

	inline operator some*()
	{
		return p;
	}

	inline economptr(const economptr &cop):p(cop.p)
	{
			cop.counter()++;
	};

	void operator=(const economptr &cop)
	{
		size_c* c= &counter();
		if (c)
		{
			if( p!= cop.p)
			{
				if (! (--(*c)) ) 
				{
					if(nopod)
						p->~some();
					delete[] (char*)p; 
				}
				p=cop.p;
				cop.counter()++;	
			}
		}
		else
		{
			p=cop.p;
			cop.counter()++;
		}
	}

	inline economptr():p(0){};
	
#if __cplusplus < 201103L
void New()
#else
template<class ... T> void New(T ... args)
#endif
	{
		if(p)
		{
			size_c* c= &counter();
			if(c)
				if (! --(*c) )
				{
					if(nopod)
						p->~some();
					delete[] (char*)p; 
				}			
		}
		size_m skolko=sizeof(size_c)+sizeof(some);
		skolko += skolko % align ? align : 0;
		skolko -= skolko % align;	
		p = (some*) new char[skolko];
		if(nopod)
#if __cplusplus < 201103L
			if(con)	
				new (p) some;
#else
			new (p) some(args...);	
#endif;
		
		*(size_c*)((char*)p + skolko - sizeof(size_c))=1;		
	}
	
/*
	inline economptr()
	{
		size_m skolko=sizeof(size_m)+sizeof(some);
		skolko += skolko % align ? align : 0;
		skolko -= skolko % align;	
		p = (some*) new char[skolko];
		new (p) some;
		*(size_c*)((char*)p + skolko - sizeof(size_c))=1;
	};
*/	
	inline size_c& counter() const
	{
		size_m skolko=sizeof(size_c)+sizeof(some);
		skolko += skolko % align ? align : 0;
		skolko -= skolko % align;
		return *(size_c*)((char*)p + skolko - sizeof(size_c));
	}

	inline ~economptr()
	{
		size_c* c= &counter();
		if(c)
			if (! --(*c) )
			{
				if(nopod)
					p->~some();
				delete[] (char*)p; 
			}
	
	}

};