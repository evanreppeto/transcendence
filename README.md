# A3: Transcend Yourself - Sequence Finder

**Course:** CIS 350: Advanced Data Structures and Algorithms  
**Project:** Transcendental Number Sequence Searcher

## Project Overview
This project implements a highly optimized string-matching algorithm to search for specific numeric sequences (such as a user's birthday) within the digits of Pi. It features an interactive Terminal User Interface (TUI) and records precise execution times.

## Algorithm Analysis: Boyer-Moore-Horspool
Rather than utilizing a naive Brute-Force approach (O(N * M)) or the standard C++ `std::string::find()`, this application implements a custom **Boyer-Moore-Horspool** algorithm. 

* **How it works:** The algorithm aligns the target sequence with the Pi text but compares characters from *right to left*. By pre-computing a "Bad Character Skip Table," the algorithm intelligently shifts the search window by multiple indices at once when it encounters a mismatch, entirely skipping useless data.
* **Time Complexity:** * **Best Case:** O(N / M) — The algorithm jumps ahead by the length of the pattern (M) on every mismatch, providing sub-linear performance. This makes it exceptionally fast for searching large texts.
  * **Worst Case:** O(N * M) — Occurs only in highly repetitive data that defeats the skip heuristic.
* **Space Complexity:** O(1) — The skip table is fixed at 256 indices (for all ASCII characters), resulting in constant extra memory allocation regardless of the input size.

## Search Results (Birthday Index)
* **Target Sequence:** 11012004
* **Index of Occurrence:** 196716067
* **Execution Time:** 767.298 ms
*(Note: A dataset of 1,000,000,000 Pi digits was utilized for testing).*

## Scope for Improvements
1. **Chunked Memory Loading:** Currently, the entire `pi-billion.txt` file is loaded into heap memory. For billion-digit numbers, the algorithm should stream the file in chunks to prevent RAM exhaustion.
2. **Multithreaded Searching:** Implementing `std::thread` to segment the text and run the search concurrently across multiple CPU cores would significantly decrease search times on massive datasets.
