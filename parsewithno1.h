  if(last)
  {
    char f = 1;
    unsigned int s=res.length();
    unsigned int sl = sepr.length();
    unsigned int r=0;
  for (int i = 0; i<last; i++) {
    for (int j = 0; j<sl ; j++)
    {
      if (str[i] == sepr[j])
      {
        switch(f)
        {
          case 2: {r++; f=0; break;}
          case 1: {f=0;break;}
        }

      goto no;
    }
  }

      if (str[i] == ' ')
      {
        switch(f)
        {
          case 0: {r++; f=1; break;}
          case 2: {r++; f=1; break;}
        }
      }
      else
      {
        switch(f)
        {
          case 1: {f=2; break;}
          case 0: {r++; f=2; break;}
        }
      }
      no:
        if (i==last-1 && str[i] != ' ')
          r++;
  }
  res.addempty(r);