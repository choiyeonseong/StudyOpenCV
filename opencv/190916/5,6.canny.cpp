//#include <opencv2\opencv.hpp>
//#define PI 3.1416
//
//using namespace cv;
//using namespace std;
//
//void edgedetectors(char *);
//void CannyThresh(int, void*);
//void houghliner();
//void houghlineseg();
//
//int lowThr;
//Mat gim, cadge;
//char *wemap = "모서리맵";
//
//int main(int argc, char* argv[]) {
//	edgedetectors("정상");
//	return 0;
//}
//
//void edgedetectors(char* w0) {
//	Mat img = imread("Ontario_Highway_401.jpg",
//		IMREAD_COLOR);
//	if (img.empty()) { cout << "사진 없다." << endl; return; }
//	namedWindow(w0, WINDOW_AUTOSIZE);
//	imshow(w0, img);
//	moveWindow(w0, 100, 100);
//	waitKey(0);
//
//	//-(1)make it gray & smooth it-
//	cvtColor(img, gim, COLOR_RGB2GRAY);
//	char *w1 = "모서리";
//	imshow(w1, gim);
//	waitKey(0);
//
//	GaussianBlur(gim, gim, Size(3, 3), 0, 0, BORDER_DEFAULT);
//	imshow(w1, gim); waitKey(0);
//
//	//-(2)edge detection : Sobel,Laplacian, Canny-
//	Mat gradX, gradY, ddgim;
//	Mat absGradX, absGradY, gradim;
//	Mat edge;
//	int scale = 1, delta = 0, ddepth = CV_16S;
//	int ftype = 2;
//
//	//-Sobel
//	if (ftype == 1) {
//		Sobel(gim, gradX, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
//		convertScaleAbs(gradX, absGradX);
//		imshow(w1, absGradX); waitKey(0);
//		Sobel(gim, gradX, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
//		convertScaleAbs(gradY, absGradY);
//		imshow(w1, absGradY); waitKey(0);
//		addWeighted(absGradX, 0.5, absGradY, 0.5, delta, gradim);
//		imshow(w1, gradim); waitKey(0);
//		threshold(gradim, edge, 128, 255, THRESH_BINARY);
//		imshow(wemap, edge); waitKey(0);
//	}
//	else if(ftype==2){
//		//-Laplacian-
//		Laplacian(gim, ddgim, ddepth, 3, scale, 0, BORDER_DEFAULT);
//		convertScaleAbs(ddgim, gradim);
//		imshow(w1, gradim); waitKey(0);
//	}
//	else {
//		//-Canny-
//		namedWindow(wemap, WINDOW_AUTOSIZE);
//		createTrackbar("minThr", wemap, &lowThr, 100, CannyThresh);
//		CannyThresh(0, 0);
//		waitKey(0);
//
//	}
//}
//
//void CannyThresh(int, void*) {
//	int ratio = 3, kernelsz = 3;
//	int T1 = 55;
//	//edge처리, 결과 = cadge;
//	Canny(gim, cadge, T1, ratio*T1, 3, kernelsz);
//	houghliner();
//	imshow(wemap, cadge);
//}
//
//void houghliner() {
//	vector<Vec2f> lines;
//	int M = cadge.rows, N = cadge.cols;
//
//	HoughLines(cadge, lines, 1, PI / 180 * 1, 100 + lowThr);
//	vector<Vec2f>::iterator it = lines.begin();
//
//	while (it != lines.end()) {
//		float r = (*it)[0], q = (*it)[1];
//		if (q<PI*0.25 || q>PI*0.75) {
//			Point p1(r / cos(q), 0), p2((r - M*sin(q)) / cos(q), M);
//			line(cadge, p1, p2, Scalar(255 / 2), 1);
//		}
//		else if (q<PI * 70 / 180 || q>PI * 110 / 180) {
//			Point p1(0, r / sin(q)), p2(N, (r - N*cos(q)) / sin(q));
//			line(cadge, p1, p2, Scalar(255 / 2), 1);
//		}
//		++it;
//	}
//}
//
//
//void houghlineseg() {
//	vector<Vec4i> linsegs;
//	//int M=cadge.rows, N=cadge.cols;
//
//	HoughLinesP(cadge, linsegs, 1, PI / 180, 50 + lowThr, 40, 20);
//	vector<Vec4i>::iterator it = linsegs.begin();
//	while (it != linsegs.end()) {
//		Point p1((*it)[0], (*it)[1]), p2((*it)[2], (*it)[3]));
//		line(cadge, p1, p2, Scalar(255 / 2), 2);
//		++it;
//	}
//}
//
