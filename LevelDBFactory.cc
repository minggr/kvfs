/*
 * LevelDBFactory.cc
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */
#include <iostream>
#include "KVStoreFactory.h"
#include "LevelDBFactory.h"
#include "LevelDBStore.h"

KVStore*
LevelDBFactory::createLocalHDInstance() {
	return new LevelDBStore;
}

KVStore*
LevelDBFactory::createLocalSSDInstance() {
	std::cout << "LevelDB on an SSD is not supported at this time." << "\n";
	return nullptr;
}

KVStore*
LevelDBFactory::createRemoteInstance() {
	std::cout << "LevelDB on a remote node is not supported at this time." <<
			"\n";
	return nullptr;
}
