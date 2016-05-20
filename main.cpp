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

#include <iostream>
#include <stdio.h>

#include "CRecinto.h"
#include "CTanque.h"
#include "CMarciano.h"
#include "CMarcador.h"
#include "CEstadistica.h"

using namespace std;

int main(int argc, char **argv)
{
	CRecinto r;
     	CTanque t;
     	CMarciano q;
     	CMisil l;
     	CMarcador n;
    	CEstadistica e;

     	TMovimiento m;
     	TAccion a;

     	SDL_Event event;
     
     	SDL_Rect dest; //Movimiento del Tanque.
     	SDL_Rect desq; //Movimiento Marcianos.
     	SDL_Rect desl; //Movimiento del Misil.

     	bool salir;
     	char opcion;
     	int done = 0;
     	int gameover = 0;
     	int contadorniveles = 1;
     
     	if(argc != 2)
     	{       cout << "Usar: " << argv[0] << " <nombrefichero>.txt" << endl;
        	exit(1);
     	}
     
     
     	r.cargarFichero(argv[1], t);

     	atexit(SDL_Quit);
     	atexit(TTF_Quit);

	
	while(!salir)
  	{
    		opcion = r.menu();
    
    		switch(opcion)
    		{
      			case 'A': 
      				cin.ignore();     //limpia el ENTER del buffer de teclado

				n.InsertarNombre(); // Pide y almacena el nombre del usuario
     
     				r.inicializaSDL();
     				r.inicializaVIDEO();
     				r.inicializaTEXTOSDL();
     				SDL_WM_SetCaption("Invasion Marciana", "Invasion Marciana"); // Titulo de la Ventana

     				/** Como el nombre es estatico, no hace falta redibujarlo en cada iteracion **/
     				r.MostrarNombre(n.GetNombre());

     				/** Primer nivel del juego **/
     				q.actualizartiempomarciano();
     				r.dibujarRecinto(t,l);

     				// Posicion del tanque y misil en pantalla.
     				r.posiciontanque(t, dest);
     
     				while (gameover == 0 || done == 0)
     				{
	  				if(done == 1) // Comenzar nuevo nivel si se eliminan todos los marcianos.
	  				{
						/** Incrementar Nivel **/
						r.incrementarNivel();

						/** Resetar Fases **/
						r.resetearFases();
	  			
	  					/** Cargar Recinto **/
	  					r.cargarFichero(argv[1], t);

	  					/** Actualizar Nuevos Tiempos **/
	  					q.actualizartiempomarciano();
	  					r.fijarNuevaVelocidad (1000);

	  					/** Anadir Dificultad **/
	  					if(r.GetContadorNiveles() >= 5 && r.GetContadorNiveles() < 10)
	  					{
	  						r.fijarNuevaVelocidad(900);
	  					}
	  					else
	  					if(r.GetContadorNiveles() > 10)
	  					{
	  						r.fijarNuevaVelocidad(800);
	  					}

     						/** Borrar Posicion final del tanque **/
     						r.borrarTanque(dest);

     						/** Dibujar el Recinto **/
     						r.dibujarRecinto(t,l);

     						// Posicion del tanque y misil en pantalla.
     						r.posiciontanque(t, dest);

     						/** Actualizar Direccion de los Marcianos **/
	  					r.actualizarDireccion();

     						done = 0;

     						if(contadorniveles == 15)
     						{
     							done = 1;
     							gameover = 1;
     						}
     	  				}

     	  				// Mostrar Puntuacion
     	  				r.MostrarPuntuacion(n.GetPuntuacion());
	  				// Mostrar Nombre
     	  				r.MostrarNombre(n.GetNombre());
     	  				// Mostrar Vidas
     	  				r.DibujarVidasTanque(t.GetVidasTanque());
     	  				// Mostrar Nivel
     	  				r.MostrarNivel(r.GetContadorNiveles());
     	  
	  				// Disparos del Tanque
	  				a = l.disparartanque();
	 				r.dibujarlaser(t,l,q,n,a,desl,desq,dest);

	 				// Velocidad de los Marcianos
	 				r.reducirMarcianoTime(r.numeroMarcianos());
     	  				// Movimiento Marcianos
	  				q.movermarcianos(r, done, desq, gameover, done); // Si los Marcianos llegan a Tierra, gameover = 1 & done = 1; Fin del Juego.

	  				// Movimiento del Tanque
	  				m = t.leerMovimiento();
	  				r.movertanque(t, l, m,dest);

	  				// Nivel Completado?
	  				r.nivelCompletado(done);

	  				if (t.GetVidasTanque() == 0)
	  				{
	  					done = 1;
	  					gameover = 1;
	  				}
	  
	  				while (SDL_PollEvent(&event))
	  				{    
	       					if (event.type == SDL_QUIT) {done = 1; gameover = 1;}
	       					if (event.type == SDL_KEYDOWN)
	       					{
		    					if(event.key.keysym.sym == SDLK_ESCAPE)
		    					{
			 					done = 1;
			 					gameover = 1;
		    					}
	       					}
 	  				}
     				}

     				/** Guardar Puntuacion Obtenida **/
     				e.GuardarInformacion(n.GetNombre(),n.GetPuntuacion());
     		
				//atexit(SDL_Quit);
     				//atexit(TTF_Quit);
     				salir = true;
      
			break;
      			case 'B':
      				cin.ignore();     //limpia el ENTER del buffer de teclado
      		
				e.AlmacenarInformacion();	
				e.CargarInformacion();
				e.MostrarPorPantalla();
				e.VaciarLista(); //Vacia el contenido de la lista enlazada.

				cout << endl;
				cout << "Pulsa ENTER para continuar..." << endl;
				while(getchar() != '\n'){};
			break;
      			case 'C': 
				cin.ignore();     //limpia el ENTER del buffer de teclado
      				e.EliminarTodasLasPuntuaciones();

      				cout << "Todas las puntuaciones eliminadas." << endl;
      				cout << endl;
				cout << "Pulsa ENTER para continuar..." << endl;
				while(getchar() != '\n'){};
			break;
      			case 'D': 
				cin.ignore();     //limpia el ENTER del buffer de teclado
      				r.InstruccionesJuego();
      				cout << endl;
				cout << "Pulsa ENTER para continuar..." << endl;
				while(getchar() != '\n'){};
			break;
      			case 'E':
      				cin.ignore();     //limpia el ENTER del buffer de teclado
      				r.InformacionAutor();
      				cout << endl;
				cout << "Pulsa ENTER para continuar..." << endl;
				while(getchar() != '\n'){};
        		break;	
      			case 'X': salir = r.confirmarsalida();
			break;
    		}
  	}

     return 0;
}
     
     
     
