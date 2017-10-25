/*
 * GameOfLife.h
 *
 *  Created on: 11 Kas 2014
 *      Author: Guner
 */

#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_
using namespace std;
#include "Cell.h"
namespace hw06{
class GameOfLife {
public:
	GameOfLife();/*Default constructor*/
	GameOfLife(const GameOfLife &newGame);/*copy constructor*/
    ~GameOfLife();/*destructor*/
	int readFile(const char *fileName);
	void writeFile(const char *fileName) const;
	inline int getWidth() const {return _width;}
	inline int getHeight() const {return _height;}
	inline int getMinWidth() const {return min_width;}
	inline int getMinHeight() const {return min_height;}
	inline void setMinWidth(int a) {min_width = a;}
	inline void setMinHeight(int b) {min_height = b;}
	inline void setHeight(int q) {_height = q;}
	inline void setWidth(int w) {_width = w;}

	void setLivingCells(int cap);/*resize livingCells array*/
	void setLivingCells(int cap,int index);/*overloading, index for deleting element*/
	void setSave(int capacity);/*resize game saves array*/
	void setTempLiving(int cp);/*resize temp_livingCells*/

	void copyGameArray(const GameOfLife & other);/*copy livingCells from other to this*/
	void printGame() const;
	void play();
	void addOtherGame(const GameOfLife & other);
	inline static int numberOfAllLivingCells() {return _allLiving;}
	void printDim() const;

	GameOfLife & operator=(const GameOfLife & game);/*assignment operator*/
	GameOfLife operator ++();/*operator play game prefix*/
	GameOfLife operator ++(int);/*operator play game postfix*/
	GameOfLife operator --();/*operator undo game prefix*/
	GameOfLife operator --(int);/*operator undo game postfix*/
	GameOfLife operator +(const Cell &cell);/*operator game+cell*/
	GameOfLife operator -(const Cell &cell);/*operator game-cell*/
	GameOfLife operator +(const GameOfLife &game);/*operator game+game*/
	GameOfLife operator -(const GameOfLife &game);/*operator game-game*/
	Cell operator [](int index)const;
	const GameOfLife operator [](int index);
	Cell operator()(int x,int y);
	GameOfLife operator +=(const GameOfLife game);
	friend ostream& operator <<(ostream &outputStream,const GameOfLife &game);

private:
	Cell *livingCells;/*living cells array*/
	Cell *temp_livingCells;/*temp living cells array*/
	Cell **save;
	int *saveCap;/*save cap list*/
	int _capacity;/*livingCells size*/
	int _step;/*number of saved game*/
	int _width;/*game max width coor*/
	int _height;/*game max height coor*/
	int min_width;/*game min width coor*/
	int min_height;/*game min height coor*/
	static int _allLiving;/*it hold all living cells in all games*/
	int checkCell(int coorX, int coorY) const;/*check cell in livingsCells*/
	int checkNeighbors(int coorX, int coorY) const;/*check surrounding cells*/
	void shirink();/*Shrink game*/
	int eraseCell(const Cell &cell);
	void renum();/*give new number to cells*/

};
}
#endif /* GAMEOFLIFE_H_ */
