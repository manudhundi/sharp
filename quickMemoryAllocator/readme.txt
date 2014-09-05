qMemAlloc (Quick memory allocator) class can used to allocate 
memory on heap quickly.

In some applications, when lot of small amounts of memory is
allocated on the heap, using sytem call malloc for each allocation
is an overhead. Using qMemAlloc api, number of system calls is
reduced. qMemAlloc does malloc in chunks of memory and thereby
reduces the number of calls to malloc. qMemAlloc on advise from
qMemNodeMgr class decides when to allocate new chunk (qMemNode)

qMemNode is a chunk of memory allocated by qMemAlloc. Until all
the memory in this chunk is used, qMemNode can be called to get
memory. It returns NULL if asked for memory size more than it can
accomodate.

qMemNodeMgr manages the qMemNodes (chunks of memory) that are in
use. It is an abstract class that provides api to query for a
qMemNode. Based on user selection, qMemNodeMgr morphs into either
1) qMemNodeMgrLazy or 2) qMemNodeMgrSqueeze (runtime polymorphism).
1) qMemNodeMgrLazy just gives memory from the current qMemNode if 
   available or else says out of memory
2) qMemNodeMgrSqueeze stores a map (STL map, that is, an RB tree)
   of all qMemNodes and selects the one with the memory size that
   can just satisfy the demand for memory. If not, it throws
   out of memory

NOTE: The caveat is, the memory allocated is not freed by
      calling individual free. All of memory is freed in one shot
      when class qMemAlloc is deallocated. It is fair to assume
      that there are applications that allocate memory and use almost
      all of it till end of the application