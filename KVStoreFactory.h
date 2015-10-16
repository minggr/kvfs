/*
 * KVStoreFactory.h
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef KVSTOREFACTORY_H
#define KVSTOREFACTORY_H

class KVStore;

class KVStoreFactory {
public:

	/* Returns instance of a KV Store that is optimized
	 * to run on a local hard disk.
	 */
	virtual KVStore* createLocalHDInstance() = 0;
	/* Returns instance of a KV Store that is optimized
	 * to run on a local SSD.
	 */
	virtual KVStore* createLocalSSDInstance() = 0;
	/* Returns instance of a KV Store that is optimized
	 * to run on remote nodes that are distributed.
	 */
	virtual KVStore* createRemoteInstance() = 0;

	virtual ~KVStoreFactory() {}
};
#endif /* KVSTOREFACTORY_H */
