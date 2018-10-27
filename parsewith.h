  
    sym=str;
    fp = 1; fs=0;
    unsigned int c=0, n=0;
  for (int i = last; --i; sym++) {
    sep = &sepr[0];
    for (int j = sl; --j ; sep++)
    {
      if (*sym == *sep)
      {
        if (!fs)
        {
          if(!fp)
          {
            res++;
            res[s++].copyb(&str[0]+n, c);
            fp=0;
          }
          n=last-i-1;
          c=1;
          fs = 1;
        }
      else
        c++;
      goto noo;
    }
  }

  goto contn;

  noo: continue;

  contn:
      if (*sym == ' ')
      {
        if (!fp)
        {
          res++;
          res[s++].copyb(&str[0]+n, c);
          fp = 1;
          fs=0;
          c=0;
        }
      }
      else
      {
        if(fp)
          {fp=0; n=last-i-1;}
        else if(fs)
        {res++; res[s++].copyb(&str[0]+n, c); fs=0; n=last-i-1; c=1;}

        if (!(i-1))
        {
          res++;
          res[s].copyb(&str[0]+n, c+1);
        }
      
     c++;
    }
  }