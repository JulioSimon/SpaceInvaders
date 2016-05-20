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

#include <fstream>
#include <iostream>
#include "CRecinto.h"


using namespace std;

const int SPRITE_W = 32;
const int SPRITE_H = 32;

const char spLIMITE[] = "img/limite.bmp";
const char spTIERRA[] = "img/tierra.bmp";
const char spCALAMAR[] = "img/calamar.bmp";
const char spCANGREJO[] = "img/cangrejo.bmp";
const char spPULPO[] = "img/pulpo.bmp";
const char spVACIO[] = "img/vacio.bmp";
const char spTANQUE[] = "img/tanque.bmp";
const char spLASERTANQUE[] = "img/laser.bmp";
const char spLASERMARCIANO[] = "img/laser2.bmp";
const char spVIDAS[] = "img/vidas.bmp";

CRecinto::CRecinto()
{
	alto = ALTO;
	ancho = ANCHO;
	direccion = 0;
	MARCIANO_TIME = 1000;
	contadorNiveles = 1;
	fase1 = fase2 = fase3 = fase4 = false;
}

CRecinto::~CRecinto()
{
     
}

/* ***************************************** */
/*   MENU PRINCIPAL                          */
/* ***************************************** */

char CRecinto :: menu()
{
  char op;
cout << endl;
cout << endl;
cout << "  " << "============================================================" << endl;  
cout << "  " << "                      INVASION MARCIANA                     " << endl;
cout << "  " << "============================================================" << endl;  
cout << "  " << "          `NMMMd                            `MMMMd          " << endl;
cout << "  " << "          `NMMMd`                           `MMMMd          " << endl;
cout << "  " << " ohhhy`    ::::/yhhh+                   shhhy::::-    -hhhh/" << endl;
cout << "  " << " hMMMN.        -MMMMy                  `mMMMN         :MMMMo" << endl;
cout << "  " << " hMMMN.   `////oMMMMd///////////////////mMMMM////:    :MMMMo" << endl;
cout << "  " << " hMMMN.   `NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMd    :MMMMo" << endl;
cout << "  " << " hMMMN.   `NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMd    :MMMMo" << endl;
cout << "  " << " hMMMN:...-NMMMMmmmmNMMMMMMMMMMMMMMMMMMMmmmmmMMMMd....+MMMMo" << endl;
cout << "  " << " hMMMMNNNNNMMMMd````+MMMMMMMMMMMMMMMMMMN-```.MMMMMNNNNNMMMMo" << endl;
cout << "  " << " hMMMMMMMMMMMMMd    /MMMMMMMMMMMMMMMMMMN.   `MMMMMMMMMMMMMMo" << endl;
cout << "  " << " hMMMMMMMMMMMMMNhhhhdMMMMMMMMMMMMMMMMMMMdhhhhMMMMMMMMMMMMMMo" << endl;
cout << "  " << " oyyyhNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNyyyy/" << endl;
cout << "  " << "     `mMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMh     " << endl;
cout << "  " << "     `dNNNNMMMMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNMMMMMNNNNy     " << endl;
cout << "  " << "      `...-NMMMm.............................MMMMd....`     " << endl;
cout << "  " << "          `NMMMd                            `MMMMd          " << endl;
cout << "  " << "      syyys////:                             ////+yyyy+     " << endl;
cout << "  " << "     `mMMMN`                                     -MMMMh     " << endl;
cout << "  " << "      yhhhy`                                     .hhhho     " << endl;
cout << "  " << "============================================================" << endl;
  cout << endl;
  cout << '\t' << "A.- Nueva Partida." << endl;
  cout << '\t' << "B.- Mostrar Puntuaciones Existentes." << endl;
  cout << '\t' << "C.- Eliminar todas las Puntuaciones." << endl;
  cout << endl;
  cout << '\t' << "D.- Instrucciones del Juego." << endl;
  cout << '\t' << "E.- Informacion del Autor." << endl;
  cout << endl;
  cout << '\t' << "X.- Salir del Programa." << endl;
  cout << endl;
  cout << '\t' << "Opción: ";
  
  cin >> op;
  
  op = toupper(op); // Por si la letra introducida está en minúsculas
  
  while ((op!='X') && ((op < 'A') || (op > 'G')))
  {
    cout << "Opción Incorrecta." << endl;
    cout << "Opción: " << endl;
    cin >> op;
    cin.ignore();     //limpia el ENTER del buffer de teclado
    op = toupper(op); // De nuevo por si la letra introducida está en minúsculas
  }
  return op;
}

bool CRecinto :: confirmarsalida()
{
  char n;
  
  cout << endl;
  cout << '\t' << "¿Quieres salir del programa (S/N)?" << endl;
  cin >> n;
  n = toupper (n);
  return (n == 'S');
}

void CRecinto :: InstruccionesJuego()
{
	cout << endl;
	cout << "  " << "----------------------------------------------------------------------------" << endl;
	cout << "  " << "|        OBJETIVO DEL JUEGO           |             CONTROLES              |" << endl;
	cout << "  " << "----------------------------------------------------------------------------" << endl;
	cout << "  " << "|   Debes evitar a toda costa que los |   ______________                   |" << endl;
	cout << "  " << "| marcianos lleguen a la tierra. Dis- |  |______________| -> Para Disparar |" << endl;
	cout << "  " << "| pones de 3 tanques para destruir las|      __                            |" << endl;
	cout << "  " << "| 15 oleadas de marcianos. Si lo con- |   __|__|__                         |" << endl;
	cout << "  " << "| sigues, ganas la partida.           |  |__|__|__| -> Para mover Tanque   |" << endl;
	cout << "  " << "----------------------------------------------------------------------------" << endl;
	cout << "  " << "|                                PUNTUACION                                |" << endl;
	cout << "  " << "----------------------------------------------------------------------------" << endl;
	cout << "  " << "|  Calamar (primera y segunda fila) = 50 puntos.                           |" << endl;
	cout << "  " << "|  Cangrejo (tercera y cuarta fila) = 100 puntos.                          |" << endl;
	cout << "  " << "|  Pulpo (ultima fila) = 200 puntos.                                       |" << endl;
	cout << "  " << "----------------------------------------------------------------------------" << endl;
}

void CRecinto :: InformacionAutor()
{
	cout << endl;
	cout << "  " << "----------------------------------------------------------------------------" << endl;
	cout << "  " << "|                           INFORMACION DEL AUTOR                          |" << endl;
	cout << "  " << "----------------------------------------------------------------------------" << endl;
	cout << "  " << "|   Nombre: Julio Jose Simon Gil                                           |" << endl;
	cout << "  " << "|   E-mail: juliojosesimongil@gmail.com                                    |" << endl;
	cout << "  " << "|           jjsimon@alu.uma.es                                             |" << endl;
	cout << "  " << "|                                                                          |" << endl;
	cout << "  " << "|   Curso: Primero                                                         |" << endl;
	cout << "  " << "|   Grupo: B                                                               |" << endl;
	cout << "  " << "----------------------------------------------------------------------------" << endl;
}

/* ***************************************** */
/*   SDL                                     */
/* ***************************************** */

int CRecinto::inicializaSDL()
{
     if (SDL_Init(SDL_INIT_VIDEO) < 0) 
     {
	  cout << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
	  return -1;
     }
     return 0;
}

int CRecinto::inicializaTEXTOSDL()
{
	if (TTF_Init() < 0) {
		cout << "No se pudo iniciar SDL_TTF: " << SDL_GetError() << endl;
		return -1;
	}
 
	return 0;
}

int CRecinto::inicializaVIDEO()
{
     screen = SDL_SetVideoMode(SPRITE_W*getAncho(),SPRITE_H*getAlto(),24,SDL_SWSURFACE| SDL_DOUBLEBUF);
     if (screen == NULL)
     {
	  cout << "No se pudo inicializar el modo Video: " << SDL_GetError() << endl;
	  return -1;
     }
     return 0;
}

/* ***************************************** */
/*   TEXTO SDL                               */
/* ***************************************** */

void CRecinto :: DibujarVidasTanque(int vidast)
{
	SDL_Rect dest;
     	SDL_Surface *image;
	int i;

	for(i=0; i<vidast; i++)
	{	
		//Cargar Imagen
		image = SDL_LoadBMP(spVIDAS);
		
		//Definir Posicion
		dest.x = (2*SPRITE_W + i*SPRITE_W);
		dest.y = 17*SPRITE_H;

		// Lo copiamos en la pantalla
	        SDL_BlitSurface(image, NULL, screen, &dest);
	       
	        // Liberamos la superficie
	        SDL_FreeSurface(image);
	}

	// Cargar Negro
	image = SDL_LoadBMP(spVACIO);
	//Definir Posicion
	dest.x = (2*SPRITE_W + (i)*SPRITE_W); // Tapa el tanque restante cuando se pierde una vida.
	dest.y = 17*SPRITE_H;
	//Copiar
	SDL_BlitSurface(image, NULL, screen, &dest);
	SDL_FreeSurface(image);
}
		
	

void CRecinto :: MostrarNombre(string nomb)
{

	SDL_Color bgcolor,fgcolor;
	SDL_Rect rectangulo;
	SDL_Surface *ttext;
	TTF_Font *fuente;
	
	// Cargar Fuente
	fuente = TTF_OpenFont("arial.ttf",18);
 
	// Definir Colores de los Numeros y del Background
	fgcolor.r=200;
	fgcolor.g=200;
	fgcolor.b=10;
 
	bgcolor.r=0;
	bgcolor.g=0;
	bgcolor.b=0;
 
	ttext = TTF_RenderText_Shaded(fuente,nomb.c_str(),fgcolor,bgcolor);
	rectangulo.y=17*SPRITE_H; // Definir Posicion
	rectangulo.x=20*SPRITE_W; //
	rectangulo.w=ttext->w;
	rectangulo.h=ttext->h;
 
	// Volcamos la superficie a la pantalla
	SDL_BlitSurface(ttext,NULL,screen,&rectangulo);
 
	// Eliminamos la Fuente
	TTF_CloseFont(fuente);
 
	// Liberar
    	SDL_FreeSurface(ttext);
}

void CRecinto :: MostrarPuntuacion(int punt)
{

	SDL_Color bgcolor,fgcolor;
	SDL_Rect rectangulo;
	SDL_Surface *ttext;
	TTF_Font *fuente;
	char msg[10];
	
	// Cargar Fuente
	fuente = TTF_OpenFont("arial.ttf",18);
 
	// Definir Colores de los Numeros y del Background
	fgcolor.r=200;
	fgcolor.g=200;
	fgcolor.b=10;
 
	bgcolor.r=0;
	bgcolor.g=0;
	bgcolor.b=0;
 
	sprintf(msg,"%d",punt); // Convertir puntuacion a char
	ttext = TTF_RenderText_Shaded(fuente,msg,fgcolor,bgcolor);
	rectangulo.y=17*SPRITE_H; // Definir Posicion
	rectangulo.x=29*SPRITE_W; //
	rectangulo.w=ttext->w;
	rectangulo.h=ttext->h;
 
	// Volcamos la superficie a la pantalla
	SDL_BlitSurface(ttext,NULL,screen,&rectangulo);
 
	// Eliminamos la Fuente
	TTF_CloseFont(fuente);
 
	// Liberar
    	SDL_FreeSurface(ttext);
}

void CRecinto :: MostrarNivel(int contadorNiveles)
{

	SDL_Color bgcolor,fgcolor;
	SDL_Rect rectangulo;
	SDL_Surface *ttext;
	TTF_Font *fuente;
	char msg[10];
	
	// Cargar Fuente
	fuente = TTF_OpenFont("arial.ttf",18);
 
	// Definir Colores de los Numeros y del Background
	fgcolor.r=10;
	fgcolor.g=200;
	fgcolor.b=10;

	if (contadorNiveles >= 5 && contadorNiveles < 10)
	{	
		fgcolor.r=200;
		fgcolor.g=10;
		fgcolor.b=10;
	}
	else
	if (contadorNiveles > 10)
	{
		fgcolor.r=150;
		fgcolor.g=150;
		fgcolor.b=10;
	}
		
 
	bgcolor.r=0;
	bgcolor.g=0;
	bgcolor.b=0;
 
	sprintf(msg,"%d",contadorNiveles); // Convertir puntuacion a char
	ttext = TTF_RenderText_Shaded(fuente,msg,fgcolor,bgcolor);
	rectangulo.y=1*SPRITE_W/2; // Definir Posicion
	rectangulo.x=29*SPRITE_W; //
	rectangulo.w=ttext->w;
	rectangulo.h=ttext->h;
 
	// Volcamos la superficie a la pantalla
	SDL_BlitSurface(ttext,NULL,screen,&rectangulo);
 
	// Eliminamos la Fuente
	TTF_CloseFont(fuente);
 
	// Liberar
    	SDL_FreeSurface(ttext);
}

/* ***************************************** */
/*  TANQUE                                   */
/* ***************************************** */

void CRecinto :: borrarTanque(SDL_Rect &dest)
{
	SDL_Surface *image;
	
	// Imagen que reemplazará al tanque
	image = SDL_LoadBMP("img/negro.bmp");
	       
	// Lo copiamos en la pantalla
	SDL_BlitSurface(image, NULL, screen, &dest);
	       
	// Liberamos la superficie
	SDL_FreeSurface(image);
}

void CRecinto::posiciontanque(CTanque &t, SDL_Rect &dest)
{
     /** Cuidado al poner este bloque dentro de un bucle en el main, **/
	       dest.x = t.showpostanqueX()*SPRITE_W;
	       dest.y = t.showpostanqueY()*SPRITE_H;
	       dest.w = SPRITE_W;
	       dest.h = SPRITE_H;
}
     
void CRecinto::movertanque(CTanque &t, CMisil &l, TMovimiento m, SDL_Rect &dest)
{
     int done = 0;
     
	  Uint8 *keys;
	  SDL_Surface *image;
	  SDL_Event event;
	  
	  if((m == IZQUIERDA) && (dest.x > 32)) // Movimiento a la izquierda
	  {
	       // Imagen que reemplazará al tanque, para luego definir una nueva posicion 
	       // y volver a copiar el tanque 5 pixels hacia la izquierda.
	       image = SDL_LoadBMP("img/negro.bmp");
	       
	       // Lo copiamos en la pantalla
	       SDL_BlitSurface(image, NULL, screen, &dest);
	       
	       // Liberamos la superficie
	       SDL_FreeSurface(image);
	       
	       image = SDL_LoadBMP(spTANQUE); // Cargar Tanque
	       SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0)); // Transparencia
	       
	       // Definir nueva posicion
		   dest.x -= 5;
		   
	       // Guardar la nueva posicion del tanque.
	       t.setpostanque(dest.x,dest.y);
	       
	       // Lo copiamos en la pantalla
	       SDL_BlitSurface(image, NULL, screen, &dest);
	       
	       // Liberamos la superficie
	       SDL_FreeSurface(image);
	  }
	  if((m == DERECHA) && (dest.x < (SPRITE_W*getAncho()) - (SPRITE_W*2))) // Movimiento a la derecha
	  {	
	       // Imagen que reemplazará al tanque, para luego definir una nueva posicion 
	       // y volver a copiar el tanque 5 pixels hacia la izquierda.
	       image = SDL_LoadBMP("img/negro.bmp");
	       
	       // Lo copiamos en la pantalla
	       SDL_BlitSurface(image, NULL, screen, &dest);
	       
	       // Liberamos la superficie
	       SDL_FreeSurface(image);
	       
	       image = SDL_LoadBMP(spTANQUE); // Cargar Tanque
	       SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0)); // Transparencia
	       
	       // Definir nueva posicion
	       dest.x += 5;
	       
	       // Guardar la nueva posicion del tanque.
	       t.setpostanque(dest.x,dest.y);
	       
	       // Lo copiamos en la pantalla
	       SDL_BlitSurface(image, NULL, screen, &dest);
	       
	       // Liberamos la superficie
	       SDL_FreeSurface(image);
	       
	  }
      // Mostramos la pantalla
      SDL_Flip(screen);
}

/* ***************************************** */
/*  LASER                                    */
/* ***************************************** */

void CRecinto::dibujarlaser(CTanque &t, CMisil &l, CMarciano &q, CMarcador &n, TAccion a, SDL_Rect &dest, SDL_Rect &desq, SDL_Rect &destanque)
{
	SDL_Surface *image;
	int i,j;

	l.CrearMisil(MISILMARCIANO, *this, t, q, dest, desq);

	if (a == FUEGO)
	{	
		//Define la poscion del disparo, para que se cubra de negro y luego lo dibuje 5 pixels mas arriba.
		l.CrearMisil(MISILTANQUE, *this, t, q, dest, desq);
	}
	if(l.EstaLlena()) /** Si EstaLlena, existen disparos activos. **/
	{	
		if(l.HayLaser(MISILTANQUE))
		{
			image = SDL_LoadBMP("img/negrolaser.bmp"); //Cargar
			SDL_BlitSurface(image, NULL, screen, &dest); //Copiar
			SDL_FreeSurface(image); //Liberar
		}

		if(l.HayLaser(MISILMARCIANO))
		{
			image = SDL_LoadBMP("img/negrolaser2.bmp"); //Cargar
			SDL_BlitSurface(image, NULL, screen, &desq); //Copiar		
			SDL_FreeSurface(image); //Liberar
		}		
		// Definir nueva posicion
		l.MueveLaser(dest, desq);


		if(l.HayLaser(MISILMARCIANO))
		{
			image = SDL_LoadBMP (spLASERMARCIANO); // Cargar Laser Marciano
			SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0)); // Transparencia

			SDL_BlitSurface(image, NULL, screen, &desq); // Copiar Laser Marciano
	    	   
			// Liberamos la superficie
			SDL_FreeSurface(image);
			
			/** Colision LaserMarciano - Tanque **/
			colisionLaserM_Tanque(l, t, dest, destanque);

			
		}


		if(l.HayLaser(MISILTANQUE))
		{
			image = SDL_LoadBMP(spLASERTANQUE); // Cargar Laser Tanque
			SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0)); // Transparencia

			SDL_BlitSurface(image, NULL, screen, &dest); // Copiar Laser Tanque
			// Liberamos la superficie
			SDL_FreeSurface(image);
	
			if (dest.y <= 0 || dest.y >= 576) //Reemplaza el laser por spNEGRO cuando BorrarLaser lo libera de la memoria.
			{
				image = SDL_LoadBMP("img/negrolaser.bmp"); //Cargar
				SDL_BlitSurface(image, NULL, screen, &dest); //Copiar
				SDL_FreeSurface(image); //Liberar
			}

			/** Colision LaserTanque - Marciano **/
			colisionLaserT_Marciano(l,n,dest);
		}

		/** Colision LaserTanque - LaserMarciano **/
		colisionLaserT_LaserM(l,dest);
	}
}

/* ***************************************** */
/*  COLISIONES                               */
/* ***************************************** */

void CRecinto :: colisionLaserT_Marciano(CMisil &l, CMarcador &n, SDL_Rect &dest)
{
	int PosMisilX = l.GetPosMisilX(MISILTANQUE);
	int PosMisilY = l.GetPosMisilY(MISILTANQUE);
	int i,j;
	SDL_Surface *image;
	
	for(i=0;i<ALTO-4;i++)
	{
		for(j=0;j<ANCHO;j++)
		{										// 2 y 14, ancho y alto del laser
			if((((j*SPRITE_W)+SPRITE_W)>PosMisilX) && (((i*SPRITE_H)+SPRITE_H)>PosMisilY) && ((PosMisilX+2)>j*SPRITE_W) && ((PosMisilY+14)>i*SPRITE_H))
			{						
				if((recinto[i][j] == CALAMAR || recinto[i][j] == PULPO || recinto[i][j] == CANGREJO))
				{
					//////////////////////////////////////////
		     			// Actualizar Puntuacion                //
		     			//////////////////////////////////////////
		     			if(recinto[i][j] == CALAMAR){ n.ActualizarPuntuacion(MAS,50);}
		     			else
		     			if(recinto[i][j] == CANGREJO){ n.ActualizarPuntuacion(MAS,100);}
		     			else
		     			if(recinto[i][j] == PULPO){ n.ActualizarPuntuacion(MAS,200);}
	
					////////////////////////////////////////
					// Borramos el Marciano               //
		     			////////////////////////////////////////

		     			recinto[i][j] = VACIO;
							
					// Imagen que reemplazará al marciano.
		     			image = SDL_LoadBMP("img/negro.bmp");
		      
		   			//Definimos su posicion
		    			dest.x = j*SPRITE_W;
		    			dest.y = i*SPRITE_H;
	   				dest.w = image->w;
		     			dest.h = image->h;
		       
		     			// Lo copiamos en la pantalla
		     			SDL_BlitSurface(image, NULL, screen, &dest);
		       
		     			// Liberamos la superficie
		     			SDL_FreeSurface(image);
	
			
					////////////////////////////////////////
					// Borramos el Misil                  //
		     			////////////////////////////////////////

		     			l.BorrarMisil(MISILTANQUE);
		     					
					// Imagen que reemplazará al marciano.
		     			image = SDL_LoadBMP("img/negrolaser.bmp");
			      
		    			//Definimos su posicion
		     			dest.x = PosMisilX;
		     			dest.y = PosMisilY;
		     			dest.w = image->w;
		     			dest.h = image->h;
	
		     			// Lo copiamos en la pantalla
		     			SDL_BlitSurface(image, NULL, screen, &dest);

		     			// Liberamos la superficie
		     			SDL_FreeSurface(image);
				}
			}
		}
	}
}

void CRecinto :: colisionLaserT_LaserM(CMisil &l, SDL_Rect &dest)
{
	int PosMisilX = l.GetPosMisilX(MISILTANQUE);
	int PosMisilY = l.GetPosMisilY(MISILTANQUE);
	int PosMisilMarX = l.GetPosMisilX(MISILMARCIANO);
	int PosMisilMarY = l.GetPosMisilY(MISILMARCIANO);
	int i,j;
	SDL_Surface *image;
	
	for(i=0;i<ALTO-4;i++)
	{
		for(j=0;j<ANCHO;j++)
		{										// 2 y 14, ancho y alto del laser
			if(((PosMisilMarX+6)>PosMisilX) && ((PosMisilMarY+14)>PosMisilY) && ((PosMisilX+2)>PosMisilMarX) && ((PosMisilY+14)>PosMisilMarY))
			{					
					////////////////////////////////////////
					// Borramos Misil Marciano            //
		     			////////////////////////////////////////

		     			l.BorrarMisil(MISILMARCIANO);
							
					// Imagen que reemplazará al marciano.
		     			image = SDL_LoadBMP("img/negrolaser2.bmp");
		      
		   			//Definimos su posicion
		    			dest.x = PosMisilMarX;
		    			dest.y = PosMisilMarY;
	   				dest.w = image->w;
		     			dest.h = image->h;
		       
		     			// Lo copiamos en la pantalla
		     			SDL_BlitSurface(image, NULL, screen, &dest);
		       
		     			// Liberamos la superficie
		     			SDL_FreeSurface(image);
	
			
					////////////////////////////////////////
					// Borramos el Misil Tanque           //
		     			////////////////////////////////////////

		     			l.BorrarMisil(MISILTANQUE);
		     					
					// Imagen que reemplazará al marciano.
		     			image = SDL_LoadBMP("img/negrolaser.bmp");
			      
		    			//Definimos su posicion
		     			dest.x = PosMisilX;
		     			dest.y = PosMisilY;
		     			dest.w = image->w;
		     			dest.h = image->h;
	
		     			// Lo copiamos en la pantalla
		     			SDL_BlitSurface(image, NULL, screen, &dest);

		     			// Liberamos la superficie
		     			SDL_FreeSurface(image);
			}
		}
	}
}

void CRecinto :: colisionLaserM_Tanque(CMisil &l, CTanque &t,SDL_Rect &dest, SDL_Rect &destanque)
{
	int PosMisilMarX = l.GetPosMisilX(MISILMARCIANO);
	int PosMisilMarY = l.GetPosMisilY(MISILMARCIANO);
	int i,j;
	SDL_Surface *image;
	
	for(i=0;i<ALTO-4;i++)
	{
		for(j=0;j<ANCHO;j++)
		{										// 2 y 14, ancho y alto del laser
			if((((t.showpostanqueX())+SPRITE_W)>PosMisilMarX) && (((t.showpostanqueY())+SPRITE_H)>PosMisilMarY) && ((PosMisilMarX+6)>t.showpostanqueX()) && ((PosMisilMarY+14)>t.showpostanqueY()))
			{

					SDL_Delay(500);

					////////////////////////////////////////
					// Reducir Vidas del Tanque           //
					////////////////////////////////////////
					t.ModificarVidasTanque(REDUCIR,1);
					
					////////////////////////////////////////
					// Borramos Misil Marciano            //
		     			////////////////////////////////////////

		     			l.BorrarMisil(MISILMARCIANO);
							
					// Imagen que reemplazará al marciano.
		     			image = SDL_LoadBMP("img/negrolaser2.bmp");
		      
		   			//Definimos su posicion
		    			dest.x = PosMisilMarX;
		    			dest.y = PosMisilMarY;
	   				dest.w = image->w;
		     			dest.h = image->h;
		       
		     			// Lo copiamos en la pantalla
		     			SDL_BlitSurface(image, NULL, screen, &dest);
		       
		     			// Liberamos la superficie
		     			SDL_FreeSurface(image);
	
			
					////////////////////////////////////////
					// Borramos Tanque                    //
		     			////////////////////////////////////////

		     			// Imagen que reemplazará al tanque
					image = SDL_LoadBMP("img/negro.bmp");

					dest.x = t.showpostanqueX();
		     			dest.y = t.showpostanqueY();
		     			dest.w = image->w;
		     			dest.h = image->h;
	       
					// Lo copiamos en la pantalla
					SDL_BlitSurface(image, NULL, screen, &dest);
	       
					// Liberamos la superficie
					SDL_FreeSurface(image);

					////////////////////////////////////////
					// Inicializar Movimiento Tanque      //
					////////////////////////////////////////
					t.setpostanque(t.showpostanqueinicioX()*SPRITE_W,t.showpostanqueinicioY()*SPRITE_H);
					destanque.x = t.showpostanqueinicioX()*SPRITE_W;

		     			////////////////////////////////////////
		     			// Redibujar Tanque                   //
		     			////////////////////////////////////////
		     					
					// Imagen que reemplazará al marciano.
		     			image = SDL_LoadBMP(spTANQUE);
			      
		    			//Definimos su nueva posicion
		     			dest.x = t.showpostanqueinicioX()*SPRITE_W;
		     			dest.y = t.showpostanqueinicioY()*SPRITE_H;
		     			dest.w = image->w;
		     			dest.h = image->h;
	
		     			// Lo copiamos en la pantalla
		     			SDL_BlitSurface(image, NULL, screen, &dest);

		     			// Liberamos la superficie
		     			SDL_FreeSurface(image);
			}
		}
	}
}

/* ***************************************** */
/*  MARCIANO                                 */
/* ***************************************** */

long CRecinto :: getMarcianoTime()
{
	return MARCIANO_TIME;
}

void CRecinto :: resetearFases()
{
	fase1 = fase2 = fase3 = fase4 = false;
}

int CRecinto :: GetContadorNiveles()
{
	return contadorNiveles;
}

void CRecinto :: incrementarNivel()
{
	contadorNiveles++;
}

void CRecinto :: fijarNuevaVelocidad (int nuevavelocidad)
{
	MARCIANO_TIME = nuevavelocidad;
}

void CRecinto :: reducirMarcianoTime (int marcianos)
{
	if(marcianos < 60 && marcianos >= 45 && fase1 == false){ MARCIANO_TIME = MARCIANO_TIME - 200; fase1 = true;}
	else
	if(marcianos < 45 && marcianos >= 30 && fase2 == false){ MARCIANO_TIME = MARCIANO_TIME - 200; fase2 = true;}
	else
	if(marcianos < 30 && marcianos >= 15 && fase3 == false){ MARCIANO_TIME = MARCIANO_TIME - 200; fase3 = true;}
	else
	if(marcianos < 15 && fase4 == false){ MARCIANO_TIME = MARCIANO_TIME - 100; fase4 = true;}

}

void CRecinto :: nivelCompletado (int &done)
{	
	if(numeroMarcianos() <= 0)
	{
		SDL_Delay(1000);
		done = 1;
	}
}

int CRecinto :: numeroMarcianos()
{
	int i,j;
	int contador = 0;

	for(i=0;i<ALTO;i++)
	{
		for(j=0;j<ANCHO;j++)
		{
			if((recinto[i][j] == CALAMAR || recinto[i][j] == PULPO || recinto[i][j] == CANGREJO))
			{
				contador++;
			}
		}
	}

	return contador;
}

void CRecinto :: actualizarDireccion()
{
	direccion = 0;
}

void CRecinto::actualizarmarcianos (int i, int j, const int direccion, SDL_Rect &desq)
{
     SDL_Surface *image;
     
     if((recinto[i][j] == CALAMAR || recinto[i][j] == PULPO || recinto[i][j] == CANGREJO))
	{
	     // Imagen que reemplazará al marciano.
	     image = SDL_LoadBMP("img/negro.bmp");
			      
	     //Definimos su posicion
	     desq.x = j*SPRITE_W;
	     desq.y = i*SPRITE_H;
	     desq.w = image->w;
	     desq.h = image->h;
	       
	     // Lo copiamos en la pantalla
	     SDL_BlitSurface(image, NULL, screen, &desq);
	       
	     // Liberamos la superficie
	     SDL_FreeSurface(image);
			      
	     /** ////////////////////////////////////////////////////////// **/
			      
	     if(getContenido(i,j) == CALAMAR)
	     {
		  image = SDL_LoadBMP(spCALAMAR); // Cargar Calamar
	     }
	     if(getContenido(i,j) == CANGREJO) 
	     {
		  image = SDL_LoadBMP(spCANGREJO); // Cargar Cangrejo
	     }
	     if(getContenido(i,j) == PULPO) 
	     {
		  image = SDL_LoadBMP(spPULPO); // Cargar Pulpo
	     }

	     
	     // Definir nueva posicion (segun la direccion de los marcianos)
	     if (direccion == 0)
	     { 
 		  desq.x = (j-1)*SPRITE_W;
		  desq.y = i*SPRITE_H;
	     }
	     else if (direccion == 1)
	     {
		  desq.x = j*SPRITE_W;
		  desq.y = (i+1)*SPRITE_H; 
	     }
	     else if (direccion == 2)
	     {
		  desq.x = (j+1)*SPRITE_W;
		  desq.y = i*SPRITE_H;
	     }
	     
	     desq.w = image->w;
	     desq.h = image->h;
			 
	     // Lo copiamos en la pantalla
	     SDL_BlitSurface(image, NULL, screen, &desq);
	     
	     // Liberamos la superficie
	     SDL_FreeSurface(image);
	}
}

/* ***************************************** */
/*   FICHERO                                 */
/* ***************************************** */

int CRecinto::getAncho() { return ancho;}
int CRecinto::getAlto() { return alto;}

int CRecinto::cargarFichero(const char nombre[], CTanque &t)
{
	ifstream f;
	char c;
	int i,j;

	f.open(nombre);

	if(f.fail())
	{
	     cout << "Error en la apertura del Fichero!" << endl;
	     return -1;
	}

	for(i = 0 ; i < alto; i++)
	{
		for(j = 0; j < ancho; j++)
		{
			f.get(c);
			switch(c)
			{	// Asignamos el enumerado correspondiente a cada letra del fichero.
				case cLIMITE: recinto[i][j] = VACIO; break;
				case cTIERRA:  recinto[i][j] = TIERRA; break;
				case cCALAMAR: recinto[i][j] = CALAMAR; break;
				case cCANGREJO: recinto[i][j] = CANGREJO; break;
				case cPULPO: recinto[i][j] = PULPO; break;
				case cINICIO: recinto[i][j] = TANQUE; t.setpostanque(j,i);	//Guarda la posicion de inicio en X,Y_ACTUAL
								      t.setpostanqueinicio(j,i);  //Guarda la posicion de inicio en X,Y_INICIO
				default:	recinto[i][j] = VACIO;
			}
		}
		
		f.ignore();		
	}
	f.close();
	return 0;
}

TContenido CRecinto::getContenido(const int x, const int y) const
{
	return recinto[x][y];
}

void CRecinto::dibujarRecinto(CTanque &t, CMisil &l)
{
     SDL_Rect dest;
     SDL_Surface *image;
     int x,y;
     int misilx, misily;
     
     for (int i = 0; i < getAlto(); i++)
     {
	  for (int j = 0; j < getAncho(); j++)
	  {
	       //Cargamos los gráficos
	       if(getContenido(i,j) == LIMITE)
	       {
		    image = SDL_LoadBMP(spVACIO);
		    SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0));
	       }
	       else if (getContenido(i,j) == TIERRA)
	       {
		    image = SDL_LoadBMP(spVACIO);
		    SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0));
	       }
	       else if (getContenido(i,j) == CALAMAR)
	       {
		    image = SDL_LoadBMP(spCALAMAR);
		    SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0));
	       }
	       else if (getContenido(i,j) == CANGREJO)
	       {
		    image = SDL_LoadBMP(spCANGREJO);
		    SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0));
	       }
	       else if (getContenido(i,j) == PULPO)
	       {
		    image = SDL_LoadBMP(spPULPO);
		    SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0));
	       }
	       else
	       {
		    image = SDL_LoadBMP(spVACIO);
		    SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0));
	       }
	       
	       //Definimos su posicion
	       dest.x = j*SPRITE_W;
	       dest.y = i*SPRITE_H;
	       dest.w = image->w;
	       dest.h = image->h;
	       
	       // Lo copiamos en la pantalla
	       SDL_BlitSurface(image, NULL, screen, &dest);
	       
	       // Liberamos la superficie
	       SDL_FreeSurface(image);
	       
	  }  
     }
     
     // Cargamos el Tanque.
     image = SDL_LoadBMP(spTANQUE);
     SDL_SetColorKey(image, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(image->format,0,0,0));
     
     // Definimos la posicion del tanque. // Y la del misil!
     dest.x = t.showpostanqueX()*SPRITE_W;
     dest.y = t.showpostanqueY()*SPRITE_H; 
     dest.w = SPRITE_W;
     dest.h = SPRITE_H;
     
     // Lo copiamos en la pantalla
     SDL_BlitSurface(image, NULL, screen, &dest);
     
     //Liberamos la supercficie.
     SDL_FreeSurface(image);
}
	
     
