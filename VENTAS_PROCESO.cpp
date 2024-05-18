#include "VENTAS_PROCESO.h"
VENTAS_PROCESO::VENTAS_PROCESO():MEDICAMENTO_GENERAL(){

}
//Metodos
void VENTAS_PROCESO::MENU_FARMACIA(){
    //Variable Temporal
        int OP_MENU=0;
    //Ciclo Repetivo
        do
        {
        system("cls") ;
        //Menu
        cout<<"*********Farmacia-CEUTEC*********"<<endl;
        cout << "1. Buscar medicamento" << endl;
        cout << "2. Imprimir Medicamentos" << endl;
        cout << "3. Crear Medicamentos" << endl;       
        cout << "4. Actualizar Medicamentos" << endl;
        cout << "5. Eliminar Medicamentos" << endl;
        cout << "6. Venta Medicamentos" <<endl;
        cout << "7. Salir" << endl;
        cout<<"Ingrese una opcion:";
        cin>>OP_MENU;
        //Switch
           switch (OP_MENU)
           {
                case 1:
                        BUSCAR_MEDICAMENTO();
                        break;
                case 2:
                        IMPRIMIR_MEDICAMENTOS();
                        break;
                case 3:
                        CREAR_MEDICAMENTO();
                        break;
                case 4:
                        ACTUALIZAR_MEDICAMENTO();
                        break;
                case 5:
                        ELIMINAR_MEDICAMENTO();
                        break;
                case 6:
                        REALIZAR_VENTA();
                        break;
                case 7:
                        cout<<"¡Hasta Pronto!"<<endl;
                        break;
                default:
                        cout<<"Ingreso una opcion Incorrecta!"<<endl;
                        break;
           }     
        } while (OP_MENU!=7);
}
void VENTAS_PROCESO::IMPORTAR_ELEMENTOS_VECTOR(){
    //Lectura de Datos
    leer_archivo.open("Registro_Medicamento.txt",ios::app);
    //Variables Temporales
    string Tipo_TE;
    string Nombre_TE;
    string Fecha_TE;
    int Cantidad_TE;
    double Precio_TE;
    int Codigo_TE;
    leer_archivo>>Tipo_TE;
    while (!leer_archivo.eof())
    {
        MEDICAMENTO_GENERAL MED_ARR;
        leer_archivo>>Nombre_TE>>Fecha_TE>>Cantidad_TE>>Precio_TE>>Codigo_TE;
        
        Vector_Ventas.push_back(MEDICAMENTO_GENERAL(Tipo_TE,Nombre_TE,Fecha_TE,Cantidad_TE,Precio_TE,Codigo_TE));
        leer_archivo>>Tipo_TE;
    }
    leer_archivo.close(); 
}
void VENTAS_PROCESO::REALIZAR_VENTA(){
    //Borrar Pantalla
    system("cls");
    
    //Llamar Metodo de Introduccion de Datos
    IMPORTAR_ELEMENTOS_VECTOR();
    //Variables
    int CODIGO_TEMP;
    bool Verificacion=false;
    int indice;
    int Cantidad;
    //Proceso de Venta
    cout<<"Ingrese el codigo del producto a vender:";
    cin>>CODIGO_TEMP;
    cout << "Ingrese la cantidad: ";
    cin >> Cantidad;
    for (int i = 0; i <Vector_Ventas.size(); i++)
    {
        if (CODIGO_TEMP==Vector_Ventas[i].getCodigo())
        {
            Verificacion=true;
            indice=i;
        } 
    }
    if (Verificacion==false)
    {
        cout<<"No se encontro el medicamento!"<<endl;
        return;
        system("Pause");
    }
    if (Cantidad>Vector_Ventas[indice].getCantidad()||Cantidad<=0)
    {
       cout<<"No disponemos de dicha cantidad!"<<endl;
       system("pause");
    }else{
        //Calculo de Datos
        Subtotal=Cantidad*Vector_Ventas[indice].getPrecio();
        Impuestos=Subtotal*0.15;
        Total=Subtotal+Impuestos;
        
        cout << "Código del producto: " <<Vector_Ventas[indice].getCodigo() << endl;
        cout << "Nombre del Producto: "<<Vector_Ventas[indice].getNombre()<< endl;
        cout << "Precio unitario: " <<Vector_Ventas[indice].getPrecio()<< endl;
        cout << "Cantidad vendida: " <<Cantidad << endl;
        cout<< "Subtotal:"<<Subtotal<<endl;
        cout<<"Impuestos:"<<Impuestos<<endl;
        cout << "Precio total: " << Total<< endl;

        //Proceso de Venta y Guardar Datos
        cout<<"Ingrese el Nm de Identidad del Cliente(Llevar Registro):";
        cin>>Nm_Identidad;
        VERIFICAR_VENTA(Nm_Identidad);
        if (Venta_Maximas<3)
        {
            double Monto=0;
            cout<<"Ingrese su monto a pagar:";
            cin>>Monto;
            while (Monto<Total)
            {
                cout<<"Monto insuficiente vuelva a ingresar:";
                cin>>Monto;
            }
            double cambio=Monto-Total;
            cout<<"Su Cambio es de:"<<cambio<<endl;
           int Cantidad_ME=Vector_Ventas[indice].getCantidad();
            Vector_Ventas[indice].setCantidad(Cantidad_ME-Cantidad);
            ofstream Clientes_escribir("Cliente_Registro.txt",ios::out|ios::app);
            Clientes_escribir<<Nm_Identidad<<" "<<Vector_Ventas[indice].getCodigo()<<" "<<Vector_Ventas[indice].getNombre()<<" "<<Cantidad<<" "<<Total<<" "<<cambio<<endl;
            Clientes_escribir.close();

            //Proceso 
            ofstream Archivo_temp("Archivo_temp.txt",ios::out|ios::app);
            for (int i = 0; i <Vector_Ventas.size(); i++)
            {
                Archivo_temp<<Vector_Ventas[i].getTipo()<<" "<<Vector_Ventas[i].getNombre()<<" "<<Vector_Ventas[indice].getFecha()<<" "<<Vector_Ventas[i].getCantidad()<<" "<<Vector_Ventas[i].getPrecio()<<" "<<Vector_Ventas[i].getCodigo()<<endl;
            }
            Archivo_temp.close();

            //Renombrar Archivos
            remove("Registro_Medicamento.txt");
            rename("Archivo_temp.txt","Registro_Medicamento.txt");
            
        }else{
            cout<<"Maxima ventas permitidas al Nm de Cuenta:"<<Nm_Identidad<<endl;
        }
        system("pause");
    }
    
}
void VENTAS_PROCESO::VERIFICAR_VENTA(string Identidad_ve){
        ifstream leer_clientes("Cliente_Registro.txt",ios::in);
        string Identidad_TEMP;
        string codigo;
        string nombre;
        string cantidad;
        string total;
        string cambio;
        Venta_Maximas=0;
        leer_clientes>>Identidad_TEMP>>codigo>>nombre>>cantidad>>total>>cambio;
        while (!leer_clientes.eof())
        {
            if (Identidad_ve==Identidad_TEMP)
            {
               Venta_Maximas++;
            }
            leer_clientes>>Identidad_TEMP>>codigo>>nombre>>cantidad>>total>>cambio;
        }
        leer_clientes.close();
}

