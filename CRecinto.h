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

#ifndef _CRECINTO_
#define _CRECINTO_

#include <SDL.h>
#include <cstdlib>
#include "CTanque.h"
#include "CMisil.h"
#include "CMarcador.h"
#include "SDL_ttf.h"

//Constantes del Escenario

const int ALTO = 18;
const int ANCHO = 33;

const char cLIMITE = 'p';
const char cCALAMAR = 'c';
const char cCANGREJO = 'k';
const char cPULPO = 'o';
const char cTIERRA = 'a';
const char cINICIO = 'i';

typedef enum {VACIO, LIMITE, TIERRA, CALAMAR, CANGREJO, PULPO, TANQUE} TContenido;

class CRecinto
{
     public:
     		/** En public para poder acceder desde CMarciano sin crear nuevos metodos **/
     		TContenido recinto[ALTO][ANCHO];

		/* ***************************************** */
		/*   MENU PRINCIPAL                          */
		/* ***************************************** */
		char menu();
		bool confirmarsalida();
		void InstruccionesJuego();
		void InformacionAutor();
	  	
	  	/* ***************************************** */
	  	/*   SDL                                     */
	  	/* ***************************************** */
	  	int inicializaSDL();
	  	int inicializaVIDEO();
	  	int inicializaTEXTOSDL();

	  	/* ***************************************** */
	  	/*   TEXTO SDL                               */
	  	/* ***************************************** */
	  	void MostrarPuntuacion(int punt);
	  	void MostrarNombre(string nomb);
	  	void DibujarVidasTanque(int vidast);
	  	void MostrarNivel(int contadorNiveles);
	  
	  	/* ***************************************** */
	  	/*  TANQUE                                   */
	  	/* ***************************************** */
	  	void movertanque(CTanque &t, CMisil &l, TMovimiento m, SDL_Rect &dest);
	  	void posiciontanque(CTanque &t, SDL_Rect &dest);
	  	void borrarTanque(SDL_Rect &dest);

	  	/* ***************************************** */
	  	/*  LASER                                    */
	  	/* ***************************************** */
	  	void dibujarlaser(CTanque &t, CMisil &l, CMarciano &q, CMarcador &n, TAccion a, SDL_Rect &dest, SDL_Rect &desq, SDL_Rect &destanque);

	  	/* ***************************************** */
	  	/*  COLISIONES                               */
	  	/* ***************************************** */
	  	void colisionLaserT_Marciano(CMisil &l, CMarcador &n, SDL_Rect &dest);
	  	void colisionLaserT_LaserM(CMisil &l, SDL_Rect &dest);
	  	void colisionLaserM_Tanque(CMisil &l, CTanque &t, SDL_Rect &dest, SDL_Rect &destanque);
	  	
	  	/* ***************************************** */
	  	/*  MARCIANO                                 */
	  	/* ***************************************** */
	  	void actualizarmarcianos (int i, int j, const int direccion, SDL_Rect &desq);
	  	void reducirMarcianoTime (int marcianos);
	  	int numeroMarcianos();
	  	long getMarcianoTime();
	  	void nivelCompletado (int &done);
	  	void fijarNuevaVelocidad (int nuevavelocidad);
	  	void actualizarDireccion();
	  	int GetContadorNiveles();
	  	void incrementarNivel();
	  	void resetearFases();
	  
	  	/* ***************************************** */
	  	/*   FICHERO                                 */
	  	/* ***************************************** */
	  	CRecinto();
	  	~CRecinto();
	  	int getAncho();
	  	int getAlto();
	  	int cargarFichero(const char nombre[], CTanque &t);
	  	TContenido getContenido(const int x, const int y) const;
	  	void dibujarRecinto(CTanque &t, CMisil &l);
	  	
	  
	  
     private:
	  
	  	SDL_Surface *screen;
	  	int ancho, alto;
	  	int direccion;
	  	long MARCIANO_TIME;
	  	int contadorNiveles;

	  	bool fase1, fase2, fase3, fase4;

};
#endif
