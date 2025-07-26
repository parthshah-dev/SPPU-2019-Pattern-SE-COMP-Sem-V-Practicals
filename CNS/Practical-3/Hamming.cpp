#include<iostream>
#include<vector>
#include<string>
using namespace std;

bool isEven(string& temp){
	int numberOfOnes = 0;
	for(int i=0; i<temp.size(); i++){
		if(temp[i] == '1'){
			numberOfOnes++;
		}
	}
	return numberOfOnes % 2 == 0;
}

int main(){
	vector<string>senderArr(8);
	
	//setting intial parity bits
	senderArr[0] = "X"; //not used
	senderArr[1] = "?";
	senderArr[2] = "?";
	senderArr[4] = "?";
	
	
	string input;
	cout << "Enter 4-bits data: ";
	cin >> input;
	
	cout << "\nYou entered: " << input;
	
	int pos = 0;
	
	for(int i=1; i<senderArr.size(); i++){
		if(senderArr[i] != "?"){
			senderArr[i] = input[pos];
			pos++;
		}
	} 
	
	cout << "\nData Before Parity: ";
	for(string s : senderArr){
		cout << s << " ";
	}
	
	//Calculate parity bits
	
	//P1
	string temp = "";
	int db = 3;
	for(int i=1; i<senderArr.size(); i++){
		if(senderArr[i] != "?"){
			temp += senderArr[i]; 
			db--;
			if(db == 0){
			 break;
			}
		}
	}
	if(isEven(temp)){
		senderArr[1] = "0";
	}
	else{
		senderArr[1] = "1";
	}
	
	//P2
	temp = "";
	db = 3;
	for(int i=1; i<senderArr.size(); i++){
		if(senderArr[i] != "?"){
			temp += senderArr[i]; 
			db--;
			if(db == 0){
			 break;
			}
		}
	}
	if(isEven(temp)){
		senderArr[2] = "0";
	}
	else{
		senderArr[2] = "1";
	}
	
	//P3
	temp = "";
	db = 3;
	for(int i=1; i<senderArr.size(); i++){
		if(senderArr[i] != "?"){
			temp += senderArr[i]; 
			db--;
			if(db == 0){
			 break;
			}
		}
	}
	if(isEven(temp)){
		senderArr[4] = "0";
	}
	else{
		senderArr[4] = "1";
	}
	
	cout << "\nData After Parity: ";
	for(string s : senderArr){
		cout << s << " ";
	}
	cout << "\n";
}
