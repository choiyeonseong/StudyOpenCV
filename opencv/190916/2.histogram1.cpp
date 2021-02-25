//#include <opencv2\opencv.hpp>
//
//using namespace std;
//using namespace cv;
//
//int W = 300, H = 200;
//
//
//
//int main(int argc, char* argv[])
//{
//	char *w0 = "ÀÔ·Â";
//	Mat img, grim;
//	char *fn = "LenaRGB.bmp";
//	char *fn2 = "faces_lessenthusia.jpg";
//
//	img = imread(fn2, IMREAD_COLOR);
//	if (img.empty()) { cout << "File Not Found" << endl; return -1; }
//	H = img.rows; W = img.cols;	//min(W,img.cols);
//	namedWindow(w0, 1); imshow(w0, img);
//	moveWindow(w0, 50, 50);
//
//	cvtColor(img, grim, COLOR_BGR2GRAY);
//	namedWindow("Èå¸²", 1); imshow("Èå¸²", grim);
//	moveWindow("Èå¸²", 50 + (W + 16), H);
//	
//	waitKey(0);
//	
//	return 0;
//}
