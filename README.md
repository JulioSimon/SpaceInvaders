# SpaceInvaders

### Introducción

Este proyecto intenta simular al clásico juego “Space Invaders”. El objetivo de este juego es repeler las 15 oleadas de marcianos, evitando que alcancen la Tierra. 

Se ha conseguido una ampliación de los niveles a 15 y el aumento de la dificultad del juego modificando la velocidad de los marcianos. Los marcianos en cada nivel de juego incrementarán su velocidad conforme se vayan eliminando, además, una vez alcanzado el nivel 5 o 10 se incrementará su velocidad global. También se ha conseguido un manejo total de las colisiones, misil-marciano, misil-misil, misil-tanque y la obtención de puntuación al eliminar los marcianos. Las puntuaciones, junto con el nombre del usuario, se almacenarán ordenadamente en un fichero tipo texto, mostrando en primer lugar el usuario que ha conseguido mayor puntuación y en último lugar el que menos. Cada jugador dispondrá de tres tanques para repeler las 15 oleadas de marcianos. El nombre del jugador, la puntuación, el nivel y la cantidad de vidas restantes, están presentes en pantalla.

No se ha realizado la elección del nivel de dificultad (fácil, difícil), pues el objetivo de este juego es conseguir la mayor puntuación posible teniendo todos los usuarios las mismas oportunidades. Por otra parte, no se ha conseguido la creación de los escudos ni de la aparición aleatoria del ovni.

### Uso

El proyecto se ha realizado sobre “ubuntu 10.04 LTS – la versión Lucid Lynx-”. Para el correcto funcionamiento del programa, se deben tener instaladas las siguientes librerías:

```<iostream>, <fstream>, <cstdlib>, <string>, <SDL.h>, <SDL_ttf.h>, <stdio.h>```

Para compilar el programa, se debe utilizar el siguiente código:

``g++ -o main *.cpp "sdl-config --cflags --libs" -lSDL_ttf``

Para su ejecución:

``./main recinto.txt``

Una vez dentro del juego, puedes salir de el en cualquier momento pulsando la tecla “Esc” o cerrando la ventana.
Adicionalmente, dentro del archivo comprimido, puedes encontrar la fuente utilizada por SDL_ttf.h y la propia librería.
