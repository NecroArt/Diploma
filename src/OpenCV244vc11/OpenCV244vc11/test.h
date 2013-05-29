#ifndef TEST_H
#define TEST_H
#include "stdafx.h"

using namespace std;

#define SIDE_LENGTH 20
#define S_THESHOLD 10 //вроде подходит
#define V_THESHOLD 165 //вроде подходит

void fillPlans (IplImage *h_plane, IplImage *s_plane, IplImage *v_plane, int depth) {
	int sum = 0;
	for (int x = 0; x < v_plane->width; x += SIDE_LENGTH) {
		for (int y = 0; y < v_plane->height; y += SIDE_LENGTH) {
			//cvSetImageROI(h_plane, cvRect(x, y, SIDE_LENGTH, SIDE_LENGTH));
			cvSetImageROI(s_plane, cvRect(x, y, SIDE_LENGTH, SIDE_LENGTH));
			cvSetImageROI(v_plane, cvRect(x, y, SIDE_LENGTH, SIDE_LENGTH));
			//CvScalar h = cvAvg(h_plane);
			CvScalar s = cvAvg(s_plane);
			CvScalar v = cvAvg(v_plane);
			//cvResetImageROI(h_plane);
			//cout << "s = " << s.val[0] << endl;
			cvResetImageROI(s_plane);
			cvResetImageROI(v_plane);
			if (/*h.val[0] < 5 && */s.val[0] < S_THESHOLD && v.val[0] > V_THESHOLD) {
				sum += SIDE_LENGTH * SIDE_LENGTH;
				for (int i = 0; i < SIDE_LENGTH && (y+i) < h_plane->height; i++) {
					uchar* h_ptr = (uchar*) (h_plane->imageData + (y+i) * h_plane->widthStep);
					uchar* s_ptr = (uchar*) (s_plane->imageData + (y+i) * s_plane->widthStep);
					for (int j = 0; j < SIDE_LENGTH && (x+j) < h_plane->width; j++) {
						h_ptr[x+j] = 0;
						s_ptr[x+j] = 255;
					}
				}
			}
		}
	}
	cout << "sum = " << sum << endl;
	cout << "image size: " << v_plane->height * v_plane->width << endl;
	cout << "% = " << (float)(sum * 100)/(v_plane->height * v_plane->width) << endl;

	IplImage* mergeImage = cvCreateImage( cvGetSize(h_plane), depth, 3 );
	IplImage* mergeImageRGB = cvCreateImage( cvGetSize(h_plane), depth, 3 );
	//cvMerge(imageHue, s_plane, v_plane, 0, mergeImage);
	cvMerge(h_plane, s_plane, v_plane, 0, mergeImage);
	cvCvtColor(mergeImage, mergeImageRGB, CV_HSV2BGR);
	cvShowImage("mergeImage", mergeImageRGB);
	cvSaveImage("ice_search.jpg", mergeImageRGB);
	cvReleaseImage(&mergeImage);
	cvReleaseImage(&mergeImageRGB);
}

void plan_output (IplImage *h_plane, IplImage *s_plane, IplImage *v_plane) {
	for( int y=0; y < SIDE_LENGTH; y++) {
		uchar* ptr = (uchar*) (h_plane->imageData + y * h_plane->widthStep);
		for (int x = 0; x <= SIDE_LENGTH; x++) {
			printf("%d ", ptr[x]);
		}
		cout << endl;
	}
	cout << "------------------------------" << endl;
	for( int y=0; y < SIDE_LENGTH; y++) {
		uchar* ptr = (uchar*) (s_plane->imageData + y * s_plane->widthStep);
		for (int x = 0; x <= SIDE_LENGTH; x++) {
			printf("%d ", ptr[x]);
		}
		cout << endl;
	}
	cout << "------------------------------" << endl;
	for( int y=0; y < SIDE_LENGTH; y++) {
		uchar* ptr = (uchar*) (v_plane->imageData + y * v_plane->widthStep);
		for (int x = 0; x <= SIDE_LENGTH; x++) {
			printf("%d ", ptr[x]);
		}
		cout << endl;
	}
}
#endif