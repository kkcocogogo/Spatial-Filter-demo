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
    <<  "This program demonstrated the use of the discrete Fourier transform (DFT). " << endl
    <<  "The dft of an image is taken and it's power spectrum is displayed."          << endl
    <<  "Usage:"                                                                      << endl
    << progName << " [image_name -- default lena.jpg] "                       << endl << endl;
}

int main(int argc, const char * argv[])
{
    help(argv[0]);
    
    // Load user specified image, if none, use lena as default target
    Mat source_image = (argc>=2) ? imread(argv[1]) : imread("/Users/timfeirg/Google Drive/OpenCV/DIP3E_Original_Images_CH02/Fig0222(a)(face).tif", CV_LOAD_IMAGE_GRAYSCALE),
    target_image;
    
    // initialize the spatial filter!
    float box_array[3][3] = {
        {(float)1/9,(float)1/9,(float)1/9},
        {(float)1/9,(float)1/9,(float)1/9},
        {(float)1/9,(float)1/9,(float)1/9}
    };
    
    float laplacian_array[3][3] = {
        {-1,-1,-1},
        {-1,8,-1},
        {-1,-1,-1}
    };
    Mat box_filter = Mat( 3, 3, CV_32F, box_array ),
    laplacian_filter = Mat( 3, 3, CV_32F, laplacian_array);
    
    filter2D( source_image, target_image, -1, box_filter );
    
    imshow("box filter", target_image);
    filter2D( source_image, target_image, -1, laplacian_filter);
    imshow("Laplacian filter", target_image);
    waitKey();
    
    return 0;
}

