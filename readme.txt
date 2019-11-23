testcase file:
KERNEL_SPACE_SIZE 8192
VIRTUAL_SPACE_SIZE 512
PAGE_SIZE 32
MAX_PROCESS_NUM 8
create memory pidAnswer
read pid addr size buf_size Answer
check str#
write pid addr size buf_size text Answer
exit pid Answer

testsuite file:
line file

testcase:
0. Original Demo testcase
1. Testing Create Failure (MAX process)
2. Testing Create Failure (Not enough Kernel space)
3. Testing memory mapping (Not continuous page mapping)
4. Testing Read/Write Failure (Out of bound)
