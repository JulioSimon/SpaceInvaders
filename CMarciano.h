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

#ifndef _CMARCIANO_
#define _CMARCIANO_

#include <SDL.h>
#include <cstdlib>



//typedef enum {IZQUIERDA, DERECHA, ABAJO} TMovimiento;

const long TIEMPO_ACTUALIZACION = 3;

class CRecinto;
class CMarciano
{
     public:
	  
	  CMarciano();
	  ~CMarciano();
	  
	  long obtenertiempo();
	  void actualizartiempomarciano();
	  long tiempomarciano();
	  void movermarcianos(CRecinto &r, int &done, SDL_Rect &desq, int &finpartida, int &finnivel);
	  void AnadirPosicion (int posX, int posY);
	  int TamanoLista();
	  void posAleatoriaMarciano(CRecinto &r, int &x, int &y);
	  
     private:
	  
	  long tiempo_actual_marciano;
	  int direccion;

	  /** Posicion Aleatoria del Marciano Atacante **/

	  struct TNodo
	  {
	  	int posX;
	  	int posY;
	  	TNodo *sig;
	  };

	  TNodo *posMarciano;
	  
	  
};

#endif

     
