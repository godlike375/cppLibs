#define iter(x) list<x>::lit

/*
	template<class T> class list
	{
	public:
		struct ln
		{
			ln(const T &n):t(n), next(0), back(0){};
			T t;
			ln *next;
			ln *back;
			inline T& operator*()
			{
				return t;
			}
		};
		class clit;
		class lit
		{
		public:
			ln *p;
			inline lit(clit& it):p(it.p){};

			inline lit(list *l):p(l->cur){};

			inline lit(ln *n):p(n){};

			inline lit(list *l, size_c n)
			{
				l.find(n);
				p=l.cur;
			}

			inline void operator++(int)
			{
				p=p->next;
			}

			inline void operator--(int)
			{
				p=p->back;
			}

			inline T& operator*()
			{
				return p->t;
			}

			inline ln* operator->()
			{
				return p;
			}

			inline operator ln*()
			{
				return p;
			}

		};

		class clit
		{
		public:
			ln* p;
			
			inline clit(lit& it):p(it.p){};

			inline clit(list *const l ):p(l->cur){};

			inline clit(ln * n ):p(n){};

			inline void operator+=(size_c i)
			{
				for(int j=0; j<i; j++)
					p=p->next;
			}

			inline void operator-=(size_c i)
			{
				for(int j=0; j<i; j++)
					p=p->back;
			}

			inline void operator++(int)
			{
				p=p->next;
			}

			inline void operator--(int)
			{
				p=p->back;
			}

			inline T& operator*()
			{
				return p->t;
			}

			inline ln* operator ->()
			{
				return p;
			}

			inline operator ln*()
			{
				return p;
			}

		};

		ln *head;
		ln *end;
		ln *cur;
		size_c icur;
		size_c cnt;

		#include "listsame.h"
		inline list(const T &n):head(new ln(n)),cur(head), end(head),cnt(1),icur(0){};

		inline list():head(0),cur(0), end(0),cnt(0), icur(0){};

		inline void init(const T &n)
		{
			head=new ln(n);
			cur=head;
			end=head;
			cnt=1;
		}

		inline void add(const T &n)
		{
			end->next=new ln(n);
			end->next->back=end;
			end=end->next;
			cnt++;
			cur=end;
			icur=cnt-1;
		}

		inline void addbeg(const T &n)
		{
			cur=new ln(n);
			if(head->next)
				head->next->back=head;
			head->back=cur;
			cnt++;
			cur->next=head;
			head=cur;
			icur=0;
		}

		inline void insert(size_c w, const T &n)
		{
			find(w);
			if(cur==head)
			{
				addbeg(n);
				return;
			}
			ln *ret=cur;
			cur=new ln(n);
			cur->back=ret->back;
			if(ret->back)
			{
				ret->back->next=cur;
				ret->back=cur;
            }
			cur->next=ret;
			cnt++;
		}

		inline void insert(const T &n)
		{
			if(cur==head)
			{
				addbeg(n);
				return;
			}

			ln *ret=cur;
			cur=new ln(n);
			cur->back=ret->back;
			if(ret->back)
			{
				ret->back->next=cur;
				ret->back=cur;
			}
			cur->next=ret;
			cnt++;
		}



		inline void clear()
		{
			cur=head;
			ln *tmp;
			for (int i=0; i<cnt; i++)
			{
				tmp=cur->next;
				delete cur;
				cur=tmp;
			}
			cnt=icur=0;
			cur=head=end=0;
		}
		
		inline ~list()
		{
			cur=head;
			ln *tmp;
			for (int i=0; i<cnt; i++)
			{
				tmp=cur->next;
				delete cur;
				cur=tmp;
			}
		}

	};
*/
	template<class T> class Hlist
	{

	public:
	struct ln;
	hStack<ln*, 0> nodes;

		struct ln
		{
			ln(const T &n):t(n), next(0), back(0){};
			ln():next(0),back(0){};
			T t;
			ln *next;
			ln *back;
			inline T& operator*()
			{
				return t;
			}
/*			inline void* operator new(size_c size, Hlist *h)
			{
				return h->nodes.pop();
			}
*/
		};

		class lit
		{
		public:
			ln* &p;

			//inline lit(const lit& cop):p(cop.p){};

			inline lit(Hlist *const l ):p(l->cur){};

			inline lit(ln *& n ):p(n){};

			/*
			inline lit(Hlist *const l , size_c n)
			{
				l.find(n);
				p=l.cur;
			}
			*/
			inline void operator+=(size_c i)
			{
#ifndef safe
				for(int j=0; j<i; j++)
					p=p->next;
#else
				int j=0;
				for(; j<i && p; j++)
					p=p->next;
				if(++j<i)
					throw("iterator is null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
			}

			inline void operator-=(size_c i)
			{
#ifndef safe
				for(int j=0; j<i; j++)
					p=p->back;
#else
				int j=0;
				for(; j<i && p; j++)
					p=p->back;
				if(++j<i)
					throw("iterator is null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
			}

			inline void operator++(int)
			{
#ifndef safe
				p=p->next;
#else
				if(p)
					p=p->next;
				else
					throw("iterator is null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
			}

			inline void operator--(int)
			{
#ifndef safe
				p=p->back;
#else
				if(p)
					p=p->back;
				else
					throw("iterator is null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
			}

			inline T& operator*()
			{
#ifndef safe
				return p->t;
#else
				if(p)
					return p->t;
				else
					throw("iterator is null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
			}

			inline ln* operator ->()
			{
				return p;
			}

			inline operator ln*()
			{
				return p;
			}

		};

		class clit
		{
		public:
			ln* p;

			//inline lit(const lit& cop):p(cop.p){};

			inline clit(Hlist *const l ):p(l->cur){};

			inline clit(ln * n ):p(n){};

			/*
			inline lit(Hlist *const l , size_c n)
			{
				l.find(n);
				p=l.cur;
			}
			*/
			inline void operator+=(size_c i)
			{
#ifndef safe
				for(int j=0; j<i; j++)
					p=p->next;
#else
				int j=0;
				for(; j<i && p; j++)
					p=p->next;
				if(++j<i)
					throw("iterator is null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
			}

			inline void operator-=(size_c i)
			{
#ifndef safe
				for(int j=0; j<i; j++)
					p=p->back;
#else
				int j=0;
				for(; j<i && p; j++)
					p=p->back;
				if(++j<i)
					throw("iterator is null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
			}

			inline void operator++(int)
			{
#ifndef safe
				p=p->next;
#else
				if(p)
					p=p->next;
				else
					throw("iterator is null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
			}

			inline void operator--(int)
			{
#ifndef safe
				p=p->back;
#else
				if(p)
					p=p->back;
				else
					throw("iterator is null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
			}

			inline T& operator*()
			{
#ifndef safe
				return p->t;
#else
				if(p)
					return p->t;
				else
					throw("iterator is null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
			}

			inline ln* operator ->()
			{
				return p;
			}

			inline operator ln*()
			{
				return p;
			}

		};

		ln *head;
		ln *end;
		ln *cur;
		size_c cnt;
        ln *const pool;


		inline Hlist(const T &n, size_c sz):cnt(1), nodes(sz), pool(::new ln[sz])
		{
			cur=pool+sz-1;
			for(size_c i=0, len=sz-1; i<len; i++, cur--) //если sz-1, то ошибка памяти
				nodes.push(cur);
			//nodes.pop();
			head=new(cur) ln(n);
			end=head;
		};
		inline Hlist():head(0),cur(0), end(0),cnt(0){};

		inline void init(const T &n, size_c sz)
		{
			head=new(nodes.pop()) ln(n);
			cur=head;
			end=head;
			cnt=1;
			pool=new ln[sz];
			new(&nodes) hStack<ln*, 0>(sz);
		}

		inline void add(const T &n)
		{
			end->next=new(nodes.pop()) ln(n);
			end->next->back=end;
			end=end->next;
			cnt++;
			cur=end;
		}

		inline void addbeg(const T &n)
		{
			cur=new(nodes.pop()) ln(n);
			if(head->next)
				head->next->back=head;
			head->back=cur;
			cnt++;
			cur->next=head;
			head=cur;
		}

		inline void insert(size_c w, const T &n)
		{
			find(w);
			if(cur==head)
			{
				addbeg(n);
				return;
			}
			ln *ret=cur;
			cur=new(nodes.pop()) ln(n);
			cur->back=ret->back;
			if(ret->back)
			{
				ret->back->next=cur;
				ret->back=cur;
			}
			cur->next=ret;
			cnt++;
		}

		inline void insert(const T &n)
		{
			if(cur==head)
			{
				addbeg(n);
				return;
			}

			ln *ret=cur;
			cur=new(nodes.pop()) ln(n);
			cur->back=ret->back;
			if(ret->back)
			{
				ret->back->next=cur;
				ret->back=cur;
			}
			cur->next=ret;
			cnt++;
		}

#define delete(x)\
 nodes.push(x)
#include "listsame.h"
#undef delete

		inline void clear()
		{
			delete[] pool;
			nodes.~hStack();
		}
		
		inline ~Hlist()
		{
			::delete[] pool;
		}

	};

/*
	template<class T, int sz> class Slist
	{

	public:
	struct ln;
	Stack<ln*, sz, 0> nodes;

		struct ln
		{
			ln(const T &n):t(n), next(0), back(0){};
			ln():next(0),back(0){};
			T t;
			ln *next;
			ln *back;
			inline T& operator*()
			{
				return t;
			}
			inline void* operator new(size_c size, Hlist *h)
			{
				return h->nodes.pop();
			}

		};

		class lit
		{
		public:
			ln *p;

			inline lit(Slist *const l ):p(l->cur){};

			inline lit(ln *const n ):p(n){};

			inline lit(Slist *const l , size_c n)
			{
				l.find(n);
				p=l.cur;
			}
			
			inline void operator+=(size_c i)
			{
				for(int j=0; j<i; j++)
					p=p->next;
			}

			inline void operator-=(size_c i)
			{
				for(int j=0; j<i; j++)
					p=p->back;
			}
			
			inline void operator++(int)
			{
				p=p->next;
			}

			inline void operator--(int)
			{
				p=p->back;
			}

			inline T& operator*()
			{
				return p->t;
			}

			inline ln* operator->()
			{
				return p;
			}

			inline operator ln*()
			{
				return p;
			}

		};

		ln *head;
		ln *end;
		ln *cur;
		size_c icur;
		size_c cnt;
        ln pool[sz];


		inline Slist(const T &n):cnt(1)
		{
			cur=pool+sz-1;
			for(size_c i=0; i<sz-2; i++, cur--)
				nodes.push(cur);
			//nodes.pop();
			head= new(--cur) ln(n);
			cur=head;
			end=head;
		};
		inline Slist():head(0),cur(0), end(0),cnt(0){};

		inline void init(const T &n)
		{
			head=new(nodes.pop()) ln(n);
			cur=head;
			end=head;
			cnt=1;
			new(&nodes) Stack<ln*, sz, 0>();
		}

		inline void add(const T &n)
		{
			end->next=new(nodes.pop()) ln(n);
			end->next->back=end;
			end=end->next;
			cnt++;
			cur=end;
			icur=cnt-1;
		}

		inline void addbeg(const T &n)
		{
			cur=new(nodes.pop()) ln(n);
			if(head->next)
				head->next->back=head;
			head->back=cur;
			cnt++;
			cur->next=head;
			head=cur;
			icur=0;
		}

		inline void insert(size_c w, const T &n)
		{
			find(w);
			if(cur==head)
			{
				addbeg(n);
				return;
			}
			ln *ret=cur;
			cur=new(nodes.pop()) ln(n);
			cur->back=ret->back;
			if(ret->back)
			{
				ret->back->next=cur;
				ret->back=cur;
			}
			cur->next=ret;
			cnt++;
		}

		inline void insert(const T &n)
		{
			if(cur==head)
			{
				addbeg(n);
				return;
			}

			ln *ret=cur;
			cur=new(nodes.pop()) ln(n);
			cur->back=ret->back;
			if(ret->back)
			{
				ret->back->next=cur;
				ret->back=cur;
			}
			cur->next=ret;
			cnt++;
		}

#define delete(x)\
 nodes.push(x)
#include "listsame.h"
#undef delete(x)
		inline void clear()
		{
			delete[] pool;
			nodes.~hStack();
		}
		
	};
*/
