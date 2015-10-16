/*
 * RamCloudStore.h
 *
 *  Created on: Oct 12, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef RAMCLOUDSTORE_H
#define RAMCLOUDSTORE_H

#include <iostream>
#include "KVStore.h"
/* Note: Replace this with RamCloud's Context.h while integrating */
#include "RamCloudContext.h"
/* Note: Replace this with RamCloud's RamCloud.h while integrating */
#include "RamCloudClient.h"

class RamCloudStore : public KVStore {
private:
	std::string coordinatorLocator;
	Context context;
	RamCloud client;

public:
	RamCloudStore(): coordinatorLocator(""), context(false),
		client(RamCloud(&context, "", ""))  {}

	virtual bool init(const std::string locator, bool hasDispatchedThread) {
		if (locator.length() == 0)
			return false;

		std::cout << "In RamCloudStore init" << "\n";
		Context context1(hasDispatchedThread);
		context = context1;
		RamCloud client1(&context, locator.c_str(), "mycluster");
		client = client1;
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


	void setCoordinatorLocator(std::string locator) {
		coordinatorLocator = locator;
	}

	void setDedicatedDispatchThread(bool hasDispatchedThread) {
		context.setDedicatedDispatchThread(hasDispatchedThread);
	}

	RamCloud getClient() {
		return client;
	}

	Context getContext() {
		return context;
	}
};

#endif /* RAMCLOUDSTORE_H */
