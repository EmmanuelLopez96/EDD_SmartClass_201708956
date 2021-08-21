/*
#ifndef HLIST_H
#define HLIST_H

#include "homework/HomeworkNode.cpp"

template <typename T>
class HomeworkList{
    private:
        
    public:
        HomeworkList();
        ~HomeworkList();

        int size;

        HomeworkNode<T> *first;
        HomeworkNode<T> *last;

        void addHomework(T _month, T _day, T _hour, T _carne, T _name, T _descritpion, T _course, T _date, T _state);
        void printHomework();
};

template <typename T>
HomeworkList<T>::HomeworkList(){
    this->first = NULL;
    this->last = NULL;
    this->size = 0;
}

template <typename T>
HomeworkList<T>::~HomeworkList(){
}

//------------------------------------------------------------- ADD HOMEWORK

template <typename T>
void HomeworkList<T>::addHomework(T _month, T _day, T _hour, T _carne, T _name, T _descritpion, T _course, T _date, T _state){
    HomeworkNode<T> *newNode = new HomeworkNode<T>(_month, _day, _hour, _carne, _name, _descritpion, _course, _date, _state, 0);

    if(this->first == NULL){
        this->first = newNode;
        this->last = newNode;
        this->size++;
        newNode->id = this->size;
    } else{
        newNode->next = NULL;
        this->last->next = newNode;
        newNode->prev = this->last;
        this->last = newNode;
        this->size++;
        newNode->id = this->size;
    }
}

template <typename T>
void HomeworkList<T>::printHomework(){
    HomeworkNode<T> *temp = this->first;
    if(temp != NULL){
        cout << "\n\n\n--- inicio ---" << endl;
        do{
            cout << temp->name << " - " << temp->id << endl;
            temp = temp->next;
        } while(temp->next == NULL);
    }
}

#endif
*/