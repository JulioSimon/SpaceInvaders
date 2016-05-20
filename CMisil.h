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

#ifndef _CMISIL_
#define _CMISIL_

#include "CTanque.h"
#include "CMarciano.h"

#include <SDL.h>
#include <cstdlib>

typedef enum {STOP,FUEGO} TAccion;
typedef enum {MISILMARCIANO, MISILTANQUE} TipoMisil;

class CRecinto;
class CMisil /** Contendra una lista enlazada para almacenar los misiles **/
{
	public:
		CMisil();
		~CMisil();
		bool EstaVacia();
		bool EstaLlena();
		bool HayLaser(TipoMisil misil);
		void CrearMisil(TipoMisil misil, CRecinto &r, CTanque &t, CMarciano &q, SDL_Rect &dest, SDL_Rect &desq);
		void BorrarMisil(TipoMisil misil);
		void MueveLaser(SDL_Rect &dest, SDL_Rect &desq);
		TAccion disparartanque();

		int GetPosMisilX(TipoMisil misil);
		int GetPosMisilY(TipoMisil misil);
	
	private:
		struct TNodo
		{
			TipoMisil procedencia;
			int x;
			int y;
			TNodo *sig;
		};
		
		typedef TNodo* TLista;
		TLista l;
};

#endif

