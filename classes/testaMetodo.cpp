#include "testaMetodo.hpp"
/*
testaMetodo::testaMetodo (char* name_file, float a, float b){
	ifstream myfile(name_file);

	vector<Point> answers;
	string linex, liney;
	int x,y;

	while(getline(myfile,linex) && getline(myfile,liney)){

		x = stoi(linex,0,10);
		y = stoi(liney,0,10);

		Point coordinates(x,y);
		answers.push_back(coordinates);
	
	}	



	this->a = a;
	this->b = b;
	this->ballPos = answers;
}

int testaMetodo::testa(string nome_gabarito)
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

bool evaluate(Point p){
	int range;
	//range = (int) this.a + p.y * b;
	if(abs(ballPos[index][0] - p.x) < range && abs(ballPos[index][1] - p.y) < range){
		//append pro vetor de avaliacao
		return true;
	}
	else{
		//append pro vetor de avaliacao
		return false;
	}
}
*/