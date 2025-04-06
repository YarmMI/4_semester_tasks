//Задача 3.1 (1 балл) Реализовать chunked_list<chunk_size, T> — гибрид списка и массива, который хранит элементы односвязным списком массивов длины chunk_size.
using namespace std;
#include <iostream>
template <typename type, size_t ch_size>
class ch_list{
    struct ListNode{
        ListNode* next;
        size_t arr_size;
        type* data;
        ListNode () : next(nullptr), arr_size(0), data(new type[ch_size]) {}
        ~ListNode() {
            if (data) {
                delete[] data;
            }
        }
    };
    ListNode *head;
    ListNode* tail;
    size_t ch_amount;
    public: 
    ch_list (): head(nullptr), tail(nullptr), ch_amount(0) {};
    ~ch_list() {
        while(head) {
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    void push_back(const type value) {
        if (tail == nullptr || tail->arr_size == ch_size) {
            ListNode* new_node = new ListNode();
            if (tail !=nullptr) tail->next = new_node;
            else head = new_node;
            tail = new_node;
        }
        tail->data[tail->arr_size++] = value;
        ch_amount++;
    }
    void print() {
        ListNode* tmp = head;
        while(tmp != nullptr) {
            for (size_t i=0; i< tmp->arr_size; i++) {
                cout << tmp->data[i] << " " ;
            }
            tmp = tmp->next;
            cout << endl;
        }
    }
    void pop_back() {
        if (!tail || tail->arr_size == 0) throw(0);
        if(tail->arr_size != 0) {
        tail->arr_size--;
        ch_amount--;
        return;
        }
       if(tail->arr_size == 0 && head != tail) {
        ListNode* tmp = head;
        while(tmp->next != tail) {
            tmp = tmp->next;
        }
        delete tail;
        tail = tmp;
        tail->next = nullptr;
        tail->arr_size--;
        ch_amount--;
       }
       else {
            delete tail;
            head = nullptr;
            tail = nullptr;
       }
    }
    void insert(size_t index, const type value) { 
        ListNode* tmp = head;
        ListNode* current;
        type a = type();
        for (int i=0; i < int(index/ch_size); i++) {
            tmp = tmp->next;
        }
        index = index % ch_size;
        if(tmp->arr_size < ch_size) {
            for(int i= tmp->arr_size; i> index; i--) {
                tmp->data[i] = tmp->data[i-1];
            }
            tmp->data[index] = value;
            tmp->arr_size++;
        }
        else {
            ListNode* NewNode = new ListNode;
            int new_size=0;
            for(int i= index; i<tmp->arr_size;i++) {
                NewNode->data[new_size] = tmp->data[i];
                new_size++;
            }
            tmp->data[index] = value;
            NewNode->next = tmp->next;
            NewNode->arr_size = new_size;
            tmp->arr_size = ch_size - new_size+1;
            tmp->next = NewNode;
            if(tmp == tail) tail = NewNode;
        }
        ch_amount++;
    }
    void erase( size_t index) {
        ListNode*tmp = head;
        for (int i=0; i < int(index/ch_size); i++) {
            tmp = tmp->next;
        }
        index = index % ch_size;
        if(tmp->arr_size > 1) {
            for (int i= index; i< tmp->arr_size-1; i++) {
                tmp->data[i] = tmp->data[i+1];
            }
           tmp->data[tmp->arr_size-1] = type();
            tmp->arr_size--;
            
        }
        else {
            if (tmp == head && tmp == tail) {
                delete tmp;
                head = nullptr;
                tail = nullptr;
            }
            else if (tmp == head) {
                head = head->next;
                delete tmp;
            }
            else {
                ListNode*curr = head;
                while(curr->next != tmp) {
                    curr = curr->next;
                }
                if(tmp == tail) {
                    delete tmp;
                    tail = curr;
                }
                else {
                curr->next = tmp->next;
                delete tmp;
                }
            }
            ch_amount--;
        }         
    }    
};

int main () { 
    // 1. push-back
    ch_list<int, 4> my_list;
    for (int i=0; i< 20; i++) {
        my_list.push_back(i);
    }
    my_list.print();
    cout << "--------------" << endl;
    // 2.pop-back
    //my_list.pop_back();
    //my_list.pop_back();
    ch_list <string, 2> str_list;
    str_list.push_back("abc");
    /* try {
        str_list.pop_back();
        str_list.pop_back();
    }
    catch(int x) {
        if (x == 0) {
            cout << "Null size!" << endl;
            return 1;
        }
    }*/
    str_list.push_back("cde");
    str_list.push_back("efg");
    str_list.push_back("ghk");
    str_list.pop_back();
    str_list.print();
    //3. insert
    my_list.insert(2, 65);
    //my_list.insert(9, -9);
    //my_list.insert(0, 19);
    my_list.print();
    cout << "--------------" << endl;
    //4. erase
    my_list.erase(4);
    my_list.erase(0);
    my_list.print();
}
