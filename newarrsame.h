
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
          u = CustomAllocator.Realloc<some>(u, wold, w);
        else
#ifdef minorard
          u = CustomAllocator.New<some>(w*sizeof(some), 0);
#else
      u = CustomAllocator.New<some, 0>(w*sizeof(some));
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
        if(!w){ CustomAllocator.Delete<char>(u, wold*sizeof(some)); free=0; u=0;}
        else
        free += w - wold;
        u = CustomAllocator.Realloc<some>(u, wold, w);
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
          u = CustomAllocator.Realloc<some, 0>(u, wold, w);
#else
      u = CustomAllocator.Realloc<some>(u, wold, w, 0);
#endif
        else
          u = (some*)CustomAllocator.New<char>(w*sizeof(some));
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
        if(!w){CustomAllocator.Delete<char>(u, wold*sizeof(some)); free=0; u=0;}
        else
#ifdef minorard
          u = CustomAllocator.Realloc<some, 0>(u, wold, w);
#else
      u = CustomAllocator.Realloc<some>(u, wold, w, 0);
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
 
