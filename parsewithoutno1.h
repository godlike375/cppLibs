    if(last)
  {
  unsigned int s=res.length(), r=0;
  bool fp = 1;
  for (unsigned int i = 0; i<last; i++)
  {
  if (str[i] == ' ')
  {
  if (!fp)
  {
    r++;
    fp = true;
  }
  continue;
    }
    else
  {
  if(fp)
  {fp=0;}
  if (i==last-1  && str[i] != ' ')
    r++;
  }
  }
  res.addempty(r);
