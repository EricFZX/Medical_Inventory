#ifndef MEDICAMENTO_GEHERAL_H
#define MEDICAMENTO_GEHERAL_H

//Librerias
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

//Acronimos STD
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ios;
using std::ifstream;
using std::setw;


class MEDICAMENTO_GENERAL {

private:
    //Atributos
    string Tipo_MED;
    string Nombre_MED;
    string Fecha_MED;
    int Codigo_MED;
    int Cantidad_MED;
    double Precio_MED;
protected:
    //Archivos
    ofstream escrbir_archivo;
    ifstream leer_archivo;
public:
    //Cosntructor
    MEDICAMENTO_GENERAL();
    MEDICAMENTO_GENERAL(string,string,string,int,double,int);
    //Metodos
    void MENU_FARMACIA();
    void IMPRIMIR_MEDICAMENTOS();
    //Metodos Crud
    void CREAR_MEDICAMENTO();
    void BUSCAR_MEDICAMENTO();
    void ELIMINAR_MEDICAMENTO();
    void ACTUALIZAR_MEDICAMENTO();
    bool VALIDAR_CODIGO(int);
    //Getters and Setters
    string getTipo();
    string getNombre();
    string getFecha();
    int getCantidad();
    double getPrecio();
    int getCodigo();

    void setTipo(string);
    void setNombre(string);
    void setFecha(string);
    void setCantidad(int);
    void setPrecio(double);
    void setCodigo(int);

};
#endif