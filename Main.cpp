//
// Created by T_Dooky on 2/18/2016 AD.
//

#include "ReadingFileLib.h"
#include <iostream>  // I/O
#include <fstream>   // file I/O
#include <vector>
#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> hires_clock;
#define NOW() std::chrono::high_resolution_clock::now()
#define DIFF(start) std::chrono::duration_cast<std::chrono::microseconds>(NOW() - start).count()

using namespace std;

class Node {
public:
    Node() { mContent = ' '; mMarker = false; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    bool mMarker;
    vector<Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string s);
    bool searchWord(string s);
    void deleteWord(string s);
private:
    Node* root;
};

Node* Node::findChild(char c)
{
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}

void Trie::addWord(string s)
{
    Node* current = root;

    if ( s.length() == 0 )
    {
        current->setWordMarker(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}


bool Trie::searchWord(string s)
{
    Node* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( current->wordMarker() )
            return true;
        else
            return false;
    }

    return false;
}

struct InWord{
    string id;
    string text;
};

int main(int argc, char *argv[]){

    //unused value
    string idField;
    string wordField;

    ifstream fp(argv[1], ios::binary);

    ReadingFile::MyReadingFile reader;

    vector<ReadingFile::MyReadingFile::SYLLABLE_DATA_RECORD> results = reader.readFile(fp);

    vector<InWord> words;
    InWord tempWord;
    ifstream file("textInput1000W.txt");
    int totalSearch = 0;

    while (file >> idField >> tempWord.id >> wordField >> tempWord.text)
    {
    //    cout << tempWord.id << "   " << tempWord.text << endl;
       words.push_back(tempWord);
        totalSearch++;
    }

    long total = reader.recordCounting(results);

    Trie* trie = new Trie();
    for(int i = 0; i < total; i++){
        ReadingFile::MyReadingFile::SYLLABLE_DATA_RECORD tmp = results.at(i);
        trie->addWord(tmp.szText);
       // printf(tmp.szText);
    }

    //declare clock
    hires_clock timer;

    int foundCount = 0;
    int notCount = 0;

    timer = NOW();
    for(int i = 0; i < totalSearch; i++){
        InWord sWord = words.at(i);
        if( trie->searchWord(sWord.text)){
           cout << "Found ID: " << sWord.id << " " << sWord.text << endl;
            foundCount++;
        }
        else{
            cout << "Not Found "<< sWord.text << endl;
            notCount++;
        }
    }
    cout << "Running takes " << DIFF(timer) << " microsec" << endl;

    cout << "Found total: " << foundCount << " Not Found: " << notCount << endl;

    return 0;
}

