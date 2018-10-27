#define maxlinear 16
class manager
{

public:
	struct node
	{
		size_m n;
		char *ofs;
		node(size_m nn, char *of):n(nn),ofs(of)
		{};
		node (){};
	};
	char *arr;
	Hlist<node> free;
	size_m memfree;

	manager(size_m size):free(node(0,0), size/(bits*align) )// :arr(size)
	{
#ifndef arduino
		size += size % align ? align : 0;
		size -= size % align;
#endif
		arr=new char[size];
		(*(free.head) ).t.ofs=arr;
		(*(free.head)).t.n=size;
		memfree=size;
		//free.init(node(size, arr.begin()), size/bits);
	}

	inline void unite(Hlist<node>::lit& bl1)
	{
		(*bl1).n+=bl1->next->t.n;
		bl1++;
		free.remove();
		bl1--;
	}

	inline void cut(Hlist<node>::lit& bl, size_m size)
	{
		(*bl).ofs+=size;
		(*bl).n-=size;
	}

#ifndef cpp11
	template <class cl> cl * New(size_m skolko=1, bool con=standart)
#else
	template <class cl, bool con=!std::is_pod<cl>::value> cl * New(size_m skolko=1)
#endif
	{
		size_m size=sizeof(cl)*skolko;
#ifndef arduino
		size += size % align ? align : 0;
		size -= size % align;
#endif
		if(size>=memfree)
			return 0;
		Hlist<node>::lit it=free.getiter(free.cur);
		for(size_m j=free.cnt, i=0; i<j; it++, i++)
			 if((*it).n > size)
			{
				cl *ret;
					ret=(cl*)(*it).ofs;
					(*it).ofs+=size;
					(*it).n-=size;
				memfree-=size;
				if(con)
					return new(ret) cl[skolko];
				return ret;
			}
			else if((*it).n == size)
			{
				free.remove();
				memfree-=size;
				if(con)
					return new((cl*)(*it).ofs) cl[skolko];
				return (cl*)(*it).ofs;

			}


		return 0;
	}

#ifndef cpp11
	template <class cl> cl * Realloc(void *p, size_m skolkob, size_m skolkos, bool cop=1)
#else
	template <class cl, bool cop=1> cl * Realloc(void *p, size_m skolkob, size_m skolkos)
#endif
	{
		size_m sizeb=sizeof(cl)*skolkob, sizes=sizeof(cl)*skolkos;
#ifndef arduino
		sizeb += sizeb % align ? align : 0;
		sizeb -= sizeb % align;
		sizes += sizes % align ? align : 0;
		sizes -= sizes % align;
#endif
		if(sizeb<sizes)
		{
			if(sizes-sizeb>=memfree)
				return 0;
			Hlist<node>::lit it=free.getiter();
			//Hlist<node>::clit resit=free.getciter(free.head);
			//short f=0;
			char *k=(char*)p+sizeb; //адрес правого прилегающего блока
			if(free.cnt>maxlinear)
			{
				size_m l=0, r=free.cnt+1;
				size_m avg = (r-l)/2;
				it+=avg;
				for(; avg ;)
				{
					if(k > (*it).ofs) // ???
					{
						l+=avg;
						avg = (r-l)/2;
						it+=avg?avg:1;	
					}
					else if(k < (*it).ofs) // ????
					{
						r-=avg;
						avg = (r-l)/2;
						it-=avg;//?avg:1;
					}
					else break;
				}			
			}
			else
			{
				for(; ((*it).ofs < k); it++);
				//for(; (k < (*it).ofs || p>(*it).ofs+(*it).n);)
					//it++;
			}
			if((*it).ofs==k) // нашли правый
			{
				if(sizeb+(*it).n >sizes) //если у правого блока и текущего достаточный размер
				{
					cut(it, sizes-sizeb); //откусываем от него кусок
					memfree-=sizes-sizeb;
					return (cl*)p;
				}
				else if(sizeb+(*it).n == sizes)
				{
					free.remove(); //или же удаляем, если больше не останется
					memfree-=sizes-sizeb;
					return (cl*)p;
				}
				//else if()//есть
			}
			else if(it->back && (it->back->t).ofs + (it->back->t).n == p) //прилегает левый блок
			{
				it--;
				size_m csize=(*it).n+sizeb;
				if(csize>= sizes) //если левый + текущий хватает размера
				{
					//unite(it);
					cl *ret=(cl*)(*it).ofs;
					if((*it).n>sizes)
					{
						(*it).n-=sizes;
						(*it).ofs+=sizes;
					}
					else if((*it).n==sizes)
						free.remove();
					memfree-=sizes-sizeb;
					return ret;	

				}
				else if(it->next->t.n + csize >= sizes) //не хватает, проверяем правый
					 // если с правым хватает
					{
						(*it).n+=sizeb;
						unite(it);
						cl *ret=(cl*)(*it).ofs;
						if((*it).n>sizes)
						{
							(*it).n-=sizes;
							(*it).ofs+=sizes;
						}
						else if((*it).n==sizes)
							free.remove();
						memfree-=sizes-sizeb;
						return ret;						
					}
			}
			else if((*it).ofs + (*it).n==p)
			{
				if((*it).n + sizeb>= sizes) //если левый + текущий хватает размера
				{
					//unite(it);
					(*it).n+=sizeb;
					cl *ret=(cl*)(*it).ofs;
					if((*it).n>sizes)
					{
						(*it).n-=sizes;
						(*it).ofs+=sizes;
					}
					else if((*it).n==sizes)
						free.remove();
					memfree-=sizes-sizeb;
					return ret;					
				}
				else //не хватает, проверяем правый
					if(it->next->t.n + (*it).n + sizeb >= sizes) // если с правым хватает
					{
						//(*it).n+=sizeb;
						unite(it);
						cl *ret=(cl*)(*it).ofs;
						if((*it).n>sizes)
						{
							(*it).n-=sizes;
							(*it).ofs+=sizes;
						}
						else if((*it).n==sizes)
							free.remove();
						memfree-=sizes-sizeb;
						return ret;						
					}
			}

				cl *ret=New<cl>(skolkos);
				if(cop)
				{
					memcpy(ret, p, skolkob*sizeof(cl));
				}
		#ifndef cpp11
			canDelete<cl>(it, p, skolkob, 0);
		#else
			canDelete<cl, 0>(it, p, skolkob);
		#endif
				return ret;
			//if(n==p);
		}else
		if(sizeb>sizes)
		{
			free.cur=free.head;
			Hlist<node>::lit it=free.getiter(free.cur);
			char *k=(char*)p+sizeb;
			size_m s=sizeb-sizes;
			if(free.cnt>maxlinear)
			{
				size_m l=0, r=free.cnt+1;
				size_m avg = (r-l)/2;
				it+=avg;
				for(; avg ;)
				{
					if(k > (*it).ofs) // ???
					{
						l+=avg;
						avg = (r-l)/2;
						it+=avg?avg:1;	
					}
					else if(k < (*it).ofs) // ????
					{
						r-=avg;
						avg = (r-l)/2;
						it-=avg;//?avg:1;
					}
					else break;
				}				
			}
			else 
				for(; ((*it).ofs < k); it++);
				if(k == (*it).ofs)
				{
					(*it).ofs -= sizeb-sizes;
					(*it).n += sizeb-sizes;
				}
				else
					free.insert(node(sizes-sizeb, (char*)p+sizes)); 
		}
		memfree+=sizeb-sizes;
		return (cl*)p;			
		}

#ifndef cpp11
	template <class cl> void canDelete(Hlist<node>::lit &it, void *p, size_m skolko=1, bool des=standart)
#else
	template <class cl, bool des=!std::is_pod<cl>::value> void canDelete(Hlist<node>::lit &it, void *p, size_m skolko=1)
#endif
	{
		if(p)
		{
			if(des)
			{
				cl *d=(cl*)p;
				for (size_m i=0; i<skolko; i++)
				d++->~cl();
			}
			skolko*=sizeof(cl);
	#ifndef arduino
			skolko += skolko % align ? align : 0;
			skolko -= skolko % align;
	#endif		
			if((*it).ofs+(*it).n==p) //левый
			{
				if(it->next && it->next->t.ofs == (char*)p+skolko)
				{ //если есть правый
					if((char*)p+skolko == (it->next->t).ofs ) //если он прилегает
					{
						(it->next->t).ofs= (*it).ofs;
						(it->next->t).n+=(*it).n+skolko;
						free.remove();//it);
					}
				}
				else
				{
					(*it).n+=skolko;
					(*it).ofs-=skolko;	
				}
					
			}
			else if((*it).ofs == (char*)p + skolko) //??? ????
			{
	        	(*it).n+=skolko;
				(*it).ofs=(char*)p;
				if(it->back && it->back->t.ofs+it->back->t.n==p)
				{
					it->back->t.n+=(*it).n;
					//it->back->t.ofs=(*it).ofs;??? ??????? ?? ???? ???? ??? ?? ? ????
					free.remove();						
				}

			}
			else
			{
				free.insert(node(skolko, (char*)p));
			}
		}
		memfree+=skolko;
	}

#ifndef cpp11
	template <class cl> void Delete(void *p, size_m skolko=1, bool des=standart)
#else
	template <class cl, bool des=!std::is_pod<cl>::value> void Delete(void *p, size_m skolko=1)
#endif
	{
		if(p)
		{
			size_m size=skolko*sizeof(cl);
	#ifndef arduino
			size += size % align ? align : 0;
			size -= size % align;
	#endif
			Hlist<node>::lit it=free.getiter();
			char *k=(char*)p+skolko;
			if(free.cnt>maxlinear)
			{
				size_m l=0, r=free.cnt+1;
				size_m avg = (r-l)/2;
				it+=avg;
				for(; avg ;)
				{
					if(k > (*it).ofs) // ???
					{
						l+=avg;
						avg = (r-l)/2;
						it+=avg?avg:1;	
					}
					else if(k < (*it).ofs) // ????
					{
						r-=avg;
						avg = (r-l)/2;
						it-=avg;//?avg:1;
					}
					else break;
				}			
			}
			else 
				for(; ((*it).ofs < k); it++);
				//for(; ((*it).ofs+(*it).n)<p; it++);
	#ifndef cpp11
		canDelete<cl>(it, p, skolko, des);
	#else
		canDelete<cl>(it, p, skolko);
	#endif
		}
	}

	~manager()
	{
		delete[] arr;
	}

};

/*
template<size_m sz> class Smanager
{

public:
	struct node
	{
		size_m n;
		char *ofs;
		node(size_m nn, char *of):n(nn),ofs(of)
		{};
		node (){};
	};
	char arr[sz];
	Slist<node, sz/(bits*16)> free;

	Smanager():free(node(0,0))// :arr(size)
	{
		(*(free.head) ).t.ofs=arr;
		(*(free.head)).t.n=sz;
		//free.init(node(size, arr.begin()), size/bits);
	}


	template <class cl> cl * New(size_m skolko=1, bool con=standart)
	{
		size_m size=sizeof(cl)*skolko;
		size=size>sizeof(void*)? size+size%sizeof(void*) : sizeof(void*);
		typename Slist<node, sz/(bits*16)>::lit it=free.getiter(free.head);
		for(size_m j=free.cnt, i=0; i<j; it++, i++)
			 if((*it).n > size)
			{
				cl *ret;
					ret=(cl*)(*it).ofs;
					(*it).ofs+=size;
					(*it).n-=size;
				if(con)
					return new(ret) cl[skolko];
				return ret;
			}
			else if((*it).n == size)
			{
				free.remove(it); //!!!!!!!!!
				if(con)
					return new((cl*)(*it).ofs) cl[skolko];
				return (cl*)(*it).ofs;

			}


		return 0;
	}

	template <class cl> cl* Realloc(void *p, size_m skolkob, size_m skolkos, bool des=standart)
	{
		size_m sizeb=sizeof(cl)*skolkob, sizes=sizeof(cl)*skolkos;
		sizeb=sizeb>sizeof(void*)? sizeb+sizeb%sizeof(void*) : sizeof(void*);
		sizes=sizes>sizeof(void*)? sizes+sizes%sizeof(void*) : sizeof(void*);
		if(sizeb<sizes)
		{
			typename Slist<node, sz/(bits*16)>::lit it=free.getiter(free.head);
			typename Slist<node, sz/(bits*16)>::lit resit=it;
			size_m t=0;
			char *k=(char*)p+sizeb;
			for(size_m j=free.cnt, i=0; i<j; it++, i++)
				if(k == (*it).ofs)
				{
					if((*it).n > sizes)
					{
						(*it).ofs+=sizes-sizeb;
						(*it).n-=sizes-sizeb;
					}
					else if((*it).n == sizes)
						free.remove(it);
					return (cl*)p;
				}
				else if((*it).n >= sizes)
				{
					resit=((*it).ofs - (char*)p) < ((*resit).ofs -(char*)p) ? it : resit;
				};

				if((*resit).n > sizes)
				{
					memcpy((*resit).ofs, p, skolkos*sizeof(cl));
					p=(*resit).ofs;
					(*resit).ofs+=sizes-sizeb;
					(*resit).n-=sizes-sizeb;
				}
				else if((*resit).n == sizes)
				{
					memcpy((*resit).ofs, p, skolkos*sizeof(cl));
					p=(*resit).ofs;
					free.remove(resit);
				}

		}
		else if(sizeb>sizes)
		{
			typename Slist<node, sz/(bits*16)>::lit it=free.getiter(free.head);
			char *k=(char*)p+sizeb;
			size_m s=(sizeb-sizes);
			for(; ((*it).ofs < k); it++);
				if(k == (*it).ofs)
				{
					(*it).ofs -= s;
					(*it).n += s;
				}
				else
					free.insert(node(s, (char*)p+sizes)); 
		}
		return (cl*)p;
	}

	template <class cl> void Delete(void *p, size_m skolko=1, bool des=standart)
	{
		if(des)
		{
			cl *d=(cl*)p;
			for (size_m i=0; i<skolko; i++)
			d++->~cl();
		}
		skolko*=sizeof(cl);
		skolko=skolko>sizeof(void*)? skolko+skolko%sizeof(void*) : sizeof(void*);
		typename Slist<node, sz/(bits*16)>::lit it=free.getiter(free.head);
				if(free.cnt>maxlinear)
		{
			size_m l=0, r=free.cnt;
			size_m avg = (r-l)/2;
			if(avg)
				for(; avg ;)
				{
					it+=avg-1;
					if((*it).ofs+(*it).n<p) // p ??? ???
						l+=avg;
					else if(p+skolko<(*it).ofs) // p ??????
						r-=avg;
					else break;
					avg = (r-l)/2;
				}			
		}
		else 
			for(; ((*it).ofs <= p) && ((*it).ofs+(*it).n)!=p  && (it.p->next) && (it.p->next != it.p); it++);

				if((*it).ofs+(*it).n==p) //свободный слева, склеиваем
				{
					if(it->next)
						if((char*)p+skolko == (it->next->t).ofs ) //свободный еще и справа
						{
							(it->next->t).ofs= (*it).ofs;
							(it->next->t).n+=(*it).n+skolko;
							free.remove(it); //удаляем левый блок, теперь он 1 общий
						}

					else
						(*it).n+=skolko;
				}
				else if((*it).ofs == (char*)p + skolko) //свободный справа, склеиваем
				{
                	(*it).n+=skolko;
					(*it).ofs=(char*)p;
				}
				else
				{
					free.insert(node(skolko, (char*)p)); //по бокам занятые, вставляем как новый свободный
				}
	}


};
*/

/*

#ifndef cpp11
template<class cl, bool nopod=standart> class Tmanager{};
#else
template<class cl, bool nopod=!is_pod<cl>::value> class Tmanager{};
#endif


template<class cl> class Tmanager<cl, 1>
{
public:

	cl* arr;
	hStack<cl*, 0> free;

	inline Tmanager(size_m size):free(size)
	{
		arr=(cl*)new char[sizeof(cl)*size];
		cl **cur=&arr;
		for(size_m i=0; i<size; i++, cur++)
			free.push(*cur);
	}


	inline cl * New()
	{
		if(free.cur>free.data-1)
			return new(free.pop()) cl;
		return 0;
	}

	inline void Delete(cl *p)
	{
		p->~cl();
		free.push(p);
	}

	inline ~Tmanager()
	{
		for (;free.cur<free.end; free.cur++)
			(*free.cur)->~cl();
		delete[] (char*)arr;
	}

};

template<class cl> class Tmanager<cl, 0>
{
	public:
	cl* arr;
	hStack<cl*, 0> free;

	inline Tmanager(size_m size):free(size)// :arr(size)
	{
		arr=(cl*)new char[sizeof(cl)*size];
		cl **cur=free.data;
		for(size_m i=0; i<size; i++, cur++)
			free.push(*cur);
		free.pop();
	}


	cl * New()
	{
		if(free.cur>free.data)
			return free.pop();
		return 0;
	}

	inline void Delete(cl *p)
	{
		free.push(p);
	}

	inline ~Tmanager()
	{
		delete[] (char*)arr;
	}

};

template<class cl> class bytep1
{
public:

	unsigned char ptr;
	inline bytep1(unsigned char n):ptr(n){};

	inline cl& operator+(void *out)
	{
		return *((cl*)((char*)out+ptr));
	}
};

template<class cl> class bytep2
{
public:

	unsigned short ptr;
	inline bytep2(unsigned short n):ptr(n){};

	inline cl& operator+(void *out)
	{
		return *((cl*)((char*)out+ptr));
	}
};

template<class cl> class bytep4
{
public:

	size_m ptr;
	inline bytep4(size_m n):ptr(n){};

	inline cl& operator+(void *out)
	{
		return *((cl*)((char*)out+ptr));
	}
};

template<class cl> class bytep8
{
public:

	unsigned long long ptr;
	inline bytep8(unsigned long long n):ptr(n){};

	inline cl& operator+(void *out)
	{
		return *((cl*)((char*)out+ptr));
	}
};
*/
