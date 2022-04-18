#include "letters_set.h"

using namespace std;

LettersSet::LettersSet() {

}

LettersSet::LettersSet(const LettersSet &other) {
	this->letters=other.letters;
}

pair<map<char, struct LetterInfo>::iterator, bool> LettersSet::insert(const pair<char, LetterInfo> &val) {
	pair<map<char,LetterInfo>::iterator,bool> resultado;
	resultado.second=false;

	resultado=this->letters.insert(val);

	return resultado;
}

unsigned int LettersSet::erase(const char &key) {
	unsigned int num;
	if(letters.find(key)!=letters.end())
		num=letters.erase(key);

	return num;
}

void LettersSet::clear() {
	this->letters.clear();
}

bool LettersSet::empty() const {
	return this->letters.empty();
}

unsigned int LettersSet::size() const {
	return this->letters.size();
}

int LettersSet::getScore(string word) {
	int suma=0;
	map<char,LetterInfo>::iterator it=letters.begin();
	for(int i=0;i<word.size();i++) {
		if((word.at(i)>=97 && word.at(i)<=122)||(word.at(i)>=65 && word.at(i)<=90)) {
			it = letters.find(toupper(word.at(i)));
			suma += it->second.score;
		}
	}
	return suma;
}

LettersSet & LettersSet::operator=(const LettersSet &cl) {
	letters = cl.letters;
	return *this;
}

LetterInfo & LettersSet::operator[](const char &val) {
	return letters.at(val);
}

ostream & operator<<(ostream & os,LettersSet & cl) {

	for(auto i=cl.letters.begin();i!=cl.letters.end();++i){
		os<<"Key: " << i->first << endl;
		os<<"    Repeticiones: "<<i->second.repetitions<<endl;
		os<<"    Puntuación  : "<<i->second.score<<endl;
	}
	return os;
}

istream & operator>>(istream & is, LettersSet & cl){
	string algo;
	pair<char,LetterInfo> elemento;

	getline(is,algo); // Para no leer la primera línea
	while(is>>elemento.first >> elemento.second.repetitions >> elemento.second.score) {
		cl.insert(elemento);
	}

	return is;
}
