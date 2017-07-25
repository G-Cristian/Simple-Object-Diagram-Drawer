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
	if (_matrix[node1][node2] & 2 == 2) {
		if (_matrix[node2][node1] & 2 == 2) {
			connectionDrawingAlgorithms.push_back(new DoubleArrowDrawingAlgorithm());
		}
		else {
			connectionDrawingAlgorithms.push_back(new ArrowDrawingAlgorithm());
		}
	}
	else if (_matrix[node2][node1] & 2 == 2) {
		connectionDrawingAlgorithms.push_back(new ReversedArrowDrawingAlgorithm());
	}

	//Also check for dashed arrows connections
	if (_matrix[node1][node2] & 4 == 4) {
		if (_matrix[node2][node1] & 4 == 4) {
			connectionDrawingAlgorithms.push_back(new DashedDoubleArrowDrawingAlgorithm());
		}
		else {
			connectionDrawingAlgorithms.push_back(new DashedArrowDrawingAlgorithm());
		}
	}
	else if (_matrix[node2][node1] & 4 == 4) {
		connectionDrawingAlgorithms.push_back(new ReversedDashedArrowDrawingAlgorithm());
	}

	return connectionDrawingAlgorithms;
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