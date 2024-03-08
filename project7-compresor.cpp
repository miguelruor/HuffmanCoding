#include "Huffman.cpp"

void compresor(const char *originalFile, const char *compressedFile){
	unsigned int totalOfChars, *freq = frequencies(originalFile, totalOfChars);
	
	if(totalOfChars==0)
		return;
	
	string *code = HuffmanCode(freq);
	
	FILE *original = fopen(originalFile, "r"), *compressed = fopen(compressedFile, "wb");
	fwrite(&totalOfChars, sizeof(int), 1, compressed);
	
	for(int i=0; i<128; i++)
		if(freq[i]>0){
			fwrite(&i, sizeof(int), 1, compressed);
			fwrite(&freq[i], sizeof(int), 1, compressed);
		}
	
	Mask myMask; 
	string s;
	int i, bit=63;
	char c;
	
	while( (c=fgetc(original)) != EOF){
		s = code[c];
		
		for(i=0; i<s.size(); i++){
			if(bit<0){
				fwrite(myMask.pointerToMask(), sizeof(long long int), 1, compressed);
				bit=63; myMask.reset();
			}
			
			if(s[i]=='0')
				bit--;
			else
				myMask.addBit(bit--);	
		}
	}
	
	fwrite(myMask.pointerToMask(), sizeof(long long int), 1, compressed);
		
	
	fclose(original); fclose(compressed);
}


int main(){
	
	char originalFile[1000], compressedFile[100];
	
	cin >> originalFile >> compressedFile;
	
	compresor(originalFile, compressedFile);
		
	return 0;
}
