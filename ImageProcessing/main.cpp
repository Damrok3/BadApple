#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <string>
#include <cmath>
#include <stdio.h>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <chrono>
#include <thread>

#define VID_WIDTH 200
#define VID_HEIGHT 50



int main()
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT); //get rid of the debug info output to console

    cv::Mat img;
    cv::VideoCapture vid("badapple.mp4"); //opens the vid
    cv::Mat frame;

    if (!vid.isOpened())
    {
        printf("Error, unable to read the video file\n");
        return -1;
    }

    //img =  cv::imread("testimg.png");

    unsigned int** arr = new unsigned int* [VID_HEIGHT];
    for (int i = 0; i < VID_HEIGHT; i++)
    {
        arr[i] = new unsigned int[VID_WIDTH];
        for (int j = 0; j < VID_WIDTH; j++)
        {
            arr[i] = new unsigned int[VID_WIDTH];
        }
    }

    cv::Vec3b bgrPixel; //Vec3b - vector with 3 byte entries 
                        //which in this case are unsigned char values

    std::string brightness_scale = ".'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"; //white-black
    //std::string brightness_scale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'."; //black-white

    std::ios::sync_with_stdio(false);   //turns of synchronisation of streams 
                                        //(can just increase perfomrance in certain scenarios)
    


    while (vid.read(frame))
    {
        std::stringstream bufor;
       
        cv::resize(frame, frame, cv::Size(VID_WIDTH, VID_HEIGHT), cv::INTER_LINEAR);

        img = frame;

        for (int i = 0; i < VID_HEIGHT; i++)
        {
            for (int j = 0; j < VID_WIDTH; j++)
            {
                unsigned int x = (unsigned int)img.at<cv::Vec3b>(i, j)[0];
                unsigned int y = (unsigned int)img.at<cv::Vec3b>(i, j)[1];
                unsigned int z = (unsigned int)img.at<cv::Vec3b>(i, j)[2];
                unsigned int vec_len = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
                arr[i][j] = vec_len / 6.48;
            }
        }
        
        for (int i = 0; i < VID_HEIGHT; i++)
        {
            for (int j = 0; j < VID_WIDTH; j++)
            {   
                bufor << brightness_scale[arr[i][j]];
            }
            bufor << '\n';
        }
        
        std::cout << bufor.str() << std::flush; //thanks to this, i have the instant output
        std::chrono::milliseconds timespan(1);
        std::this_thread::sleep_for(timespan);
        system("cls");
    }
    vid.release(); // closes the vid

    for (int i = 0; i < VID_HEIGHT; i++)
    {
        arr[i] = new unsigned int[VID_WIDTH];
        for (int j = 0; j < VID_WIDTH; j++)
        {
            delete[] arr[i];
        }
    }
    delete[] arr;

    
    //std::cout << (int)bgrPixel[1] << std::endl; //show one BGR value (reversed RGB)
    //std::cout << bgrPixel << std::endl;

    //cv::imshow("Window", img);

    

    return 0;
}

