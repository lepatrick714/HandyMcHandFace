#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"

using namespace cv;

int main(int argc, char**argv) {
    VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;

    Mat grayedOut;
    Mat blurOut;
    Mat thresholdOut;


    namedWindow("grayedOut", 1);
    namedWindow("blurOut", 2);
    namedWindow("thresholdOut", 3);

    for(;;) {
        Mat frame;
        cap >> frame;

        //Grayed out the image
        cvtColor(frame, grayedOut, COLOR_BGR2GRAY);
        imshow("grayedOut", grayedOut);

        GaussianBlur(grayedOut, blurOut, Size(7,7), 1.5, 1.5);
        imshow("blurOut", blurOut);

        threshold(blurOut, thresholdOut, 127, 255, THRESH_BINARY_INV);
        imshow("thresholdOut", thresholdOut);

        if(waitKey(30) >= 0) break;
    }
    return 0;
}
