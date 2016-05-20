////////////////////////////////////////////////////////////////////////////////
//                            INFORMACION DEL AUTOR                           //
////////////////////////////////////////////////////////////////////////////////
//    Nombre: Julio Jose Simon Gil                                            //
//    E-mail: juliojosesimongil@gmail.com                                     //
//            jjsimon@alu.uma.es                                              //
//                                                                            //
//    Curso: Primero                                                          //
//    Grupo: B                                                                //
//                                                                            //
//    Inicio del Proyecto: Marzo 2010                                         //
//    Fin del Proyecto: Julio 2010                                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "CMarcador.h"

using namespace std;

CMarcador :: CMarcador()
{
	puntuacion = 0;
}

CMarcador :: ~CMarcador()
{
}

int CMarcador :: GetPuntuacion()
{
	return puntuacion;
}

void CMarcador :: ActualizarPuntuacion(TPuntuacion modificar, int epuntuacion)
{
	if(modificar == MAS)
	{
		puntuacion = puntuacion + epuntuacion;
	}
	else
	if(modificar == MENOS && puntuacion >= epuntuacion)
	{
		puntuacion = puntuacion - epuntuacion;
	}
	else
	if(modificar == MENOS && puntuacion < epuntuacion)
	{
		ResetearPuntuacion();
	}
}

void CMarcador :: ResetearPuntuacion()
{
	puntuacion = 0;
}

string CMarcador :: GetNombre()
{
	return nombre;
}

void CMarcador :: InsertarNombre()
{
	cout << "Inserta tu nombre: " << endl;
	getline(cin,nombre);
	cout << endl;
}

	

