#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cv.h>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
Mat src;
Mat pc[14];
// 0     1   2   3   4   5   6   7   8   9  10    11    12    13
//di33,di55,e33,e55,op5,op3,cs3,cs5,gd3,gd5,mor3,mor5};

//

int check(int x,int y,int z);
int mask33_Erosion(int x,int y,int z);
int mask33_Dilation(int x,int y,int z);

int mask55_Dilation(int x,int y,int z);
int mask55_Erosion(int x,int y,int z);

int mask33_Dilation_op(int x,int y,int z);
int mask55_Dilation_op(int x,int y,int z);
int mask33_Erosion_cs(int x,int y,int z);
int mask55_Erosion_cs(int x,int y,int z);
//
/** @function main */
int main(int argc, char** argv)
{
	String ins="F16";
	/// Read the image 
	src = imread(ins+".jpg", 1 );
	cvtColor( src, pc[0], CV_RGB2GRAY );
	cvtColor( src, pc[1], CV_RGB2GRAY );
	cvtColor( src, pc[2], CV_RGB2GRAY );
	cvtColor( src, pc[3], CV_RGB2GRAY );
	cvtColor( src, pc[4], CV_RGB2GRAY );
	cvtColor( src, pc[5], CV_RGB2GRAY );
	cvtColor( src, pc[6], CV_RGB2GRAY );
	cvtColor( src, pc[7], CV_RGB2GRAY );
	cvtColor( src, pc[8], CV_RGB2GRAY );
	cvtColor( src, pc[9], CV_RGB2GRAY );
	cvtColor( src, pc[10], CV_RGB2GRAY );
	cvtColor( src, pc[11], CV_RGB2GRAY );
	cvtColor( src, pc[12], CV_RGB2GRAY );
	cvtColor( src, pc[13], CV_RGB2GRAY );
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
				pc[0].at<uchar>(Point(i,j))= mask33_Dilation(i,j,-1);
				pc[2].at<uchar>(Point(i,j))= mask33_Erosion(i,j,-1);
				pc[1].at<uchar>(Point(i,j))= mask55_Dilation(i,j,-1);
				pc[3].at<uchar>(Point(i,j))= mask55_Erosion(i,j,-1);
					//cout<<"ROW:"<<mask55_Dilation(i,j)<<endl;
		}
		//cout<<"ROW:"<<mask55_Dilation(i,100)<<endl;
	}
	//opening&closing
	for(int i=0;i<col;i++){
		for(int j=0;j<row;j++){
				pc[4].at<uchar>(Point(i,j))= mask55_Dilation_op(i,j,3);
				pc[5].at<uchar>(Point(i,j))= mask33_Dilation_op(i,j,2);
				pc[7].at<uchar>(Point(i,j))= mask55_Erosion_cs(i,j,1);
				pc[6].at<uchar>(Point(i,j))= mask33_Erosion_cs(i,j,0);
					//cout<<"ROW:"<<mask55_Dilation(i,j)<<endl;
		}
		//cout<<"ROW:"<<mask55_Dilation(i,100)<<endl;
	}
	//gradient
	for(int i=0;i<col;i++){
		for(int j=0;j<row;j++){
				int tmp3=pc[0].at<uchar>(Point(i,j))-pc[2].at<uchar>(Point(i,j));
				int tmp5=pc[1].at<uchar>(Point(i,j))-pc[3].at<uchar>(Point(i,j));
				pc[8].at<uchar>(Point(i,j))= tmp3;
				pc[9].at<uchar>(Point(i,j))= tmp5;
					//cout<<"ROW:"<<mask55_Dilation(i,j)<<endl;
		}
		//cout<<"ROW:"<<mask55_Dilation(i,100)<<endl;
	}
	//morphological smoothing
	for(int i=0;i<col;i++){
		for(int j=0;j<row;j++){
				int tmp3=mask33_Dilation_op(i,j,5);
				int tmp5=mask55_Dilation_op(i,j,4);

				pc[10].at<uchar>(Point(i,j))= tmp3;
				pc[11].at<uchar>(Point(i,j))= tmp5;
		}
	}
	for(int i=0;i<col;i++){
		for(int j=0;j<row;j++){
				int tmp3=mask33_Erosion_cs(i,j,10);
				int tmp5=mask55_Erosion_cs(i,j,11);

				pc[12].at<uchar>(Point(i,j))= tmp3;
				pc[13].at<uchar>(Point(i,j))= tmp5;
		}
	}



	namedWindow( "d33", CV_WINDOW_AUTOSIZE );
	imshow( "d33", pc[0] );
	imwrite( ins+"_d33.jpg", pc[0]);

	namedWindow( "d55", CV_WINDOW_AUTOSIZE );
	imshow( "d55", pc[1] );
	imwrite( ins+"_d55.jpg", pc[1]);

	namedWindow( "e33", CV_WINDOW_AUTOSIZE );
	imshow( "e33",pc[2] );
	imwrite( ins+"_e33.jpg", pc[2]);

	namedWindow( "e55", CV_WINDOW_AUTOSIZE );
	imshow( "e55", pc[3] );
	imwrite( ins+"_e55.jpg", pc[3]);

	namedWindow( "op3", CV_WINDOW_AUTOSIZE );
	imshow( "op3", pc[5]);
	imwrite( ins+"_op3.jpg", pc[5]);

	namedWindow( "op5", CV_WINDOW_AUTOSIZE );
	imshow( "op5", pc[4]);
	imwrite( ins+"_op5.jpg", pc[4]);

	namedWindow( "cs3", CV_WINDOW_AUTOSIZE );
	imshow( "cs3", pc[6]);
	imwrite( ins+"_cs3.jpg", pc[6]);

	namedWindow( "cs5", CV_WINDOW_AUTOSIZE );
	imshow( "cs5", pc[7]);
	imwrite( ins+"_cs5.jpg", pc[7]);

	namedWindow( "gd3", CV_WINDOW_AUTOSIZE );
	imshow( "gd3", pc[8]);
	imwrite( ins+"_gd3.jpg", pc[8]);

	namedWindow( "gd5", CV_WINDOW_AUTOSIZE );
	imshow( "gd5", pc[9]);
	imwrite( ins+"_gd5.jpg", pc[9]);

	namedWindow( "mor3", CV_WINDOW_AUTOSIZE );
	imshow( "mor3", pc[12]);
	imwrite( ins+"_mor3.jpg", pc[12]);

	namedWindow( "mor5", CV_WINDOW_AUTOSIZE );
	imshow( "mor5", pc[13]);
	imwrite( ins+"_mor5.jpg", pc[13]);

	waitKey(0);
	return 0;
}
//
int mask33_Erosion(int x,int y,int z){
	int arr[9]={check(x-1,y-1,z),
				check(x,y-1,z),
				check(x+1,y-1,z),
				check(x-1,y,z),
				check(x,y,z),
				check(x+1,y,z),
				check(x-1,y+1,z),
				check(x,y+1,z),
				check(x+1,y+1,z)
	};
	sort(arr,arr+9);
	return arr[0];
}
int mask33_Dilation(int x,int y,int z){
	int arr[9]={check(x-1,y-1,z),
				check(x,y-1,z),
				check(x+1,y-1,z),
				check(x-1,y,z),
				check(x,y,z),
				check(x+1,y,z),
				check(x-1,y+1,z),
				check(x,y+1,z),
				check(x+1,y+1,z)
	};
	sort(arr,arr+9);
	return arr[8];
}

int mask55_Dilation(int x,int y,int z){
	int arr4[25]={0};
	int c=0;
	for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
			arr4[c]=check(i,j,z);
			c++;
		}
	}
	sort(arr4,arr4+25);
	/*if(x==100)
		cout<<"ROW:"<<arr2[24]<<endl;*/
	return arr4[24];
}
int mask55_Erosion(int x,int y,int z){
	int arr[25];
	int c=0;
	for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
			arr[c]=check(i,j,z);
			c++;
		}
	}
	sort(arr,arr+25);
	return arr[0];
}

int mask33_Dilation_op(int x,int y,int z){
	int arr[9]={check(x-1,y-1,z),
				check(x,y-1,z),
				check(x+1,y-1,z),
				check(x-1,y,z),
				check(x,y,z),
				check(x+1,y,z),
				check(x-1,y+1,z),
				check(x,y+1,z),
				check(x+1,y+1,z)
	};
	sort(arr,arr+9);
	return arr[8];
}
int mask55_Dilation_op(int x,int y,int z){
	int arr2[25]={0};
	int c=0;
	for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
			arr2[c]=check(i,j,z);
			c++;
		}
	}
	sort(arr2,arr2+25);
	return arr2[24];
}

int mask33_Erosion_cs(int x,int y,int z){
	int arr[9]={check(x-1,y-1,z),
				check(x,y-1,z),
				check(x+1,y-1,z),
				check(x-1,y,z),
				check(x,y,z),
				check(x+1,y,z),
				check(x-1,y+1,z),
				check(x,y+1,z),
				check(x+1,y+1,z)
	};
	sort(arr,arr+9);
	
	return arr[0];
}
int mask55_Erosion_cs(int x,int y,int z){
	int arr3[25]={0};
	int c=0;
	for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
			arr3[c]=check(i,j,z);
			c++;
		}
	}
	sort(arr3,arr3+25);
	return arr3[0];
}
/*
int mask33_op(int x,int y,int z){
	int ae=mask33_Erosion(x,y,z);
	Mat tp ;
	cvtColor( src, tp, CV_RGB2GRAY );


	sort(arr,arr+9);
	return arr[8];
}
int mask55_op(int x,int y,int z){
	int arr2[25]={0};
	int c=0;
	for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
			arr2[c]=check(i,j,z);
			c++;
		}
	}
	sort(arr2,arr2+25);
	return arr2[24];
}

int mask33_cs(int x,int y,int z){
	int arr[9]={check(x-1,y-1,z),
				check(x,y-1,z),
				check(x+1,y-1,z),
				check(x-1,y,z),
				check(x,y,z),
				check(x+1,y,z),
				check(x-1,y+1,z),
				check(x,y+1,z),
				check(x+1,y+1,z)
	};
	sort(arr,arr+9);
	
	return arr[0];
}
int mask55_cs(int x,int y,int z){
	int arr3[25]={0};
	int c=0;
	for(int i=x-2;i<=x+2;i++){
		for(int j=y-2;j<=y+2;j++){
			arr3[c]=check(i,j,z);
			c++;
		}
	}
	sort(arr3,arr3+25);
	if(x==250&&y==250)
				cout<<"!!"<<c<<endl;

	return arr3[0];
}
*/
//檢查是否出界
int check(int x,int y,int z){
	if(x>=0&&x<src.cols&&y>=0&&y<src.rows){
		int c=0;
		switch(z){
			case -1:
				c=src.at<uchar>(Point(x,y));
				break;
			case 0:
				c=pc[0].at<uchar>(Point(x,y));
				break;
			case 1:
				c=pc[1].at<uchar>(Point(x,y));
				break;
			case 2:
				c=pc[2].at<uchar>(Point(x,y));
				break;
			case 3:
				c=pc[3].at<uchar>(Point(x,y));
				break;
			case 4:
				c=pc[4].at<uchar>(Point(x,y));
				break;
			case 5:
				c=pc[5].at<uchar>(Point(x,y));
				break;
			case 6:
				c=pc[6].at<uchar>(Point(x,y));
				break;
			case 7:
				c=pc[7].at<uchar>(Point(x,y));
				break;
			case 8:
				c=pc[8].at<uchar>(Point(x,y));
				break;
			case 9:
				c=pc[9].at<uchar>(Point(x,y));
				break;
			case 10:
				c=pc[10].at<uchar>(Point(x,y));
				break;
			case 11:
				c=pc[11].at<uchar>(Point(x,y));
				break;

			default: 
				;
		}
		return 	c;
	}
	else
		return 0;
}

