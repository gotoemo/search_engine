#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<map>
#include<vector>
#include"stemmer.hpp"

using namespace std;

/*Read the play and construct inverted index for all words
(the index were done by map [red-black tree] temperarily)*/
void readfile(int docnum, map<string, int>& index);

void readfile(int docnum, map<string, int>& index)
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
        struct stemmer * z = create_stemmer();
        int res = stem(z, b, n-1);
        free_stemmer(z);

        //storing in map "index"
        string stemmedword(b);
        index[stemmedword]++;
    }
}

/*Save the index into hardware so as to find words at once without reforming.
The filename is the word and contents are index of play and frequency*/
void writefile(int docnum, map<string, int>& index);

void writefile(int docnum, map<string, int>& index)
{
    string dicpath = "index/";
    for(map<string, int>::iterator i = index.begin(); i != index.end(); i++)
    {
        string path = dicpath + i->first;
        ofstream ofs;
        ofs.open(path, ios::app);
        ofs << docnum << " " << i->second << endl;
    }
}


int main()
{
    for(int i = 1; i <= 17; i++)
    {
        map<string, int> index;
        readfile(i, index);
        writefile(i, index);
    }

    return 0;
}
