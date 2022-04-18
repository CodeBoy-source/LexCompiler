#include"letters_set.h"
#include<iostream>
#include<fstream>
#include<vector>


#ifndef __BAG_H__
#define __BAG_H__

using namespace std;

/**
 *  \brief TDA abstracto Bolsa
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 */

template < class T>
class Bag{
	private:
		//T elements [500];
		//int n_elements;
		vector <T> v;

	public:

		Bag()=default;

		Bag(const Bag<T> & other){
			this->copiarElementos(other);
		}
		void add(const T & element){
			//n_elements++;
			v.push_back(element);
		}
		T get(){
			srand(time(NULL));
			int aleatorio=rand()%(v.size());
			T elemento=v[aleatorio];
			swap(v[aleatorio],v.back());
			v.pop_back();
			return elemento;
		}

		void clear(){
			v.clear();
		}

		int size() const {
			return v.size();
		}

		void copiarElementos(const Bag<T> & other){
			if(this->n_elements!=0)
				this->v.clear();
			for(int i=0;i<other.n_elements;i++)
				this->add(other.v[i]);
		}

		bool empty(){
			return v.size()==0;
		}

		const Bag<T>operator=(const Bag<T> & other){
			if(this!=&other)
				copiarElementos(other);
			return this;
		}

		const T operator[](int i)const{
			return v[i];
		}


};

#endif
