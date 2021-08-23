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

//#include "./student/StudentList.cpp"
#include "./graph/StudentGraph.cpp"
#include "./graph/TaskGraph.cpp"

using namespace std;

StudentList<string> *cdll;
StudentGraph<string> *sg;
TaskList<string> *tkl;
TaskGraph<string> *tg;
ErrorGraph *errg;

//------------------------------------------------------------------------------------- WRITE FINAL CODE

void writeCode(){
    ofstream code;
    code.open("final code.txt", ios::out);
    if(code.fail()){
        cout << "\t\t\t\t\t    error - No se pudo abrir el archivo" << endl;
    } else{
        code << "¿Elements?\n";
        code << cdll->print();
        code << tkl->printTask();
        code << "¿Elements?\n";
        code.close();
    }
}

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
                hw[i][j][k] = new TaskNode<string>("-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "0");
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
            hw[stoi(hour)-8][stoi(day)-1][stoi(month)-7] = new TaskNode<string>(month, day, hour, carne, name, description, course, date, state, "0");
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
            tkl->addTask(vector[i]->month, vector[i]->day, vector[i]->hour, vector[i]->carne, vector[i]->name, vector[i]->description, vector[i]->course, vector[i]->date, vector[i]->state, to_string(i));
    }
}

//------------------------------------------------------------- ADD TASK

void insertTask(){
    string month, day, hour, carne, name, description, course, date, state;
    bool accepted;

    do{
        cout << "Ingresa el mes (7 - 11): ";
        cin >> month;
        if(stoi(month) < 7 || stoi(month) > 11){
        cout << "\t\t\t\t\t    error - Debes de ingresar un mes valido" << endl;
        }
    } while(stoi(month) < 7 || stoi(month) > 11);
    do{
        cout << "Ingresa el dia (1 - 30): ";
        cin >> day;
        if(stoi(day) < 1 || stoi(day) > 30){
        cout << "\t\t\t\t\t    error - Debes de ingresar un dia valido" << endl;
        } 
    } while(stoi(day) < 1 || stoi(day) > 30);
    do{
        cout << "Ingresa la hora (8 - 16): ";
        cin >> hour;
        if(stoi(hour) < 8 || stoi(hour) > 16){
        cout << "\t\t\t\t\t    error - Debes de ingresar una hora valida" << endl;
        } 
    } while(stoi(hour) < 8 || stoi(hour) > 16);
   
    int position = ((stoi(hour)-8) * 30 + (stoi(day)-1)) * 5 + (stoi(month)-7);

    TaskNode<string> *modify = tkl->test(to_string(position));

    if(tkl->test(to_string(position)) != NULL){
        cout << "\t\t\t\t\t    nota - Existe espacio disponible" << endl;
        do{
            cout << "Ingresa el carnet: ";
            cin >> carne;
            if(carne.length() != 9 || cdll->searchByCarne(carne) == NULL){
            cout << "\t\t\t\t\t    error - Debes de ingresar 9 digitos y un carnet existente" << endl;
            }
        } while(carne.length() != 9 || cdll->searchByCarne(carne) == NULL);
        cout << "Ingres el nombre: ";
        cin >> name;
        cout << "Ingresa la descripcion: ";
        cin >> description;
        cout << "Ingresa el nombre del curso: ";
        cin >> course;
        cout << "Ingresa la fecha";
        cin >> date;
        cout << "Ingresa el estado (pendiente | realizado | incumplido): "; 
        cin >> state;

        modify->month = month;
        modify->day = day;
        modify->hour = hour;
        modify->carne = carne;
        modify->name = name;
        modify->description = description;
        modify->course = course;
        modify->date = date;
        modify->state = state;
    } else{
        cout << "\t\t\t\t\t    error - No existe espacio disponible" << endl;
    }
}

//------------------------------------------------------------- MODIFY TASK MENU

void modifyTask(string data){
    int option;
    string newInfo;
    bool accepted;
    TaskNode<string> *modify = tkl->modifyTest(data);

    if(modify != NULL){
        do{
            cout << "\n\n\n********************************************" << endl;
            cout << "************** Modificar Tarea *************" << endl;
            cout << "********************************************" << endl;
            cout << "1. Carnet" << endl;   
            cout << "2. Nombre" << endl;   
            cout << "3. Descripcion" << endl;   
            cout << "4. Materia" << endl;   
            cout << "5. Fecha" << endl;   
            cout << "6. Estado" << endl;   
            cout << "7. Regresar" << endl;   
            cout << "********************************************" << endl;
            cout << "Ingresa la opcion deseada: ";
            cin >> option;
            Sleep(600);

            switch (option)
            {
            case 1:
                do{
                    cout << "Ingresa el carnet: ";
                    cin >> newInfo;
                    if(newInfo.length() != 9 || cdll->searchByCarne(newInfo) == NULL){
                        cout << "\t\t\t\t\t    error - Debes de ingresar 9 digitos y un carnet existente" << endl;
                    }
                } while(newInfo.length() != 9 || cdll->searchByCarne(newInfo) == NULL);
                modify->carne = newInfo;
                break;
            case 2:
                cout << "Ingresa el nuevo nombre: ";
                cin >> newInfo;
                modify->name = newInfo;
                break;
            case 3:
                cout << "Ingresa la nueva descripcion: ";
                cin >> newInfo;
                modify->description = newInfo;
                break;
            case 4:
                cout << "Ingresa la nueva materia: ";
                cin >> newInfo;
                modify->course = newInfo;
                break;
            case 5:
                cout << "Ingresa la nueva fecha: ";
                cin >> newInfo;
                modify->date = newInfo;
                break;
            case 6:
                cout << "Ingresa el nuevo estado: ";
                cin >> newInfo;
                modify->state = newInfo;
            case 7:
                break;
            default:
                cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
                break;
            }
        } while(option != 7);
    } else{
        cout << "\t\t\t\t\t    error - No existe tarea para editar" << endl;
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
                    cout <<  "Ingrese el nuevo numero de carnet: ";
                    cin >> newInfo;   
                    if(to_string(newInfo).length() != 9){
                        cout << "\t\t\t\t\t    error - Debes de ingresar 9 digitos" << endl;
                    }                 
                } while(to_string(newInfo).length() != 9);
                modify->carne = newInfo;                        
                break;
            case 2:
                do{
                    cout << "Ingrese el nuevo numero de DPI: ";
                    cin >> newData;
                    if(newData.length() != 13){
                        cout << "\t\t\t\t\t    error - Debes de ingresar 13 digitos" << endl;
                    }
                } while(newData.length() != 13);
                modify->dpi = newData;
                break;
            case 3:
                cout << "Ingrese el nuevo nombre: ";
                cin >> newData;
                modify->name = newData;
                break;
            case 4:
                cout << "Ingrese el nuevo nombre de carrera: ";
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
                cout << "Ingrese la nueva clave: ";
                cin >> newData;
                modify->password = newData;
                break;
            case 7:
                cout << "Ingrese el nuevo numero de creditos: ";
                cin >> newInfo;
                modify->credits = newInfo;
                break;
            case 8:
                cout << "Ingrese la nueva edad: ";
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
        cout << "2. Lista de tareas" << endl;
        cout << "3. Lista de errores" << endl;
        cout << "4. Busqueda de tarea (linealizacion)" << endl;
        cout << "5. Calcular posicion en lista" << endl;
        cout << "6. Generar codigo de salida" << endl;
        cout << "7. Regresar" << endl;   
        cout << "********************************************" << endl;
        cout << "Ingresa la opcion deseada: ";
        cin >> option;
        Sleep(600);

        switch (option){
        case 1:
            sg->generateGraph(&*cdll);            
            break;
        case 2:
            tg->generateGraph(&*tkl);
            break;
        case 3:
            errg->generateGraph(&*cdll->errorGraph());
            break;
        case 4:{
            int mes, dia, hora;
            do{
                cout << "Ingresa el mes (7 - 11): ";
                cin >> mes;
                if(mes < 7 || mes > 11){
                    cout << "\t\t\t\t\t    error - Debes de ingresar un mes valido" << endl;
                }
            } while(mes < 7 || mes > 11);
            do{
                cout << "Ingresa el dia (1 - 30): ";
                cin >> dia;
                if(dia < 1 || dia > 30){
                    cout << "\t\t\t\t\t    error - Debes de ingresar un dia valido" << endl;
                } 
            } while(dia < 1 || dia > 30);
            do{
                cout << "Ingresa la hora (8 - 16): ";
                cin >> hora;
                if(hora < 8 || hora > 16){
                    cout << "\t\t\t\t\t    error - Debes de ingresar una hora valida" << endl;
                } 
            } while(hora < 8 || hora > 16);

            int linear = ((hora-8) * 30 + (dia-1)) * 5 + (mes-7);
            
            TaskNode<string> *show = tkl->modifyTest(to_string(linear));
            if(show != NULL){
                cout << "Fecha: " << show->date << endl;
                cout << "Carnet: " << show->carne << endl;
                cout << "Nombre: " << show->name << endl;
                cout << "Estado: " << show->state << endl;
                cout << "Materia: " << show->course << endl;
                cout << "Descripcion: " << show->description << endl;
            } else{
                cout << "\t\t\t\t\t    error - No hay tarea almacenada en esta fecha" << endl;
            }
        }
            break;
        case 5:{
            int mes, dia, hora;
            do{
                cout << "Ingresa el mes (7 - 11): ";
                cin >> mes;
                if(mes < 7 || mes > 11){
                    cout << "\t\t\t\t\t    error - Debes de ingresar un mes valido" << endl;
                }
            } while(mes < 7 || mes > 11);
            do{
                cout << "Ingresa el dia (1 - 30): ";
                cin >> dia;
                if(dia < 1 || dia > 30){
                    cout << "\t\t\t\t\t    error - Debes de ingresar un dia valido" << endl;
                } 
            } while(dia < 1 || dia > 30);
            do{
                cout << "Ingresa la hora (8 - 16): ";
                cin >> hora;
                if(hora < 8 || hora > 16){
                    cout << "\t\t\t\t\t    error - Debes de ingresar una hora valida" << endl;
                } 
            } while(hora < 8 || hora > 16);

            int linear = ((hora-8) * 30 + (dia-1)) * 5 + (mes-7);

            cout << "\nrow-major -> (hora * 30 + dia) * 5 + mes" << endl;
            cout << "row-major -> ((" << hora << "-8) * 30 + (" << dia << "-1)) * 5 + (" << mes << "-7)" << endl;
            cout << "row-major -> " << linear << endl;
        }
            break;
        case 6:
                writeCode();
                break;
        case 7:
            break;
        default:
            cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
            break;
        }        
    } while(option != 7);
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
                insertTask();
            }
            break;
        case 2:
            if(selected == 0){
                cout << "Ingresa el DPI del estudiante: ";
                cin >> data;
                modifyStudent(data);
            } else{
                cout << "Ingresa el indice de la tarea: ";
                cin >> data;
                modifyTask(data);
            }
            break;
        case 3:
            if(selected == 0){
                cout << "Ingresa el DPI del estudiante: ";
                cin >> data;
                if(cdll->searchStudent(data)){
                    cdll->deleteStudent(data);
                } else {
                    cout << "\t\t\t\t\t    error - No existe estudiante con DPI " << data << endl;
                }
            } else{
                char opt;
                cout << "Ingresa el indice de la tarea: ";
                cin >> data;
                TaskNode<string> *del = tkl->modifyTest(data);
                if(del != NULL){
                    cout << "Esta seguro de eliminar la tarea " << data << "(y/n) ";
                    cin >> opt;
                    if(opt == 'y'){
                        del->month = "-1";
                        del->day = "-1";
                        del->hour = "-1";
                        del->name = "-1";
                        del->description = "-1";
                        del->carne = "-1";
                        del->date = "-1";
                        del->state = "-1";
                        del->course = "-1";       
                        cout << "\t\t\t\t\t    nota - Tarea " << data << " eliminada exitosamente" << endl;
                    }               
                } else{
                    cout << "\t\t\t\t\t    error - Ninguna tarea almacenada en el indice " << data << endl;
                }
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
            cout << "Ingrese la ruta del archivo *.cvs: ";
            cin >> studentsPath;
            readStudents(studentsPath);
            break;
        case 2:
            cout << "Ingrese la ruta del archivo *.cvs: ";
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