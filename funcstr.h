/*
  DynString strconvert(String & a)
  {
  int l = a.Length();
  DynString d;
  d.addempty(l);
  for (char *i = !d, *j = &a[1]; l--;)
  {
   i++ = *j++;
  }

  return d;
  }
*/

//???? to_str(float)



inline char tochar(short num)
{
  if (num > -1 && num < 10)
    return char(num + 48);
  if (num > 9 && num < 16)
    return char(num + 87);
  return '-';
}

inline char upper(char ch)
{
  if ((ch>96 && ch <123)||(ch>-33 && ch<0))
    return ch-32;
  if(ch==-72)
    return -88;
}

inline char lower(char ch)
{
  if ((ch>64 && ch <91)||(ch>-65 && ch<-32))
    return ch+32;
  if(ch==-88)
    return -72;
}

inline char letter(short ch)
{
  if(ch>=0 && ch<6)
  {
    return char(ch-32);
  }
  /*
  else if(ch == 6)
  {
    return '?';
  }
  */
  else if(ch >6 && ch<=32)
  {
    return char(ch-33);
  }
};

short number(char ch)
{
  if(ch>=-32 && ch<-26)
  {
    return ch+32;
  }
  /*
  else if(ch == '?')
  {
    return 6;
  }
  */
  else if(ch >=-26 && ch<=0)
  {
    return ch+33;
  }
     
}

const dynstr& filterin(dynstr &s)
{
  char *p=&s[0];
  char c;
  for(int i=s.length()+1; --i; p++)
  {
    c=*p;
    if(c>-97 && c<-80)
    {
      c+=64;
      *p=c;
      continue;
    }
    else if(c>-33 && c<-16)
    {
      c+=16;
      *p=c;
      continue;
    }
    else if(c>-129 && c<-96)
    {
      c+=64;
      *p=c;
      continue;
    }
    else if(c==-15)
    {
      c=-72;
      *p=c;
      continue;
    }
    else if(c==-16)
    {
      c=-88;
      *p=c;
      continue;
    }
  }
  return s;
}

const dynstr& filterout(dynstr &s)
{
  char *p=&s[0];
  char c;
  for(int i=s.length()+1; --i; p++)
  {
    c=*p;
    if(c>-33 && c<-16)
    {
      c-=64;
      *p=c;
      continue;
    }
    if(c>-17 && c<0)
    {
      c-=16;
      *p=c;
      continue;
    }
    if(c>-65 && c<-32)
    {
      c-=64;
      *p=c;
      continue;
    }
    else if(c==-72)
    {
      c=-15;
      *p=c;
      continue;
    }
    else if(c==-88)
    {
      c=-16;
      *p=c;
      continue;
    }
  }
  return s;
}

inline short tonum(char ch)
{
  if (ch > 47 && ch < 58)
    return short(ch) - 48;
  return -1;
}

inline unsigned char tonumhex(char ch)
{
  if (ch > 96 && ch < 103)
    return short(ch) - 87;
  return -1;
}

inline DynString to_str(int num)
{
  if (!num) {
    return DynString('0');
  }
  DynString res;
  int i = 0;
  for (int n = num; n ; n /= 10, i++);
  if (num < 0)
  {
    num *= -1;
    res.addempty(i + 1);
    for (; i; num /= 10 )
      res[i--] = tochar(num % 10);
    res[0] = '-';
  }
  else
  {
    res.addempty(i);
    for (; i--; num /= 10 )
      res[i] = tochar(num % 10);
  }
  return res;
}

inline void to_str(int num, dynstr &p)
{
  if (!num) {
    move(DynString('0'), p);
    return;
  }
  DynString res;
  int i = 0;
  for (int n = num; n ; n /= 10, i++);
  if (num < 0)
  {
    num *= -1;
    res.addempty(i + 1);
    for (; i; num /= 10 )
      res[i--] = tochar(num % 10);
    res[0] = '-';
  }
  else
  {
    res.addempty(i);
    for (; i--; num /= 10 )
      res[i] = tochar(num % 10);
  }
  move(res, p);
}

inline DynString to_strf(float num)
{
  if (!num)
  {
    return DynString('0');
  }
  DynString res;
  int i = 0;
  int kol = 5;
  for (int n = num; n ; n /= 10, i++);
  int n = num * 100000;
  for (; (n % 10) == 0 ; n /= 10, kol--);
  if (kol)
    kol++;
  if (num < 0)
  {
    num *= -1;
    n *= -1;
    res.addempty(i + kol + 1);
    res[0] = '-';
    res[i + 1] = '.';
    int j = i;
    for (int n2 = num; j >= 1 ; n2 /= 10, j)
      res[j--] = tochar(n2 % 10);
    j = i + kol;
    for (; j > i + 1; n /= 10 )
      res[j--] = tochar(n % 10);

  }
  else
  {
    res.addempty(i + kol);
    res[i] = '.';
    int j = i - 1;
    for (int n2 = num; j >= 0 ; n2 /= 10, j)
      res[j--] = tochar(n2 % 10);
    j = i - 1 + kol;
    for (; j > i; n /= 10 )
      res[j--] = tochar(n % 10);
  }

  return res;

}

inline void to_strf(float num, dynstr &p)
{
  if (!num)
  {
    move(DynString('0'), p);
    return;
  }
  DynString res;
  int i = 0;
  int kol = 5;
  for (int n = num; n ; n /= 10, i++);
  int n = num * 100000;
  for (; (n % 10) == 0 ; n /= 10, kol--);
  if (kol)
    kol++;
  if (num < 0)
  {
    num *= -1;
    n *= -1;
    res.addempty(i + kol + 1);
    res[0] = '-';
    res[i + 1] = '.';
    int j = i;
    for (int n2 = num; j >= 1 ; n2 /= 10, j)
      res[j--] = tochar(n2 % 10);
    j = i + kol;
    for (; j > i + 1; n /= 10 )
      res[j--] = tochar(n % 10);

  }
  else
  {
    res.addempty(i + kol);
    res[i] = '.';
    int j = i - 1;
    for (int n2 = num; j >= 0 ; n2 /= 10, j)
      res[j--] = tochar(n2 % 10);
    j = i - 1 + kol;
    for (; j > i; n /= 10 )
      res[j--] = tochar(n % 10);
  }

  move(res, p);

}

inline bool isnum(char n)
{
  if (n > 47 && n < 58)
    return true;
  return false;
}

inline bool islet(char n)
{
  if (n > 96 && n < 123)
    return true;
  if (n > -33 && n < 0)
    return true;
  return false;
}

//number и letter доработать под английские
