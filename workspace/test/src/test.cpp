/*
 * test.C
 *
 *  Created on: Jul 3, 2015
 *      Author: yamorn
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(void){
	string filename = "/home/yamorn/Pictures/p2253510452.jpg";

	Mat img = imread(filename);

	if(img.empty()){
		cout << " read failed." << endl;
		return -1;
	}

    namedWindow("Display Image",  WINDOW_AUTOSIZE  );

    imshow("Display Image", img);

    waitKey(0);

	return 0;
}



