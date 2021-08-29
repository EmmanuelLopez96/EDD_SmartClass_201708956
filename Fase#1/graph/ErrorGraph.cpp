#include <iostream>
#include <sstream>
#include <fstream>

#include "../error/ErrorList.cpp"

using namespace std;

class ErrorGraph{
    private:
        
    public:        
        ErrorGraph();
        ~ErrorGraph();
        
        void generateGraph(ErrorList *gerrl);
        string dirToString(ErrorNode *value);
        string valrToString(string value);
};

ErrorGraph::ErrorGraph(){ }

ErrorGraph::~ErrorGraph(){ }

void ErrorGraph::generateGraph(ErrorList *gerrl){
    string acum = "digraph G{\n rankdir = LR; \nnode [shape=box]; \ncompound=true; \n";
    string nodo = "";
    string enlace = "";

    ErrorNode *tmp = gerrl->first;
    while(tmp->next != NULL){
        string hex = dirToString(&*tmp);         
        nodo += "\"" + hex + "\"" + "[label=\"" + valrToString(tmp->type) + "\n" + valrToString(tmp->description) + "\n\n--" + valrToString(tmp->id) + "--\"];\n";
        string currLink = dirToString(&*tmp);
        string nextLink = dirToString(&*(tmp->next));
        enlace += "\"" + currLink + "\" -> \"" + nextLink + "\"[dir=\"right\"];\n";
        tmp = tmp->next;
    }    

    nodo += "\"" + dirToString(&*tmp) + "\"[label=\"" + valrToString(tmp->type) + "\n" + valrToString(tmp->description) + "\n\n--" + valrToString(tmp->id) + "--\"];\n";
    acum += nodo + enlace + "\n}\n";

    string filename("errors.dot");
    fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if(!file_out.is_open()){
        cout << "\t\t\t\t\t    error - Error al abrir el archivo " << filename << endl;
    } else{
        file_out << acum << endl;
        cout << "\t\t\t\t\t    nota - Grafo de errores creado correctamente" << endl;
    }

    string cmd = "dot -Tsvg errors.dot -o errors.svg";
    system(cmd.c_str());   

}

string ErrorGraph::dirToString(ErrorNode *value){
    stringstream ss; 
    ss << &*value;
    return ss.str();
}

string ErrorGraph::valrToString(string value){
    stringstream ss; 
    ss << value;
    return ss.str();
}