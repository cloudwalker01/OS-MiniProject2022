OS-MiniProject-2022

Introduction

Virtual memory is a technique that abstracts main memory into a large, uniform array of storage, separating the logical memory perceived by the user from the physical memory. This frees the programmer from concerns of storage limitations and allows the execution of processes that are not completely in memory. 
This is generally achieved through the strategy of demand paging, where pages are loaded only as they are needed during program execution. Pages reside in secondary memory and are swapped into main memory when the process is loaded. The pager swaps in only those pages are likely to be needed, and replaces pages from secondary memory in case of page faults, i.e, if the page we need is not loaded into the main memory.







Overview

This implementation of virtual memory management uses pure demand paging with an inverted page table, along with global replacement. The page table is represented by a vector containing pairs of the form {pid,page_num}. Several page replacement algorithms such as OPT, LRU, MRU, LIFO and FIFO have been implemented. All of these internally use a list to keep track of the pages that are currently in main memory, along with a map for faster lookup and deletion.
