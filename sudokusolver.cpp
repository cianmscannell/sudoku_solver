// sudokusolver.cpp
// CIAN SCANNELL , 10/15/2014
#include <iostream>
using namespace std;

#include "sudokugrid.h"
#include "gridio.h"

// mandatory function to define below main:
void solve(SudokuGrid &);

// do not change main
int main() {
    int problem[9][9];

    if ( !getProblem(problem) ) {
        cout << "bad input grid; terminating" << endl;
        return 1;
    }

    try {
        SudokuGrid grid(problem); // object, not pointer this time

        cout << "Problem:" << endl;
        display(&grid);           // so pass address to display
        cout << endl;

        solve(grid);

        if (grid.isSolved())
            cout << "Success! Solution:" << endl;
        else
            cout << "Not successful. Best effort:" << endl;

        display(&grid);
    }

    catch(GridException e) {
        cout << "exception: " << e << endl;
    }

    return 0;
}

// attempt to solve the problem using simple logic rules
void solve(SudokuGrid &grid) {

    // TYPE (MOST OR ALL OF) YOUR SOLUTION HERE
    // DECLARE UTILITY FUNCTIONS (IF ANY) HERE OR ABOVE, BUT DEFINE THEM BELOW
    bool solved = false;
    bool changed = true;
    int count = 0;
    int cand; // dummy variable holds candidates for a particular space


    while(!solved && changed){
      changed = false;
      for (int  i=0 ; i <= 8 ; i++ ) {
    	   for (int j = 0 ; j  <= 8 ; j++ ) {
           count = 0;
	          if(grid.getNumber(i,j) == 0) {
	             for (int n=1 ; n <= 9 ; n++ ) {
	    	           if( grid.isCandidate(n,i,j) == true ){
		                   cand = n;
		                   ++count;
                     }
                   }
		           if (count == 1 ) {
		               grid.setNumber(cand,i,j);
                   changed = true;
               }
	          }
	        }
      }
      solved = grid.isSolved();
    }
}
