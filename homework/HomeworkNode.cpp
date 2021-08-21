#ifndef STUDENTH_H
#define STUDENTH_H

#include <stdlib.h>

template <typename T>
class HomeworkNode{
    private:
        
    public:
        HomeworkNode(T _month, T _day, T _hour, T _carne, T _name, T _description, T _course, T _date, T _state);
        ~HomeworkNode();

        T month;
        T day;
        T hour;
        T carne;
        T name;
        T description;
        T course;
        T date;
        T state;

        HomeworkNode *next;
        HomeworkNode *prev;
};

template <typename T>
HomeworkNode<T>::HomeworkNode(T _month, T _day, T _hour, T _carne, T _name, T _description, T _course, T _date, T _state){
    this->month = _month;
    this->day = _day;
    this->hour = _hour;
    this->carne = _carne;
    this->name = _name;
    this->description = _description;
    this->course = _course;
    this->date = _date;
    this->state = _state;

    this->next = NULL;
    this->prev = NULL;
}

template <typename T>
HomeworkNode<T>::~HomeworkNode(){
}

#endif