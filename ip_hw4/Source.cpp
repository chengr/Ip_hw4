#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cv.h>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
Mat src,di33,di55,e33,e55,op5,op3,cs3,cs5;

//

int checks(int x,int y);
int check_op5(int x,int y);
int check_op3(int x,int y);
int check_cs5(int x,int y);
int check_cs3(int x,int y);
int mask33_Erosion(int x,int y);
int mask33_Dilation(int x,int y);

int mask55_Dilation(int x,int y);
int mask55_Erosion(int x,int y);

int mask33_Dilation_op(int x,int y);
int mask55_Dilation_op(int x,int y);
int mask33_Erosion_cs(int x,int y);
int mask55_Erosion_cs(int x,int y);
//
/** @function main */
int main(int argc, char** argv)
{
	String ins="F16";
	/// Read the image 
	src = imread(ins+".jpg", 1 );
	cvtColor( src, di33, CV_RGB2GRAY );
	cvtColor( src, di55, CV_RGB2GRAY );
	cvtColor( src, e33, CV_RGB2GRAY );
	cvtColor( src, e55, CV_RGB2GRAY );
	cvtColor( src, op5, CV_RGB2GRAY );
	cvtColor( src, cs5, CV_RGB2GRAY );
	cvtColor( src, op3, CV_RGB2GRAY );
	cvtColor( src, cs3, CV_RGB2GRAY );
	cvtColor( src, src, CV_RGB2GRAY );
	/// Show your results
	namedWindow( "src", CV_WINDOW_AUTOSIZE );
	imshow( "src", src );
	imwrite( ins+"_gry.jpg", src );
	int row=src.rows;
	int col=src.cols;

	//Dilation&Erosion
	for(int i=0;i<col;i++){
		for(int j=0;j<row;j++){
				di33.at<uchar>(Point(i,j))= mask33_Dilation(i,j);
				e33.at<uchar>(Point(i,j))= mask33_Erosion(i,j);
				di55.at<uchar>(Point(i,j))= mask55_Dilation(i,j);
				e55.at<uchar>(Point(i,j))= mask55_Erosion(i,j);
					//cout<<"ROW:"<<mask55_Dilation(i,j)<<endl;
		}
		//cout<<"ROW:"<<mask55_Dilation(i,100)<<endl;
	}
	//opening&closing
	for(int i=0;i<col;i++){
		for(int j=0;j<row;j++){
				op5.at<uchar>(Point(i,j))= mask55_Dilation_op(i,j);
				op3.at<uchar>(Point(i,j))= mask33_Dilation_op(i,j);
				cs5.at<uchar>(Point(i,j))= mask55_Erosion_cs(i,j);
				cs3.at<uchar>(Point(i,j))= mask33_Erosion_cs(i,j);
					//cout<<"ROW:"<<mask55_Dilation(i,j)<<endl;
		}
		//cout<<"ROW:"<<mask55_Dilation(i,100)<<endl;
	}



	namedWindow( "d33", CV_WINDOW_AUTOSIZE );
	imshow( "d33", di33 );
	imwrite( ins+"_d33.jpg", di33);

	namedWindow( "d55", CV_WINDOW_AUTOSIZE );
	imshow( "d55", di55 );
	imwrite( ins+"_d55.jpg", di55);

	namedWindow( "e33", CV_WINDOW_AUTOSIZE );
	imshow( "e33", e33 );
	imwrite( ins+"_e33.jpg", e33);

	namedWindow( "e55", CV_WINDOW_AUTOSIZE );
	imshow( "e55", e55 );
	imwrite( ins+"_e55.jpg", e55);

	namedWindow( "op3", CV_WINDOW_AUTOSIZE );
	imshow( "op3", op3);
	imwrite( ins+"_op3.jpg", op3);

	namedWindow( "op5", CV_WINDOW_AUTOSIZE );
	imshow( "op5", op5);
	imwrite( ins+"_op5.jpg", op5);

	namedWindow( "cs3", CV_WINDOW_AUTOSIZE );
	imshow( "cs3", cs3);
	imwrite( ins+"_cs3.jpg", cs3);

	namedWindow( "cs5", CV_WINDOW_AUTOSIZE );
	imshow( "cs5", cs5);
	imwrite( ins+"_cs5.jpg", cs5);

	waitKey(0);
	return 0;
}
//
int mask33_Erosion(int x,int y){
	int arr[9]={checks(x-1,y-1),
				checks(x,y-1),
				checks(x+1,y-1),
				checks(x-1,y),
				checks(x,y),
				checks(x+1,y),
				checks(x-1,y+1),
				checks(x,y+1),
				checks(x+1,y+1)
	};
	sort(arr,arr+9);
	return arr[0];
}
int mask33_Dilation(int x,int y){
	int arr[9]={checks(x-1,y-1),
				checks(x,y-1),
				checks(x+1,y-1),
				checks(x-1,y),
				checks(x,y),
				checks(x+1,y),
				checks(x-1,y+1),
				checks(x,y+1),
				checks(x+1,y+1)
	};
	sort(arr,arr+9);
	return arr[8];
}

int mask55_Dilation(int x,int y){
	int arr2[25]={0};
	int c=0;
	for(int i=x-2;i<x+2;i++){
		for(int j=y-2;j<y+2;j++){
			arr2[c]=checks(i,j);
			c++;
		}
	}
	sort(arr2,arr2+25);
	/*if(x==100)
		cout<<"ROW:"<<arr2[24]<<endl;*/
	return arr2[24];
}
int mask55_Erosion(int x,int y){
	int arr[25];
	int c=0;
	for(int i=x-2;i<x+2;i++){
		for(int j=y-2;j<y+2;j++){
			arr[c]=checks(i,j);
			c++;
		}
	}
	sort(arr,arr+25);
	return arr[0];
}

int mask33_Dilation_op(int x,int y){
	int arr[9]={check_op3(x-1,y-1),
				check_op3(x,y-1),
				check_op3(x+1,y-1),
				check_op3(x-1,y),
				check_op3(x,y),
				check_op3(x+1,y),
				check_op3(x-1,y+1),
				check_op3(x,y+1),
				check_op3(x+1,y+1)
	};
	sort(arr,arr+9);
	return arr[8];
}
int mask55_Dilation_op(int x,int y){
	int arr2[25]={0};
	int c=0;
	for(int i=x-2;i<x+2;i++){
		for(int j=y-2;j<y+2;j++){
			arr2[c]=check_op5(i,j);
			c++;
		}
	}
	sort(arr2,arr2+25);
	/*if(x==100)
		cout<<"ROW:"<<arr2[24]<<endl;*/
	return arr2[24];
}

int mask33_Erosion_cs(int x,int y){
	int arr2[25]={0};
	int c=0;
	for(int i=x-2;i<x+2;i++){
		for(int j=y-2;j<y+2;j++){
			arr2[c]=check_cs3(i,j);
			c++;
		}
	}
	sort(arr2,arr2+25);
	/*if(x==100)
		cout<<"ROW:"<<arr2[24]<<endl;*/
	return arr2[0];
}
int mask55_Erosion_cs(int x,int y){
	int arr[25];
	int c=0;
	for(int i=x-2;i<x+2;i++){
		for(int j=y-2;j<y+2;j++){
			arr[c]=check_cs5(i,j);
			c++;
		}
	}
	if(x==100)
		cout<<"ROW:"<<arr[0]<<endl;
	sort(arr,arr+25);
	return arr[0];
}

//檢查是否出界
int checks(int x,int y){
	if(x>=0&&x<src.cols&&y>=0&&y<src.rows){
		int c=src.at<uchar>(Point(x,y));
		return 	c;
	}
	else
		return 0;
}

int check_op5(int x,int y){
	if(x>=0&&x<src.cols&&y>=0&&y<src.rows){
		int c=e55.at<uchar>(Point(x,y));
		return 	c;
	}
	else
		return 0;
}
int check_op3(int x,int y){
	if(x>=0&&x<src.cols&&y>=0&&y<src.rows){
		int c=e33.at<uchar>(Point(x,y));
		return 	c;
	}
	else
		return 0;
}

int check_cs5(int x,int y){
	if(x>=0&&x<src.cols&&y>=0&&y<src.rows){
		int c=di55.at<uchar>(Point(x,y));
		return 	c;
	}
	else
		return 0;
}
int check_cs3(int x,int y){
	if(x>=0&&x<src.cols&&y>=0&&y<src.rows){
		int c=di33.at<uchar>(Point(x,y));
		return 	c;
	}
	else
		return 0;
}

