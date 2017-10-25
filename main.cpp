/*
 * main.cpp
 *
 *  Created on: 11 Kas 2014
 *      Author: Guner
 */

#include <iostream>
#include "GameOfLife.h"
#include "Cell.h"
using namespace std;
using namespace hw06;

void test1(Cell &c1,Cell &c2);
void test2(GameOfLife &game1,GameOfLife &game2);

int GameOfLife::_allLiving=0;
int main()
{
	int enter;
	Cell c1,c2;
	test1(c1,c2);
	cout << "------------------------\n";
	cout << "------------------------\n";
	cout << "enter any integer\n";
	cin >> enter;
	cout << "operator test,GameOfLife operators\n";
	cout << "creating a game with 3.txt\n";
	GameOfLife game1,game2;
	if(0==game1.readFile("3.txt"))
	{
		cout <<"file cannot open!(3.txt)\n";
		return 1;
	}
	if(0==game2.readFile("2.txt"))
	{
		cout <<"file cannot open!(2.txt)\n";
		return 1;
	}
	test2(game1,game2);

	return 0;
}

void test1(Cell &c1,Cell &c2)
{
	cout << "operator test,Cell operators\n";
	cout << "create two cells\nfirst cell\n";
	cin >> c1;
	cout << "second cell\n";
	cin >> c2;
	cout << "testing \"" << c1 << ">" << c2 << "\"=";
	bool a=c1>c2;
	cout << a<< endl;
	cout << "testing \"" << c1 << "<" << c2 << "\"=";
	a=c1<c2;
	cout << a<< endl;
	cout << "testing \"" << c1 << ">=" << c2 << "\"=";
	a=c1>=c2;
	cout << a<< endl;
	cout << "testing \"" << c1 << "<=" << c2 << "\"=";
	a=c1<=c2;
	cout << a<< endl;
	cout << "testing \"" << c1 << "==" << c2 << "\"=";
	a=c1==c2;
	cout << a<< endl;
	cout << "testing \"" << c1 << "!=" << c2 << "\"=";
	a=c1!=c2;
	cout << a<< endl;
	cout << "end of cell test\n";
}


void test2(GameOfLife &game1,GameOfLife &game2)
{
	int select;
	do
	{
		cout << "Game Test Menu\n1.Print Game with \"<<\" operator\n2.play game"
			 <<"with \"game++\" operator\n3.play game with \"++game\" operator"
			 <<"\n4.undo game with \"--game\" operator\n5.undo game with"
			 <<"\"game--\" operator\n6.add cell into game with \"+\" operator"
			 <<"\n7.remove cell into game with \"-\" operator\n8.add game into"
			 <<"game with game+game operator\n9.subtraction game from game with"
			 <<" game-game operator\n10.return cell with [] operator\n11.return"
			 <<" cell with () operator\n12.merger games return itself with +="
			 <<" operator\n13.Write current game to file\n0.Exit\nPlease enter "
			 <<"number for testing game\n\n";
		cin >> select;
		if(select==1)
		{
			cout << "your choice is << !\n";
			cout << game1;
		}
		else if(select==2)
		{
			cout << "your choice is game++ !\n";
			cout <<"print1\n" << game1++ << "print2\n" << game1 << endl;
		}
		else if(select==3)
		{
			cout << "your choice is ++game !\n";
			cout <<"print1\n" << game1++ << "print2\n" << game1 << endl;
		}
		else if(select==4)
		{
			cout << "your choice is --game !\n";
			cout <<"print1\n" << --game1 << "print2\n" << game1 << endl;
		}
		else if(select==5)
		{
			cout << "your choice is game-- !\n";
			cout <<"print1\n" << game1-- << "print2\n" << game1 << endl;
		}
		else if(select==6)
		{
			Cell c1;
			cout << "your choice is game+cell !\n";
			cin >> c1;
			cout <<"print1\n" << game1 << "print2\n" << game1+c1 << endl;
		}
		else if(select==7)
		{
			Cell c1;
			cout << "your choice is game-cell !\n";
			cin >> c1;
			cout <<"print1\n" << game1 << "print2\n" << game1-c1 << endl;
		}
		else if(select==8)
		{
			cout << "your choice is game+game !\n";
			cout << "print first game\n" << game1 << "print second game\n"
				 << game2 << "after operation\n" << game1+game2;
		}
		else if(select==9)
		{
			cout << "your choice is game-game !\n";
			cout << "print first game\n" << game1 << "print second game\n"
				 << game2 << "after operation\n" << game1-game2;
		}
		else if(select==10)
		{
			int x,y;
			cout << "your choice is game[][] !\n";
			cout << "enter x\n";
			cin >> x;
			cout << "enter y\n";
			cin >> y;
			cout << game1[x][y];
		}
		else if(select==11)
		{
			int x,y;
			cout << "your choice is game() !\n";
			cout << "enter x\n";
			cin >> x;
			cout << "enter y\n";
			cin >> y;
			cout << game1(x,y);
		}
		else if(select==12)
		{
			cout << "your choice is +=";
			cout << "print first game\n" << game1 << "print second game\n"
				 << game2;
			game1+=game2;
			cout << "print first after operation\n" << game1;
		}
		else if(select==13)
		{
			cout << "write file\n please enter output name\n>>";
			char name[30];
			cin >> name;
			game1.writeFile(name);
			cout <<"game wrote\n";
		}
		else if(select==0)
		{
			cout << "exit!\n";
		}
		else
		{
			cout << "you enter wrong number!\n";
		}
	}
	while(select!=0);
}
