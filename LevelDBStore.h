/*
 * LevelDBStore.h
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef LEVELDBSTORE_H
#define LEVELDBSTORE_H

#include <iostream>
#include "KVStore.h"
#include "leveldb/db.h"

class LevelDBStore : public KVStore {
public:
	LevelDBStore(){};

	virtual bool
	init(const std::string dbAbsolutePath, bool hasDispatchedThread)	override;

	virtual bool open(const std::string dbname, void** handle) override;

	virtual bool put(void* handle, const std::string& key,
			const std::string& value) override;

	virtual bool get(void* handle, const std::string&key,
			std::string& value) override;

	virtual bool remove(void* handle, const std::string& key) override;

	static void setDBAbsolutePath(std::string dbAbsolutePath);

};

#endif /* LEVELDBSTORE_H */
