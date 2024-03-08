#include "Huffman.cpp"

void descompresor(const char *compressedFile, const char *originalFile){
	unsigned int totalOfChars, *freq = new unsigned int[128], c; 
	
	for(int i=0; i<128; i++)
		freq[i]=0;
	
	long long unsigned int allChars=0;
	
	FILE *compressed=fopen(compressedFile, "rb"), *original=fopen(originalFile, "w");
	fread(&totalOfChars, sizeof(int), 1, compressed);
	
	if(totalOfChars==0)
		return;
	
	for(int i=0; i<totalOfChars; i++){
		fread(&c, sizeof(int), 1, compressed);
		fread(&freq[c], sizeof(int), 1, compressed);
		allChars+=freq[c];
	}
	
	HuffmanNode *root = Huffman(freq), *aux=root;
	
	Mask myMask;
	
	for(int bit=-1, count=0; count<allChars; bit--){
		if(aux->left==NULL){ //Si aux es nodo hoja, entonces:
			fwrite(&(aux->item.c), sizeof(char), 1, original);
			count++;
			aux=root;
		}
		
		if(count==allChars)
			break;
		
		if(bit<0){
			bit=63;
			fread(myMask.pointerToMask(), sizeof(long long int), 1, compressed);
		}
		
		if(myMask.ask(bit))
			aux=aux->right;
		else
			aux=aux->left;
	}
	
	fclose(compressed); fclose(original);
}


int main(){
	
	char originalFile[1000], compressedFile[100];
	
	cin >> originalFile >> compressedFile;
	
	descompresor(originalFile, compressedFile);
	
	return 0;
}
