//header files
#include<iostream> 
#include <fstream>
#include <string>
#include <cstdlib>   
#include <ctime> 
#include<cctype>
#include <queue>

using namespace std;

//Linked list node
struct Node{ 
	 string word;
     string hint;
     Node* next;
   
     //Constructor for new node 
     Node(string wo, string hi){     
     word=wo;
     hint=hi;
     next=NULL;
	}
};

//Linked list functions

//Function for new node insertion
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

//Function to count no. of nodes
int countNodes(Node* head) {           
     int count=0;
     Node* temp=head;

     while (temp!=NULL) {
        count++;
        temp=temp->next;
     }

     return count;
}

//Function to count no. of nodes
Node* getNode(Node* head, int index) {  
     Node* temp=head;
     int i=0;

     while (temp!=NULL && i<index) {
        temp=temp->next;
        i++;
     }
     return temp;
}

//remove the current node so that it wont appear again in the level
void removeNode(Node*& head, Node* toDelete) {
    if (head==NULL || toDelete==NULL) 
	return;

    if (head==toDelete) {
        head=head->next;
        delete toDelete;
        return;
    }

    Node* temp=head;
    while (temp->next!=NULL && temp->next!=toDelete) {
    temp=temp->next;
    }

    if (temp->next==toDelete) {
    temp->next=toDelete->next;
    delete toDelete;
    }
}

//Game logic funtions
void giveHint(Node* current, int &hintCount, int &levelHintCount) { 

     //Function for hints
     if (levelHintCount>=2) {
        cout<<"No hints left for this word!\n";
        return;
     }
    
     if (hintCount==0) {
        cout<<"Hint 1: The word starts with '"<<current->word[0]<<"'\n";
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

//Function for scrambling words randomly
string scrambleWord(string word) { 
     int n=word.length();
     for (int i= n-1; i>0; i--) {
        int j=rand() % (i + 1);
        swap(word[i], word[j]);
      }
     return word;
     }

//Function to convert string to lowercase
string toLowerStr(string s) { 
     for (int i= 0; i<s.length(); i++) {
        s[i]=tolower(s[i]);
      }
     return s;
     }

//Function for trimming whitespaces
string trim(const string& s) {  
     size_t start = s.find_first_not_of(" \t\n\r");
     size_t end = s.find_last_not_of(" \t\n\r");
     if (start == string::npos) return "";
     return s.substr(start, end - start + 1);
     }

//Game instructions function
void showInstructions() {
	
     cout<<"=============================================="<<endl;
     cout<<"      WELCOME TO THE WORD SCRAMBLE GAME!          "<<endl;
     cout<<"=============================================="<<endl;
     cout<<"Instructions:"<<endl;
     cout<<"1. You will be asked to scramble words and select level."<<endl;
     cout<<"2. There will be five rounds in each level."<<endl;
     cout<<"3. Type your answer and press Enter."<<endl;
     cout<<"4. If you want hint type 'hint.'"<<endl;
     cout<<"5. You will be given 2 hints for each word."<<endl;
     cout<<"6. If you want to skip word type 'skip'."<<endl;
     cout<<"7. Skipped word will be shown correctly."<<endl;
     cout<<"8. If you want to exit type 'exit'"<<endl;
     cout<<"9. After each level playAgain will be shown."<<endl;
     cout<<"10.Your final score and corrected words will be shown at the end."<<endl;
     cout<<"======================================="<<endl;
}

//Main game execution 
int main(){
	
	 srand(time(0));
	 char selectLevelAgain='y';

	 showInstructions();

     //Main game loop
	 while( selectLevelAgain=='y'|| selectLevelAgain=='Y') {   
     Node* head = NULL;
     queue<string> correctGuesses;
      
     //Selection of levels
     int levelChoice;
     cout<<"Select Difficulty Level:" << endl;
     cout<<"1. Easy" << endl;
     cout<<"2. Medium" << endl;
     cout<<"3. Hard" << endl;
     do{
     cout<<"Enter your choice (1-3):";
     cin>> levelChoice;
     if (levelChoice<1 || levelChoice>3) {
     cout<<"Invalid choice! Please enter 1,2,or 3.\n";
     }
     } 
	 while(levelChoice<1 || levelChoice>3);
     cin.ignore();
    
     string filename;

     //Filename based on level selected
     if(levelChoice== 1)             
     filename = "easy.txt";
    
     else if (levelChoice== 2) 
     filename= "medium.txt";
    
     else filename = "hard.txt";
    
     //File Input/Output
     ifstream file(filename.c_str()); 
     if(!file) {
     cout<< "Error: Could not open " << filename << " file!\n";
     return 1;
     }
     //Reading hints and words
     string word, hint; 
    
     while(file>> word) {
     getline(file, hint);
    
     if(hint.size()>0 && hint[0]==' ')
     hint.erase(0, 1);
     insertNode(head, word, hint);
     }

     file.close();
  
     int totalWords = countNodes(head);
       
	 
     if (totalWords==0) {
     cout<<"\nNo words found in the selected file!"<<endl;
     cout<<"Try again later.\n";
     break; 
}
   
     //Initialization of variables of game
     int score=0;  
     int wordsPlayed=0;
     const int MAX_WORDS=5;
     bool exitGame= false;
    
     
	 while (wordsPlayed < MAX_WORDS && !exitGame)
 { 
     //Selecting random word index
     int randomIndex= rand() % totalWords;  
     Node* current = getNode(head, randomIndex);
     string scrambled = scrambleWord(current->word);

     string guess;
   
     //No. of attempts
     int attempts=3;  
     int hintCount=0;
     int levelHintCount = 0; 

     cout<<"\nScrambled word: "<<scrambled<<endl;
     cout<<"Hint: "<<current->hint<<endl;
   
     //Inner loop for guessing attempts
     while (attempts > 0)              
 {
     cout<<"\nYour Guess (hint/skip/exit): ";
     getline(cin, guess);
     guess=trim(guess);
     
    if (guess=="") {
    cout<<"You didn't enter anything. Please type something.\n";
    continue;  
}

     string guessLower=toLowerStr(guess);     
     string wordLower=toLowerStr(current->word);

     if  (guessLower=="exit") {        //Exit command
        exitGame=true;
        break;
     }

     if  (guessLower=="hint") {        //Hint command
        giveHint(current, hintCount, levelHintCount);
        continue;
     }

     if  (guessLower=="skip") {        //skip command
        cout<<"Word skipped! Correct word: "<<current->word<<endl;
        break;
     }

     if  (guessLower==wordLower) {     //Checking correct guess
        cout<<"Correct! Well done!\n";
        score++;
        
        //Storing correctly guessed words in queue
        correctGuesses.push(current->word);    
        break;
     }
     else {   
    
        //Handles wrong guess
        attempts--;
        if (attempts>0)
            cout<<"Wrong! Attempts left: "<<attempts<<endl;
        else
            cout<<"Out of attempts! Correct word: "<<current->word<<endl;
     }
 }
   
      wordsPlayed++ ;
      removeNode(head,current);
      totalWords--;

 }     //End of game round loop

     //Game ending summary
     cout<<"\n======================================\n";
     cout<<"       GAME OVER - FINAL SCORE        \n";
     cout<<"======================================\n";
     cout<<"Your final score: "<<score<<endl;

     //Displaying all words correctly
     cout<<"\nWords You Guessed Correctly:\n";
        while (!correctGuesses.empty()) {
            cout<<"- "<<correctGuesses.front()<<endl;
            correctGuesses.pop();
         }
        
         //Asking user to play another level
         if (!exitGame) {   
            cout<<"\nPlay again?(y/n): ";
            cin>>selectLevelAgain;
            cin.ignore();
         } else {
            selectLevelAgain='n';
         }
        
     //Cleaning dynamically allocated linked list nodes        
     Node* temp;     
        while (head!=NULL) {
            temp=head;
            head=head->next;
            delete temp;

         }
}
     //Final goodbye message
     cout<<"\nGoodbye! Game ending, thanks for playing!\n";  
     
}
