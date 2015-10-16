/*
 * KVFSMetaData.h
 *
 *  Created on: Oct 15, 2015
 *      Author: Prasanna Ponnada
 */

#include <stdint.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#ifndef KVFS_METADATA
#define KVFS_METADATA

struct KVFSMetaData{
	KVFSMetaData():atime(0),mtime(0),ctime(0) {}
        uint64_t       atime;      /* last access time */
        uint64_t       mtime;      /* last modification time */
        uint64_t       ctime;      /* last status change time */
    	friend class boost::serialization::access;
    	template<class Archive>
    	void serialize(Archive& ar, const unsigned int version) {
    		ar& atime;
    		ar& mtime;
    		ar& ctime;
    	}
} ;


#endif /* KVFS_METADATA */
