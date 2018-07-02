#ifndef _PARSERNODECONNECTIVITY_H_

#include "ConnectivityMatrix.h"

using namespace std;

namespace prsr {
	class AbstractParserNodeConnectivity {
	public:
		AbstractParserNodeConnectivity() {}
		virtual ~AbstractParserNodeConnectivity() {}

		virtual void setConnectivityBetweenNodesInConnectivityMatrix(int node1, int node2, ConnectivityMatrix &connectivityMatrix) const = 0;
	};

	class ParserNodeNormalConnectivity :public AbstractParserNodeConnectivity {
	public:
		ParserNodeNormalConnectivity() {}
		virtual ~ParserNodeNormalConnectivity() {}

		void setConnectivityBetweenNodesInConnectivityMatrix(int node1, int node2, ConnectivityMatrix &connectivityMatrix) const override final {
			connectivityMatrix.setArrowBetweenNodes(node1, node2);
		}
	};

	class ParserNodeDashedConnectivity :public AbstractParserNodeConnectivity {
	public:
		ParserNodeDashedConnectivity() {}
		virtual ~ParserNodeDashedConnectivity() {}

		void setConnectivityBetweenNodesInConnectivityMatrix(int node1, int node2, ConnectivityMatrix &connectivityMatrix) const override final {
			connectivityMatrix.setDashedArrowBetweenNodes(node1, node2);
		}
	};
}

#endif // !_PARSERNODECONNECTIVITY_H_
