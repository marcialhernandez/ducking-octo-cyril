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
//OpenMP
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

/*class listaOffset{

private:
	int pos,cantidadRestante;
	//listaOffset(int pos);
public:
	listaOffset(int posActual); //constructor por defecto
	~listaOffset(); //destructor
	void restaCantidad();
	int posActual();
	bool confirmaCantidad();
};

listaOffset::listaOffset(int posActual){
	pos=posActual;
	cantidadRestante=16; //La minima lista es de 16 elementos
}

listaOffset::~listaOffset(){}

void listaOffset::restaCantidad(){
	cantidadRestante=cantidadRestante-1;
}

int listaOffset::posActual(){
	int posActual=pos*16+(16-cantidadRestante);
	return posActual;
}

bool listaOffset::confirmaCantidad(){
	if (cantidadRestante==0){
		return true;
	}
	else{
		return false;
	}
}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Estructura que guarda info del offset de cada conjunto, y la cantidad restante de elementos por  //
// ordenar																							//
//////////////////////////////////////////////////////////////////////////////////////////////////////

struct listaOffset{
	int pos;
	int cantidadRestante;
	float valor;
	//listaOffset(int pos);
	void restaCantidad();
	int posActual();
	bool confirmaCantidad();
};

/*listaOffset::listaOffset(int posActual){
	pos=posActual;
	cantidadRestante=16; //La minima lista es de 16 elementos
}*/

void listaOffset::restaCantidad(){
	cantidadRestante=cantidadRestante-1;
}

int listaOffset::posActual(){
	int posActual=this->pos+16-cantidadRestante;
	return posActual;
}

bool listaOffset::confirmaCantidad(){
	if (cantidadRestante==0){
		return true;
	}
	else{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int Left(int iIndex) {
	return ((iIndex << 1) + 1);
}

int Right(int iIndex) {
	return ((iIndex << 1) + 2);
}

int Parent(int iIndex) {
	return ((iIndex - 1) >> 1);
}

void Swap(float& irX, float& irY) {
	float iTemp = irX;
	irX = irY;
	irY = iTemp;
}

int SwapWithChild(int iIndex, listaOffset* ipHeap, int iSize) {
	int iLeft		= Left(iIndex);
	int iRight		= Right(iIndex);
	int iLargest	= iIndex;
	if (iRight < iSize) {
		if (ipHeap[iLeft].valor < ipHeap[iRight].valor) {
			iLargest = iRight;
		} else {
			iLargest = iLeft;
		}
		if (ipHeap[iIndex].valor > ipHeap[iLargest].valor) {
			iLargest = iIndex;
		}
	} else if (iLeft < iSize) {
		if (ipHeap[iIndex].valor < ipHeap[iLeft].valor) {
			iLargest = iLeft;
		}
	}
	if (ipHeap[iIndex].valor < ipHeap[iLargest].valor) {
		Swap(ipHeap[iIndex].valor, ipHeap[iLargest].valor);
	}
	return iLargest;
}

void RemoveRoot(listaOffset* ipHeap, int iSize) {
	// Swap the last element with the root
	Swap(ipHeap[0].valor, ipHeap[iSize - 1].valor);
	--iSize;
	int iLasti = 0;
	int i = SwapWithChild(0, ipHeap, iSize);
	while (i != iLasti) {
		iLasti = i;
		i = SwapWithChild(i, ipHeap, iSize);
	}
}

int SwapWithParent(int i, listaOffset* ipHeap) {
	if (i < 1) {
		return i;
	}
	int iParent = Parent(i);
	if (ipHeap[i].valor > ipHeap[iParent].valor) {
		Swap(ipHeap[i].valor, ipHeap[iParent].valor);
		return iParent;
	} else {
		return i;
	}
}

void AddElement(float iNewEntry, listaOffset* ipHeap, int iSize) {
	ipHeap[iSize].valor = iNewEntry;
	int iLasti = iSize;
	int i = SwapWithParent(iLasti, ipHeap);
	while (iLasti != i) {
		iLasti = i;
		i = SwapWithParent(i, ipHeap);
	}
}

void OutputArray(listaOffset* ipArray, int iBar, int iSize) {
	using namespace std;
	for (int i = 0; i < iSize; ++i) {
		if (i == iBar) {
			cout << "|  ";
		}
		cout << ipArray[i].valor << "  ";
	}
	cout << endl;
}

void Print(listaOffset* IntArray, int size)
   {

   for (int k = 0; k < size; k++)
      cout << IntArray[k].valor << " - ";

   cout << endl;
   }

int main() {
	using namespace std;

	srand(time(NULL));  // set an arbitrary starting point
	//float iaArray[15];
	listaOffset iaArray[15];
	for (int i = 0; i < 15; ++i) {
		iaArray[i].valor = (1000.0 * rand()) / RAND_MAX;
	}

	Print(iaArray, 15);

	cout << endl;
	cout << "-------------------formo el monticulo----------------" << endl;

	 // Output the heap after each element that we add
	for (int i = 0; i < 15; ++i) {
		AddElement(iaArray[i].valor, iaArray, i);
		//OutputArray(iaArray, i + 1, 15);
			}

	Print(iaArray, 15);

		cout << endl;
		cout << "----------------Remuevo el elemento 15--------------------" << endl;


	 // Output the heap after each element that we remove
	//for (int i = 0; i < 14; ++i) {
		RemoveRoot(iaArray, 15);
		//RemoveRoot(iaArray, 15);
		//AddElement(iaArray[i], iaArray, i);
		//OutputArray(iaArray, 14 - i, 15);
		//cout << endl;
		//cout << "---------------------------------------------" << endl;
	//}

	Print(iaArray, 15);

			cout << endl;
		cout << "-----------------Agrego el elemento 0.1---------------------" << endl;

	AddElement(0.1, iaArray, 0);

	Print(iaArray, 15);

			cout << endl;
		cout << "---------------------------------------------" << endl;

    return 0;
}