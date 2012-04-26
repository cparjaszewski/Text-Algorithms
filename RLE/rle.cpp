#include <stdio.h>

struct rChar {
	int len;
	char character;
	bool end;
	rChar(int l, char c, bool e=false) : len(l),character(c), end(e) {}
};

int GetRCharLength(const rChar * rc) {
	int result = 0;
	while (!rc[result++].end );
	return result;
}
inline int getMax(const int a,const int b) {
	return a > b? a : b;
}

inline int getMin(const int a,const int b) {
	return a < b? a : b;
}


const rChar X[] = {rChar(4,'a'), rChar(3,'b'), rChar(2,'c'), rChar(4,'a'), rChar(6,'b'), rChar(3,'a'),rChar(0,0,true)};
const rChar Y[] = {rChar(2,'b'), rChar(4,'c'), rChar(2,'a'), rChar(7,'b'), rChar(4,'a'), rChar(3,'c'),rChar(0,0,true)};

void ForcePathUpdate(int i, int j, int k, int l, int ** M) {
	// assert (X[_i].character == Y[_j].character)	
	do { 
		// get the minimum | the sizes are not equal
		if (X[i].len < Y[i].len) 
		// horizontal
		{
			int lasti = i;
			// Search next block
			while(!(X[++i].character == Y[j].character) && (i<k));
			if (i ==k) break;
			M[i+1][j+1] = getMax(M[i+1][j+1], (M[lasti+1][j+1] + X[lasti].len));
		} else 
		// vertical
		{
			int lastj = j;
			while(!(X[i].character == Y[++j].character) && (j<l));
			if (j ==l) break;
			M[i+1][j+1] = getMax(M[i+1][j+1],(M[i+1][lastj+1] + Y[lastj].len)) ;
		}
	} 
	while (!(X[i].len == Y[j].len) && (i==k) &&  (j==l)) ;
	// There is no corner exit and none of strings is already finished
	
}


int main () {
	int k = GetRCharLength(X);
	int l = GetRCharLength(Y);
	int ** M = new int*[k];
	for(int i=0;i<=k;i++) {
		M[i] = new int[l+1];
		for(int j=0;j<=l;j++) M[i][j]=0;
	}
	for(int i=0;i<k;i++) {
		for(int j=0;j<l;j++) {
			// LIGHT
			if(X[j].character != Y[i].character) {
				M[i+1][j+1] = getMax(M[i][j+1],M[i+1][j]);
			}
			// DARK
			else {
				int d = getMin(X[i].len,Y[j].len);
				// Get the maximum of four values
				M[i+1][j+1] = getMax(getMax(M[i][j]+d,M[i+1][j+1]),getMax(M[i][j+1],M[i+1][j]));
				ForcePathUpdate(i,j,k,l,M);			
			}
		}
	}
		


	
	return 0;
}
