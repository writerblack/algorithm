//Problem description:
//在一组平面坐标里面，找到最近的一对坐标
//Given N(2<=N<=100,000) points on the plane, find the nearest two points, print the minimum distance. 

//input:
//Line 1: Line 1: an integer N, stands for the total number of points.
//N lines follow: each line contains a pair of (x, y) which are the coordinates of a point and splited by spaces, each value is no bigger than 1,000,000,000.

//output:
//Line1: the minimum distance, accurate up to 2 decimal places.

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdio>

using namespace std;

double getDistance(double x1, double y1, double x2, double y2){
	return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

const bool cmp_x(const vector<double>& a, const vector<double>& b){
	return a[0] < b[0];
}

const bool cmp_y(const vector<double>& a, const vector<double>& b){
	return a[1] < b[1];
}

double minDistance(vector<vector<double>>& array,int left,int right){
	if (left>= right)return numeric_limits<double>::max();
	if (left + 1 == right){
		double x1 = array[left][0];
		double y1 = array[left][1];
		double x2 = array[right][0];
		double y2 = array[right][1];
		return getDistance(x1,y1,x2,y2);
	}
	int median = (left + right) / 2;
	double leftMin=minDistance(array, left, median);
	double rightMin = minDistance(array, median+1, right);
	double ans = min(leftMin, rightMin);
	double medianX = array[median][0];
	sort(array.begin()+left, array.begin()+right+1, cmp_y);
	for (int i = left; i <=right; i++){
		for (int j = i+1; j <=right&&j<=left+11; j++){
			double d = getDistance(array[i][0], array[i][1], array[j][0], array[j][1]);
			ans = min(ans, d);
		}
	}
	return ans;
}

int main(){
	int n;
	scanf("%d", &n);
	vector<vector<double>> array;
	for (int i = 0; i < n; i++){
		vector<double> cur;
		double x,y;
		scanf("%lf %lf", &x,&y);
		cur.push_back(x);
		cur.push_back(y);
		array.push_back(cur);
	}
	sort(array.begin(), array.end(), cmp_x);
	double result = minDistance(array,0,n-1);
	printf("%.2f\n", result);
}