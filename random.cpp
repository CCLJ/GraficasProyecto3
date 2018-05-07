#include <fstream>
#include <iostream>

using namespace std;

int main() {
	int sizeOfCube;
	cin >> sizeOfCube;
	ofstream outputFile("info_random.txt");
	outputFile << sizeOfCube << " " << sizeOfCube << " " << sizeOfCube << endl;
	for (int i = 0; i < sizeOfCube*sizeOfCube*sizeOfCube; ++i) {
		if (i < sizeOfCube * sizeOfCube * sizeOfCube - 1) {
			outputFile << int(rand() % 100 + 1) << endl;
		} else {
			outputFile << int(rand() % 100 + 1);
		}
	}
	outputFile.close();
}