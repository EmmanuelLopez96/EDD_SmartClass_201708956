#include <stdlib.h>
#include <string>

using namespace std;

int cont = 100;

class ErrorNode {
    private:
    
    public:
        ErrorNode(string, string);
        ~ErrorNode();

        int id;
        string type;
        string description;
        
        ErrorNode *next;
};

ErrorNode::ErrorNode(string _type, string _description){
    this->id = ++cont;
    this->type = _type;
    this->description = _description;

    this->next = NULL;
}

ErrorNode::~ErrorNode(){ }