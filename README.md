# MiniMallocPlus

MiniMallocPlus is a **custom memory allocator** implemented in C.  
It simulates dynamic memory allocation using a fixed **1 MB memory pool**.  
The allocator supports **allocation, freeing, memory stats, fragmentation calculation, and logging**.

---

## Features

- First-Fit, Best-Fit, Worst-Fit, Next-Fit, and Quick-Fit allocation strategies.
- Tracks allocations and frees with file/line info.
- Prints memory layout and statistics (allocated, free, fragmentation, active blocks).
- Logs memory events to `memory_log.txt`.
- Works on **Windows** and **Linux**.
- Merges adjacent free blocks to reduce fragmentation.

---

## Project Structure

```

MiniMallocPlus/
│
├─ include/
│   ├─ mini\_malloc.h
│   └─ logger.h
│
├─ src/
│   ├─ main.c
│   ├─ mini\_malloc.c
│   ├─ memory\_stats.c
│   └─ logger.c
│
├─ Makefile
└─ README.md

````

---

## Installation & Build

### Linux

```bash
git clone <repo_url>
cd MiniMallocPlus
make
./MiniMallocPlus
````

### Windows (using MinGW)

1. Install [MinGW-w64](https://www.mingw-w64.org/) and ensure `gcc` and `make` are in your PATH.
2. Open **PowerShell** or **cmd**, navigate to the project folder:

```powershell
cd C:\path\to\MiniMallocPlus
make
.\MiniMallocPlus.exe
```

---

## Usage

* Run the executable to see memory allocation, free blocks, and stats.
* Logs of allocations/frees are written to `memory_log.txt`.
* You can modify the allocation strategy in `main.c`:

```c
set_allocation_strategy(FIRST_FIT);   // FIRST_FIT, BEST_FIT, WORST_FIT, NEXT_FIT, QUICK_FIT
```

* Add/remove allocations using `mini_malloc(size)` and `mini_free(ptr)`.

---

## Output Example

```
MiniMallocPlus Demo

Step 1: Allocate a=100, b=200, c=50
Memory Stats:
Total Memory       : 1048576 bytes
Allocated          : 350 bytes
Free               : 1048226 bytes
Fragmentation      : 0.02%
Active Allocations : 3
Largest Free Block : 1048034 bytes

Step 2: Free b
Memory Stats:
Total Memory       : 1048576 bytes
Allocated          : 150 bytes
Free               : 1048426 bytes
Fragmentation      : 0.04%
Active Allocations : 2
Largest Free Block : 1048034 bytes

Step 3: Allocate d=150
Memory Stats:
Total Memory       : 1048576 bytes
Allocated          : 300 bytes
Free               : 1048276 bytes
Fragmentation      : 0.02%
Active Allocations : 3
Largest Free Block : 1048034 bytes
```

> Note: Output format is cleaned for better readability.

---

## Allocation Strategies Explained

1. **First-Fit**:

   * Allocates the first free block that is large enough.
   * Fast, simple, may leave small fragmented blocks at the start.

2. **Best-Fit**:

   * Allocates the **smallest free block** that fits the request.
   * Reduces leftover space but slower to find the block.

3. **Worst-Fit**:

   * Allocates the **largest free block**.
   * Leaves medium-sized blocks for future allocations.

4. **Next-Fit**:

   * Like First-Fit, but starts searching from the **last allocation**.
   * Can improve performance in some patterns but may fragment the start.

5. **Quick-Fit**:

   * Maintains free lists by block size for fast allocation.
   * Simplified in this demo version.

---

## License

This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.

```