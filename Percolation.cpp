#include "Percolation.h"
using std::vector;
Percolation::Percolation(int n) {
	grid_n = n;
	site_cnt = 0;
	for (int i = 0;i < (n+2)*(n+2); ++i)
	{
		grid.push_back(0);
	}
	UF = grid;
	UFsize = grid;
}

void Percolation::Union(int i0, int j0, int i1, int j1) {
	int c0 = Find(i0, j0), c1=Find(i1, j1);
	if (c0 == c1) return;
	// make smaller root point to the larger one
	if (UFsize[c0] < UFsize[c1]) {
		UF[c0] = c1;
		UFsize[c1] += UFsize[c0];
	}
	else {
		UF[c1] = c0;
		UFsize[c0] += UFsize[c1];
	}
}

bool Percolation::connected(int i0, int j0, int i1, int j1) {
	int idx0 = i0*(grid_n+2) + j0, idx1 = i1*(grid_n+2) + j1;
	return (UF[idx0]) && (UF[idx1]) && (Find(i0, j0) == Find(i1, j1));
}

int Percolation::Find(int i, int j) {
	int idx = i*(grid_n+2) + j;
	while (idx != UF[idx]) idx = UF[idx];
	return idx;
}

void Percolation::open(int i, int j) {
	if (isOpen(i, j)) return;
	if (i<1 || i>grid_n || j<1 || j>grid_n) {
		//cout << "index out of range!" << endl;
		exit(1);
	}
	int idx = i*(grid_n + 2) + j;
	++site_cnt;
	grid[idx] = 1;
	UF[idx] = idx;
	UFsize[idx] = 1;
	//left
	idx = i*(grid_n + 2) + j - 1;
	if (grid[idx])
		Union(i, j - 1, i, j);
	//right
	idx = i*(grid_n + 2) + j + 1;
	if (grid[idx])
		Union(i, j + 1, i, j);
	//up
	idx = (i-1)*(grid_n + 2) + j;
	if (grid[idx])
		Union(i-1, j, i, j);
	//down
	idx = (i+1)*(grid_n + 2) + j;
	if (grid[idx])
		Union(i+1, j, i, j);
}

bool Percolation::isOpen(int i, int j) {
	int idx = i*(grid_n+2) + j;
	return grid[idx] == 1;
}

bool Percolation::isFull(int i, int j) {
	int idx = i*(grid_n + 2) + j;
	if (!UF[idx]) return false;
	for (int k = 1;k <= grid_n; ++k) {
		if (connected(i, j, 1, k))
			return true;
	}
	return false;
}

bool Percolation::percolates() {
	for (int k = 1;k <= grid_n; ++k) {
		if (isFull(grid_n, k))
			return true;
	}
	return false;
}

void Percolation::clear() {
	site_cnt = 0;
	for (auto &i : grid)
			i = 0;
	for (auto &ii : UF)
			ii = 0;
}
