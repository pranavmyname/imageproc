#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cxcore.h>
using namespace cv;
int hmin=98,smin=132,vmin=143,smax=255,hmax=255,vmax=255;
void ont(int,void*)
{

}
int main(int argc, char *argv[])
{
    Mat img,hsv,bw,t1,t2,t3;

    VideoCapture vid(0);
    namedWindow( "lena", CV_WINDOW_AUTOSIZE );
    namedWindow("win1",1);
    createTrackbar("Hue Min","win1",&hmin,255,ont);
    createTrackbar("Hue Max","win1",&hmax,255,ont);
    createTrackbar("Saturation Min","win1",&smin,255,ont);
    createTrackbar("Saturation Max","win1",&smax,255,ont);
    createTrackbar("Value Min","win1",&vmin,255,ont);
    createTrackbar("Value max","win1",&vmax,255,ont);
    ont(0,0);
    vid>>img;
    t1=Mat::zeros(img.rows,img.cols,CV_8UC1);
    t2=Mat::zeros(img.rows,img.cols,CV_8UC1);
    t3=Mat::zeros(img.rows,img.cols,CV_8UC1);
    while(true){
    vid>>img;
    GaussianBlur(img,img,Size(3,3),0.95,0.0);
    cvtColor(img,hsv,CV_RGB2HSV);
    //split(hsv,t1,t2,t3,NULL);
    for(int i=0;i<hsv.rows;i++)
    {
        for(int j=0;j<hsv.cols;j++){
                t1.at<uchar>(i,j)=hsv.at<Vec3b>(i,j)[0];
                t2.at<uchar>(i,j)=hsv.at<Vec3b>(i,j)[1];
                t3.at<uchar>(i,j)=hsv.at<Vec3b>(i,j)[2];
        }
    }
    inRange(t1,Scalar(hmin),Scalar(hmax),t1);
    inRange(t2,Scalar(smin),Scalar(smax),t2);
    inRange(t3,Scalar(vmin),Scalar(vmax),t3);
    inRange(hsv,Scalar(hmin,smin,vmin),Scalar(hmax,smax,vmax),bw);
    imshow("lena1", t1);
    imshow("lena2",t2);
    imshow("lena3",t3);
    imshow("lena",bw);
    if(waitKey(10)>=0) break;}
    return 0;
}



