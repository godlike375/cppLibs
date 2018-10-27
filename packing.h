template<class T> const T& unpack(size_x s, void* adr)
{
size_m* v=(size_m*)adr;
for(; --s; )
{
v=*(size_m**)v;
}
return *(const T*&)v;
}

template<class T> void* pack(size_x s, const T& val)
{
size_m* v = (size_m*)new T(val);
for(; --s; )
{
size_m* t= v;
v = new size_m;
*v = (size_m)t;
}
return v;
}