#include "evaluator.hpp"

//#define DEBUG 1 //usar junto com debug da main.cpp

evaluator::evaluator (cv::String file_name, float a, float b){
	this->index = 0;

	std::ifstream myfile(file_name.c_str());
	std::string linex, liney, linefps;
	int x, y;

	std::getline(myfile, linefps);
	std::istringstream(linefps) >> this->fps;
	//this->fps = stoi(linefps, 0, 10);

	while(std::getline(myfile, linex) && std::getline(myfile, liney)){


		std::istringstream(linex) >> x;
		std::istringstream(liney) >> y;
		/*
		x = stoi(linex, 0, 10);
		y = stoi(liney, 0, 10);
		*/
		cv::Point coordinates(x, y);
		this->ballPos.push_back(coordinates);
	}	

	myfile.close();

	this->a = a;
	this->b = b;
}


int evaluator::test(cv::Point p, cv::Mat frame){
	int range = (int) (this->a * (float) ballPos[index].y + this->b);
	range += 10;
	//std::cout << "ballPos: " << ballPos[index] << endl;
	//std::cout << "range: " << range << endl;
	dbg_circle(frame, ballPos[index], range, 2); //amarelo raio de acerto
	if(this->ballPos[index].x != -1){
		if(p.x != -1){
			if(std::abs(this->ballPos[index].x - p.x) < range && std::abs(this->ballPos[index].y - p.y) < range){
				dbg_circle(frame, p, range, 1); //acerto em verde
				return 1;
			}else{
				dbg_circle(frame, p, range, 0); //erro em vermelho
				return 0;
			}
		}else{
			//marcador falso negativo
			return 0;
		}
	}else{
		if(p.x != -1){
			dbg_circle(frame, p, range, 0); //erro em vermelho
			return 0;
		}else{
			//marcador verdadeiro negativo
			//nao conta na calibração
			return 0;
		}
	}
	
}

void evaluator::add(bool data){
	this->score.push_back(data);
	this->index += 1;
}


float evaluator::evaluate(){
	float accumulator = 0;
	for (std::vector<bool>::iterator it = this->score.begin(); it != this->score.end() ; it++)
	{
		if(*it == true)
			accumulator++;
	}
	return accumulator/this->score.size();
}

int dbg_circle(cv::Mat frame, cv::Point center, int radius, int color){
	#ifdef DEBUG
		if(color == 0) circle( frame, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
		else if(color == 1) circle( frame, center, radius, cv::Scalar(0,255,0), 3, 8, 0 );
		else if(color == 2) circle( frame, center, radius, cv::Scalar(0,255,255), 3, 8, 0 );
	#endif
	return 0;
}