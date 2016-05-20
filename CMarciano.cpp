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

#include "CMarciano.h"
#include "CRecinto.h"
#include <iostream>
#include <cstdlib>

using namespace std;

CMarciano::CMarciano()
{
     tiempo_actual_marciano = obtenertiempo();
     direccion = 0;
     posMarciano = NULL;

}

CMarciano::~CMarciano()
{
}

void CMarciano::actualizartiempomarciano()
{
     tiempo_actual_marciano = obtenertiempo();
}

long CMarciano::obtenertiempo()
{
     return SDL_GetTicks();
}

long CMarciano::tiempomarciano()
{
     return tiempo_actual_marciano;
}

void CMarciano :: AnadirPosicion (int posX, int posY)
{
	TNodo *aux;
	TNodo *nuevo;
		
	if (posMarciano == NULL)
	{
		posMarciano = new TNodo;
		posMarciano->posX = posX;
		posMarciano->posY = posY;
		posMarciano->sig = NULL;
	}
	else
	{
		aux = posMarciano;
		
		if(aux->sig == NULL)
		{
			nuevo = new TNodo;
			nuevo->posX = posX;
			nuevo->posY = posY;
			aux->sig = nuevo;
			nuevo->sig = NULL;
		}
		else
		{
			while(aux->sig != NULL) 
			{
				aux = aux->sig;
			}

			nuevo = new TNodo;
			nuevo->posX = posX;
			nuevo->posY = posY;
			aux->sig = nuevo;
			nuevo->sig = NULL;
		}
	}
}

int CMarciano :: TamanoLista()
{
	TNodo *aux;
	
	if(posMarciano == NULL)
	{
		return 0;
	}
	else
	{
		aux = posMarciano;

		if(aux->sig == NULL)
		{
			return 1;
		}
		else
		{
			int contador = 0;
			
			while (aux->sig != NULL)
			{
				contador++;
				aux = aux->sig;
			}

			return contador;
		}
	}
}

void CMarciano::posAleatoriaMarciano(CRecinto &r, int &x, int &y)
{
	int i,j;
	int posicionLista;
	TNodo *aux;

	for(i=0;i<ALTO-4;i++) // Evitamos la zona del tanque
	{
		for(j=0;j<ANCHO;j++)
		{
			if((r.recinto[i][j] == CALAMAR || r.recinto[i][j] == PULPO || r.recinto[i][j] == CANGREJO))
			{
				if(r.recinto[i+1][j] == VACIO) // Posicion Valida para Atacar
				{
					AnadirPosicion(j*32,i*32);
				}
			}
		}
	}

	if(posMarciano != NULL)
	{
		posicionLista = rand()%TamanoLista();

		aux = posMarciano;

		if(aux->sig == NULL)
		{
			x = aux->posX;
			y = aux->posY;
		}
		else
		{
			int contador = 0;
			
			while (aux->sig != NULL && contador != posicionLista)
			{
				contador++;
				aux = aux->sig;
			}

			x = aux->posX;
			y = aux->posY;
		}
	}

	while(posMarciano != NULL)
	{
		aux = posMarciano;
		posMarciano = posMarciano->sig;
		delete(aux);
	} 
}
	
	

void CMarciano::movermarcianos(CRecinto &r, int &done, SDL_Rect &desq, int &finpartida, int &finnivel)
{
    int i,j;

    bool izquierda, derecha;
     
    	const int min_x = 0;
	const int max_x = ANCHO;
	const int min_y = 0;
	const int max_y = ALTO - 4;
    
     if(obtenertiempo() - tiempomarciano() >= r.getMarcianoTime())
     {
     	/** Movimiento de los Marcianos **/
     	if (direccion == 0)
     	{
     		for (i = min_y; i <= max_y; i++)
     		{
     			for (j = min_x + 2; j <= max_x - 1; j++)
     			{
     				//Modificamos la posicion de los sprites en pantalla.
     				r.actualizarmarcianos(i,j,0,desq);

				//Modificamos la posicion de los enumerados en el array.
				r.recinto[i][j-1] = r.recinto [i][j];
			}

			//Comprobamos si algun alienigena ha llegado al limite, para cambiar la direccion.
			if((r.recinto[i][min_x + 1] != VACIO))
			{
				direccion = 1;
			}
		}
	}
	else if (direccion == 1)
	{
		for (i=max_y; i>=min_y; i--)
		{
			for (j=min_x; j<=max_x; j++)
			{
				//Modificamos la posicion de los sprites en pantalla.
 				r.actualizarmarcianos(i,j,1,desq);
 				
				//Modificamos la posicion de los enumerados en el array.
				r.recinto[i+1][j] = r.recinto [i][j];
				r.recinto[i][j] = VACIO;
				if(r.recinto[i+1][j] != VACIO && j <= 5)
				{
					direccion = 2;
					if(i+1 > ALTO-5)
					{
						finpartida = 1;
						finnivel = 1;
					}
				}
				else if (r.recinto[i+1][j] != VACIO  && direccion == 1)
				{
					direccion = 0;
					if(i+1 > ALTO-5)
					{
						finpartida = 1;
						finnivel = 1;
					}
				}
			}
		}
	}
	else if (direccion == 2)
	{
		for (i=min_y; i<= max_y; i++)
		{
			for (j=max_x - 2; j>=min_x + 1; j--)
			{
				//Modificamos la posicion de los sprites en pantalla.
				r.actualizarmarcianos(i,j,2,desq);
						  
				//Modificamos la posicion de los enumerados en el array.
				r.recinto[i][j+1] = r.recinto [i][j];
				r.recinto[i][j] = VACIO;
						  

			}
			
			//Comprobamos si algun alienigena ha llegado al limite, para cambiar la direccion.
			if((r.recinto[i][max_x - 2] != VACIO))
			{
				direccion = 1;
			}
		}
	}
	
	//Actualizamos el Tiempo
	actualizartiempomarciano();
     } 
}

