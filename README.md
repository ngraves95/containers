# Containers
This is a C module to mimic C++'s shared_ptr class.
It uses reference counting to keep track of containers, and when the reference count hits 0, the object contained is freed.
