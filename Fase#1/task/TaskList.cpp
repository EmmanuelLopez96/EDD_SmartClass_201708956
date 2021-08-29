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
        string printTask();
        void deleteTask(string _position);
        TaskNode<T>* test(string _position);
        TaskNode<T>* modifyTest(string _position);

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
string TaskList<T>::printTask(){
    TaskNode<T> *temp = this->first;
    string finalText = "";
    string delimiter = "/";
    while(temp != NULL){
        if(temp->name != "-1"){
            vector<string> words{};
            finalText += "\t¿element type=\"task\"?\n";
            finalText += "\t\t¿item Carnet = \"" + temp->carne + "\" $?\n";
            finalText += "\t\t¿item Nombre = \"" + temp->name + "\" $?\n";
            finalText += "\t\t¿item Descripcion = \"" + temp->description + "\" $?\n";
            finalText += "\t\t¿item Materia = \"" + temp->course + "\" $?\n";
            finalText += "\t\t¿item Fecha = \"" + temp->date + "\" $?\n";
            finalText += "\t\t¿item Hora = \"" + temp->hour + "\" $?\n";
            finalText += "\t\t¿item Estado = \"" + temp->state + "\" $  ?\n";
            finalText += "\t¿$element?\n"; 
        }
        temp = temp->next;
    } 
    return finalText;
}

template <typename T>
TaskNode<T>* TaskList<T>::test(string _position){
    TaskNode<T> *temp = this->first;
    while(temp != NULL){
        if(temp->id == _position && temp->name == "-1"){
            return temp;
        } 
        temp = temp->next;
    }
    return NULL;
}

template <typename T>
TaskNode<T>* TaskList<T>::modifyTest(string _position){
    TaskNode<T> *temp = this->first;
    while(temp != NULL){
        if(temp->id == _position && temp->name != "-1"){
            return temp;
        } 
        temp = temp->next;
    }
    return NULL;
}

template <typename T>
void TaskList<T>::deleteTask(string _position){
    TaskNode<T> *remove = modifyTest(_position);
    TaskNode<T> *temp = this->first;
    TaskNode<T> *temp2 = this->last;

    char option;
    cout << "Esta seguro de eliminar la tarea " << remove->id << "(y/n) ";
    cin >> option;

    if(remove != NULL){
        if(option == 'y'){
            if(remove == temp){
                this->first = remove->next;
                remove->next = NULL;
                remove->next->prev = NULL;
            } else if(remove == temp2){
                this->last = remove->prev;
                remove->prev->next = NULL;
                remove->prev = NULL;
            } else{
                remove->prev->next = remove->next;
                remove->next->prev = remove->prev; 
                remove->prev = NULL;
                remove->next = NULL;
            }
            cout << "\t\t\t\t\t    nota - Tarea " << _position << " eliminada exitosamente" << endl;
        }       
    } else{
        cout << "\t\t\t\t\t    error - Ninguna tarea almacenada en el indice " << _position << endl;
    }
}