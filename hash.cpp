#include<stdlib.h>
#include<string.h>
#include"hash.hpp"

Hashtable *createHashTable()
{
   Hashtable *newTable = (Hashtable *)malloc(sizeof(Hashtable));

   for (int i = 0; i < 26; i++)
   {
      newTable->hash[i] = NULL; // 将每个指针初始化为 NULL
   }

   return newTable;
}
void addWord(Hashtable *library, char *word)//add word in hash table, count is used to give each word a index
{
   int index = getLetterIndex(word[0]);
   if (index == -1)
   {
      return;
   }

   Node *newNode = (Node *)malloc(sizeof(Node));
   newNode->Next = NULL;
   newNode->p.freq=0;
   strcpy(newNode->p.word, word);

   // 检查是否已经存在于链表中
   Node *current = library->hash[index];
   Node *save = NULL;
   while (current != NULL)
   {
      if (strcmp(current->p.word, word) == 0)//already in the hashtable
      {
         current->p.freq++;
         free(newNode); //free the node
         return;
      }
      save = current;
      current = current->Next;
   }
   if (save == NULL)
   {
      library->hash[index] = newNode;
      return;
   }
   else
   {
      save->Next = newNode;
      return;
   }
}
int findword(Hashtable *library, char* word)//find word in hashtable
{
   int index = getLetterIndex(word[0]);
   if (index == -1)
   {
      return -1;
   }
   Node *startNode = (Node *)malloc(sizeof(Node));
   startNode=library->hash[index];
   while(startNode!=NULL)
   {
      if(strcmp(startNode->p.word,word)==0)
      {
         startNode->p.freq++;
         return startNode->p.freq;
      }
      else
      {
         startNode=startNode->Next;
      }
   }
   return -1;
}
void stem_tolower(char* word, int length)//Convert uppercase letters to lowercase letters.
{
   for(int i=0;i<length;i++)
   {
      if(word[i]>='A'&&word[i]<='Z')
      {
         word[i]=word[i]-'A'+'a';
      }
   }
}
int getLetterIndex(char c)//get the index for each word
{
   if (c >= 'a' && c <= 'z')
   {
      return c - 'a';
   }
   return -1; // 其他字符
}