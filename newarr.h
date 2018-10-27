static manager m(1024*1024*35);

#ifdef minorard
template <class some, bool nopod=standart> class NewArr {};
#else
template <class some, bool nopod=!is_pod<some>::value > class NewArr {};
#endif

template <class some> class NewArr<some, 1> {
  size_m w;
  size_m free;
  some *u;

  public:

    inline NewArr(const NewArr &copy)
    {
      w = 0;
      size_m l = copy.length();
      if(l)
      {
        asmemal(l);
        free=w-l;
        register size_m k=0;
        for (register some * i = u, *j = &copy[0]; k<l; k++)
          new(i++) some(*j++);
      }
      else
      {
        free=0;
        u=0;
      }
    }

    inline void operator=(const NewArr &s)
    {
      size_m len = s.length();
        some *uu=u;
      for(int i=w-free+1; --i;)
        uu++->~some();
      
    if (len > w)
      asmemal(len - w);
    free = w - len;
    if (len <= w>>1)
     asmemdel();
      register size_m k=0;
      for (register some * i = u, *j = &s[0]; k<len; k++)
          new(i++) some(*j++);
    }

    inline void operator++(int)
    {
      if(!free)
        memal();
      new (u+w-free--)some;
    }

    inline void operator--(int)
    {
      (u+w- ++free)->~some();
      if(free>=w>>1)
        memdel();
    }

    inline void add(const some &ad) 
    {
      if(!free)
        memal();
     new(u+w - free--) some(ad);
    }

    inline void addbeg(const some &ad) 
    {
      if(!free)
        memal();
      trans(w-free--, u, u+1);
     new(u) some(ad);
    }

    inline void addbeg(const some &ad, size_m kolvo) 
    {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free, u, u+kolvo);
      size_m k=0;
      for (register some * i = u; k<kolvo; k++)
        new(i++) some(ad);
     free-=kolvo;
    }

    inline void operator++()
    {
      if(!free)
        memal();
      trans(w-free--, u, u+1);
      new(u) some;
    }

    inline void addbegempty(size_m kolvo) {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free, u, u+kolvo);
        new(u) some[kolvo];
      free -= kolvo;
    }

    inline void operator--()
    {
      u->~some();
      if(++free>=w>>1)
        memdel();
      trans(w-free, u+1, u);
    }

    inline void removebeg(size_m kolvo=1)
    {
      size_m j=0;
      for(some * i = u; j<kolvo; j++)
        (i++)->~some();
      free += kolvo;
      trans(w-free, u+kolvo, u);
      if(free>=w>>1)  
        memdel();
    }    

    inline void add(const some& ad, size_m kolvo) {
      if(free<kolvo)
        memal(kolvo);
      register size_m k = 0;
      for (register some * i = u + (w - free); k<kolvo; k++)
          new(i++) some(ad);
      free -= kolvo;
    }

    inline void addempty(size_m kolvo) {
      if(free<kolvo)
        memal(kolvo);
      register size_m k = 0;
     // for (register some * i = u + (w - free); k<kolvo; k++)
     //   new(i++) some;
        new(u + (w - free)) some[kolvo];
      free -= kolvo;
    }

    inline void operator+=(const NewArr &ad)
    {
      size_m W=ad.length();
      memal(W);
      free-=W;
      for (register some *i = u + w - free - W++ , *j = &ad[0];  --W; )
          new(i++) some(*j++);
    }

    inline void remove(size_m W) {
      (u+W)->~some();
      trans(w-free-W, u + W+1, u + W);
      if(++free >= w>>1)
        memdel ();
    }

    inline void remove(size_m wn, size_m wk) {
      size_m sz=wk-wn+1, j=0;
      for(some * i = u+wn; j<sz; j++)
        (i++)->~some();
      trans(sz,u+wk+1,u+wn);
      free += sz;
      if(free>=w>>1)  
        memdel();
    }

    inline void clear()
    {
      register some *uu=u;
      for(register size_m i=w-free+1, j=0; j<i; j++)
        uu++->~some();
      delete[] (char*)u;
      w=free=0;
      u=0;
    }

    inline void insert(size_m W, const some& ins) {
      if(!free)
        memal();
      trans(w-free-- -W, u+W, u+W+1);
      new(u+W) some (ins);
    }

    inline void insert(size_m W) {
      if(!free)
        memal();
      trans(w-free-- -W, u+W, u+W+1);
      new(u+W) some;
    }

    inline void insert(size_m W, const some& ins, size_m kolvo) {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free -W, u+W, u+W+kolvo);
      free -= kolvo;
      register size_m j=0;
      for (some* i = u+W; j<kolvo; j++)
        new(i++) some (ins);
    }

    inline ~NewArr() {
    if(u)
    {
        register some *uu=u;
        for(register size_m i=w-free, j=0; j<i; j++)
          uu++->~some();
      m.Delete<char>(u, w*sizeof(some));    	
	}
    }


  inline NewArr():w(0), free(0), u(0) {};

    inline void reverse(size_m wn, size_m wk)
    {
      size_m mid=(w-free-1)/2;
      if(mid)
      {
      some m;
      size_m k=0;
        for(some *i=u+wn, *j=u+wk; k<mid; k++, j--, i++)
        {
        m=*j;
        *j=*i;
        *i=m;
        }
      }
    }

    inline void reverse()
    {
      size_m mid=(w-free-1)/2;
      if(mid)
      {
      some m;
      size_m k=0;
        for(some *i=u, *j=u+w-free-1; k<mid; k++, j--, i++)
        {
        m=*j;
        *j=*i;
        *i=m;
        }
      }
    }

    inline some &operator[](size_m W) const {
    return u[W];
    }

    inline int last() const
    {
      return w - free - 1;
    }

    inline NewArr operator+(const NewArr &ad)
    {
      NewArr ret(*this);
      ret += ad;
      return ret;
    }


    inline void cut(size_m wn, size_m wk)
    {
      if (wn)
        remove(0, wn - 1);
      if (wk != w-free-1)
        remove(wk - wn + 1, w - free - 1);
    }

    inline NewArr part(size_m wn, size_m wk)
    {
      NewArr ret;
      size_m len = wk - wn + 1;
      ret.addempty(len++);
      for (some *i = u+wn, *j = &ret[0]; --len;)
        *j++ = *i++;
      return ret;
    }

    inline operator bool()
    {
        return (w-free);
    }

    inline some * operator!()
    {
      return u;
    }

    inline size_m length() const
    {
      return w - free;
    }

    inline some* begin()
    {
      return u;
    }

    inline some* end()
    {
      return u+(w-free);
    }

private:

  inline void trans(size_m len, some *o, some *k)
  {
    #if !custom
    memcpy(k,o,len*sizeof(some));
    #else
      size_m**oo=(size_m**)o, **kk=(size_m**)k;
      register size_m a=len*sizeof(some)/sizeof(size_m*);
      if(a)
      {
        for (register size_m i=0; i<a; i++)
          *kk++ = *oo++;
      }
      a=len*sizeof(some)%sizeof(size_m*);
      if(a)
    {
    char *kkk=(char*)kk, *ooo=(char*)oo;
        for(register size_m i=0; i<a; i++)
          *kkk++=*ooo++;
      }
    #endif
  }

    inline void memal(size_m skolko=1)
  { //????????? ??????
    size_m wold = w, wk = w - free + skolko; //????????? ?????? ??????
  if(!w)
      {w=1; free=0; u=0;}
  
  while (w < wk)w<<=1;
    if (wold != w)
      {
        free += w - wold;
        if(wold)
          u = m.Realloc<some>(u, wold, w);
        else
#ifdef minorard
        	u = m.New<some>(w, 0);
#else
			u = m.New<some, 0>(w);
#endif  
      }
    }

    inline void memdel()
    { 
      size_m wold = w, z = w - free; //?????? ??????
      //?????? ???? ?????? ?????? ??? ????? ???????? ???????
    while (z <= w>>1 && w)w>>=1;
      if (w != wold)
      {
        free += w - wold;
#ifdef minorard
        if(!w){ m.Delete<some>(u, wold, 0); free=0; u=0;}
#else
		if(!w){ m.Delete<some, 0>(u, wold); free=0; u=0;}
#endif  
      	else
        u = m.Realloc<some>(u, wold, w);
      }
    }

    inline void asmemal(size_m skolko=1)
  { //????????? ??????
    size_m wold = w, wk = w + skolko; //????????? ?????? ??????
  if(!w)
      {w=1; free=0; u=0;}
  while (w < wk)w<<=1;
    if (wold != w)
      {
        free += w - wold;
        if(wold)
#ifdef minorard
        	u = m.Realloc<some>(u, wold, w, 0);
#else
			u = m.Realloc<some, 0>(u, wold, w);
#endif
        else
        	u = (some*)m.New<char>(w*sizeof(some));
      }
    }

    inline void asmemdel()
    {
      size_m wold = w, z = w - free; //?????? ??????
      //?????? ???? ?????? ?????? ??? ????? ???????? ???????
      while (z <= w>>1 && w)w>>=1;
      if (w != wold)
      {
        free += w - wold;
#ifdef minorard
        if(!w){ m.Delete<some>(u, wold, 0); free=0; u=0;}
        else
        u = m.Realloc<some>(u, wold, w, 0);
#else
		if(!w){ m.Delete<some, 0>(u, wold, 0); free=0; u=0;}
		else
		u = m.Realloc<some, 0>(u, wold, w);
#endif  
      }
    }
public:





        inline void operator*=(float skolko)
      {
       if (w - free > 0) {
      size_m wk, wn = w - free;
      wk=wn;
        skolko*=wk;
        skolko-=wk;
        for (register size_m j = 1, i=0; j <= skolko; j++, i++) {
          if(wk<j)
          {
            wk+=wn;
              i=0;
          }
            add(u[i]);}

          }
        }

    inline void operator>>(some &kuda)
    {
      kuda = u[w - free - 1];
    }

    inline void operator<<(some &what)
    {
      u[w - free - 1] = what;
    }

        inline NewArr operator*(float skolko)
      {
        NewArr n(*this);
          n*=skolko;
          return n;
      }

        inline void operator/=(float skolko)
        {
          float wn = w - free;
          float wk = wn / skolko;
          remove(wk, wn - 1);
        }

      inline NewArr operator/(float skolko)
      {
        NewArr n(*this);
        n/=skolko;
        return n;
      }

        inline void operator%=(float skolko)
        {
          float wn = w - free;
          float wk = wn / skolko;
          remove(wk - wk, wn - 1 - wk);
        }

        inline NewArr operator%(float skolko)
        {
          NewArr n(*this);
          n%=skolko;
          return n;
        }

        inline size_m find(some what, size_m wn, size_m wk)
        {
          for (register size_m i = wn; i <= wk; i++)
            if (u[i] == what)return i;
          return -1;
        }

        inline int find(some what)
        {
          size_m wn = 0, wk = w - free - 1;
          for (register size_m i = wn; i <= wk; i++)
            if (u[i] == what)return i;
          return -1;
        }

      inline void operator-=(NewArr &what)
      {
      size_m wn, wk = 0, W = what.length();
        wn = find(what[0]);
        if (wn > -1) {
        for (register size_m i = 1; i < W ; ++i)
        {
          if (wk == -1)break;
          wk = find(wk+1, W-1,what[i]);
          if (wk == -1)break;
        }
        }
        if (wk != -1)
        remove(wn, wk);
      }

      inline NewArr operator-(NewArr &what)
      {
        NewArr ret(*this);
        ret-=what;
        return ret;
      }

        inline bool operator<(NewArr &cmp)
        {
        if (cmp.length() > w - free)
            return true;
          else
            return false;
        }
        inline bool operator>(NewArr &cmp)
        {
        if (cmp.length() < w - free)
            return true;
          else
            return false;
        }
        inline bool operator<=(NewArr &cmp)
        {
        if (cmp.length() >= w - free)
            return true;
          else
            return false;
        }
        inline bool operator>=(NewArr &cmp)
        {
          if (cmp.length() <= w - free)
            return true;
          else
            return false;
        }
 

};

template <class some> class NewArr<some, 0> {
  size_m w;
  size_m free;
  some *u;

  public:

    inline NewArr(const NewArr &copy)
    {
      w = 0;
      size_m l = copy.length();
      if(l)
      {
        asmemal(l);
        free=w-l;
        trans(l, &copy[0], u);
      }
      else
      {
        free=0;
        u=0;
      }
    }

    inline void operator=(const NewArr &s)
    {
      size_m len = s.length();
    if (len > w)
      asmemal(len - w);
    free = w - len;
    if (len <= w>>1)
     asmemdel();
        trans(len, &s[0], u);
    }

    inline void operator++(int)
    {
  	  if(!free)
  		  memal();
  		free--;
    }

    inline void operator--(int)
    {
      if(++free>=w>>1)
        memdel();
    }

    inline void add(const some &ad) 
    {
      if(!free)
        memal();
      u[w-free--]=ad;
    }

    inline void add(const some& ad, size_m kolvo) {
      if(free<kolvo)
        memal(kolvo);
      size_m k = kolvo+1;
      for (register some * i = u + (w - free); --k; )
        *i++ =ad;
      free -= kolvo;
    }

    inline void addempty(size_m kolvo) {
      if(free<kolvo)
        memal(kolvo);
      free -= kolvo;
    }


    inline void addbeg(const some &ad) 
    {
      if(!free)
        memal();
      trans(w-free--, u, u+1);
      u[0]=ad;
    }

    inline void addbeg(const some &ad, size_m kolvo) 
    {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free, u, u+kolvo);
      size_m k=0;
      for (register some * i = u; k<kolvo; k++)
        *i++=ad;
     free-=kolvo;
    }

    inline void operator++()
    {
      if(!free)
        memal();
      trans(w-free--, u, u+1);
      new(u) some();
    }

    inline void addbegempty(size_m kolvo) {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free, u, u+kolvo);
      register size_m k = 0;
      //for (register some * i = u + (w - free); k<kolvo; k++)
        //new(i++) some;
      new(u) some[kolvo];
      free -= kolvo;
    }

    inline void operator--()
    {
      if(++free>=w>>1)
        memdel();
      trans(w-free, u+1, u);
    }

    inline void removebeg(size_m kolvo=1)
    {
      free += kolvo;
      trans(w-free, u+kolvo, u);
      if(free>=w>>1)  
        memdel();
    }   

    inline void operator+=(const NewArr &ad)
    {
      size_m W=ad.length();
      memal(W);
      free-=W;
	  trans(W, &ad[0], u + w - free - W);
	}

    inline void remove(size_m W) {
      trans(w-free-W, u + W+1, u + W);
      if(++free >= w>>1)
        memdel ();
    }

    inline void remove(size_m wn, size_m wk) {
    size_m sz=wk-wn+1;
    trans(sz, u+wk+1, u+wn);
      free += sz;  
      memdel();
    }

    inline void clear()
    {
      delete[] (char*)u;
      w=free=0;
      u=0;
    }

    inline void insert(size_m W, const some& ins) {
      if(!free)
        memal();
      trans(w-free-- -W, u+W, u+W+1);
      u[W]=ins;
    }

    inline void insert(size_m W) {
      if(!free)
        memal();
      trans(w-free-- -W, u+W, u+W+1);
    }

    inline void insert(size_m W, const some& ins, size_m kolvo) {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free-- -W, u+W, u+W+kolvo);
      free -= kolvo++;
      for (some* i = u+W; --kolvo;)
        *i++ = ins;
    }


    inline ~NewArr() {
	if(u)
      m.Delete<char>(u, w*sizeof(some));
    }


  inline NewArr():w(0), free(0), u(0) {};

    inline void reverse(size_m wn, size_m wk)
    {
      size_m mid=(w-free-1)/2;
      if(mid)
      {
      some m;
      size_m k=0;
        for(some *i=u+wn, *j=u+wk; k<mid; k++, j--, i++)
        {
        m=*j;
        *j=*i;
        *i=m;
        }
      }
    }

    inline void reverse()
    {
      size_m mid=(w-free-1)/2;
      if(mid)
      {
      some m;
      size_m k=0;
        for(some *i=u, *j=u+w-free-1; k<mid; k++, j--, i++)
        {
        m=*j;
        *j=*i;
        *i=m;
        }
      }
    }

    inline some &operator[](size_m W) const {
    return u[W];
    }

    inline int last() const
    {
      return w - free - 1;
    }

    inline NewArr operator+(const NewArr &ad)
    {
      NewArr ret(*this);
      ret += ad;
      return ret;
    }


    inline void cut(size_m wn, size_m wk)
    {
      if (wn)
        remove(0, wn - 1);
      if (wk != w-free-1)
        remove(wk - wn + 1, w - free - 1);
    }

    inline NewArr part(size_m wn, size_m wk)
    {
      NewArr ret;
      size_m len = wk - wn + 1;
      ret.addempty(len++);
      for (some *i = u+wn, *j = &ret[0]; --len;)
        *j++ = *i++;
      return ret;
    }

    inline operator bool()
    {
        return (w-free);
    }

    inline some * operator!()
    {
      return u;
    }

    inline size_m length() const
    {
      return w - free;
    }

    inline some* begin()
    {
      return u;
    }

    inline some* end()
    {
      return u+(w-free);
    }

private:

  inline void trans(size_m len, some *o, some *k)
  {
    #if !custom
    memcpy(k,o,len*sizeof(some));
    #else
      size_m**oo=(size_m**)o, **kk=(size_m**)k;
      register size_m a=len*sizeof(some)/sizeof(size_m*);
      if(a)
      {
        for (register size_m i=0; i<a; i++)
          *kk++ = *oo++;
      }
      a=len*sizeof(some)%sizeof(size_m*);
      if(a)
    {
    char *kkk=(char*)kk, *ooo=(char*)oo;
        for(register size_m i=0; i<a; i++)
          *kkk++=*ooo++;
      }
    #endif
  }

    inline void memal(size_m skolko=1)
  { //????????? ??????
    size_m wold = w, wk = w - free + skolko; //????????? ?????? ??????
  if(!w)
      {w=1; free=0; u=0;}
  
  while (w < wk)w<<=1;
    if (wold != w)
      {
        free += w - wold;
        if(wold)
          u = m.Realloc<some>(u, wold, w);
        else
#ifdef minorard
        	u = m.New<some>(w, 0);
#else
			u = m.New<some, 0>(w);
#endif  
      }
    }

    inline void memdel()
    { 
      size_m wold = w, z = w - free; //?????? ??????
      //?????? ???? ?????? ?????? ??? ????? ???????? ???????
    while (z <= w>>1 && w)w>>=1;
      if (w != wold)
      {
        free += w - wold;
#ifdef minorard
        if(!w){ m.Delete<some>(u, wold, 0); free=0; u=0;}
#else
		if(!w){ m.Delete<some, 0>(u, wold); free=0; u=0;}
#endif  
      	else
        u = m.Realloc<some>(u, wold, w);
      }
    }

    inline void asmemal(size_m skolko=1)
  { //????????? ??????
    size_m wold = w, wk = w + skolko; //????????? ?????? ??????
  if(!w)
      {w=1; free=0; u=0;}
  while (w < wk)w<<=1;
    if (wold != w)
      {
        free += w - wold;
        if(wold)
#ifdef minorard
        	u = m.Realloc<some>(u, wold, w, 0);
#else
			u = m.Realloc<some, 0>(u, wold, w);
#endif
        else
        	u = (some*)m.New<char>(w*sizeof(some));
      }
    }

    inline void asmemdel()
    {
      size_m wold = w, z = w - free; //?????? ??????
      //?????? ???? ?????? ?????? ??? ????? ???????? ???????
      while (z <= w>>1 && w)w>>=1;
      if (w != wold)
      {
        free += w - wold;
#ifdef minorard
        if(!w){ m.Delete<some>(u, wold, 0); free=0; u=0;}
        else
        u = m.Realloc<some>(u, wold, w, 0);
#else
		if(!w){ m.Delete<some, 0>(u, wold, 0); free=0; u=0;}
		else
		u = m.Realloc<some, 0>(u, wold, w);
#endif  
      }
    }
public:





        inline void operator*=(float skolko)
      {
       if (w - free > 0) {
      size_m wk, wn = w - free;
      wk=wn;
        skolko*=wk;
        skolko-=wk;
        for (register size_m j = 1, i=0; j <= skolko; j++, i++) {
          if(wk<j)
          {
            wk+=wn;
              i=0;
          }
            add(u[i]);}

          }
        }

    inline void operator>>(some &kuda)
    {
      kuda = u[w - free - 1];
    }

    inline void operator<<(some &what)
    {
      u[w - free - 1] = what;
    }

        inline NewArr operator*(float skolko)
      {
        NewArr n(*this);
          n*=skolko;
          return n;
      }

        inline void operator/=(float skolko)
        {
          float wn = w - free;
          float wk = wn / skolko;
          remove(wk, wn - 1);
        }

      inline NewArr operator/(float skolko)
      {
        NewArr n(*this);
        n/=skolko;
        return n;
      }

        inline void operator%=(float skolko)
        {
          float wn = w - free;
          float wk = wn / skolko;
          remove(wk - wk, wn - 1 - wk);
        }

        inline NewArr operator%(float skolko)
        {
          NewArr n(*this);
          n%=skolko;
          return n;
        }

        inline size_m find(some what, size_m wn, size_m wk)
        {
          for (register size_m i = wn; i <= wk; i++)
            if (u[i] == what)return i;
          return -1;
        }

        inline int find(some what)
        {
          size_m wn = 0, wk = w - free - 1;
          for (register size_m i = wn; i <= wk; i++)
            if (u[i] == what)return i;
          return -1;
        }

      inline void operator-=(NewArr &what)
      {
      size_m wn, wk = 0, W = what.length();
        wn = find(what[0]);
        if (wn > -1) {
        for (register size_m i = 1; i < W ; ++i)
        {
          if (wk == -1)break;
          wk = find(wk+1, W-1,what[i]);
          if (wk == -1)break;
        }
        }
        if (wk != -1)
        remove(wn, wk);
      }

      inline NewArr operator-(NewArr &what)
      {
        NewArr ret(*this);
        ret-=what;
        return ret;
      }

        inline bool operator<(NewArr &cmp)
        {
        if (cmp.length() > w - free)
            return true;
          else
            return false;
        }
        inline bool operator>(NewArr &cmp)
        {
        if (cmp.length() < w - free)
            return true;
          else
            return false;
        }
        inline bool operator<=(NewArr &cmp)
        {
        if (cmp.length() >= w - free)
            return true;
          else
            return false;
        }
        inline bool operator>=(NewArr &cmp)
        {
          if (cmp.length() <= w - free)
            return true;
          else
            return false;
        }
 

};

#define newarr NewArr