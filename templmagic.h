template<bool B, class T = void>
struct enable {};

template<class T>
struct enable<true, T> { typedef T type; };

template<bool B, class T = void>
struct disable {};

template<class T>
struct disable<false, T> { typedef T type; };