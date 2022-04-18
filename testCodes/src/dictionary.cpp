#include "dictionary.h"

using namespace std;

Dictionary::Dictionary(const Dictionary & other) {
	this->words=other.words;
}

int Dictionary::count(const string & val)const {
	//string l= (basic_string<char> &&) val;
	return this->words.count(val);
}

bool Dictionary::exists(const string &val) const {
	bool resultado=false;
	string l= (basic_string<char> &&) val;
	if(this->words.find(l)!=this->words.end())
		resultado=true;
	return resultado;
}
/*pair<set<string>::iterator,bool>*/
pair<set<string>::iterator, bool> Dictionary::insert(const string &val) {
	pair<set<string>::iterator,bool> resultado;

	string palabra=val;

	transform(palabra.begin(),palabra.end(),palabra.begin(),::toupper);

	resultado=words.insert(val);
	return resultado;
}

unsigned int Dictionary::erase(const string &val) {
	return this->words.erase(val);
}

void Dictionary::clear() {
	this->words.clear();
}

bool Dictionary::empty() const {
	return this->words.empty();
}


unsigned int Dictionary::size(){
	return this->words.size();
}

int Dictionary::getOcurrences(const char c) {
	// string l= reinterpret_cast<const char *>(c);
	int suma=0;
	int veces=0;
	for(auto it=this->words.begin();it!=this->words.end();it++){
		veces=0;
		for(int i=0;i<it->size();i++){
			if(tolower(c)==(*it)[i])
				veces++;
		}
		suma+=veces;
	}
	return suma;
}

int Dictionary::getTotalLetters() {
	int suma=0;
	char letra='A';
	while(letra<='Z')
		suma+= getOcurrences(letra++);
	return suma;
}

vector<string> Dictionary::wordsOfLength(int length) {
	vector<string> palabras;
	vector<string>::iterator i=palabras.begin();

	set<string>::iterator j;

	for(j = words.begin(); j != this->words.end() ; j++){
		if (j->size() == length) {
			i=palabras.insert(i, *words.find(*j));
		}
	}
	reverse(palabras.begin(), palabras.end());

	return palabras;

}
