#include<opencv\cv.h>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main(){
    VideoCapture cap(0);

    if(!cap.isOpened()){
        cout << "change the camera port number! ";
        return -1;
    }

    while(true){
        Mat frame;
        cap.read(frame);
        imshow("camera", frame);
        if (waitKey(30) == 27) {
            return 0;
        }
    }
}
