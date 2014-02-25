#include "test/GenerateTest.hpp"

int
main()
{
	using namespace std; using namespace fsml; using namespace boost::multiprecision;
	const cpp_int maxT = 25;
	for (cpp_int t = 0; t <= maxT; ++t) {
		FlatMachine fm{generateFlatMachine(1, 1, t)};
		cout << t;
		for (const auto& s : fm.steps)
			cout << '&' << s.source << " -> " << s.target;
		cout << "\\\\\\hline\n";
	}
	return 0;
}
