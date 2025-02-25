// Задача 2.2 (1 балл). Написать на C++ шаблонный класс динамического массива Vector<T>, не используя std::vector 
//(конструкторы, деструктор, функция добавления в конец и по индексу, удаления элемента с конца и по индексу, доступа к элементу) и тестирующую программу
// Задача 2.5 (+0.5 балла к задаче 2.2): сделать так, чтобы работал инициализатор

#include <iostream>
#include <initializer_list>
//#include <vector>
using namespace std;

template <typename type>
class Vector {
    private:
    type* data;
    size_t size;
    size_t capacity;

    public:
    Vector() : data(nullptr), size(0), capacity(0) {}
    Vector (const size_t siz) :data(new type [siz]), size(siz), capacity(siz) {
        for (size_t i=0; i<size; i++) {
            data[i] = type(0);
        }
    }
    Vector (initializer_list<type> arr) : data(new type [arr.size()]), size(arr.size()), capacity(arr.size()) {
        int i=0;
        for (type elem : arr) {
            data[i] = elem;
            i++;
        }
    }
    ~Vector () {
        if (size > 0) {
            delete [] data;
        }
    }
    const type operator [] (const size_t index) const {
        return data[index];
    }
    type & operator [](const size_t index) {
        return data[index];
    }
    size_t Size() {
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
        if (size == 1) throw (1);
        size--;
    }
   void insert(int index, type elem) {
    if (size+1 >= capacity)  {
        capacity *= 2;
            type* tmp = new type [capacity];
            for (int i=0; i<size; i++) {
                tmp[i] = data[i];
            }
            delete [] data;
            data = tmp;
    }
    for(int i=size-1; i != index-1; i--) {
        data[i+1] = data[i];
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

};

int main (void) {
    // 1) Проверка initializer_list
    Vector <double> my_vec = {1.2, -132.89, 0.7631, 12473.2134,1,3,4};
    cout << "Элемент вектора по равенству под номером 3 = " << my_vec[2] << endl;
    cout << endl;
    // 2) Доступ к элементу
    Vector <int> vec = {1,2,3,4,5,6,7,8,9,10};
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
    vec.insert(6, 100);
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
        if (x==1) {
            return 0;
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
}   

