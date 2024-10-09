#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<map>
#include<vector>
#include<stdlib.h>
#include"stemmer.hpp"
#include"hash.hpp"

using namespace std;

/*Read the play and construct inverted index for all words
(the index were done by map [red-black tree] temperarily)*/
void readfile(int docnum, Hashtable *library);

void readfile(int docnum, Hashtable *library)
{
	string path = "resource/" + to_string(docnum);
    ifstream ifs;
    ifs.open(path, ios::in);
    string word;
    while(ifs >> word)
    {
        while(!word.empty() && !isalpha(word.back())) word.pop_back();
        while(!word.empty() && !isalpha(word.front())) word.erase(0, 1);
        int n = word.length();
        if(n == 0) continue;

        //given stemming program("stemmer.cpp")
        char b[n+1] = {};
        for(int i = 0; i < n; i++) b[i] = word[i];
        stem_tolower(b, n);
        struct stemmer * z = create_stemmer();
        int res = stem(z, b, n-1);
        b[res+1] = 0;
        free_stemmer(z);

        //storing in map "index"
        addWord(library, b);
    }
}

/*Save the index into hardware so as to find words at once without reforming.
The filename is the word and contents are index of play and frequency*/
void writefile(int docnum, Hashtable *library);

void writefile(int docnum, Hashtable *library)
{
    string dicpath = "index/";
    for(int i = 0; i < 26; i++)
    {
        Node* ptrNode = library->hash[i];
        while(ptrNode)
        {
            string file(ptrNode->p.word);
            string path = dicpath + file;
            ofstream ofs;
            ofs.open(path, ios::app);
            ofs << docnum << " " << ptrNode->p.freq << endl;
            ptrNode = ptrNode->Next;
        }
    }
}


int main()
{
    for(int i = 1; i <= 3; i++)
    {
        Hashtable* library = createHashTable();
        readfile(i, library);
        writefile(i, library);
    }

    return 0;
}
