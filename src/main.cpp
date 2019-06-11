


#include "EvenOddIterSorter.hpp"

int main()
{






	Data_t *pSortedData 	= (Data_t*)sds_alloc(NUM_ELEMENTS*sizeof(Data_t) ) ;

	Data_t *pInputData 		= (Data_t*)sds_alloc(NUM_ELEMENTS*sizeof(Data_t) ) ;


	int j = 0 ;
	for(int i = NUM_ELEMENTS-1 ; i >=0 ; i--)
	{
		pInputData[j] = i;
		j++;
	}



	unsigned long clock_start, clock_end;
	clock_start = sds_clock_counter();


	sort_accel(pInputData, pSortedData);


	clock_end = sds_clock_counter();
	printf("Array Sorted in %f ms \n", (1000.0/sds_clock_frequency())*(double)(clock_end-clock_start));






	printf("Sorted Array: \n");

	for(int i = 0 ; i < NUM_ELEMENTS; i++)
	{
		printf("%d, \n", (int)pSortedData[i]);
	}


    return 0;
}
