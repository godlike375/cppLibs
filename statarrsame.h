  inline StatArr():w(0), u(0) {};

    inline void reverse(unsigned int wn, unsigned int wk)
    {
      unsigned int mid=(w-1)/2;
      if(mid)
      {
      some m;
      unsigned int k=0;
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
      unsigned int mid=(w-1)/2;
      if(mid)
      {
      some m;
      unsigned int k=0;
        for(some *i=u, *j=u+w-free-1; k<mid; k++, j--, i++)
        {
        m=*j;
        *j=*i;
        *i=m;
        }
      }
    }

    inline some &operator[](unsigned int W) const {
    return u[W];
    }

    inline int last() const
    {
      return w - 1;
    }

    inline StatArr operator+(const StatArr &ad)
    {
      StatArr ret(*this);
      ret += ad;
      return ret;
    }

    inline void cut(unsigned int wn, unsigned int wk)
    {
      if (wn)
        remove(0, wn - 1);
      if (wk != w-free-1)
        remove(wk - wn + 1, w - free - 1);
    }

    inline StatArr part(unsigned int wn, unsigned int wk)
    {
      StatArr ret;
      unsigned int len = wk - wn + 1;
      ret.addempty(len++);
      for (some *i = u+wn, *j = &ret[0]; --len;)
        *j++ = *i++;
      return ret;
    }

    inline operator bool()
    {
        return (w);
    }

    inline some * operator!()
    {
      return u;
    }

    inline unsigned int length() const
    {
      return w;
    }

    inline some* begin()
    {
      return u;
    }

    inline some* end()
    {
      return u+w;
    }

private:

  inline void trans(unsigned int len, some *o, some *k)
  {
    #if !custom
    memcpy(k,o,len*sizeof(some));
    #else
      unsigned int**oo=(unsigned int**)o, **kk=(unsigned int**)k;
      register unsigned int a=len*sizeof(some)/sizeof(unsigned int*);
      if(a)
      {
        for (register unsigned int i=0; i<a; i++)
          *kk++ = *oo++;
      }
      a=len*sizeof(some)%sizeof(unsigned int*);
      if(a)
    {
    char *kkk=(char*)kk, *ooo=(char*)oo;
        for(register unsigned int i=0; i<a; i++)
          *kkk++=*ooo++;
      }
    #endif
  }

  void resize(unsigned int W)
  {
    if(w!=W)
    {
      some *t=new (some*) char[W*sizeof(some)];
      if(w<W)
        trans(w, u, t);
      else
        trans(W, u, t);
      delete[] (char*)u;
      u=t;
    }
  }

  void asresize(unsigned int W)
  {
    if(w!=W)
    {
      delete[] (char*)u;
      u=new (some*) char[W*sizeof(some)];
    }
  }