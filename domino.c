#include "lista.h"
#include <stdio.h>

#define PIECE_MAX 7

//deck_player
//deck_pc
//deck_table
//deck_back

TppecaDomino * ai_move(TppecaDomino * deck_pc, TppecaDomino * deck_player, TppecaDomino ** deck_table, TppecaDomino ** deck_back){

	TppecaDomino * p; 

	int i;
	int bool1, bool2;

	TppecaDomino * unknown = sum(deck_player, *deck_back);


	int * freq_order = frequency_rank(unknown);
	free(unknown);
	unknown = NULL;

	for(i = 0; i < PIECE_MAX; i++){

		for(p = deck_pc; p != NULL; p = p->right){


			bool1 = (int)p->numberRight == freq_order[i] && 
				(*deck_table == NULL || p->numberLeft == left_table_number(*deck_table) || p->numberLeft == right_table_number(*deck_table));
			bool2 = (int)p->numberLeft == freq_order[i] && 
				(*deck_table == NULL || p->numberRight == left_table_number(*deck_table) || p->numberRight == right_table_number(*deck_table));

			if(bool1 || bool2){
				deck_pc = push_table(deck_pc, deck_table, p->numberRight, p->numberLeft);
				return deck_pc;
			}
		}

		if(i == PIECE_MAX - 1 && *deck_back != NULL){
			deck_pc = catch_piece(deck_pc, deck_back);//pesca uma peça

			unknown = sum(deck_player, *deck_back);
			freq_order = frequency_rank(unknown);
			free(unknown);
			unknown = NULL;

			i = -1;//para reiniciar o loop
		}
	}

	return deck_pc;
}

int can_play(TppecaDomino * deck_a, TppecaDomino * deck_table, TppecaDomino * deck_back){
	TppecaDomino * p;

	//if(deck_back != NULL) return 1;

	for(p = deck_a; p != NULL; p = p->right){
		if(where_play(p, deck_table)) return 1;
	}

	return 0;
}
