class DynString {

  size_x w;
  size_x free;
  char *u;

    inline void trans(unsigned short len, char *o, char *k)
    {
      #if !custom
      memcpy(k,o,len);
      #else
    register unsigned short a=len/sizeof(unsigned int*);
    unsigned int**oo=(unsigned int**)o, **kk=(unsigned int**)k;
      if(a)
      {
        for (register unsigned short i=0; i<a; i++)
          *kk++ = *oo++;
      }
      a=len%sizeof(unsigned int*);
      if(a)
      {
        k=(char*)kk, o=(char*)oo;
        for(register unsigned short i=0; i<a; i++)
          *k++=*o++;
      }
      #endif
    }

    inline void memal(size_x skolko=1)
  { //выделение памяти
    size_x wold = w, wk = w - free + skolko; //запомнить старый размер
  if(!w)
      {w=1; free=0; u=0;} 
    while (w < wk)w<<=1;
    if (wold != w)
      {
        size_x z = wold - free;
        free += w - wold;
        char *t = new char[w + 1];
        if(u)
          trans(z, u, t);
        delete [] u;
    u = t;
      }
    }

    inline void memdel()
    {
    size_x wold = w, z = w - free; //старый размер
      //делать пока занято меньше или равно половина размера
    while (z <= w>>1 && w>>1)w>>=1; 
      if (w != wold) {
    free += w - wold;
        char * t = new char[w + 1];
        z = w - free;
        trans(z, u, t);
        delete [] u;
        u = t;
    }
    if(!z){delete []u; w=free=0; u=0;}
  }

    inline void asmemal(size_x skolko=1)
  { //выделение памяти
      size_x wold = w, wk = w + skolko; //запомнить старый размер
  if(!w)
      {w=1; free=0; u=0;}
      while (w < wk)w<<=1;
      if (wold != w) {
        char *t = new char[w + 1];
        delete [] u;
        u = t;
      }
    }

    inline void asmemdel()
    {
      size_x wold = w, z = w - free; //старый размер
      //делать пока занято меньше или равно половина размера
    while (z <= w>>1 && w>>1)w>>=1;
      if (w != wold) {
        free += w - wold;
        char * t = new char[w + 1];
        delete [] u;
        u = t;
      }
    if(!z){delete []u; w=free=0; u=0;}
    }

  public:

  inline DynString():w(0), free(0), u(0) {};


    inline DynString(char *s)
    {
      w = 0;
      size_x len = 0; for (; s[len]; len++);
      if(len)
      {
        w=2;
        while (w < len) w<<=1;
        free = w - len;
        u = new char[w + 1];
        trans(len, s, u);
      }
      else
      {
        free=0;
        u=0;
      }
    }
#ifdef arduino
  inline explicit  operator char*() const
#else 
  inline operator char*() const
#endif
  {
      u[w - free] = '\0';
      return u;
  }

  inline DynString(char ch) {
    w = 2;
    u = new char[w + 1];
    free = 1;
    u[0] = ch;
  };

  inline DynString(const DynString &copy)
  {
    w = 0;
    size_x l = copy.length();
    if(l)
    {
      asmemal(l);
      free=w-l;
      trans(l, !copy, u);
    }
    else
    {
      free=0;
      u=0;
    }
   }

  inline void operator=(const DynString &s)
  {
	  size_x len = s.length();
	  if (len > w)
		asmemal(len - w);
      free = w - len;
      if (len <= w>>1)
        asmemdel();
          trans(len, !s, u);//вернуть по индексу с конца
  }

  inline void operator=(char * s)
  {
    size_x len = 0; for (; s[len]; len++);
    if (len > w)
      asmemal(len - w);
    free = w - len;
    if (len <= w>>1)
      asmemdel();
    trans(len, s, u);
  }


  inline void operator=(char s)
  {
    if(w!=2)
    {
    delete []u;
    u=new char [2];
    w=2;
    free=1;
    }
    u[0]=s;
  }

    inline void re() //пересчитать размеры строки
    {
    size_x len = 0; for (; u[len]; len++);
      if(len>w)
        memal(len-w+free);
      if(len<w>>1)
      {
        free=w-len;
        memdel();
      }
    }

    inline void addempty(unsigned int kolvo) {
    if(free<kolvo)
      memal(kolvo);
      free -= kolvo;
    }

    inline void addbeg(char ad) 
    {
      if(!free)
        memal();
      trans(w-free--, u, u+1);
      u[0]=ad;
    }

    inline void addbeg(char ad, unsigned int kolvo) 
    {
      if(free<kolvo)
        memal(kolvo);
	  trans(w-free, u, u+kolvo);
	  unsigned int k=0;
      for (register char * i = u; k<kolvo; k++)
        *i++=ad;
     free-=kolvo;
    }

    inline void operator++()
    {
      if(!free)
        memal();
      trans(w-free--, u, u+1);
      new(u) char();
    }

    inline void addbegempty(unsigned int kolvo) {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free, u, u+kolvo);
        new(u) char[kolvo];
      free -= kolvo;
    }

    inline void operator--()
    {
      if(++free>=w>>1)
        memdel();
      trans(w-free, u+1, u);
    }

    inline void removebeg(unsigned int kolvo)
    {
      free += kolvo;
      trans(w-free, u+kolvo, u);
      if(free>=w>>1)  
        memdel();
    }   

    inline void clear()
    {
      w = free = 0;
      delete []u;
      u=0;
    }

	inline DynString part(size_x wn, size_x wk)
    {
      DynString ret;
      size_x len = wk - wn + 1;
      ret.addempty(len);
        trans(len, u+wn, !ret);
      return ret;
    }

    inline void cut(size_x wn, size_x wk)
    {
      if (wn != 0)
        remove(0, wn - 1);
      if (wk != w - free - 1)
        remove(wk-wn+1, w - free - 1); //потому что уже удаляли левую часть, всё сместилось
    }

    inline void add(char ad) {
      if(!free)
        memal();
      u[w - free--] = ad;
    }

    inline void add(char ad, size_x kolvo) {
      if(free<kolvo)
        memal(kolvo);
      for (register size_x i = 0; i < kolvo; i++) {
        u[w - free--] =  ad;
      }
    }

    inline void add(char * ad, size_x kolvo) {
    size_x len = 0; for (; ad[len]; len++);
    if(free<len*kolvo)
      memal((len * kolvo)-free);
      for (size_x j = 0; j < kolvo; j++) {
        for (register size_x i = 0; ad[i]; i++)
        {
          u[w - free--] = ad[i];
        }
      }
    }

    inline void add(DynString &ad, size_x kolvo)
    {
      size_x W = ad.length();
      memal(W * kolvo);
      for (size_x j = 0; j < kolvo; j++) {
        for (register size_x i = 0; i < W; i++)
        {
          u[w - free--] = ad[i];
        }
      }
    }

    //сделать удаление строки первой попавшейся


    inline void remove(size_x W) { 
      trans(w-free-W, u+W, u+W+1);
      if(++free>=w>>1)
        memdel ();
    }

    inline void copyb(char *str, size_x len)
    {
      if (len > w)
        asmemal(len - w);
      free = w - len;
      if (len <= w>>1)
        asmemdel();
      trans(len, str, u);
    }

    inline void remove(size_x wn, size_x wk) {
		size_x sz=w-1-(wk-wn);
		trans(sz,u+wk+1,u+wn);
	  free += wk - wn + 1;
      memdel();
    }

    inline void insert(size_x W, char ins) {
      if(!free)
        memal();
      trans(w-free-- -W, u+W, u+W+1);
      u[W]=ins;
    }

    inline void insert(size_x W, char ins, size_x kolvo) {
      if(free<kolvo)
		memal(kolvo); //не kolvo-free, ибо всё в memal предусмотрено
	  trans(w-free -W, u+W, u+W+kolvo);
      free -= kolvo++;
	  for (char* i = u+W; --kolvo;)
		  *i++=ins;
	}

    inline void insert(size_x W, const DynString& ins) {
      size_x kolvo=ins.length();
      if(free<kolvo)
    memal(kolvo); //не kolvo-free, ибо всё в memal предусмотрено
    trans(w-free -W, u+W, u+W+kolvo);
      free -= kolvo++;
    for (char* i = u+W, *j=!ins; --kolvo;)
      *i++=*j++;
  }
  
    inline void insert(size_x W, char* ins) {
      size_x kolvo=0;
	  for(;ins[kolvo]; kolvo++);
      if(free<kolvo)
    memal(kolvo); //не kolvo-free, ибо всё в memal предусмотрено
    trans(w-free -W, u+W, u+W+kolvo);
      free -= kolvo++;
    for (char* i = u+W, *j=ins; --kolvo;)
      *i++=*j++;
  }
	inline void reverse(size_x wn, size_x wk)
	{
	  size_x mid=(wk-wn)/2;
	  if(mid)
	  {
		++mid;
		char m;
		  for(char *i=u+wn, *j=u+wk; --mid;)
		  {
			m=*j;
			*j--=*i;
			*i++=m;
		  }
	  }   
	}

    inline void reverse()
    {
	  size_x mid=(w-free-1)/2;
	  if(mid)
	  {
		++mid;
		char m;
		  for(char *i=u, *j=u+w-free-1; --mid;)
		  {
			m=*j;
			*j--=*i;
			*i++=m;
		  }
	  }
    }


    inline char& operator[](size_x W) 
    {
#ifndef safe
      return u[W];
#else
      if(W>0 && W<w-free)
      return u[W];
      else
      {
        if(W>w || W<0)
          throw("index out of string's memory in file" str(__FILE__) "on line "str( __LINE__) str(\n));
        else if(W+1>w-free)
          throw("index out of string's range in file" str(__FILE__) "on line "str( __LINE__) str(\n));
        else
          return u[W];
      }
#endif
    }

    inline char operator()(size_x W) const
	{
#ifndef safe
      return u[W];
#else
      if(W>0 && W<w-free)
      return u[W];
      else
      {
        if(W>w || W<0)
          throw("index out of string's memory in file" str(__FILE__) "on line "str( __LINE__) str(\n));
        else if(W+1>w-free)
          throw("index out of string's range in file" str(__FILE__) "on line "str( __LINE__) str(\n));
        else
          return u[W];
      }
#endif
    }

    inline int last() const
    {
#ifndef safe      
      return w - free - 1;
#else
      if(w!=free)
        return w-free-1;
      else
        throw("string have'nt got last element");
#endif
    }

  inline DynString operator+(char *ad)
  {
    DynString n(*this);
    n += ad;
    return n;
  }

	inline DynString operator+(const DynString &ad)
    {
      DynString n(*this);
      n += ad;
      return n;
    }

    inline void operator+=(const DynString &ad)
    {
      size_x W = ad.length();
      memal(W);
      trans(W, !ad, u+(w-free));
      free -= W;
    }

    inline void operator+=(char * ad)
    {
      size_x len = 0; for (; ad[len]; len++);
      memal(len);
      trans(len, ad, u+(w-free));
      free -= len;
    }

    inline bool operator!=(const DynString &cmp) const
    {
      return !(*(this)==cmp);
    }

  inline bool operator==(const DynString &cmp) const
    {
      size_x len = cmp.length();
      if (len == w - free)
      {
        unsigned int**oo=(unsigned int**)u, **kk=(unsigned int**)!cmp;
        register size_x a=len/sizeof(unsigned int*);
        if(a)
        {
          for (a++; --a ; )
            if (*oo++ != *kk++)
              return false;
        }
        a=len%sizeof(unsigned int*);
        if(a)
        {
          char *k=(char*)kk, *o=(char*)oo;
          for(a++; --a; )
            if (*o++ != *k++)
              return false;
        } 
          return true;
      }
      else
        return false;
    }

       inline bool operator<(const DynString &cmp) const
        {
          if (cmp.length() > w - free)
            return true;
          else
            return false;
        }
        inline bool operator>(const DynString &cmp) const
        {
          if (cmp.length() < w - free)
            return true;
          else
            return false;
        }
        inline bool operator<=(const DynString &cmp) const
        {
          if (cmp.length() >= w - free)
            return true;
          else
            return false;
        }
        inline bool operator>=(const DynString &cmp) const
        {
          if (cmp.length() <= w - free)
            return true;
          else
            return false;
        }

    inline bool operator==(char *cmp)
    {
    size_x len = 0; for (; cmp[len]; len++);
      if (len == w - free)
      {
        unsigned int**oo=(unsigned int**)u, **kk=(unsigned int**)!cmp;
        register size_x a=len/sizeof(unsigned int*);
        if(a)
      {
        for (a++; --a ; )
          if (*oo++ != *kk++)
            return false;
      }
      a=len%sizeof(unsigned int*);
      if(a)
      {
        char *k=(char*)kk, *o=(char*)oo;
        for(a++; --a; )
          if (*o++ != *k++)
            return false;
      } 
        return true;
      }
      else
        return false;
    }

    inline bool operator!=(char *cmp)
    {
      return !(*(this)==cmp);
    }

    inline char * operator!() const
    {
      u[w - free] = '\0';
      return u;
    }


    inline size_x length() const
    {
      return w - free;
    }

    inline void operator--(int)
    {
      if(++free>=w>>1)
        memdel ();
    }

    inline void operator++(int)
    {
      if(!free)
        memal();
      free--;
    }

    inline ~DynString() 
    {
      delete []u;
    }

  operator size_m() const
  {
    size_m hash = 0, ppow=1;
    for(size_x i=0, j=w-free; i<j; i++)
    {
      hash +=((*this)(i)-'a')*ppow;
      ppow*=31;
    }
    return hash;
  } 

};

#define dynstr DynString

//??????? findall() - ????????? ??? ????? ?????
//????? insert ?????
//???? ?????????? ?????????? ???????-= ????????????
//??????????? ????? reverse ?? ???????
//????? | ?& ?????? ?? ???
//??????, ???? ?????/???? ? ????????adbeg
//tohigher tolower ?? ??
//???? ?????? << ?>>  ??????? ??? ?????? ? ???
// ???? (?????????? ????? ????? ???, ????)
//???? ???????? ?? ??? (?2 ???????

#ifdef iostr
ostream& operator<<(ostream& stream, const dynstr& d)
{
    cout<<(char*)d;
}
#endif

   /*


        inline void operator*=(float skolko)
      {
       if (w - free > 0) {
      size_x wk, wn = w - free;
      wk=wn;
        skolko*=wk;
        skolko-=wk;
        for (register size_x j = 1, i=0; j <= skolko; j++, i++) {
          if(wk<j)
          {
            wk+=wn;
              i=0;
          }
            add(u[i]);}

          }
        }

      inline DynString operator*(float skolko)
      {
        DynString n(*this);
          n*=skolko;
          return n;
      }

      inline void operator/=(float skolko)
        {
          float wn = w - free;
         float wk = wn / skolko;
          remove(wk, wn - 1);
        }

      inline DynString operator/(float skolko)
      {
        DynString n(*this);
        n/=skolko;
        return n;
      }

        inline void operator%=(float skolko)
        {
          float wn = w - free;
          float wk = wn / skolko;
          remove(0, wn - 1 - wk);
        }

        inline DynString operator%(float skolko)
        {
        DynString n(*this);
          n%=skolko;
          return n;
        }


        inline char * operator+(char ad)
        {
          DynString n(*this);
          n += ad;
          return !n;
        }

        inline void readress()
        {
        char * t = new char[w+1];
        for (register size_x i = 0; i < w - free; i++)
          t[i] = u[i];
        delete [] u;
        u = t;
        }


        inline void insert(size_x W, char * ins) {
          memal();
          for (register size_x i = w - free - 1; i >= W; i--)
          {
            u[i + 1] = u[i];
          }
          u[W] = *ins;
          free--;
        }   //доработать под строки

        inline void insert(size_x W, char * ins, size_x kolvo) {
          memal(kolvo);
          for (register size_x i = w - free - 1; i >= W; i--)
          {
            u[i + kolvo] = u[i];
          }
          free -= kolvo;
          for (register size_x i = W; i < W + kolvo; i++)
          {
            u[i] = *ins;
          }
          //доработать под строки
        }




        inline void operator-=(DynString &what)
        {
          size_x wn, wk = 0, W = what.length();
          wn = find(what[0]);
          size_x wkl = wn;
          if (wn > -1) {

            for (register size_x i = 1; i < W ; ++i)
            {
              if (wk == -1)break;
              wk = find(what[i]);
              if (wk == wkl + 1)
                wkl = wk;
              else
                break;
            }
          }

          if (wk != -1 && wk == wkl)
            remove(wn, wk);
        }

        inline void operator-=(char * what)
        {
          size_x len;
          for (len = 0; u[len]; len++) {}
          size_x wn, wk = 0, W = len + 1;
          wn = find(what[0]);
          size_x wkl = wn;
          if (wn > -1) {

            for (register size_x i = 1; i < W ; ++i)
            {
              if (wk == -1)break;
              wk = find(what[i]);
              if (wk == wkl + 1)
                wkl = wk;
              else
                break;
            }
          }
          if (wk != -1 && wk == wkl)
            remove(wn, wk);
        }

        inline void operator-=(char what)
        {
          remove(find(what));
        }

        inline void operator-(size_x W)
        {
            for (register size_x i = W; i < w - free; i++)
              u[i] = u[i + 1];
            free++;
            memdel ();
        }

        inline char * operator-(char what)
        { DynString n;
          remove(find(what));
          return !n;
        }

        inline char * operator-(char * what)
        { DynString n;
          size_x wn, wk = 0;
          wn = n.find(what[0]);
          if (wn > -1) {
            for (register size_x i = 1; what[i] ; ++i)
            {
              if (wk == -1)break;
              wk = n.find(what[i]);
            }
          }
          if (wk != -1)
            n.remove(wn, wk);
          return !n;
        }

        inline char * operator-(DynString &what)
        { DynString n(*this);
          size_x wn, wk = 0, W = what.length();
          wn = n.find(what[0]);
          size_x wkl = wn;
          if (wn > -1) {

            for (register size_x i = 1; i < W ; ++i)
            {
              if (wk == -1)break;
              wk = n.find(what[i]);
              if (wk == wkl + 1)
                wkl = wk;
              else
                break;
            }
          }
          if (wk != -1 && wk == wkl)
            n.remove(wn, wk);
          return !n;
        }

        inline size_x find(char what, size_x wn, size_x wk)
      { if (wn > -1 && wk < w - free) {
            for (register size_x i = wn; i <= wk; i++)
              if (u[i] == what)return i;
          }
          return -1;
        }

        inline size_x find(char what)
        {
          size_x wn = 0, wk = w - free - 1;
          for (register size_x i = wn; i <= wk; i++)
            if (u[i] == what)return i;
          return -1;
        }

        inline size_x find(char * what, size_x wn, size_x wk)
      { if (wn > -1 && wk < w - free) {
            wn = find(what[0], wn, wk);
            size_x wkl = wn;
            if (wn > -1) {
              for (register size_x i = 1; what[i] ; ++i)
              {
                if (wk == -1)break;
                wk = find(what[i]);
              }
            } else {
              return wn;
            }

            if (wk != -1 && wk == wkl)
              return wn;
          }
          return -2;
        }

        inline size_x find(char * what)
        {
          size_x len = 0; for (len; what[len]; ++len) {}
          size_x wn, wk = 0, W = len;
          wn = find(what[0]);
          size_x wkl = wn;
          if (wn > -1) {

            for (register size_x i = 1; i < W ; ++i)
            {
              if (wk == -1)break;
              wk = find(what[i]);
              if (wk == wkl + 1)
                wkl = wk;
              else
                break;
            }
          } else {
            return wn;
          }
          if (wk != -1 && wk == wkl)
        return wn;
      }
    */
