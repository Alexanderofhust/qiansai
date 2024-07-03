#include<opencv2/opencv.hpp>
//#include <xfeatures2d.hpp>  //SURF特征点头文件
#include <iostream>
#include<vector>
#include "main.h"

using namespace std;
using namespace cv;

float speedx, speedw;
vector<Point> points;



int navi_cal(void)
{
	
		mydetectQRcode1();
		move_cal(points);
	

	return 0;
}


void mydetectQRcode1(void)
{
	Mat img = imread("D:\\openCV\\catoons\\qrcode3.png");
	if (img.empty()) {
		cout << "请确认图像文件名称是否正确" << endl;
		//return -1; 
	}
	Mat gray, qrcode_bin;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	QRCodeDetector qrcodedetector;
	
	string information;
	bool isQRcode;
	isQRcode = qrcodedetector.detect(gray, points);  //识别二维码
	if (isQRcode)
	{
		//解码二维码
		information = qrcodedetector.decode(gray, points, qrcode_bin);
		cout << points << endl;  //输出二维码四个顶点的坐标
	}
	else
	{
		cout << "无法识别二维码，请确认图像时候含有二维码" << endl;
		//return -1;
	}
	//绘制二维码的边框
	for (int i = 0; i < points.size(); i++)
	{
		if (i == points.size() - 1)
		{
			line(img, points[i], points[0], Scalar(0, 0, 255), 2, 8);
			break;
		}
		line(img, points[i], points[i + 1], Scalar(0, 0, 255), 2, 8);
	}
	//将解码内容输出到图片上
	putText(img, information.c_str(), Point(20, 30), 0, 1.0, Scalar(0, 0, 255), 2, 8);

	//利用函数直接定位二维码并解码
	string information2;
	vector<Point> points2;
	information2 = qrcodedetector.detectAndDecode(gray, points2);
	cout << points2 << endl;
	putText(img, information2.c_str(), Point(20, 55), 0, 1.0, Scalar(0, 0, 0), 2, 8);

	//输出结果
	imshow("result", img);
	namedWindow("qrcode_bin", WINDOW_NORMAL);
	imshow("qrcode_bin", qrcode_bin);
	waitKey(1);
	//进行一次自动退出，放到主while进行循环
}
//传入的Point必须为4个点
void move_cal(const vector<Point>& xpoints5)
{
	int tempX, tempY, lastx, lasty;
	int centerX,centerY;
	int width, height;//宽和高取最大值
	int distance_para;
	int tempw = 0;
	int temph = 0;

	tempX = 0;
	tempY = 0;
	lastx = 0;
	lasty = 0;
	for (const auto& point: xpoints5) {
		tempX += point.x;
		tempY += point.y;
		if (0 == lastx)
		{
			lastx = point.x;
			lasty = point.y;
		}
		if (lastx != 0)
		{
			tempw = (point.x - lastx) * (point.x - lastx);
			temph = (point.y - lasty) * (point.y - lasty);
		}
		if (tempw > width)
		{
			width = tempw;
		}
		if (temph > height)
		{
			height = temph;
		}
	}
	lastx = 0;
	lasty = 0;
	tempw = 0;
	temph = 0;
	centerX = tempX / 4;
	centerX = tempY / 4;
	tempX = 0;
	tempY = 0;
	/*centerX = (static_cast<float>(xpoints1.x + xpoints2.x + xpoints3.x + xpoints4.x)) / 4;
	centerY = (static_cast<float>(xpoints1.y + xpoints2.y + xpoints3.y + xpoints4.y)) / 4;*/
	//由此确定了中心点的x，y坐标，我们实际要用的是的x来转向
	//此处也确定了二维码的大小
	distance_para = width + height;
	xspeedcal(distance_para);
	wspeedcal(centerX);
	
}

void xspeedcal(int xdistance)
{
	float p1, p2, p3,p01;
	p1 = 0;
	p2 = 0;
	p3 = 0;
	p01 = 0;
	//此处假设使用一个三次函数拟合，获得实际数据后标定，使用matlab拟合功能得到这个三次函数
	speedx = p1 * xdistance + p2 * xdistance * xdistance + p3 * xdistance * xdistance * xdistance + p01;;
}

void wspeedcal(int xcenterX)
{
	float p4, p5, p6,p02;
	p4 = 0;
	p5 = 0;
	p6 = 0;
	p02 = 0;
	//此处拟合原理同上
	speedw = p4 * xcenterX + p5 * xcenterX * xcenterX + p6 * xcenterX * xcenterX * xcenterX + p02;
}