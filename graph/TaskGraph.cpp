#include <iostream>
#include <sstream>
#include <fstream>

#include "../task/TaskList.cpp"

using namespace std;

template <typename T>
class TaskGraph{
    private:
        
    public:
        TaskGraph();
        ~TaskGraph();
        
        void generateGraph(TaskList<T> *gtkl);
        string dirToString(TaskNode<T> *value);
        string valrToString(T value);
};

template <typename T>
TaskGraph<T>::TaskGraph(){
}

template <typename T>
TaskGraph<T>::~TaskGraph(){
}

template <typename T>
void TaskGraph<T>::generateGraph(TaskList<T> *gtkl){
    string acum = "digraph G{\n rankdir = LR; \nnode [shape=box]; \ncompound=true; \n";
    string nodo = "";
    string enlace = "";

    TaskNode<T> *temp = gtkl->first;
    while(temp->next != NULL){
        string hex = dirToString(&*temp);
        if(valrToString(temp->name) == "-1"){
            nodo += "\"" + hex + "\"" + "[label=\"Sin tarea\n\n--" + valrToString(temp->id) + "--\"];\n";
        } else{
            nodo += "\"" + hex + "\"" + "[label=\"" + valrToString(temp->month) + "\n" + valrToString(temp->day) + "\n" + valrToString(temp->hour) + 
            "\n" + valrToString(temp->carne) + "\n" + valrToString(temp->name) + "\n" + valrToString(temp->description) + "\n" + valrToString(temp->course) +
            "\n" + valrToString(temp->date) + "\n" + valrToString(temp->state) + "\n\n--" + valrToString(temp->id) + "--\"];\n";
        }
        string nextLink = dirToString(&*(temp->next));
        string currLink = dirToString(&*temp);
        enlace += "\"" + currLink + "\" -> \"" + nextLink + "\"[dir=\"rigth\"];\n";
        enlace += "\"" +  nextLink + "\" -> \"" + currLink + "\"[dir=\"left\"];\n";
        temp = temp->next;
    }

    if(valrToString(temp->name) == "-1"){
        nodo += "\"" + dirToString(&*temp) + "\"[label=\"Sin tarea\n\n--" + valrToString(temp->id) + "--\"];\n";   
    } else{
        nodo += "\"" + dirToString(&*temp) + "\"[label=\"" + valrToString(temp->month) + "\n" + valrToString(temp->day) + "\n" + valrToString(temp->hour) + 
        "\n" + valrToString(temp->carne) + "\n" + valrToString(temp->name) + "\n" + valrToString(temp->description) + "\n" + valrToString(temp->course) +
        "\n" + valrToString(temp->date) + "\n" + valrToString(temp->state) + "\n--" + valrToString(temp->id) + "--\"];\n";
    }
    acum += nodo + enlace + "\n}\n";
    
    string filename("tasks.dot");
    fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if(!file_out.is_open()){
        cout << "\t\t\t\t\t    error - Error al abrir el archivo " << filename << endl;
    } else {
        file_out << acum << endl;
        cout << "\t\t\t\t\t    nota - Grafo de tareas creado correctamente" << endl;
    }

    string cmd = "dot -Tsvg tasks.dot -o tasks.svg";
    system(cmd.c_str());
}

template <typename T> 
string TaskGraph<T>::dirToString(TaskNode<T> *value){
    stringstream ss; 
    ss << &*value;
    return ss.str();
}

template <typename T> 
string TaskGraph<T>::valrToString(T value){
    stringstream ss; 
    ss << value;
    return ss.str();
}