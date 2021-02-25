//#include <opencv2\opencv.hpp>
//#include <opencv2\core.hpp>
//#include <opencv2\highgui.hpp>
//#include <Windows.h>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//void morphrocessor(char *);
//void skin_color_processor(Mat img, Mat face);
//bool isskin(Vec3b px3);
//Mat locateFaces(Mat mface);
//void drawReEBounds(Mat, vector<vector<Point>>, vector<Vec4i>, Mat);
//
//int main(int argc, char* argv[]) {
//	morphrocessor("형태처리");
//	return 0;
//}
//
//void morphrocessor(char* w0) {
//	Mat img = imread("worldleaders_atUN.jpg", IMREAD_COLOR);
//	Mat face = Mat::zeros(Size(img.cols, img.rows), CV_8U);
//	Mat mface = face.clone();
//	if (img.empty()) { cout << "사진없다." << endl; return; }
//
//	namedWindow(w0, WINDOW_AUTOSIZE);
//	imshow(w0, img);
//	moveWindow(w0, 100, 100);
//	waitKey(0);
//
//	//- find skin pixels -
//	skin_color_processor(img, face);
//	imshow("얼굴", face);
//	waitKey(0);
//
//	//- MORPHGY:erode/dilate/open/close -
//	if (1) {
//		// 0 or 1
//		erode(face, mface, Mat(), Point(-1, -1), 1);
//		dilate(mface, mface, Mat(), Point(-1, -1), 1);
//	}
//	else {
//		Mat mel(5, 5, CV_8U, Scalar(1));
//		morphologyEx(face, mface, MORPH_OPEN, mel);
//		morphologyEx(mface, mface, MORPH_CLOSE, mel);
//	}
//	imshow("얼굴", mface);
//	waitKey(0);
//
//	//-find face contours -
//	Mat fcontr = locateFaces(mface);
//	imshow("얼굴윤곽", fcontr);
//	waitKey(0);
//}
//
//void skin_color_processor(Mat img, Mat face) {
//	for (int i = 0; i < img.rows; i++) {
//		for (int j = 0; j < img.cols; j++) {
//			if (isskin(img.at<Vec3b>(i, j)))
//				face.at<uchar>(i, j) = 255;
//		}
//	}
//}
//
//bool isskin_Peer(uchar r, uchar g, uchar b) {
//	if (!(r > 95 && g > 40 && b > 20)) return false;
//	else if (!(abs(r - b) > 15 && r > g&&r > b)) return false;
//	else {
//		uchar mx = max(r, g);
//		uchar mn = min(r, b);
//		if (max(mx, b) - min(mn, b) <= 15)return false;
//		else return true;
//	}
//}
//
//bool isskin(Vec3b px3) {
//	return isskin_Peer(px3[2], px3[1], px3[0]);
//}
//
//Mat locateFaces(Mat mface) {
//	Mat canny_oput;
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//	RNG rng(12345);
//	int thresh = 100;//Canny
//
//	Canny(mface, canny_oput, thresh, thresh * 2, 3);//aperture
//	findContours(canny_oput, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));//mode, method, offset
//
//	//- draw contours -
//}