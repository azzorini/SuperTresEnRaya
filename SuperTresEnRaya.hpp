#pragma once

#include <string>
#include <vector>

#include "TresEnRaya.hpp"

struct Index3EnRaya {
	unsigned i, j;
	Index3EnRaya() : i(0), j(0) {}
	Index3EnRaya(unsigned pos) {
		pos--;
		i = pos / 3;
		j = pos - 3*i;
	}
	Index3EnRaya(unsigned _i, unsigned _j) : i(_i), j(_j) {}
	unsigned to_pos() const { return 3*i + j + 1; }
};

enum JUGADA_STATUS: unsigned short {FALLIDA, HECHA, HECHA_ELEGIR_TABLERO};

class SuperTresEnRaya {
	std::vector< std::vector<TresEnRaya> > super_partida;
	TresEnRaya partida;
	Index3EnRaya tablero_actual;
	unsigned short playing;
public:
	SuperTresEnRaya(bool empieza_en_centro = true) : super_partida(3, std::vector<TresEnRaya>(3, TresEnRaya())), partida(), tablero_actual(5), playing(PLAYER1) {
		if (!empieza_en_centro) tablero_actual = Index3EnRaya(10);
	}

	friend std::ostream& operator<<(std::ostream&, const SuperTresEnRaya&);

	bool game_ended() const { return partida.game_ended(); }

	unsigned short get_player() const { return playing; }
	unsigned short get_winner() const { return partida.get_winner(); }

	// El jugador actual juega en el tablero actual y se cambia al tablero que toque
	// En caso de que la jugada falle se indicará al devolver el resultado
	// También se indicará si el siguiente jugador tiene que elegir tablero
	unsigned short play(unsigned);

	// Se cambia el tablero en el que se va a jugar
	bool cambia_tablero(unsigned);
};
