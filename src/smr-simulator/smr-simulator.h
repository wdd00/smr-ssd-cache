#ifndef SMR_SSD_CACHE_SMR_SIMULATOR_H
#define SMR_SSD_CACHE_SMR_SIMULATOR_H

#define DEBUG 0
/* ---------------------------smr simulator---------------------------- */
#include <pthread.h>

typedef struct
{
        unsigned long       offset;
} SSDTag;

typedef struct
{
        SSDTag     ssd_tag;
        long       ssd_id;			// ssd buffer location 
        unsigned   ssd_flag;
//	long		usage_count;
	long		next_ssd_buf;
} SSDDesc;

#define SSD_VALID 0x01
#define SSD_DIRTY 0x02

typedef struct SSDHashBucket
{
        SSDTag				hash_key;
        long                             ssd_id;
        struct SSDHashBucket		*next_item;
} SSDHashBucket;

typedef struct
{
	unsigned long		n_usedssd;
	long		first_usedssd;		// Head of list of used ssds
	long		last_usedssd;		// Tail of list of used ssds
} SSDStrategyControl;

typedef struct BandDescForFIFO
{
        long band_num;
        long first_page;
        long next_free_band;
} BandDescForFIFO;

typedef struct BandHashBucketForFIFO
{
        long band_num;
        long band_id;
        struct BandHashBucketForFIFO *next_item;
} BandHashBucketForFIFO;

typedef struct BandControlForFIFO
{
        long first_freeband;
        long last_freeband;
        long n_usedband;
} BandControlForFIFO;

extern unsigned long flush_bands;
extern unsigned long flush_fifo_blocks;
extern unsigned long read_fifo_blocks;
extern unsigned long read_smr_blocks;
extern unsigned long read_smr_bands;
//extern unsigned long write-fifo-num;

extern SSDDesc		*ssd_descriptors;
extern char             *ssd_blocks;
extern SSDStrategyControl *ssd_strategy_control;
extern SSDHashBucket	*ssd_hashtable;
BandHashBucketForFIFO *band_hashtable_for_fifo;
BandControlForFIFO *band_control_for_fifo;
BandDescForFIFO *band_descriptors_for_fifo;

//#define GetSSDblockFromId(ssd_id) ((void *) (ssd_blocks + ((long) (ssd_id)) * SSD_SIZE))
#define GetSSDHashBucket(hash_code) ((SSDHashBucket *) (ssd_hashtable + (unsigned long) (hash_code)))
#define GetBandHashBucketforfifo(hash_code) ((BandHashBucketForFIFO *)(band_hashtable_for_fifo +(unsigned long)(hash_code)))

extern unsigned long GetSMRActualBandSizeFromSSD(unsigned long offset);
extern unsigned long GetSMRBandNumFromSSD(unsigned long offset);
extern off_t GetSMROffsetInBandFromSSD(SSDDesc *ssd_hdr);
extern int smrread(int smr_fd, char* buffer, size_t size, off_t offset);
extern int smrwrite(int smr_fd, char* buffer, size_t size, off_t offset);

extern unsigned long NSSDs;
extern unsigned long NSSDTables;
extern unsigned long NSMRBands;
extern unsigned long SSD_SIZE;
extern size_t BLCKSZ;
extern size_t BNDSZ;
extern unsigned long INTERVALTIMELIMIT;
extern unsigned	long NSSDLIMIT;
extern unsigned long NSSDCLEAN;
extern char     smr_device[100];
extern char	inner_ssd_device[100];
extern int 	inner_ssd_fd;
extern int 	smr_fd;
extern unsigned	long interval_time;
extern pthread_mutex_t free_ssd_mutex;
extern pthread_mutex_t inner_ssd_hdr_mutex;
extern pthread_mutex_t inner_ssd_hash_mutex;
extern void initSSD();

#endif
