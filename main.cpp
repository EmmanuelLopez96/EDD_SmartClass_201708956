#include <iostream>
#include <windows.h>
#include <regex>
#include <string>
#include <conio.h>
#include <locale.h>
#include <clocale>
#include <iterator>
#include <stdio.h>
#include <fstream>

#include "./student/StudentList.cpp"
#include "./graph/StudentGraph.cpp"
#include "./task/TaskList.cpp"

using namespace std;

StudentList<string> *cdll;
StudentGraph<string> *sg;
TaskList<string> *tkl;

//------------------------------------------------------------------------------------- HOMEWORK
//------------------------------------------------------------- READ HOMEWORK FILE

void readHomework(string path){
    int rows = 9;
    int cols = 30;
    int depth = 5;
    int cont = 0;
    int length = rows * cols * depth;
    TaskNode<string> *hw[rows][cols][depth];
    TaskNode<string> *vector[rows*cols*depth];

    //------------------------------------------------------------- 3D ARRAY
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            for(int k=0; k<depth; k++){
                hw[i][j][k] = new TaskNode<string>("-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1");
            }
        }
    }

    //------------------------------------------------------------- READ FILE
    ifstream file(path);
    string line;
    char delimiter = ',';
    getline(file, line);
    
    while(getline(file, line)){
        stringstream stream(line);
        string month, day, hour, carne, name,  description, course, date, state;

        getline(stream, month, delimiter);
        getline(stream, day, delimiter);
        getline(stream, hour, delimiter);
        getline(stream, carne, delimiter);
        getline(stream, name, delimiter);
        getline(stream, description, delimiter);
        getline(stream, course, delimiter);
        getline(stream, date, delimiter);
        getline(stream, state, delimiter);

        string errorText = "";

        if(cdll->searchByCarne(carne) == NULL || (stoi(hour) < 8 || stoi(hour) > 16) || (stoi(month) < 7 || stoi(month) > 11) || (stoi(day) < 1 || stoi(day) > 30)){
            if(cdll->searchByCarne(carne) == NULL){
                errorText += "Ningun estudiante corresponde a " + carne + ", ";
            }
            if(stoi(hour) < 8 || stoi(hour) > 16){
                errorText += "Hora fuera del rango establecido, ";
            }
            if(stoi(month) < 7 || stoi(month) > 11){
                errorText += "Mes fuera del rango establecido, ";
            }
            if(stoi(day) < 1 || stoi(day) > 30){
                errorText += "Dia fuera del rango establecido. ";
            }
            errorList->insert("Tarea", errorText);
        } else{
            hw[stoi(hour)-8][stoi(day)-1][stoi(month)-7] = new TaskNode<string>(month, day, hour, carne, name, description, course, date, state);
        }
    }

    //------------------------------------------------------------- ROW-MAJOR (i * cols + j) * depth + k;

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            for(int k=0; k<depth; k++){
                int position = (i * cols + j) * depth + k;
                vector[position] = hw[i][j][k];
            }
        }
    }

    for(int i=0; i<length; i++){
        if(vector[i]->name != "-1"){
            tkl->addTask(vector[i]->month, vector[i]->day, vector[i]->hour, vector[i]->carne, vector[i]->name, vector[i]->description, vector[i]->course, vector[i]->date, vector[i]->state);
        }
    }
}

//------------------------------------------------------------------------------------- STUDENTS
//------------------------------------------------------------- READ STUDENTS FILE

void readStudents(string path){
    ifstream file(path);
    string line;
    char delimiter = ',';
    getline(file, line);
    while(getline(file, line)){
        stringstream stream(line);
        string carnet, dpi, name, email, password, career, credits, age;

        getline(stream, carnet, delimiter);
        getline(stream, dpi, delimiter);
        getline(stream, name, delimiter);
        getline(stream, career, delimiter);
        getline(stream, password, delimiter);
        getline(stream, credits, delimiter);
        getline(stream, age, delimiter);
        getline(stream, email, delimiter);

        cdll->addStudent(carnet, dpi, name, career, password, credits, age, email);
    }
}

//------------------------------------------------------------- MODIFY STUDENT INFO MENU

void modifyStudent(string data){
    int option;
    int newInfo;
    bool accepted;
    string newData;
    StudentNode<string> *modify = cdll->searchStudent(data);

    if(modify != NULL){
        do{
            cout << "\n\n\n********************************************" << endl;
            cout << "*********** Modificar Estudiante ***********" << endl;
            cout << "********************************************" << endl;
            cout << "1. Carnet" << endl;   
            cout << "2. DPI" << endl;   
            cout << "3. Nombre" << endl;   
            cout << "4. Carrera" << endl;   
            cout << "5. Correo" << endl;   
            cout << "6. Clave" << endl;   
            cout << "7. Creditos" << endl;   
            cout << "8. Edad" << endl;   
            cout << "9. Regresar" << endl;   
            cout << "********************************************" << endl;
            cout << "Ingresa la opcion deseada: ";
            cin >> option;
            Sleep(600);

            switch (option)
            {
            case 1:
                do{
                    cout <<  "Ingrese el nuevo numero de carnet ";
                    cin >> newInfo;   
                    if(to_string(newInfo).length() != 9){
                        cout << "\t\t\t\t\t    error - Debes de ingresar 9 digitos" << endl;
                    }                 
                } while(to_string(newInfo).length() != 9);
                modify->carne = newInfo;                        
                break;
            case 2:
                do{
                    cout << "Ingrese el nuevo numero de DPI ";
                    cin >> newData;
                    if(newData.length() != 13){
                        cout << "\t\t\t\t\t    error - Debes de ingresar 13 digitos" << endl;
                    }
                } while(newData.length() != 13);
                modify->dpi = newData;
                break;
            case 3:
                cout << "Ingrese el nuevo nombre ";
                cin >> newData;
                modify->name = newData;
                break;
            case 4:
                cout << "Ingrese el nuevo nombre de carrera ";
                cin >> newData;
                modify->career = newData;
                break;
            case 5:            
                do{
                    cout << "Ingrese el nuevo correo ";
                    cin >> newData;
                    accepted = cdll->verifyEmail(newData);
                    if(accepted == false){
                        cout << "\t\t\t\t\t    error - Debes de seguir la ER user@dominio.[com|es|org]" << endl;
                    }
                } while(accepted != true);
                modify->email = newData;
                break;
            case 6:
                cout << "Ingrese la nueva clave ";
                cin >> newData;
                modify->password = newData;
                break;
            case 7:
                cout << "Ingrese el nuevo numero de creditos ";
                cin >> newInfo;
                modify->credits = newInfo;
                break;
            case 8:
                cout << "Ingrese la nueva edad ";
                cin >> newInfo;
                modify->age = newInfo;
                break;
            case 9:
                break;
            default:
                cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
                break;
            }
        } while(option != 9);
    } else{
        cout << "\t\t\t\t\t    error - No existe estudiante con DPI " << data << endl;        
    }  
}

//------------------------------------------------------------- ADD STUDENT

void insertStudent(){      
    string carnet, dpi, name, career, email, password, credits, age;
    bool accepted;

    do{
        cout << "Ingresa el carnet: ";
        cin >> carnet;
        if(carnet.length() != 9){
            cout << "\t\t\t\t\t    error - Debes de ingresar 9 digitos" << endl;
        }
    } while(carnet.length() != 9);
    do{
        cout << "Ingresa el DPI: ";
        cin >> dpi;
        if(dpi.length() != 13){
            cout << "\t\t\t\t\t    error - Debes de ingresar 13 digitos" << endl;
        }
    } while(dpi.length() != 13);
    cout << "Ingesa el nombre: ";
    cin >> name;
    cout << "Ingresa la carrera: ";
    cin >> career;
    do{
        cout << "Ingresa el correo: ";
        cin >> email;
        accepted = cdll->verifyEmail(email);
        if(accepted == false){
            cout << "\t\t\t\t\t    error - Debes de seguir la ER user@dominio.[com|es|org]" << endl;
        }
    } while(accepted != true);
    cout << "Ingresa la clave: ";
    cin >> password;
    cout << "Ingresa los creditos: ";
    cin >> credits;
    cout << "Ingresa la edad: ";
    cin >> age;

    cdll->addStudent(carnet, dpi, name, career, password, credits, age, email);
}

//------------------------------------------------------------- REPORTS MENU

void showReports(){
    int option;

    do{
        cout << "\n\n\n********************************************" << endl;
        cout << "***************** Reportes *****************" << endl;
        cout << "********************************************" << endl;
        cout << "1. Lista de estudiantes" << endl;
        cout << "2. Linealizacion de tareas" << endl;
        cout << "3. Lista de errores" << endl;
        cout << "4. Regresar" << endl;   
        cout << "********************************************" << endl;
        cout << "Ingresa la opcion deseada: ";
        cin >> option;
        Sleep(600);

        switch (option){
        case 1:
            //cdll->print();
            sg->generateGraph(&*cdll);            
            break;
        case 2:
            cout << "Muestra la linealizacion de tareas" << endl;
            break;
        case 3:
            cdll->printErrors();
            break;
        case 4:
            break;
        default:
            cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
            break;
        }        
    } while(option != 4);
}

//------------------------------------------------------------- EDIT INFORMATION MENU

void editInformation(int selected, string str){
    int option;
    string data;

    do {
        cout << "\n\n\n********************************************" << endl;
        cout << str << endl;    
        cout << "********************************************" << endl;
        cout << "1. Ingresar" << endl;
        cout << "2. Modificar" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Regresar" << endl;
        cout << "********************************************" << endl;
        cout << "Ingresa la opcion deseada: ";
        cin >> option;
        Sleep(600);

        switch (option) {
        case 1:
            if(selected == 0){
                insertStudent();
            } else{
                cout << "Entraste a ingresar tarea" << endl;
            }
            break;
        case 2:
            if(selected == 0){
                cout << "Ingresa el DPI del estudiante ";
                cin >> data;
                modifyStudent(data);
            } else{
                cout << "Entraste a modificar tarea" << endl;
            }
            break;
        case 3:
            if(selected == 0){
                cout << "Ingresa el DPI del estudiante ";
                cin >> data;
                if(cdll->searchStudent(data)){
                    cdll->deleteStudent(data);
                } else {
                    cout << "\t\t\t\t\t    error - No existe estudiante con DPI " << data << endl;
                }
            } else{
                cout << "Entraste a eliminar tarea" << endl;
            }
            break;
        case 4:            
            break;
        default:
            cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
            break;
        }
    } while(option != 4);
}

//------------------------------------------------------------- SELECT MENU

void manualInput(){
    int option;
    string str = "";
    do{
        cout << "\n\n\n********************************************" << endl;
        cout << "************** Ingreso Manual **************" << endl;
        cout << "********************************************" << endl;
        cout << "1. Estudiante" << endl;
        cout << "2. Tarea" << endl;
        cout << "3. Regresar" << endl;
        cout << "********************************************" << endl;
        cout << "Ingresa la opcion deseada: ";
        cin >> option;
        Sleep(600);

        switch (option){
        case 1:
            str = "************ Editar Estudiante *************";
            editInformation(0, str);
            break;
        case 2:
            str = "*************** Editar Tarea ***************";             
            editInformation(1, str);
        case 3:
            break;
        default:
            cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
            break;
        }
    } while (option != 3);
}

//------------------------------------------------------------- INT MAIN

int main(){
    system("cls");
    setlocale(LC_ALL, "");
    int option;
    string studentsPath, homeworkPath;
    cdll = new StudentList<string>();
    tkl = new TaskList<string>();
    
    do{
        cout << "\n\n\n********************************************" << endl;
        cout << "************** Menu Principal **************" << endl;
        cout << "********************************************" << endl;
        cout << "1. Carga de usuarios" << endl;
        cout << "2. Carga de tareas" << endl;
        cout << "3. Ingreso manual" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Salir" << endl;
        cout << "********************************************" << endl;
        cout << "Ingresa la opcion deseada: ";
        cin >> option;
        Sleep(600);

        switch (option){
        case 1:
            cout << "Ingrese la ruta del archivo *.cvs" << endl;
            cin >> studentsPath;
            readStudents(studentsPath);
            break;
        case 2:
            cout << "Ingrese la ruta del archivo *.cvs" << endl;
            cin >> homeworkPath;
            readHomework(homeworkPath);
            break;
        case 3:
            manualInput();
            break;
        case 4:
            showReports();
            break;
        case 5:
            cout << "Hasta luego" << endl;
            break;
        default:
            cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
            break;
        }
    } while (option != 5);
    return 0;
}