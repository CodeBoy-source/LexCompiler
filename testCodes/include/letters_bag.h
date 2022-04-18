#include"letters_set.h"
#include<iostream>
#include<fstream>
#include<vector>
#include"bag.h"

using namespace std;

#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__



/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */

//template <class T>

class LettersBag{
	private:
		//LettersBag(const LettersSet &lettersSet);

		Bag <char> letters;

	public:

		LettersBag()=default;

		LettersBag(const LettersSet & lettersSet);

		/**
		 * Introduce una letra en la bolsa
		 * @param c letra a insertar a la bolsa
		 */

		void insertLetter(const char & c);

		/**
		 * @brief Parsea un LettersSet y construye la LettersBag asociada
		 * @param letterset LettersSet que se procesa
		 */

		void parseLetterSet(const LettersSet & letterset);

		/**
		 * Extrae una letra aleatoria de la bolsa
		 * @return la letra extraida
		 */

		char extractLetter();

		/**
		 * @brief extrae un conjunto de letras
		 * @param num numero de letras a extraer
		 * @return vector con todas las letras extraidas
		 */

		vector<char> extractLetters(int num);

		/**
		 * @brief Vacía la bolsa
		 */

		void clear();

		/**
		 * @brief Tamaño de la bolsa
		 * @return int con el tamaño de la bolsa
		 */

		unsigned int size() const;

		LettersBag & operator=(const LettersBag & other);

		//ostream & operator<<(ostream & os, const LettersBag & bl);

};

#endif
