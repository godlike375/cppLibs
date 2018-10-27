#ifndef bytes3
#define bytes3

#ifndef arduino
typedef unsigned int unint;
#else
typedef unsigned long unint;
#endif

class uint3b
{
public:
	unsigned char ui[3];

	inline uint3b(unint i)
	{
			unsigned short *p1=(unsigned short*)ui, *p2=(unsigned short*)&i;
			*p1++=*p2++;
			unsigned char *p3=(unsigned char*)p1, *p4=(unsigned char*)p2;
			*p3=*p4;
	}

	inline uint3b(unsigned short i)
	{
		*(unsigned short*)ui=i;
		ui[2]=0;
	}

	inline uint3b(unsigned char i)
	{
		ui[0]=i;
		ui[1]=0;
		ui[2]=0;
	}


	inline void operator=(unint i)
	{
			unsigned short *p1=(unsigned short*)ui, *p2=(unsigned short*)&i;
			*p1++=*p2++;
			unsigned char *p3=(unsigned char*)p1, *p4=(unsigned char*)p2;
			*p3=*p4;
	}

	inline void operator=(unsigned short i)
	{
		*(unsigned short*)ui=i;
		ui[2]=0;
	}

	inline void operator=(unsigned char i)
	{
		ui[0]=i;
		ui[1]=0;
		ui[2]=0;
	}

	uint3b(){
		ui[0]=0;
		ui[1]=0;
		ui[2]=0;
	};

	inline void operator+=(unint s)
	{
		unint r=(unint)*this;
		r+=s;
		*this=r<=16777215u?r:r-16777215u;
	}

	inline void operator-=(unint s)
	{
		unint r=(unint)*this;
		r-=s;
		*this=r<=16777215u?r:16777215u-(4294967295u-r);
	}

	inline void operator*=(unint s)
	{
		unint r=(unint)*this;
		r*=s;
		*this=r<=16777215u?r:r-16777215u;
	}

	inline void operator/=(unint s)
	{
		unint r=(unint)*this;
		r/=s;
		*this=r;
	}

	inline void operator%=(unint s)
	{
		unint r=(unint)*this;
		r%=s;
		*this=r;
	}

	inline void operator++()
	{
		unint r=(unint)*this;
		++r;
		*this=r;
	}

	inline void operator--()
	{
		unint r=(unint)*this;
		--r;
		*this=r;
	}

	inline void operator++(int)
	{
		unint r=(unint)*this;
		r++;
		*this=r;
	}

	inline void operator--(int)
	{
		unint r=(unint)*this;
		r--;
		*this=r;
	}

	inline void operator^=(unint s)
	{
		unint r=(unint)*this;
		r^=s;
		*this=r;
	}

	inline void operator>>=(unint s)
	{
		unint r=(unint)*this;
		r>>=s;
		*this=r;
	}

	inline void operator<<=(unint s)
	{
		unint r=(unint)*this;
		r<<=s;
		*this=r;
	}		

	inline void operator|=(unint s)
	{
		unint r=(unint)*this;
		r|=s;
		*this=r;
	}

	inline void operator&=(unint s)
	{
		unint r=(unint)*this;
		r&=s;
		*this=r;
	}

	inline operator unint() const
	{
		unint tmp;
		if(! ((size_m)ui  %2))
		{
			tmp=*((unsigned short*)ui);
				*(((unsigned char*)&tmp)+2)=ui[2];
		}
		else
		{
			tmp=ui[0];
			*(unsigned short*)(((unsigned char*)&tmp)+1)=*(unsigned short*)(ui+1);
		}
		return tmp;
	}
};

#endif
