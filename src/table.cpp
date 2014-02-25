#include "test/GenerateTest.hpp"

int
main()
{
	using namespace std; using namespace fsml; using namespace boost::multiprecision;
<<<<<<< HEAD
	const cpp_int maxT = 50;
=======
	const cpp_int maxT = 241;
>>>>>>> 9cb849d224ca52fb081a03df758f396535235555
	for (cpp_int t = 0; t <= maxT; ++t) {
		FlatMachine fm{generateFlatMachine(1, 2, t)};
		cout << t;
		for (const auto& s : fm.steps)
			cout << ',' << s.source << " -> " << s.target;
		cout << '\n';
	}
	return 0;
}
