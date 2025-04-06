//Задача 3.2 (2 балла) Реализовать класс Object, у которого есть операция std::string get(std::string key),
//  insert(std::string key, std::string value) с амортизированным постоянным временем работы этих методов
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Object {
    private:
    vector<string> keys;
    vector<string> values;
    public:
    hash<string> hasher;
    void insert(const string key,const string value) {
        if(keys.size() == 0) {
            keys.push_back(key);
            values.push_back(value);
            return;
        }
        for(int i=0; i<keys.size(); i++){
            if(hasher(key) == hasher(keys[i])) {
                if(key == keys[i]) {
                    values[i] = value;
                    return;
                }
            }  
        }
        keys.push_back(key);
        values.push_back(value);
    }
    string get(string key) {
        for (int i=0; i<keys.size(); i++) {
            if(hasher(key) == hasher(keys[i])){
                if(key == keys[i]) {
                    return values[i];
                }
            }
        }
        throw(0);
    }
    void print() {
        for(int i=0; i<keys.size(); i++) {
            cout << keys[i] << " -- " << values[i] << endl;
        }
    }
};

int main (void) {
    Object obj;
    obj.insert("3", "abc");
    obj.insert("2", "cde");
    obj.insert("6", "asw");
    obj.insert("8","dfa");
    obj.print();
    cout << endl;
    cout << endl;
    obj.insert("2", "uio");
    obj.insert("8", "tre");
    obj.print();
    cout << endl;
    cout << obj.get("6")<<endl;
    /*try{
        obj.get("7");
    }
    catch(int x) {
        if(x == 0){
        cout<<"Have no key" <<endl;
        return 1;
        }
    }*/
    return 0;
}
