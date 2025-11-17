#include<iostream>
#include <fstream>
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

void insertNode(Node*& head, const string& word, const string& hint) {
    Node* newNode=new Node(word, hint);

    if (head==NULL) {
        head=newNode;
        return;
    }

    Node* temp=head;
    while (temp->next!=NULL)
        temp=temp->next;

    temp->next=newNode;
}

int countNodes(Node* head) {
    int count=0;
    Node* temp=head;

    while (temp!=NULL) {
        count++;
        temp=temp->next;
    }

    return count;
}

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
	showInstructions();
    int levelChoice;
    cout<<"Select Difficulty Level:" << endl;
    cout<<"1. Easy" << endl;
    cout<<"2. Medium" << endl;
    cout<<"3. Hard" << endl;
    cout<<"Enter your choice (1-3):";
    cin>> levelChoice;
    cin.ignore();
    
    
string filename;

if(levelChoice== 1) 
filename = "easy.txt";
else if (levelChoice== 2) 
filename= "medium.txt";
else filename = "hard.txt";

ifstream file(filename.c_str());
if(!file) {
    cout<< "Error: Could not open " << filename << " file!\n";
    return 1;
}
	
 }

