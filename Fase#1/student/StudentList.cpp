#ifndef SLIST_H
#define SLIST_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <regex>
#include <clocale>

#include "./StudentNode.cpp"
#include "../graph/ErrorGraph.cpp"
//#include "../error/ErrorList.cpp"

template <typename T>
class StudentList{
    private:

    public:
        StudentNode<T> *first;
        StudentNode<T> *last;
        
        int size;
        
        void addStudent(T _carne, T _dpi, T _name, T _career, T _password, T _credits, T _age, T _email);
        void deleteStudent(string _dpi);
        void printErrors();
        string print();
        bool verifyEmail(const string& email);
        ErrorList *errorGraph();
        StudentNode<T>* searchStudent(string _dpi); 
        StudentNode<T>* searchByCarne(string _carne);
        
        StudentList();
        ~StudentList();
};

//------------------------------------------------------------- CONSTRUCTOR | DESTRUCTOR

template <typename T>
StudentList<T>::StudentList()
{
    this->first = NULL;
    this->last = NULL;
    this->size = 0;
}

template <typename T> 
StudentList<T>::~StudentList(){ }

//------------------------------------------------------------- EMAIL VERIFICATION

template <typename T>
bool StudentList<T>::verifyEmail(const string& email){
    const regex expReg("(\\w+)(\\.|_)?(\\w*)@(\\w+)\\.(com|es|org)");
    return regex_match(email, expReg);
}

//------------------------------------------------------------- ADD STUDENT

ErrorList *errorList = new ErrorList();
template <typename T> 
void StudentList<T>::addStudent(T _carne, T _dpi, T _name, T _career, T _password, T _credits, T _age, T _email){
    StudentNode<T> *newNode = new StudentNode<T>(_carne, _dpi, _name, _career, _password, _credits, _age, _email, 0);
    string errorText = "";

    if(_carne.length() != 9 || _dpi.length() != 13 || verifyEmail(_email) == false ){
        if(_carne.length() != 9){
            errorText += "Carnet no cumple con los digitos establecidos, ";
        }
        if(_dpi.length() != 13){
            errorText += "DPI no cumple con los digitos establecidos, ";
        }
        if(verifyEmail(_email) == false){
            errorText += "Email no cumple con la expresion regular. ";
        }
        errorList->insert("Estudiante", errorText);
        cout << "\t\t\t\t\t    error - " << errorText << endl;
    } else{
        if(this->first == NULL){
            this->first = newNode;
            this->last = newNode;
            this->size++;
            newNode->id = this->size;
        }else{
            newNode->next = this->first;
            first->prev = newNode;

            newNode->prev = this->last;
            this->last->next = newNode;

            this->last = newNode;
            this->size++;
            newNode->id = this->size;
        }
    }
}

//------------------------------------------------------------- SEARCH STUDENT

template <typename T>
StudentNode<T>* StudentList<T>::searchStudent(string _dpi){
    StudentNode<T>* temp = this->first;
    if(temp != NULL){
        do{
            if(temp->dpi == _dpi){
                return temp;
            } 
            temp = temp->next;
        } while(temp != first);
    } else{
        cout << "\t\t\t\t\t    error - Ningun estudiante registrado con el DPI " << _dpi << endl;
    }
    return NULL;
}

//------------------------------------------------------------- SEARCH STUDENT BY CARNE

template <typename T>
StudentNode<T>* StudentList<T>::searchByCarne(string _carne){
    StudentNode<T>* temp = this->first;
    if(temp != NULL){
        do{
            if(temp->carne == _carne){
                return temp;
            } 
            temp = temp->next;
        } while(temp != first);
    } else{
        cout << "\t\t\t\t\t    error - Ningun estudiante registrado con el DPI " << _carne << endl;
    }
    return NULL;    
}

//------------------------------------------------------------- DELETE STUDENT

template <typename T>
void StudentList<T>::deleteStudent(string dpi){
    StudentNode<T> *remove = searchStudent(dpi);
    StudentNode<T> *temp = this->first;
    StudentNode<T> *temp2 = this->last;

    char option;
    cout << "Esta seguro de eliminar al estudiante " << remove->name << " (y/n): ";
    cin >> option;

    if(remove != NULL){
        if(option == 'y'){
            if(remove == temp){
                remove->prev->next = remove->next;
                remove->next->prev = remove->prev;
                this->first = remove->next;
            } else if(remove == last){
                remove->prev->next = this->first;
                this->last = remove;
                this->first->prev = this->last;
            } else{
                remove->prev->next = remove->next;
                remove->next->prev = remove->prev;
            }
            cout << "\t\t\t\t\t    nota - Estudiante con DPI " << dpi << " eliminado exitosamente" << endl;
        }
    } else{
        cout << "\t\t\t\t\t    error - Ningun estudiante registrado con carnet: " << dpi << endl;
    }
}

//------------------------------------------------------------- PRINT LIST

template <typename T>
string StudentList<T>::print(){
    StudentNode<T> *temp = this->first;
    if(temp != NULL){
        string finalText = "";
        do{
            finalText += "\t¿element type=\"user\"?\n";
            finalText += "\t\t¿item Carnet = \"" + temp->carne + "\" $?\n";
            finalText += "\t\t¿item DPI = \"" + temp->dpi + "\" $?\n";
            finalText += "\t\t¿item Nombre = \"" + temp->name + "\" $?\n";
            finalText += "\t\t¿item Carrera = \"" + temp->career + "\" $?\n";
            finalText += "\t\t¿item Password = \"" + temp->password + "\" $?\n";
            finalText += "\t\t¿item Creditos = \"" + temp->credits + "\" $?\n";
            finalText += "\t\t¿item Edad = \"" + temp->age + "\" $?\n";
            finalText += "\t¿$element\n";
            temp = temp->next;
            
        } while(temp != first);
        return finalText;
    } else{
        cout << "Lista vacia" << endl;
    }
    return "empty string";
}

//------------------------------------------------------------- PRINT ERRORS

template <typename T>
void StudentList<T>::printErrors(){
    errorList->printErrors();   
}

template <typename T>
ErrorList* StudentList<T>::errorGraph(){
    return errorList;
}

#endif 