#ifndef FSML_GENERATETEST_HPP
#define FSML_GENERATETEST_HPP
#include "fsml/FlatMachine.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/labeled_graph.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>
namespace fsml
{
typedef boost::labeled_graph<boost::adjacency_list<boost::vecS, boost::vecS,
	boost::directedS>, std::string> BoostGraph;

FlatMachine generateFlatMachine(const size_t& numInitials, const size_t& numStates,
	const boost::multiprecision::cpp_int& transitions);

void generateBoostGraph(const size_t& numInitials, const size_t& numStates,
	const boost::multiprecision::cpp_int& transitions, FlatMachine& fm, BoostGraph& bg);

}
#endif // FSML_GENERATETEST_HPP
