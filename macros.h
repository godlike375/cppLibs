#define for1to(a,c)\
for(int a=0; a<c; a++)

#define for1toval(a,b,c)\
for(int a=b; a<c; a++)

#define for2to(a,b,d,e)\
for(int a=0; a<d; a++)\
for(int b=0; b<e; b++)

#define for2toval(a,b,x,y,d,e)\
for(int a=x; a<d; a++)\
for(int b=y; b<e; b++)

#define for1from(a,c)\
for(int a=c; a>0; a--)

#define for1fromval(a,b,c)\
for(int a=c; a>b; a--)

#define for2from(a,b,d,e)\
for(int a=d; a>0; a--)\
for(int b=e; b>0; b--)

#define for2fromval(a,b,x,y,d,e)\
for(int a=d; a>x; a--)\
for(int b=e; b>y; b--)

#define da DynArr
#define ds DynString
#define db DataBase	

//Методы dynarra записать в виде функций