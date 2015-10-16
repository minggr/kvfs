/*
 * FileSystemManager.h
 *
 *  Created on: Oct 15, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef KVS_FILESYSTEM_MANAGER
#define KVS_FILESYSTEM_MANAGER

#include <city.h>
#ifdef __SSE4_2__
#include "citycrc.h"
#endif

#include "KVStore.h"
#include "KVFSMetaData.h"
#include "KVFSDirectory.h"
#include "KVFSFile.h"

class FileSystemManager {
public:
    explicit
	FileSystemManager(KVStore* kvStore);

    uint64_t
	mountFileSystem(std::string& fsName, void*& fsHandle);


    bool
	addDirectory(uint64_t fsId,
                 const std::string& parent_dir_name,
                 const std::string& dir_name,
				 KVFSMetaData metadata,
				 uint64_t dirHandle,
				 void* fsHandle);

    bool
    listDirectory(uint64_t fsId,
                  const std::string& parent_dir_name,
                  const std::string& dir_name,
                  KVFSMetaData metadata,
                  KVFSDirectoryEntry* entries,
                  uint64_t* entryCount,
				  void* fsHandle);

    bool
    removeDirectory(uint64_t fsId,
    		        const std::string& parent_dir_name,
                    const std::string& dir_name,
					void* fsHandle);

    bool
	addFile(uint64_t fsId,
            const std::string& parent_dir_name,
            const std::string& file_name,
            KVFSMetaData metadata,
			void* fsHandle) {
    	return true;
    }

    bool
	removeFile(uint64_t fsId,
               const std::string& parent_dir_name,
               const std::string& file_name,
			   void* fsHandle) {
    	return true;
    }

    bool
	readFile(uint64_t fsId,
             const std::string& parent_dir_name,
             const std::string& file_name,
             uint64_t offset,
			 uint64_t length,
             char* readBuffer,
			 void* fsHandle) {
    	return true;
    }

    bool
	writeFile(uint64_t fsId,
              const std::string& parent_dir_name,
              const std::string& file_name,
              uint64_t offset,
			  uint64_t length,
              const char *writeBuffer,
			  void* fsHandle) {
    	return true;
    }

    bool
	openFile(uint64_t fsId,
             const std::string& parent_dir_name,
             const std::string& file_name,
	   	     KVFSMetaData metadata,
			 void* fsHandle) {
    	return true;
    }

    KVStore* getKVStore() {
    	return kvstore;
    }

private:
    KVStore* kvstore;
};

#endif  // KVS_FILESYSTEM_MANAGER
