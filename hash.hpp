struct WordNode
{
   char word[21];
   int freq;
};
typedef struct WordNode WordNode;
struct Node
{
   WordNode p;
   struct Node *Next;
};
typedef struct Node Node;
struct Hashtable
{
   Node *hash[26];
};
typedef struct Hashtable Hashtable;

Hashtable *createHashTable();
void addWord(Hashtable *library, char *word);
int findword(Hashtable *library, char* word);
void stem_tolower(char* word, int length);
int getLetterIndex(char c);