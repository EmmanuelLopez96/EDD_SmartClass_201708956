#ifndef TSKNODE_H
#define TSKNODE_H

#include <stdlib.h>

template <typename T>
class TaskNode{
    private:
        
    public:
        TaskNode(T _month, T _day, T _hour, T _carne, T _name, T _description, T _course, T _date, T _state, T _id);
        ~TaskNode();

        T month;
        T day;
        T hour;
        T carne;
        T name;
        T description;
        T course;
        T date;
        T state;
        T id;

        TaskNode *next;
        TaskNode *prev;
};

template <typename T>
TaskNode<T>::TaskNode(T _month, T _day, T _hour, T _carne, T _name, T _description, T _course, T _date, T _state, T _id){
    this->month = _month;
    this->day = _day;
    this->hour = _hour;
    this->carne = _carne;
    this->name = _name;
    this->description = _description;
    this->course = _course;
    this->date = _date;
    this->state = _state;
    this->id = _id;

    this->next = NULL;
    this->prev = NULL;
}

template <typename T>
TaskNode<T>::~TaskNode(){
}

#endif