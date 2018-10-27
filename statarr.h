template <class some, bool nopod=standart> class StatArr {};

template <class some> class StatArr<some, 1> {
  unsigned int w;
  some *u;

  public:

    inline StatArr(const StatArr &copy)
    {
      w = 0;
      unsigned int l = copy.length();
      if(l)
      {
        asresize(l);
        register unsigned int k=0;
        for (register some * i = u, *j = &copy[0]; k<l; k++)
          new(i++) some(*j++);
      }
      else
        u=0;
    }

    inline void operator=(const StatArr &s)
    {
      unsigned int len = s.length();
      some *uu=u;
      for(int i=0; i<w; i++)
        uu++->~some();
    if (len != w)
      asresize(len);
      register unsigned int k=0;
      for (register some * i = u, *j = &s[0]; k<len; k++)
          new(i++) some(*j++);
    }

    inline void operator+=(const DynArr &ad)
    {
      unsigned int W=ad.length();
      w+=W;
      resize(w);
      for (register some *i = u + w - free - W++ , *j = &ad[0];  --W; )
          new(i++) some(*j++);
    }

    inline void clear()
    {
      register some *uu=u;
      for(register unsigned int i=0; i<w; i++)
        uu++->~some();
      delete[] (char*)u;
      w=0;
      u=0;
    }

    inline ~StatArr() {
        register some *uu=u;
        for(register unsigned int i=0; i<w; i++)
          uu++->~some();
      delete[] (char*)u;
    }


template <class some> class StatArr<some, 0> {
  unsigned int w;
  some *u;

  public:

    inline StatArr(const StatArr &copy)
    {
      w = 0;
      unsigned int l = copy.length();
      if(l)
      {
        asresize(l);
        register unsigned int k=0;
        trans(l, &copy[0], u);
      }
      else
        u=0;
    }

    inline void operator=(const StatArr &s)
    {
      unsigned int len = s.length();
	  if (len != w)
	  {
		asresize(len);
		trans(len, &s[0], u);
	  }
    }

    inline void operator+=(const StatArr &ad)
    {
      unsigned int W=ad.length();
      w+=W;
      resize(w);
      trans(W, &ad[0], u + w);
    }

    inline void clear()
    {
      delete[] (char*)u;
      w=0;
      u=0;
    }

    inline ~StatArr() {
      delete[] (char*)u;
    }