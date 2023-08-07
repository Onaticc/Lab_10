#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// grab the size of the alphabet 
#define SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode* children[SIZE];
    int count;
};

// Trie structure
struct Trie {
    struct TrieNode* root;
};

//prototype functions 
struct TrieNode* createTrieNode();
void insert(struct Trie* pTrie, char* word);
int numberOfOccurrences(struct Trie* pTrie, char* word);
struct TrieNode* deallocateTrieNode(struct TrieNode* pNode);
struct Trie* deallocateTrie(struct Trie* pTrie);
struct Trie* createTrie();
int readDictionary(char* filename, char** pInWords);
void freeDictionary(struct Trie* tree);
//end function prototypes 

//call function trienode
// Creates a new Trie node
struct TrieNode* createTrieNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < SIZE; i++) {
        newNode->children[i] = NULL;
    }
    newNode->count = 0;
    return newNode;
}//end function call 

//call function insert
//Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word) {
    struct TrieNode* curr = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = createTrieNode();
        }
        curr = curr->children[index];
    }
    curr->count++;
}//end function call insert

//call function occurences 
//Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie* pTrie, char* word) {
    struct TrieNode* curr = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}//end function call

//call function trienode 
//Deallocate the trie node
struct TrieNode* deallocateTrieNode(struct TrieNode* pNode) {
    if (pNode == NULL) {
        return NULL;
    }
    for (int i = 0; i < SIZE; i++) {
        pNode->children[i] = deallocateTrieNode(pNode->children[i]);
    }
    free(pNode);
    return NULL;
}//end function call 

//call function deallocate 
//Deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    pTrie->root = deallocateTrieNode(pTrie->root);
    free(pTrie);
    return NULL;
}//end function call 

//call function trie
//Initializes a trie structure
struct Trie* createTrie() {
    struct Trie* pTrie = (struct Trie*)malloc(sizeof(struct Trie));
    pTrie->root = createTrieNode();
    return pTrie;
}//end function call 

//call function readDictionary 
// Reads the number of words in the dictionary and stores them in the array pInWords
int readDictionary(char* filename, char** pInWords) {
    FILE* fp;
    int numWords = 0;
    char word[256];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fscanf(fp, "%d", &numWords); // Read the number of words from the file
    for (int i = 0; i < numWords; ++i) {
        fscanf(fp, "%s", word);
        pInWords[i] = strdup(word);
    }
    fclose(fp);
    return numWords;
}

// Just frees all the memory pointed to by tree (directly and indirectly)
void freeDictionary(struct Trie* tree) {
    tree->root = deallocateTrieNode(tree->root);
    free(tree);
}//end function call 

//call main 
int main(void) {
    char* inWords[256];
    int numWords = readDictionary("dictionary.txt", inWords);

    // Read the dictionary words
    printf("%d\n", numWords);
    for (int i = 0; i < numWords; ++i)
        printf("%s\n", inWords[i]);

    struct Trie* pTrie = createTrie();

    // Insert dictionary words into the trie
    for (int i = 0; i < numWords; i++)
        insert(pTrie, inWords[i]);

    // Test the occurrences of some words
    char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
    for (int i = 0; i < 5; i++)
        printf("\t%s:%d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));

    pTrie = deallocateTrie(pTrie);

    if (pTrie != NULL)
        printf("There is an error in this program\n");

    // Deallocate the memory for the dictionary words
    for (int i = 0; i < numWords; ++i)
        free(inWords[i]);

    return 0;
}//end main call 
