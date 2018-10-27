template<class T> class StructBase
{
  fstream file;
  public:

  DynArr<T> data; //массив с элементами типа T, в который будут загружаться структуры

  StructBase(char * name) //конструктор сразу открывает базу, переданную по имени name
  {
     file.open(name, ios::in | ios::binary); //открыть в двоичном режиме чтения
     file.seekg(0, ios::beg); //перейти в начало файла
     int len = 0; //сколько элементов в файле
     file.read((char*)&len, sizeof(int)); //считать len из файла
     data.addempty(len); //выделить len памяти
     for (int i = 0; i < len ;) 
       file.read((char*)&data[i++], sizeof(T)); //считывать в цикле len раз информацию
       // из файла и записывать в data
     file.close(); //закрыть файл
  }

  inline  StructBase(){};

  void open(char * name) //то же самое, что и конструктор с name
  {
    file.open(name, ios::in | ios::binary);
    file.seekg(0, ios::beg);
    int len = 0;
     file.read((char*)&len, sizeof(int));
    data.addempty(len);
    for (int i = 0; i < len ;)
      file.read((char*)&data[i++], sizeof(T));
    file.close();
  }

  void save (char * name) //сохранить базу в файл
  {
    file.open(name, ios::out | ios::binary); //открыть в двоичном режиме записи
    file.seekg(0, ios::end); //переместиться в конец файла
    int len = data.length(); //получить кол-во элементов в базе
    file.write((char*)&len, sizeof(int)); //записать len в файл
    for (int i = 0; i < len;)
      file.write((char*)&data[i++], sizeof(T)); //записывать в цикле Len раз информацию из
      // data в файл
    file.close(); //закрыть файл
    data.clear(); //очистить data
  }

  void renameBase (char *name, char *lastname) //переименовать базу из name в lastname
  {
    rename(name, lastname); 
  }

 	inline DynArr<T> & operator[](int i) //можно обращаться к объекту по индексу и получать
  // элемент из data
  {
    return data[i];
  }

  const T& get(unsigned int i, char *name)
  {
    if (file.is_open())
    {
      return data[i];
    }
    else
    {
      file.open(name, ios::out | ios::binary);
      file.seekg(0, ios::beg);
      int len = 0;
      file.read((char*)&len, sizeof(int));
      if(i>len)
        throw("too big index");
      else
      {
        file.seekg(i, ios::beg);
        T ret;
        file.read((char*)&ret, sizeof(T));
        return ret;
      }
    }

  }

  inline ~StructBase()
  {
    file.close();
    //неявно вызывается и деструктор data
  }
};
