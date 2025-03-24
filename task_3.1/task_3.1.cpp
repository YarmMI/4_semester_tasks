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
            for (size_t i=0; i<tmp->arr_size; i++) {
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
    void insert(size_t index, const type value) { // реализовать вставку и удаление без глобального сдвига, а //только если удаление и элемент x не последний, то удаляем x остальные элементы этого чанка сдвигаем ///наверх, остальные чанки вообще не трогаем, вставка если переполнился нынешний чанк, то создаём новый чанк и //там вставляем последний элемент предыдущего чанка, остальыне в новом - 0
        //методы insert и erase за O(1)
        ListNode* tmp = head;
        ListNode* current;
        for (int i=0; i < int(index/ch_size); i++) {
            tmp = tmp->next;
        }
        index = index % ch_size;
        type a = tmp->data[ch_size-1];
        type b;
        for (size_t i=ch_size-1; i!= index; i--) {
            tmp->data[i] = tmp->data[i-1];
        }
        tmp->data[index] = value;   
        current = tmp->next;
        while(current != tail) {
            for (int i=ch_size-1;i!= 0; i--) {
                if (i == ch_size-1) b = current->data[i];
                current->data[i] = current->data[i-1];
            }
            current->data[0] = a;
            a = b;
            current = current->next;
        }
        if(tail->arr_size < ch_size) {
            tail->arr_size++;
            for (int i = tail->arr_size-1; i !=0; i--) {
                tail->data[i] = tail->data[i-1];
            }
            tail->data[0] = a;
            
        }
        else {
            ListNode* new_Node = new ListNode();
            b = tail->data[ch_size-1];
            for (int i=ch_size-1; i !=0; i--) {
                tail->data[i] = tail->data[i-1];
            }
            tail->data[0] = a;
            new_Node->data[0] = b;
            tail->next = new_Node;
            new_Node->arr_size++;
            tail = new_Node;
            tail->next = nullptr;
        }
        ch_amount++; 
        
    }
    void erase( size_t index) {
        ListNode*tmp = head;
        for (int i=0; i < int(index/ch_size); i++) {
            tmp = tmp->next;
        }
        index = index % ch_size;
        ListNode* current = tmp;
        ListNode*temp = nullptr;
        while (current != nullptr) {
            if (current == tail && current->arr_size != 1) {
                temp->data[temp->arr_size-1] = current->data[0];  
                for (size_t i=0; i< current->arr_size; i++) {
                    current->data[i] = current->data[i+1];
                }
                current->arr_size--;
                break;
            }
            else if (current == tail && current->arr_size == 1) {
                temp->data[temp->arr_size-1] = current->data[0];
                current->arr_size--;
                current = nullptr;
                tail = temp;
                break;
            }
            if (current == tmp && current->next != nullptr) {
                for (size_t i= index; i < current->arr_size-1; i++) {
                    current->data[i] = current->data[i+1];
                }
                temp = current;
                current = current->next;
                continue;
            }
            else if (current == tmp && current->next == nullptr) {
                for (size_t i= index; i < current->arr_size-1; i++) {
                    current->data[i] = current->data[i+1];
                }
                current->arr_size--;
                break;
            }
            temp->data[temp->arr_size-1] = current->data[0];
            temp = current;
            for (size_t i=0; i<current->arr_size; i++) {
                current->data[i] = current->data[i+1];
            }
            current = current->next;
        }
    }    
};

int main () { 
    // 1. push-back
    ch_list<int, 3> my_list;
    for (int i=0; i< 20; i++) {
        my_list.push_back(i);
    }
    my_list.print();
    cout << "--------------" << endl;
    // 2.pop-back
    my_list.pop_back();
    my_list.pop_back();
    ch_list <string, 4> str_list;
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
    my_list.insert(6, 65);
    my_list.insert(9, -9);
    my_list.insert(13, 21);
    my_list.insert(0, 19);
    my_list.print();
    cout << "--------------" << endl;
    //4. erase
    my_list.erase(4);
    my_list.erase(0);
    my_list.print();
}
