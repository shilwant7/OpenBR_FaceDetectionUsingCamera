#include <openbr/openbr_plugin.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include<iostream>
using namespace std;
using namespace cv;

static void printTemplate(const br::Template &t)
{
    const QPoint firstEye = t.file.get<QPoint>("Affine_0");
    const QPoint secondEye = t.file.get<QPoint>("Affine_1");
//  const QPoint firstEye = t.file.get<QPoint>("First_Eye");
//  const QPoint secondEye = t.file.get<QPoint>("Second_Eye");
    printf("%s eyes: (%d, %d) (%d, %d)\n", qPrintable(t.file.fileName()), firstEye.x(), firstEye.y(), secondEye.x(), secondEye.y());
}

int main(int argc, char** argv)
{

 br::Context::initialize(argc, argv);

//  VideoCapture cap("rtsp://admin:password@ip/h264/ch1/main/av_stream?tcp");//for camera
VideoCapture cap("gd.mp4");//for video

 QSharedPointer<br::Transform> transform = br::Transform::fromAlgorithm("Open+Cascade(FrontalFace)+Draw(inPlace=true)");//+ASEFEyes

    if(!cap.isOpened())
        return -1;
    for(;;)
    {
        Mat frame;
        cap >> frame;

        if( frame.empty() )
            break; // end of video stream

        br::Template queryB(frame);
        queryB >> *transform;

        /*  const QPoint firstEye = queryB.file.get<QPoint>("First_Eye");
        const QPoint secondEye = queryB.file.get<QPoint>("Second_Eye");
        const QRect faceroi = queryB.file.get<QRect>("FrontalFace");

        cv::Point fe(firstEye.x(), firstEye.y());
        cv::Point se(secondEye.x(), secondEye.y());
        cv::Point te(firstEye.x() + 30, firstEye.y());

        cv::circle(frame, fe, 5.0, cv::Scalar(255, 0, 0));
        cv::circle(frame, se, 5.0, cv::Scalar(0, 0, 255));
        cv::rectangle(frame, Point (faceroi.x(),faceroi.y()), Point (faceroi.x()+faceroi.width(),faceroi.y()+faceroi.height()), Scalar(255,0,255),2,8,0);



        // float comparisonA = distance->compare(queryA, queryB);
        // printf("comparison Dennis to camera: %.3f\n", comparisonA);

        */
        imshow("camera is on !", frame);

        if( waitKey(1) == 27 ) break; // stop capturing by pressing ESC
    }
   
    // the camera will be closed automatically upon exit
    // cap.close();

    br::Context::finalize();
    return 0;
}
