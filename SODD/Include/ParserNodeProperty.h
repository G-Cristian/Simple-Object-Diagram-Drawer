#ifndef _PARSERNODEPROPERTY_H_
#define _PARSERNODEPROPERTY_H_

#include <string>
#include "Parser.h"

using namespace std;

namespace prsr {
	class AbstractParserNodeProperty {
	public:
		AbstractParserNodeProperty() {}
		virtual ~AbstractParserNodeProperty() {}

		virtual void setThisPropertyToNodeProperty(NodeProperties& outNodeProperty) const = 0;
		virtual bool isValidProperty() const = 0;
	};

	class ParserNodeDescriptionProperty:public AbstractParserNodeProperty {
	public:
		ParserNodeDescriptionProperty(string &description) { _description = description; }
		virtual ~ParserNodeDescriptionProperty() {}

		void setThisPropertyToNodeProperty(NodeProperties& outNodeProperty) const override final { outNodeProperty.description = _description; }
		bool isValidProperty() const override final { return true; }
	private:
		string _description;
	};

	class ParserNodeRadiusProperty:public AbstractParserNodeProperty {
	public:
		ParserNodeRadiusProperty(double radius) { _radius = radius; }
		virtual ~ParserNodeRadiusProperty() {}

		void setThisPropertyToNodeProperty(NodeProperties& outNodeProperty) const override final { outNodeProperty.radius = _radius; }
		bool isValidProperty() const override final { return true; }
	private:
		double _radius;
	};

	class ParserNodeInvalidProperty :public AbstractParserNodeProperty {
	public:
		ParserNodeInvalidProperty() { }
		virtual ~ParserNodeInvalidProperty() {}

		void setThisPropertyToNodeProperty(NodeProperties& outNodeProperty) const override final { }
		bool isValidProperty() const override final { return false; }
	};
}

#endif // !_PARSERNODEPROPERTY_H_
