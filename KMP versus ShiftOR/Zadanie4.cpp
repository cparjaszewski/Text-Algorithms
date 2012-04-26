// Zadanie4.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#ifdef _PRINTDEBUG_
const bool printDebug = true;
#else
const bool printDebug = false;
#endif

const int testSize = 250;
const int repeatTest = 12;
const int wordSize = 1000000;
const int templateSize = 30;
const int dictionarySize = 2;


/*inline static char GetCharNumber(char c){
	return c - 'A';
}
*/
inline static char GetChar(int r){
	return 'A' + r;
}

inline static char GenerateChar() {
	int r = rand() % dictionarySize;
	return GetChar(r);
};

inline static void printTable(int * table, const char * text, int size) {
	for(int i=0;i<size;i++){
		printf("%d",table[i]);
	}
	printf(" for text ");
	int testSize = strlen(text);
	for(int i=0;i<testSize;i++){
		printf("%c",text[i]);
	}
	printf("\n");
};

inline static void printByteArray(const unsigned int byteArray, short size) {
	unsigned int neg = ~byteArray;
	unsigned int i = 1 << size;
	while(i > 0){
		if(neg & i) {
			printf("1");
		} else {
			printf("0");
		}
		i /= 2;
	}
	printf("\n");
};

class Source {
	private:
		char sourceTexts[testSize][wordSize+1];
		char searchedTexts[testSize][templateSize+1];

		void Init() {
			// Start main random-source-texts initialization
			for(int i=0; i < testSize; i++) {
				for(int j=0; j < wordSize; j++) {
					this->sourceTexts[i][j] = GenerateChar();
					if (j < templateSize) {
						this->searchedTexts[i][j] = GenerateChar();
					} 
				}			
			}
		}

	public:
		const char * GetSourceText(int index) {
			return this->sourceTexts[index];
		}
		const char * GetSearchedText(int index) {
			return this->searchedTexts[index];
		}
		void Reset() {		
			this->Init();
		}

		Source() {
			// Initialize the char matrix
			// Fill source and searched text matriex
			for(int i=0; i < testSize; i++) {
					this->searchedTexts[i][templateSize] = '\0';
					this->sourceTexts[i][wordSize] = '\0';
			 }

			this->Init();
		}

		virtual ~Source() {
			for(int i=0; i<testSize; i++){
				// delete [] *this->sourceTexts[i];
				// delete [] *this->searchedTexts[i];
			}	
//			delete [] this->searchedTexts;
		}
	
};

class KMP{
	private:
		int * btTable;
		int countRatio;
		double lapsedTime;

		bool initBacktrackingTable(const char * text){
			int size = strlen(text);
			if (size==0) {return false;}
			this->btTable = new int[size];
			btTable[0] = -1;
			btTable[1] = 0;

			int cnd = 0, pos = 2;
			while(pos < size) {
				if (text[pos-1] == text[cnd]){
					this->btTable[pos] = (cnd+1);
					cnd +=1; pos +=1;
				} else if (cnd > 0) {
					cnd = this->btTable[cnd];
				} else {
					this->btTable[pos] = 0;
					pos +=1;
				}
			}
			// DEBU
			if (printDebug) printTable(this->btTable, text, size);
			
			return true;
		}

	public: 
		int CountRatio() {
			return this->countRatio;
		}
		double LapsedTime() {
			return this->lapsedTime;
		}
		void ResetRatio() {
			this->countRatio = 0;
			this->lapsedTime = 0;
		}

		void Search(const char * text, const char * source) {
			double start = GetTickCount();
			if (initBacktrackingTable(text)){
				int m = 0, i = 0, S = wordSize, W = templateSize;
				
				while((m + i) < S) {
					if(text[i] == source[m + i]){
						i += 1;
						if (i==W) {
							this->countRatio++;
							break;
						}
					} else {
						m += i - this->btTable[i];
						if (i>0) {
							i = this->btTable[i];
						}
					}
				}
			}
			this->lapsedTime += (GetTickCount()-start);
		}
		
		KMP() {
			this->countRatio = 0;
			this->lapsedTime = 0;
		}

		~KMP(){	delete[] this->btTable;}
};

class ShiftOR {
	private:
		unsigned int * bitArray;
		unsigned int bitTable;
		int countRatio;
		double lapsedTime;

		void initBitArray(const char * text) {
			int textSize = strlen(text);
			for(int i='A';i<'Z';i++){
				this->bitArray[i] = ~0;
				for(int j=0;j< textSize;j++){
					this->bitArray[i] &= ((text[j]==i)?(~0):~(1<<j));
				}
				this->bitArray[i] = ~bitArray[i];
			}
		}

	public:
		int CountRatio() {
			return this->countRatio;
		}

		double LapsedTime() {
			return this->lapsedTime;
		}

		void ResetRatio() {
			this->countRatio = 0;
			this->lapsedTime = 0;
		}
		void Search(const char * text, const char * source) {
			double start = GetTickCount();
			initBitArray(text);
			int sourceLength = strlen(source);
			unsigned int textLength = strlen(text);
			unsigned int byteArray = (~0);
			for(int i=0;i<sourceLength;i++) {
				byteArray <<= 1;
				byteArray |= this->bitArray[source[i]];
				if (~byteArray & (1 << textLength)) {
					countRatio++;
					break;
				}
			}
			this->lapsedTime += (GetTickCount()-start);
		};
		ShiftOR () {
			this->countRatio = 0;
			this->lapsedTime = 0;
			this->bitArray = new unsigned int ['Z'];
		};
		virtual ~ShiftOR () {delete [] this->bitArray;};

};

class Test {
	private:
		Source *s;
	public: 

		void CompareTest() {
			KMP * kmp = new KMP();
			ShiftOR *shOR = new ShiftOR();
			unsigned int kmpTotal=0;
			unsigned int shORTotal=0;
			for(int k=0;k<repeatTest;k++) {
				printf("Test (%d/%d)\n",(k+1),repeatTest );
				kmp->ResetRatio();
				shOR->ResetRatio();
				for(int i=0;i<testSize;i++) {
					const char * sourceText = s->GetSourceText(i);
					const char * searchedText = s->GetSearchedText(i);
					kmp->Search(searchedText,sourceText);
					shOR->Search(searchedText, sourceText);
				}
				printf("KMP     - found %4d | time lapsed: %6.0f\n",kmp->CountRatio() ,  kmp->LapsedTime());
				printf("ShiftOR - found %4d | time lapsed: %6.0f\n",shOR->CountRatio(), shOR->LapsedTime());
				kmpTotal += (unsigned int) kmp->LapsedTime();
				shORTotal += (unsigned int) shOR->LapsedTime();
				if(k != (repeatTest - 1)) {
					s->Reset();
				}
			}
			printf("\n\nSUMMARY:\n\nKMP total time: %12u | ShiftOR total time %12u \n",kmpTotal, shORTotal);
		}
		Test() {
			this->s = new Source();
		};
		virtual ~Test() {
			delete this->s;
		};
};


int main()
{
	// Initialize random words
	printf("Initializing Test data for %d strings of size %d\n", testSize, wordSize);
	Test *t = new Test();
	printf("Starting the test for both (KMP and Shift-OR) Algorithms\n");
	t->CompareTest();
	printf("Ending the test for both (KMP and Shift-OR) Algorithms\n");
	
	return 0;
}

