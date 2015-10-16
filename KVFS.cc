/*
 * TestKVStoreFactory.cc
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */
#include <iostream>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "FileSystemManager.h"
#include "KVStoreFactory.h"
#include "LevelDBFactory.h"
#include "RocksDBFactory.h"
#include "RamCloudFactory.h"


BOOST_CLASS_EXPORT(KVFSDirectory);
int main() {

#ifdef LOCAL_HD
	KVStoreFactory* factory = new LevelDBFactory;
	KVStore* store = factory->createLocalHDInstance();
	FileSystemManager* fm = new FileSystemManager(store);
#elif LOCAL_SSD
	KVStoreFactory* factory = new RocksDBFactory;
	KVStore* store = factory->createLocalSSDInstance();
#elif REMOTE
	KVStoreFactory* factory = new RamCloudFactory;
	KVStore* store = factory->createRemoteInstance();
#endif

	std::string coordinatorLocation = "www.coordinator.com";
	if (store != nullptr)
		store->init(coordinatorLocation, true);

	std::string fsName = "mykvfs.db";
	void* fsHandle = nullptr;
	uint64_t fsId = fm->mountFileSystem(fsName, fsHandle);
	if (fsId < 0)
		std::cout << "Could not create file system: " << fsName <<
		std::endl;
	else
		std::cout << "Mounted file system: " << fsName << " with fsId: "
			<< fsId << std::endl;

	KVFSMetaData metadata;
	bool sts = fm->addDirectory(fsId, "/", "/", metadata,
			                    0, fsHandle);
	if (sts == true)
		std::cout << "Created directory: /" << std::endl;
	else
		std::cerr << "Failed to create directory: /" << std::endl;

	sts = fm->addDirectory(fsId, "/", "home", metadata, 1, fsHandle);
	if (sts == true)
		std::cout << "Created directory: /home" << std::endl;
	else
		std::cerr << "Failed to create directory: /home" << std::endl;

	sts = fm->addDirectory(fsId, "/", "tmp", metadata, 2, fsHandle);
	if (sts == true)
		std::cout << "Created directory: /tmp" << std::endl;
	else
		std::cerr << "Failed to create directory: /tmp" << std::endl;


	sts = fm->addDirectory(fsId, "/home/user/", "git/", metadata,
			                    0, fsHandle);
	if (sts == false)
			std::cout << "Failed to create directory: /home/user/git" <<
			std::endl;

	std::cout << "Trying to create an existing directory: /home" << std::endl;
	sts = fm->addDirectory(fsId, "/", "home", metadata, 1, fsHandle);
	if (sts == false)
		std::cout << "Failed to create existing directory: /home" << std::endl;


	KVFSDirectoryEntry entries;
    uint64_t entryCount;

    std::cout << "Listing directories in /:" << std::endl;
	sts = fm->listDirectory(fsId, "/", "/", KVFSMetaData(), &entries,
			                &entryCount, fsHandle);

	if (entryCount > 0) {
		for (std::string dirEntry : entries.directoryEntries)
			std::cout << dirEntry << std::endl;
	}
	return 0;
}





