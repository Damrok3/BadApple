#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <string>

int main()
{
    cv::Mat img;
    img =  cv::imread("testimg.png");
    
    
        
    cv::Vec3b bgrPixel = img.at<cv::Vec3b>(1, 1);   //Vec3b - vector with 3 byte entries 
                                                    //which in this case are unsigned char values
    
    std::cout << (int)bgrPixel[1] << std::endl; //show one BGR value (reversed RGB)
    std::cout << bgrPixel<<std::endl;
    
    
    
    
    //cv::imshow("Window", img);

    //cv::waitKey(3000);

    return 0;
}

