/*
 * LevelDBFactory.h
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef LEVELDBFACTORY_H
#define LEVELDBFACTORY_H

#include "KVStoreFactory.h"
#include "LevelDBStore.h"

class LevelDBFactory : public KVStoreFactory {
public:
	KVStore* createLocalHDInstance();
	KVStore* createLocalSSDInstance();
	KVStore* createRemoteInstance();
	~LevelDBFactory() {}
};
#endif /* LEVELDBFACTORY_H */
