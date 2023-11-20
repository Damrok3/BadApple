#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <string>
#include <cmath>
#include <stdio.h>
#include <opencv2/videoio.hpp>
#include <chrono>

int main()
{
    cv::Mat img;
    cv::VideoCapture vid;
    cv::Mat frame;

    //vid.open("example.mp4"); //opens the vid
    //if (!vid.isOpened())
    //{
    //    printf("Error, unable to read the video file\n");
    //    return -1;
    //}

    //vid.release(); // closes the vid

    img =  cv::imread("testimg.png");
    cv::Size s = img.size();
    
    cv::Vec3b bgrPixel;
    //Vec3b - vector with 3 byte entries 
    //which in this case are unsigned char values
    std::string brightness_scale = ".'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"; //white-black
    //std::string brightness_scale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'."; //black-white
    unsigned int** arr = new unsigned int* [s.height];
    for (int i = 0; i < s.height; i++)
    {
        arr[i] = new unsigned int[s.width];
        for (int j = 0; j < s.width; j++)
        {
            int x = (int)img.at<cv::Vec3b>(i, j)[0];
            int y = (int)img.at<cv::Vec3b>(i, j)[1];
            int z = (int)img.at<cv::Vec3b>(i, j)[2];
            int vec_len = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
            arr[i][j] = vec_len / 6.48;
        }
    }
    std::ios::sync_with_stdio(false);
    std::stringstream bufor;
    for (int i = 0; i < s.height; i++)
    {
        for (int j = 0; j < s.width; j++)
        {
            //printf("%c",brightness_scale[arr[i][j]]);
            bufor << brightness_scale[arr[i][j]];
        }
        //printf("\n");
        bufor << '\n';
         
    }

    std::cout << bufor.str() << std::flush;

    
    //std::cout << (int)bgrPixel[1] << std::endl; //show one BGR value (reversed RGB)
    //std::cout << bgrPixel << std::endl;

    //cv::imshow("Window", img);

    //cv::waitKey(3000);

    return 0;
}

