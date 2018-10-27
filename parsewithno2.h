    f=1;
    unsigned int c=0, n=0;
  for (int i = 0; i<last; i++) {
    for (int j = 0; j<sl ; j++)
    {
      if (str[i] == sepr[j])
      {
        switch(f)
        {
          case 2: {res[s++].copyb(&str[0]+n, c); n=i; c=1; f=0; break;}
          case 0: {c++;break;}
          case 1: {n=i; c=1; f=0;break;}
        }

      goto noo;
    }
  }

      if (str[i] == ' ')
      {
        switch(f)
        {
          case 0: {res[s++].copyb(&str[0]+n, c); f=1; break;}
          case 2: {res[s++].copyb(&str[0]+n, c); f=1; break;}
        }
      }
      else
      {
        switch(f)
        {
          case 2: {c++; break;}
          case 1: {n=i; c=1; f=2; break;}
          case 0: {res[s++].copyb(&str[0]+n, c); n=i; c=1; f=2; break;}
        }
      }
      noo:
        if (i==last-1 && str[i] != ' ')
        {
          res[s++].copyb(&str[0]+n, c);
        }
  }
}