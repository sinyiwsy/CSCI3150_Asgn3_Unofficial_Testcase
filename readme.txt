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
1. Testing Create & Exit Failure (MAX process, no such process exist)
2. Testing Read/Write Failure (Out of bound)
3. Testing Create with swap & Read/Write (Not enough Kernel space)
4. Testing Read/Write with swap ()
5. Testing Read/Write with Exit ()
6. Testing Read/Write with 2 swap ()
7. Testing Read/Write with Exit (manual check)
8. Testing Dirty bit ()

Misc:


