#pragma once


#include "sds_lib.h"
#include <ap_int.h>
#include <ap_fixed.h>
#include <stdint.h>
#include <assert.h>
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "ap_int.h"




#define NUM_ELEMENTS 5000

typedef ap_uint<32> Data_t ;



void EvenOddSortHLS(hls::stream< Data_t > &InputDataStream , hls::stream< Data_t > &SortedDataStream);




#pragma SDS data access_pattern(pInputData:SEQUENTIAL,  pSortedData:SEQUENTIAL)
#pragma SDS data copy(pInputData[0:NUM_ELEMENTS],  pSortedData[0:NUM_ELEMENTS])
#pragma SDS data data_mover(pInputData:AXIDMA_SIMPLE, pSortedData:AXIDMA_SIMPLE)


void sort_accel(	Data_t* pInputData,
					Data_t* pSortedData
					);
