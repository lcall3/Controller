//##########################################################################
//
// lcall3 Controller is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// lcall3 Controller is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with lcall3 Controller. If not, see <http://www.gnu.org/licenses/>.
//
//##########################################################################

// This is the header file that outlines all the functions that's required to
// communicate with the host computer
//
// Last edited: 2018-03-27
// Contributor: Muchen He

#ifndef communicate_h
#define communicate_h

// Defined special characters 
#define START_ARRAY '@'
#define ARRAY_SEPARATE ','
#define NEXT_ENTRY '&'
#define END_ARRAY '!'
#define PARSE_ARRAY '#'

int parse_array (int **x, int **y, unsigned int **t);

enum {
    rm_length,
    rm_x,
    rm_y,
    rm_time
};

#endif
