//
//#include "stdafx.h"
//#include "opencv2/highgui/highgui.hpp"
//
///**
//* @function main
//*/
//int main( int argc, const char** argv )
//{
//	CvCapture* capture;
//	IplImage* frame = 0;
//
//	while (true)
//	{
//		//Read the video stream
//		capture = cvCaptureFromCAM(1);
//		frame = cvQueryFrame( capture );
//
//		// create a window to display detected faces
//		cvNamedWindow("Sample Program", CV_WINDOW_AUTOSIZE);
//
//		// display face detections
//		cvShowImage("Sample Program", frame);
//
//		int c = cvWaitKey(10);
//		if( (char)c == 27 ) { exit(0); }
//
//	}
//
//	// clean up and release resources
//	cvReleaseImage(&frame);
//
//	return 0;
//
//}
//
#include "stdafx.h"

#define MyCode
#ifdef MyCode

#include <Windows.h>
#include <highgui.h>
#include <cv.h>
#include "skeletonization.h"
#include "analysis.h"

using namespace std;

#define MyCode1
#ifdef MyCode1
void sleep () {
	Sleep(3000);
}

void pause () {
	printf("%s", "press any key to continue\n");
	_gettch();
}

int radius = 7;
int radius_max=10;
void myTrackbarRadius(int pos) {
        radius = pos;
}
int iterations = 6;
int iterations_max = 10;
void myTrackbarIterations(int pos) {
        iterations = pos;
}
int block = 11;
int block_max = 100;
void myTrackbarBlock(int pos) {
        block = (pos%2 == 0 && pos != 0 ? pos + 1 : (pos < 3 ? 3 : pos));
}

int pixels = 8;
int pixels_max = 55;
void myTrackbarPixels(int pos) {
        pixels = pos;
}

//bilateral
int filter_height = 10, filter_height_max = 200, filter_width = 10, filter_width_max = 200, sigma1 = 0, sigma1_max = 500, sigma2 = 0, sigma2_max = 500;
void myTrackbarFilterHeight(int pos) {filter_height = pos;}
void myTrackbarFilterWidth(int pos) {filter_width = pos;}
void myTrackbarSigma1(int pos) {sigma1 = pos;}
void myTrackbarSigma2(int pos) {sigma2 = pos;}

int main (int argc, char** argv) {
#define image_input
#ifdef image_input
	IplImage *inputImage = 0;
	// ��� �������� ������� ������ ����������
    //char* filename = argc == 2 ? argv[1] : "test_find_pixel.bmp";
	//char* filename = argc == 2 ? argv[1] : "Barns_grand_tetons_HSV_separation.jpg";
	char* filename = argc == 2 ? argv[1] : "4.jpg";
    // �������� ��������
	inputImage = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);

	IplImage *inputImage1 = 0;
	inputImage1 = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED);
	//inputImage = cvLoadImage(filename, 1);
	//cvShowImage("original", inputImage);
    printf("[i] image: %s\n", filename);
    if (!inputImage) {
		printf("%s", "image not found\n");
		pause();
		exit(0);
	}
#define ice_search
#ifdef ice_search
	IplImage* hsv = cvCreateImage( cvGetSize(inputImage1), 8, 3 );
	IplImage* h_plane = cvCreateImage( cvGetSize(inputImage1), 8, 1 );
	IplImage* s_plane = cvCreateImage( cvGetSize(inputImage1), 8, 1 );
	IplImage* v_plane = cvCreateImage( cvGetSize(inputImage1), 8, 1 );
	cvCvtColor( inputImage1, hsv, CV_BGR2HSV );
	// ��������� �� ������
	cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );
	//for( int y=0; y < 20/*(h_plane->width)*/; y++) {
	//	uchar* ptr = (uchar*) (v_plane->imageData + y * v_plane->widthStep);
	//	for (int x = 0; x <= 20/*h_plane->height*/; x++) {
	//		cout << ptr[x] << " ";
	//	}
	//	cout << endl;
	//}
	//cvShowImage("h", h_plane);
	//cvShowImage("s", s_plane);
	/*IplImage* imageHue = cvCreateImage( cvGetSize(s_plane), 8, 1 );
	for( int y=0; y < imageHue->height; y++) {
		uchar* ptr = (uchar*) (imageHue->imageData + y * imageHue->widthStep);
		for (int x = 0; x <= imageHue->width; x++) {
			ptr[x] = 255;
		}
		cout << endl;
	}
	IplImage* imageSat = cvCreateImage( cvGetSize(s_plane), 8, 1 );
	for( int y=0; y < imageSat->height; y++) {
		uchar* ptr = (uchar*) (imageSat->imageData + y * imageSat->widthStep);
		for (int x = 0; x <= imageSat->width; x++) {
			ptr[x] = 255;
		}
		cout << endl;
	}
	IplImage* imageVal = cvCreateImage( cvGetSize(v_plane), 8, 1 );
	for( int y=0; y < imageVal->height; y++) {
		uchar* ptr = (uchar*) (imageVal->imageData + y * imageVal->widthStep);
		for (int x = 0; x <= imageVal->width; x++) {
			ptr[x] = 255;
		}
		cout << endl;
	}*/
	IplImage* imageVal = cvCreateImage( cvGetSize(v_plane), 8, 1 );
	for( int y=0; y < 20/*v_plane->height*/; y++) {
		uchar* ptr = (uchar*) (v_plane->imageData + y * v_plane->widthStep);
		for (int x = 0; x <= 20/*v_plane->width*/; x++) {
			printf("%d ", ptr[x]);
		}
		cout << endl;
	}
	//IplImage* mergeImage = cvCreateImage( cvGetSize(h_plane), 8, 3 );
	//cvMerge(imageHue, v_plane, imageSat, 0, mergeImage);
	//cvShowImage("mergeImage", mergeImage);
	cvShowImage("v_plane", v_plane);
	//����� ������� 5�5
	//��������� � ������� ���
	//�� ��� �� ��
#endif //ice_search
//#define build_skelets
#ifdef build_skelets
	//inputImage = buildSkeleton(inputImage);
	vector <Skelet> skelets;
	skelets = getSkelets(buildSkeleton(inputImage));
	Skelet skelet1 = skelets[0];

	IplImage *inputImage2 = cvLoadImage("test_find_pixel_2.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	if (!inputImage2) {
		printf("%s", "image not found\n");
		pause();
		exit(0);
	}
	vector <Skelet> skelets_2;
	skelets_2 = getSkelets(inputImage2);
	cvReleaseImage(&inputImage2);
	
	Skelet skelet2 = skelets_2[0];
	//bool fl = compareSkelets(skelet1, skelet2);
#endif
#endif
//#define main_action
#ifdef main_action
	cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
	//��������� �������
	IplImage *improvedImage = cvCreateImage( cvGetSize(inputImage), IPL_DEPTH_8U, 3 );
	
	printf("improve Image Quality started\n");
	improveImageQuality(inputImage1, improvedImage);
	printf("improve Image Quality finished\n");
	cvNamedWindow("improved",0/*CV_WINDOW_AUTOSIZE*/);
	cvShowImage("improved", improvedImage);
    

	//����������� �����������
	//IplImage *erode = cvCloneImage(newImage);
	//IplImage *dilate = cvCloneImage(newImage);
	IplImage *sum = cvCloneImage(improvedImage);
	IplImage *gray = cvCreateImage( cvGetSize(improvedImage), IPL_DEPTH_8U, 1 );
	IplImage *dst = cvCreateImage( cvGetSize(improvedImage), IPL_DEPTH_8U, 1 );
	
	
	//IplImage *bin = cvCreateImage( cvGetSize(inputImage), IPL_DEPTH_8U, 1 );
	
	
	
	cvCreateTrackbar("Radius", "original", &radius, radius_max, myTrackbarRadius);
	cvCreateTrackbar("Iterations", "original", &iterations, iterations_max, myTrackbarIterations);
	cvCreateTrackbar("Pix", "original", &pixels, pixels_max, myTrackbarPixels);
	cvCreateTrackbar("Block", "original", &block, block_max, myTrackbarBlock);
	cvCreateTrackbar("HeightF", "original", &filter_height, filter_height_max, myTrackbarFilterHeight);
	cvCreateTrackbar("WidthF", "original", &filter_width, filter_width_max, myTrackbarFilterWidth);
	cvCreateTrackbar("Sigma 1", "original", &sigma1, sigma1_max, myTrackbarSigma1);
	cvCreateTrackbar("Sigma 2", "original", &sigma2, sigma2_max, myTrackbarSigma2);
	cvShowImage("original", inputImage);
	cvNamedWindow("canny200-250", 1); //��� �� ��� ��������� ���������
	
	cvNamedWindow("bin", 1);
	int source_radius = radius, source_iterations = iterations, source_block = block, source_pixels = pixels;
	while(1) {
		//if () {
				IplConvKernel* Kern = cvCreateStructuringElementEx(radius*2+1, radius*2+1, radius, radius, CV_SHAPE_ELLIPSE);
				printf("dilate started\n");
				cvDilate(improvedImage, sum, Kern, iterations);
				printf("dilate finished\n");
				printf("erode started\n");
				cvErode(sum, sum, Kern, iterations);
				printf("erode finished\n");
				//cvShowImage("SUM", sum);
				cvReleaseStructuringElement(&Kern);
		
				printf("Smoothing started\n");	
				IplImage *smoothImage = cvCloneImage(sum);
				cvSmooth(sum, smoothImage, CV_BILATERAL, filter_height, filter_width, sigma1, sigma2);
				cvNamedWindow("smooth", 0);
				cvShowImage("smooth", smoothImage);
				printf("Smoothing finished\n");
			//IplImage *dst = cvCreateImage( cvGetSize(improvedImage), IPL_DEPTH_8U, 1 );
			//IplImage *smoothImage = cvLoadImage("smooth.jpg", 1);
			
				IplImage *gray = cvCreateImage( cvGetSize(improvedImage), IPL_DEPTH_8U, 1 );
				cvCvtColor(smoothImage, gray, CV_RGB2GRAY);
				IplImage *bin = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 1);
				printf("Adaptive Threshold started\n");
				cvAdaptiveThreshold(gray, bin, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, block, pixels);
				printf("Adaptive Threshold finished\n");
				cvShowImage("bin", bin);
				printf("Canny started\n");
				cvCanny(gray, dst, 200, 250, 3);
				printf("Canny finished\n");
				cvShowImage("canny200-250", dst);

				//���������� ������� ���� �������
				CvMemStorage* storage = cvCreateMemStorage(0);
				CvSeq* contours=0;
				IplImage *imageInRange = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 1);
				//cvInRangeS(gray, cvScalar(40), cvScalar(150), imageInRange);
				int contoursCont = cvFindContours(bin, storage, &contours,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));
				IplImage *dst1 = cvCloneImage(improvedImage);
				for(CvSeq* seq0 = contours; seq0 != 0; seq0 = seq0->h_next){
					cvDrawContours(dst1, seq0, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8);
				}
				cvNamedWindow("contours", 0);
				cvShowImage("contours", dst1);
				cvReleaseImage(&imageInRange);
				cvReleaseImage(&dst1);

				cvReleaseImage(&gray);
				cvReleaseImage(&bin);
				cvReleaseImage(&smoothImage);
		//}
			char c = cvWaitKey(33);
			if (c == 27) {
				break;
			}
			//cvReleaseImage(&smoothImage);

			//cvReleaseImage(&dst);
			system("cls");
		
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&dst);
	cvReleaseImage(&sum);
	cvReleaseImage(&improvedImage);
	cvReleaseImage(&inputImage1);
#endif

	//��������� �������� �� �������
	//���������� ������ ��� ������� ��� ������ ��������

	//����� ������� �������� �� �������
	//���������� 2 ������ �� ������� ������� �������� � ��������

	//���������� �������������� ������ ������
	
	//���������� ���������� �� ������ �� �������� �� ������ ������

	//���������� �������������� ��������� �������� �� ������ ������

	//����������� ����������� �������� �������� �� ������ ������

	//���������� ���������� �������� ��������

	//����� �������� �������� �������� �� ������ ������
	//����� �����, ����������� ��������� ������ � ���� �� �������
	
	printf("All done\n");
	//pause();
	//cvWaitKey(0);
	while( 1 )
	{
		if( cvWaitKey( 100 ) == 27 )
		break;
	}
	cvDestroyAllWindows();
	//cvReleaseImage(&inputImage);
	return 1;
}
#endif
#endif