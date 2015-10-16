/*
 * LevelDBStore.cc
 *
 *  Created on: Oct 15, 2015
 *      Author: Prasanna Ponnada
 */

#include "LevelDBStore.h"

bool
LevelDBStore::init(const std::string coordinatorLoc, bool hasDispatchedThread) {
	/* there is no co-ordinator in Level DB, nothing to init */
	return true;
}

bool
LevelDBStore::open(const std::string dbName, void** handle) {

	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;

	leveldb::Status status = leveldb::DB::Open(options,	dbName, &db);

	if (status.ok() == false)
	{
		std::cerr << "Unable to open/create database " << dbName << std::endl;
		std::cerr << status.ToString() << std::endl;
		return false;
	}

	*handle = db;
	return true;
}

bool
LevelDBStore::put(void* handle, const std::string& key,
		const std::string& value) {
	leveldb::DB* db = reinterpret_cast<leveldb::DB*>(handle);
	leveldb::Status status = db->Put(leveldb::WriteOptions(), key, value);
	if(status.ok())
		return true;
	else
		return false;
}

bool
LevelDBStore::get(void* handle, const std::string&key, std::string& value) {
	leveldb::DB* db = reinterpret_cast<leveldb::DB*>(handle);
	leveldb::Status status = db->Get(leveldb::ReadOptions(), key, &value);
	if(status.ok())
		return true;
	else
		return false;
}

bool
LevelDBStore::remove(void* handle, const std::string& key) {
	leveldb::DB* db = reinterpret_cast<leveldb::DB*>(handle);
	leveldb::Status status = db->Delete(leveldb::WriteOptions(), key);
	if(status.ok())
		return true;
	else
		return false;
}
