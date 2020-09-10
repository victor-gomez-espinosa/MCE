/* Fecha: 30 de Septiembre de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Parte 1 de la Tarea 3 de la materia Programación y analisis de algoritmos impartida en cimat mty
 *    Codigo para simular el inventario de una ferreteria, para saber que herramientas tiene, cuantas tiene y el costo de cada una.
 */

//librerias
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int menu(){//menu de opcines

unsigned int op=0;

 // muestra opciones
   printf( "%s", "\nIntroduza su opcion\n"
      "1  crear el archivo:\n"
      "    \"hardware.txt\" a 100 registros vacios\n"
      "2  ingresar datos  de una herramienta  \n"
      "3  listar todas las herramientas\n"
      "4  eliminar un registro de una herramienta que ya no hay\n"
      "5  modificar un registro del archivo (Herramienta Cantidad Costo)\n"
      "6  Salir\n " );

   scanf( "%u", &op );

return op;
}

int menu2(){//menu de opcines2

unsigned int op=0;

// muestra opciones
    printf( "%s", "\n que deseas modificar\n"
            "1  Nombre de la herramienta\n"
            "2  Cantidad\n"
            "3  Costo\n"
            "4  salir\n");

    scanf( "%u", &op );

return op;
}



// define la estructura RegistroHerramienta
struct RegistroHerramienta {
   unsigned int numregistro; // numero de regstro de la herramienta
   char herramienta[ 20 ]; // nombre de la herramienta
   int cantidad; // cantidad de esa herramienta
   double costo; // costo de la herramienta
}; // end

int fcrea_arcvhivo(  ){ //a) inicializar el archivo "hardware.dat" a 100 registros vacios

   unsigned int i; // contador que va del 1 al 100

   // crea un registro con la estructura RegistroHerramienta en blanco
   struct RegistroHerramienta registro = { 0, "", 0, 0.0 };

   FILE *rhfPtr; // hardware.dat apuntador al archivo

   //crea un archivo binario y termina si no lo puede crear
   if ( ( rhfPtr = fopen( "hardware.dat", "wb" ) ) == NULL ) {
      puts( "No se puede crear el archivo." );
   } // end if
   else {
      // poner 100 registros en blanco en el archivo
      for ( i = 1; i <= 100; ++i ) {
         fwrite( &registro, sizeof( struct RegistroHerramienta ), 1, rhfPtr );
      } // end for

      fclose ( rhfPtr ); // fclose cierra el archivo
   } // end else

   return 0;
} // end fcrea_arcvhivo

int fescribe_archivo(  ) //b) ingresa los datos relativos a cada herramienta
{
   FILE *rhfPtr; // hardware.dat apuntador al archivo

   // crea un registro con la estructura RegistroHerramienta en blanco
   struct RegistroHerramienta registro = { 0, "", 0, 0.0 };

   // fopen abre el archivo para actualizarlo, termina si no se puede abrir
   if ( ( rhfPtr = fopen( "hardware.dat", "rb+" ) ) == NULL ) {// rb+ actualizar el archivo tipo binario, leer y actualizar
      puts( "Archivo no se puede abrir o no existe (elija la opcion 1)" );
   } // end if
   else {
      // El usuario especifica el numero de registro
      printf( "%s", "Introduzca el numero de registro de la herramienta"
         " ( 1 to 100, 0 para terminar )\n? " );
      scanf( "%d", &registro.numregistro );

      // el usuario ingresa la informacion que se escribe al archivo, herramienta cantidad y costo
      while ( registro.numregistro != 0 ) {
         // el usuario introduce el herramienta cantidad y costo
         printf( "%s", "Introduzca: Nombre de la Herramienta(sin espacios) Cantidad Costo\n? " );

         // se pone el valor  de  herramienta cantidad y costo en el registro
         fscanf( stdin, "%19s%d%lf", registro.herramienta,
            &registro.cantidad, &registro.costo );

         // busca la posicion en el archivo del registro especificado
         fseek( rhfPtr, ( registro.numregistro - 1 ) *
            sizeof( struct RegistroHerramienta ), SEEK_SET );

         // escribe la informacion en el archivo
         fwrite( &registro, sizeof( struct RegistroHerramienta ), 1, rhfPtr );

         // permitir al usuario hacer otro registro de una herramienta
         printf( "%s", "Introduzca el numero de registro de la herramienta\n? " );
         scanf( "%d", &registro.numregistro );
      } // end while

      fclose( rhfPtr ); // fclose cierra el archivo
   } // end else
   return 0;
} // end fescribe_archivo

int flee_archivo(  ) //c) lista todas las herramientas
{
   FILE *rhfPtr; // hardware.dat apuntador al archivo
   int result; // usado para verificar si fread leyo bytes

   // crea un registro con la estructura RegistroHerramienta en blanco
   struct RegistroHerramienta registro = { 0, "", 0, 0.0 };

   // fopen abre el archivo, termina si no se puede abrir
   if ( ( rhfPtr = fopen( "hardware.dat", "rb" ) ) == NULL ) {//rb solo lee el archivo de tipo binario
      puts( "Archivo no se puede abrir o no existe (elija la opcion 1)" );
   } // end if
   else {
      printf( "%9s\t%19s\t%10s%\t%10s\n", "#Registro", "Herramienta",
         "Cantidad", "Costo" );

      // leer todos los registro (hasta eof)
      while ( !feof( rhfPtr ) ) {
         result = fread( &registro, sizeof( struct RegistroHerramienta ), 1, rhfPtr );

         // muestra el registro
         if ( result != 0 && registro.numregistro != 0 ) {
            printf( "%9d\t%19s\t%10d\t%10.2f\n", registro.numregistro, registro.herramienta,
            registro.cantidad, registro.costo );
         } // end if
      } // end while

      fclose( rhfPtr ); // fclose cierra el archivo
   } // end else
   return 0;
} // end flee_archivo



int fborra_registro(  ){ //d) elimina un registro de una herramienta que ya no hay

   FILE *rhfPtr; // hardware.dat apuntador al archivo

   struct RegistroHerramienta registro; // guarda el registro leido (el que se va a borrar)

   // crea un registro con la estructura RegistroHerramienta en blanco
   struct RegistroHerramienta registroDefault = { 0, "", 0, 0.0 };

   unsigned int NumRegistro; // numero de registro a borrar

    // fopen abre el archivo, termina si no lo puede abrir
   if ( ( rhfPtr = fopen( "hardware.dat", "rb+" ) ) == NULL ) {// rb+ actualizar el archivo tipo binario, leer y actualizar
      puts( "Archivo no se puede abrir o no existe (elija la opcion 1)" );
   } // end if
   else {

       // numero de registro a borrar
       printf( "%s", "Introduzca el numero de registro a borrar( 1 - 100 ): " );
       scanf( "%d", &NumRegistro );



       // mover el apuntador al registro adecuado
       fseek( rhfPtr, ( NumRegistro - 1 ) * sizeof( struct RegistroHerramienta ),
          SEEK_SET );


       // lee registro del archivo
       fread( &registro, sizeof( struct RegistroHerramienta ), 1, rhfPtr );


       // muestra error si no existe
       if ( registro.numregistro == 0 ) {
          printf( "Registro %d no existe.\n", NumRegistro );
       } // end if
       else { // borra el registro
          // mover el puntero al lugar correcto
          fseek( rhfPtr, ( NumRegistro- 1 ) * sizeof( struct RegistroHerramienta ),
             SEEK_SET );

          // reemplaza el registro con registro en blanco
          fwrite( &registroDefault,
             sizeof( struct RegistroHerramienta ), 1, rhfPtr );
       } // end else
   }//end else
   fclose( rhfPtr ); // fclose cierra el archivo
   return 0;
} // end function borraRegistro

int fmodifica_registro(  ){ //e) actualiza cualquier informacion en el archivo (modificar un nombre, costo o cantidad)
    unsigned int op=0; //se inicializan variables a utilizar


   FILE *rhfPtr; // hardware.dat apuntador al archivo

   struct RegistroHerramienta registro; // guarda el registro leido (el que se va a borrar)

   // crea un registro con la estructura RegistroHerramienta en blanco
   struct RegistroHerramienta registroDefault = { 0, "", 0, 0.0 };

   unsigned int NumRegistro; // numero de registro a borrar

    // fopen abre el archivo, termina si no lo puede abrir
   if ( ( rhfPtr = fopen( "hardware.dat", "rb+" ) ) == NULL ) {// rb+ actualizar el archivo tipo binario, leer y actualizar
      puts( "Archivo no se puede abrir o no existe (elija la opcion 1)" );
   } // end if
   else {

       // numero de registro a borrar
       printf( "%s", "Introduzca el numero de registro a modificar( 1 - 100 ): " );
       scanf( "%d", &NumRegistro );



       // mover el apuntador al registro adecuado
       fseek( rhfPtr, ( NumRegistro - 1 ) * sizeof( struct RegistroHerramienta ),
          SEEK_SET );


       // lee registro del archivo
       fread( &registro, sizeof( struct RegistroHerramienta ), 1, rhfPtr );


       // muestra error si no existe
       if ( registro.numregistro == 0 ) {
          printf( "Registro %d no existe.\n", NumRegistro );
       } // end if
       else { // borra el registro
            printf( "%9s\t%19s\t%10s%\t%10s\n", "#Registro", "Herramienta",
         "Cantidad", "Costo" );
            //muestra la informacion del registro
            printf( "%9d\t%19s\t%10d\t%10.2f\n", registro.numregistro, registro.herramienta,
            registro.cantidad, registro.costo );

            while((op=menu2())!=4){//selecciona la opcion
                switch ( op ) {

                case 1: //modifica el nombre de la herramienta
                    printf( "%s", "Nuevo nombre (sin espacios): " );
                    scanf( "%s", registro.herramienta );


                   break;
                case 2: //modifica la cantidad de la herramienta
                   printf( "%s", "Nuevo cantidad: " );
                   scanf( "%d", &registro.cantidad );


                   break;
                case 3: //modifica el costo de la herramienta
                   printf( "%s", "Nuevo Costo: " );
                   scanf( "%lf", &registro.costo );

                   break;
                default:
                   puts( "Opcion incorrecta" ); //termina el programa
                   break;
                }//end switch
            }//end while

            //muestra la actualizacion del registro
            printf( "%9s\t%19s\t%10s%\t%10s\n", "#Registro", "Herramienta",
         "Cantidad", "Costo" );
            printf( "%9d\t%19s\t%10d\t%10.2f\n", registro.numregistro, registro.herramienta,
                    registro.cantidad, registro.costo );

            // mueva el puntero al lugar correcto
            fseek( rhfPtr, ( NumRegistro - 1 ) * sizeof( struct RegistroHerramienta ),
                    SEEK_SET );

            // escribe la actualizacion sobre el antiguo
            fwrite( &registro, sizeof( struct RegistroHerramienta ), 1, rhfPtr );


       } // end else
   }//end else
   fclose( rhfPtr ); // fclose cierra el archivo
   return 0;
} // end function borraRegistro


int main(){
    unsigned int op=0;

   while((op=menu())!=6){//selecciona la opcion
        switch ( op ) {

            case 1: //a) inicia el archivo hardware.dat con 100 registros vacios
               fcrea_arcvhivo(  );
               break;
            case 2: //b) ingresa los datos relativos a cada herramienta
               fescribe_archivo(  );
               break;
            case 3: //c) lista todas las herramientas
               flee_archivo(  );
               break;
            case 4: //d) elimina un registro de una herramienta que ya no hay
               fborra_registro(  );
               break;
            case 5://e) actualiza cualquier informacion en el archivo (modificar un nombre, costo o cantidad)
               fmodifica_registro(  );
               break;
            default:
               puts( "Opcion incorrecta" ); //termina el programa
               break;
        }//end switch
   }//end while
    return 0;
}//end main
