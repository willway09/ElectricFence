#include <iostream>
#include <fstream>

int main() {
	std::ifstream data("raw.dat", std::ios_base::binary);
	std::ifstream diff("abs.dat", std::ios_base::binary);
	std::ofstream recon("reconstructed.dat", std::ios_base::binary);
	std::ofstream changeArr("change.arr");

	int lookAhead = 5;
	int count = 800000;

	float* dataArr = new float[count];
	float* diffArr = new float[count];

	for(int i = 0; i < count; i++) {
		data.read((char*)(dataArr + i), 4);
		diff.read((char*)(diffArr + i), 4);
	}



	float lastVal = 0;
	int lastSet = 0;
	for(int i = 0; i < count - lookAhead; i++) {
		if(diffArr[i] > .3 ) {
			if(lastSet > 5) lastSet = 0;
			if(lastSet == 0) {
				float temp = dataArr[i + 5];
				if(temp > .5) {
					lastVal = 1;
				} else if(temp >= -.5) {
					lastVal = 0;
				} else {
					lastVal = -1;
				}

				changeArr << i << ", " << lastVal << std::endl;

				//lastVal = dataArr[i + 5];
			}
		}

		lastSet++;

		recon.write((char*)&lastVal, 4);
	}

	for(int i = 0; i < lookAhead; i++) {
		recon.write((char*)&lastVal, 4);
	}
}
