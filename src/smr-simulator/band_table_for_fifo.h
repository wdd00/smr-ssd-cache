#ifndef BANDTABLE_H
#define BANDTABLE_H

#define DEBUG 0
/*-----------------------------------band----------------------------*/
#define bool unsigned char
#define size_t long

extern unsigned long NBANDTables;

extern void initBandTableforfifo(size_t size);
extern unsigned long bandtableHashcodeforfifo(long band_num);
extern long bandtableLookupforfifo(long band_num,unsigned long hash_code);
extern long bandtableInsertforfifo(long band_num,unsigned long hash_code,long band_id);
extern long bandtableDeleteforfifo(long band_num,unsigned long hasd_code);
#endif    /*  BANDTABLE_H*/
