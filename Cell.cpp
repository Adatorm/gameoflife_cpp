/*
 * Cell.cpp
 *
 *  Created on: 11 Kas 2014
 *      Author: Guner
 */
#include <iostream>
using namespace std;
#include "Cell.h"
namespace hw06{
bool Cell::operator<(Cell const &c1)const{
	if(getY()<c1.getY())
		return true;
	else if(getY()==c1.getY() && getX()<c1.getX())
		return true;
	else
		return false;
}

bool Cell::operator>(Cell const &c1)const{
	if(getY()>c1.getY())
			return true;
		else if(getY()==c1.getY() && getX()>c1.getX())
			return true;
		else
			return false;
}

bool Cell::operator>=(Cell const &c1)const{
	if(getY()>=c1.getY())
		return true;
	else
		return false;
}

bool Cell::operator<=(Cell const &c1)const{
	if(getY()<=c1.getY())
		return true;
	else
		return false;
}

bool Cell::operator==(Cell const &c1)const{
	if(getY()==c1.getY() && getX()==c1.getX())
		return true;
	else
		return false;
}

bool Cell::operator!=(Cell const &c1)const{
	if(getY()!=c1.getY() || getX()!=c1.getX())
		return true;
	else
		return false;
}

Cell Cell::operator++(){
	setX(getX()+1);
	setY(getY()+1);
	return *this;
}

Cell Cell::operator++(int ignoreMe){
	Cell temp(getX(),getY());
	++*this;
	return temp;
}

istream& operator >>(istream& inputStream,Cell&c1)
{
	int x,y;
	cout << "enter integer for x coor" << endl;
	inputStream >> x;
	cout << "enter integer for y coor" << endl;
	inputStream >> y;
	c1.setX(x);
	c1.setY(y);
return inputStream;
}

ostream& operator <<(ostream& outputStream,const Cell &c1){
	outputStream << "(" ;
	outputStream << c1.getX() ;
	outputStream << "," ;
	outputStream << c1.getY() ;
	outputStream << ")";
	return outputStream;
}

}
