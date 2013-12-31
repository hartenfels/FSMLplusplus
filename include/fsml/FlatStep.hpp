#ifndef FSML_FLATSTEP_HPP
#define FSML_FLATSTEP_HPP
#include <string>
namespace fsml
{

struct FlatStep {
	FlatStep(const std::string& source, const std::string& input,
			const std::string& action, const std::string& target);
	~FlatStep() = default;
	operator std::string() const;

    std::string source;
    std::string input;
    std::string action;
    std::string target;
};

}
#endif // FSML_FLATSTEP_HPP
