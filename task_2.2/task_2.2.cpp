// Задача 2.2 (1 балл). Написать на C++ шаблонный класс динамического массива Vector<T>, не используя std::vector 
//(конструкторы, деструктор, функция добавления в конец и по индексу, удаления элемента с конца и по индексу, доступа к элементу) и тестирующую программу
// Задача 2.4 (1 балл, требует 2.2). Написать классы итераторов для класса Vector, определить функции begin и end и показать, что с ними работает range-based for loop.
// Задача 2.5 (+0.5 балла к задаче 2.2): сделать так, чтобы работал инициализатор

#include <iostream>
#include <initializer_list>
#include <string>
using namespace std;

template <typename type>
class Vector {
    private:
    type* data;
    int size;
    int capacity;

    public:
    Vector() : data(nullptr), size(0), capacity(0) {
        cout << "Вызван стандартный конструктор" << endl;
    } // как именно он работает
    Vector (const size_t siz) :data(new type [siz]), size(siz), capacity(siz) {
        cout << "Вызван специальный конструктор" << endl; 
        for (size_t i=0; i<size; i++) {
            data[i] = type();
        }
        cout << endl;
    }
    Vector (initializer_list<type> arr) : data(new type [arr.size()]), size(arr.size()), capacity(arr.size()) {
        int i=0;
        for (type elem : arr) {
            data[i] = elem;
            i++;
        }
    }
    ~Vector () {
        if (capacity > 0) {
            cout << "destructor: ";
            for(int i =0; i< size; i++) {
                cout << data[i] <<  " ";
            }
            cout << endl; 
            delete [] data;
        }
    }
    const type operator [] (const size_t index) const {
        return data[index];
    }
    type & operator [](const size_t index) {
        return data[index];
    }
    int Size() {
        return size;
    }
    void push_back (const type elem) {
        if (capacity == 0) {
            capacity =1;
            data = new type[1];
        }
        if (size >= capacity) {
            capacity *= 2;
            type* tmp = new type [capacity];
            for (int i=0; i<size; i++) {
                tmp[i] = data[i];
            }
            delete [] data;
            data = tmp;
        }
        data[size] = elem;
        size ++;
    }
    void pop_back () {
        if (size == 0) throw (0);
        size--;
    }
   void insert(int index, type elem) { 
    if (size+1 >= capacity)  {
        capacity *= 2;
            type* tmp = new type [capacity];
            for (int i=0; i<index; i++) {
                tmp[i] = data[i];
            }
            tmp[index] = elem;
            for (int i=index+1; i<size+1; i++) {
                tmp[i] = data[i-1];
            }
            delete [] data;
            data = tmp;
            size++;
            return;
    }
    for(int i=size; i > index; i--) {
        data[i] = data[i-1];
    }
    data[index] = elem;
    size++;
   }
   void erase(int index) {
    for(int i=index-1; i<size-1; i++) {
        data[i] = data[i+1];
    }
    size--;
   }

   class Iterator {
    private:
    type *ptr;
    public:
    Iterator(type* data = nullptr) : ptr(data) {}
    Iterator& operator++() {
        ++ptr;
        return*this;
    }
    bool operator != (const Iterator& other)const {
        return this->ptr != other.ptr;
    }
    type& operator* () {
        return *ptr;
    }
   };
   Iterator begin() {
    return Iterator(data);
   }
   Iterator end () {
    return Iterator(data+size);
   }

};

int main (void) {
    // 1) Проверка initializer_list
    Vector <double> my_vec = {1.2, -132.89, 0.7631, 12473.2134,1,3,4};
    cout << "Элемент вектора по равенству под номером 3 = " << my_vec[2] << endl;
    cout << endl;
    // 2) Доступ к элементу
    Vector <int> vec = {1,2,3,4,5,6,7,8};
    cout << "vec[3] before change = " << vec[3] << endl;
    vec[3] = 18;
    cout << "vec[3] after change = " << vec[3] << endl;
    cout << endl;
    // 3) Добавление в конец 
    cout << "Размер вектора до добавления в конец = " << vec.Size() << endl;
    for (int i=0;i<vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    vec.push_back(85);
    cout << "Размер вектора после добавления в конец = " << vec.Size() << endl;
    for (int i=0;i<vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    cout << endl;
    // 4) Добавление по индексу 
    cout << "Вектор до добавления - " ;
    for (int i=0; i<vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    vec.insert(0, 100);
    cout << "Вектор после добавления - " ;
    for (int i=0; i<vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    cout << endl;
    // 5) Удаление из конца
    cout << "Размер вектора до удаления из конца = " << vec.Size() << endl;
    for (int i=0;i<vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    vec.pop_back();
    cout << "Размер вектора после удаления из конца = " << vec.Size() << endl;
    for (int i=0;i<vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    cout << endl;
    // 5.1) Случаи когда size = 0 или 1
    Vector <char> vec_er = {4,2};
    try {
        vec_er.pop_back();
    }
    catch(int x) {
        if (x==0) {
            cout << "Cant delete in zero size" << endl;
            return 1;
        }
    }
    cout << endl;
    // 6) Удаление по индексу 
    cout << "Вектор до удаления - " ;
    for (int i=0; i<vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    vec.erase(2);
    cout << "Вектор после удаления - " ;
    for (int i=0; i<vec.Size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    cout << endl;
    //7.Подаём строку в конструктор
    Vector <char> vec_ch;
    Vector <string> (5);
    cout << endl;
    cout << endl;

    //8 Итераторы
    Vector <string> vec_it = {"one", "two", "three", "four", "five"};
    cout<< "Цикл for с итераторами: ";
    for (auto x = vec_it.begin();x != vec_it.end();++x) {
        cout << *x << " ";
    }
    cout << endl;
    cout <<endl;
    cout << "range-based-for: ";
    Vector <double> vec_i2 = {14,15,12.1140,9.148,-84.012};
    for(auto y: vec_i2) {
        cout << y<< " ";
    }
    cout << endl;
    cout <<endl;

    return 0;
}   

