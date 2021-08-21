#include <stdlib.h>
#include <iostream>

#include "../task/TaskNode.cpp"

template <typename T>
class TaskList{
    private:
        
    public:
        TaskNode<T> *first;
        TaskNode<T> *last;
        
        void addTask(T _month, T _day, T _hour, T _carne, T _name, T _descritpion, T _course, T _date, T _state, T _id);
        void printTask();
        
        TaskList();
        ~TaskList();
};

template <typename T>
TaskList<T>::TaskList(){
    this->first = NULL;
    this->last = NULL;
}

template <typename T>
TaskList<T>::~TaskList(){
}

//------------------------------------------------------------- ADD TASK

template <typename T>
void TaskList<T>::addTask(T _month, T _day, T _hour, T _carne, T _name, T _descritpion, T _course, T _date, T _state, T _id){
    TaskNode<T> *newNode = new TaskNode<T>(_month, _day, _hour, _carne, _name, _descritpion, _course, _date, _state, _id);

        if(this->first == NULL){
            this->first = newNode;
            this->last = newNode;
            newNode->next = NULL;            
        }else{
            newNode->prev = this->last;
            newNode->next = NULL;
            this->last->next = newNode;
            this->last = newNode;
        }
}

template <typename T>
void TaskList<T>::printTask(){
    TaskNode<T> *temp = this->first;
    cout << "\n\n\n--- inicio ---" << endl;
    while(temp != NULL){
        cout << temp->name << " - " << temp->date << " <-> ";
        temp = temp->next;
    } 
    cout << "\n\n\n--- final ---" << endl;    
}