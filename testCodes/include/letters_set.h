#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */

#include<map>
#include<string>
#include<iostream>
#include "ostream"

using namespace std;

struct LetterInfo{
	int repetitions;
	int score;
};

class LettersSet{
	private:
		map<char,LetterInfo> letters;

	public:
		LettersSet();

		/**
		 * @brief Constructor de copia
		 * @param other LettersSet a copiar
		 */
		LettersSet(const LettersSet & other);

		/**
		 * @brief Inserta un elemento en el LetterSet
		 * @param val Valor a insertar
		 * @return Par que contiene un iterador apuntado hacia la posicion de la insercion y un bool que marca su la inserción ha sido correcta
		 */
		pair<map<char,LetterInfo>::iterator ,bool> insert(const pair<char,LetterInfo> & val);

		unsigned int erase(const char & key);

		void clear();

		bool empty()const;

		unsigned int size() const;

		int getScore(string word);

		LettersSet & operator=(const LettersSet & cl);

		LetterInfo & operator[](const char & val);

		friend ostream & operator<<(ostream& os, LettersSet & cl);

		friend istream & operator>>(istream& is, LettersSet & cl);

		auto begin()const{
			return letters.begin();
		}

		auto end()const{
			return letters.end();
		}


};

#endif
