#include <iostream>
#include <string>

#include "SuperTresEnRaya.hpp"

int main() {
	SuperTresEnRaya partida(false);
	std::string line;
	unsigned casilla;
	bool exito;
	unsigned short status = HECHA_ELEGIR_TABLERO;

	while (!partida.game_ended()) {
		if (status == HECHA_ELEGIR_TABLERO) {
			std::cout << partida << '\n';
			std::cout << "El jugador " << partida.get_player() << " tiene que elegir tablero en el que jugar\n";
			do {
				std::cout << "Elija tablero para jugar (1-9): ";
				std::getline(std::cin, line);
				try {
					casilla = std::stoi(line);
				} catch (...) {
					casilla = 0;
				}
				exito = partida.cambia_tablero(casilla);
			} while (!exito);

			std::cout << "\n\n\n";

		}
		std::cout << partida << '\n';
		std::cout << "Turno del jugador " << partida.get_player() << '\n';
		do {
			std::cout << "Elija casilla para jugar (1-9): ";
			std::getline(std::cin, line);
			try {
				casilla = std::stoi(line);
			} catch (...) {
				casilla = 0;
			}
			status = partida.play(casilla);
		} while (status == FALLIDA);

		std::cout << "\n\n\n";
	}

	std::cout << partida << '\n';

	if (partida.get_winner() != NONE)
		std::cout << "Ganó el jugador " << partida.get_winner() << '\n';
	else
		std::cout << "La partida acabó en empate\n";
}
