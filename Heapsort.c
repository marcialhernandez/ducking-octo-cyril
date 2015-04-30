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

/////////////////////////////////////////

const int Max = 20;

typedef float IntArrayType[Max];

/* Given:  IntArray      Array of integers.
           Count  The number of integers in IntArray
   Task:   To print out the integers from IntArray.
   Return: Nothing.
*/
void Print(IntArrayType IntArray, int Count)
   {

   for (int k = 0; k < Count; k++)
      cout << setw(5) << IntArray[k];

   cout << endl;
   }


/* Given:  Nothing.
   Task:   To fill IntArray with random integers.
   Return: IntArray   Array of random integers.
*/
void FillArray(IntArrayType IntArray)
   {
   int k;

   srand(time(NULL));  // set an arbitrary starting point
   for (k = 0; k < Max; k++)
      IntArray[k] = (1000.0 * rand()) / RAND_MAX;
   }

class HeapClass
   {

   public:

   	/* 
	Constructor
   	Argumentos: Array, cantidad de flotantes.
   Return:  Un puntero que contiene la data del monticulo
*/
      HeapClass(IntArrayType IntArray, int cantidad)
   {
   int posicionActual;

   if (cantidad <= 0)
      {
      cerr << "Cannot construct a heap with size 0 or less." << endl;
      exit(1);
      }

   MaxHeapSize = cantidad;
   HeapSize = cantidad;
   HeapArrayPtr = IntArray;   // a pointer assignment statement

   // Set CurrentPosition to the last index of a parent node:
   posicionActual = (HeapSize - 2) / 2;

   while (posicionActual >= 0)
      {
      // Get heap condition for subtree rooted at index CurrentPosition:
      FilterDown(posicionActual);
      posicionActual--;
      }
   }

/* Given:  Nothing other than the implicit HeapClass object.
   Task:   To remove the smallest item from the heap and readjust it
           so that it remains a heap.  If there is nothing to remove
           from the heap, terminate the program.
   Return: In the function name, return this smallest item.
*/

     int Delete(void)
   {
   int Temp;

   if (HeapSize == 0)
      {
      cerr << "Cannot remove from an empty heap" << endl;
      exit(1);
      }

   Temp = HeapArrayPtr[0];   // Item at index 0 is the smallest
   // copy last one to root:
   HeapArrayPtr[0] = HeapArrayPtr[HeapSize - 1];
   HeapSize--;
   FilterDown(0);   // readjust to be a heap
   return Temp;
   }




      /* Given:  Item   Number to insert into the heap.
           Of course, we also have the implied HeapClass object.
   Task:   To insert Item into the heap so as to maintain it as a heap.
   Return: Nothing directly, but the implied HeapClass object is modified.
*/
void Insert(int Item)
   {
   if (HeapSize == MaxHeapSize)
      {
      cerr << "Cannot insert into a full heap" << endl;
      exit(1);
      }

   // At first, place item at the end of the heap:
   HeapArrayPtr[HeapSize] = Item;
   FilterUp(HeapSize);   // restore heap property
   HeapSize++;
   }

   private:
      int * HeapArrayPtr;   // pointer to array holding the heap data
      int MaxHeapSize;
      int HeapSize;

      /* Given:  StartIndex   Index at which to start restoring the heap.
           Of course, we also have the implied HeapClass object.
           It is assumed that we already have a heap except possibly
           for the item at index StartIndex.
   Task:   To readjust the items in the subtree rooted at StartIndex
           so that we have a heap.
   Return: Nothing directly, but the implied HeapClass object is
           modified.
*/
void FilterDown(int StartIndex)
   {
   int CurrentPosition, ChildPosition, RightChildPosition, Target;

   CurrentPosition = StartIndex;
   Target = HeapArrayPtr[StartIndex];
   ChildPosition = LeftChild(CurrentPosition);

   while (ChildPosition < HeapSize)
      {
      RightChildPosition = ChildPosition + 1;
      //  Set ChildPosition to index of smaller of right, left children:
      if ((RightChildPosition < HeapSize) &&
        (HeapArrayPtr[RightChildPosition] <= HeapArrayPtr[ChildPosition]))
        ChildPosition = RightChildPosition;

      if (Target <= HeapArrayPtr[ChildPosition])
         break;  // Get out of loop, heap OK with Target at CurrentPosition

      // Move value of the smaller child to the parent node:
      HeapArrayPtr[CurrentPosition] = HeapArrayPtr[ChildPosition];
      // Move down the tree:
      CurrentPosition = ChildPosition;
      ChildPosition = LeftChild(CurrentPosition);
      }

   // Put Target into the correct location:
   HeapArrayPtr[CurrentPosition] = Target;
   }
      /* Given:  StartIndex  The index at which to start restoring the heap.
           Of course, we also have the implied HeapClass object.
           It is assumed that we have a heap from index 0 to index
           StartIndex - 1, so that the only item possibly out of order
           is the one at StartIndex.
   Task:   Move up the tree from StartIndex, adjusting so as to
           have a heap from index 0 to index StartIndex.
   Return: Nothing directly, but the implied HeapClass object is
           modified.
*/
void FilterUp(int StartIndex)
   {
   int CurrentPosition, ParentPosition, Target;

   CurrentPosition = StartIndex;
   ParentPosition = Parent(CurrentPosition);
   Target = HeapArrayPtr[StartIndex];

   while (CurrentPosition != 0)
      {
      if (HeapArrayPtr[ParentPosition] <= Target)
         break; // Get out of loop, heap OK with Target at CurrentPosition

      // Move parent value to child:
      HeapArrayPtr[CurrentPosition] = HeapArrayPtr[ParentPosition];
      // Move up in the tree:
      CurrentPosition = ParentPosition;
      ParentPosition = Parent(CurrentPosition);
      }

   // Place Target at the position located for it:
   HeapArrayPtr[CurrentPosition] = Target;
   }
      // Useful private functions.  Automatically inline functions
      // when put their code here:
      int Parent(int CurrentIndex)
         {
         return (CurrentIndex - 1) / 2;
         }
      int RightChild(int CurrentIndex)
         {
         return 2 * (CurrentIndex + 1);
         }
      int LeftChild(int CurrentIndex)
         {
         return 2 * CurrentIndex + 1;
         }
   };

/* Given:  IntArray  Array to be sorted.
           Count     The number of data items in IntArray.
   Task:   To sort IntArray into descending order using a heap sort.
   Return: IntArray  Sorted array.
*/
void HeapSort(IntArrayType IntArray, int Count)
   {
   int Smallest, k;
   HeapClass H(IntArray, Count);  // constructor makes IntArray a heap

   for (k = Count - 1; k >= 1; k--)
      {
      // Remove smallest item and place at index k
      Smallest = H.Delete();
      IntArray[k] = Smallest;
      }
   // At this point IntArray[0] contains the largest item by default
   }


int main(void)
   {
   IntArrayType IntArray;

   FillArray(IntArray);

   cout << "Original data" << endl;
   Print(IntArray, Max);

   HeapSort(IntArray, Max);
   cout << endl << "Sorted data" << endl;
   Print(IntArray, Max);

   return 0;
}