#include <stdlib.h>
#include <iostream>

#include "./ErrorNode.cpp"

class ErrorList{
    private:
    
    public:
        ErrorList();
        ~ErrorList();

        ErrorNode *first;
        ErrorNode *last;

        void insert(string, string);
        void printErrors();
};

ErrorList::ErrorList(){
    this->first = NULL;
    this->last = NULL;
}

void ErrorList::insert(string type, string description){
    ErrorNode* newNode = new ErrorNode(type, description);

    if(this->first == NULL){
        this->first = newNode;
        this->last = newNode;
        first->next = NULL;
    } else {
        this->last->next = newNode;
        newNode->next = NULL;
        this->last = newNode;
    }
}

void ErrorList::printErrors(){
    ErrorNode* temp = this->first;
    if(temp != NULL){
        do{
            cout << temp->id << " - "<< temp->type << " - " << temp->description << endl;
            temp = temp->next;
        } while(temp != NULL);
    }
}
