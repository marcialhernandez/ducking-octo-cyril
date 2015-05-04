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

//////////////////////////////////////////////////////////////////////////////////////////////////////

void heapsort(listaOffset A[], int length);
void buildheap(listaOffset A[], int length);
void heapify(listaOffset A[], int heaplength, int root);
void swap(listaOffset& x, listaOffset& y);

int main()
{
	int n=10;
	float A[n]={95.5,95.4,95.3,95.9,95.8,32.5,98.5,7.5,6.5,20.5};
	listaOffset datosConjunto[n];
	for (int i=0;i<n;i++){
		datosConjunto[i].pos=i;
		datosConjunto[i].cantidadRestante=16;
		datosConjunto[i].valor=A[i];
	}
	
	// Sort the list		       (takes O(n lg n) time)
	buildheap(datosConjunto, n);
	
	// Print the sorted list:	       (takes O(n) time)
	cout << endl << "Monticulo Creado\n";
	for ( int i = 0 ; i < n ; i++ ){
		cout << datosConjunto[i].valor << "  ";
	}
	cout << endl;

	swap(datosConjunto[0], datosConjunto[n-2]);
	heapify(datosConjunto, n-2, 0);	

	cout << endl << "Obtengo root dejandolo al final\n";
	for ( int i = 0 ; i < n ; i++ ){
		cout << datosConjunto[i].valor << "  ";
	}
	cout << endl;

	datosConjunto[n-1].valor=150.5;
	buildheap(datosConjunto, n);

	cout << endl << "Reemplazo el final y rehago el monticulo\n";
	for ( int i = 0 ; i < n ; i++ ){
		cout << datosConjunto[i].valor << "  ";
	}
	cout << endl;

	/*for (int i=n-1;i!=-1;i--){
		cout << datosConjunto[i].valor << "  ";
	}*/
}



void heapsort(listaOffset A[], int length)//	       (takes O(n lg n) time)
{
	int heapsize = length;
	
	buildheap(A, length);	//Take the unsorted list and make it a heap
	for (int i = length-1; i >=1; i--)
	{
		swap(A[0], A[i]);
		heapsize--;
		heapify(A, heapsize, 0);		
	}
}

void buildheap(listaOffset A[], int length)	//     (takes O(n) time)
{	
	for (int i = floor((length)/2); i >= 0 ; i--)
		heapify(A, length, i);
}

void heapify(listaOffset A[], int heapsize, int root) //(takes O(h) time,
					// h is the height of root
{
	int left = 2*root+1, 
		right = 2*root +2,
		largest;
	
	if ( (left < heapsize) && (A[left].valor > A[root].valor))
		largest = left;
	else 
		largest = root;
	
	if ( (right < heapsize) && (A[right].valor > A[largest].valor))
		largest = right;
		
	if (largest != root)
	{
		swap(A[root], A[largest]);
		heapify(A, heapsize, largest);
	}
}

void swap(listaOffset& x, listaOffset& y)
{
	listaOffset temp;
	
	temp = x;
	x = y;
	y = temp;
}