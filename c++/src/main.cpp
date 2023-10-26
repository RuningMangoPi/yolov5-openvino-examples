#include "detector.hpp"

int main(int argc, char const *argv[]){
    Detector* detector = new Detector;
    std::string xml_path = "./yolov5s/yolov5s.xml";
    detector->init(xml_path,0.1,0.5);
    /*
    VideoCapture capture;
    capture.open(0);
    Mat src;
    while(1){
        capture >> src;
        vector<Detector::Object> detected_objects;
    detector->process_frame(src,detected_objects);
    for(int i=0;i<detected_objects.size();++i){
         int xmin = detected_objects[i].rect.x;
        int ymin = detected_objects[i].rect.y;
        int width = detected_objects[i].rect.width;
        int height = detected_objects[i].rect.height;
        Rect rect(xmin, ymin, width, height);//左上坐标（x,y）和矩形的长(x)宽(y)
        cv::rectangle(src, rect, Scalar(255, 0, 0),1, LINE_8,0);
    }
        cv::imshow("cap",src);
        waitKey(1);
    }
    */
    cv::Mat src = imread("./bus.jpg");
    cv::Mat osrc = src.clone();
    cv::resize(osrc,osrc, Size(640,640));
    vector<Detector::Object> detected_objects;

    auto start = chrono::high_resolution_clock::now();
    detector->process_frame(src,detected_objects);
    auto end = chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout<<"use "<<diff.count()<<" s" << std::endl;
    
    for(int i=0;i<detected_objects.size();++i){
         int xmin = detected_objects[i].rect.x;
        int ymin = detected_objects[i].rect.y;
        int width = detected_objects[i].rect.width;
        int height = detected_objects[i].rect.height;
        cv::Rect rect(xmin, ymin, width, height);//左上坐标（x,y）和矩形的长(x)宽(y)
        cv::rectangle(osrc, rect, Scalar(0, 255, 0), 2, LINE_8, 0);
    }
    // cv::imshow("result",osrc);
    // waitKey(0);
    cv::imwrite("result.jpg", osrc);

    return 0;
}