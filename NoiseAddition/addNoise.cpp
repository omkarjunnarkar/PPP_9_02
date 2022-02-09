#include<iostream>
#include<iomanip>
#include<fstream>
#include<math.h>
#include<vector>
#include<Eigen/Dense>
#include<cstdlib>
#include"src/rapidcsv.h"

using namespace std;
using namespace rapidcsv;
using namespace Eigen;

void main() {

	Document d2bar("displacement_2_bar.csv");
	vector<double> ycol2ele = d2bar.GetColumn<double>(0);
	int data_size2ele = ycol2ele.size();
	MatrixXd y_measured_2_ele(data_size2ele, 1);
	for (int u = 0; u < data_size2ele; u++) {
		y_measured_2_ele(u, 0) = ycol2ele[u];
	}

	Document dyt("displacement_tapered_10e.csv");
	vector<double> ycolt = dyt.GetColumn<double>(0);
	int data_sizet = ycolt.size();
	MatrixXd y_measured_t(data_sizet, 1);
	for (int u = 0; u < data_sizet; u++) {
		y_measured_t(u, 0) = ycolt[u];
	}

	ofstream noise2bar("noisy_displacement_2_bar.csv");
	ofstream noisetbar("noisy_displacement_tapered_10e.csv");

	double noise;

	for (int i = 0; i < data_size2ele; i++) {
		noise = ((double)rand() / (RAND_MAX)) ;
		noise = noise * 1e-4;
		
		y_measured_2_ele(i, 0) = y_measured_2_ele(i, 0) + noise ;
		noise2bar << y_measured_2_ele(i, 0) << endl;
		
	}

	for (int i = 0; i < data_sizet; i++) {
		noise = ((double)rand() / (RAND_MAX));
		noise = noise * 1e-5;

		y_measured_t(i, 0) = y_measured_t(i, 0) + noise;
		noisetbar << y_measured_t(i, 0) << endl;

	}

	noise2bar.close();
	noisetbar.close();

}