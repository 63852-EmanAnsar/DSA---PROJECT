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

int main(){
	  int levelChoice;
    cout<<"Select Difficulty Level:" << endl;
    cout<<"1. Easy" << endl;
    cout<<"2. Medium" << endl;
    cout<<"3. Hard" << endl;
    cout<<"Enter your choice (1-3): ";
    cin>> levelChoice;
    cin.ignore();
	
}
