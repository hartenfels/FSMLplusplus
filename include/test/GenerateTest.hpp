#ifndef FSML_GENERATETEST_HPP
#define FSML_GENERATETEST_HPP
#include "fsml/FlatMachine.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>
namespace fsml
{
/// A directed graph with labeled vertices from the Boost.Graph library.
typedef boost::labeled_graph<boost::adjacency_list<boost::vecS, boost::vecS,
	boost::directedS>, std::string> BoostGraph;

/**Generates a FlatMachine for testing purposes.
@param numInitials The number of initial states.
@param numStates The number of non-initial states.
@param transitions The transition configuration.
@return A generated FlatMachine.*/
FlatMachine generateFlatMachine(const size_t& numInitials, const size_t& numStates,
	const boost::multiprecision::cpp_int& transitions);

/**Generates a FlatMachine and an equivalent BoostGraph for testing purposes.
@param numInitials The number of initial states.
@param numStates The number of non-initial states.
@param transitions The transition configuration.
@param[out] fm An empty FlatMachine to be filled.
@param[out] bg An empty BoostGraph to be filled.*/
void generateBoostGraph(const size_t& numInitials, const size_t& numStates,
	const boost::multiprecision::cpp_int& transitions, FlatMachine& fm, BoostGraph& bg);

}
#endif // FSML_GENERATETEST_HPP
