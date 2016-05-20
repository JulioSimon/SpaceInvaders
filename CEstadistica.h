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

#ifndef _CESTADISTICA_
#define _CESTADISTICA_

#include <string>

using namespace std;

class CEstadistica
{
	public:

		CEstadistica();
		~CEstadistica();
		void GuardarInformacion(string nombre, int puntuacion);
		void AlmacenarInformacion();
		void anadir (string nom, string pun);
		void EliminarTodasLasPuntuaciones();
		void MostrarPorPantalla();
		void CargarInformacion();
		void OrdenarLista();
		void VaciarLista();

	private:

		struct TNodo
		{
			string nombre;
			string puntuacion;
			TNodo *sig;
		};

		TNodo *l;

};
#endif
		
