//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <math.h>
#include "BitArray2D.hpp"
#include "common.hpp"



BitArray2D::BitArray2D(unsigned int rows, unsigned int columns) {

  if(rows == 0 or columns == 0){
    throw BitArray2DException("Wrong");
  }
  this -> columns = columns;
  this -> rows = rows;
  array = (char*)calloc(rows*columns, sizeof(char));
  //array = "0010001001010101";

  //calloc(100,100);

  //array = &array[rows * columns];
  //typedef char memoryBitBoard[columns];
  //memoryBitBoard BitBoard[rows];

  //*array = *BitBoard;
  //A[Row][Column]
  //&A[i][j] = Xa + L(C * i + j)

}


BitArray2D::~BitArray2D() {
  //Deallocate Memory
  //Don't Touch
}


bool BitArray2D::get(unsigned int row, unsigned int column){
   // check array bounds
  if(row < 0 or row >= BOARD_SIZE or column < 0 or column >= BOARD_SIZE){
    throw BitArray2DException("Wrong");
  }

   // get the element
   return get_bit_elem(array, columns, row, column);

}



void BitArray2D::set(unsigned int row, unsigned int column){
   // check array bounds
  if(row < 0 or row >= BOARD_SIZE or column < 0 or column >= BOARD_SIZE){
    throw BitArray2DException("Wrong");
  }

   // set the element
   set_bit_elem(array, columns, row, column);
}
