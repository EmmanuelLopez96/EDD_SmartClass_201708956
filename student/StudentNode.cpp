#ifndef SNODO_H
#define SNODO_H

#include <stdlib.h>

template <typename T>
class StudentNode{
    private:

    public:
        StudentNode(T _carne, T _dpi, T _name, T _career, T _password, T _credits, T _age, T _email, int _id);
        ~StudentNode();
        
        T carne;
        T dpi;
        T name;
        T career;
        T password;
        T credits;
        T age;
        T email;
        int id;

        StudentNode *next; 
        StudentNode *prev;
};

template <typename T>
StudentNode<T>::StudentNode(T _carne, T _dpi, T _name, T _career, T _password, T _credits, T _age, T _email, int _id){
    this->carne = _carne;
    this->dpi = _dpi;
    this->name = _name;
    this->career = _career;
    this->password = _password;
    this->credits = _credits;
    this->age = _age;
    this->email = _email;
    this->id = _id;
    
    this->next = NULL;
    this->prev = NULL;
}

template <typename T>
StudentNode<T>::~StudentNode(){
}

#endif