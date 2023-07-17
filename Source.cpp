#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h>
using namespace std;


void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
struct position {
	int ri, ci;

};
void init(char**& b, int& dim, string pname[], int& turn) {
	ifstream in("Text.txt");
	in >> dim;
	b = new char* [dim];
	for (int r = 0; r < dim; r++) {
		b[r] = new char[dim];
	}
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
			in >> b[r][c];

		}
	}
	for (int i = 0; i < 2; i++) {
		cout << "Enter player name : ";
		cin >> pname[i];
	}
	turn = 1;


}
void drawbox(int sr, int sc, int brow, int bcol, char sym) {
    for (int r = 0; r <= brow; r++) {
		for (int c = 0; c <= bcol; c++) {
			if ((r==0 || c ==0 || c ==(bcol) || r==(brow)) || r==c )
			{
				SetClr(5);
				gotoRowCol(sr+r, sc+c);
				cout << sym;
			}
			
		}

	}
}
void drawbox1(int sr, int sc, int brow, int bcol, char sym) {
	for (int r = 0; r <= brow; r++) {
		for (int c = 0; c <= bcol; c++) {
			if ((r == 0 || c == 0 || c == (bcol) || r == (brow)) || r + c == brow) {
				gotoRowCol(sr + r, sc + c);
				cout << sym;
			}
		}

	}
}
void drawbox2(int sr, int sc, int brow, int bcol, char sym) {
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			
			if (sym == 'o') {
				if (r == ceil((brow - brow) / 5) && c == ceil((bcol - 1) / 5) )
				{
					SetClr(6);
					gotoRowCol(sr + r, sc + c - 1);
					cout << sym;
				}
			}
			else if (sym == '-') {
				if (r == ceil((brow - brow)) && c == ceil((bcol - bcol)))
				{
					SetClr(7);
					gotoRowCol(sr + r, sc);
					cout << sym;
				}
			}
			else {
				if (r == ceil((brow - brow)) && c == ceil((bcol - bcol)))
				{   
					SetClr(3);
					gotoRowCol(sr + r, sc);
					cout << sym;
				}
			}
			
		}

	}
}

void print(int dim, int brow, int bcol, char** b) {
	int i = 4,rr=0;
	int h = brow;
	int w = bcol;
	for (int r = 0; r < h; r++) {
		for (int c = 0; c < w; c++) {

			if (r == 0 || c == 0 || r == h - 1 || c == w - 1 || r == h / 4 || c == w / 4
				|| r == h / 2 || c == w / 2 || r == 3 * h / 4 || c == 3 * w / 4 || r == c || 
				c == (w - r) - 1 || c == (w/2 - r) - 1 || r == ((h+h/2)-c)-1 || r == ((h - h / 2) + c) - 1
				||  c == ((w - w / 2) + r) - 1) 
			{

				cout << char(-37);
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	
}
void printbox1(int dim, int brow, int bcol, char** b) {
	system("cls");
	for (int r = 0; r < dim-1; r++) {
		for (int c = 0; c < dim-1; c++) {

			if ((r+c)%2==0) {
				drawbox(r * brow, c * bcol, brow, bcol, char(-37));
			
			}
			else {
				drawbox1(r * brow, c * bcol, brow, bcol, char(-37));
				
			}

		}
	}
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {

			if ((r + c) % 2 == 0) {
				drawbox2(r * brow, c * bcol, brow, bcol, b[r][c]);
			}
			else {
				drawbox2(r * brow, c * bcol, brow, bcol, b[r][c]);
			}

		}
	}
	
}
void turnMsg(string pname) {
	cout << pname << "'s turn : " << endl;
}

void turnchange(int& turn) {
	turn = (turn + 1) % 2;
}
void updateboard(char**& b, position& sc, position& dc) {
	char p = b[sc.ri][sc.ci];
	b[dc.ri][dc.ci] = p;
	b[sc.ri][sc.ci] = '-';
}
void selectPosition(position& p, int dim) {
	
	cout << "Enter coordinates: (A1:E5): " << endl;
	char c;
	int d;
	cin >> c>>d;
	c = toupper(c);
	p.ri = d - 1;
	p.ci = c - 'A'; 
	/*
	int x, y;
	getRowColbyLeftClick(x, y);
	p.ri = x / dim;
	p.ci = y / dim;
	*/
}
bool upperPlayer(char sym) {
	return sym == 'o';
}
bool lowerPlayer(char sym) {
	return sym == 'O';
}
bool ismypiece(char sym, int turn) {
	if (turn == 0) {
		return upperPlayer(sym);
	}
	else {
		return lowerPlayer(sym);
	}
}
bool isvalidsi(char** b, int dim, position si, int turn) {
	if (si.ri < 0 || si.ri >= dim || si.ci < 0 || si.ci >= dim) {
		return false;
	}
	return ismypiece(b[si.ri][si.ci], turn);
}
bool isvaliddc(char** b, int dim, position dc, int turn) {
	if (dc.ri < 0 || dc.ri >= dim || dc.ci < 0 || dc.ci >= dim) {
		return false;
	}
	return !ismypiece(b[dc.ri][dc.ci], turn);
}

bool win(char**b,position dc,int turn) {

	if (turn == 1) {
		if (b[dc.ri + 1][dc.ci] == 'o') {
			return true;
		}
	}
	else {
		if (b[dc.ri - 1][dc.ci] == 'O') {
			return true;
		}
	}
	return false;
}
void updateboard1(char**& b, position& sc, position& dc) {
	char p = b[sc.ri][sc.ci];
	b[dc.ri][dc.ci] = p;
	b[dc.ri-1][dc.ci] = '-';
}
void updateboard2(char**& b, position& sc, position& dc) {
	char p = b[sc.ri][sc.ci];
	b[dc.ri][dc.ci] = p;
	b[dc.ri + 1][dc.ci] = '-';
}
void updateboard3(char**& b, position& sc, position& dc) {
	char p = b[sc.ri][sc.ci];
	b[dc.ri][dc.ci] = p;
	b[sc.ri - 1][sc.ci-1] = '-';
}
void updateboard4(char**& b, position& sc, position& dc) {
	char p = b[sc.ri][sc.ci];
	b[dc.ri][dc.ci] = p;
	b[sc.ri ][sc.ci + 1] = '-';
}

void copyUpdateboard(char**& b, position& sc, position& dc) {
	int r = abs(sc.ri - dc.ri);
	int c = abs(sc.ci - dc.ci);
	int ci = (sc.ci - dc.ci);

	if (sc.ri > dc.ri && c == 2) {
		updateboard3(b, sc, dc);
	}
	else if (sc.ri < dc.ri) {
		updateboard1(b, sc, dc);
	}
	else if (sc.ri > dc.ri ) {
		updateboard2(b, sc, dc);
	}
	else if (sc.ri == dc.ri && c == 2) {
		updateboard4(b, sc, dc);

	}
	
}
int main() {
	

	char** b;
	string pname[20];
	int dim = 0, nop = 2, turn = 0,wincount = 0;
 	position sc, dc;
	init(b, dim, pname, turn);
	//print(50,50,5,50,50,b);

	printbox1(dim, 10, 10, b);
	_getch();
	cout << endl;

	while (true) {
		turnMsg(pname[turn]);
		do {
			do {
				cout << "source: " << endl;
				selectPosition(sc, dim);
			} while (!isvalidsi(b, dim, sc, turn));
			cout << "dest: " << endl;
			selectPosition(dc, dim);

		} while (!isvaliddc(b, dim, dc, turn));
		if (win(b,dc,turn) == true) {
			copyUpdateboard(b, sc, dc);
		}
	updateboard(b, sc, dc);
	printbox1(dim, 10, 10, b);

	turnchange(turn);
	cout << endl;

	}
	return 0;
}