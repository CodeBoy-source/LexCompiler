#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<algorithm>

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

using namespace std;


/**
 * @brief TDA Dictionary
 * @details Almacena las palabras de un fichero de texto y permite iterar sobre ellas
 *
 */

class Dictionary{
	private:
		set <string> words;
	public:
		Dictionary()=default;

		/**
		 * @brief Crea un diccionario con el mismo contenido que se le pasa como argumento
		 * @param other Objeto a copiar
		 */
		Dictionary(const Dictionary & other);

		/**
		 * @brief Indica si una palabra en el diccionario
		 * @param val palabra que se quiere buscar
		 * @return Entero indicando el numero de apariciones [0,1]
		 */

		int count(const string & val)const;

		/**
		 *
		 * @param val
		 * @return
		 */

		bool exists(const string & val)const;

		//pair<set<string>::iterator,bool> insert(const string & val);

		/**
		 * @brief Inserta un elemento en el Diccionario
		 * @param val elemento a insertar
		 * @return
		 */

		pair<set<string>::iterator,bool> insert(const string & val);

		/**
		 * @brief Elimina un valor del diccionario
		 * @param val elemento a eliminar
		 * @return 0 si no está, 1 si lo ha borrado
		 */

		unsigned int erase(const string & val);

		/**
		 * @brief limpia el diccionario
		 */

		void clear();

		/**
		 * @brief Comprueba si el diccionario está vacío
		 * @return true si el diccionario está vacío, false en caso contrario
		 */

		bool empty()const;

		/**
		 * @brief Tamaño del diccionario
		 * @return Número de palabras que hay en el diccionario
		 */

		unsigned int size();

		/**
		 * @brief Indica el número de apariciones de una letra
		 * @param c letra a buscar
		 * @return El número de apariciones de la letra
		 */

		int getOcurrences(const char c);

		/**
		 * @brief Indica el numero total de letras del diccionario
		 * @return el numero total de letras que hay en el diccionario
		 */

		int getTotalLetters();

		/**
		 * @brief Devuelve un vector con las palabras en el diccionario con la longitud indicada
		 * @param length longitud de las palabras a buscar
		 * @return vector de palabras con la longitud dada
		 */

		vector<string> wordsOfLength(int length);

		set<string>::iterator begin(){return words.begin();}

		set<string>::iterator end(){return words.end();}

};

#endif
