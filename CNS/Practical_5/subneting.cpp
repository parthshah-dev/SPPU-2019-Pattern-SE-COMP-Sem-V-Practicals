#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int calculateBorrowedBits(int numberOfSubnets) {
    for (int i = 1; i < 8; i++) {
        if (pow(2, i) == numberOfSubnets) {
            return i;
        }
    }
    return -1;
}

int binaryToDecimal(string& binaryString, int start, int end) {
    string binarySubstr = binaryString.substr(start, end - start);

    int decimal = 0;
    for (char bit : binarySubstr) {
        if (bit != '0' && bit != '1') {
            cerr << "Error: Invalid binary digit '" << bit << "' in subnet mask." << endl;
            return -1;
        }
        decimal = decimal * 2 + (bit - '0');
    }
    return decimal;
}

int main() {
    int numberOfSubnets;
    string inputIp;

    cout << "Enter IP address (e.g., 192.168.1.0): ";
    cin >> inputIp;

    cout << "Enter number of required subnets: ";
    cin >> numberOfSubnets;

    int borrowedBits = calculateBorrowedBits(numberOfSubnets);
    if (borrowedBits == -1) {
        cout << "Error: Invalid number of subnets. Must be a power of 2 (e.g., 2, 4, 8, 16... up to 256)." << endl;
        return 1;
    }

    cout << "\nNumber of bits to borrow from host portion: " << borrowedBits << endl;

    string subnetMaskBinary = "11111111.11111111.11111111.00000000";

    int bitPosition = 27;
    for (int j = 0; j < borrowedBits; j++) {
        subnetMaskBinary[bitPosition] = '1';
        bitPosition++;
    }

    cout << "Updated subnet mask in binary: " << subnetMaskBinary << endl;

    int subnetMaskDecimalLastOctet = binaryToDecimal(subnetMaskBinary, 27, subnetMaskBinary.size());
    cout << "Decimal value of last octet of subnet mask: " << subnetMaskDecimalLastOctet << endl;

    int blockSize = 256 / numberOfSubnets;

    vector<string> subnetAddresses;
    string baseIp = inputIp.substr(0, inputIp.rfind('.') + 1); // e.g., "192.168.1."

    for (int i = 0; i < numberOfSubnets; i++) {
        int subnetStart = i * blockSize;
        string subnetIp = baseIp + to_string(subnetStart);
        subnetAddresses.push_back(subnetIp);
    }

    cout << "\nGenerated Subnet Addresses:\n";
    for (int i = 0; i < subnetAddresses.size(); i++) {
        cout << "Subnet " << i + 1 << " network address: " << subnetAddresses[i] << endl;
    }

    return 0;
}
