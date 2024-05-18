#include "MEDICAMENTO_GENERAL.h"
MEDICAMENTO_GENERAL::MEDICAMENTO_GENERAL(){
        
}
MEDICAMENTO_GENERAL::MEDICAMENTO_GENERAL(string tipo,string nombre,string fecha, int cant, double precio, int codigo)
{
        Tipo_MED=tipo;
        Nombre_MED=nombre;
        Fecha_MED=fecha;
        Cantidad_MED=cant;
        Precio_MED=precio;
        Codigo_MED=codigo;
}

//Metodos Crud
//Create
void MEDICAMENTO_GENERAL::CREAR_MEDICAMENTO(){
        //Borrar Pantalla
        system("cls");
        //
        escrbir_archivo.open("Registro_Medicamento.txt",ios::out|ios::app);
        cout<<"Ingrese el tipo de medicamento:";
        cin>>Tipo_MED;
        cout<<"Ingrese el nombre del medicamento:";
        cin>>Nombre_MED;
        cout<<"Ingrese la fecha de caducidad del medicamento:";
        cin>>Fecha_MED;
        cout<<"Ingrese la cantidad del medicamento:";
        cin>>Cantidad_MED;
        cout<<"Ingrese el precio del medicamento:";
        cin>>Precio_MED;
        cout<<"Ingrese el codigo del medicamento:";
        cin>>Codigo_MED;
        //Metodo Validar Dato
        if (VALIDAR_CODIGO(Codigo_MED))
        {
                escrbir_archivo<<Tipo_MED<<" "<<Nombre_MED<<" "<<Fecha_MED<<" "<<Cantidad_MED<<" "<<Precio_MED<<" "<<Codigo_MED<<endl;
        }else{
                cout<<"Codigo de Medicamento ya existe no se puede agregar al registro.\n";
        }
        //Cerrar Archivo_Texto
        escrbir_archivo.close();
        system("pause");
        
}
//Read
void MEDICAMENTO_GENERAL::BUSCAR_MEDICAMENTO(){
        //Borrar Pantalla
        system("cls");
        int Codigo_TEMP;
        cout<<"Ingrese el Codigo del Medicamento que desea buscar:";
        cin>>Codigo_TEMP;

        //Realizar Busqueda
        leer_archivo.open("Registro_Medicamento.txt",ios::in);
        leer_archivo>>Tipo_MED;
        //Ciclo
        while (!leer_archivo.eof())
        {
                leer_archivo>>Nombre_MED>>Fecha_MED>>Cantidad_MED>>Precio_MED>>Codigo_MED;
                //Condicional
                if (Codigo_TEMP==Codigo_MED)
                {
                        cout<<"Medicamento Encontrado:\n";
                        cout<<"Tipo de Medicamento:"<<Tipo_MED<<endl;
                        cout<<"Nombre de Medicamento:"<<Nombre_MED<<endl;
                        cout<<"Fecha Vencimiento:"<<Fecha_MED<<endl;
                        cout<<"Cantidad Disponible:"<<Cantidad_MED<<endl;
                        cout<<"Precio:"<<Precio_MED<<"lps"<<endl;
                        cout<<"Codigo:"<<Codigo_MED<<endl;
                        //Finalizar
                        leer_archivo.close();
                        system("pause");
                        return;
                }
                leer_archivo>>Tipo_MED;
        }
        cout<<"Registro Inexistente!"<<endl;
        system("pause");
        leer_archivo.close();
}
//Actualizar Registro
void MEDICAMENTO_GENERAL::ACTUALIZAR_MEDICAMENTO(){
        //Borrar Pantalla
        system("cls");
        
        //Variables Temporales
        int Codigo_TEMP;
        bool Reg_VER;
        //Aberturar de Archivo
        leer_archivo.open("Registro_Medicamento.txt",ios::in);
        ofstream escribir_temporal("Temp_Medicamento.txt",ios::out|ios::app);

        cout<<"Ingrese el codigo del Registro a modificar:";
        cin>>Codigo_TEMP;

        leer_archivo>>Tipo_MED;
        while(!leer_archivo.eof()){
                leer_archivo>>Nombre_MED>>Fecha_MED>>Cantidad_MED>>Precio_MED>>Codigo_MED;
                if (Codigo_TEMP==Codigo_MED)
                {
                        cout<<"Ingrese la nueva Cantidad Disponible:";
                        cin>>Cantidad_MED;
                        cout<<"Ingrese el nuevo precio del medicamento:";
                        cin>>Precio_MED;
                        cout<<"Ingrese la nueva Fecha de Vencimiento:";
                        cin>>Fecha_MED;
                        escribir_temporal<<Tipo_MED<<" "<<Nombre_MED<<" "<<Fecha_MED<<" "<<Cantidad_MED<<" "<<Precio_MED<<" "<<Codigo_MED<<endl;
                        Reg_VER=true;
                }else{
                        escribir_temporal<<Tipo_MED<<" "<<Nombre_MED<<" "<<Fecha_MED<<" "<<Cantidad_MED<<" "<<Precio_MED<<" "<<Codigo_MED<<endl;
                }
                leer_archivo>>Tipo_MED;
        }
        //Mostrar Validacion
        cout<<(Reg_VER ? "Registro Actualizado Correctamente!":"No se pudo Actualizar el Registro!")<<endl;
        
        //Cierre de Archivos
        leer_archivo.close();
        escribir_temporal.close();

        //Remplazar Archivo
        remove("Registro_Medicamento.txt");
        rename("Temp_Medicamento.txt","Registro_Medicamento.txt");

        //Pausar
        system("pause");
}
//Eliminar Registro
void MEDICAMENTO_GENERAL::ELIMINAR_MEDICAMENTO(){
        system("cls");
        //Manipulacion Archivos de Texto
        leer_archivo.open("Registro_Medicamento.txt",ios::in);
        ofstream escribir_temporal("Temp_Medicamento.txt",ios::out|ios::app);

        //Validacion de archivo
        if (!leer_archivo)
        {
                cout<<"ERROR ARCHIVO TXT";
                return;
        }
        //Proceso de Elimacion de Registro
        //Variables a usar
        int Codigo_TEMP;
        bool Reg_VER;

        cout<<"Ingrese el codigo del registro a eliminar:";
        cin>>Codigo_TEMP;

        leer_archivo>>Tipo_MED;
        while (!leer_archivo.eof())
        {
                leer_archivo>>Nombre_MED>>Fecha_MED>>Cantidad_MED>>Precio_MED>>Codigo_MED;
                if (Codigo_TEMP==Codigo_MED)
                {
                        Reg_VER=true;
                }else{
                        escribir_temporal<<Tipo_MED<<" "<<Nombre_MED<<" "<<Fecha_MED<<" "<<Cantidad_MED<<" "<<Precio_MED<<" "<<Codigo_MED<<endl;
                }
                leer_archivo>>Tipo_MED;
        }
        //Mostrar Validacion
        cout<<(Reg_VER ? "Registro Eliminado Correctamente":"No se encontro el Registro")<<endl;
        
        //Cierre de Archivos
        leer_archivo.close();
        escribir_temporal.close();

        //Remplazar Archivo
        remove("Registro_Medicamento.txt");
        rename("Temp_Medicamento.txt","Registro_Medicamento.txt");

        //Pausar
        system("pause");
}
//Metodo Validar Existencia de Codigo
bool MEDICAMENTO_GENERAL::VALIDAR_CODIGO(int Codigo_verifica){
   ifstream leer_codigo("Registro_Medicamento.txt",ios::in);
   //Variables Temporales
   string Tipo_TEMP;
   string Nombre_TEMP;
   string Fecha_TEMP;
   int Cantidad_TEMP;
   double Precio_TEMP;
   int Codigo_TEMP;

   //Inicializar Lectura
   leer_codigo>>Tipo_TEMP;
   //Bucle Repetivo
   while(!leer_codigo.eof()){
        leer_codigo>>Nombre_TEMP;
        leer_codigo>>Fecha_TEMP;
        leer_codigo>>Cantidad_TEMP;
        leer_codigo>>Precio_TEMP;
        leer_codigo>>Codigo_TEMP;
        //Condicional de validacion
        if (Codigo_TEMP==Codigo_verifica)
        {
                leer_archivo.close();
                return false;
        }
        leer_codigo>>Tipo_TEMP;
   }
        //No hay codigo repetido
        leer_archivo.close();
        return true;
}
//Metodo para imprimir todos los medicamentos
void MEDICAMENTO_GENERAL::IMPRIMIR_MEDICAMENTOS(){
        //Borrar Pantalla
        system("cls");
        
        leer_archivo.open("Registro_Medicamento.txt",ios::in);
        cout<<"***********Tabla Medicamentos***********"<<endl;
        //Aplicar Formato
        cout<<setw(18)<<std::left<<"Tipo MED";
        cout<<setw(18)<<std::left<<"Nombre MED";
        cout<<setw(18)<<std::left<<"Fecha VEN";
        cout<<setw(18)<<std::left<<"Stock";
        cout<<setw(18)<<std::left<<"Precio";
        cout<<setw(18)<<std::left<<"Codigo MED"<<endl;
        //Lectura de Datos
        leer_archivo>>Tipo_MED;
        while (!leer_archivo.eof())
        {
               for (int i = 0; i <6; i++)
               {
                   cout<<setw(18)<<std::left<<Tipo_MED;
                   leer_archivo>>Tipo_MED;
               }
               cout<<endl;
        }
        //Cerrar Archivo
        leer_archivo.close(); 
        //System Pause
        system("pause");  
}
//Getter and Setters
string MEDICAMENTO_GENERAL::getTipo(){
        return Tipo_MED;
}
string MEDICAMENTO_GENERAL::getNombre(){
        return Nombre_MED;
}
string MEDICAMENTO_GENERAL::getFecha(){
        return Fecha_MED;
}
int MEDICAMENTO_GENERAL::getCantidad(){
        return Cantidad_MED;
}
double MEDICAMENTO_GENERAL::getPrecio(){
        return Precio_MED;
}
int MEDICAMENTO_GENERAL::getCodigo(){
        return Codigo_MED;
}

void MEDICAMENTO_GENERAL::setTipo(string NewTipo){
      Tipo_MED=NewTipo; 
}
void MEDICAMENTO_GENERAL::setNombre(string NewNombre){
        Nombre_MED=NewNombre; 
}
void MEDICAMENTO_GENERAL::setFecha(string NewFecha){
       Fecha_MED=NewFecha; 
}
void MEDICAMENTO_GENERAL::setCantidad(int NewCantidad){
        Cantidad_MED=NewCantidad; 
}
void MEDICAMENTO_GENERAL::setPrecio(double NewPrecio){
        Precio_MED=NewPrecio; 
}
void MEDICAMENTO_GENERAL::setCodigo(int newCodigo){
        Codigo_MED=newCodigo;
}