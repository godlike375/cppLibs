#ifndef database
#define database

class DataBase
{

void parsestr2
(char *str, DynArr<DynString> &res)
{
	unsigned int size=res.length();
  unsigned int last = 0;
  for(; str[last]; last++);
  if(last)
  {
  	unsigned int j = 0;
    bool fp = false, fs = false;
    int c=0, n=0;
    for (int i = 0; j<size; i++)
    {
      if (str[i] == '|')
      {
        if (fs)
        {
          res[j++].copyb(&str[0]+n,c);
          fs = 0;
          n=i;
          c=0;
          continue;
        }
        c=0;
        n=i;
        fs = 1;
        continue;
      }

    if (str[i] == ' ' && !fs)
    {
      if (!fp)
      {
        if(c)
          res[j++].copyb(&str[0]+n, c);
        fp = 1;
      }
      continue;
    }
    else
     {
  if(fp)
    {fp=0; n=i; c=0;}
      c++;
      if (!(i-1))
        res[j].copyb(str+n, c+1);
     }
    }
  }
}

    fstream fileb, file; //2 объекта файловых потока для работы с фалом базы и файлом
    // таблицы
    void lt() //load tables - загрузка таблиц из файлов в массив
    {
      fileb.seekg(0, ios::beg);
      char * s, n[128]; //массивы символов для считывания строк из файлов таблиц и для
      // считывания имен таблиц из файла базы
      s = new char[bufsize]; //выделяем память под bufsize символов
      fileb >> n; //получить имя базы
      str++; //выделить единицу памяти
      str[0]++;
      str[0][0].add(n); //добавить имя базы в [0][0][0]
      int x; //кол-во таблиц
      fileb >> x; //получить кол-во таблиц
      if (x > 0) {
        str.addempty(x); //ыыделить память для таблиц
        DynArr<DynString> obr; //массив строк для дальнейшего открытия файлов по именам
        // из негоp
        int  cnt = 0; //счетчик для str[0][cnt] и str[cnt]
        obr.addempty(x);
        int t; //сколько выделить памяти (для каждой таблицы свое значение)
        for (int i = 1; i <= x ; i++)
        {
          fileb >> n; //считать название таблицы из файла
          obr[i-1] = n; //записать в Obr
          fileb >> t; //считать кол-во строк в таблице
          str[i].addempty(t); //выделить память под строки
        }
        for (int i = 0; i < x; i++)
        {
          file.open(obr[i]);
          if(file.is_open())
          {
	          cnt++;
	          str[0]++;
	          str[0][0].add(obr[i]); //добавляем имя файла таблицы из базы в первую строку
            // новый столбец
	          int y = str[i+1].length();
	          file.seekg(0, ios::beg);
	          file.getline(s, bufsize);
	          parse(s, str[0] [cnt]); //записать имена столбцов
			  int z = str[0] [cnt].length();
	          for (int j = 0, size = str[cnt].length(); j < size; j++)
	            str[cnt][j].addempty(z);
	          for (int j = 0; j < y; j++){
              file.getline(s, bufsize);
	            parsestr2(s, str[cnt] [j]);
				 //разделить каждую строку файла на массив
              // строк и записать в массив строк str[cnt][j]
	          }
	          file.close();}
	                
        }
      }
      delete []s;
    }

  public:
    DynArr<DynArr<DynArr<DynString> > > str; //главный трёхмерный массив строк 
    DynArr<short, 0> change; //Какие из файлов были изменены за время работы, чтобы
    // сохранение перезаписывало только их.
    unsigned short bufsize; //максимальная длина строки в файле, по умолчанию 32768

    inline DataBase(int n = 32768): bufsize(n){};//пустой конструктор с инициализацией

    DataBase(char * name, short n = 32768) //Открыть уже существующую базу
    {
      bufsize = n;
      fileb.open(name); //открыть файл базы
      if (fileb.is_open()) //если файл базы открылся
        lt(); //загрузить таблицы
      fileb.close(); //закрыть файл базы
    }

    void createBase(char * name) //Создание новой базы
    {
      if (str.length() > 0) //если массив str не пустой
        str.clear(); //очистить
      fileb.seekg(0, ios::beg); //перейти в начало файла
      str++;
      str[0]++;
      str[0][0].add(name); 
    }

    void createTable(char * name) //Создание новой таблицы в текущей базе
    {
      str++;
      str[0]++;
      str[0][0].add(name);
    }

    void addTable(char * name) //Добавление уже существующей таблицы из файла в
    // текущую базу
    {
      file.open(name);
      if (file.is_open()) 
      {
        DynString lf;
        char *s;
        s = new char[bufsize];
        str++;
        str[0][0].add(name); //добавляем имя файла таблицы из базы в первую строку
        // новый столбец
        str[0]++;
        file.seekg(0, ios::beg);
        file.getline(s, bufsize);
        lf = s;
        parse(lf, str[0] [str[0].last()]);
        int str0l= str[0].last(); //последний индекс в str[0]
        int strl = str.last(); //последний индекс в str
        int cols=str[0] [str0l].length(); //кол-во столбцов в таблице 
        while (1)
        {
          file.getline(s, bufsize);
          if(file.eof())break; //если конец файла, то выйти из цикла
          str[strl]++;
          lf = s;
          str[strl] [str[strl].last()].addempty(cols); //заполнить последнюю строку
          //по кол-ву столбцов таблицы 
          parsestr2(lf, str[strl] [str[strl].last()]); //парсить в выделенную память
        }
        file.close();
        delete[] s;
      }
    }

    void removeTable(char * name, bool del = 0) //Удаление таблицы из текущей базы
    {
      bool fl=0; //флаг что нашли в массиве
      int i=0;
      for (int l=str[0][0].length(); i<l; i++) //берем из массива имена по i, пока не
      // найдем номер нужного
        if(str[0][0][i] == name)
          {
            fl=1;
            break;
          }  
      if (fl) //если нашли 
      {
        if (del) //если надо удалить файл
          remove(!str[0][0][i]); //удалить файл по имени из str[0][0][i]
        str[0][0].remove(i);
        str[0].remove(i);
        str.remove(i);
        //удалить из массива всё о таблице
        for (int f = 0, cl = change.length(); f < cl; f++)
          if (change[f] == i)
            change.remove(f); //удалить из массива изменений всё о таблице
      }
      //Дописать если удаленная таблица была изменена, убрать ее из массива изменений
    }

    void save(bool del=0, bool all=0) //Сохранение БД и таблиц в файл
    { 
      bool fstr;
      fileb.open(str[0][0][0], ios::out);
      fileb.seekg(0, ios::beg);
      fileb << str[0][0][0] << ' ' << retstr(str.last()) << ' '; //выводим имя базы
      // и кол-во таблиц в файл базы
      for (int i = 1, str0 = str.length(); i < str0; i++)
        fileb << str[0][0][i] << ' ' << retstr(str[i].length()) << ' '; //выводим все
        // таблицы и их размеры
      if(!all) //если сохранять не все, используем массив изменений и сохраняем их
      {
	      for (int i = 0, cl = change.length(); i < cl; i++)
	      {
          int chngi=change[i];
	        file.open(str[0][0][chngi], ios::out);
	        file.seekg(0, ios::end);
	        int sl = str[0][chngi].length();
	        for (int j = 0; j < sl; j++)
	          file << str[0][chngi][j] << ' '; //выводим столбцы
	        file << '\n';
          int str2 = str[0][chngi].length();

	        for (int j = 0, str1 = str[chngi].length(); j < str1; j++)
	        {
	          for (int k = 0; k < str2; k++)
	          {
	            fstr = 0;   //флаг что это строка (с пробелами) или слово
	            if (str[chngi][j][k].length() == 0)
	              fstr = 1;
	            //заменить этот цикл на функицю find() у строки или is_str() is_word()
	            if (!fstr)
	              for (int s = 0, str3 = str[chngi][j][k].length(); s < str3; s++)
	              {
	                if (str[chngi][j][k][s] == ' ') //если нашли пробел
	                {
	                  fstr = 1; //это строка
	                  break; //выходим из цикла
	                }
	              }
	            if (!fstr)
	              file << str[change[i]][j][k] << ' '; //если не строка, выводим в файл
                // и добавляем пробел
	            else
	              file << '|' << str[change[i]][j][k] << '|' << ' '; //иначе обрамляем
                // |с двух сторон|
	          }
	          file << '\n'; //переходим на следующую строку в файле
	        }
	        file.close();
	      }
 	  }
 	  else //если сохранять всё
 	  {
		for (int i = 1, cl = str.length(); i < cl; i++)
	      {
	        file.open(str[0][0][i], ios::out);
	        file.seekg(0, ios::end);
	        int sl = str[0][i].length();
	        for (int j = 0; j < sl; j++)
	          file << str[0][i][j] << ' ';
	        file << '\n';

	        for (int j = 0, str1 = str[i].length(); j < str1; j++)
	        {
	          for (int k = 0, str2 = str[i][j].length(); k < str2; k++)
	          {
	            //длина слова
	            fstr = 0;   //флаг что строка
	            if (str[i][j][k].length() == 0)
	              fstr = 1;
	            //заменить этот цикл на функицю find() у строки или is_str() is_word()
	            if (!fstr)
	              for (int s = 0, str3 = str[i][j][k].length(); s < str3; s++)
	              {
	                if (str[i][j][k][s] == ' ')
	                {
	                  fstr = 1;
	                  break;
	                }
	              }
	            if (!fstr)
	              file << str[i][j][k] << ' ';
	            else
	              file << '|' << str[i][j][k] << '|' << ' ';
	          }
	          file << '\n';
	        }
	        file.close();
	      }
 	  }
      fileb.close();
      if(del) 
      	str.clear(); //если надо очистить массив строк, то очищаем
      change.clear(); //очищаем массив изменений
    }

    void openBase(char * name, short n=32768) //Открыть существующую базу из файла
    {
      bufsize = n;
      if (str.length() > 0)
        str.clear();
      if (change.length() > 0)
        change.clear();
      fileb.open(name);
      if (fileb.is_open()) 
      {
        fileb.seekg(0, ios::beg);
        lt();
      }
      fileb.close();
    }

    DynArr<DynString> &query(char * name, int pos) //Запрос строки из таблицы по номеру
    {
      int num = 1;
      for (int l = str[0][0].length();  num < l; num++)
      {
        if (str[0][0][num] == name)
          return str[num][pos];
      }
      throw("no such tablename");
    }

    void adcols(char * tabnam, const DynArr<DynString> &names) //Добавить столбцы
    {
      int num=1;
      bool f=false;
      for (num = 0; num <= str[0][0].last(); num++) //Находим номер таблицы
      {
        if (str[0][0][num] == tabnam)
        {f=true; break;}
      }
      if (f)
        str[0][num] += names;
    }

    void adcol(char* tabnam, const DynString &name) //Добавить 1 столбец
    {
      int num=1;
      bool f=false;
      for (num = 0; num <= str[0][0].last(); num++)
      {
        if (str[0][0][num] == tabnam)
        {
          f=true;
          break;
        }
      }
      if (f)
        str[0][num].add(name);
    }

    void adrow(char* tabnam, const DynArr<DynString> &names) //Добавить 1 строку
    {
      int num=1;
      bool f=false;
      for (int l=str[0][0].length(); num < l; num++)
      {
        if (str[0][0][num] == tabnam)
        {f=true;break;}
      }
      if (f)
        str[num].add(names);
    }

    void adrows(char* tabnam, const DynArr<DynArr<DynString> > &names) //Добавить строки
    // из массива
    {
      int num=1;
      bool f=false;
      for (int l=str[0][0].length(); num < l; num++)
      {
        if (str[0][0][num] == tabnam)
        {f=true; break;}
      }
      if (f)
        str[num] += names;
    }

    inline DynArr<DynArr<DynString> >& operator[](int i) //Вернуть i-ый элемент массива
    {
      return str[i];
    }

    inline DynArr<DynArr<DynString> >& operator[](char *name)//элемент по названию таблицы
    {
      for (int l = str[0][0].length(), i = 1; i < l; i++)
        if (str[0][0][i] == name )
          return str[i];
      return str[0];
    }


    void renameBase(char *name) //Переименовать базу
    {
      rename(str[0][0][0], name);
      str[0][0][0] = name;
    }

    void renameTable(char *oldname, char *newname) //Переименовать таблицу
    {
      for (int l = str[0][0].length(), i = 1; i < l; i++)
        if (str[0][0][i] == oldname )
        {
          str[0][0][i] = newname;
          rename(oldname, newname);
          break;
        }
    }

    inline ~DataBase(){}; //автоматический деструктор для всех полей класса
};

//Сделать проверку, если у таблиц одинаковое имя, то не загружать лишние, не создавать с одинаковым именем или не добавлять извне
//Может сделать запросы из query
//Подумать насчет размера для считывания строки.

#endif