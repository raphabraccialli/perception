#include "ballCandidate.hpp"

using namespace std;
using namespace cv;

#define trainingSize 15
#define MAX_FRAMES 3


class ImageProcessing{
public:

    /*
     * Variaveis
     */

    Mat copy; // matriz auxiliar
    Mat img; //img original
    vector<ballCandidate> candidatos;


    /*
     * Métodos
     */

    ImageProcessing(char *); //construtor
    int predict(Mat);

private:

    CvANN_MLP annTrained;
    KalmanFilter KF;
    bool firstTime;
    int notFound;

    Point ball;

    void drawRect(Rect, int);
    int predictAnn(int i, Mat imgTreino, float * maxActivationValue, int * candidatePos);
    void correctKalman();
    void predictKalman();
    int euclideanDist(Point, Point);
    void initKalman();


};
