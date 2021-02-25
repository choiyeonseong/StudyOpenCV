//#include <opencv2\opencv.hpp>
//
//using namespace std;
//using namespace cv;
//
//void histogrammer(Mat grim, char* w, int c);
//void rgb_histogrammer(Mat src);
//void equalize_histogra(char *weq, Mat img, int x, int y);
//void hsv_skinner(Mat src, int wx, int wy);
//
//int W = 300, H = 200;
//
//int main(int argc, char* argv[])
//{
//	char *w0 = "입력";
//	Mat img, grim;
//	//char *fn = "LenaRGB.bmp";
//	char *fn2 = "faces_lessenthusia.jpg";
//
//	/*Starter - Load & display image*/
//	img = imread(fn2, IMREAD_COLOR);
//	if (img.empty()) { cout << "File Not Found" << endl; return -1; }
//	H = img.rows; W = img.cols; //min(W,img.cols);
//	namedWindow(w0, 1); imshow(w0, img);
//	moveWindow(w0, 50, 50);
//
//	cvtColor(img, grim, COLOR_BGR2GRAY);
//	
//	/*step 1*/
//	histogrammer(grim, "H0", -1);
//	
//	/*step 2*/
//	rgb_histogrammer(img);
//
//	/*step 3*/
//	hsv_skinner(img, 50 + (16 + W) * 2, 50); waitKey(0);
//	
//	waitKey(0);
//
//	return 0;
//}
// 
///*step 1*/
///*이미지에서 픽셀들이 가지는 값의 출현빈도 : 히스토그램*/
//void histogrammer(Mat src, char *whist, int chan) {
//	const int hSize[1] = { 256 };
//	int channels[1] = { 0 };
//	float hrange[2] = { 0.,256. };
//	const float* ranges[1];
//	ranges[0] = hrange;
//	Mat hist;
//
//	//히스토그램 계산
//	calcHist(&src, 1, channels, Mat(), hist, 1,hSize, ranges);
//
//	double HWhi = 100, maxval = 0;
//	Mat histIm(HWhi, hSize[0], CV_8U, Scalar(255));//Histgr 영상 생성
//	minMaxLoc(hist, 0, &maxval, 0, 0);	//minv,maxv,minloc,maxloc
//	double barscale = HWhi / maxval;	//height scaler(for histogram plot)
//
//	//막대그래프그리기
//	for (int b = 0; b < hSize[0]; b++) {
//		float binVal = hist.at<float>(b);
//		int h = (int)(binVal*barscale);
//		line(histIm, Point(b, hSize[0]), Point(b, HWhi - h), Scalar(0), 1);
//	}
//
//	namedWindow(whist, 1);
//	imshow(whist, histIm);
//	int cx = chan == -1 ? 1 : chan;
//	int cy = chan == -1 ? 0 : 2;
//	moveWindow(whist, 50 + (W + 16)*cx, 50 + (38 + H)*cy);
//
//}
//
///*step 2*/
//void rgb_histogrammer(Mat src) {
//	char *wC1 = "Blue", *wC2 = "Green", *wC3 = "Red";
//	vector<Mat> vex;
//	int Wp = W + 16, Hp = H + 38;
//
//	cv::split(src, vex);
//	
//	/*blue*/
//	namedWindow(wC1, 1);
//	imshow(wC1, vex[0]); moveWindow(wC1, 50, 50 + Hp);
//	
//	/*green*/	
//	namedWindow(wC2, 1);
//	imshow(wC2, vex[1]); moveWindow(wC2, 50+Wp, 50 + Hp);
//	
//	/*red*/
//	namedWindow(wC3, 1);
//	imshow(wC3, vex[2]); moveWindow(wC3, 50+Wp*2, 50 + Hp);
//	
//	histogrammer(vex[0], "Hb", 0);
//	histogrammer(vex[1], "Hg", 1);
//	histogrammer(vex[2], "Hr", 2);
//
//	equalize_histogra("EqHist[blue]", vex[0], 50 + Wp * 3, 50 + Hp);
//}
//
//void equalize_histogra(char *weq, Mat img, int x, int y)
//{
//	Mat eqHim;
//	equalizeHist(img, eqHim);//히스토그램 균일화, 평활화 -> 이미지의 콘트라스트 향상
//	namedWindow(weq, 1);
//	imshow(weq, eqHim); moveWindow(weq, x, y);
//	histogrammer(eqHim, "HEQ", 3);//--as if a 4th channel
//}
//
//
//void hsv_skinner(Mat src, int wx = 0, int wy = 0) {
//	Mat hsv, dst_bgr;
//	char *w = "HS(V=255)", *wskin = "HS-skin";
//	vector<Mat> vex;
//	int hminax[2] = { 160,10 }, sminax[2] = { 25,166 };
//	cvtColor(src, hsv, COLOR_BGR2HSV);
//
//	split(hsv, vex);
//	vex[2] = 255; //V channel = 255 - focus only on (H,S) -
//	merge(vex, hsv);
//	cvtColor(hsv, dst_bgr, COLOR_HSV2BGR);
//	namedWindow(w, 1); imshow(w, dst_bgr);
//	moveWindow(w, wx, wy);
//
//	Mat hmask, smask, mask2, skinmask;
//	//- hue masking -
//	threshold(vex[0], hmask, hminax[1], 255, THRESH_BINARY_INV);// below hminax[1] = 10?
//	threshold(vex[1], mask2, hminax[0], 255, THRESH_BINARY);	// above hminax[0] = 160?
//	if (hminax[0] < hminax[1])
//		hmask = hmask&mask2;
//	else hmask = hmask | mask2;
//
//	//- sat masking -
//	threshold(vex[1], smask, sminax[1], 255, THRESH_BINARY_INV);// below sminax[1] = 166
//	threshold(vex[1], mask2, sminax[0], 255, THRESH_BINARY);	// above sminax[0] = 25
//	smask = smask&mask2;
//
//	skinmask = hmask&smask;
//
//	Mat skindetect(src.size(), CV_8UC3, Scalar(0, 0, 0));	//- skin-only 출력 image -
//	src.copyTo(skindetect, skinmask);
//	namedWindow(wskin, 1);
//	imshow(wskin, skindetect);
//	moveWindow(wskin, wx + W + 16, wy);
//}