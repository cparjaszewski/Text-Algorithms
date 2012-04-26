#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NP(char* pat, int m){
	int period = 1;
	for(int i=2;i<=m;i++) {
		if(pat[i] != pat[i-period]) period = i;
	}
	return period;
}
bool checkPeriod(char *pat,int m, int period){
	bool result = true;
	for(int i=period;i<=m;i++) {
		result &= (pat[i] == pat[i+period]);
	}
	return result;
}
void doTest(char * pat) {
	int tempLength = strlen(pat);
	int tempPeriod = NP(pat,tempLength);
	bool check = checkPeriod(pat,tempLength,tempPeriod);
	if (check) printf("OK\n");
	else printf("WRONG\n");
}

int main() {
	char * texts[]= {"",
	"axxaaaxxa",
	"zwezwe",
	"bbbbbXbbXbXbbbXXX",
	"AddddddXAddddXAddX",
	"AddddddXAddddXAddY"};
	int no = sizeof(texts)/sizeof(char * );
	for(int i=0;i<no;i++){
		doTest(texts[i]);
	}
	
return 0;
}
