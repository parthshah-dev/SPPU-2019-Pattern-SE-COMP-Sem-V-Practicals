#include <iostream>
#include <vector>
#include <random>
using namespace std;

bool randomTrueFalse() {
    static std::random_device rd;  
    static std::mt19937 gen(rd()); 
    static std::uniform_int_distribution<> dis(0, 1); 

    return dis(gen) == 1;
}

void sendFrame(int frameNo) {
    cout << "\nSending Frame " << frameNo + 1;
}

int main() {
    int ackTime = 3;  
    int nFrames;

    cout << "Enter number of frames: ";
    cin >> nFrames;

    vector<string> frameData(nFrames);

    for(int i = 0; i < nFrames; i++) {
        cout << "Enter data of frame " << i + 1 << ": ";
        cin >> frameData[i];
    }

    // Receiver's data frame storage
    vector<string> receiverFrameData(nFrames);

    // Sending and receiving frames
    for(int i = 0; i < nFrames; i++) {
        sendFrame(i);

        bool isReceived = randomTrueFalse();

        if(!isReceived) {
            cout << "\nFrame " << i + 1 << " not received...Send Again!";
            sendFrame(i);
        }

        cout << "\nFrame " << i + 1 << " is received...";
        receiverFrameData[i] = frameData[i];
    }

    cout << "\nAll frames sent and received successfully.\n";
    
    cout << "\nData received at receivers side: ";
    for(int i = 0; i < receiverFrameData.size(); i++) {
        cout << "\nFrame " << i+1 << ": " << receiverFrameData[i]; 
    }
    cout << endl;	
	
    return 0;
}

