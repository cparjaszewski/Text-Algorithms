#include <iostream>
#include <vector>
using namespace std;

/*
pM (pn) - is the p-long version of LCS algorithm
*/

struct mList {
	int value;
	bool isEmpty;
	mList * next;
	mList() {
		isEmpty = true;
	}
	
};

struct pmData {
	// first & second word
	char *x,*y;

	// auxiliary table
	int *C;

	// auxiliary guard
	int p;
};

struct auxData {
	// Table of matches list
	mList * matchList;

	// Auxiliary Array
	int ** M;
};

mList * getMatches(char * templateChar, char searchedChar) {
	int k = strlen(templateChar);
	mList * matches = new mList;
	mList * temp = matches;
	
	for(int i = 0; i < k; i++) {
		if (templateChar[i] == searchedChar) {
			temp->value = i;
			temp->next = new mList;
			temp = temp->next;
		}
	}
	matches->isEmpty = false;

	return matches;
}

pmData initData() {
	pmData pm;
	pm.x = "abcdababababcbabcbbababbcbabcbabcbbabbadbbcbabcbabdbcbdbdbbdbcbcbbdbdbdbabdabacacdbdbc";
	pm.y = "abdbcbdbdbdbdbdbcbcbbbdbcbdbdbdbdbdbcbcbdbcbdbdbdbdbdbcbcbdbcbdbdbdbdbdbcbccbcaaaaaaaaacabacbabacbacabcabcbacbdbdbbdbdbbdbcbbcbbcbcbabbabbdbc";

	return pm;
}

auxData initAuxData(pmData pm) {
	auxData * ad = new auxData;
	// getDimensions
	int m = strlen(pm.x);
	int n = strlen(pm.y);

	// Init Match List
	ad->matchList = new mList[500];
	for(int i = 0; i < m ; i++) {
		if (ad->matchList[pm.x[i]].isEmpty) {
			ad->matchList[pm.x[i]] = * getMatches(pm.y,pm.x[i]);
		}
	}

	// Init Aux Array
	ad->M = new int *[n];

	for (int i=0;i<n;i++){
		ad->M[i] = new int[m];
	}
	for(int i=0;i<m;i++) {
		ad->M[0][i] = 0;
	}
	return * ad;
}

int getMinFromMatchList(auxData ad, pmData pm, int i, int low) {
	// t <- min { j \in MATCHLIST(x_i) | j > low}
	int n = strlen(pm.y);
	int min;
	mList list = ad.matchList[pm.x[i]];
	while (list.value > -1) {
		if (list.value > low) {
			min = list.value;
			break;
		}
		list = *list.next;
	}
	return min;
}

// LABEL FUNCTION
void recover(int *k, pmData *pm, auxData *ad) {
	int p = (*k-1);
	*k = p;
	int m = strlen(pm->x);
	for (int i = m;i>0;i--) {
		if (ad->M[*k][i] > 0 ) {
			pm->C[*k] = pm->x[i];
			*k--;
		}
	}
}

// MAIN FUNCTION
int main() {
	pmData pm = initData();
	int m = strlen(pm.x);
	int n = strlen(pm.y);
	auxData ad = initAuxData(pm);

	int t=0, prev,low,high,first = 0;
	for (int k=1; k <n;k++) { 
		prev = first;
		low = ad.M[k-1][prev];
		high = n+1;
		for(int i = (prev+1);i<m;i++) {
			t = getMinFromMatchList(ad, pm, i, low);  // t <- min { j \in MATCHLIST(x_i) | j > low}
			if (t < high) {
				high = t;
				ad.M[k][i] = high;
			} else {
				ad.M[k][i] = 0;
			}
			if ((ad.M[k][i] > 0) && (first == prev)) {
				first = i;
			}
			if (ad.M[k-1][i] > 0) {
				low = ad.M[k-1][i];
			}
		}
		// M[k,0:m] contains the set of k-minimal points
		if (first == prev) {
			recover(&k,&pm,&ad);
		}
	}

	return 0;
}