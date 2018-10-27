inline void* operator new(size_m sz, void *p)
{
#ifndef safe
	return p;
#else
	if(p)
		return p;
	else
		throw("placement new for null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
}

inline void* operator new[](size_m, void *p)
{
#ifndef safe
	return p;
#else
	if(p)
		return p;
	else
		throw("placement new for null-pointer in file" str(__FILE__) "on line "str( __LINE__) str(\n));
#endif
} 



