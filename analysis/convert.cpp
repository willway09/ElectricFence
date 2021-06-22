#include <iostream>
#include <fstream>

int main() {
	std::ifstream input("analysis.csv");
	std::ofstream output("raw.dat", std::ios_base::binary);
	for(int i = 0; i < 800000; i++) {
		double d;
		input >> d;
		float f = (float)d;

		output.write((char*)(&f), 4);
	}
}
