//Задача 3.2 (2 балла) Реализовать класс Object, у которого есть операция std::string get(std::string key),
//  insert(std::string key, std::string value) с амортизированным постоянным временем работы этих методов
#include <iostream>
#include<unordered_map>
using namespace std;

class Object{
    private:
    std::unordered_map<string, string> table;
    public:
    void insert(const string key, const string value) {
        table[key] = value;
    }
    string get(const string key) const{
        auto pair = table.find(key);
        if(pair != table.end()) {
            return pair->second;
        }
        else {
            throw(0);
            return "\0";
        }
    }

};

int main (void) {
    Object obj;
    obj.insert("1", "First");
    obj.insert("2", "Second");
    obj.insert("3", "Third");
    obj.insert("4", "Fourth");
    obj.insert("5", "Fifth");

    cout<< obj.get("3") << endl;
    obj.insert("3", "New value");
    cout<< obj.get("3") << endl;
    /*try{
        obj.get("10");
    }
    catch(int x) {
        if(x == 0) {
            cout << "No key in table" << endl;
            return 1;
        }
    }*/
    return 0;
    
}
