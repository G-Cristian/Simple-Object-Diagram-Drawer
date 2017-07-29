#ifndef _CONNECTIVITYMATRIX_H_
#define _CONNECTIVITYMATRIX_H_

#include <vector>
#include <list>

#include "ConnectionDrawingAlgorithms.h"

using namespace std;

class ConnectivityMatrix {
public:
	ConnectivityMatrix(int nodesCount);
	~ConnectivityMatrix();

	void setEdgeBetweenNodes(int node1, int node2);
	void setArrowBetweenNodes(int node1, int node2);
	void setDashedArrowBetweenNodes(int node1, int node2);

	list<ConnectionDrawingAlgorithm*> getConnectionAlgorithmsBetweenNodes(int node1, int node2) const;
	bool hasConnection(int node1, int node2) const;
	bool hasArrow(int node1, int node2) const;
	bool hasDashedArrow(int node1, int node2) const;


	vector<list<int> > toAdjacencyList()const;

	int getNodeCounts() const;
private:
	int _nodesCount;
	vector<vector<int> > _matrix;
};

#endif // !_CONNECTIVITYMATRIX_H_

