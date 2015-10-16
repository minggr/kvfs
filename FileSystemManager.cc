/*
 * FileSystemManager.cc
 *
 *  Created on: Oct 15, 2015
 *      Author: Prasanna Ponnada
 */
#include "FileSystemManager.h"
#include "KVStore.h"
#include "KVFSDirectory.h"
#include "KVFSFile.h"

FileSystemManager::FileSystemManager(KVStore* kvStore):kvstore(kvStore) {}

uint64_t
FileSystemManager::mountFileSystem(std::string& fsName, void*& fsHandle) {
	uint64_t fsId = -1;
	if (this->getKVStore()->open(fsName, &fsHandle) == true) {
		fsId = CityHash64(fsName.c_str(), fsName.length());
		return fsId;
	}
	return fsId;
}

bool
FileSystemManager::addDirectory(uint64_t fsId,
                                const std::string& parent_dir_name,
                                const std::string& dir_name,
                                KVFSMetaData metadata,
								uint64_t dirHandle,
								void* fsHandle) {

    bool status = false;

    std::string absolutePath = parent_dir_name + dir_name;

    if (parent_dir_name == dir_name) {
        KVFSObject* directory = new KVFSDirectory(fsId, parent_dir_name,
        		                                  dir_name,
        			                              metadata, dirHandle);
        if (directory->exists(this->getKVStore(), fsHandle)) {
        	std::cerr << "Directory: " << dir_name << " already exists" <<
        			std::endl;
        	return false;
        }

        status = directory->create(this->getKVStore(), fsHandle);
        return status;
    }

    KVFSObject* parentDirectory = new KVFSDirectory(fsId, parent_dir_name,
    		                                        parent_dir_name,
    			                                    metadata, dirHandle);
    if (!parentDirectory->exists(this->getKVStore(), fsHandle)) {
    	std::cerr << "Parent directory: " << parent_dir_name <<
    			" doesn't exist " << std::endl;
    	return false;
    }

	KVFSObject* directory = new KVFSDirectory(fsId, parent_dir_name, dir_name,
			metadata, dirHandle);

	if (directory->exists(this->getKVStore(), fsHandle)) {
		std::cerr << "Directory: " << parent_dir_name + dir_name <<
				" already exists " << std::endl;
		return false;
	} else
		status = directory->create(this->getKVStore(), fsHandle);
    return status;
}

bool
FileSystemManager::listDirectory(uint64_t fsId,
                                 const std::string& parent_dir_name,
                                 const std::string& dir_name,
                                 KVFSMetaData metadata,
                                 KVFSDirectoryEntry* entries,
                                 uint64_t* entryCount,
								 void* fsHandle) {
    *entryCount = 0;
    entries->directoryEntries.clear();

    std::string sub_dir_name = (parent_dir_name == dir_name) ?
            parent_dir_name : dir_name;

    KVFSDirectory* kvsFSDir = new KVFSDirectory(fsId, parent_dir_name,
    		                                    sub_dir_name, metadata, -1);
    if(!kvsFSDir->exists(this->getKVStore(), fsHandle)) {
        return false;
    }

    kvsFSDir->listDirectory(entries, entryCount, this->getKVStore(), fsHandle);
    return true;
}

bool
FileSystemManager::removeDirectory(uint64_t fsId,
                                   const std::string& parent_dir_name,
                                   const std::string& dir_name,
								   void* fsHandle) {

//    /* First check to see if parent directory exists */
//    KVFSObject* logFSParentDir = new KVFSDirectory(fsId,
//    		                                       parent_dir_name,
//                                                   parent_dir_name);
//    if (!logFSParentDir->exists()) {
//        delete logFSParentDir;
//        return false;
//    }
//
//    /* Parent directory exists. Now, check to see if desired directory
//     * exists.
//     */
//    KVFSObject* logFSDir = new KVFSDirectory(fsId,
//    		                                 parent_dir_name,
//                                             dir_name);
//    if (!logFSDir->exists()) {
//
//        delete logFSParentDir;
//        delete logFSDir;
//        return false;
//    }
//
//    /* Desired directory and its parent exist. Get rid of the directory */
//    logFSDir->remove();
//
//    delete logFSParentDir;
//    delete logFSDir;
        
    return true;
}
