
template<class One, class Two>
class mypair
{
public:
One one;
Two two;

	inline mypair(One one, Two two)
	{
		this->one=one;
		this->two=two;
	}

	inline mypair()
	{
	}

	inline void newpair(One one, Two two)
	{
		this->one=one;
		this->two=two;
	}

	inline void operator[](One one)
	{
		this->one=one;
	}


	inline void operator()(Two two)
	{
		this->two=two;
	}

	inline One operator!()
	{
		return one;
	}

	inline Two operator*()
	{
		return two;
	}

};