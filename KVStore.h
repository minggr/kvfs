/*
 * KVStore.h
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */

#include <iostream>
#ifndef KVSTORE_H
#define KVSTORE_H

class KVStore {
public:
	KVStore() {};
	virtual bool init(const std::string locator, bool hasDispatchedThread) = 0;
	virtual bool open(const std::string dbname, void** handle) = 0;
	virtual bool put(void* handle, const std::string& key,
			const std::string& value) = 0;
	virtual bool get(void* handle, const std::string& key,
			std::string& value) = 0;
	virtual bool remove(void* handle, const std::string& key) = 0;
	virtual ~KVStore() {};
};

#endif /* KVSTORE_H */
