#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char firstWord [] = "ABCDEFGHIJKLMNOP";
const char secondWord [] = "BFEBCDFEBCHGBCBE";



void HuntSzymanski() {
	int m = strlen(firstWord);
	int n = strlen(secondWord);
	int * tresh = new int[m];
	int ** matchList = new int*[m];
	int *link = new int[n];
	int temp;
	
	for(int i=0;i<m;i++) {
		temp = 0;
		tresh[i] = n + 1;
		char currentChar = firstWord[i];
		for(int j=0;j<n;j++) if(currentChar == secondWord[j]) temp++;
		matchList[i] = new int[n];
		temp = 0;
		for(int j=n;j>0;j--) if(currentChar == secondWord[j]) matchList[i][temp++] = j;
	}
	tresh[0] = 0;
	link[0] = -1;
}

int main()
{

	
	return 0;
}

