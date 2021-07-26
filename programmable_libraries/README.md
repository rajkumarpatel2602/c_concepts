Programmable libraries does tasks for application, while being completely application agnostic.

* What library does.
1. Offer support for creating of doubly linkedList
2. Listing of all elements in dll.
3. Application agnostic interface. Capabilities of passing callbacks for db search on any application structures. e.g. student_t and employee_t.

Application Flow :
1. create db
- Initialise db structure
-- Init Head pointer and register generic callback.

2. Insert elements in db.
- Pass db handle and filled structure as a data member.

3. Search for a strcture element in the databse.
- Pass db handle and entry to search. [this entry would be the one which is supported by the callback.]
-- This call would Iterate over db and will search pass node data [structure of student or employee] and item to search.
