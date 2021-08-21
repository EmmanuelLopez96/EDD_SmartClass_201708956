#include <iostream>
#include <sstream>
#include <fstream>

#include "../student/StudentList.cpp"

using namespace std;

template <typename T>
class StudentGraph{
    private:
    public:
        StudentGraph();
        void generateGraph(StudentList<T> *gcdll);
        string dirToString(StudentNode<T> *value);
        string valrToString(T value);
};

template <typename T>
StudentGraph<T>::StudentGraph(){
}

template <typename T> 
void StudentGraph<T>::generateGraph(StudentList<T> *gcdll){
    string acum = "digraph G{\n rankdir = LR; \nnode [shape=box]; \ncompound=true; \n";
    string nodo = "";
    string enlace = "";

    StudentNode<T> *tmp = gcdll->first;
    while(tmp->next != gcdll->first){
        string hex = dirToString(&*tmp); 
        nodo += "\"" + hex + "\"" + "[label=\"" + valrToString(tmp->name) + "\n" + valrToString(tmp->carne) + "\"];\n";
        enlace += "\"" +  dirToString(&*tmp) + "\" -> \"" + dirToString(&*(tmp->next)) + "\"[dir=\"both\"];\n";
        tmp = tmp->next;
    }
    
    nodo += "\"" + dirToString(&*tmp) + "\"[label=\"" + valrToString(tmp->name) + "\n" + valrToString(tmp->carne) + "\"];\n";
    enlace += "\"" +  dirToString(&*tmp) + "\" -> \"" + dirToString(&*(tmp->next)) + "\"[dir=\"both\"];\n";
    acum += nodo + enlace + "\n}\n";

    string filename("students.dot");
    fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if(!file_out.is_open()){
        cout << "\t\t\t\t\t    error - Error al abrir el archivo " << filename << endl;
    }else{
        file_out << acum << endl;
        cout << "\t\t\t\t\t    nota - Grafo de estudiantes creado correctamente" << endl;
    }

    string cmd = "dot -Tpdf students.dot -o students.pdf";
    system(cmd.c_str());    
}

template <typename T> 
string StudentGraph<T>::dirToString(StudentNode<T> *value){
    stringstream ss; 
    ss << &*value;
    return ss.str();
}

template <typename T> 
string StudentGraph<T>::valrToString(T value){
    stringstream ss; 
    ss << value;
    return ss.str();
}