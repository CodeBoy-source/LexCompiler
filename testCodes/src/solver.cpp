#include"solver.h"

Solver::Solver(const Dictionary &dict, const LettersSet &letters_set) {
	dic=dict;
	letters=letters_set;
}

pair<vector<string>,int> Solver::getSolutions(const vector<char> &available_letters, bool score_game) {
	pair<vector<string>,int> v;
	Dictionary d=dic;
	int mejor=0;
	/*for(int i=0;i<available_letters.size();i++){
	  d=this->contiene(d,tolower(available_letters[i]),mejor);
	  }*/
	v.second=0;

	auto itv=v.first.begin();
	for(auto it=d.begin();it!=d.end()&&!d.empty();it++) {
		int score=score_game?letters.getScore(*it):it->size();
		if(score>v.second) {
			if (this->valida(*it,available_letters)) {
				v.second = score;
				v.first.clear();
				itv = v.first.begin();
				itv = v.first.insert(itv, *it);
			}
		}
		else if(score==v.second)
			if(this->valida(*it,available_letters))
				itv=v.first.insert(itv,*it);
	}
	return v;

}

bool Solver::valida(const string &word, vector<char> letras) {
	bool encontrada,valida;
	encontrada=true;
	//valida=true;
	int tam;
	for(int i=0;i<word.size()&&encontrada;i++){
		tam=letras.size();
		encontrada=false;
		for(int j=0;j<letras.size()&&!encontrada;j++) {
			if (word[i] == tolower(letras[j])) {
				letras[j] = letras[letras.size() - 1];
				encontrada = true;
				letras.pop_back();
				j--;
			}
		}

	}

	return encontrada;
}
