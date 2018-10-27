
  inline DynArr():w(0), free(0), u(0) {};

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
#ifndef safe
      return u[W];
#else
      if(W>0 && W<w-free)
        return u[W];
      else
      {
        if(W>w || W<0)
          throw("index out of array's memory in file" str(__FILE__) "on line "str( __LINE__) str(\n));
        else if(W+1>w-free)
          throw("index out of array's range in file" str(__FILE__) "on line "str( __LINE__) str(\n));
        else
          return u[W];
      }
#endif
    }

    inline some operator()(size_x W) {
#ifndef safe
      return u[W];
#else
      if(W>0 && W<w-free)
        return u[W];
      else
      {
        if(W>w || W<0)
          throw("index out of array's memory in file" str(__FILE__) "on line "str( __LINE__) str(\n));
        else if(W+1>w-free)
          throw("index out of range in file" str(__FILE__) "on line "str( __LINE__) str(\n));
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
        throw("array have'nt got last element");
#endif
    }

    inline DynArr operator+(const DynArr &ad)
    {
      DynArr ret(*this);
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

    inline DynArr part(size_m wn, size_m wk)
    {
      DynArr ret;
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
      if(w)
        return u;
    }

    inline some* end()
    {
      if(w)
        return u+(w-free);
    }

    inline some& peek()
    {
      if(w)
        return u[w-free-1];
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
  { //выделение памяти
    size_m wold = w, wk = w - free + skolko; //запомнить старый размер
  if(!w)
      {w=1; free=0; u=0;}
  
  while (w < wk)w<<=1;
    if (wold != w)
      {
        free += w - wold;
        some *t = (some*)new char[w*sizeof(some)];
        if(u)
          trans(wold, u, t);
        delete [] (char*)u;
        u = t;
      }
    }

    inline void memdel()
    {
      size_m wold = w, z = w - free; //старый размер
      //делать пока занято меньше или равно половина размера
    while (z <= w>>1 && w)w>>=1;
      if (w != wold)
      {
        free += w - wold;
        if(!w){ delete [](char*)u; free=0; u=0;}
        else
        {
          some *t = (some*)new char[w*sizeof(some)];
          trans(w, u, t);
          delete [] (char*)u;
          u = t;
        }
      }
      
    }

    inline void asmemal(size_m skolko=1)
  { //выделение памяти
    size_m wold = w, wk = w + skolko; //запомнить старый размер
  if(!w)
      {w=1; free=0; u=0;}
  while (w < wk)w<<=1;
    if (wold != w)
      {
        free += w - wold;
        some *t = (some*)new char[w*sizeof(some)];
        if(u)
        {
          delete [] (char*)u;         
        }
        u = t;
      }
    }

    inline void asmemdel()
    {
      size_m wold = w, z = w - free; //старый размер
      //делать пока занято меньше или равно половина размера
      while (z <= w>>1 && w)w>>=1;
      if (w != wold)
      {
        free += w - wold;
        some *t = (some*)new char[w*sizeof(some)];
        delete [] (char*)u;
        u = t;
      }
      if(!w){delete [](char*)u; free=0; u=0;}
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

    inline void operator<<(const some &what)
    {
      u[w - free - 1] = what;
    }

        inline DynArr operator*(float skolko)
      {
        DynArr n(*this);
          n*=skolko;
          return n;
      }

        inline void operator/=(float skolko)
        {
          float wn = w - free;
          float wk = wn / skolko;
          remove(wk, wn - 1);
        }

      inline DynArr operator/(float skolko)
      {
        DynArr n(*this);
        n/=skolko;
        return n;
      }

        inline void operator%=(float skolko)
        {
          float wn = w - free;
          float wk = wn / skolko;
          remove(wk - wk, wn - 1 - wk);
        }

        inline DynArr operator%(float skolko)
        {
          DynArr n(*this);
          n%=skolko;
          return n;
        }

        int find_ptr(some* what)
        {
          if(what>=u && what<u+w-free)
            return int(what-u);
          return -1;          
        }

        inline int find(const some& what, size_m wn, size_m wk)
        {
          for (register size_c i = wn; i <= wk; i++)
            if (u[i] == what)return i;
          return -1;
        }

        inline int find(const some& what)
        {
          size_m wk = w - free;
          for (register size_c i = 0; i < wk; i++)
            if (u[i] == what)return i;
          return -1;
        }

      inline void operator-=(DynArr &what)
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

      inline DynArr operator-(DynArr &what)
      {
        DynArr ret(*this);
        ret-=what;
        return ret;
      }

        inline bool operator<(DynArr &cmp)
        {
        if (cmp.length() > w - free)
            return true;
          else
            return false;
        }
        inline bool operator>(DynArr &cmp)
        {
        if (cmp.length() < w - free)
            return true;
          else
            return false;
        }
        inline bool operator<=(DynArr &cmp)
        {
        if (cmp.length() >= w - free)
            return true;
          else
            return false;
        }
        inline bool operator>=(DynArr &cmp)
        {
          if (cmp.length() <= w - free)
            return true;
          else
            return false;
        }
 
