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

#include "CEstadistica.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

const char ESPACIO = ' ';

using namespace std;

CEstadistica :: CEstadistica()
{
	l = NULL;
}

CEstadistica :: ~CEstadistica()
{
}

void CEstadistica :: GuardarInformacion(string nombre, int puntuacion) // OK
{
	ofstream f;

	f.open("puntos.txt", ios::app);

	if(f.fail())
	{
	     cout << "Error en la apertura del Fichero!" << endl;
	     return;
	}

	f << nombre << ": " << puntuacion << endl;

	f.close();
}

void CEstadistica :: MostrarPorPantalla() //OK
{
	ifstream f;
	string aux;
	string puntuacion;

	f.open("puntos.txt");

	if(f.fail())
	{
	     cout << "Error en la apertura del Fichero!" << endl;
	     return;
	}

	cout << endl;
	
	while(!f.eof())
	{
		getline(f,aux);
		cout << "  " << aux << endl;
	}

	f.close();
}

void CEstadistica :: EliminarTodasLasPuntuaciones() //OK
{
	ofstream f;

	f.open("puntos.txt");

	if(f.fail())
	{
	     cout << "Error en la apertura del Fichero!" << endl;
	     return;
	}

	f.close();

}

void CEstadistica :: anadir (string nom, string pun) // OK
{
	TNodo *aux;
	TNodo *nuevo;
	
	if (l == NULL)
	{
		aux = new TNodo;
		l = aux;
		aux->nombre = nom;
		aux->puntuacion = pun;
		aux->sig = NULL;
	}
	else
	{
		aux = l;
		
		while (aux->sig != NULL)
		{
			aux = aux->sig;
		}
		
		nuevo = new TNodo;
		nuevo->nombre = nom;
		nuevo->puntuacion = pun;
		aux->sig = nuevo;
		nuevo->sig = NULL;
	}

	OrdenarLista();
}
void CEstadistica :: CargarInformacion() //OK
{
	ofstream f;
	TNodo *aux;

	f.open("puntos.txt", ios::out);

	if(f.fail())
	{
		cout << "Error en la apertura del Fichero!" << endl;
		return;
	}

	aux = l;
	while(aux != NULL)
	{
		f << aux->nombre << ":" << aux->puntuacion << endl;
		aux = aux->sig;
	}

	f.close();
}	

void CEstadistica :: AlmacenarInformacion()
{
	string aux;
	string aux2;
	bool ok = false;
	
	ifstream f;

	f.open("puntos.txt", ios::in);

	if(f.fail())
	{
		cout << "Error en la apertura del Fichero!" << endl;
		return;
	}

	while(!f.eof())
	{
		if(ok)
		{
			anadir(aux, aux2); 	// Almacenamos en lista
		}
		getline(f,aux,':'); 	// Leemos el Nombre
		getline(f,aux2); 	// Leemos la puntuacion

		ok = true;
	}

	f.close();
}

void CEstadistica :: OrdenarLista() // OK
{
	int i, auxpuntuacion, comienzopuntuacion;
	TNodo *comienzo, *aux, *mod;
	string nomb, punt;
	bool ok = false;

	if (l != NULL)
	{
		comienzo = l; //Comienzo va pasando al siguiente en lugar de lista para no perder la lista.

		while (comienzo != NULL)
		{
			aux = comienzo; //Aux ira recorriendo la lista y comparando con comienzo

			while (aux != NULL)
			{
				auxpuntuacion = atoi(aux->puntuacion.c_str());		 // Hay que converir el tipo string a int, ya que comparando	
				comienzopuntuacion = atoi(comienzo->puntuacion.c_str()); // strings, 360 > 234000.
				
				if (auxpuntuacion >= comienzopuntuacion)
				{
					mod = aux; //Si encuentra una puntuacion mayor coloca a "mod" en su posicion.
					ok = true;
				}

				aux = aux->sig;
			}

			if(ok == true)
			{
				/** Intercambio de Informacion **/
				nomb = mod->nombre;
				punt = mod->puntuacion;
				mod->nombre = comienzo->nombre;
				mod->puntuacion = comienzo->puntuacion;
				comienzo->nombre = nomb;
				comienzo->puntuacion = punt;
			}
			
			ok = false;
			comienzo = comienzo->sig; // Pasar al siguiente elemento de la lista
		}
	}
}

void CEstadistica :: VaciarLista()
{
	TNodo *aux, *ant;

	if(l != NULL)
	{
		aux = l;
		while(aux != NULL)
		{
			ant = aux;
			aux = aux->sig;
			delete(ant);
		}
		l = NULL;
	}
}
			
