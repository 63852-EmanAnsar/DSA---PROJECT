#include<iostream>
using namespace std;

struct Node{
	string word;
    string hint;
    Node* next;
    
    Node(string wo, string hi){
    word=wo;
    hint=hi;
    next=NULL;
	}
};

void showInstructions() {
    cout<<"======================================="<<endl;
    cout<<"         WELCOME TO THE GAME!          "<<endl;
    cout<<"======================================="<<endl;
    cout<<"Instructions:"<<endl;
    cout<<"1. You will be asked questions one by one."<<endl;
    cout<<"2. Type your answer and press Enter."<<endl;
    cout<<"3. To exit the current level, type 'exit'."<<endl;
    cout<<"4. To quit the entire game, type 'quit'."<<endl;
    cout<<"5. Your final score will be shown at the end."<<endl;
    cout<<"======================================="<<endl;
}

int main(){
    int levelChoice;
    cout<<"Select Difficulty Level:" << endl;
    cout<<"1. Easy" << endl;
    cout<<"2. Medium" << endl;
    cout<<"3. Hard" << endl;
    cout<<"Enter your choice (1-3): ";
    cin>> levelChoice;
    cin.ignore();

	showInstructions();
    return 0;

	
}
