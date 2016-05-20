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

#include "CTanque.h"
#include <iostream>

using namespace std;

CTanque::CTanque()
{
	vidas = 3;
}

CTanque::~CTanque()
{
}

int CTanque::showpostanqueX()
{
     return x_actual;
}

int CTanque::showpostanqueY()
{
     return y_actual;
}

int CTanque::showpostanqueinicioX()
{
     return x_inicio;
}

int CTanque::showpostanqueinicioY()
{
     return y_inicio;
}

void CTanque::setpostanque(int x, int y)
{
     x_actual = x;
     y_actual = y;
}

void CTanque::setpostanqueinicio(int x, int y)
{
     x_inicio = x;
     y_inicio = y;
}

TMovimiento CTanque::leerMovimiento()
{
//	SDL_Event event;
	Uint8 *keys;

	keys=SDL_GetKeyState(NULL);
	
	if (keys[SDLK_LEFT])
	{
	     return IZQUIERDA;
	}
	if (keys[SDLK_RIGHT])
	{
	     return DERECHA;
	}
	return NADA;
}

int CTanque :: GetVidasTanque()
{
	return vidas;
}

void CTanque :: ModificarVidasTanque(TVidas accion, int cantidad)
{
	if(accion == AUMENTAR && vidas < 3)
	{
		vidas = vidas + cantidad;
	}
	else
	if(accion == REDUCIR && vidas > 0)
	{
		vidas = vidas - cantidad;
	}
}
