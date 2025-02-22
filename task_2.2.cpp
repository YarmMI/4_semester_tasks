// Задача 2.2 (1 балл). Написать на C++ шаблонный класс динамического массива Vector<T>, не используя std::vector 
//(конструкторы, деструктор, функция добавления в конец и по индексу, удаления элемента с конца и по индексу, доступа к элементу) и тестирующую программу

// 1. Как освободить память в pop_back/ удаление по индексу
// 2. Что значит добавление по индексу - выделить доп места до нового элемента?
// 3. Как сделать vector <int> vec = {...}
#include <iostream>
//#include <vector>
using namespace std;

template <typename type>
class vector {
    private:
    type* data;
    size_t size;
    size_t capacity;

    public:
    vector() : data(nullptr), size(0), capacity(0) {}
    vector (const size_t siz) :data(new type [siz]), size(siz), capacity(siz) {
        for (size_t i=0; i<size; i++) {
            data[i] = type(0);
        }
    }
    ~vector () {
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
    vector& operator = (type* array) {
        
    }
};

int main (void) {
    vector <int> vec(10);
    vector <double> v = {1,2,3,4};
    for(int i=0; i<vec.Size(); i++) {
        vec[i] = i;
    } 
    for(int i=0; i<vec.Size(); i++) {
        cout << vec[i] << endl;
    } 
    try {
    vec.pop_back();
    }
    catch(int x) {
        if (x == 0) {
            cout << "Not push_back with 0 size!" << endl;
            return 1;
        }
        if (x == 1) return 0;
    }
    cout  << endl;
    for(int i=0; i<vec.Size(); i++) {
        cout << vec[i] << endl;
    } 
    cout << endl;
    vec[15] = 76;
    cout << vec[15] << endl;
    return 0;
}

