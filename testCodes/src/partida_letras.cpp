//
// Created by unai on 1/12/21.
//

#include <iostream>
#include "bag.h"
#include "letters_set.h"
#include "letters_bag.h"
#include "solver.h"
#include "dictionary.h"
#include<vector>

using namespace std;
/*
   bool criterio(LetterInfo i, LetterInfo j){

   LettersSet letters

   return i.repetitions<j.repetitions;
   }*/

int main(int argc, char *argv[]) {


	Dictionary dic;
	LettersSet conjunto;
	string diccionario = argv[2];
	string puntuaciones = argv[1];

	char *l=argv[3];

	bool modo_juego;

	if(*l=='P')
		modo_juego=true;
	else
		modo_juego=false;

	int num_letras=atoi(argv[4]);

	string palabra;

	vector<char> letras;

	ifstream archivo;

	archivo.open(diccionario, ios::in);

	if (archivo.fail()) {
		cout << "Error al abrir el archivo" << endl;
		exit(1);
	}
	while (getline(archivo, palabra)) {
		dic.insert(palabra);
	}
	ifstream archivo_letras;
	archivo_letras.open(puntuaciones, ios::in);
	if(archivo_letras.fail()){
		cout<<"Error al abrir el archivo "<<puntuaciones<<endl;
		exit(1);
	}
	archivo_letras>>conjunto;
	LettersBag bolsa(conjunto);
	for(int i=0;i<num_letras;i++)
		letras.push_back(bolsa.extractLetter());

	Solver juego(dic,conjunto);

	pair<vector<string>,int> soluciones =juego.getSolutions(letras,modo_juego);

	cout<<"LETRAS DISPONIBLES:"<<endl;
	for(int i=0;i<letras.size();i++){
		cout<<letras[i]<<" ";
	}
	cout<<endl<<"SOLUCIONES:"<<endl;


	if(soluciones.first.size()>0) {
		for (int i = 0; i < soluciones.first.size(); i++)
			cout << soluciones.first[i]<< endl;
		cout<<"PUNTUACION:"<<endl<<soluciones.second;
	}

	else
		cout<<"No hay palabras con esas letras"<<endl;

	return 0;
}
