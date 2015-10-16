CC=g++ -O3 -std=c++11
CFLAGS=-c -Wall -I leveldb/include -DLOCAL_HD=1
LDFLAGS= -lleveldb -lpthread -lcityhash -lboost_serialization
SOURCES=LevelDBFactory.cc LevelDBStore.cc RamCloudFactory.cc RocksDBFactory.cc KVFS.cc FileSystemManager.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=kvfs

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	
.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf kvfs *.o *.db  2> /dev/null
