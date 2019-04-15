# -*- coding: utf-8 -*-

# This is the answers file for the CMPSC 473 - Spring 2019 - Project #1
# Answers data structures
# DO NOT MODIFY THESE VARIABLES HERE
wordy = {
    "1b": None,
    "1d": None,
    "1e": None,
    "2b": None,
    "2c": None,
    "2d": None,
    "2e": None,
    "3b": None,
    "3c": None,
    "4a": None,
    "4bi": None,
    "4bii": None,
    "4biii": None,
    "4biv": None,
    "4bv": None,
    "4bvi": None
}
numerical = {
    "1a": None,
    "1c": None,
    "2ai32": None,
    "2aii32": None,
    "2aiii32": None,
    "2ai64": None,
    "2aii64": None,
    "2aiii64": None,
    "3ai32": None,
    "3aii32": None,
    "3aiii32": None,
    "3ai64": None,
    "3aii64": None,
    "3aiii64": None,
}

###########################################################
# Answer Section
# You may edit the values of variables below
###########################################################

# FILL OUT YOUR ID AND ANSWERS BELOW
# PSU ID (e.g. xyz1234)
ID = "oza5"

###########################################################
# (1) Stack, heap, and system calls
###########################################################

# (1.a) What is the size of the proces stack when it is
#   waiting for user input?
#   Enter your answer in bytes.
numerical["1a"] = 84000

# (1.b) Which addresses are for the local variables and
#   which ones are for the dynamically allocated variables?
#   What are the directions in which the stack and the heap
#   grow on your system?
wordy["1b"] =  "Address 1 addresses belong to local variables whereas Address 2 addresses belong to the dynamically allocated variables. This is because the stack usually occupies higher addresses compared to the heap and the stack holds local variables. When looking at the addresses, we notice that the stack grows downwards (Address 1 decreases) as it should on most systems and the heap grows upwards (Address 2 increases)"

# (1.c) What is the size of the process heap when it
#   is waiting for user input?
#   Enter your answer in bytes.
numerical["1c"] = 132000

# (1.d) What are the address limits of the stack and the heap?
wordy["1d"] = "stack-7ffe946dc000-7ffe946f1000 & heap-011e9000-0120a000"

# (1.e) For each unique system call, write in your own words
#   (just one sentence should do) what purpose this system
#   call serves for this program.
wordy["1e"] =  "#execve(): Executes and runs the program.#mmap():used to dynamically allocate variables to the heap in the virtual address space.#open(): Returns a file descriptor and is mostly used to reference libraries.#close(): Close file with specific file descriptor, used on opened libraries.#read(): Reads all the commands in file being executed.#mprotect(): Make sure that memory accesses violations are not caused .#munmap(): same function as mmap() owever it has different arguments.#arch_prctl(): Sets architecture-specific thread state for the virtual-address space.#write():Allows for the program to output to the cmd line. #brk(): Sets the location of the program break so that the program does not unintentionally overwrite occupied addresses. #exit_group(): Terminates the program exiting all threads.#access(): Validates all user permissions to execute the file. #fstat(): Returns information about the file."

###########################################################
# (2) Debugging Refresher
###########################################################

# (2.a) Observe and report the differences in the following
#   for the 32-bit and 64-bit executables

# (2.a.i.32) size of compiled code (32-bit)
#   Enter your answer in bytes.
numerical["2ai32"] = 1691

# (2.a.ii.32) size of code during run time (32-bit)
#   Enter your answer in bytes.
numerical["2aii32"] = "13816 x 1024 = 14147584 Bytes.Using gdb we run the code and then place a break at line 6. We then continue just before we segment,once that is done we use pgrep to get the pid and use pmap pid to get the information we need."
 
# (2.a.iii.32) size of linked libraries (32-bit)
#   Enter your answer in bytes.
numerical["2aiii32"] ="1789952 Bytes, Using gdb we run the code and then place a break at line 6. We then continue just before we segment,once that is done we use pgrep to get the pid and use pmap pid to get the information we need.In this info we add all line with lib in them."

# (2.a.i.64) size of compiled code (64-bit)
#   Enter your answer in bytes.
numerical["2ai64"] = 2183

# (2.a.ii.64) size of code during run time (64-bit)
#   Enter your answer in bytes.
numerical["2aii64"] = "15872 x 1024 = 16252928 Bytes Using gdb we run the code and then place a break at line 6. We then continue just before we segment,once that is done we use pgrep to get the pid and use pmap pid to get the information we need."

# (2.a.iii.64) size of linked libraries (64-bit)
#   Enter your answer in bytes.
numerical["2aiii64"] ="3874816 Bytes Using gdb run the code and then place a break at line 6. We then continue just before we segment,once that is done we use pgrep to get the pid and use pmap pid to get the information we need.In this info we add all line with lib in them."


# (2.b) Use gdb to find the program statement that
#   caused the error
wordy["2b"] = "line 6 in prog2.c is where the error occurs where :int x [300000]"

# (2.c) Explain the cause of this error.
wordy["2c"] = "A segfault is caused because we are allocating more space to the stack than it can store."

# (2.d) Examine individual frames in the stack to find each
#   frame's size. Estimate the number of invocations of the
#   recursive function that should be possible. How many
#   invocations occur when you actually execute the program?
wordy["2d"] = "We use stack info of two consecutive stack frame to determine the size of each frame. We get that the size is 0x124FB0 or 1200048 in decimal.Our allocation in line 6 needs 300000x4 = 1200000bytes. The stack is 12009472 bytes big (from stack limits). The recursive function should be called 10 (stack size/frame size) times before a segfault happens. This represents what is happening in our program."

# (2.e) What are the contents of a frame in general?
#   Which of these are present in a frame corresponding
#   to an invocation of the recursive function and
#   what are their sizes?
wordy["2e"] =  "A frame usually contains local variables, return addresses and temporary parameters. mostly data in the frames are local variables. Their size is 1200000 bytes. The 48 remaining bytes are present for the return address."

###########################################################
# (3) More debugging
###########################################################

# (3.a) Observe and report the differences in the following
#   for the 32-bit and 64-bit executables:

# (3.a.i.32) size of compiled code (32-bit)
#   Enter your answer in bytes.
numerical["3ai32"] = 1984

# (3.a.ii.32) size of code during run time (32-bit)
#   Enter your answer in bytes.
numerical["3aii32"] = "437184 x 1024 = 447676416 Bytes. Using gdb we run the code and then place a break at line 6. We then continue just before we segment,once that is done we use pgrep to get the pid and use pmap pid to get the information we need." 

# (3.a.iii.32) size of linked libraries (32-bit)
#   Enter your answer in bytes.
numerical["3aiii32"] = "1961984 bytes Using gdb run the code and then place a break at line that causes error. We then continue just before we segment,once that is done we use pgrep to get the pid and use pmap pid to get the information we need.In this info we add all line with lib in them."

# (3.a.i.64) size of compiled code (64-bit)
#   Enter your answer in bytes.
numerical["3ai64"] = 2556

# (3.a.ii.64) size of code during run time (64-bit)
#   Enter your answer in bytes.
numerical["3aii64"] = "43474916 x 1024 = 4.451831398 x 10^10 bytes.Using gdb we run the code and then place a break at line that causes error. We then continue just before we segment,once that is done we use pgrep to get the pid and use pmap pid to get the information we need."

# (3.a.iii.64) size of linked libraries (64-bit)
#   Enter your answer in bytes.
numerical["3aiii64"] = "6512640 bytes Using gdb run the code and then place a break at line that causes error. We then continue just before we segment,once that is done we use pgrep to get the pid and use pmap pid to get the information we need.In this info we add all line with lib in them."

# (3.b) Use valgrind to find the cause of the error
#   including the program statement causing it
wordy["3b"] = "Using valgrind, we can see that t problem is at line 13. However, the line is exponentially mallocing more and more memory to the point where it overflows the heap causing a memory leak."

# (3.c) How is this error different than the one for prog2?
wordy["3c"] = "both are memory overflows prog2 is a stack overflow whereas prog3 is a memory leak caused due to heap overflow."

###########################################################
# (4) And some more
###########################################################

# (4.a) Describe the cause and nature of these errors.
#   How would you fix them?
wordy["4a"] = "The cause of this error is once again a memory leak caused by huge number of mallocs by allocate() and in comparison lower numbers of free() used. To solve this we can use free() with all of our malloc statements."

# (4.b) Modify the program to use getrusage for measuring the following:

# (4.b.i) user CPU time used
wordy["4bi"] = "0.00091386 secs"

# (4.b.ii) system CPU time used
#   What is the difference between (i) and (ii)?
wordy["4bii"] = "0.000467928 secs.User CPU time is basically time spent by the kernel to execute user instructions whereas time spent by operating system code on behalf of processes is system CPU time."

# (4.b.iii) maximum resident set size
#   what is this?
wordy["4biii"] = "1814676 bytes, A processe's resident set size is the amount of memory that is acquired and is currently present in RAM."

# (4.b.iv) signals received
#   Who may have sent these?
wordy["4biv"] = "0 signals. These may have been sent by the CPU to cause a trap it could also be possibly because of user caused interrupt."

# (4.b.v) voluntary context switches
wordy["4bv"] = "2"

# (4.b.vi) involuntary context switches
#   what is the difference between (v) and (vi)?
wordy["4bvi"] = "142. A voluntary context switch is usually initiated by the thread itself. An involuntary context switch is usually forced by the system scheduler upon the thread and changes the process control to another thread to allow priority scheduling and use of the CPU."

###########################################################
# Sanity Check
# DO NOT MODIFY ANYTHING BELOW HERE
###########################################################
if ID == "":
    print("Please fill out your student ID in the variable ID")
for key in numerical:
    if type(numerical[key]) is not int:
        print("Type error of answer %s (should be a numerical value)" % key)
for key in wordy:
    if type(wordy[key]) is not str:
        print("Type error of answer %s (should be a string)" % key)
