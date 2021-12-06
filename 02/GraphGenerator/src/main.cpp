#include <iostream>
#include "generator.h"

using std::cout, std::cin, std::endl;

int main(int argc, char** argv) {

    // Input
    unsigned nodeCount;
    unsigned weightCountMin;
    unsigned weightCountMax;
    unsigned nodeWeightSD;
    unsigned averageComponentCount;
    unsigned componentNodeCountSD;
    unsigned averageNodeDegree;
    unsigned nodeDegreeSD;
    if (argc > 8) {
        nodeCount = atoi(argv[1]);
        weightCountMin = atoi(argv[2]);
        weightCountMax = atoi(argv[3]);
        nodeWeightSD = atoi(argv[4]);
        averageComponentCount = atoi(argv[5]);
        componentNodeCountSD = atoi(argv[6]);
        averageNodeDegree = atoi(argv[7]);
        nodeDegreeSD = atoi(argv[8]);
    } else {
        cout << endl << "Enter node count:" << endl;
        cin >> nodeCount;
        cout << endl << "Enter weight count min:" << endl;
        cin >> weightCountMin;
        cout << endl << "Enter weight count max:" << endl;
        cin >> weightCountMax;
        cout << endl << "Enter node weight standart deviation:" << endl;
        cin >> nodeWeightSD;
        cout << endl << "Enter average component count:" << endl;
        cin >> averageComponentCount;
        cout << endl << "Enter component node count standart deviation:" << endl;
        cin >> componentNodeCountSD;
        cout << endl << "Enter average node degree:" << endl;
        cin >> averageNodeDegree;
        cout << endl << "Enter node degree standart deviation:" << endl;
        cin >> nodeDegreeSD;
    }

    // Process

    // Output
}
