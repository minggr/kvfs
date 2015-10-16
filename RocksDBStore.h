/*
 * RocksDBStore.h
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef ROCKSDBSTORE_H_
#define ROCKSDBSTORE_H_

#include <iostream>
#include "KVStore.h"

class RocksDBStore : public KVStore {
public:
	RocksDBStore() {};

	virtual bool init(const std::string locator, bool hasDispatchedThread) {
		std::cout << "In RocksDBStore init" << "\n";
		return true;
	}

	virtual bool open(const std::string dbname, void** handle) {
		return true;
	}

	virtual bool put(void* handle, const std::string& key,
			const std::string& value) {
		return true;
	}

	virtual bool get(void* handle, const std::string&key,
			std::string& value) {
		return true;
	}

	virtual bool remove(void* handle, const std::string& key) {

		return true;
	}

};

#endif /* ROCKSDBSTORE_H_ */
