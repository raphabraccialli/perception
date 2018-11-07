
#include "sizeCheck.hpp"

#define DEBUG 1
#define SIZE_VAR 0.5//percentual variation of expected ball size

sizeCheck::sizeCheck(float a, float b){
	this->a = a;
	this->b = b;

}

bool sizeCheck::run(cv::Point center, int radius){
	
	float expected_radius = this->a * center.y - this->b;

	//Tolerância para o raio da bola em 20%
	//Exclui candidatos com raior maior ou menor do que o esperado
	if (radius > expected_radius*1.2) 
		return false;
	if (radius < expected_radius*0.8) 
		return false;
	else
		return true;
}