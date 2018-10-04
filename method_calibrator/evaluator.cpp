#include "evaluator.hpp"

evaluator::evaluator (String file_name, float a, float b){
	this->index = 0;

	ifstream myfile(file_name);
	string linex, liney, linefps;
	int x, y;

	getline(myfile, linefps);
	this->fps = stoi(linefps, 0, 10);

	while(getline(myfile, linex) && getline(myfile, liney)){

		x = stoi(linex, 0, 10);
		y = stoi(liney, 0, 10);

		Point coordinates(x, y);
		this->ballPos.push_back(coordinates);
		cout << coordinates << endl;	
	}	



	this->a = a;
	this->b = b;
}

int evaluator::testa(string nome_gabarito)
{

	string linex, liney, linegx, linegy;

	int frames = 0, acertos = 0, f_pos = 0, f_neg = 0;
	float resultado;

	//Armazena os arquivos em variáveis.
	ifstream gabarito("nome_gabarito");
	ifstream myfile("nome_qualquer");


	if(gabarito.is_open() && myfile.is_open()){

		//Para não considerar como frame a linha que indica o fps
		getline(myfile,linex);
		getline(gabarito,linegx);

		//Lê cada linha de cada arquivo e compara,
		//aramzenando o número de duplas de linhas(frames)
		//e as duplas iguais entre os arquivos (acertos).
		while(getline(myfile,linex) && getline(gabarito,linegx) && getline(myfile,liney) && getline(gabarito,linegy)){
			if(linex == linegx && liney == linegy){				
				acertos++;
			}
			else if(linex == "-1" && linegx != "-1"){
				f_neg++;
			}
			else if(linex != "-1" && linegx == "-1"){
				f_pos++;
			}
			frames++;
		}

		myfile.close();
		gabarito.close();

		//Calcula a porcentagem de acertos e mostra na tela.
		resultado = (acertos*1.0/frames)*100;
		cout << "Porcentagem de acerto: " << resultado << endl;

		//Calcula a porcentagem de falsos positivos e falsos negativos e mostra na tela
		f_pos = (f_pos*1.0/frames)*100;
		f_neg = (f_neg*1.0/frames)*100;

		cout << "Falsos positivos: "<< f_pos << endl;
		cout << "Falsos negativos: "<< f_neg << endl;
	}

	else{
		cout << "Not possible to open the file." << endl;
	}

	return resultado;

}	

int evaluator::add(Point p){
	int range = (int) (this->a * (float) ballPos[index].y + this->b);
	range += 10;
	cout << "ballPos: " << ballPos[index] << endl;
	cout << "range: " << range << endl;
	if(this->ballPos[index].x != -1){
		if(p.x != -1){
			if(abs(this->ballPos[index].x - p.x) < range && abs(this->ballPos[index].y - p.y) < range){
				this->score.push_back(true);
				this->index += 1;
				return 1;
			}else{
				this->score.push_back(false);
				this->index += 1;
				return 0;
			}
		}else{
			this->score.push_back(false);
			this->index += 1;
			return 0;
		}
	}else{
		if(p.x != -1){
			this->score.push_back(false);
			this->index += 1;
			return 0;
		}else{
			this->score.push_back(true);
			this->index += 1;
			return 1;
		}
	}
	
}

float evaluator::evaluate(){
	float accumulator;
	for (vector<bool>::iterator it = this->score.begin(); it != this->score.end() ; it++)
	{
		if(*it == true)
			accumulator++;
	}
	return accumulator/this->score.size();
}