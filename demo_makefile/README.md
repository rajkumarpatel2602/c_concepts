# Makefile works on the conecept of dependency tree!


# Diagram

 Target [final executable or libfile]
 |
 --------------------------------------------
 |                     |                    |
 Req1                 Req2                 Req3  [.o files or external lib files]
 |                     |
 ----------       -------------
 |        |       |           |
 Raw1    Raw2    Raw3        Raw4  [Raw material -- .h, .c]


# Usagae of makefile

To create following
1. exectuble [for function which as main method]
2. libraries [independent libraries]
3. installation [installation of libraries]
