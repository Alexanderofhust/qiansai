#include<opencv2/opencv.hpp>
//#include <xfeatures2d.hpp>  //SURF������ͷ�ļ�
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
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		//return -1; 
	}
	Mat gray, qrcode_bin;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	QRCodeDetector qrcodedetector;
	
	string information;
	bool isQRcode;
	isQRcode = qrcodedetector.detect(gray, points);  //ʶ���ά��
	if (isQRcode)
	{
		//�����ά��
		information = qrcodedetector.decode(gray, points, qrcode_bin);
		cout << points << endl;  //�����ά���ĸ����������
	}
	else
	{
		cout << "�޷�ʶ���ά�룬��ȷ��ͼ��ʱ���ж�ά��" << endl;
		//return -1;
	}
	//���ƶ�ά��ı߿�
	for (int i = 0; i < points.size(); i++)
	{
		if (i == points.size() - 1)
		{
			line(img, points[i], points[0], Scalar(0, 0, 255), 2, 8);
			break;
		}
		line(img, points[i], points[i + 1], Scalar(0, 0, 255), 2, 8);
	}
	//���������������ͼƬ��
	putText(img, information.c_str(), Point(20, 30), 0, 1.0, Scalar(0, 0, 255), 2, 8);

	//���ú���ֱ�Ӷ�λ��ά�벢����
	string information2;
	vector<Point> points2;
	information2 = qrcodedetector.detectAndDecode(gray, points2);
	cout << points2 << endl;
	putText(img, information2.c_str(), Point(20, 55), 0, 1.0, Scalar(0, 0, 0), 2, 8);

	//������
	imshow("result", img);
	namedWindow("qrcode_bin", WINDOW_NORMAL);
	imshow("qrcode_bin", qrcode_bin);
	waitKey(1);
	//����һ���Զ��˳����ŵ���while����ѭ��
}
//�����Point����Ϊ4����
void move_cal(const vector<Point>& xpoints5)
{
	int tempX, tempY, lastx, lasty;
	int centerX,centerY;
	int width, height;//��͸�ȡ���ֵ
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
	//�ɴ�ȷ�������ĵ��x��y���꣬����ʵ��Ҫ�õ��ǵ�x��ת��
	//�˴�Ҳȷ���˶�ά��Ĵ�С
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
	//�˴�����ʹ��һ�����κ�����ϣ����ʵ�����ݺ�궨��ʹ��matlab��Ϲ��ܵõ�������κ���
	speedx = p1 * xdistance + p2 * xdistance * xdistance + p3 * xdistance * xdistance * xdistance + p01;;
}

void wspeedcal(int xcenterX)
{
	float p4, p5, p6,p02;
	p4 = 0;
	p5 = 0;
	p6 = 0;
	p02 = 0;
	//�˴����ԭ��ͬ��
	speedw = p4 * xcenterX + p5 * xcenterX * xcenterX + p6 * xcenterX * xcenterX * xcenterX + p02;
}