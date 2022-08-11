#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Declaracion de variables globales

// Funcion de asignacion de carta
int Repartir_Carta();

// Declarar arreglo booleano
bool BCartas[52];

// Declarar arreglo con todas las cartas
string SCartas[52] = { "As de Corazones", "Corazones (2)", "Corazones (3)","Corazones (4)","Corazones (5)","Corazones (6)","Corazones (7)","Corazones (8)","Corazones (9)","Corazones (10)","Corazones (J)","Corazones (Q)","Corazones (R)", "As de Picas", "Picas (2)", "Picas (3)", "Picas (4)", "Picas (5)", "Picas (6)", "Picas (7)", "Picas (8)", "Picas (9)", "Picas (10)", "Picas (J)", "Picas (Q)", "Picas (R)", "As de Diamantes", "Diamantes (2)", "Diamantes (3)", "Diamantes (4)", "Diamantes (5)", "Diamantes (6)", "Diamantes (7)", "Diamantes (8)", "Diamantes (9)", "Diamantes (10)", "Diamantes (J)", "Diamantes (Q)", "Diamantes (R)", "As de Treboles", "Treboles (2)", "Treboles (3)", "Treboles (4)", "Treboles (5)", "Treboles (6)", "Treboles (7)", "Treboles (8)", "Treboles (9)", "Treboles (10)", "Treboles (J)", "Treboles (Q)", "Treboles (R)" };

// Declarar arreglo con el valor de las cartas
int ICartas[52] = { 1,2,3,4,5,6,7,8,9,10,10,10,10,1,2,3,4,5,6,7,8,9,10,10,10,10,1,2,3,4,5,6,7,8,9,10,10,10,10,1,2,3,4,5,6,7,8,9,10,10,10,10 };

/**
 * Estructura Player-Miembros:
 * - Suma: Puntos de cada jugador
 * - Dinero: Dinero actual del jugador
 * - Apuesta: Dinero apostado por el jugador en la ronda actual
 * - J_Nombre: Nombre del jugador
 * - Activo: Booleano para saber si el jugador tiene dinero, se inicia como true
 */
struct Players {
	int Suma, Dinero, Apuesta;
	string J_Nombre;
	bool Activo;
} Jugador[4];

int main () {
  cout << "Hello, world!" << endl;

  // Se abre el archivo para registro de partidas
	fstream BlackJack;
	BlackJack.open("BlackJack.txt", std::fstream::in | std::fstream::out | std::fstream::app);

  // Declarar variables
	int Num_Carta, Num_Jugadores, Respuesta = 1, Carta = 1, Victoria = 100;
	int Premio;
	string Repetir;

	// Preguntar el numero de personas a jugar... Maximo 3
	cout << "Bienvenido(s) a BlackJack" << endl << "¿Cuantas personas jugaran esta partida? (De 1 a 3 jugadores)" << endl;
	cin >> Num_Jugadores;

	while (Num_Jugadores < 1 || Num_Jugadores > 3) { // Validar el numero de jugadores
		cout << endl << "Ingresa un numero de jugadores valido" << endl;
		cin >> Num_Jugadores;
	}

	Jugador[Num_Jugadores].J_Nombre = "Dealer"; // Nombre del Dealer

  // Se pregunta el nombre de los jugadores y se inicializan sus valores
	for (int Contador = 0; Contador < Num_Jugadores; Contador++) {
		cout << endl << "Nombre del Jugador #" << Contador + 1 << endl;
		cin >> Jugador[Contador].J_Nombre;

		Jugador[Contador].Dinero = 1000;
		Jugador[Contador].Activo = true;
		system("pause");
	}

	Jugador[Num_Jugadores].Activo = true;
	system("cls"); // Limpiar la pantalla de introduccion y los nombres

	// Bucle para validar si al menos un jugador tiene dinero, mediante su bool Activo
	while (Jugador[0].Activo == 1 || Jugador[1].Activo == 1 || Jugador[2].Activo == 1) {

		// Habilitar las cartas de nuevo
		Premio = 0;

		for (int Contador = 0; Contador <= 51; Contador++)
			BCartas[Contador] = true;
		
    Victoria = 100;

		for (int Contador = 0; Contador < Num_Jugadores; Contador++) {
      
			if (Jugador[Contador].Activo == false)
				continue;

			// Bucle para validar una apuesta ingresada, con minimo de 1 y maximo del dinero actual del jugador
			if (Contador != Num_Jugadores) {
				while (true) {
					cout << Jugador[Contador].J_Nombre << ", Cuanto apuestas?" << endl;
					cin >> Jugador[Contador].Apuesta;

					if (Jugador[Contador].Apuesta >= 1 && Jugador[Contador].Apuesta <= Jugador[Contador].Dinero)
						break;
					
          cout << "Ingresa una apuesta valida" << endl;
				}
				// Asignacion de valores de la apuesta de cada jugador y el premio de victoria
				Jugador[Contador].Dinero -= Jugador[Contador].Apuesta;
				Premio += Jugador[Contador].Apuesta;
			}
		}

		for (int Contador = 0; Contador <= Num_Jugadores; Contador++) { // El "for" recorre cada jugador
		
			// Si el jugador actual no tiene dinero, se saltara su turno en el bucle
			if (Jugador[Contador].Activo == false)
				continue;
        
			system("cls");

			// Inicializacion de variables del turno del jugador
			Respuesta = 1;
			Carta = 1;
			Jugador[Contador].Suma = 0;
			cout << "Turno de: " << Jugador[Contador].J_Nombre << endl; // Imprimir el nombre del jugador en turno
			
			Carta = 0; // Reinicia el conteo de las cartas que a tomado el jugador

			// Bucle externo para repartir cartas
			while (Respuesta == 1 && Carta <= 4 && Jugador[Contador].Suma != 21) { // El "while" repite el proceso de reparto de cartas hasta que el usuario pare... O se pase de 21... O ya tenga mas de 5 cartas
  
				// Bucle interno para las dos primeras cartas
				do {
					// Asignar carta aleatoria
					Num_Carta = Repartir_Carta();
					BCartas[Num_Carta] = false;
					Carta++;

					// Mostrar carta
					if (ICartas[Num_Carta] == 1 || ICartas[Num_Carta] == 11) {
            
						// Si la carta fue un AS, pedir el valor de 1 u 11
						cout << endl << "Obtuviste un " << SCartas[Num_Carta] << endl << "¿Quieres que su valor sea 1 u 11?" << endl;
						cin >> ICartas[Num_Carta];

						while (ICartas[Num_Carta] != 1 && ICartas[Num_Carta] != 11) {
							cout << "Escoje entre 1 u 11" << endl;
							cin >> ICartas[Num_Carta];
						}
					}

					else {
						// Cuaquier otra carta diferente de AS
						cout << Jugador[Contador].J_Nombre << ", Tu carta #" << Carta << " es: " << SCartas[Num_Carta] << endl;
					}
          
					Jugador[Contador].Suma += ICartas[Num_Carta]; //Sumar el valor de las cartas e imprimir
					cout << "Hasta el momento tu sumatoria es de: " << Jugador[Contador].Suma << endl;
          
				} while (Carta < 2);

				if (Jugador[Contador].Suma == 21) // Ver si el jugador gano con 21
				{
					cout << endl << "¡Felicidades! ¡Has conseguido 21! ¡Has ganado!" << endl;
					break;
				}
				else
				{
					if (Jugador[Contador].Suma > 21)
					{
						cout << endl << "¡Suerte a la proxima! Te has pasado de 21" << endl;
						Jugador[Contador].Suma = 0;
						system("pause");
						system("cls");
						break;
					}
					else
					{
						// Preguntar si quiere otra carta
						cout << endl << "¿Quieres otra carta?" << endl << "1 --> Si" << endl << "0 --> No" << endl;
						cin >> Respuesta;
						while (Respuesta != 0 && Respuesta != 1) // Validar la respuesta
						{
							cout << endl << "Escoje" << endl << "1 --> Si" << endl << "0 --> No";
							cin >> Respuesta;
						}
						if (Respuesta == 0 || Carta == 6)
						{
							cout << endl << "Tu turno ha acabado" << endl;
							system("pause");
							break;
						}
						system("cls"); // Limpiar pantalla
					}
				}
			}

			// Seccion del turno acabado del jugador
			if (Jugador[Contador].Suma == 21)
			{
				Victoria = Contador;
				break;
			}

			// Asignacion del index de victoria por comparacion
			if (Contador > 0)
			{
				if (Contador != Num_Jugadores) // Regresar si fallo
				{
					if (Jugador[Contador].Suma > Jugador[Contador - 1].Suma)
						Victoria = Contador;
					else
						Victoria = Contador - 1;
				}
				else
				{
					if (Jugador[Contador].Suma > Jugador[0].Suma && Jugador[Contador].Suma > Jugador[Victoria].Suma)
						Victoria = Contador;
					else {
						if (Jugador[0].Suma > Jugador[Victoria].Suma)
							Victoria = 0;
					}
				}

			}
		}

		system("cls");
		// Impresion de las diferentes posibilidades de victoria
    
		// Caso del dealer
		if (Victoria == Num_Jugadores) {
			cout << "La casa gano el premio de " << Premio << endl << "Puntos: " << Jugador[Victoria].Suma << endl;
			BlackJack << endl << "La casa gano el premio de " << Premio << endl << "Puntos: " << Jugador[Victoria].Suma << endl;
		}
		else {
			// Caso de que todos pierdan
			if (Victoria == 100)
			{
				cout << "Todos perdieron y recuperaron sus apuestas" << endl;
				BlackJack << "Todos perdieron y recuperaron sus apuestas" << endl;
			}

			// Caso de victoria para un jugador
			else {
				cout << "El dealer suma la apuesta de " << Jugador[Victoria].J_Nombre << " al premio de " << Premio << endl;
				BlackJack << endl << "El dealer suma la apuesta de " << Jugador[Victoria].Suma << " al premio de " << Premio << endl;
				Premio += Jugador[Victoria].Apuesta;
        
				// Mostrar la victoria de X Jugador
				Jugador[Victoria].Dinero += Premio;
				cout << Jugador[Victoria].J_Nombre << " ¡Ha ganado esta ronda y el premio de " << Premio << "!" << endl << "Puntos: " << Jugador[Victoria].Suma << endl;
				BlackJack << Jugador[Victoria].J_Nombre << " ¡Ha ganado esta ronda y el premio de " << Premio << "!" << endl << "Puntos: " << Jugador[Victoria].Suma << endl;
			}
		}

		// Gestion e impresion del dinero de la ronda
		for (int Contador = 0; Contador < Num_Jugadores; Contador++) {
			// Si nadie gana, cada jugador recupera su apuesta
			if (Victoria == 100)
				Jugador[Contador].Dinero += Jugador[Contador].Apuesta;

			// Impresion del dinero de cada jugador
			cout << "Dinero de " << Jugador[Contador].J_Nombre << ": " << Jugador[Contador].Dinero << endl;
			BlackJack << "Dinero de " << Jugador[Contador].J_Nombre << ": " << Jugador[Contador].Dinero << endl;

			// Eliminacion de un jugador sin dinero restante
			if (Jugador[Contador].Dinero < 1) {
				Jugador[Contador].Activo = false;
				cout << Jugador[Contador].J_Nombre << " se quedo sin dinero y ya no esta en la partida " << endl;
				BlackJack << Jugador[Contador].J_Nombre << " se quedo sin dinero y ya no esta en la partida " << endl;
			}
		}
    
		// Bucle para administracion del booleano del dealer, validando si al menos un jugador tiene dinero restante
		Jugador[Num_Jugadores].Activo = false;

		for (int Contador = 0; Contador <= Num_Jugadores - 1; Contador++) {
			if (Jugador[Contador].Activo == true) {
				Jugador[Num_Jugadores].Activo = true;
				break;
			}
		}

		// Se pregunta al usuario si desea seguir jugando
		cout << "Seguir jugando?\n1-Si\n0-No" << endl;
		cin >> Repetir;
    
		if (Repetir == "0")
			break;

		system("pause");
	}

	// Fin del juego y del programa
	cout << "Fin del juego" << endl;
	BlackJack << "Fin del juego" << endl;
	system("pause");
	BlackJack.close();
	return 0;
}

// Funcion Repartir carta-Sin parametros: Se usa cada vez que se asigna una carta
int Repartir_Carta()
{
	// Inicializar aleatorios
	srand(time(NULL));
	int Aleatorio = rand() % 52;
  
	while (BCartas[Aleatorio] == false)
		Aleatorio = rand() % 52;
    
	return Aleatorio;
}