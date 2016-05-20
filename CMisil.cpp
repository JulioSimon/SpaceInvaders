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

#include "CMisil.h"
#include "CRecinto.h"
#include <iostream>

using namespace std;

CMisil::CMisil()
{
	l = NULL;
}

CMisil::~CMisil()
{
}

TAccion CMisil::disparartanque()
{
	Uint8 *keys;
	SDL_Event event;

	keys=SDL_GetKeyState(NULL);
	if (keys[SDLK_SPACE])
	{
		return FUEGO;
	}
	else
	{
		return STOP;
	}
}

bool CMisil :: EstaVacia()
{
	bool ok = false;
	
	if(l == NULL)
	{
		ok = true;
	}
	
	return ok;
}

bool CMisil :: EstaLlena()
{
	bool ok = false;
	
	if(l != NULL)
	{
		ok = true;
	}
	
	return ok;
}

bool CMisil::HayLaser(TipoMisil misil)
{
	TNodo *aux = l;

	while(aux != NULL && aux->procedencia != misil)
		aux = aux->sig;

	return aux != NULL;
}

void CMisil :: CrearMisil(TipoMisil misil, CRecinto &r, CTanque &t, CMarciano &q, SDL_Rect &dest, SDL_Rect &desq)
{
	TNodo *aux;
	TNodo *nuevo;
	bool misiltanque = false;
	bool misilmarciano = false;
	int x;
	int y;
	
	if (l==NULL)
	{
		if (misil == MISILTANQUE)
		{
			aux = new TNodo;
			l = aux;
			aux->procedencia = misil;
			dest.x = aux->x = t.showpostanqueX()+17;
			dest.y = aux->y = t.showpostanqueY()-17; /** (-17) Evita que el misil tape al tanque **/
			aux->sig = NULL;
		}
		else
		if (misil == MISILMARCIANO)
		{
			q.posAleatoriaMarciano(r, x, y);
			nuevo = new TNodo;
			nuevo->procedencia = misil;
			desq.x = nuevo->x = x+17;
			desq.y = nuevo->y = y+30; 
			nuevo->sig = NULL;
			l = nuevo;
		}
	}
	else
	{
		aux = l;
		
		if(aux->procedencia == MISILTANQUE)  /** Misiles restringidos a 1 de cada tipo **/
		{
			dest.x = aux->x;
			dest.y = aux->y;
			misiltanque = true;
		}
		else if (aux->procedencia == MISILMARCIANO)
		{
			desq.x = aux->x;
			desq.y = aux->y;
			misilmarciano = true;
		}
		
		while (aux->sig != NULL)
		{
			aux = aux->sig;
			if(aux->procedencia == MISILTANQUE)  /** Misiles restringidos a 1 de cada tipo **/
			{
				dest.x = aux->x;
				dest.y = aux->y;
				misiltanque = true;
			}
			else if (aux->procedencia == MISILMARCIANO)
			{
				desq.x = aux->x;
				desq.y = aux->y;
				misilmarciano = true;
			}
		}
		
		if(misil == MISILTANQUE && misiltanque == false) /** Evita que se cree otro misil tipo tanque cuando ya existe uno activo **/
		{
			nuevo = new TNodo;
			nuevo->procedencia = misil;
			dest.x = nuevo->x = t.showpostanqueX()+17;
			dest.y = nuevo->y = t.showpostanqueY()-17;
			aux->sig = nuevo;
			nuevo->sig = NULL;
		}
		else if (misil == MISILMARCIANO && misilmarciano == false) /** Evita que se cree otro misil tipo marciano cuando ya existe uno activo **/
		{
			q.posAleatoriaMarciano(r, x, y);
			nuevo = new TNodo;
			nuevo->procedencia = misil;
			desq.x = nuevo->x = x+17;
			desq.y = nuevo->y = y+30; 
			aux->sig = nuevo;
			nuevo->sig = NULL;
		}
	}
}
	
void CMisil :: BorrarMisil(TipoMisil misil)
{
	TNodo *aux;
	TNodo *ant;
	bool ok = false;
	
	if(l==NULL)
	{
	}
	else if (l->procedencia == misil)
	{	
		aux = l;

		l = l->sig;
		delete (aux);
	}
	else 
	{	
		aux = l->sig;
		ant = l;
		while (aux != NULL && !ok)
		{	
			if(aux->procedencia == misil) ok = true; /** Necesario para controlar si el ultimo elemento se puede borrar o no **/
			else
			{
				ant = aux;
				aux = aux->sig;
			}
			
		}
		
		if(ok == true) /** Controlamos si el elemento a borrar esta en la ultima posicion **/
		{
			ant->sig = aux->sig;
			delete aux;
		}
		
	}
}

void CMisil :: MueveLaser(SDL_Rect &dest, SDL_Rect &desq)
{
	TNodo *aux;
	TipoMisil m;;

	aux = l;
	while(aux != NULL)
	{
			if(aux->procedencia == MISILTANQUE)
			{
				aux->y = aux->y - 5;
				dest.y = dest.y - 5;
			}
			else if (aux->procedencia == MISILMARCIANO)
			{
				aux->y = aux->y + 2;
				desq.y = desq.y + 2;	// Velocidad de Movimiento de Misiles
			}
			
			if(aux->y <= 0 || aux->y >= 576)
			{
				m = aux->procedencia;
				aux = aux->sig;
				BorrarMisil(m);
			}
			else
				aux = aux->sig;
	}
}

int CMisil :: GetPosMisilX(TipoMisil misil)
{
	TNodo *aux;

	aux = l;

	while(aux != NULL && aux->procedencia != misil) 
	{
		aux = aux->sig;
	}

	if(aux != NULL && aux->procedencia == misil) // l != NULL para evitar acceder a un misil ya borrado
	{
		return aux->x;
	}
}

int CMisil :: GetPosMisilY(TipoMisil misil)
{
	TNodo *aux;

	aux = l;

	while(aux != NULL && aux->procedencia != misil)
	{
		aux = aux->sig;
	}

	if(aux != NULL && aux->procedencia == misil) // l != NULL para evitar acceder a un misil ya borrado
	{
		return aux->y;
	}
}
			
