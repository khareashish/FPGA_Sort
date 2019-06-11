#include "EvenOddIterSorter.hpp"



void EvenOddSortHLS(hls::stream< Data_t > &InputDataStream , hls::stream< Data_t > &SortedDataStream)
{



	Data_t DataBuffer[NUM_ELEMENTS];
	Data_t Even[NUM_ELEMENTS];




	// fill in the input data buffer
	for(int i = 0 ; i < NUM_ELEMENTS; i++)
	{
		DataBuffer[i] = InputDataStream.read();
	}



	bool bSortingCompleted = false;

// Sort the data:

	while (!bSortingCompleted)
	{
		bSortingCompleted = true;

		for (int j = 0; j < (NUM_ELEMENTS / 2); j++)
		{

			if (DataBuffer[2 * j] > DataBuffer[2 * j + 1])
			{
				bSortingCompleted = false;
				Even[2 * j] = DataBuffer[2 * j + 1];
				Even[2 * j + 1] = DataBuffer[2 * j];
			}

			else
			{
				Even[2 * j] = DataBuffer[2 * j];
				Even[2 * j + 1] = DataBuffer[2 * j + 1];
			}
		}


	// odd line of comparators
		for (int j = 0; j < (NUM_ELEMENTS / 2 - 1); j++)
		{
			if (Even[2 * j + 1] > Even[2 * j + 2])
			{
				bSortingCompleted = false;
				DataBuffer[2 * j + 1] = Even[2 * j + 2];
				DataBuffer[2 * j + 2] = Even[2 * j + 1];
			}
			else
			{
				DataBuffer[2 * j + 1] = Even[2 * j + 1];
				DataBuffer[2 * j + 2] = Even[2 * j + 2];
			}
		}

		DataBuffer[0] = Even[0];
		DataBuffer[NUM_ELEMENTS-1] = Even[NUM_ELEMENTS-1];
	}




	// Output the resutls:

	for(int i = 0 ; i < NUM_ELEMENTS; i++)
	{
		Data_t SortedDataOut = DataBuffer[i];
		SortedDataStream.write(SortedDataOut);
	}


}






// SDSoC Wrapper for Even Odd Sort:



#pragma SDS data access_pattern(pInputData:SEQUENTIAL,  pSortedData:SEQUENTIAL)
#pragma SDS data copy(pInputData[0:NUM_ELEMENTS],  pSortedData[0:NUM_ELEMENTS])
#pragma SDS data data_mover(pInputData:AXIDMA_SIMPLE, pSortedData:AXIDMA_SIMPLE)


void sort_accel(	Data_t* pInputData,
					Data_t* pSortedData
					)
{



#pragma HLS INLINE OFF
#pragma HLS DATAFLOW





	hls::stream< Data_t > InputDataStream;
	hls::stream< Data_t > SortedDataStream;




// populate input Data stream
	for(int i=0; i<NUM_ELEMENTS;i++)
	{
		#pragma HLS LOOP_FLATTEN off
		#pragma HLS PIPELINE

		Data_t DataIn = pInputData[i];
		InputDataStream.write( DataIn );
	}


	EvenOddSortHLS(InputDataStream, SortedDataStream);



	for(int i=0; i<NUM_ELEMENTS;i++)
	{
		#pragma HLS LOOP_FLATTEN off
		#pragma HLS PIPELINE


		Data_t SortedDataOut = SortedDataStream.read();
		pSortedData[i] = SortedDataOut;

	}
}

