/*
 * RamCloudFactory.cc
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */
#include "KVStoreFactory.h"
#include "RamCloudFactory.h"
#include "RamCloudStore.h"


KVStore*
RamCloudFactory::createLocalHDInstance() {
	std::cout << "RamCloud on a local hard disk is not supported at this time."
			<< "\n";
	return nullptr;
}

KVStore*
RamCloudFactory::createLocalSSDInstance() {
	std::cout << "RamCloud on a local SSD is not supported at this time."
			<< "\n";
	return nullptr;
}

KVStore*
RamCloudFactory::createRemoteInstance() {
	return new RamCloudStore;
}
