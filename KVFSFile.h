/*
 * KVFSFile.h
 *
 *  Created on: Oct 15, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef KV_FS_FILE
#define KV_FS_FILE

#include "KVFSMetaData.h"
#include "KVFSObject.h"

class KVFSFile : public KVFSObject {
  public:
	  KVFSFile(uint64_t fsId, const std::string& parent_dir_name,
	           const std::string& file_name, KVFSMetaData metadata,
			   uint64_t handle) :
				KVFSObject(fsId, parent_dir_name, file_name, KVFS_DIRECTORY),
				meta(metadata),
				handle(handle) {}
    ~KVFSFile();
    virtual bool exists(KVStore* store, void* fsHandle) = 0;
    virtual bool create(KVStore* store, void* fsHandle) = 0;
    virtual bool remove(KVStore* store, void* fsHandle) = 0;
    virtual bool open(const std::string& parent_dir_name,
       			      const std::string& file_name,
			          KVFSMetaData metadata) = 0;
    virtual bool close() = 0;
    virtual uint64_t read(uint64_t handle, uint64_t offset, uint64_t length,
                          KVFSBuffer *readBuffer) = 0;
    virtual uint64_t write(uint64_t handle, uint64_t offset, uint64_t length,
                           const KVFSBuffer *writeBuffer) = 0;
    inline KVFSMetaData getLogFSMetaData() { return meta; }
    inline uint64_t getHandle() { return handle; }

private:
    KVFSFile():handle(-1) {}
    KVFSMetaData meta;
    uint64_t handle;
};

#endif /* KV_FS_FILE */
