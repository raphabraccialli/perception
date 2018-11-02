#include "kalman.hpp"

//construtor
//Load(xml) e chama iniciação de Kalman
ImageProcessing::ImageProcessing(char *xml){
    initKalman();
    //    KF = KalmanFilter(4, 2, 0);
    //    KF.transitionMatrix = *(Mat_<float>(4, 4) << 1,0,1,0,   0,1,0,1,  0,0,1,0,  0,0,0,1);
    //    Mat_<float> measurement(2,1); measurement.setTo(Scalar(0));

    //    // init...
    //    KF.statePre.at<float>(2) = 0;
    //    KF.statePre.at<float>(3) = 0;
    //    setIdentity(KF.measurementMatrix);
    //    setIdentity(KF.processNoiseCov, Scalar::all(1e-4));
    //    setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));
    //    setIdentity(KF.errorCovPost, Scalar::all(.1));
    //    firstTime = 1;
}

//Inicia Kalman, define parâmetros.
void ImageProcessing::initKalman(){

    int stateSize = 4; //state size (variaveis que vc deseja obter: x, y, v_x, v_y)
    int measSize = 2; //measurement size (variaveis que vc mede: x, y)

    KF = KalmanFilter(stateSize,measSize, 0);

    // [ 1 0 dT 0  0 0 ]
    // [ 0 1 0  dT 0 0 ]
    // [ 0 0 1  0  0 0 ]
    // [ 0 0 0  1  0 0 ]
    // [ 0 0 0  0  1 0 ]
    // [ 0 0 0  0  0 1 ]
    KF.transitionMatrix = *(Mat_<float>(4, 4) << 1,0,1,0,   0,1,0,1,  0,0,1,0,  0,0,0,1);

    setIdentity(KF.processNoiseCov, Scalar(1e-2)); // -5
    //    KF.processNoiseCov.at<float>(2,2) = 5.0f;
    //    KF.processNoiseCov.at<float>(3,3) = 5.0f;

    setIdentity(KF.measurementMatrix);
    setIdentity(KF.measurementNoiseCov, Scalar(1e-1));
    setIdentity(KF.errorCovPost, Scalar::all(1));
    firstTime = 1;
    notFound = 0;
}

void ImageProcessing::drawRect(Rect ROI, int cor){
    rectangle(this->img, ROI, Scalar(0,cor,255), 1, 8, 0);
    imshow("Imagem", this->img);
}

int ImageProcessing::euclideanDist(Point ref, Point final){
    return sqrt(pow(ref.x - final.x,2) + pow(ref.y - final.y, 2));
}

//corrige a partir das medidas
void ImageProcessing::correctKalman(){
    Mat_<float> measurement(2,1);
    //measurement.setTo(Scalar(0));

    measurement(0) = ball.x;
    measurement(1) = ball.y;
    // The "correct" phase that is going to use the predicted value and our measurement
    KF.correct(measurement);

}

//prediz e mostra na imagem
void ImageProcessing::predictKalman(){

    if (!firstTime) {
        Mat prediction = KF.predict();
        //show image
        Point predictPt(prediction.at<float>(0),prediction.at<float>(1));
        circle(this->img,predictPt,10,Scalar(0,255,0));
        imshow("Imagem", this->img);
    }
}

Mat findFeatures(Mat *img){

    Mat cols = img->colRange(0,16);
    Mat aux(*img);
    cv::hconcat(aux, cols, aux);
    //    cols = img->colRange(0,1);
    //    cv::hconcat(aux, cols, aux);

    cv::Mat hist;
    const int histSize = 16;
    float range[] = { 0, 256 } ;
    const float* histRange = { range };
    cv::calcHist(img,1,0,Mat(),hist,1,&histSize,&histRange,true,false);
//    //cout << hist << endl;

    int k = 0;
    int j;
    for ( j = img->cols ; j < aux.cols; j++, k++){
        aux.at<uchar>(0,j) = hist.at<uchar>(0,k);
    }

//    /*************SHOW HISTOGRAM*************/

//        int hist_w = 512; int hist_h = 400;
//        int bin_w = cvRound( (double) hist_w/histSize );

//        Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0));

//        normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

//        for( int i = 1; i < histSize; i++ )
//        {
//            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
//                  Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
//                  Scalar( 255, 0, 0), 2, 8, 0  );

//        }

//        imshow("hist",histImage);
//        waitKey(0);
    return aux;
}

int ImageProcessing::predictAnn(int i,Mat imgTreino, float* maxActivationValue, int* candidatePos){

    //limiar que determina o valor minimo da funcao de ativacao para dizer que eh bola!!!
    float threshold = 0.65; //aumentar ou diminuir conforme necessidade


    resize(imgTreino, imgTreino, Size(trainingSize, trainingSize),0,0,INTER_CUBIC);
    cvtColor(imgTreino,imgTreino, CV_BGR2GRAY);
    imgTreino = imgTreino.reshape(0,1);
    //imgTreino = findFeatures(&imgTreino).clone();


    imgTreino.convertTo(imgTreino, CV_32FC1);

//    float media = mean(imgTreino).val[0];
//    subtract(imgTreino, media, imgTreino);

    Mat responseMat;
    annTrained.predict(imgTreino,responseMat);

    Point maxIdx;
    minMaxLoc(responseMat,0,0,0,&maxIdx);

    if (maxIdx.x == 1){ //achou bola, entao eh necessario verificar o peso da funcao de ativacao
        float actValue = responseMat.at<float>(1);
        if (actValue >= threshold && *maxActivationValue < actValue){
            //cout << responseMat << endl;
            *candidatePos = i;
            *maxActivationValue = actValue;
            return 1;
        }
    }
    return 0; //nao achou bola
}

int ImageProcessing::predict(Mat copy){

    int candidatePos;
    int findBall = 0;
    float maxActivationValue = -1;

    Mat field = copy.clone();
    for(int i = 0; i < field.rows;i++){
        for(int j = 0; j < field.cols;j++){
            if (i > field.rows/2){
                field.at<uchar>(i,j) = 255;
            }
            else
                field.at<uchar>(i,j) = 0;
        }
    }

    candidatos = findBallCandidates(true,copy, field);

    for (int i = 0; i < candidatos.size(); i++) {

        clock_t timer = clock();

        //essa funcao retorna se achou-se bola ou nao
        findBall += predictAnn(i,candidatos[i].roi, &maxActivationValue, &candidatePos);

        timer = clock() - timer;
        //cout << "Executou em " << ((float)timer)/CLOCKS_PER_SEC*1000000 << " usegundos" << endl;

    }

    predictKalman();

    if (!findBall){
        notFound++;
        if( notFound >= 10 ) firstTime = 1; //se perder a bola por muitos frames, nao confiar mais na predicao

        return -1; //nao achou a bola
    }



    this->ball.x = candidatos[candidatePos].center.x;
    this->ball.y = candidatos[candidatePos].center.y;
    drawRect(candidatos[candidatePos].rect, 0);

    /************************///KALMAN
    if (firstTime){
        KF.statePost.at<float>(0) = candidatos[candidatePos].center.x;
        KF.statePost.at<float>(1) = candidatos[candidatePos].center.y;
        KF.statePost.at<float>(2) = 0;
        KF.statePost.at<float>(3) = 0;
        firstTime = 0;
    }
    else
        correctKalman();
    /************************///KALMAN

    notFound = 0;
    return candidatePos; //encontrou a bola
}

