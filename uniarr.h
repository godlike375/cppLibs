class uniarr
{
void * p;
int size;
public:
bool id;
uniarr()
{
	p=0;
}

inline template<class t>void array(t *temp, int siz)
{
	size=siz;
	p=new t[size];
	for (t *i = temp, *j=(t*)p; siz--; )
		*i++=*j++;
}

inline template<class t>void re()
{
	t* n=new t[size];
	int siz=size;
	for (t *i = n, *j=(t*)p; siz--; )
		*i++=*j++;
	p=n;
}

inline template<class t>void readress()
{
	t* n=new t[size];
	int siz=size;
	for (t *i = n, *j=(t*)p; siz--; )
		*i++=*j++;
	delete []p; 
	p=n;
}

inline template<class t> uniarr(t *temp, int siz)
{
	size=siz;
	p=new t[size];
	for (t *i = temp, *j=(t*)p; siz--; )
		*i++=*j++;
}

inline template<class t>& in(int w)
{
	return ((t*)p)[w];
}

inline void * operator!()
{
  return p;
}

 ~uniarr()
{
		delete []p;
}

friend class uniarr;

};

typedef uniarr vararr;