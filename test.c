/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Copyright (C) Marcial Hernandez Sanchez, 2015
 * University of Santiago, Chile (Usach) 
 */

/////////////////////////////////////////
//C
#include <stdio.h>
#include <unistd.h>
//File descriptors from sys - C
#include <sys/types.h>
#include <sys/stat.h>
//System tools to open and write - C
#include <fcntl.h>
//C++
#include <iostream>
#include <iomanip>  // needed by setw
#include <ctime>    // needed by time function
#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
//OpenMP
#ifdef _OPENMP
#include <omp.h>
#endif
 
using namespace std;

int main(){
	for (int i=0,j=5;i<5;i++,j++){
		cout <<"i: "<<i<<"j: "<<j<<endl;
	}
	return 0;
}