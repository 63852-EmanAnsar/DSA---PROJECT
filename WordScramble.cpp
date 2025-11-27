#include<iostream>
#include <fstream>
#include <string>
#include <cstdlib>   
#include <ctime> 
#include<cctype>
#include <queue>

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

Node* getNode(Node* head, int index) {
    Node* temp=head;
    int i=0;

    while (temp!=NULL && i<index) {
        temp=temp->next;
        i++;
    }

    return temp;
}

void giveHint(Node* current, int &hintCount, int &levelHintCount) {
	
    if (levelHintCount>=2) {
        cout<<"No hints left for this level!\n";
        return;
    }
    
    if (hintCount==0) {
        cout<<"Hint 1: Starts with '"<<current->word[0];
        hintCount++;
        levelHintCount++;
        return;
    }
    
    if (hintCount==1) {
        cout<<"Hint 2: Ends with '"<<current->word[current->word.length()-1]<<"'\n";
        hintCount++;
        levelHintCount++;
        return;
    }
    
}


string scrambleWord(string word) {
    int n=word.length();
    for (int i= n-1; i>0; i--) {
        int j=rand() % (i + 1);
        swap(word[i], word[j]);
    }
    return word;
}

string toLowerStr(string s) {
    for (int i= 0; i<s.length(); i++) {
        s[i]=tolower(s[i]);
    }
    return s;
}


string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
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
    Node* head = NULL;
    queue<string> correctGuesses;

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

   string word, hint;
   while(file>> word) {
   getline(file, hint);
   if(hint.size()>0 && hint[0]==' ')
   hint.erase(0, 1);
   insertNode(head, word, hint);
}

   file.close();
   srand(time(0));
   int totalWords = countNodes(head);

   int score=0;
   int wordsPlayed=0;
   const int MAX_WORDS=5;
   bool exitGame= false;

   while (wordsPlayed < MAX_WORDS && !exitGame)

{
   int randomIndex= rand() % totalWords;
   Node* current = getNode(head, randomIndex);
   string scrambled = scrambleWord(current->word);

   string guess;

   int attempts=3;
   int hintCount=0;
   int levelHintCount = 0; 

   cout<<"\nScrambled word: "<<scrambled<<endl;
   cout<<"Hint: "<<current->hint<<endl;}
 while (attempts > 0)
{
    cout<<"\nYour Guess (hint/skip/exit): ";
    getline(cin, guess);

    guess=trim(guess);

    string guessLower=toLowerStr(guess);
    string wordLower=toLowerStr(current->word);

    if (guessLower=="exit") {
        exitGame=true;
        break;
    }

    if (guessLower=="hint") {
        giveHint(current, hintCount, levelHintCount);
        continue;
    }

    if (guessLower=="skip") {
        cout<<"Word skipped! Correct word: "<<current->word<<endl;
        break;
    }

    if (guessLower==wordLower) {
        cout<<"Correct! Well done!\n";
        score++;
        correctGuesses.push(current->word);
        break;
    }
    else {
        attempts--;
        if (attempts>0)
            cout<<"Wrong! Attempts left: "<<attempts<<endl;
        else
            cout<<"Out of attempts! Correct word: "<<current->word<<endl;
    }
}


