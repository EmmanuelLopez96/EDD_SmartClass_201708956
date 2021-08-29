#include <iostream>
#include <sstream>
#include <fstream>

#include "../student/StudentList.cpp"

using namespace std;

int counting = 0;
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
    counting++; 

    StudentNode<T> *tmp = gcdll->first;
    while(tmp->next != gcdll->first){
        string hex = dirToString(&*tmp);         
        nodo += "\"" + hex + "\"" + "[label=\"" + valrToString(tmp->carne) + "\n" + valrToString(tmp->dpi) + "\n" + valrToString(tmp->name) +
        "\n" + valrToString(tmp->career) + "\n" + valrToString(tmp->email) + "\n" + valrToString(tmp->password) + "\n" + valrToString(tmp->age) +
        "\n" + valrToString(tmp->credits) +"\"];\n";
        string currLink = dirToString(&*tmp);
        string nextLink = dirToString(&*(tmp->next));
        enlace += "\"" + currLink + "\" -> \"" + nextLink + "\"[dir=\"right\"];\n";
        enlace += "\"" + nextLink + "\" -> \"" + currLink + "\"[dir=\"left\"];\n";
        tmp = tmp->next;
    }
    
    nodo += "\"" + dirToString(&*tmp) + "\"[label=\"" + valrToString(tmp->carne) + "\n" + valrToString(tmp->dpi) + "\n" + valrToString(tmp->name) +
        "\n" + valrToString(tmp->career) + "\n" + valrToString(tmp->email) + "\n" + valrToString(tmp->password) + "\n" + valrToString(tmp->age) +
        "\n" + valrToString(tmp->credits) +"\"];\n";
    string currLink = dirToString(&*tmp);
    string nextLink = dirToString(&*(tmp->next));
    enlace += "\"" + currLink + "\" -> \"" + nextLink + "\"[dir=\"right\"];\n";
    enlace += "\"" +  nextLink + "\" -> \"" + currLink + "\"[dir=\"left\"];\n";
    acum += nodo + enlace + "\n}\n";

    string filename("students" + to_string(counting) + ".dot");
    fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if(!file_out.is_open()){
        cout << "\t\t\t\t\t    error - Error al abrir el archivo " << filename << endl;
    }else{
        file_out << acum << endl;
        cout << "\t\t\t\t\t    nota - Grafo de estudiantes creado correctamente" << endl;
    }

    string cmd = "dot -Tsvg students" + to_string(counting) + ".dot -o students" + to_string(counting) + ".svg";
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