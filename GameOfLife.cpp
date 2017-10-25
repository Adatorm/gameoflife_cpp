/*
 * GameOfLife.cpp
 *
 *  Created on: 11 Kas 2014
 *      Author: Guner
 */

#include <iostream>
#include <cstdio>/*read file,write file=fopen,fclose,fscanf and fprintf*/
using namespace std;
#include "GameOfLife.h"
#include "Cell.h"
namespace hw06{
GameOfLife::GameOfLife() {
	_height = 0;
	_width = 0;
	min_width = 0;
	min_height = 0;
	_capacity=0;
	_step=0;
	save=NULL;
	temp_livingCells=NULL;
	livingCells=NULL;
	saveCap=NULL;
}

GameOfLife::GameOfLife(const GameOfLife &game){
	_capacity=game._capacity;
	_step=game._step;
	_width=game._width;
	_height=game._height;
	min_width=game.min_width;
	min_height=game.min_height;
	livingCells=new Cell[game._capacity];/*allocate new livingCells*/
	save=new Cell*[game._step];
	for(int i=0;i<_step;++i)/*allocate new save 2D array*/
		save[i]=new Cell[_capacity];
	saveCap=new int[_step];/*allocate saved game's cap*/

	for(int i=0;i<_capacity;++i)/*copy livingCells*/
		livingCells[i]=game.livingCells[i];
	for(int i=0;i<_step;++i)/*copy saved games*/
		for(int j=0;j<_capacity;++j)
			save[i][j]=game.save[i][j];
	for(int i=0;i<_step;++i)
		saveCap[i]=game.saveCap[i];
	temp_livingCells=NULL;
	_allLiving=_allLiving+_capacity;
}

GameOfLife::~GameOfLife(){
	delete [] livingCells;/*delete old livingCells*/
	for(int i=0;i<_step;++i)/*delete game's saves.*/
		delete [] save[i];
	delete [] save;
	delete []saveCap;/*delete game's save's cap*/
	save=NULL;
	livingCells=NULL;
	saveCap=NULL;
	_allLiving=_allLiving-_capacity;
}

int GameOfLife::readFile(const char *fileName) {
	FILE* inp;
	int cell;/*cell,1 meaning alive,0 dead*/
	int counter=0;/*livingCells array index*/
	inp = fopen(fileName, "r");
	if (inp == NULL)
		return 0;/*if file does not exist*/
	fscanf(inp, "%d%d", &_height, &_width);/*read table dimension*/
	for (int i = 1; i <= getHeight(); ++i)
		for (int j = 1; j <= getWidth(); ++j) {
			fscanf(inp, "%d", &cell);
			if (cell == 1)/*if cell is living,add to livingCells*/
			{
				setLivingCells(_capacity+1);
				livingCells[counter]=Cell(i,j);
				++counter;
			}
		}
	fclose(inp);/*close file*/
	_allLiving = _allLiving + _capacity;
	setSave(_step+1);
		for(int i=0;i<_capacity;++i)
			save[_step-1][i]=livingCells[i];
	shirink();
	return 1;
}

void GameOfLife::writeFile(const char *fileName) const {
	FILE *outp;
	outp = fopen(fileName, "w");
	fprintf(outp, "%d %dcapa-%d\n", getHeight() - getMinHeight() + 1,
			getWidth() - getMinWidth() + 1,_capacity);
	for (int i = getMinHeight(); i <= getHeight(); ++i) {
		for (int j = getMinWidth(); j <= getWidth(); ++j) {
			if (checkCell(i, j) == 1)
				fprintf(outp, "%d ", 1);
			else
				fprintf(outp, "%d ", 0);
		}
		fprintf(outp, "\n");
	}
	fclose(outp);
}

void GameOfLife::setLivingCells(int cap){
	if(_capacity==0)
	{
		delete [] livingCells;
		livingCells=new Cell [cap];
		_capacity=cap;
	}
	else
	{
		int size;
		if(cap<_capacity)
			size=cap;
		else
			size=_capacity;
		Cell *temp=new Cell[cap];
		for(int i=0;i<size;++i)
			temp[i]=livingCells[i];
		delete [] livingCells;
		livingCells=temp;
		_capacity=cap;
	}
}

void GameOfLife::setLivingCells(int cap,int index){
	if(_capacity==0)
	{
		delete [] livingCells;
		livingCells=new Cell [cap];
		_capacity=cap;
	}
	else
	{
		int size;
		if(cap<_capacity)
		{
			size=cap;
			Cell *temp=new Cell[cap];
			int j=0;
			for(int i=0;i<size;++i)
			{
				if(j==index)
					--j;
				temp[i]=livingCells[j];
				++j;
			}
		}
		else
			size=_capacity;
		Cell *temp=new Cell[cap];
		for(int i=0;i<size;++i)
			temp[i]=livingCells[i];
		delete [] livingCells;
		livingCells=temp;
		_capacity=cap;
	}
}

void GameOfLife::setSave(int cp){
	if(_step==0)
	{
		save=new Cell*[cp];
		for(int i=0;i<cp;++i)
			save[i]=new Cell[_capacity];
		saveCap=new int[cp];
		saveCap[cp-1]=_capacity;
		_step=cp;
	}
	else
	{
		int size;
		if(cp<_step)
			size=cp;
		else
			size=_step;
		int *tempCap=new int[cp];
		for(int i=0;i<size;++i)
			tempCap[i]=saveCap[i];
		Cell **temp=new Cell*[cp];
		for(int i=0;i<cp;++i)
			temp[i]=new Cell[_capacity];
		for(int i=0;i<size;++i)
			for(int j=0;j<_capacity;++j)
				temp[i][j]=save[i][j];
		for(int i=0;i<_step;++i)
			delete [] save[i];
		delete [] save;
		delete [] saveCap;
		save=temp;
		saveCap=tempCap;
		_step=cp;
	}
}

void GameOfLife::setTempLiving(int cp){
	if(cp==1)
	{
		temp_livingCells=new Cell[cp];
	}
	else if(cp>1)
	{
		Cell *temp=new Cell[cp];
		for(int i=0;i<cp-1;++i)
			temp[i]=temp_livingCells[i];
		delete [] temp_livingCells;
		temp_livingCells=temp;
	}
}

void GameOfLife::printGame() const {
	cout << endl;

	for (int i = getMinHeight(); i <= getHeight(); ++i)
		cout << "- ";
	cout << endl;

	for (int i = getMinHeight(); i <= getHeight(); ++i) {
		for (int j = getMinWidth(); j <= getWidth(); ++j) {
			if (checkCell(i, j) == 1)
				cout << "x ";
			else
				cout << "  ";
		}
		cout << "|";
	}
	for (int i = getMinWidth(); i <= getWidth(); ++i)
		cout << "- ";
	cout << endl;
}

void GameOfLife::play() {
	int counter=0;
	for (int i = getMinHeight() - 1; i <= getHeight() + 1; ++i)
		for (int j = getMinWidth() - 1; j <= getWidth() + 1; ++j)
			if (checkNeighbors(i, j) == 1
			|| (checkNeighbors(i, j) == 2 && checkCell(i, j) == 1)) {
				setTempLiving(counter+1);
				temp_livingCells[counter]=(Cell(i, j));
				++counter;
			}
	_allLiving = _allLiving - _capacity;
	setLivingCells(counter);
	for (int i = 0; i < counter; ++i)/*copy temp*/
		livingCells[i]=temp_livingCells[i];
	_allLiving = _allLiving + counter;
	setSave(_step+1);
	for(int i=0;i<counter;++i)/*save game*/
		save[_step-1][i]=livingCells[i];
	shirink();/*recalculate sizes*/
	_capacity=counter;
	saveCap[_step-1]=_capacity;/*add livingcells number*/
}

int GameOfLife::checkCell(int coorX, int coorY) const {
	if (coorX > getHeight() + 1 || coorX < getMinHeight() - 1
			|| coorY > getWidth() + 1 || coorY < getMinWidth() - 1)
		return -1;/*out of range*/
	for (int i = 0; i < _capacity; ++i) {
		if (livingCells[i].getX() == coorX && livingCells[i].getY() == coorY)
			return 1;
	}
	return 0;
}

int GameOfLife::checkNeighbors(int x, int y) const {
	int liveCell = 0;/*number of living neighbors*/
	if (checkCell(x - 1, y - 1) != -1 && checkCell(x - 1, y - 1) == 1)/*upper left*/
		liveCell++;
	if (checkCell(x - 1, y) != -1 && checkCell(x - 1, y) == 1)/*up*/
		liveCell++;
	if (checkCell(x - 1, y + 1) != -1 && checkCell(x - 1, y + 1) == 1)/*upper right*/
		liveCell++;
	if (checkCell(x, y - 1) != -1 && checkCell(x, y - 1) == 1)/*left*/
		liveCell++;
	if (checkCell(x, y + 1) != -1 && checkCell(x, y + 1) == 1)/*right*/
		liveCell++;
	if (checkCell(x + 1, y - 1) != -1 && checkCell(x + 1, y - 1) == 1)/*bottom left*/
		liveCell++;
	if (checkCell(x + 1, y) != -1 && checkCell(x + 1, y) == 1)/*down*/
		liveCell++;
	if (checkCell(x + 1, y + 1) != -1 && checkCell(x + 1, y + 1) == 1)/*bottom right*/
		liveCell++;
	if (liveCell == 3)
		return 1;
	else if (liveCell == 2)
		return 2;
	return 0;
}

void GameOfLife::addOtherGame(const GameOfLife & other) {
	int counter=0;/*only calc adding new cells*/
	for (int i = 0; i < other._capacity; ++i)
	{
		if (checkCell(other.livingCells[i].getX(), other.livingCells[i].getY())!= 1)
		{
			setLivingCells(_capacity+1);
			livingCells[_capacity-1]=(Cell(other.livingCells[i].getX(),
									other.livingCells[i].getY()));
			++counter;

		}
	}
	_allLiving = _allLiving + counter;
	setSave(_step+1);
	for(int i=0;i<_capacity;++i)
		save[_step-1][i]=livingCells[i];
	shirink();
}

void GameOfLife::shirink() {
	int minH = 8000, minW = 8000, H = -8000, W = -8000;
	for (int i = 0; i < _capacity; ++i) {
		if (livingCells[i].getX() > H)
			H = livingCells[i].getX();
		if (livingCells[i].getX() < minH)
			minH = livingCells[i].getX();
		if (livingCells[i].getY() > W)
			W = livingCells[i].getY();
		if (livingCells[i].getY() < minW)
			minW = livingCells[i].getY();
	}
	setHeight(H);
	setWidth(W);
	setMinHeight(minH);
	setMinWidth(minW);

	for(int i=0;i<_capacity;++i)/*update,it fix Cell coor and sizes*/
		{
			livingCells[i]=Cell(livingCells[i].getX()-getMinHeight(),livingCells[i].getY()-getMinWidth());
		}
		setHeight(getHeight()-getMinHeight());
		setWidth(getWidth()-getMinWidth());
		setMinHeight(0);
		setMinWidth(0);
}

int GameOfLife::eraseCell(const Cell &cell){
	int status=0;
	for (int i = 0; i < _capacity; ++i)
		if (livingCells[i].getY() == cell.getY()
				&& livingCells[i].getX() == cell.getX()){

			setLivingCells(_capacity-1,i);
			--_allLiving;
			status=1;
			break;
		}
	if(status!=1)
		return 0;
	shirink();
	return 1;
}

void GameOfLife::printDim() const {
	cout << endl << getHeight() - getMinHeight() + 1 << "x"
			<< getWidth() - getMinWidth() + 1 << endl;
}

GameOfLife & GameOfLife::operator=(const GameOfLife & game){
	delete [] livingCells;/*delete old livingCells*/
	for(int i=0;i<_step;++i)/*delete game's saves.*/
		delete [] save[i];
	delete [] save;
	delete [] saveCap;
	_allLiving=_allLiving-_capacity;

	_capacity=game._capacity;
	_step=game._step;
	_width=game._width;
	_height=game._height;
	min_width=game.min_width;
	min_height=game.min_height;
	livingCells=new Cell[game._capacity];/*allocate new livingCells*/
	save=new Cell*[game._step];
	for(int i=0;i<_step;++i)/*allocate new save 2D array*/
		save[i]=new Cell[_capacity];
	saveCap=new int[game._step];/*allocate new save games cap array*/
	for(int i=0;i<_capacity;++i)
		livingCells[i]=game.livingCells[i];
	for(int i=0;i<_step;++i)
		for(int j=0;j<_capacity;++j)
			save[i][j]=game.save[i][j];
	for(int i=0;i<_step;++i)
		saveCap[i]=game.saveCap[i];
	temp_livingCells=NULL;
	_allLiving=_allLiving+_capacity;
	return *this;
}

GameOfLife GameOfLife::operator ++() {
	play();
	return *this;
}

GameOfLife GameOfLife::operator ++(int) {
	GameOfLife temp=*this;
	play();
	return temp;
}

GameOfLife GameOfLife::operator --() {
	setSave(_step-1);
	_allLiving = _allLiving - _capacity;

	setLivingCells(saveCap[_step-1]);
	_capacity=saveCap[_step-1];
	for(int i=0;i<_capacity;++i)
		livingCells[i]=save[_step-1][i];
	_allLiving = _allLiving + _capacity;
	shirink();
	return *this;
}

GameOfLife GameOfLife::operator --(int) {
	GameOfLife game = *this;
	setSave(_step-1);
	_allLiving = _allLiving - _capacity;
	setLivingCells(saveCap[_step-1]);
	_capacity=saveCap[_step-1];
	for(int i=0;i<_capacity;++i)
		livingCells[i]=save[_step-1][i];
	_allLiving = _allLiving + _capacity;
	shirink();
	return game;
}

GameOfLife GameOfLife::operator +(const Cell &cell) {
	GameOfLife temp=*this;
	Cell cellTemp(cell.getX(),cell.getY());
	if (checkCell(cellTemp.getX(), cellTemp.getY()) != 1) {
		temp.setLivingCells(_capacity+1);
		temp.livingCells[_capacity-1]=cell;
		_allLiving++;
		temp.setSave(_step+1);
		for(int i=0;i<_capacity;++i)
		{
			temp.save[_step-1][i]=temp.livingCells[i];
		}
	}
	temp.shirink();
	return temp;
}

GameOfLife GameOfLife::operator -(const Cell &cell) {
	GameOfLife temp=*this;
	temp.eraseCell(cell);
	return temp;
}

GameOfLife GameOfLife::operator +(const GameOfLife &game) {
	GameOfLife temp=*this;
	temp.addOtherGame(game);
	return temp;
}

GameOfLife GameOfLife::operator -(const GameOfLife &game){
	GameOfLife temp=*this;
	for(int i=0;i<temp._capacity;++i)
	{
		if(temp.checkCell(game.livingCells[i].getX(),
							game.livingCells[i].getY())==1)
		{
			temp.eraseCell(game.livingCells[i]);
		}
	}
	return temp;
}

Cell GameOfLife::operator [](int index)const{
	for (int i = 0; i < _capacity; ++i) {
			if (livingCells[i].getY() == index) {
				return livingCells[i];
			}
	}
	return Cell(-1000, -1000);
}

const GameOfLife GameOfLife::operator [](int index){
	GameOfLife temp;

	for (int i = 0; i < _capacity ; ++i) {
		if (livingCells[i].getX() == index) {
			temp = temp + livingCells[i] ;
		}
	}
	return temp;
}

Cell GameOfLife::operator()(int x,int y){
	return (*this)[x][y];
}

GameOfLife GameOfLife::operator +=(const GameOfLife game){
	GameOfLife temp=*this;
	addOtherGame(game);
	return *this;
}

ostream& operator <<(ostream &outputStream,const GameOfLife &game){
	outputStream << endl;

	for (int i = game.getMinHeight(); i <= game.getHeight(); ++i)
		outputStream << "- ";
	outputStream << endl;
	for (int i = game.getMinHeight(); i <= game.getHeight(); ++i) {
		for (int j = game.getMinWidth(); j <= game.getWidth(); ++j) {
			if (game.checkCell(i, j) == 1)
				outputStream << "x ";
			else
				outputStream << "  ";
		}
		outputStream << "|" << endl;
	}
	for (int i = game.getMinHeight(); i <= game.getHeight(); ++i)
		outputStream << "- ";
	cout << endl;
	return outputStream;
}

}/*namespaces hw06*/
