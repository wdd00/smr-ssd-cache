#include <stdio.h>
#include <stdlib.h>
#include "smr-simulator.h"
#include "band_table_for_fifo.h"

static bool isSameband(long band_id1,long band_id2);

void initBandTableforfifo(size_t size)
{
	band_hashtable_for_fifo = (BandHashBucketForFIFO *)malloc(sizeof(BandHashBucketForFIFO)*size);
	size_t i;
	BandHashBucketForFIFO *band_hash = band_hashtable_for_fifo;
	for(i = 0;i < size; band_hash++,i++){
		band_hash->band_num = -1;
		band_hash->band_id = -1;
		band_hash->next_item = NULL;	
	}	
}

unsigned long bandtableHashcodeforfifo(long band_num)
{
	unsigned long band_hash = band_num % NBANDTables;
	return band_hash;
}

size_t bandtableLookupforfifo(long band_num,unsigned long hash_code)
{
	BandHashBucketForFIFO *nowbucket = GetBandHashBucketforfifo(hash_code);
	while(nowbucket != NULL){
		if(isSameband(nowbucket->band_num,band_num))
			return nowbucket->band_id;	
		nowbucket = nowbucket->next_item;
	}
	return -1;
}

long bandtableInsertforfifo(long band_num,unsigned long hash_code,long band_id)
{
//	printf("insert table:band_num%ld hash_code:%ld band_id:%ld\n ",band_num,hash_code,band_id);
	BandHashBucketForFIFO *nowbucket = GetBandHashBucketforfifo(hash_code);	
	while(nowbucket->next_item != NULL && nowbucket != NULL){
		nowbucket = nowbucket->next_item;
	}
	if(nowbucket != NULL){
		BandHashBucketForFIFO *newitem = (BandHashBucketForFIFO *)malloc(sizeof(BandHashBucketForFIFO));
		newitem->band_num = band_num;
		newitem->band_id = band_id;
		newitem->next_item = NULL;
		nowbucket->next_item = newitem;
	} else {
		nowbucket->band_num = band_num;
		nowbucket->band_id = band_id;
		nowbucket->next_item = NULL;	
	}
	return -1;
}

long bandtableDeleteforfifo(long band_num,unsigned long hash_code)
{
	BandHashBucketForFIFO *nowbucket = GetBandHashBucketforfifo(hash_code);
	long del_val;
	BandHashBucketForFIFO *delitem;
	while(nowbucket->next_item != NULL && nowbucket != NULL){
		if(isSameband(nowbucket->next_item->band_num,band_num)){
			del_val = nowbucket->next_item->band_id;
			break;
		}
		nowbucket = nowbucket->next_item;
	}
	if(nowbucket->next_item != NULL) {
		delitem = nowbucket->next_item;
		nowbucket->next_item = nowbucket->next_item->next_item;
		free(delitem);
		return del_val;
	}
	else {
		delitem = nowbucket->next_item;
		nowbucket->next_item = NULL;
		free(delitem);
		return del_val;
	}
	return -1;
}

static bool isSameband(long band_num1,long band_num2)
{
	if(band_num1 != band_num2)
		return 0;
	else return 1;
}
