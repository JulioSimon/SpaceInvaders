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

#ifndef _CMARCADOR_
#define _CMARCADOR_

#include <string>

const char ENTER = '\n';

using namespace std;

typedef enum {MAS, MENOS} TPuntuacion;

class CMarcador
{
	public:
		CMarcador();
		~CMarcador();
		int GetPuntuacion();
		void ActualizarPuntuacion(TPuntuacion modificar, int epuntuacion);
		void ResetearPuntuacion();
		string GetNombre();
		void InsertarNombre(); // Se pide desde el Menu

	private:

		string nombre;
		int puntuacion;


};
#endif

