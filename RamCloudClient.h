/*
 * RamCloudClient.h
 *
 *  Created on: Oct 14, 2015
 *      Author: Prasanna Ponnada
 */

#include "RamCloudContext.h"

#ifndef RAMCLOUDCLIENT_H
#define RAMCLOUDCLIENT_H

/* Note: This is a stubbed out RamCloud client. At integration time, this file
 * needs to be replaced with RamCloud.h
 */
class RamCloud {
  public:
    RamCloud(Context* context, const char* serviceLocator,
             const char* clusterName):
            	 coordinatorLocator(serviceLocator),
            	clientContext(context),
				clusterName(clusterName) {}
    virtual ~RamCloud() {};
  private:
    std::string coordinatorLocator;
    Context* clientContext;
    std::string clusterName;
};
#endif /* RAMCLOUDCLIENT_H_ */
