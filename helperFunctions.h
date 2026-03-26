#include<stdio.h>

/*
	This function returns the index of the first
	instance where key is found. Otherwise, function 
	returns -1.
	
	key - the data (value) to be found
	A[] - the array to find key
	nElem - number of elements in A[]
*/
int
Search(int key, int A[], int nElem)
{
	int result;
	int i = 0;
	
	while (i < nElem && A[i] != key)
		i++;
	
	if (i < nElem){
		result = i;
	}else{
		result = -1;
	}
	return result;
}

/* 
  This function copies all elements one position up 
  from the data to be deleted. It retains the sequence
  of the array.

  *aData - array to be modified
  startInd - index of data to be deleted
  nElem - number of elements in the array
*/
void
copy(int * aData, int startInd, int nElem)
{
  int i;
	
	for (i = startInd + 1; i < nElem; i++)
	    aData[i-1] = aData[i];
	    //*(aData + i -1) = *(aData + i);
}

/*
  This function deletes the data from
  the given parameters. It uses Search()
  and copy()

  key - the data (value) to be deleted
  aData[] - array
  *pElem - number of elements in aData[]
*/
void
del(int key, int aData[], int * pElem)
{
  int index;
	
	index = Search(key, aData, *pElem);
	
	if (index != -1)  //found
	{  
       copy(aData, index, *pElem);
	   (*pElem)--;
	}
}

/*
	This function adds data from given parameters.
	
	key - the data (value) to be added
	aData[] - the array added to
	*pElem - number of elements in aData[]
*/
void
add(int key, int aData[], int * pElem){
	aData[*pElem] = key;
	*pElem = *pElem + 1;
}

/* 
	For testing purposes
*/
void
PrintArray(int A[],int pElem){
	for(int i=0;i<pElem;i++){
		printf("%d ",A[i]);
	}
	printf("\n");
}