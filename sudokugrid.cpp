// sudokugrid.cpp
// CIAN SCANNELL, 10/13/2014

#include "sudokugrid.h"
#include "gridio.h"
using namespace std;

// IMPLEMENT CONSTRUCTOR AND 7 MEMBER FUNCTIONS AS SPECIFIED IN "sudokugrid.h"

SudokuGrid::SudokuGrid(const int problem[9][9]) {
    for( int i = 0 ; i <= 8 ; i++) {
        for(int j = 0 ; j <= 8 ; j++) {
            array[i][j].number = problem[i][j];
	    if( array[i][j].number > 0)
	      array[i][j].fixed = true;
	    else
	      array[i][j].fixed = false;
            if( problem[i][j] < 0 || problem[i][j] > 9)
	      throw GridException(DATA);	   
}
}
}


int SudokuGrid::getNumber(int row, int column) const {
    if( row < 0 || row > 8 || column < 0 || column > 8)
         throw GridException(INDEX);
    else   
         return array[row][column].number;
}


void SudokuGrid::setNumber(int number, int row, int column) {
     if( number < 0 || number > 9 )
     	 throw GridException(DATA);
     else if( row < 0 || row > 8 || column < 0 || column > 8)
         throw GridException(INDEX);
     else if( array[row][column].fixed == true )
     	 throw GridException(RULE);
     else
	 array[row][column].number = number;
}
	  

bool SudokuGrid::occursInRow(int number, int row) const {
     if( row < 0 || row > 8)
     	 throw GridException(INDEX);
     for( int i = 0 ; i <= 8 ; i++) {
         if( array[row][i].number == number)
             return true;        
     }
             return false;            
}


bool SudokuGrid::occursInColumn(int number, int column) const {
      if ( column < 0 || column > 8)
	throw GridException(INDEX);
      for( int i = 0 ; i <= 8 ; i++) {
        if( array[i][column].number == number )
            return true;           
      }
            return false;
}


bool SudokuGrid::occursInBox(int number, int row, int column) const { 
      int r, c;
      if( column < 0 || column > 8 || row < 0 || row > 8)
	throw GridException(INDEX);
      if( row == 0 || row == 1 || row == 2)
          r = 0;
      else if ( row == 3 || row == 4 || row == 5)
          r = 3; 
      else
          r = 6;

      if( column == 0 || column == 1 || column == 2)
          c = 0;
      else if ( column == 3 || column == 4 || column == 5)
          c = 3;
      else 
          c = 6;


       for(int i = r ; i <= r+2 ; i++) {
          for( int j = c ; j <= c+2 ; j++) {
                if( array[i][j].number == number )
                    return true;
	  }
       }
                    return false;
}

bool SudokuGrid::isCandidate(int number, int row, int column) const {
     if( row < 0 || row > 8 || column < 0 || column > 8)
         throw GridException(INDEX);
     else if( occursInRow(number,row) == false && occursInColumn(number,column) == false && occursInBox(number,row,column) ==false && number > 0 && number < 10)
          return true;
     else
         return false;
}


bool SudokuGrid::isSolved() const {
  int count = 0;
  for(int n = 1 ; n <=9 ; n++) {
    for(int i = 0; i <=8 ; i++) {
      if(occursInRow(n,i) == true)
	count++;
    }
    for(int j = 0; j <= 8; j++) {
      if(occursInColumn(n,j) == true)
	count++;
    }
    for(int i = 0; i <=8 ; i+=3) {
      for(int j = 0; j<=8; j+=3) {
	if(occursInBox(n,i,j) == true)
	  count++;
      }
    }
  }
    if(count == 243)
      return true;
    else
      return false;
}
