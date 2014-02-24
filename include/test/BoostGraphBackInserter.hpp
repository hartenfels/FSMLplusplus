#ifndef FSML_BOOSTGRAPHBACKINSERTER_H
#define FSML_BOOSTGRAPHBACKINSERTER_H
#include "test/GenerateTest.hpp"
namespace fsml
{

class BoostGraphBackInserter : public std::back_insert_iterator<std::vector<std::string>>
{
public:
	explicit BoostGraphBackInserter(std::vector<std::string> &v) :
		std::back_insert_iterator<std::vector<std::string>>(v) {}

	BoostGraphBackInserter& operator=(BoostGraph::vertex_descriptor& value)
	{
		container->push_back("s" + std::to_string(value));
		return *this;
	}

	BoostGraphBackInserter& operator=(BoostGraph::vertex_descriptor&& value)
	{
		container->push_back("s" + std::to_string(value));
		return *this;
	}

	BoostGraphBackInserter& operator*() { return *this; }

	BoostGraphBackInserter& operator++() { return *this; }

	BoostGraphBackInserter operator++(int) { return *this; }
};

}
#endif // FSML_BOOSTGRAPHBACKINSERTER_H
