#include "letters_bag.h"

LettersBag::LettersBag(const LettersSet & lettersSet) {
	parseLetterSet(lettersSet);
}

void LettersBag::insertLetter(const char & c){
	letters.add(c);
}

void LettersBag::parseLetterSet(const LettersSet & letterset) {
	for(auto it=letterset.begin();it!=letterset.end();++it){
		for(int i=0;i<it->second.repetitions;i++)
			this->insertLetter(it->first);
	}
}

char LettersBag::extractLetter(){
	return letters.get();
}

vector<char> LettersBag::extractLetters(int num){
	vector<char> letras;

	for(int i=0; i<num; i++)
		letras.push_back(letters.get());
	return letras;
}

void LettersBag::clear(){
	letters.clear();
}

unsigned int LettersBag::size()const{
	return letters.size();
}

