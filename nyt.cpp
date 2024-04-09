#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <list>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<string> dictionaryWords;
vector<string> validWords;
vector<pair<string,int>> validAnswers;
vector<string> topTen;



char allLetters[12];

void selectPuzzle();
void getWords();
void printPuzzle();
void getValidWords();
void shallowSearch();
bool deepSearch(int depth);
void getAllValidAnswers();
void getBestAnswers();
string appendWords(string priorWord);
int cntDistinct(string str);

enum Side{
    TOP,
    LEFT,
    BOTTOM,
    RIGHT,
    NONE
};

int main()
{
    getWords();
    
    selectPuzzle();
    getValidWords();
    //shallowSearch();
    if(!deepSearch(1))
        if(!deepSearch(2))
            if(!deepSearch(3))
                if(!deepSearch(4))
                    cout<<"nothin'";
                
        
    
    
    //getAllValidAnswers();
    getBestAnswers();
    return 0;
}

void selectPuzzle()
{
    int test = -1;
    bool invalid;
    bool confirmation = true;
    bool twelveLetters = false;
    string inputtedLetters;
    string confirmAnswer = "N";
    cout<<"Welcome to Letterboxed Solver!\n";
    while(confirmation)
    {
        invalid=true;
        cout<<"Enter your puzzle number, or enter 0 to enter your own puzzle!\nSelection: ";
        while(invalid)
        {
            cin>>test;
            invalid=false;
            switch (test)
            {
                case 0:  
                    while(!twelveLetters)
                    {
                        std::cout<<"\nGive letters starting on the TOP going CLOCKWISE from the LEFT CORNER :";
                        cin>>inputtedLetters;
                        if(inputtedLetters.size()==12){
                            twelveLetters=true;
                            strcpy(allLetters,inputtedLetters.c_str());
                        }
                        else{
                            cout<<"\nNot 12 letters...\n";
                        }
                    }
                    break;
                case 1:
                    strcpy(allLetters,"abxqsodrimun");
                    break;
                case 2:
                    strcpy(allLetters,"awitmepnrbks");
                    break;
                case 3:
                    strcpy(allLetters,"atkhrifeslun");
                    break;
                default:
                    invalid=true;
                    cout<<"\n\nInvalid response... please enter a valid selection\nSelection:";
            }
        }
        printPuzzle();
        cout<<"\nDoes this look right to you? (y/n): ";
        cin>>confirmAnswer;
        confirmAnswer = toupper(confirmAnswer.front());
        if(confirmAnswer=="Y") confirmation = false;
    }
    for(int i=0; i<12; i++)
    {
        allLetters[i] = toupper(allLetters[i]);
    }
}

void getWords()
{
    ifstream file("words_easy.txt");
    string str;
    while(getline(file,str)){ 
        if(str.length() < 13)
            dictionaryWords.push_back(str);
    }
}

void printPuzzle()
{
    std::cout<<"\n  "<<allLetters[0]<<" "<<allLetters[1]<<" "<<allLetters[2]<<" \n"
                            <<allLetters[11]<<"       "<<allLetters[3]<<"\n"
                            <<allLetters[10]<<"       "<<allLetters[4]<<"\n"
                            <<allLetters[9]<<"       "<<allLetters[5]<<"\n"
                <<"  "<<allLetters[8]<<" "<<allLetters[7]<<" "<<allLetters[6]<<" \n";
}

void getValidWords()
{
    bool valid;
    for(string &c_word : dictionaryWords)
    {
        valid = true;
        Side currentSide = NONE;
        for(int i=0; i<c_word.size(); i++){
              
            //top
            if((c_word[i]==allLetters[0] ||  c_word[i]==allLetters[1] || c_word[i]==allLetters[2]) && currentSide!=TOP)
            {
                currentSide=TOP;
            }
            //right
            else if((c_word[i]==allLetters[3] || c_word[i]==allLetters[4] || c_word[i]==allLetters[5]) && currentSide!=RIGHT)
            {
                currentSide=RIGHT;
            }
            //bottom
            else if((c_word[i]==allLetters[6] || c_word[i]==allLetters[7] || c_word[i]==allLetters[8]) && currentSide!=BOTTOM)
            {
                currentSide=BOTTOM;
            }
            //left
            else if((c_word[i]==allLetters[9] || c_word[i]==allLetters[10] || c_word[i]==allLetters[11]) && currentSide!=LEFT)
            {
                currentSide=LEFT;
            }
            //invalid
            else
            {
                valid = false;
                break;
            }
        }
        if(valid)
        {
            string validWord(c_word);
            validWords.push_back(validWord);
        }
    }  
}

void shallowSearch()
{
    for(string &v_word : validWords)
    {
        string w_word = appendWords(v_word);
        if(cntDistinct(w_word)!=12)
        {
            string x_word = appendWords(w_word);
            if(cntDistinct(x_word)!=12)
            {
                string y_word = appendWords(x_word);
                if(cntDistinct(y_word)!=12)
                {
                    int testSize = cntDistinct(y_word);
                    string z_word = appendWords(y_word);
                    if(cntDistinct(z_word)==12);
                    {
                        validAnswers.push_back(std::make_pair(z_word,5));
                    }
                } 
                else
                {
                    validAnswers.push_back(std::make_pair(y_word,4));
                }
            }
            else
            {
                validAnswers.push_back(std::make_pair(x_word,3));
            }
        }
        else
        {
            validAnswers.push_back(std::make_pair(w_word,2));
        }
    }
}

bool deepSearch(int depth)
{
    bool success = false;
    string twoWords;
    string threeWords;
    string fourWords;
    cout<<endl<<"Searching "<<depth<<" layers deep"<<endl;
    for(string &a_word : validWords)
    {
        if(cntDistinct(a_word)!=12)
        {
            if(depth>=2)
            {
                for(string &b_word : validWords)
                {
                    if((a_word.back()==b_word.front()) && (a_word!=b_word))
                    {
                        twoWords = a_word + " " + b_word;
                        if(cntDistinct(twoWords)!=12)
                        {
                            if(depth>=3)
                            {
                                for(string &c_word : validWords)
                                {
                                    if((b_word.back()==c_word.front()) && (c_word!=a_word) && (c_word!=b_word))
                                    {
                                        threeWords = twoWords + " " + c_word;
                                        if(cntDistinct(threeWords)!=12)
                                        {
                                            if(depth>=4)
                                            {
                                                for(string &d_word : validWords)
                                                {
                                                    if((c_word.back()==d_word.front()) && (d_word!=a_word) && (d_word!=b_word) && (d_word!=c_word))
                                                    {
                                                        fourWords = threeWords + " " + d_word;
                                                        if(cntDistinct(fourWords)==12)
                                                        {
                                                            validAnswers.push_back(std::make_pair(fourWords,4));
                                                            success=true;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        else
                                        {
                                            validAnswers.push_back(std::make_pair(threeWords,3));
                                            success=true;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            validAnswers.push_back(std::make_pair(twoWords,2));
                            success=true;
                        }
                    }
                }
            }
        }
        else
        {
            validAnswers.push_back(std::make_pair(a_word,1));
            success=true;
        }
    }
    return success;
}

bool sortByLength(const std::string& a, const std::string& b)
{
    return a.size() < b.size();
}

void getBestAnswers(int words)
{
    int shortestLength = 100;
    int shortestWords = words;
    int numOfAnswers;
    string bestAnswer;
    vector<string> shortestAnswers;

    if(shortestWords==0)
    {
        auto minIt = min_element(validAnswers.begin(), validAnswers.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.second < b.second;
            });
        if(minIt!=validAnswers.end())
            shortestWords=minIt->second;
    }
    cout<<endl<<"We found answers that are "<<shortestWords<<" words long. How many answers do you want: ";
    cin>>numOfAnswers;
    for(pair<string, int> valids : validAnswers)
    {
        if(valids.second==shortestWords)
        {
            shortestAnswers.push_back(valids.first);
        }
    }
    sort(shortestAnswers.begin(), shortestAnswers.end(), sortByLength);

    int numElements = min(numOfAnswers, static_cast<int>(shortestAnswers.size()));

    for(int i=0; i < numElements; i++)
    {
        topTen.push_back(shortestAnswers[i]);
    }

    int i=0;
    cout<<endl<<"Best answers:"<<endl;
    for(string finalAnswers : topTen)
    {
        i++;
        cout<<"#"<<i<<") "<<finalAnswers<<endl;
    }
}

void getBestAnswers()
{
    getBestAnswers(0);
}

string appendWords(string priorWord)
{
    int total = 0;
    int tempTotal;
    string bestAddition;
    string tempAddition;
    for(string &v_word : validWords)
    {
        tempTotal = 0;
        if(v_word!=priorWord)
        {
            char last = priorWord.back();
            char first = v_word.front();
            if(priorWord.back()==v_word.front())
            {
                tempAddition = priorWord + " " + v_word;
                tempTotal = cntDistinct(tempAddition);
                if(tempTotal>total)
                {
                    total = tempTotal;
                    bestAddition = tempAddition;
                }
            }
        }
    }
    int bug = 0;
    return bestAddition;
}

int cntDistinct(string str)
{
    unordered_set<char> s;
    for (int i = 0; i < str.size(); i++) {
        if(str[i]!=' ')
            s.insert(str[i]);
    }
    return s.size();
}