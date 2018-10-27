#ifndef cpp11
template<class T> void move(const T &o, const T &k, bool con = standart)
#else
template<class T, bool con=!std::is_pod<T>::value> void move(const T &o, const T &k)
#endif
{
#if sustom
	  register unsigned int a=sizeof(T)/sizeof(unsigned int*);
	  unsigned int**oo=(unsigned int**)&o, **kk=(unsigned int**)&k;
	  if(a)
	  {
		for (register unsigned short i=0; i<a; i++)
		  *kk++ = *oo++;
	  }
	  a=sizeof(T)%sizeof(unsigned int*);
	  if(a)
	  {
		char *kkk=(char*)kk, *ooo=(char*)oo;
		for(register unsigned short i=0; i<a; i++)
		  *kkk++=*ooo++;
	  }
#else
	  memcpy((const_cast<T*>(&k) ), (const_cast<T*>(&o) ), sizeof(T));
#endif

	if(con)
	{
		(const_cast<T*>(&k) )->~T();
   		new(const_cast<T*>(&o) ) T;	
	}
   	
}
