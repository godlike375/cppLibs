template<class some> class smartptr{

public:

some * p; //pointer
size_c * c; //counter

inline smartptr():p(0),c(0){};

inline operator some*()
{
	return p;
}
/*
inline smartptr(const smartptr &cop)
{
	p= new some;
	*p=*cop.p;
	c=new int(1);
};
*/
inline smartptr(const smartptr &cop):p(cop.p), c(cop.c)
{
		(*c)++;
};

void clone(const smartptr &cop)
{
	p= new some;
	*p=*cop.p;
	c=new size_c(1);
}

void move(const smartptr &cop)
{
	cop.p= p;
	cop.c=c;
	p=0;
	c=0;
}

inline smartptr(some * n):p(n),c(new size_c(1)){};

void operator=(const smartptr &cop)
{
	if (c)
	{
		if( p!= cop.p)
		{
			if (! (--(*c)) ) 
			{
				delete p;
				delete c;
			} 
			p=cop.p;
			c = cop.c;
			(*c)++;	
		}
	}
	else
	{
		p=cop.p;
		c = cop.c;
		(*c)++;
	}
		
}

void operator=(some * n)
{
	if (c)
	{
		if( p!= n)
		{
			if (! (--(*c)) ) 
			{
				delete p;
				delete c;
			} 
			p=n;
			c=new size_c(1);
		}
	}
	else
	{
		p=n;
		c=new size_c(1);
	}
}
inline some &operator*()
{
	return *p;
}

inline void operator++()
{
	++p;
}

inline void operator--()
{
	--p;
}

inline operator bool()
{
	return bool(p);
}

inline void operator++(int)
{
	p++;
}

inline void operator--(int)
{
	p--;
}

inline some &operator[](size_c w)
{
	return p[w];
}

inline some *operator->()
{
	return p;
}

inline ~smartptr()
{
	if(c)
		if (! (--(*c)) )
		{
			delete c; 
			delete p;
		}

}

};

#define smpt smartptr
#define smrptr smartptr

#undef align


template<class some> class controlptr{

public:

some * p; //pointer

inline controlptr():p(0){};

inline operator some*()
{
	return p;
}

inline controlptr(const controlptr &cop):p(cop.p)
{
	const_cast<controlptr*>(&cop)->p=0;
};

void clone(const controlptr &cop)
{
	p= new some;
	*p=*cop.p;
}

inline controlptr(some * n):p(n){};

void operator=(const controlptr &cop)
{
	p=cop.p;
    const_cast<controlptr*>(&cop)->p=0;
}

void operator=(some * n)
{
	p=n;
}

inline some &operator*()
{
	return *p;
}

inline void operator++()
{
	++p;
}

inline void operator--()
{
	--p;
}

inline operator bool()
{
	return bool(p);
}

inline void operator++(int)
{
	p++;
}

inline void operator--(int)
{
	p--;
}

inline some &operator[](size_c w)
{
	return p[w];
}

inline some *operator->()
{
	return p;
}

inline ~controlptr()
{
	delete p;
}

};

#define cptr controlptr
#define ctrlptr controlptr
