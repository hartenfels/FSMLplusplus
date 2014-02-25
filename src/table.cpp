#include "test/GenerateTest.hpp"

int
main()
{
	using namespace std; using namespace fsml; using namespace boost::multiprecision;
	const cpp_int maxT = 50;
	for (cpp_int t = 0; t <= maxT; ++t) {
		FlatMachine fm{generateFlatMachine(1, 2, t)};
		cout << t;
		for (const auto& s : fm.steps)
			cout << ',' << s.source << " -> " << s.target;
		cout << '\n';
	}
	return 0;
}
