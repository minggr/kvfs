/*
 * KVFSDirectory.h
 *
 *  Created on: Oct 15, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef KV_FS_DIRECTORY
#define KV_FS_DIRECTORY

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/serialization/vector.hpp>

#include "KVFSMetaData.h"
#include "KVFSObject.h"

class KVFSFile;
class KVFSDirectory;

struct KVFSDirectoryEntry {
  KVFSDirectoryEntry():directoryName(""), directoryEntries() {}
  KVFSDirectoryEntry(std::string directoryName):directoryName(directoryName),
		  directoryEntries() {}
  std::string directoryName;
  std::vector<std::string> directoryEntries;
  friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& directoryName;
		ar& directoryEntries;
	}

};

class KVFSDirectory : public KVFSObject {
public:
  KVFSDirectory():KVFSObject(-1, "", "", KVFS_DIRECTORY),
	meta(KVFSMetaData()),
	handle(0) {}
  KVFSDirectory(uint64_t fsId, const std::string& parent_dir_name,
                const std::string& dir_name, KVFSMetaData metadata,
				uint64_t handle) :
					KVFSObject(fsId, parent_dir_name, dir_name, KVFS_DIRECTORY),
					meta(metadata),
					handle(handle) {}
  ~KVFSDirectory() {};

  virtual bool exists(KVStore* store, void* fsHandle) {
	  std::string absolutePath = (parent == name) ? parent : (parent + name);
	  char dirKey[512];
	  snprintf(dirKey, 512, "%lu",
			  CityHash64(absolutePath.c_str(), absolutePath.length()));
	  std::string value;
	  if (store->get(fsHandle, dirKey, value) == true)
		  return true;
	  else
		  return false;
  }

  virtual bool create(KVStore* store, void* fsHandle) {
	  std::stringstream ss;
	  {
		  boost::archive::text_oarchive oa(ss);
		  oa << *this;
	  }
	  std::string absolutePath = (parent == name) ? parent : (parent + name);
	  char dirKey[512];
	  snprintf(dirKey, 512, "%lu",
			  CityHash64(absolutePath.c_str(), absolutePath.length()));
	  if (store->put(fsHandle, dirKey, ss.str()) == true) {
		  std::string parentDirEntryKeyStr = parent + ".entry";
		  char parentDirEntryKey[512];
		  snprintf(parentDirEntryKey, 512, "%lu",
				  CityHash64(parentDirEntryKeyStr.c_str(),
						  parentDirEntryKeyStr.length()));


		  std::string dirEntriesStr;
		  if (store->get(fsHandle, parentDirEntryKey, dirEntriesStr) == true)
		  {
			  std::stringstream dirEntriesReadStream;
			  dirEntriesReadStream << dirEntriesStr;
			  KVFSDirectoryEntry kvfsDirectoryEntry;
			  boost::archive::text_iarchive ia(dirEntriesReadStream);
			  ia >> kvfsDirectoryEntry;
			  kvfsDirectoryEntry.directoryEntries.push_back(name);

			  std::stringstream dirEntriesWriteStream;
			  boost::archive::text_oarchive oa(dirEntriesWriteStream);
			  oa << kvfsDirectoryEntry;
			  if (store->put(fsHandle, parentDirEntryKey,
					         dirEntriesWriteStream.str()) != true) {
				  std::cerr << "Couldn't persist directory entries for: " <<
						  parent << std::endl;
				  return false;
			  }
		  } else {
			  KVFSDirectoryEntry kvfsDirectoryEntry(parent);
			  std::stringstream dirEntriesWriteStream;
			  boost::archive::text_oarchive oa(dirEntriesWriteStream);
			  oa << kvfsDirectoryEntry;
			  if (store->put(fsHandle, parentDirEntryKey,
					         dirEntriesWriteStream.str()) != true) {
				  std::cerr << "Couldn't persist empty directory entries "
						  "for: " << parent << std::endl;
				  return false;
			  }
		  }
		  return true;
	  }
	  else
		  return false;
  }

  virtual void listDirectory(KVFSDirectoryEntry* entries,
		                     uint64_t* entryCount,
							 KVStore* store,
							 void* fsHandle) {
	  std::string absolutePath = (parent == name) ? parent : (parent + name);
	  char dirKey[512];
	  std::string absolutePathEntry = absolutePath + ".entry";
	  snprintf(dirKey, 512, "%lu",
			  CityHash64(absolutePathEntry.c_str(),
					  absolutePathEntry.length()));
	  std::string dirEntriesStr;
	  if (store->get(fsHandle, dirKey, dirEntriesStr) == true)
	  {
		  std::stringstream dirEntriesReadStream;
		  dirEntriesReadStream << dirEntriesStr;
		  KVFSDirectoryEntry kvfsDirectoryEntry;
		  boost::archive::text_iarchive ia(dirEntriesReadStream);
		  ia >> kvfsDirectoryEntry;
		  *entryCount = kvfsDirectoryEntry.directoryEntries.size();
		  if (entryCount > 0) {
			  for ( std::string entry : kvfsDirectoryEntry.directoryEntries)
				  entries->directoryEntries.push_back(entry);
		  }
	  }
  }

  virtual bool remove(KVStore* store, void* fsHandle) {
	  return true;
  }

  virtual bool addFile(uint64_t fsId, std::string parent_dir_name,
                       std::string file_name, KVFSMetaData metadata) {
	  return true;
  }


  inline KVFSMetaData getLogFSMetaData() { return meta; }
  inline uint64_t getHandle() { return handle; }

private:
  struct KVFSMetaData meta;
  uint64_t handle;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<KVFSObject>(*this);
		ar& meta;
		ar& handle;
	}

};

#endif /* KV_FS_DIRECTORY */
