	unsigned int c=0, n=0;
	fp=1;

	for (int i=0; i<last; i++)
	{
    if (str[i] == ' ')
    {
    if (!fp)
    {
      if(c)
      {
        res[s++].copyb(&str[0]+n, c);
      }
      fp = true;
    }
    continue;
      }
      else
    {
  if(fp)
    {fp=0; n=i; c=0;}
    c++;
  if (i==last-1  && str[i] != ' ')
  {
    res[s].copyb(&str[0]+n, c+1);
  }
  }
}
