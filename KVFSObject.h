/*
 * KVFSObject.h
 *
 *  Created on: Oct 15, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef KVFS_OBJECT
#define KVFS_OBJECT
#include <iostream>
#include <sstream>
//#include <boost/serialization/base_object.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

enum KVFSEntryType {
	KVFS_DIRECTORY,
	KVFS_FILE,
	KVFS_ENTRY_END
};

class KVFSObject {
public:
    KVFSObject();
    KVFSObject(uint64_t fsId, std::string parent, std::string name,
               KVFSEntryType type):
                	fsId(fsId), parent(parent), name(name), type(type) {}
    KVFSObject(const KVFSObject& kvFSObject)
    :fsId(kvFSObject.fsId)
    ,parent(kvFSObject.parent)
    ,name(kvFSObject.name)
    ,type(kvFSObject.type) {}

    class KVFSBuffer {
    	std::stringstream sst;
    };

    virtual bool exists(KVStore* store, void* fsHandle) = 0;
    virtual bool create(KVStore* store, void* fsHandle) = 0;
    virtual bool remove(KVStore* store, void* fsHandle) = 0;
    virtual ~KVFSObject() {};

    inline uint64_t getFSId() {
        return fsId;
    }

    inline std::string getParentDirName() {
        return parent;
    }

    inline std::string getDirName() {
        return name;
    }

    inline KVFSEntryType getType() {
        return type;
    }

protected:
    uint64_t fsId;
    std::string parent;
    std::string name;
    KVFSEntryType type;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& fsId;
		ar& parent;
		ar& name;
		ar& type;
	}

};

#endif /* LOGFS_OBJECT */
