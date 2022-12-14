#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

bool win = false;

// Random word based on the level
string RandomWord(int level) {
    srand(time(0));
	int random_line;
    if (level == 1)
		random_line = (rand() % 100) + 1; //line between 1-100

	if (level == 2)
		random_line = (rand() % 100) + 101; //line between 101-200
	if (level == 3)
		random_line = (rand() % 100) + 201; //line between 201-300
	int line_no = 1;
	string line, word;
	ifstream file("words.txt");
	while (getline(file, line))
	{
		if (random_line == line_no)
		{
			word = line;
			break;
		}
		line_no++;
	}
	return word;
}

void Hangman(int turns){
	switch (turns)
	{
	case 0:
		cout << "\t|--------|" << endl;
		cout << "\t|        0" << endl;
		cout << "\t|       /|\\" << endl;
		cout << "\t|        |" << endl;
		cout << "\t|       / \\" << endl;
		cout << "\t|" << endl;
		cout << "\t|_" << endl;
		break;

	case 1:
		cout << "\t|--------|" << endl;
		cout << "\t|        0" << endl;
		cout << "\t|       /|\\" << endl;
		cout << "\t|        |" << endl;
		cout << "\t|         \\" << endl;
		cout << "\t|" << endl;
		cout << "\t|_" << endl;
		break;
	case 2:
		cout << "\t|--------|" << endl;
		cout << "\t|        0" << endl;
		cout << "\t|       /|\\" << endl;
		cout << "\t|        |" << endl;
		cout << "\t|           " << endl;
		cout << "\t|" << endl;
		cout << "\t|_" << endl;
		break;
	case 3:
		cout << "\t|--------|" << endl;
		cout << "\t|        0" << endl;
		cout << "\t|       /|\\" << endl;
		cout << "\t|         " << endl;
		cout << "\t|           " << endl;
		cout << "\t|" << endl;
		cout << "\t|_" << endl;
		break;
	case 4:
		cout << "\t|--------|" << endl;
		cout << "\t|        0" << endl;
		cout << "\t|        |\\" << endl;
		cout << "\t|         " << endl;
		cout << "\t|           " << endl;
		cout << "\t|" << endl;
		cout << "\t|_" << endl;
		break;
	case 5:
		cout << "\t|--------|" << endl;
		cout << "\t|        0" << endl;
		cout << "\t|        |  " << endl;
		cout << "\t|         " << endl;
		cout << "\t|           " << endl;
		cout << "\t|" << endl;
		cout << "\t|_" << endl;
		break;
	case 6:
		cout << "\t|--------|" << endl;
		cout << "\t|        0" << endl;
		cout << "\t|           " << endl;
		cout << "\t|         " << endl;
		cout << "\t|           " << endl;
		cout << "\t|" << endl;
		cout << "\t|_" << endl;
		break;
	case 7:
		cout << "\t|--------|" << endl;
		cout << "\t|         " << endl;
		cout << "\t|           " << endl;
		cout << "\t|         " << endl;
		cout << "\t|           " << endl;
		cout << "\t|" << endl;
		cout << "\t|_" << endl;
		break;
	}
}

string help_letter(string word, string letter){
    string unknown="";
    for (int x = 0; x < word.size(); x++)
	{
		if (letter.find(word.at(x)) == -1){
             unknown += word[x];
             break;
        }
	}
    return unknown;
}

void PrintWord(string word, string letter){
	for (int x = 0; x < word.size(); x++)
	{
		if (letter.find(word.at(x)) != -1)
			cout << word.at(x) << " ";
		else
		{
			cout << "_ ";
			win = false;
		}
	}
}

int main() {
	int turns = 7, level;

	cout << "choose your level: \n1)Easy\n2)Medium\n3)Hard\n-->";
	cin >> level;

	//Validate input
	while (level < 1 || level>3) {
		system("cls");
		cout << "You have enered a wrong number, renter your level..\n";
		cout << "choose your level: \n1)Easy\n2)Medium\n3)Hard\n-->";
		cin >> level;
	}

    string letter, word = RandomWord(level);
	string guessesMade = "";

	system("cls"); 

	bool help = false, cheating = false;
    int number_of_help = word.size()/2;
	
	while (turns > 0)
	{
		win = true;
		Hangman(turns);
		PrintWord(word, guessesMade);
		if (help)
		{
			win = false;
			help = false;
		}

		if (win == true)
			break;
		cout << "\nYou have " <<number_of_help<<" helps left" << endl;
		cout << "\nGuesses made so far: " << guessesMade << endl;
		cout << "\nEnter a letter: ";
		cin >> letter;

		if (letter.size() >= 2)
		{
			if (letter == "help")
			{
                if(number_of_help==0){
                    cout<<"\nOOPS! Out of help, try yourself\n";
                    continue;
                }
				help = true;
				turns--;
                number_of_help--;
                letter = help_letter(word, guessesMade);
				cout <<"help letter is "<<letter << endl;
			}
			else
			{
				system("cls");
				cheating = true;
                break;
			}
		}

		guessesMade += letter[0];

		if (word.find(letter) != -1 || help)
		{
			system("cls");
			continue;
		}
		else
		{
			system("cls");
			turns--;
		}
	}

	if ((turns == 0) && !cheating) 
	{
		cout << "\nYou Lost:(\nThe word was: "<<word<<endl;
	}
	if ((turns > 0) && !cheating) 
	{
		cout << "\nYou won!!\nThe word was: "<<word<<endl;
	}
    if(cheating){
        cout << "\nYou cheated!!\nThe word was: "<<word<<endl;
    }
	return 0;
}
