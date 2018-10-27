#ifndef MYPARSER
#define MYPARSER

void parse (const DynString &str, DynArr<DynString> &res) {
  unsigned int last = str.length();
  #include "parsewithoutno1.h"
  #include "parsewithoutno2.h"
  }
  }

void parse (char *str, DynArr<DynString> &res) {
    int last = 0;
  for(; str[last]; last++);
  #include "parsewithoutno1.h"
  #include "parsewithoutno2.h"
  }
}  

void parse2
(const DynString &str, DynArr<DynString> &res)
{
  int last = str.length();
  if(last)
  {
  unsigned int s=0;
  bool fp;
  char *sym;
  #include "parsewithoutno2.h"
  }
}

void parse2
(char *str, DynArr<DynString> &res)
{
  unsigned int s=0;
  int last = 0;
  for(; str[last]; last++);
  if(last)
  {
  bool fp;
  char *sym;
   #include "parsewithoutno2.h"
  }
}

inline float power(float a, char b)
{
if(!b)
  return 1;
else if(b<0)
{
  b=0-b;
  for(float t=a;--b; a*=t)
  return 1/a;
}
else
{
  float t=a;
  for(; --b; a*=t);
  return a;
}
}

float parsefloat
(const DynString &num)
{
  short dot = -1;
  float res = 0;
  int last = num.last();
  for (int i = 0; i < last; ++i)
    if (num[i] == '.')
    {
      dot = i;
      goto tochka;
    }

  for (int i = last, j = 0; i >= 0; i--, j++)
  {
    res += tonum(num[i]) * power(10, j);
  }
  if (num[0] == '-')
    res *= -1;
  return res;
tochka:
  //до точки
  for (int i = dot + 1, j = -1; i <= last; i++, j--)
  {
    res += tonum(num[i]) * power(10, j);
  }
  //от точки
  for (int i = dot - 1, j = 0; i >= 0; i--, j++)
  {
    res += tonum(num[i]) * power(10, j);
  }
  if (num[0] == '-')
    res *= -1;
  return res;
}

int parseint
(const DynString &num)
{
  int res = 0;
  int last = num.length();
  unsigned char j=0;
  char *n=&num[last-1];
  for (; --last;)
  {
	res += tonum(*n--) * power(10, j++);
  }
  if (num[0] == '-')
	res *= -1;
  else
	res += tonum(num[0]) * power(10, j);
  return res;
}

unsigned int parsebin (const DynString &bin)
{
  int res = 0;
  int last = bin.length();
  char *b=&bin[last-1];
  unsigned char j=0;
  for (; --last;)
  {
	res += tonum(*b--) * power(2, j--);
  }
  return res;
}

unsigned int parsehex (const DynString &hex)
{
  int res = 0;
  int last = hex.length();
  char *h=&hex[last-1];
  unsigned char j=0;
  for (; --last ; j++)
  {
    res += tonumhex(*h--) * power(16, j--);
  }
  return res;
}


void parse
(const DynString &str, DynArr<DynString> &res, DynArr<char> &sepr) {
  int last = str.length();
#include "parsewithno1.h"
#include "parsewithno2.h"
  
}

void parse
(char *str, DynArr<DynString> &res, DynArr<char> &sepr) {
  unsigned int last = 0;
  for(; str[last]; last++);
#include "parsewithno1.h"
#include "parsewithno2.h"
}

void parse2
(char *str, DynArr<DynString> &res, DynArr<char> &sepr) {

  unsigned int last = 0;
  for(; str[last]; last++);
  if(last)
  {
    char f = 1;
    unsigned int s=0;
    unsigned int sl = sepr.length();
  #include "parsewithno2.h"
}

void parse2
(const DynString &str, DynArr<DynString> &res, DynArr<char> &sepr) {
  int last = str.length();
  if(last)
  {
    char f = 1;
    unsigned int s=0;
    unsigned int sl = sepr.length();
  #include "parsewithno2.h"
}

#endif