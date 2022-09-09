#include<dlib/image_processing/frontal_face_detector.h>
#include<dlib/image_processing.h>
#include<dlib/opencv.h>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;
using namespace dlib;

//Desenhar linha
void desenhalinha(cv::Mat &image, full_object_detection landmarks, int start, int end, bool isClosed=false){
    std::vector<cv::Point> points;
    for(int i=start; i<=end; i++){
        points.push_back(cv::Point(landmarks.part(i).x(), landmarks.part(i).y()));
    }
    cv::polylines(image, points, isClosed, cv::Scalar(0, 255, 255), 2, 16);
}

void desenhalinhas(cv::Mat &image, full_object_detection landmarks){
    desenhalinha(image, landmarks, 36, 41, true);       //olho esquerdo
    desenhalinha(image, landmarks, 42, 47, true);       //olho direito
}

//encontra os pontos da face e desenha as linhas sobre os pontos dos olhos
void encontraLandmarks(Mat &frame, frontal_face_detector faceDetector, shape_predictor landmarkDetector,
    std::vector<dlib::rectangle> &faces, float resizeScale, int skipFrames, int frameCounter){

        //armazenar imagem redimensionada
        Mat smallFrame;

        //redimensiona frame para imagem menor
        resize(frame, smallFrame, Size(), 1.0/resizeScale, 1.0/resizeScale);

        //muda para o formato da dlib
        cv_image<bgr_pixel> dlibImageSmall(smallFrame);
        cv_image<bgr_pixel> dlibImage(frame);

        //detecta faces no intervalo de quadros
        if(frameCounter % skipFrames == 0){
            faces = faceDetector(dlibImageSmall);
        }

        //loop sobre rostos
        for(int i=0; i<faces.size(); i++){

            //dimensione as coordenadas do retângulo como fizemos a detecção de rosto em uma imagem menor redimensionada
            dlib::rectangle rect(int(faces[i].left() * resizeScale),
                int(faces[i].top() * resizeScale),
                int(faces[i].right() * resizeScale),
                int(faces[i].bottom() * resizeScale));

            //detecção dos landmarks faciais
            full_object_detection faceLandmark = landmarkDetector(dlibImage, rect);

            //desenha as linhas sobre os landmarks
            desenhalinhas(frame, faceLandmark);

            //cálculo das distancia euclidianas
	        double P37_41_x = faceLandmark.part(37).x() - faceLandmark.part(41).x();
            double P37_41_y=  faceLandmark.part(37).y() - faceLandmark.part(41).y() ;
            double p37_41_sqrt=sqrt((P37_41_x * P37_41_x) + (P37_41_y * P37_41_y));

            double P38_40_x = faceLandmark.part(38).x() - faceLandmark.part(40).x();
            double P38_40_y = faceLandmark.part(38).y() - faceLandmark.part(40).y();
            double p38_40_sqrt=sqrt((P38_40_x * P38_40_x) + (P38_40_y * P38_40_y));

            double P36_39_x = faceLandmark.part(36).x() - faceLandmark.part(39).x();
            double P36_39_y = faceLandmark.part(36).y() - faceLandmark.part(39).y();
            double p36_39_sqrt=sqrt((P36_39_x * P36_39_x) + (P36_39_y * P36_39_y));

            //Calculo do EAR
            double EAR = (p37_41_sqrt +  p38_40_sqrt)/(2* p36_39_sqrt);

            cout << "EAR value =  " << EAR << endl;
        }
}

int main(){

    //crie um objeto de captura de vídeo para mostrar o vídeo da webcam
    VideoCapture videoCapture(-1);

    //checar se o opencv conseguiu abrir a camera
    if(!videoCapture.isOpened()){
        cout<<"can not open webcam"<<endl;
        return 0;
    }

    //definir os landmarks do rosto
    frontal_face_detector faceDetector = get_frontal_face_detector();

    //define landmark detector
    shape_predictor landmarkDetector;

    //carregar o modelo treinado de landmarks
    deserialize("../dlibAndModel/shape_predictor_68_face_landmarks.dat") >> landmarkDetector;

    //redimensionar altura
    float resizeHeight = 480;

    //definir skip frames
    int skipFrames = 3;

    //Obter primeiro frame
    Mat frame;
    videoCapture >> frame;

    //redimensiona a escala
    float height = frame.rows;
    float resizeScale = height/resizeHeight;

    //inicia o tickCounter
    double tick = getTickCount();
    int frameCounter=0;

    //cria uma tela para mostrar os frames
    namedWindow("frame", WINDOW_NORMAL);

    //criar variavel que armazena o fps
    double fps = 30.0;

    std::vector<dlib::rectangle> faces;

    while (1){
        if(frameCounter == 0){
            tick = getTickCount();
        }

        //lê o frame
        videoCapture >> frame;

        encontraLandmarks(frame, faceDetector, landmarkDetector, faces, resizeScale, skipFrames, frameCounter);

        String fpss;
        fpss = to_string(fps);

        //mostra o frame
        imshow("frame", frame);

        //precionar o esc para sair da aplicação
        char key = waitKey(1);
        if(key == 27){
            break;
        }

        //incrementa o frame counter
        frameCounter++;

        //calcula fps depois de todo 100 frames
        if(frameCounter == 100){
            tick = ((double)getTickCount() - tick)/getTickFrequency();
            fps = 100.0/tick;
            frameCounter = 0;
        }
    }

    //release captura de video
    videoCapture.release();

    //fecha todas as janelas abertas
    destroyAllWindows();

    return 0;
}
