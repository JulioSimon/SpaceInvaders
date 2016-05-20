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

#ifndef _CTANQUE_
#define _CTANQUE_

#include <SDL.h>
#include <cstdlib>

typedef enum {IZQUIERDA, DERECHA, NADA} TMovimiento;
typedef enum {AUMENTAR, REDUCIR} TVidas;

class CTanque
{
     public:
	  
	  CTanque();
	  ~CTanque();
	  
	  int showpostanqueX();
	  int showpostanqueY();
	  int showpostanqueinicioX();
	  int showpostanqueinicioY();
	  void setpostanque(int x, int y);
	  void setpostanqueinicio(int x, int y);
	  TMovimiento leerMovimiento();
	  int GetVidasTanque();
	  void ModificarVidasTanque(TVidas accion, int cantidad);
	  
     private:
	  
	  int x_actual, y_actual;
	  int x_inicio, y_inicio;
	  int vidas;
	  
	  
};
#endif

     
     
