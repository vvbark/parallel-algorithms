# include <iostream>
# include <string.h>
# include <omp.h>

using namespace std; 

int countWords(char* str) {
	int counter = 0;
	
	for (int i = 1; i <= strlen(str); i++)
		if (str[i] == ' ' && str[i - 1] != ' ')		
			counter++;
	
	counter ++;
	
	return counter;
}


int main(int argc, char* argv[])
{
		
	if (argc > 1)
	{		
		cout << "Your word is <<" << argv[1] << ">>" << endl;
		cout << "Number of words : " << countWords(argv[1]) << endl;
	} 
	else
		cout << "Not arguments" << endl;
	
	return 0;
}
