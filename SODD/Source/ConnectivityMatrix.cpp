#include "../Include/ConnectivityMatrix.h"

ConnectivityMatrix::ConnectivityMatrix(int nodesCount) {
	_nodesCount = nodesCount;

	_matrix = vector<vector<int> >(_nodesCount, vector<int>(nodesCount, 0));
}

ConnectivityMatrix::~ConnectivityMatrix() {

}

void ConnectivityMatrix::setEdgeBetweenNodes(int node1, int node2) {
	_matrix[node1][node2] |= 1;
}

void ConnectivityMatrix::setArrowBetweenNodes(int node1, int node2) {
	setEdgeBetweenNodes(node1, node2);
	setEdgeBetweenNodes(node2, node1);
	_matrix[node1][node2] |= 2;
}

void ConnectivityMatrix::setDashedArrowBetweenNodes(int node1, int node2) {
	setEdgeBetweenNodes(node1, node2);
	setEdgeBetweenNodes(node2, node1);
	_matrix[node1][node2] |= 4;
}

list<ConnectionDrawingAlgorithm*> ConnectivityMatrix::getConnectionAlgorithmsBetweenNodes(int node1, int node2) const {
	list<ConnectionDrawingAlgorithm*> connectionDrawingAlgorithms = list<ConnectionDrawingAlgorithm*>();
	//check for arrows connections
	if (hasArrow(node1, node2)) {
		if (hasArrow(node2, node1)) {
			connectionDrawingAlgorithms.push_back(new DoubleArrowDrawingAlgorithm());
		}
		else {
			connectionDrawingAlgorithms.push_back(new ArrowDrawingAlgorithm());
		}
	}
	else if (hasArrow(node2, node1)) {
		connectionDrawingAlgorithms.push_back(new ReversedArrowDrawingAlgorithm());
	}

	//Also check for dashed arrows connections
	if (hasDashedArrow(node1, node2)) {
		if (hasDashedArrow(node2, node1)) {
			connectionDrawingAlgorithms.push_back(new DashedDoubleArrowDrawingAlgorithm());
		}
		else {
			connectionDrawingAlgorithms.push_back(new DashedArrowDrawingAlgorithm());
		}
	}
	else if (hasDashedArrow(node2, node1)) {
		connectionDrawingAlgorithms.push_back(new ReversedDashedArrowDrawingAlgorithm());
	}

	return connectionDrawingAlgorithms;
}

bool ConnectivityMatrix::hasConnection(int node1, int node2) const {
	return (_matrix[node1][node2] & 1) == 1;
}

bool ConnectivityMatrix::hasArrow(int node1, int node2) const {
	return (_matrix[node1][node2] & 2) == 2;
}

bool ConnectivityMatrix::hasDashedArrow(int node1, int node2) const {
	return (_matrix[node1][node2] & 4) == 4;
}

vector<list<int> > ConnectivityMatrix::toAdjacencyList()const {
	vector<list<int> > adjacencyList = vector<list<int> >(_nodesCount);

	for (int row = 0; row < _nodesCount; ++row) {
		for (int column = 0; column < _nodesCount; ++column) {
			if (_matrix[row][column] & 1 == 1)
				adjacencyList[row].push_back(column);
		}
	}

	return adjacencyList;
}

int ConnectivityMatrix::getNodeCounts() const {
	return _nodesCount;
}