
#include "sizeCheck.hpp"

#define DEBUG 1
#define SIZE_VAR 0.5//percentual variation of expected ball size

sizeCheck::sizeCheck(float a, float b){
	this->a = a;
	this->b = b;

}

bool sizeCheck::run(cv::Vec3f circle){
	float expected_radius = this->a * cvRound(circle[1]) + this->b;
	float tolerance = 0.5;
	tolerance *= expected_radius; 

	//Tolerância para o raio da bola em 20%
	//Exclui candidatos com raior maior ou menor do que o esperado
	if (std::abs(circle[2] - expected_radius) > tolerance)
		return false;
	else
		return true;
}