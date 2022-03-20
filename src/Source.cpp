#include <iostream>
#include <conio.h>
#include <windows.h>
//Bugs:
//1. Entering A and then A 2 times after failing to endter correct selection coordinates the first time results in an infinite loop for some reason.
// Bug 1 Resolved
//PAWN NOT TAKING 2 STEPS
//BISHOP NOT WORKING

//Add kill counter
//Add HandShake Option
//Add Resign Option
//Make check			//make it inside destination selector validation, not inside moves functions
//Make Check Mate
//Make Stalemate

//Add Save/Load

//Add Time

//Movecountofpiece function ka issue hai

using namespace std;

//FUNCTIONS LIST

int Start();
//int Load();
//int Save;
//int Howto();
int moveSelector(int &pturn);
void whitesetter(int white[][8], int rowsize);
void blacksetter(int black[][8], int rowsize);
void stateinitializer(int state[][8], int white[][8], int black[][8]);
int pieceSelector(int state[][8], int pturn, char &col, int &row, int &actualrow, int &column/*is unercheck? iss case mai yahee dekhle if that piece can possible remove the check, only select if it can maybe*/);
int isValidSelection(char &col, int &row, int state[][8], int pturn, int &actualrow, int &column);
int destinationSelector(int state[][8], int pturn, int SelectedPieceCode, char &cold, int &rowd, int &actualrow, int &column, int &actualrowd, int &columnd);
int isValidDestination(char &cold, int &rowd, int state[][8], int pturn, int &actualrow, int &column, int &actualrowd, int &columnd);
void PrintEmptyBoard(int state[][8], char outputstates[][8]);

//ListofMoveFunctions:
//King		//board			//destination coordinates	//SelectionCoordinates		//so that we know which piece it can or cannot kill
bool King(int states[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]);
//Queen()
bool Queen(int states[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]);
//Bishop
bool Bishop(int states[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]);
//Knight
bool Knight(int states[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]);
//Rook
bool Rook(int states[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]);
//Pawn(pturn)
bool Pawn(int states[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]);


int MOVE(int state[][8], char boardstatesoutput[][8], int &n, char &col, int &row, char &cold, int &rowd, int movecountofpiece[][8]);

int blackCheck(int states[][8], int movecountofpiece[][8], int pturn);



//MAIN
int main() {
	char input;
	cout << "To Start New Game Press P" << endl;
	cout << "To Load Game Press L" << endl;	
	cout << "To Close the Game, Press X" << endl;
	cin >> input;
	if(input == 'P' || input == 'p')Start();
	return 0;

}//End of MAIN FUNCTION //



int Start() {
	int boardstates[8][8];
	int movecountofpiece[8][8];
	char boardstatesoutput[8][8];
	int white[2][8];
	whitesetter(white, 2);
	int black[2][8];
	blacksetter(black, 2);
	stateinitializer(boardstates, white, black);
	int n = 1;
	int whitekills = 0, blackkills = 0;

	char col;//the column in which player will input when he wants to select the place of the piece
	int row;//the row in which the player will input when he wants to select the place of the piece
	char cold;//the column in which player will input where he wants to send the already selected piece
	int rowd;//the row in which the player will input where he wants to send the already selected piece

	//cout << "This is the white set :" << endl << endl;

	//for (int i = 0; i < 2; i++) {
		//for (int j = 0; j < 8; j++) {
		//	cout << white[i][j] << " ";
		//}
		//cout << endl;
	//}

	//cout << "\n\nThis is the black set :" << endl << endl;

	//for (int i = 0; i < 2; i++) {
		//for (int j = 0; j < 8; j++) {
			//cout << black[i][j] << " ";
		//}
		//cout << endl;
	//}


	//cout << "\n\nThis is the state array : " << endl << endl;

	//for (int i = 0; i < 8; i++) {
		//for (int j = 0; j < 8; j++) {
			//cout << boardstates[i][j] << " ";
		//}
		//cout << endl << endl;
	//}

	//Initializing moveofpiececount array
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {
			movecountofpiece[i][j] = 0;
		}
	}
	for (int i = 2; i<6; i++) {
		for (int j = 0; j < 8; j++) {
			movecountofpiece[i][j] = -1;
		}
	}
	for (int i = 6; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			movecountofpiece[i][j] = 0;
		}
	}
	//initialized


	PrintEmptyBoard(boardstates, boardstatesoutput);
	char input;
	cout << "To Make a Move, Press M		To Save this Game, Press S		To Close This Game, Press X";

	cin >> input;
	if(input=='M' || input == 'm'){ int isvalid = MOVE(boardstates, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece); }
	

	//if (isvalid != -19) {
		//cout << "Valid move";
	//}
	//else
	//cout << "invalid selection";
	_getch();
	return 0;
}



int moveSelector(int &pturn) {
	if (pturn % 2 == 0 ) {
		return 2;
	}
	else return 1;
}
void whitesetter(int white[][8], int rowsize) {
	white[0][0] = 7;//rook1
	white[0][1] = 5;//knight1
	white[0][2] = 3;//bishop1
	white[0][3] = 1;//King
	white[0][4] = 2;//Queen
	white[0][5] = 4;//bishop2
	white[0][6] = 6;//knight2
	white[0][7] = 8;//rook2
	for (int i = 1; i<2; i++) {
		for (int j = 0; j < 8; j++) {
			white[i][j] = 9;
		}
	}
}
void blacksetter(int black[][8], int rowsize) {
	black[0][0] = -7;//rook1
	black[0][1] = -5;//knight1
	black[0][2] = -3;//bishop1
	black[0][3] = -1;//King
	black[0][4] = -2;//Queen
	black[0][5] = -4;//bishop2
	black[0][6] = -6;//knight2
	black[0][7] = -8;//rook2
	for (int i = 1; i<2; i++) {
		for (int j = 0; j < 8; j++) {
			black[i][j] = -9;
		}
	}
}
void stateinitializer(int state[][8], int white[][8], int black[][8]) {
	//upper part
	for (int row = 0; row < 1; row++) {
		for (int column = 0; column < 8; column++) {
			state[row][column] = white[row][column];
		}
	}
	for (int row = 1; row < 2; row++) {
		for (int column = 0; column < 8; column++) {
			state[row][column] = white[row][column];
		}
	}

	//Middle Part
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			state[i][j] = 0;
		}
	}



	//lower part
	int realrow = 0;
	int realcolumn = 0;
	for (int row = 7; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			state[row][column] = black[realrow][realcolumn];
			realcolumn++;
		}
	}

	realrow = 1;
	realcolumn = 0;
	for (int row = 6; row < 7; row++) {
		for (int column = 0; column < 8; column++) {
			state[row][column] = black[realrow][realcolumn];
			realcolumn++;
		}
	}


}
void PrintEmptyBoard(int state[][8], char outputstates[][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (state[i][j] == -9) { outputstates[i][j] = 'p'; }
			if (state[i][j] == -8) { outputstates[i][j] = 'r'; }
			if (state[i][j] == -7) { outputstates[i][j] = 'r'; }
			if (state[i][j] == -6) { outputstates[i][j] = 'n'; }
			if (state[i][j] == -5) { outputstates[i][j] = 'n'; }
			if (state[i][j] == -4) { outputstates[i][j] = 'b'; }
			if (state[i][j] == -3) { outputstates[i][j] = 'b'; }
			if (state[i][j] == -2) { outputstates[i][j] = 'q'; }
			if (state[i][j] == -1) { outputstates[i][j] = 'k'; }
			if (state[i][j] == 0) { outputstates[i][j] = ' '; }
			if (state[i][j] == 1) { outputstates[i][j] = 'K'; }
			if (state[i][j] == 2) { outputstates[i][j] = 'Q'; }
			if (state[i][j] == 3) { outputstates[i][j] = 'B'; }
			if (state[i][j] == 4) { outputstates[i][j] = 'B'; }
			if (state[i][j] == 5) { outputstates[i][j] = 'N'; }
			if (state[i][j] == 6) { outputstates[i][j] = 'N'; }
			if (state[i][j] == 7) { outputstates[i][j] = 'R'; }
			if (state[i][j] == 8) { outputstates[i][j] = 'R'; }
			if (state[i][j] == 9) { outputstates[i][j] = 'P'; }
		}
	}
	
	
	
	
	system("cls");
	cout << "________________________________________________" << endl;
	//ABC
	cout << "|    A    B    C    D    E    F    G    H      |" << endl;
	cout << "|----------------------------------------------|" << endl;
	//row 1
	cout << "|  |" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "|8 |" << "  " << outputstates[0][0] << "  " << "\xfe\xfe" << outputstates[0][1] << "\xfe\xfe" << "  " << outputstates[0][2] << "  " << "\xfe\xfe" << outputstates[0][3] << "\xfe\xfe" << "  " << outputstates[0][4] << "  " << "\xfe\xfe" << outputstates[0][5] << "\xfe\xfe" << "  " << outputstates[0][6] << "  " << "\xfe\xfe" << outputstates[0][7] << "\xfe\xfe" << "| 8|" << endl;
	cout << "|  |" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//row 2
	cout << "|  |" << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "|7 |" << "\xfe\xfe" << outputstates[1][0] << "\xfe\xfe" << "  " << outputstates[1][1] << "  " << "\xfe\xfe" << outputstates[1][2] << "\xfe\xfe" << "  " << outputstates[1][3] << "  " << "\xfe\xfe" << outputstates[1][4] << "\xfe\xfe" << "  " << outputstates[1][5] << "  " << "\xfe\xfe" << outputstates[1][6] << "\xfe\xfe" << "  " << outputstates[1][7] << "  " << "| 7|" << endl;
	cout << "|  |" << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//row 3
	cout << "|  |" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "|6 |" << "  " << outputstates[2][0] << "  " << "\xfe\xfe" << outputstates[2][1] << "\xfe\xfe" << "  " << outputstates[2][2] << "  " << "\xfe\xfe" << outputstates[2][3] << "\xfe\xfe" << "  " << outputstates[2][4] << "  " << "\xfe\xfe" << outputstates[2][5] << "\xfe\xfe" << "  " << outputstates[2][6] << "  " << "\xfe\xfe" << outputstates[2][7] << "\xfe\xfe" << "| 6|" << endl;
	cout << "|  |" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "|  |" << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "|5 |" << "\xfe\xfe" << outputstates[3][0] << "\xfe\xfe" << "  " << outputstates[3][1] << "  " << "\xfe\xfe" << outputstates[3][2] << "\xfe\xfe" << "  " << outputstates[3][3] << "  " << "\xfe\xfe" << outputstates[3][4] << "\xfe\xfe" << "  " << outputstates[3][5] << "  " << "\xfe\xfe" << outputstates[3][6] << "\xfe\xfe" << "  " << outputstates[3][7] << "  " << "| 5|" << endl;
	cout << "|  |" << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//row 5
	cout << "|  |" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "|4 |" << "  " << outputstates[4][0] << "  " << "\xfe\xfe" << outputstates[4][1] << "\xfe\xfe" << "  " << outputstates[4][2] << "  " << "\xfe\xfe" << outputstates[4][3] << "\xfe\xfe" << "  " << outputstates[4][4] << "  " << "\xfe\xfe" << outputstates[4][5] << "\xfe\xfe" << "  " << outputstates[4][6] << "  " << "\xfe\xfe" << outputstates[4][7] << "\xfe\xfe" << "| 4|" << endl;
	cout << "|  |" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "|  |" << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "|3 |" << "\xfe\xfe" << outputstates[5][0] << "\xfe\xfe" << "  " << outputstates[5][1] << "  " << "\xfe\xfe" << outputstates[5][2] << "\xfe\xfe" << "  " << outputstates[5][3] << "  " << "\xfe\xfe" << outputstates[5][4] << "\xfe\xfe" << "  " << outputstates[5][5] << "  " << "\xfe\xfe" << outputstates[5][6] << "\xfe\xfe" << "  " << outputstates[5][7] << "  " << "| 3|" << endl;
	cout << "|  |" << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//row 7
	cout << "|  |" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "|2 |" << "  " << outputstates[6][0] << "  " << "\xfe\xfe" << outputstates[6][1] << "\xfe\xfe" << "  " << outputstates[6][2] << "  " << "\xfe\xfe" << outputstates[6][3] << "\xfe\xfe" << "  " << outputstates[6][4] << "  " << "\xfe\xfe" << outputstates[6][5] << "\xfe\xfe" << "  " << outputstates[6][6] << "  " << "\xfe\xfe" << outputstates[6][7] << "\xfe\xfe" << "| 2|" << endl;
	cout << "|  |" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "|  |" << endl;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "|  |" << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "|  |" << endl;
	cout << "|1 |" << "\xfe\xfe" << outputstates[7][0] << "\xfe\xfe" << "  " << outputstates[7][1] << "  " << "\xfe\xfe" << outputstates[7][2] << "\xfe\xfe" << "  " << outputstates[7][3] << "  " << "\xfe\xfe" << outputstates[7][4] << "\xfe\xfe" << "  " << outputstates[7][5] << "  " << "\xfe\xfe" << outputstates[7][6] << "\xfe\xfe" << "  " << outputstates[7][7] << "  " << "| 1|" << endl;
	cout << "|  |" << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "\xfe\xfe\xfe\xfe\xfe" << "     " << "|  |"<<endl;
	cout << "|----------------------------------------------|" << endl;
	cout << "|     A    B    C    D    E    F    G    H     |" << endl;
	cout << "|______________________________________________|" << endl;
}

int pieceSelector( int state[][8], int pturn, char &col, int &row, int &actualrow, int &column/*is unercheck? iss case mai yahee dekhle if that piece can possible remove the check, only select if it can maybe*/) {
	int validity = -19;
	//while (validity == -19) {
		cout << "Enter Co-ordinates of piece you want to move : " << endl;
		cin >> col;
		//cout << "Enter row Co-ordinates of block to be selected : " << endl;
		cin >> row;

		validity = isValidSelection(col, row, state, pturn, actualrow, column);
	//}
	//when control enters this poit, i will have the correct values of the coordinates.
	//col = col entered by user during selection and row = row entered by user during selection
	//returning validity to MOVE
	return validity;
	
}
int isValidSelection(char &col, int &row, int state[][8], int pturn, int &actualrow, int &column) {

	if (col < 'A' || col>'Z') {
		if (col<'a' || col>'z') {
			cout << "Invalid Column Selection";
			return -19;
		}
	}
	if (row < 1 || row>8) {
		cout << "Invalid Row Selection";
		return -19;
	}

	if (col == 'A' || col == 'a') { column = 0; }
	if (col == 'B' || col == 'b') { column = 1; }
	if (col == 'C' || col == 'c') { column = 2; }
	if (col == 'D' || col == 'd') { column = 3; }
	if (col == 'E' || col == 'e') { column = 4; }
	if (col == 'F' || col == 'f') { column = 5; }
	if (col == 'G' || col == 'g') { column = 6; }
	if (col == 'H' || col == 'h') { column = 7; }
	
	if (row == 1 ) { actualrow = 7; }
	if (row == 2) { actualrow = 6; }
	if (row == 3) { actualrow = 5; }
	if (row == 4) { actualrow = 4; }
	if (row == 5) { actualrow = 3; }
	if (row == 6) { actualrow = 2; }
	if (row == 7) { actualrow = 1; }
	if (row == 8) { actualrow = 0; }

	int stateofselectedindex = state[actualrow][column];

	if (pturn == 1 && stateofselectedindex<0) {
		cout << "Invalid Piece, Please select a White Piece." << endl;
		return -19;
	}//Invalid Piece
	if (pturn == 1 && stateofselectedindex == 0) {
		cout << "You selected an empty space. Re-enter co-ordinates." << endl;
		return -19;
	}//empty block
	if (pturn == 1 && stateofselectedindex>0) {
		cout << "Valid Selection." << endl;
		return stateofselectedindex;
	}//correct selection

	if (pturn == 2 && stateofselectedindex>0) {
		cout << "Invalid Piece, Please select a Black Piece." << endl;
		return -19;
	}//Invalid Piece
	if (pturn == 2 && stateofselectedindex == 0) {
		cout << "You selected an empty space. Re-enter co-ordinates." << endl;
		return -19;
	}//empty block
	if (pturn == 2 && stateofselectedindex<0) {
		cout << "Valid Selection." << endl;
		return stateofselectedindex;
	}//correct selection
}

int destinationSelector(int state[][8], int pturn, int SelectedPieceCode, char &cold, int &rowd, int &actualrow, int &column, int &actualrowd, int &columnd) {	
	//according to the code, i need move finctions to determine the destination.
	//on second thought, this is the best time to see if it lets me over write my own goti. all other moves are valid at this point.
	//a note to self : mai goti ka naam to return kar wa raha hoo piece selector se, lekin uski wo location return nahi kar wa raha jis se us ko in case of correct move; delete karwana hai


	int validity = -19;
	//while (validity == -19) {
		cout << "Enter Co-ordinates of the block where you want to send the selected piece : " << endl;
		cin >> cold;
		//cout << "Enter row Co-ordinates of block where you want to send the selected piece : " << endl;
		cin >> rowd;

		validity = isValidDestination(cold, rowd, state, pturn, actualrow, column, actualrowd, columnd);
	//}
	//when control enters this poit, i will have the correct values of the coordinates.
	//col = col entered by user during selection and row = row entered by user during selection
	//returning validity to MOVE
	return validity;
}

int isValidDestination(char &cold, int &rowd, int state[][8], int pturn, int &actualrow, int &column, int &actualrowd, int &columnd) {

	if (cold < 'A' || cold>'Z') {
		if (cold<'a' || cold>'z') {
			cout << "Invalid Column Selection";
			return -19;
		}
	}
	if (rowd < 1 || rowd>8) {
		cout << "Invalid Row Selection";
		return -19;
	}


	if (cold == 'A' || cold == 'a') { columnd = 0; }
	if (cold == 'B' || cold == 'b') { columnd = 1; }
	if (cold == 'C' || cold == 'c') { columnd = 2; }
	if (cold == 'D' || cold == 'd') { columnd = 3; }
	if (cold == 'E' || cold == 'e') { columnd = 4; }
	if (cold == 'F' || cold == 'f') { columnd = 5; }
	if (cold == 'G' || cold == 'g') { columnd = 6; }
	if (cold == 'H' || cold == 'h') { columnd = 7; }



	if (rowd == 1) { actualrowd = 7; }
	if (rowd == 2) { actualrowd = 6; }
	if (rowd == 3) { actualrowd = 5; }
	if (rowd == 4) { actualrowd = 4; }
	if (rowd == 5) { actualrowd = 3; }
	if (rowd == 6) { actualrowd = 2; }
	if (rowd == 7) { actualrowd = 1; }
	if (rowd == 8) { actualrowd = 0; }

	int stateofselectedindex = state[actualrowd][columnd];

	if (pturn == 1 && stateofselectedindex>0) {
		cout << "You cannot kill your own piece. Please Re-enter co-ordinates." << endl;
		return -19;
	}//Trying to kill your own piece
	
	if (pturn == 1 && stateofselectedindex<0) {
		//cout << "Killed" << endl;
		return stateofselectedindex;
	}//actually killing the other players unit

	if (pturn == 2 && stateofselectedindex<0) {
		cout << "You cannot kill your own piece. Please Re-enter co-ordinates." << endl;
		return -19;
	}//Trying to kill your own piece
	
	
	if (pturn == 2 && stateofselectedindex<0) {
		cout << "Killed" << endl;
		return stateofselectedindex;
	}//actually killing the other players unit

}

int MOVE(int state[][8], char boardstatesoutput[][8], int &n, char &col, int &row, char &cold, int &rowd, int movecountofpiece[][8]) {
	int actualrow =0, column = 0, actualrowd= 0, columnd=0;
	int pturn = moveSelector(n);

	if (pturn == 1)		cout << "\n\nWhite Player's turn (Captial Units)" << endl;
	else		cout << "\n\nBlack Player's turn (Small Units)" << endl;
	
	int returnvalidity = pieceSelector(state, pturn, col, row, actualrow, column);//in case it is valid, returnvalidity = selected goti ka code
	while (returnvalidity == -19) {
		cout << "\nPlease Re-enter co-ordinates for selection : " << endl;
		returnvalidity = pieceSelector(state, pturn, col, row, actualrow, column);
	}               
	int movesuccessful = destinationSelector(state, pturn, returnvalidity, cold, rowd, actualrow, column, actualrowd, columnd);
	if (movesuccessful == -19) {
		cout << "\nPlease Re-enter selection co-ordinates : " << endl;
		MOVE(state, boardstatesoutput, pturn, col, row, cold, rowd, movecountofpiece);
	}

	bool movereallysuccessful = true;


	if (returnvalidity == 1 || returnvalidity == -1) {//King of any player is selected
		
		movereallysuccessful = King(state, cold, rowd, col, row, pturn, movecountofpiece);
		if (!movereallysuccessful) {
			cout << "Invalid Move" << endl;
			MOVE(state, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece);
		}
	}
	else if (returnvalidity == 2 || returnvalidity == -2) {//Queen of any player is selected
		
		movereallysuccessful = Queen(state, columnd, actualrowd, column, actualrow, pturn, movecountofpiece);
		if (!movereallysuccessful) {
			cout << "Invalid Move" << endl;
			MOVE(state, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece);
		}
	}
	else if (returnvalidity == 3 || returnvalidity == -3) {//Bishop 2 of any player is selected
		movereallysuccessful = Bishop(state, columnd, actualrowd, column, actualrow, pturn, movecountofpiece);
		if (!movereallysuccessful) {
			cout << "Invalid Move" << endl;
			MOVE(state, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece);
		}
	}
	else if (returnvalidity == 4 || returnvalidity == -4) {//Bishop 1 of any player is selected
		
		movereallysuccessful = Bishop(state, columnd, actualrowd, column, actualrow, pturn, movecountofpiece);
		if (!movereallysuccessful) {
			cout << "Invalid Move" << endl;
			MOVE(state, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece);
		}
	}
	else if (returnvalidity == 5 || returnvalidity == -5) {//Knight 2 of any player is selected
		movereallysuccessful = Knight(state, columnd, actualrowd, column, actualrow, pturn, movecountofpiece);
		if (!movereallysuccessful) {
			cout << "Invalid Move" << endl;
			MOVE(state, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece);
		}
	}
	else if (returnvalidity == 6 || returnvalidity == -6) {//knight 1 of any player is selected
		
		movereallysuccessful = Knight(state, columnd, actualrowd, column, actualrow, pturn, movecountofpiece);
		if (!movereallysuccessful) {
			cout << "Invalid Move" << endl;
			MOVE(state, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece);
		}
	}
	else if (returnvalidity == 7 || returnvalidity == -7) {//rook2 of any player is selected
		
		movereallysuccessful = Rook(state, columnd, actualrowd, column, actualrow, pturn, movecountofpiece);
		if (!movereallysuccessful) {
			cout << "Invalid Move" << endl;
			MOVE(state, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece);
		}
	}
	else if (returnvalidity == 8 || returnvalidity == -8) {//rook1 of any player is selected
		
		movereallysuccessful = Rook(state, columnd, actualrowd, column, actualrow, pturn, movecountofpiece);
		if (!movereallysuccessful) {
			cout << "Invalid Move" << endl;
			MOVE(state, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece);
		}
	}
	else if (returnvalidity == 9 || returnvalidity == -9) {//pawn is selected
		movereallysuccessful = Pawn(state, columnd, actualrowd, column, actualrow, pturn, movecountofpiece);
		if (!movereallysuccessful) {
			cout << "Invalid Move" << endl;
			MOVE(state, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece);
		}
	}
	
	system("cls");
	PrintEmptyBoard(state, boardstatesoutput);
	n++;
	MOVE(state, boardstatesoutput, n, col, row, cold, rowd, movecountofpiece);
	//isEvenPossible();
	//DestinationStateChecker();//in case apna hee piece para ho, return false (not possible)
	//isPlayerKindUnderCheck();
	//if yes
	//	DoesThisMoveRemoveCheck();
	//else
	//	DoesitPutOwnKingUnderCheck();
	//
	//
	//Mover();
	//Update(/*n bhi issi mai ++ hoga*/);
	//isOtherPlayerUnderCheckorCheckMateorNone();
	//cout respectively
	return movesuccessful;//yaani positive
}


//Piece Moves

//King		//board			//destination coordinates	//SelectionCoordinates		//so that we know which piece it can or cannot kill
bool King(int state[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]) {


			if (actualrowd == 1 + actualrow && columnd == 1 + column) {//NE
				state[actualrowd][columnd] = state[actualrow][column];
				movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
				state[actualrow][column] = 0;
				movecountofpiece[actualrow][column] = -1;
				
				return true;
			}
			else if (actualrowd == 1 + actualrow && columnd == column) {//seedha aage(ooper North)
				state[actualrowd][columnd] = state[actualrow][column];
				movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
				state[actualrow][column] = 0;
				movecountofpiece[actualrow][column] = -1;
				
				return true;
			}
			else if (actualrowd == actualrow - 1 && columnd == column) {//Seedha peechay (neechay South)
				state[actualrowd][columnd] = state[actualrow][column];
				movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
				state[actualrow][column] = 0;
				movecountofpiece[actualrow][column] = -1;
				return true;
			}
			else if (actualrowd == 1 + actualrow && columnd == column - 1) {//NW
				state[actualrowd][columnd] = state[actualrow][column];
				movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
				state[actualrow][column] = 0;
				movecountofpiece[actualrow][column] = -1;
				
				return true;
			}
			else if (actualrowd == actualrow && columnd == column + 1) {//Right (East)
				state[actualrowd][columnd] = state[actualrow][column];
				movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
				state[actualrow][column] = 0;
				movecountofpiece[actualrow][column] = -1;
				
				return true;
			}
			else if (actualrowd == actualrow && columnd == column - 1) {//Left (West)
				state[actualrowd][columnd] = state[actualrow][column];
				movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
				state[actualrow][column] = 0;
				movecountofpiece[actualrow][column] = -1;
				
				return true;
			}
			else if (actualrowd == actualrow - 1 && columnd == column + 1) {//SE
				state[actualrowd][columnd] = state[actualrow][column];
				movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
				state[actualrow][column] = 0;
				movecountofpiece[actualrow][column] = -1;
				
				return true;
			}
			else if (actualrowd == actualrow - 1 && columnd == column - 1) {//SW
				state[actualrowd][columnd] = state[actualrow][column];
				movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
				state[actualrow][column] = 0;
				movecountofpiece[actualrow][column] = -1;
				return true;
				
			}	
		return false;
}
//Queen()
bool Queen(int state[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]) {
	int stepsrowwise = 0;
	int stepscolwise = 0;
	int row = actualrow;
	int col = column;
	int steps = 0;

	//Diagonal Moves copied from bishop
	if (actualrowd > actualrow && columnd > column) {//SE
		stepsrowwise = actualrowd - actualrow;
		stepscolwise = columnd - column;
		if (stepsrowwise != stepscolwise) {
			return false;
		}//if this 'if' is false, then it lies on concerned diagonal
		steps = stepscolwise; //colwise or rowwise does not make a difference at this point because both are equal
		for (int i = 1; i < steps; i++) {
			row++;
			col++;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else if (actualrowd < actualrow && columnd < column) {//NW
		stepsrowwise = actualrow - actualrowd;
		stepscolwise = column - columnd;
		if (stepsrowwise != stepscolwise) {
			return false;
		}//if this 'if' is false, then it lies on concerned diagonal
		steps = stepscolwise; //colwise or rowwise does not make a difference at this point because both are equal
		for (int i = 1; i < steps; i++) {
			row--;
			col--;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else if (actualrowd > actualrow && columnd < column) {//SW
		stepsrowwise = actualrowd - actualrow;
		stepscolwise = column - columnd;
		if (stepsrowwise != stepscolwise) {
			return false;
		}//if this 'if' is unfulfilled, then it lies on concerned diagonal
		steps = stepscolwise; //colwise or rowwise does not make a difference at this point because both are equal
		for (int i = 1; i < steps; i++) {
			row++;
			col--;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else if (actualrowd<actualrow && columnd>column) {
		stepsrowwise = actualrow - actualrowd;
		stepscolwise = columnd - column;
		if (stepsrowwise != stepscolwise) {
			return false;
		}//if this 'if' is false, then it lies on concerned diagonal
		steps = stepscolwise; //colwise or rowwise does not make a difference at this point because both are equal
		for (int i = 1; i < steps; i++) {
			row--;
			col++;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else if (actualrowd > actualrow && columnd == column) {//neechay (South)				//+ Moves  Copied from Rook
		steps = actualrowd - actualrow;
		for (int i = 1; i < steps; i++) {
			row++;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else if (actualrowd < actualrow && columnd == column) {//ooper (North)
		steps = actualrow - actualrowd;
		for (int i = 1; i < steps; i++) {
			row--;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else if (actualrowd == actualrow && columnd > column) {//Right
		steps = columnd - column;
		for (int i = 1; i < steps; i++) {
			col++;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else if (actualrowd == actualrow && columnd < column) {//Left
		steps = column - columnd;
		for (int i = 1; i < steps; i++) {
			col--;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else
		return false;
}

//Bishop // not killing prolly
bool Bishop(int state[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]) {
	//at the time of calling this function i know for sure that the destination is not my own unit and not outside the board
	int stepsrowwise = 0;
	int stepscolwise = 0;
	int row = actualrow;
	int col = column;

	if (actualrowd > actualrow && columnd > column) {//SE
		stepsrowwise = actualrowd - actualrow;
		stepscolwise = columnd - column;
		if (stepsrowwise != stepscolwise) {
			return false;
		}//if this 'if' is false, then it lies on concerned diagonal
		int steps = stepscolwise; //colwise or rowwise does not make a difference at this point because both are equal
		for (int i = 1; i < steps; i++) {
			row++;
			col++;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else if (actualrowd < actualrow && columnd < column) {//NW
		stepsrowwise = actualrow - actualrowd;
		stepscolwise = column - columnd;
		if (stepsrowwise != stepscolwise) {
			return false;
		}//if this 'if' is false, then it lies on concerned diagonal
		int steps = stepscolwise; //colwise or rowwise does not make a difference at this point because both are equal
		for (int i = 1; i < steps; i++) {
			row--;
			col--;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else if (actualrowd > actualrow && columnd < column) {//SW
		stepsrowwise = actualrowd - actualrow;
		stepscolwise = column - columnd;
		if (stepsrowwise != stepscolwise) {
			return false;
		}//if this 'if' is unfulfilled, then it lies on concerned diagonal
		int steps = stepscolwise; //colwise or rowwise does not make a difference at this point because both are equal
		for (int i = 1; i < steps; i++) {
			row++;
			col--;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else if (actualrowd<actualrow && columnd>column) {
		stepsrowwise = actualrow - actualrowd;
		stepscolwise = columnd - column;
		if (stepsrowwise != stepscolwise) {
			return false;
		}//if this 'if' is false, then it lies on concerned diagonal
		int steps = stepscolwise; //colwise or rowwise does not make a difference at this point because both are equal
		for (int i = 1; i < steps; i++) {
			row--;
			col++;
			if (state[row][col] != 0) {
				return false;
			}
		}
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}
	else return false;
}

//Knight
bool Knight(int state[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]) {
	if (actualrowd == actualrow + 2 && columnd == column + 1) {
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}//ooper right
	if (actualrowd == actualrow + 2 && columnd == column - 1) {
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}//ooper left
	if (actualrowd == actualrow - 2 && columnd == column + 1) {
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}//neechay right
	if (actualrowd == actualrow - 2 && columnd == column - 1) {
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}//neechay left
	if (actualrowd == actualrow + 1 && columnd == column + 2) {
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}//right ooper
	if (actualrowd == actualrow + 1 && columnd == column - 2) {
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}//left ooper
	if (actualrowd == actualrow - 1 && columnd == column + 2) {
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}//right neechay
	if (actualrowd == actualrow - 1 && columnd == column - 2) {
		state[actualrowd][columnd] = state[actualrow][column];
		movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
		state[actualrow][column] = 0;
		movecountofpiece[actualrow][column] = -1;
		return true;
	}//left neechay
	else
		return false;
}

//Rook
bool Rook(int state[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8]) {
	int steps = 0;
	int row = actualrow;
	int col = column;
	
		if (actualrowd > actualrow && columnd == column) {//neechay (South)
			steps = actualrowd - actualrow;
			for (int i = 1; i < steps; i++) {
				row++;
				if (state[row][col] != 0) {
					return false;
				}
			}
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else if (actualrowd < actualrow && columnd == column) {//ooper (North)
			steps = actualrow - actualrowd;
			for (int i = 1; i < steps; i++) {
				row--;
				if (state[row][col] != 0) {
					return false;
				}
			}
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else if (actualrowd == actualrow && columnd > column) {//Right
			steps = columnd - column;
			for (int i = 1; i < steps; i++) {
				col++;
				if (state[row][col] != 0) {
					return false;
				}
			}
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else if (actualrowd == actualrow && columnd < column) {//Left
			steps = column - columnd;
			for (int i = 1; i < steps; i++) {
				col--;
				if (state[row][col] != 0) {
					return false;
				}
			}
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column] + 1;
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else
			return false;
}
//Pawn(pturn)
bool Pawn(int state[][8], int columnd, int actualrowd, int column, int actualrow, int pturn, int movecountofpiece[][8])
{
	if (pturn == 1) {
		if (actualrowd == actualrow + 1 && columnd == column && state[actualrowd][columnd]==0) {//p1 Moving 1 step forward
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrowd][columnd] + 1;//Adding 1 to it's move count at its present position
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else if (actualrowd == actualrow + 2 && columnd == column && movecountofpiece[actualrow][column] == 0 && state[actualrowd][columnd]==0 && state[actualrowd+1][columnd]==0) {//p1 Moving 2 steps forward
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrowd][columnd] + 1;//adding 1 to its move count at its present location
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else if (actualrowd == actualrow + 1 && columnd == column + 1 && pturn == 1 && state[actualrowd][columnd] < 0) {//p1 killing one to the right
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrowd][columnd] + 1;//adding 1 to its move count at its present location
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else if (actualrowd == actualrow + 1 && columnd == column - 1 && pturn == 1 && state[actualrowd][columnd] < 0) {//p1 killing one to the left
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrowd][columnd] + 1;//adding 1 to its move count at its present location
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else return false;
	}
	else if (pturn == 2) 
	{
		if (actualrowd == actualrow - 1 && columnd == column) {//p2 Moving 1 step forward
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrowd][columnd] + 1;//Adding 1 to it's move count at its present position
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else if (actualrowd == actualrow - 2 && columnd == column && movecountofpiece[actualrow][column] == 0 && state[actualrowd+1][column]==0 && state[actualrowd][columnd] == 0 ) {//p2 Moving 2 steps forward
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrowd][columnd] + 1;//adding 1 to its move count at its present location
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else if (actualrowd == actualrow - 1 && columnd == column + 1 && pturn == 2 && state[actualrowd][columnd] > 0) {//p2 killing one to the right
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrowd][columnd] + 1;//adding 1 to its move count at its present location
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else if (actualrowd == actualrow - 1 && columnd == column - 1 && pturn == 2 && state[actualrowd][columnd] > 0) {//p2 killing one to the left
			state[actualrowd][columnd] = state[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrow][column];
			movecountofpiece[actualrowd][columnd] = movecountofpiece[actualrowd][columnd] + 1;//adding 1 to its move count at its present location
			state[actualrow][column] = 0;
			movecountofpiece[actualrow][column] = -1;
			return true;
		}
		else return false;
	}
	return false;
}



int blackCheck(int state[][8], int movecountofpiece[][8], int pturn) {
	bool kingfound=false;
	int i = 0;
	int j = 0;
	for (i = 0; i < 8 && kingfound == false; i++) {
		for (j = 0; j < 8 && kingfound == false; j++) {
			if (state[i][j] == -1) {
				kingfound = true;
			}
		}
	}//it will return the coordinates of the king
	bool apnigotistandinginpath = false;
	bool isUnderCheck = false;
	int itemp = i;
	int jtemp = j;
	//Bishop or Queen in SE Diag
	while (itemp<8 && jtemp<8 && isUnderCheck==false && apnigotistandinginpath == false) {
		if (state[itemp][jtemp] < 0) {//iss path par, pehle apni hee goti khari hai
			apnigotistandinginpath = true;
		}
		if (state[itemp][jtemp] == 2 || state[itemp][jtemp] == 3 || state[itemp][jtemp] == 4 && apnigotistandinginpath == false && isUnderCheck==false) {
			isUnderCheck = true;
			return -21;
		}
		itemp++;
		jtemp++;
	}//at the time of exiting this loop, it either found a friendly goti in the path, or found nothing in the path
	
	itemp = i;//bringing coordinates back to King's position
	jtemp = j;//Bringing coordinates back to King's position

	//Bishop or Queen in NW diagonal
	while (itemp > 0 && jtemp > 0 && isUnderCheck == false && apnigotistandinginpath == false) {
		if (state[itemp][jtemp] < 0) {//iss path par, pehle apni hee goti khari hai
			apnigotistandinginpath = true;
		}
		//				White Queen					White Bishop			White Bishop
		if (state[itemp][jtemp] == 2 || state[itemp][jtemp] == 3 || state[itemp][jtemp] == 4 && apnigotistandinginpath == false && isUnderCheck == false) {
			isUnderCheck = true;
			return -21;
		}
		itemp--;
		jtemp--;
	}//at the time of exiting this loop, it either found a friendly goti in the path, or found nothing in the path

	itemp = i;//bringing coordinates back to King's position
	jtemp = j;//Bringing coordinates back to King's position

	while (itemp > 0 && jtemp < 8 && isUnderCheck == false && apnigotistandinginpath == false) {
		if (state[itemp][jtemp] < 0) {//iss path par, pehle apni hee goti khari hai
			apnigotistandinginpath = true;
		}
		//				White Queen					White Bishop			White Bishop
		if (state[itemp][jtemp] == 2 || state[itemp][jtemp] == 3 || state[itemp][jtemp] == 4 && apnigotistandinginpath == false && isUnderCheck == false) {
			isUnderCheck = true;
			return -21;
		}
		itemp--;
		jtemp++;
	}



}