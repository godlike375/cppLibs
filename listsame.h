/*
		inline void find(unsigned int w)
		{
			int d1=icur-w; //от cur
			int d2=w; //от начала
			int d3=cnt-w-1; //от конца
			if (d1>0)
			{
				if(d1<d2 && d1<d3)
				{
					for(; icur>w; icur--)
						cur=cur->back;
				}
				else if(d2<=d3)
				{	
					icur=w;
					cur=head;
					for(; d2; d2--)
						cur=cur->next;
				}
				else
				{	
					icur=w;
					cur=end;
					for(; d3; d3--)
						cur=cur->back;
				}
			}
			else if (d1<0)
			{
				d1=0-d1;
				if(d1<=d2 && d1<=d3)
				{
					for(; icur<w; icur++)
						cur=cur->next;
				}
				else if(d2<=d3)
				{	
					icur=w;
					cur=head;
					for(; d2; d2--)
						cur=cur->next;
				}
				else
				{	
					icur=w;
					cur=end;
					for(; d3; d3--)
						cur=cur->back;
				}
			}
		}
*/

		inline void find(ln *w)
		{
			cur=head;
			while(cur!=w)
				cur=cur->next;
		}


		inline lit getiter()
		{
			cur=head;
			return lit(this);
		}

		inline const lit getiter(ln *&n)
		{
			return lit(n);
		}

		inline lit getiter(unsigned int n)
		{
			return lit(this, n);
		}

		inline const clit getciter(ln *n)
		{
			return clit(n);
		}
/*
		inline T& operator[](unsigned int w)
		{
			find(w);
			return cur->t;
		}
*/
		inline void remove()
		{
			ln *tmp;
			if(cur==head)
			{
				if(head->next)//??0
					cur=head->next;
				delete (head);
				head=cur;
				head->back=0;
			}
			else if(cur==end)
			{
				cur=end->back;
				delete (end);
				end=cur;
				end->next=0;
				
			}
			else
			{
				tmp=cur->next;
				cur->next->back=cur->back;
				cur->back->next=cur->next;
				delete (cur);
				cur=tmp;
			}
			cnt--;
		}
/*
		inline void remove(unsigned int w)
		{
			find(w);
			remove();
		}
*/
		inline void remove(ln* w)
		{
			find(w);
			remove();
		}

		inline void operator--(int)
		{
			cnt--;
			ln *t=end->back;
			delete (end);
			end=t;
			cur=end;
			//icur=cnt-1;
		}

		inline void operator--()
		{
			cnt--;
			ln *t=head->next;
			delete (head);
			head=t;
			cur=head;
			//icur=0;
		}
