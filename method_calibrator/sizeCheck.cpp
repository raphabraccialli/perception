#include "sizeCheck.hpp"

#define DEBUG 1
#define SIZE_VAR 0.5//percentual variation of expected ball size

sizeCheck::sizeCheck(float a, float b){
	this->a = a;
	this->b = b;

}

int sizeCheck::run(vector<Vec3f> circles){
	
	for(int i=0; i < circles.size(); i++){
		float expected = (circles[i][1] * a + b);
		if(abs(circles[i][2]-expected)/expected > SIZE_VAR)
			circles.erase(circles.begin() + i);
	}

	return 0; //TODO return vector?
}