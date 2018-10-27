#ifndef dynamicarr
#define dynamicarr


#ifndef cpp11
template <class some, bool nopod=standart> class DynArr {};
#else
template <class some, bool nopod=!std::is_pod<some>::value > class DynArr {};
#endif

template <class some> class DynArr<some, 1> {
  size_c w;
  size_c free;
  some *u;

  public:

    inline DynArr(const DynArr &copy)
    {
      w = 0;
      size_c l = copy.length();
      if(l)
      {
        asmemal(l);
        free=w-l;
        register size_c k=0;
        for (register some * i = u, *j = &copy[0]; k<l; k++)
          new(i++) some(*j++);
      }
      else
      {
        free=0;
        u=0;
      }
    }

    inline void operator=(const DynArr &s)
    {
      size_c len = s.length();
        some *uu=u;
      for(int i=w-free+1; --i;)
        uu++->~some();
      
    if (len > w)
      asmemal(len - w);
    free = w - len;
    if (len <= w>>1)
     asmemdel();
      register size_c k=0;
      for (register some * i = u, *j = &s[0]; k<len; k++)
          new(i++) some(*j++);
    }

    inline void operator++(int)
    {
      if(!free)
        memal();
      new (u+w-free--)some;
    }

    inline void operator--(int)
    {
      (u+w- ++free)->~some();
      if(free>=w>>1)
        memdel();
    }

    inline void add(const some &ad) 
    {
      if(!free)
        memal();
     new(u+w - free--) some(ad);
    }

    inline void addbeg(const some &ad) 
    {
      if(!free)
        memal();
      trans(w-free--, u, u+1);
     new(u) some(ad);
    }

    inline void addbeg(const some &ad, size_c kolvo) 
    {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free, u, u+kolvo);
      size_c k=0;
      for (register some * i = u; k<kolvo; k++)
        new(i++) some(ad);
     free-=kolvo;
    }

    inline void operator++()
    {
      if(!free)
        memal();
      trans(w-free--, u, u+1);
      new(u) some;
    }

    inline void addbegempty(size_c kolvo) {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free, u, u+kolvo);
        new(u) some[kolvo];
      free -= kolvo;
    }

    inline void operator--()
    {
        
      u->~some();
      ++free;
      trans(w-free, u+1, u);
      if(free>=w>>1)
        memdel();
        
    }

    inline void removebeg(size_c kolvo)
    {
      size_c j=0;
      for(some * i = u; j<kolvo; j++)
        (i++)->~some();
      free += kolvo;
      trans(w-free, u+kolvo, u);
      if(free>=w>>1)  
        memdel();
    }    

    inline void add(const some& ad, size_c kolvo) {
      if(free<kolvo)
        memal(kolvo);
      register size_c k = 0;
      for (register some * i = u + (w - free); k<kolvo; k++)
          new(i++) some(ad);
      free -= kolvo;
    }

    inline void addempty(size_c kolvo) {
      if(free<kolvo)
        memal(kolvo);
      register size_c k = 0;
        new(u+w-free) some[kolvo];
      free -= kolvo;
    }

    inline void operator+=(const DynArr &ad)
    {
      size_c W=ad.length();
      memal(W);
      free-=W;
      for (register some *i = u + w - free - W++ , *j = &ad[0];  --W; )
          new(i++) some(*j++);
    }
    

    inline void remove(size_c W) {
      (u+W)->~some();
      trans(w-free-W, u + W+1, u + W);
      if(++free >= w>>1)
        memdel ();
    }

    inline void remove(size_c wn, size_c wk) {
      size_c sz=wk-wn+1, j=0;
      for(some * i = u+wn; j<sz; j++)
        (i++)->~some();
      trans(sz,u+wk+1,u+wn);
      free += sz;
      if(free>=w>>1)  
        memdel();
    }

    inline void clear()
    {
      register some *uu=u;
      for(register size_c i=w-free, j=0; j<i; j++)
        uu++->~some();
      delete[] (char*)u;
      w=free=0;
      u=0;
    }

    inline void insert(size_c W, const some& ins) {
      if(!free)
        memal();
      trans(w-free-- -W, u+W, u+W+1);
      new(u+W) some (ins);
    }

    inline void insert(size_c W) {
      if(!free)
        memal();
      trans(w-free-- -W, u+W, u+W+1);
      new(u+W) some;
    }

    inline void insert(size_c W, const some& ins, size_c kolvo) {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free -W, u+W, u+W+kolvo);
      free -= kolvo;
      register size_c j=0;
      for (some* i = u+W; j<kolvo; j++)
        new(i++) some (ins);
    }

    inline ~DynArr() {
            register some *uu=u;
            for(register size_c i=w-free, j=0; j<i; j++)
              uu++->~some();
          delete[] (char*)u;
    }

#include "dynarrsame.h"

};

template <class some> class DynArr<some, 0> {
  size_c w;
  size_c free;
  some *u;

  public:

    inline DynArr(const DynArr &copy)
    {
      w = 0;
      size_c l = copy.length();
      if(l)
      {
        asmemal(l);
        free=w-l;
        trans(l, &copy[0], u);
      }
      else
      {
        free=0;
        u=0;
      }
    }

    inline void operator=(const DynArr &s)
    {
      size_c len = s.length();
    if (len > w)
      asmemal(len - w);
    free = w - len;
    if (len <= w>>1)
     asmemdel();
        trans(len, &s[0], u);
    }

    inline void operator++(int)
    {
  	  if(!free)
  		  memal();
  		free--;
    }

    inline void operator--(int)
    {
      if(++free>=w>>1)
        memdel();
    }

    inline void add(const some &ad) 
    {
      if(!free)
        memal();
      u[w-free--]=ad;
    }

    inline void add(const some& ad, size_c kolvo) {
      if(free<kolvo)
        memal(kolvo);
      size_c k = kolvo+1;
      for (register some * i = u + (w - free); --k; )
        *i++ =ad;
      free -= kolvo;
    }

    inline void addempty(size_c kolvo) {
      if(free<kolvo)
        memal(kolvo);
      free -= kolvo;
    }


    inline void addbeg(const some &ad) 
    {
      if(!free)
        memal();
      trans(w-free--, u, u+1);
      u[0]=ad;
    }

    inline void addbeg(const some &ad, size_c kolvo) 
    {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free, u, u+kolvo);
      size_c k=0;
      for (register some * i = u; k<kolvo; k++)
        *i++=ad;
     free-=kolvo;
    }

    inline void operator++()
    {
      if(!free)
        memal();
      trans(w-free--, u, u+1);
      new(u) some();
    }

    inline void addbegempty(size_c kolvo) {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free, u, u+kolvo);
      register size_c k = 0;
      for (register some * i = u + (w - free); k<kolvo; k++)
        new(i++) some;
      //new(u) some[kolvo];
      free -= kolvo;
    }

    inline void operator--()
    {
      if(++free>=w>>1)
        memdel();
      trans(w-free, u+1, u);
    }

    inline void removebeg(size_c kolvo)
    {
      free += kolvo;
      trans(w-free, u+kolvo, u);
      if(free>=w>>1)  
        memdel();
    }   

    inline void operator+=(const DynArr &ad)
    {
      size_c W=ad.length();
      memal(W);
      free-=W;
	  trans(W, &ad[0], u + w - free - W);
	}

    inline void remove(size_c W) {
      trans(w-free-W, u + W+1, u + W);
      if(++free >= w>>1)
        memdel ();
    }

    inline void remove(size_c wn, size_c wk) {
    size_c sz=wk-wn+1;
    trans(sz, u+wk+1, u+wn);
      free += sz;  
      memdel();
    }

    inline void clear()
    {
      delete[] (char*)u;
      w=free=0;
      u=0;
    }

    inline void insert(size_c W, const some& ins) {
      if(!free)
        memal();
      trans(w-free-- -W, u+W, u+W+1);
      u[W]=ins;
    }

    inline void insert(size_c W) {
      if(!free)
        memal();
      trans(w-free-- -W, u+W, u+W+1);
    }

    inline void insert(size_c W, const some& ins, size_c kolvo) {
      if(free<kolvo)
        memal(kolvo);
      trans(w-free-- -W, u+W, u+W+kolvo);
      free -= kolvo++;
      for (some* i = u+W; --kolvo;)
        *i++ = ins;
    }


    inline ~DynArr() {
      delete[] (char*)u;
    }

#include "dynarrsame.h"

};

#define dynarr DynArr
/*для максимального ускорения можно добавить возможность
  резервивать дополнительную память или сообщать, что мы собираемся
  удалить сколько то объектов и только после удаления надо очищать память

  Еще можно сделать addmany() и removemany() с переменным кол-вом аргументов для быстроты работы*/
//Можно сделать compare(), которая выдает кол-во совпадений элементов текущего массива и сравниваемого
//Тоже переделать все операторы под вариант равно и без равно
//Переделать find (в строках последний его вариант готовый)
//- и -= работает криво засчет find
//Еще как идея, сделать добавление/удаление из начала массива adbeg rembeg
//Унарный минус работает аналогично reverse для всего массива
//Операторы | и & перегрузить для массивов
//Подумать, чтоб и здесь и в строках, если ты знаешь, что долго не будет изменяться массив, то какб бы заморозить его, убрать затраты по памяти лишние,
//путем установки размера на w-free, срежется запасная часть, потом если он начнет изменяться, то опять изменить размер до двойки в степени, назвать можно freeze()
//подумать о перегрузке << и >>
//Подумать насчет дополнительных флажков в классе (для freeze, еще чего-то)


#ifdef iostr
template <class T>
ostream& operator<<(ostream& stream, const dynarr<T>& d)
{
    stream<<'[';
    if(d.length())
    {
        for(size_m i=0, j=d.length()-1; i<j; i++)
            stream<<d[i]<<", ";
        stream<<d[d.length()-1]<<']';
    }
    else
        stream<<" ]";
}
#endif

#endif