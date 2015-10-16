/*
 * RamCloudContext.h
 *
 *  Created on: Oct 14, 2015
 *      Author: Prasanna Ponnada
 */

#ifndef RAMCLOUD_CONTEXT_H
#define RAMCLOUD_CONTEXT_H

/* Note: This is only a stubbed out/mock Context. At integration time, this file
 * needs to be replaced with Context.h
 */
class Context {
  public:
    Context(bool hasDedicatedDispatchThread):
    	hasDedicatedDispatchThread(hasDedicatedDispatchThread) {}
    ~Context() {}
    void setDedicatedDispatchThread(bool hasDispatchedThread) {
    	hasDedicatedDispatchThread = hasDispatchedThread;
    }
  private:
    bool hasDedicatedDispatchThread;
};

#endif  // RAMCLOUD_CONTEXT_H
