#ifndef  VENTAS_PROCESO_H
#define VENTAS_PROCESO_H
#include "MEDICAMENTO_GENERAL.h"
#include <vector>

using std::vector;

class VENTAS_PROCESO:MEDICAMENTO_GENERAL
{
private:
   ofstream Escribir_Transacciones;
   ifstream Leer_Transacciones;
   double Total;
   double Subtotal;
   double Impuestos;
   string Nm_Identidad;
   bool verificacion;
   int Venta_Maximas;
   vector<MEDICAMENTO_GENERAL>Vector_Ventas;

public:
    VENTAS_PROCESO();
    void MENU_FARMACIA();
    void IMPORTAR_ELEMENTOS_VECTOR();
    void REALIZAR_VENTA();
    void VERIFICAR_VENTA(string);
};


    
    
    

    






#endif