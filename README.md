# CSCI3150 Asgn3 Unofficial Testcase

## Paging

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
0. Original Demo testcase
1. Testing Create Failure (MAX process)
2. Testing Create Failure (Not enough Kernel space)
3. Testing memory mapping (Not continuous page mapping)
4. Testing Read/Write Failure (Out of bound)

## Paging with Swap
Upload it Later
