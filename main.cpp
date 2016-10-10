#include "Percolation.h"
#include <iostream>
#include <random>
#include <functional>
#include <ctime>
using namespace std;
int main() {
	int n = 200;
	int trails = 100;
	Percolation p0(n);
	std::default_random_engine generator(time(0));
	std::uniform_int_distribution<int> distribution(1, n);
	auto randpos = std::bind(distribution, generator);
	bool isper = false;
	vector<double> xi(trails, 0);
	
	for (int k = 0;k < trails;++k) {
		isper = false;
		while (!isper)
		{
			int i = randpos(), j = randpos();
			p0.open(i, j);
			isper = p0.percolates();
			//cout << p0.site_cnt<< endl;
		}
		xi[k] = (double)(p0.site_cnt) / (n*n);
		p0.clear();
		cout << k << endl;
	}

	double thre=0;
	for (int k = 0;k < trails;++k) {
		thre += xi[k];
	}
	thre /= trails;
	cout << thre << endl;
	
	system("pause");
	return 0;
}
