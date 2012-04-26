#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * FindRow(char * first, char * second, int fLen, int sLen){
	char * tempRow;
	char * mediumRow = new char[sLen];
	for(int i=0;i<sLen;i++) mediumRow[i] = 0;
	for(int i=0;i<fLen;i++){
		for(int j=0;j<sLen;j++){
			if(first[i] == second[j]) tempRow[j] = (mediumRow[j-1] + 1);
			else { 
				int a=Lnew[j-1];
				int b=L[j];
				mediumRow[j] = a>b?a:b;
			}
			for(int j=0;j<sLen;j++) mediumRow[j] = tempRow[j];
		}
	}
	return mediumRow;
}

char * Hirschberg(char * first, char * second, int fLen, int sLen, bool reverse) {
	char * LCS;
	if (sLen==0) {
		return "";
	} else if (fLen == 1) {
		bool exists = false;
		int first_index_0 = reverse?(fLen-1):0;
		for(int k = 0; k < fLen && (!exists); k++) if(first[first_index_0]==second[k]) exists = true;
		if (exists) {
			LCS = new char[2];
			LCS[0] = first[first_index_0];
			LCS[1] = '\0';
			return LCS ;
		} else {
			return "";
		}
	} else {
		int halve = (m+1)/2;
		char * LCS_lower = FindRow(x, y,    halve, sLen, false);
		char * LCS_upper = FindRow(x, y, fLen - i, sLen, true);
		// Searching for a local maximum
		k = 0;
		max = 0;
		for(int l=0;l < n;l++) {
			if (LCS_lower[l] + LCS_upper[sLen-l] > max) {
				max = LCS_lower[l] + LCS_upper[l];
				k = l;
			}
		}
		char * newOne1 = Hirschberg(first,			  second   ,        halve,        k,LCS_lower,  p);
		char * newOne2 = Hirschberg(first[halve],second[k], fLen - halve, sLen - k, LCS_upper, r);
		p = q + r;
		for(int l=0; l<r; l++) {
			C[q+l] = D[l];
		}
		char LCS = 
	}
} 


int main()
{

	
	return 0;
}

