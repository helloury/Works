#ifndef Estrutura_h
#define Estrutura_h

using namespace std;
template<typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node() : data(nullptr), next(nullptr), prev(nullptr) {}

    static Node<T>* Nodemaker(T value) {
        Node<T>* P = new Node<T>();
        if (P) {
            P->data = value;
        }
        return P;
    }

    static void deleteNode(Node<T>* node) {
        delete node;
    }
};
//Pilha
template<typename T>
class Stack {
    Node<T>* top;
    int size;
public:
    Stack() : top(nullptr), size(0) {}

    ~Stack() {
        while (top != nullptr) {
            Node<T>* temp = top;
            top = top->next;
            Node<T>::deleteNode(temp);
        }
        size = 0;
    }
    
    bool push(T value) {
        Node<T>* P = Node<T>:: Nodemaker(value);
        if (!P) return false;

        P->next = top;
        top = P;
        size++;
        return true;
    }

    T TOP() {
        return top ? top->data : T();
    }

    void pop() {
        if (top) {
            Node<T>* temp = top;
            top = top->next;
            Node<T>::deleteNode(temp);
            size--;
        }
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return top == nullptr;
    }
};
//Lista Duplamente circular
template<typename T>
class DoublycircularList {
private:
    Node<T>* head;
    Node<T>* It;
    int size;
public:
    DoublycircularList() : head(nullptr), It(nullptr), size(0) {}

    ~DoublycircularList() {
        Delete();
    }
     
    bool insertAfter(T value) {
        Node<T>* P = Node<T>:: Nodemaker(value);
        if (!P) return false;

        if (!It) {
            head = It = P;
            P->prev = P->next = P;
        } else {
            P->next = It->next;
            P->prev = It;
            It->next = (P->next)->prev = P;
            It = P;
        }
        size++;
        return true;
    }

    bool insertBefore(T value) {
        Node<T>* P = Node<T>:: Nodemaker(value);
        if (!P) return false;

        if (!It) {
            head = It = P;
            P->prev = P->next = P;
        } else {
            P->prev = It->prev;
            P->next = It;
            It->prev = (P->prev)->next = P;
            It = P;
            if (head == P->next) {
                head = P;
            }
        }
        size++;
        return true;
    }

    bool Itmm() {
        if (It) {
            It = It->next;
            return true;
        }
        return false;
    }

    bool Itnn() {
        if (It) {
            It = It->prev;
            return true;
        }
        return false;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void moveToEnd() {
        if (head) {
            It = head->prev;
        } else {
            It = nullptr;
        }
    }

    int getSize() const {
        return size;
    }

    T getItValue() const {
        return It ? It->data : T();
    }

    void moveToStart() {
        It = head;
    }
        void Delete() {
        if (It) {
            Node<T>* temp = It;
            if (temp == head) {
                if (temp->next != temp) {
                    head = It = temp->next;
                    It->prev = temp->prev;
                    (temp->prev)->next = It;
                } else {
                    head = It = nullptr;
                }
            } else {
                It = It->next;
                (temp->next)->prev = temp->prev;
                (temp->prev)->next = temp->next;
            }
            Node<T>::deleteNode(temp);
            size--;
        }
    }
};
#endif
