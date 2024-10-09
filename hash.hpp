typedef struct WordNode WordNode;
typedef struct Node Node;
typedef struct Hashtable Hashtable;

Hashtable *createHashTable();
void addWord(Hashtable *library, char *word);
int findword(Hashtable *library, char* word);
void stem_tolower(char* word, int k);
int getLetterIndex(char c);