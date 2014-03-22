//
//  main.cpp
//  SpatialFilter
//
//  Created by Tim Feirg on 3/22/14.
//  Copyright (c) 2014 Tim Feirg. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

static void help(const char* progName)
{
    cout << endl
    <<  "This program demonstrates spatial filter in OpenCV and basic spatial filter design. " << endl
    <<  "Usage:"                                                                      << endl
    << progName << " [image_name -- default lena.jpg] "                       << endl << endl;
}

int main(int argc, const char * argv[])
{
    help(argv[0]);
    
    // Load user specified image, if none, use lena as default target
    Mat source_image = (argc>=2) ? imread(argv[1]) : imread("/Users/timfeirg/Google Drive/OpenCV/DIP3E_Original_Images_CH02/Fig0222(a)(face).tif", CV_LOAD_IMAGE_GRAYSCALE),
    target_image;
    
    // initialize the box filter for demo purpose
    float box_array[3][3] = {
        {(float)1/9,(float)1/9,(float)1/9},
        {(float)1/9,(float)1/9,(float)1/9},
        {(float)1/9,(float)1/9,(float)1/9}
    };
    // another text book weighted average blur filter, described in page 120
    float weighted_avg_array[3][3] = {
        {(float)1/16,(float)2/16,(float)1/16},
        {(float)2/16,(float)4/16,(float)2/16},
        {(float)1/16,(float)2/16,(float)1/16}
    };
    // the laplacian filter is designed based on the coefficients I found on internet
    float laplacian_array[3][3] = {
        {-1,-1,-1},
        {-1,8,-1},
        {-1,-1,-1}
    };

    
    // creating filter as Mat objects based on the array just designed
    Mat box_filter = Mat( 3, 3, CV_32F, box_array ),
    laplacian_filter = Mat( 3, 3, CV_32F, laplacian_array ),
    weighted_avg_filter = Mat( 3, 3, CV_32F, weighted_avg_array);
    
    // start filtering in spatial domain, for convenience sake I store result of each process in the same target_image object, apologies
    filter2D( source_image, target_image, -1, box_filter );
    imshow("box filter blur effect", target_image);
    
    filter2D( source_image, target_image, -1, weighted_avg_filter);
    imshow("weighted average", target_image);
    
    filter2D( source_image, target_image, -1, laplacian_filter );
    imshow("Laplacian filter", target_image);
    
    // high-boost filtering from what I know is original image + Laplacian filtered image
    float highboost_coefficient = 1;
    target_image += highboost_coefficient * source_image;
    
    imshow( "high-boost filter", target_image );
    waitKey();
    
    return 0;
}

