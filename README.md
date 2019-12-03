# CSCI3150 Asgn3 Unofficial Testcase
This is an unofficial testcase program for CSCI3150 Asgn3. Inspired by Eric Lo's homework grading way.
This program might not include all requirements.
If you get a full mark in this program, it does not mean that you can get full mark in official grading way.
Welcome to modify the testcases in it.  
If you have any problem, you can open an issue.

## Paging with Swap
Just put your kernel.c in it.
```
make
./runtest <test case no.>
    //'0'~'9' to select a test case
    //'10' to run all the test cases
    //'11' to run all test cases separately
```


testsuite.txt file:
```
<Number of testcase>
<Number of action> <File path>
```

testcase_x.txt file:
```C
KERNEL_SPACE_SIZE <Kernel size>
VIRTUAL_SPACE_SIZE <Virtuak size>
PAGE_SIZE <Page size>
MAX_PROCESS_NUM <Number of max process>
create <memory> <pidAnswer>
read <pid> <addr> <size> <buf_size> <text read> <Answer>
//if <text read> == nil which means nothing to read
write <pid> addr size buf_size text Answer
//if <text write> == nil which means nothing to read
exit <pid> <Answer>
check <str>#
```

Testcase:  
```

```


