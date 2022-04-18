/**
 *   \file solver.h
 *   \brief Archivo de declaración de la clase Solver
 */
#ifndef SOLVER_H
#define SOLVER_H
#include<iostream>
#include<vector>
#include<set>
#include"dictionary.h"
#include"letters_set.h"

class Solver{
	private:
		Dictionary dic;
		LettersSet letters;
		// Dictionary contiene(Dictionary d,char l, int & mejor);
		bool valida(const string &word, vector<char> letras );
	public:
		Solver(const Dictionary & dict, const LettersSet & letters_set);
		pair<vector<string>,int> getSolutions(const vector<char> & available_letters, bool score_game);
};

#endif
