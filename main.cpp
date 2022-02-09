#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <cctype>
#define M 101

struct Word {
	const char* word;
	const char* type;
	const char* meaning;
};
struct node {
	Word word;
	node* next;
};
void Init(node* heads[]) {
	for (int i = 0; i < M; i++) {
		heads[i] = NULL;
	}
}
node* createWord(Word w) {
	node* p = new node;
	p->word = w;
	p->next = NULL;
	return p;
}
int hashFunction(Word w) {
	int h = 0;
	for (int i = 0; i < strlen(w.word); i++) {
		h += (int)tolower(w.word[i]) * (i + 1);
	}
	return h % M;
}
int hashF(const char* word) {
	int h = 0;
	for (int i = 0; i < strlen(word); i++) {
		h += (int)tolower(word[i]) * (i + 1);
	}
	return h % M;
}
void addWord(node* heads[], Word w) {
	int h = hashFunction(w);	// Arrange word in the hash table
	node* r = heads[h];
	node* p = createWord(w);
	// Add at beginning
	if (r == NULL) {
		heads[h] = p;
	}
	// Add at last
	else {
		int compare = hashFunction(p->word);// only add once
		while (r != NULL) {
			if (compare == h) {// if the word already had, break the loop
				break;
			}
			else {	// if not, continue to go to the last node
				r = r->next;
			}
		}
		if (compare != h) {// recheck whether the word is repeated
			r->next = p;	// Add at last
		}
	}
}
void updateWord(node* heads[], Word w) {
	int h = hashFunction(w);
	node* r = heads[h];
	if (r != NULL) {
		int compare = hashFunction(r->word);
		while (r != NULL) {
			if (compare == h) {
				r->word = w;
				break;
			}
			else {	
				r = r->next;
			}
		}
	}
}
void display(node* heads[]) {
	for (int i = 0; i < M; i++) {
		if (heads[i] != NULL) {	//Only print bucket which has value
			printf("===== BUCKET %d =====\n", i);
			node* p = heads[i];
			while (p != NULL) {
				printf("%s (%s): %s",p->word.word,p->word.type,p->word.meaning);
				p = p->next;
			}
			printf("\n");
		}
	}
}
void searchWord(node* heads[],const char* word) {
	int h = hashF(word);
	node* r = heads[h];
	if (r != NULL) {
		int compare = hashF(word);
		while (r != NULL) {
			if (compare == h) {
				printf("%s (%s): %s",r->word.word,r->word.type, r->word.meaning);
				break;
			}
		}
	}
}
void removeWord(node* heads[], char* word) {
	int h = hashF(word);
	node* r = heads[h];
	node* prev = NULL;
	while (r != NULL) {
		if (strcmp(word, r->word.word) == 0) {
			if (prev == NULL) {
				heads[h] = r->next;
			}
			else {
				prev->next = r->next;
				r->next = NULL;
				delete(r);
				break;
			}
		}
		prev = r;
		r = r->next;
	}
}
int main() {
	Word w1 = { "Student","N","Hoc sinh" };
	Word w2 = { "Teacher","N","Giao vien" };
	Word w3 = { "Worker","N","Cong nhan" };
	node* heads[M];
	Init(heads);
	addWord(heads, w1);
	addWord(heads, w2);
	addWord(heads, w3);
	//display(heads);
	printf("\t++++++++++++++++++++++++++++++++\n");
	printf("\t+                              +\n");
	printf("\t+ WELCOME TO LONG'S DICTIONARY +\n");
	printf("\t+                              +\n");
	printf("\t++++++++++++++++++++++++++++++++\n");
	printf("\n");
	char a[10];
	printf("Search Word: ");
	scanf("%s", a);
	searchWord(heads,(const char*)a);
	return 0;
}