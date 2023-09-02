#include "SuperTresEnRaya.hpp"

std::ostream& operator<<(std::ostream& os, const SuperTresEnRaya& p) {
	unsigned i, j;
	unsigned short player;
	std::string line, mark;
	std::vector<std::string> lines;
	std::string line_up, line_mid, line_down;
	std::string sep_simple(5, '-'), sep_doble(19, '=');

	sep_simple = "\t\t" + sep_simple + "||" + sep_simple + "||" + sep_simple;
	sep_doble = "\t\t" + sep_doble;

	for (i = 0; i < 3; i++) {
		line_up = "\t\t"; line_mid = "\t\t"; line_down = "\t\t";
		for (j = 0; j < 3; j++) {
			if (j > 0) {
				line_up += "||";
				line_mid += "||";
				line_down += "||";
			}
			if (p.super_partida[i][j].game_ended()) {
				player = p.super_partida[i][j].get_winner();
				if (player == PLAYER1) {
					line = "\033[31m";
					mark = "X";
				} else if (player == PLAYER2) {
					line = "\033[34m";
					mark = "O";
				} else {
					line = "\033[90m";
					mark = "-";
				}
				line += mark + "|" + mark + "|" + mark + "\033[0m";
				line_up += line; line_mid += line; line_down += line;
			} else {
				if (i == p.tablero_actual.i && j == p.tablero_actual.j) {
					line_up += "\033[1;32m";
					line_mid += "\033[1;32m";
					line_down += "\033[1;32m";
				}

				lines = p.super_partida[i][j].get_tablero_vs();

				line_up += lines[0] + "\033[0m";
				line_mid += lines[1] + "\033[0m";
				line_down += lines[2] + "\033[0m";
			}
		}
		os << line_up << '\n' << sep_simple << '\n' << line_mid << '\n' << sep_simple << '\n' << line_down << '\n';

		if (i < 2) os << sep_doble << '\n';
	}

	return os;
}

unsigned short SuperTresEnRaya::play(unsigned pos) {
	Index3EnRaya new_tab;
	TresEnRaya* p;

	if (pos < 1 || pos > 9) return FALLIDA;

	p = &super_partida[tablero_actual.i][tablero_actual.j];

	// Intentamos hacer la jugada en el tablero actual
	// si da problemas devolvemos que hubo un error
	if (!p->player_plays(pos, playing)) return FALLIDA;

	// Cambiamos el jugador
	playing = (playing == PLAYER1 ? PLAYER2 : PLAYER1);

	if (p->game_ended()) {
		if (p->get_winner() == NONE) partida.add_none(tablero_actual.to_pos());
		else partida.player_plays(tablero_actual.to_pos(), p->get_winner());
	}

	new_tab = Index3EnRaya(pos);

	if (super_partida[new_tab.i][new_tab.j].game_ended()) {
		if (!partida.ultima_casilla()) {
			tablero_actual = Index3EnRaya(10);
			return HECHA_ELEGIR_TABLERO;
		} else {
			new_tab = Index3EnRaya(partida.primero_vacio());
		}
	}

	tablero_actual = new_tab;

	return HECHA;
}

bool SuperTresEnRaya::cambia_tablero(unsigned pos) {
	Index3EnRaya new_tab;

	if (pos < 1 || pos > 9) return false;

	new_tab = Index3EnRaya(pos);

	if (super_partida[new_tab.i][new_tab.j].game_ended()) return false;

	tablero_actual = new_tab;

	return true;
}
