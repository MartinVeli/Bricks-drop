/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Martin Velichkov
* @idnumber 3MI0600314
* @compiler VC
*
* file with helper functions
*
*/


#include <iostream>
#include <fstream>
using namespace std;


constexpr int rows = 10;
constexpr int cols = 8;
constexpr int maxSizeOfBrick = 4;
constexpr int account = 64;

void filedMatrix(char matrix[][cols], int indexRow, char& color, int brickStartPosition, int sizeOfBrick)
{
	for (size_t i = brickStartPosition; sizeOfBrick; i--, sizeOfBrick--) {
		if (matrix[indexRow][i] == -1) {
			matrix[indexRow][i] = color;
		}
		else { 
			++color; 
			return; 
		}
	}
	++color;
}

int validRandomNumberForSize(int availableSpace)
{	
	while (true) {
		int n = rand() % 10;
		if (n > 0 && n <= maxSizeOfBrick && n <= availableSpace)
			return n;
	}
}

int validRandomNumberForPosition(int availableSpace)
{
	while (true) {
		int n = rand() % 10;
		if (n <= availableSpace)
			return n;
	}
}

void printMatrix(const char matrix[][cols], int result)
{
	cout << endl;
	for (int i = 0; i < cols; i++)
		cout << "  " << i;
	cout << endl;
	for (size_t i = 0; i < rows; i++)
	{
		cout << i;
		for (size_t j = 0; j < cols; j++)
		{
			cout << "|" << matrix[i][j] << "|";
		}
		cout << endl;
	}
	cout << "Your result is: " << result << endl;
}

char validInput(char ch1, char ch2) {
	char input;
	while (true) {
		cin >> input;
		if (input == ch1 || input == ch2)
			return input;
		else cout << "Incorrect input! Enter valid char";
	}
}

char validInputForPlayOrQuit(char ch1, char ch2, char ch3) {
	char input;
	while (true) {
		cin >> input;
		if (input == ch1 || input == ch2 || input == ch3)
			return input;
		else cout << "Incorrect input! Enter valid char";
	}
}

int rightEndOfBlock(const char matrix[][cols], int col, int row) {
	char ch = matrix[row][col];
	for (int i = col; i < cols; i++) {
		if (matrix[row][i] != ch) {
			if (i > col)
				return i - 1;
			else return i;
		}
	}
	return cols - 1;
}

int emptyPositionsR(const char matrix[][cols], int colR, int row) {
	int count = 0;
	for (int i = colR + 1; i < cols; i++) {
		if (matrix[row][i] == -1) {
			count++;
		}
	}
	return count;
}

int emptyPositionsL(const char matrix[][cols], int col, int row) {
	int count = 0;
	for (int i = col - 1; i > -1 ; i--) {
		if (matrix[row][i] == -1) {
			count++;
		}
	}
	return count;
}

bool validData(int col, int row, const char matrix[][cols], char ch, int position) {
	if (matrix[row][col] != -1) {
		int colR = rightEndOfBlock(matrix, col, row);
		if (position > 0) {
			if (ch == 'r' && colR < cols - 1) {
				if (position <= emptyPositionsR(matrix, colR, row))
					return 1;
			}
			else if (ch == 'l') {
				if (col > 0 && position <= emptyPositionsL(matrix, col, row))
					return 1;
			}
		}
	}
	return 0;
}

void validRowColDirectionPosition(int& col, int& row, const char matrix[][cols], char& ch, int& position) {
	while (true) {
		cout << "Enter col:";
		cin >> col;
		cout << "Enter row:";
		cin >> row;
		cout << "Direction:" << endl << "Enter 'l' for left or 'r' to right:";
		ch = validInput('l', 'r');
		cout << "Enter position:";
		cin >> position;
		if (col >= 0 && col < cols && row >= 0 && row < rows) {
			if (validData(col, row, matrix, ch, position))
				return;
			else cout << "Incorrect input!";
		}
	}
}

void changeBlockL(char matrix[][cols], int userRow, int& userCol, int position, int& colR) {
	char ch = matrix[userRow][userCol];
	userCol -= 1;
	for (userCol, colR; position; userCol--, colR--, position--) {
		matrix[userRow][userCol] = ch;
		matrix[userRow][colR] = -1;
	}
}

void changeBlockR(char matrix[][cols], int userRow, int& userCol, int position, int& colR) {
	char ch = matrix[userRow][userCol];
	colR += 1;
	for (userCol, colR; position; userCol++, colR++, position--) {
		matrix[userRow][userCol] = -1;
		matrix[userRow][colR] = ch;
	}
}

void destroyRow(char matrix[][cols], int currentRow) {
	for (size_t i = 0; i < cols; i++) {
		matrix[currentRow][i] = -1;
	}
}

void swapRows(char matrix[][cols], int currentRow) {
	for (size_t i = 0; i < cols; i++) {
		matrix[currentRow][i] = matrix[currentRow - 1][i];
	}
}

int checkForCurrentRow(const char matrix[][cols]) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] != -1)
				return i;
		}
	}
	return 0;
}

void resizeMatrix(char matrix[][cols], int currentRow) {
	int highestRow = checkForCurrentRow(matrix) - 1;
	for (int i = currentRow; i > highestRow; i--) {
		destroyRow(matrix, i);
		swapRows(matrix, i);
	}
}

void checkForFiledRow(char matrix[][cols], int currentRow, int& result)
{
	for (size_t i = 0; i < cols; i++) {
		if (matrix[currentRow][i] == -1)
			return;
	}
	resizeMatrix(matrix, currentRow);
	result += 10;
}

int checkForRow(const char matrix[][cols], int userRow, int userCol, int colR) {
	int row = userRow + 1;

	for (row; row < rows; row++) {
		for (int i = userCol; i < colR; i++) {
			if (matrix[row][i] != -1)
				return row - 1;
		}
	}
	return rows - 1;
}

void dropBlock(char matrix[][cols], int userRow, int row, int userCol, int colR) {
	char ch = matrix[userRow][userCol];
	for (int i = userCol; i < colR; i++) {
		matrix[row][i] = ch;
		matrix[userRow][i] = -1;
	}
}

void fillingInEmptyPositions(char matrix[][cols], int currentRow, int& result) {
	currentRow -= 1;
	for (int i = rows - 2; i > currentRow - 1; i--) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] != -1) {
				int colR = rightEndOfBlock(matrix, j, i);
				colR += 1;
				if (i < rows - 1) {
					int row = checkForRow(matrix, i, j, colR);
					if (row != i) {
						dropBlock(matrix, i, row, j, colR);
						checkForFiledRow(matrix, row, result);
					}
				}
				j = colR -1;
			}
		}
	}
}

void generateNewRow(char matrix[][cols], int& result)
{
	int currRow = checkForCurrentRow(matrix);
	int availableSpace = cols - 1;
	char color = 'a';
	int currResult = result;
	while (true)
	{
		while (availableSpace)
		{
			int brickStartPosition = validRandomNumberForPosition(availableSpace);
			int sizeOfBrick = validRandomNumberForSize(availableSpace);
			if (sizeOfBrick <= brickStartPosition + 1)
			{
				availableSpace -= sizeOfBrick;
				filedMatrix(matrix, rows - 1, color, brickStartPosition, sizeOfBrick);
			}
		}
		fillingInEmptyPositions(matrix, currRow, result);
		if (currResult == result) {
			break;
			return;
		}
		else
			currResult = result;
	}
}

void changeBlockPosition(int userRow, int userCol, char direction,
						 int position, char matrix[][cols], int& result)
{
	int colR = rightEndOfBlock(matrix, userCol, userRow);
	if (direction == 'l') {
		changeBlockL(matrix, userRow, userCol, position, colR);
		userCol += 1;
		colR += 1;
	}
	else {
		changeBlockR(matrix, userRow, userCol, position, colR);
	}
	if (userRow < rows - 1) {
		int row = checkForRow(matrix, userRow, userCol, colR);
		if (row != userRow) {
			dropBlock(matrix, userRow, row, userCol, colR);
			checkForFiledRow(matrix, row, result);
		}
	}
	int currentRow = checkForCurrentRow(matrix);
	fillingInEmptyPositions(matrix, currentRow, result);
	checkForFiledRow(matrix, currentRow, result);
}

void playerCommands(int& userRow, int& userCol, char& playOrQuit, char& direction,
	int& position, char matrix[][cols], int& result)
{
	int currRow = checkForCurrentRow(matrix);

	cout << endl << "Play, quit or continue" << endl << "Enter: 'p' to play, 'q' to quit or 'c' to continue:";
	playOrQuit = validInputForPlayOrQuit('p', 'q', 'c');
	if (playOrQuit == 'p') {
		printMatrix(matrix, result);
		validRowColDirectionPosition(userCol, userRow, matrix, direction, position);
		changeBlockPosition(userRow, userCol, direction, position, matrix, result);
	}
}

void swaps(char matrix[][cols], int currentRow) {
	for (size_t i = 0; i < cols; i++) {
		matrix[currentRow - 1][i] = matrix[currentRow][i];
	}
}

void displacements(char matrix[][cols]) {
	int highestRow = checkForCurrentRow(matrix);
	for (int i = highestRow; i < rows; i++) {
		swaps(matrix, i);
	}
	destroyRow(matrix, rows - 1);
}

void deleteMatrix(char matrix[][cols]) {
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i][j] = -1;
		}
	}
}

void generatePlayZone(char matrix[][cols])
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i][j] = -1;
		}
	}
}

void ofStream(int result) {
	ofstream outputFile("account.txt");

	if (outputFile.is_open()) {
		outputFile << result;
		outputFile.close();
	}
	else {
		cerr;
	}
}

bool quit(char ch, int result, int bestResult) {
	if (ch == 'q') {
		if (result > bestResult)
			ofStream(result);
		return true;
	}
	return false;
}

void login() {

	ofstream outputFile("account.txt");
	if (outputFile.is_open()) {
		cout << "Enter your account:";
		char str[account];
		cin.getline(str, account);
		outputFile << str;
		outputFile.close();
	}
	else {
		cerr;
	}
}

void gameOver(char matrix[][cols], int& result, char& ch, int& bestResult) {
	printMatrix(matrix, result);
	cout << "Game over";
	cout << endl << "Play or quit" << endl << "Enter: 'n' to new game or 'q' to quit:";
	ch = validInput('n', 'q');
	if (ch == 'n') {
		result = 0;
		deleteMatrix(matrix);
		printMatrix(matrix, result);
		generateNewRow(matrix, result);
		printMatrix(matrix, result);
		if (result > bestResult) {
			ofStream(result);
			bestResult = result;
		}
	}
}

void play(char matrix[][cols])
{
	login();
	generatePlayZone(matrix);
	printMatrix(matrix, 0);
	int bestResult = 0;
	int userRow = 0;
	int userCol = 0;
	int position = 0;
	int result = 0;
	int currentRow = rows - 1;
	char playOrQuit;
	char direction;
	char ch;
	generateNewRow(matrix, result);
	while (true) 
	{
		currentRow = checkForCurrentRow(matrix);
		playerCommands(userRow, userCol, playOrQuit, direction, position, matrix, result);
		if (quit(playOrQuit, result, bestResult))
			break;
		fillingInEmptyPositions(matrix, currentRow, result);
		printMatrix(matrix, result);
		displacements(matrix);
		generateNewRow(matrix, result);
		currentRow = checkForCurrentRow(matrix);
		if (currentRow == 0){
			gameOver(matrix, result, ch, bestResult);
			if (quit(ch, result, bestResult))
				break;
		}
	}
}

int main()
{
	srand(time(0));
	char matrix[rows][cols];
	play(matrix);
}
