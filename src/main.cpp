//#include "opencv2/opencv.hpp"
//#include "opencv2/videoio.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdio>
using namespace cv;

RNG rng(12345);

Mat  drawConvex(Mat img)
{
    Mat thresh_out = img.clone();

    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierachy;

    findContours(thresh_out,contours,hierachy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

    std::vector< std::vector<Point> > hull(contours.size());

    for(size_t i =0; i< contours.size();i++)
    {
        convexHull( Mat(contours[i]),hull[i],false);
    }
    Mat drawing = Mat::zeros(thresh_out.size(),CV_8UC3);

    for(size_t i =0; i< contours.size();i++)
    {
        Scalar color = Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        drawContours(drawing,contours,(int)i,color,1,8,std::vector<Vec4i>(),0,Point());
        drawContours(drawing,hull,(int)i,color,1,8,std::vector<Vec4i>(),0,Point());
    }
    return  drawing;
}

void frameProccessing(Mat& frame)
{
     //Grayed out the image
    Mat grayedOut;
    Mat blurOut;
    Mat thresholdOut;

    cvtColor(frame, grayedOut, COLOR_BGR2GRAY);

     GaussianBlur(grayedOut, blurOut, Size(5,5), 1.5, 1.5);
     blurOut.convertTo(blurOut,-1,.70,25);

     threshold(blurOut, thresholdOut, 100, 130, THRESH_BINARY);

     thresholdOut = drawConvex(thresholdOut);
     imshow("thresholdOut", thresholdOut);

}


int main(int argc, char**argv) {
    VideoCapture cap(0);
   if(!cap.isOpened())
    {
        printf("No webcam found\n");
        return -1;
    }



    //namedWindow("grayedOut", 1);
    //namedWindow("blurOut", 2);
    //namedWindow("thresholdOut", 3);

    for(;;) {
        Mat frame;
        cap >> frame;
        if(frame.data !=NULL)
        {
        frameProccessing(frame);
        }
        if(waitKey(30) >= 0)break;
    }
    return 0;
}
