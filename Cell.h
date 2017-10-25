/*
 * Cell.h
 *
 *  Created on: 11 Kas 2014
 *      Author: Guner
 */
#include <iostream>
using namespace std;
#ifndef CELL_H_
#define CELL_H_
namespace hw06{

class Cell {
public:
	Cell(){setX(0),setY(0);}/*default constructor*/
	Cell(int a){setX(a),setY(0);}/*one parameter constructor*/
	Cell(int a,int b){setX(a),setY(b);}/*two parameter constructor*/
	inline int getX()const{return x;}/*return x*/
	inline int getY()const{return y;}/*return y*/
	bool operator<(Cell const &c1)const;
	bool operator>(Cell const &c1)const;
	bool operator>=(Cell const &c1)const;
	bool operator<=(Cell const &c1)const;
	bool operator==(Cell const &c1)const;
	bool operator!=(Cell const &c1)const;
	Cell operator++();
	Cell operator++(int);
	friend istream& operator >>(istream& inputStream,Cell& c1);
	friend ostream& operator <<(ostream& outputStream,const Cell &c1);

	inline void setX(int a){x=a;}/*set x*/
	inline void setY(int b){y=b;}/*set y*/
private:
	int x;
	int y;
};
}
#endif /* CELL_H_ */
