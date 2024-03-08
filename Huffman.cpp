#include "mySTL.cpp"
#include <string>
#include <cstdio>

struct dupla{
	char c;
	unsigned int freq;
	
	dupla(char _c=0, unsigned int _freq=0){
		c=_c; freq=_freq;
	}
	
	bool operator>(const dupla &right){
		return freq > right.freq;
	}
};

typedef tree<dupla> HuffmanNode;

HuffmanNode* Huffman(unsigned int *freq){
	priority_queue<HuffmanNode> PQ(128);
	HuffmanNode *aux, *aux2, *root;
	
	for(int i=0; i<=127; i++)
		if(freq[i]>0){
			aux = new HuffmanNode(dupla(i, freq[i]));
			PQ.insert(*aux);
		}
	
	while(PQ.size()>1){
		root = new HuffmanNode; aux = new HuffmanNode; aux2 = new HuffmanNode;
		*aux = PQ.delMin(); *aux2 = PQ.delMin();
		root->item = dupla(0, aux->item.freq + aux2->item.freq);
		root->join(aux, aux2);
		PQ.insert(*root);
	}
	
	*root = PQ.delMin();
	
	return root;
}

	unsigned int* frequencies(const char *filename, unsigned int &totalOfChars){
	FILE* file = fopen(filename, "r");
	unsigned int *freq = new unsigned int[128];
	
	for(int i=0; i<128; i++)
		freq[i]=0;
	
	totalOfChars=0;
	
	while(!feof(file))
		if(freq[fgetc(file)]++ == 0)
			totalOfChars++;
	
	fclose(file);
	
	return freq;
}

void DFS_Code(HuffmanNode *pt, string *code){ 
	static string s;
	
	if(pt->left==NULL){ //Si pt es nodo hoja (las hojas en el árbol creado por la función Huffman son las únicas que tienen hijos apuntando a NULL), entonces:
		code[pt->item.c] = s; 
		return;
	}
	
	s.push_back('0'); DFS_Code(pt->left, code); s.erase(s.size()-1, s.size());
	s.push_back('1'); DFS_Code(pt->right, code); s.erase(s.size()-1, s.size());
}

string* HuffmanCode(unsigned int *freq){
	HuffmanNode *root = Huffman(freq);
	
	string *code = new string[128]; 
	DFS_Code(root, code);
	
	return code;
}

