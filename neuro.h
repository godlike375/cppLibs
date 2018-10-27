class neuro
{
	public:
	float power;
	DynArr<float> d,w;
	DynArr<neuro *> send, receive;
	DynArr<short> a;
	neuro()
	{
	}
	void connect(neuro * s)
	{
		send.add(s);
		s->d++;
		s->w.add(1);
		s->receive.add(this);
		a.add(s->d.last());
	}

	void activ()
	{
		power=0;
		int n=d.length();
		for (int i = 0; i < n; i++) {
			power+=d[i]*w[i];
		}
		if (power<0.5f)
			power=0;
		if (power>1.0f)
			power=1;
	}

	void trans()
	{
		if (power>0){
			int s=send.last();
			for (int j = 0; j <= s; j++) {
				send[j]->d[a[j]]=power;
			}
		}
	}
	//operator=();
};