#include <iostream>
#include <vector>
#include <random>
using namespace std;

// Simulate random success or failure (50% chance)
bool randomTrueFalse() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 1);
    return dis(gen) == 1;
}

int main() {
    int nFrames, windowSize;
    cout << "Enter number of frames: ";
    cin >> nFrames;

    cout << "Enter window size: ";
    cin >> windowSize;

    vector<string> data(nFrames);
    for (int i = 0; i < nFrames; ++i) {
        cout << "Data for frame " << i + 1 << ": ";
        cin >> data[i];
    }

    int i = 0; // Start of current window
    int retransmissions = 0;

    while (i < nFrames) {
        bool errorOccurred = false;

        cout << "\n--- Sending window from Frame " << i + 1 
             << " to Frame " << min(i + windowSize, nFrames) << " ---\n";

        for (int j = i; j < i + windowSize && j < nFrames; ++j) {
            cout << "Sending Frame " << j + 1 << " (" << data[j] << ")";
            if (randomTrueFalse()) {
                cout << " -> Received\n";
            } else {
                cout << " -> Lost\n";
                errorOccurred = true;
                break; // Stop sending, simulate Go-Back-N
            }
        }

        if (errorOccurred) {
            retransmissions++;
            cout << "Transmission error! Resending window starting from Frame " << i + 1 << "\n";
        } else {
            i += windowSize; // Move window forward
        }
    }

    cout << "\nAll frames sent successfully!\n";
    cout << "Total retransmissions: " << retransmissions << "\n";

    return 0;
}

