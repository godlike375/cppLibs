class var
{
public:
void * p;
size_m id;
inline var():p(0){};

template<class t>void re()
{
	p=new t(*(t*)p);
}

template<class t> var(const t& temp):p(new t(temp))
{
	id = type<t>::id;
};

template<class t>void copy(const var &cop)
{
	p=new t(*(t*)cop.p);
	id=cop.id;
};

template<class t>void assign(const var &cop)
{
	id=cop.id;
	delete p;
	p=new t(*cop.p);
};

template<class t> operator t&()
{
	return *(t *)p;
}

template<class t> void operator=(const t &temp)
{
	delete p; //здесь можно перебирать деструкторы в массиве и вызывать нужный
	p=new t(temp);
	id = type<t>::id;
}

template<class t> void clear()
{
	((t*)p)->~t();
	delete p;
	p=0;
}

template<class t> t& get()
{
	return *(t*)p;
}

inline void * operator!()
{
  return p;
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
