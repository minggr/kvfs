/*
 * RamCloudFactory.h
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef RAMCLOUDFACTORY_H_
#define RAMCLOUDFACTORY_H_

class RamCloudFactory : public KVStoreFactory {
public:
	KVStore* createLocalHDInstance();
	KVStore* createLocalSSDInstance();
	KVStore* createRemoteInstance();
	~RamCloudFactory() {}
};
#endif /* RAMCLOUDFACTORY_H_ */
