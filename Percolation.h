#ifndef PERCOLATION_H_
#define PERCOLATION_H_
#include <vector>

class Percolation {
public:
	Percolation(int n);
	void open(int i, int j);
	bool isOpen(int i, int j);
	bool isFull(int i, int j);
	void Union(int i0, int j0, int i1, int j1);
	int Find(int i, int j);
	bool connected(int i0, int j0, int i1, int j1);
	bool percolates();
	void clear();

	int grid_n;
	int site_cnt = 0;
	std::vector<int> grid;
	std::vector<int> UF;
	std::vector<int> UFsize;
};

#endif

