/*
 * RocksDBFactory.cc
 *
 *  Created on: Oct 14, 2015
 *      Author: ponnada
 */


/*
 * RocksDBFactory.cc
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */
#include <iostream>
#include "KVStoreFactory.h"
#include "RocksDBFactory.h"
#include "RocksDBStore.h"


KVStore*
RocksDBFactory::createLocalHDInstance() {
	std::cout << "RocksDB on a local hard disk is not supported at this time."
			<< "\n";
	return nullptr;
}

KVStore*
RocksDBFactory::createLocalSSDInstance() {
	return new RocksDBStore;
}

KVStore*
RocksDBFactory::createRemoteInstance() {
	std::cout << "RocksDB on a remote node is not supported at this time."
			<< "\n";
	return nullptr;
}
