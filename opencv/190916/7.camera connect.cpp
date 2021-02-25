#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//void edgedetectors(char*);
//void houghliner(char *);
void camerashooter(char*);
void skin_color_processor(Mat img, Mat face);
bool isskin(Vec3b px3);
bool isskin_Peer(uchar r, uchar g, uchar b);

int main(int argc, char* argv[]) {
	//edgedetectors("Á¤»ó");
	camerashooter("¹æ¼ÛÁß");

	return(0);
}

void camerashooter(char* wcam) {
	Mat frame;
	bool stop(false);
	int fps = 30;
	VideoCapture cap(0);
	if (!cap.isOpened()) return;
	int wide = (int)cap.get(CAP_PROP_FRAME_WIDTH);
	int high = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
	namedWindow(wcam, WINDOW_AUTOSIZE);
	moveWindow(wcam, 100, 100);

	//-read a frame and display it,and ...
	Mat fays = Mat::zeros(Size(wide, high), CV_8U);
	Mat face = Mat::zeros(Size(wide, high), CV_8U);

	while (!stop) {
		cap >> frame;
		imshow(wcam, frame);
		//-any image processing & analysis -
		fays.copyTo(face);//clear up!
		skin_color_processor(frame, face); imshow("¾ó±¼", face);
		moveWindow("¾ó±¼", 100 + 640, 100);
		if (waitKey(1000 / fps) >= 0) stop = true;
	}
	cap.release();
}

void skin_color_processor(Mat img, Mat face) {
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			
			if (isskin(img.at<Vec3b>(i, j)))
				face.at<uchar>(i, j) = 255;
		}
	}
}


bool isskin(Vec3b px3) {
	return isskin_Peer(px3[2], px3[1], px3[0]);
}

bool isskin_Peer(uchar r, uchar g, uchar b) {
	if (!(r > 95 && g > 40 && b > 20)) return false;
	else if (!(abs(r - b) > 15 && r > g&&r > b)) return false;
	else {
		uchar mx = max(r, g);
		uchar mn = min(r, b);
		if (max(mx, b) - min(mn, b) <= 15)return false;
		else return true;
	}
}