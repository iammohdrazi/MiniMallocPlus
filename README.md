```markdown
# MiniMallocPlus

**MiniMallocPlus** is a **custom memory allocator** implemented in C.  
It simulates dynamic memory allocation using a fixed **1 MB memory pool**.  
The allocator supports **allocation, freeing, memory stats, fragmentation calculation, and logging**.

---

## Features

- First-Fit, Best-Fit, Worst-Fit, Next-Fit, and Quick-Fit allocation strategies.
- Tracks allocations and frees with file/line info.
- Prints memory layout and statistics:
  - Total memory
  - Allocated memory
  - Free memory
  - Fragmentation percentage
  - Active allocations
  - Largest free block
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

* Run the executable to select a memory allocation strategy and view memory allocation stats.
* Logs of allocations and frees are written to `memory_log.txt`.
* Modify the allocation strategy in `main.c`:

```c
set_allocation_strategy(FIRST_FIT);   // FIRST_FIT, BEST_FIT, WORST_FIT, NEXT_FIT, QUICK_FIT
```

* Add/remove allocations using `mini_malloc(size)` and `mini_free(ptr)`.
* If you change the allocation strategy: run `make clean` and then `make`.

---

## Interactive Demo Example

```
=== MiniMallocPlus ===

Select allocation strategy:
1) First-Fit
2) Best-Fit
3) Worst-Fit
4) Next-Fit
5) Quick-Fit
Enter choice: 2

=== BEST-FIT ===

Demo Allocations:
Memory Stats:
  Total Memory       :    1048576 bytes
  Allocated          :        350 bytes
  Free               :    1048226 bytes
  Fragmentation      :      0.02%
  Active Allocations :          3
  Largest Free Block :    1048034 bytes

Free b (200 bytes)
Memory Stats:
  Total Memory       :    1048576 bytes
  Allocated          :        150 bytes
  Free               :    1048426 bytes
  Fragmentation      :      0.04%
  Active Allocations :          2
  Largest Free Block :    1048034 bytes

Allocate d=150 bytes
Memory Stats:
  Total Memory       :    1048576 bytes
  Allocated          :        300 bytes
  Free               :    1048156 bytes
  Fragmentation      :      0.02%
  Active Allocations :          3
  Largest Free Block :    1048034 bytes

Continue? (y/n):
```

---

## Allocation Strategies & Example Behaviors

| Strategy      | How It Works                                               | Example Behavior                                                 |
| ------------- | ---------------------------------------------------------- | ---------------------------------------------------------------- |
| **First-Fit** | Allocates the **first free block** large enough            | Fast allocation; may leave small fragmented blocks at the start  |
| **Best-Fit**  | Allocates the **smallest block** that fits                 | Minimizes leftover space; slower search                          |
| **Worst-Fit** | Allocates the **largest free block**                       | Leaves medium-sized blocks; may reduce fragmentation later       |
| **Next-Fit**  | Like First-Fit but starts from **last allocation**         | Can improve performance in certain allocation patterns           |
| **Quick-Fit** | Maintains free lists by block size for **fast allocation** | Very fast allocation for repeated sizes; simplified in this demo |

---

## Visual Memory Layout Example

### Initial State (1 MB Free)

```
[Free: 1048576 bytes]
```

### After Allocating a=100, b=200, c=50 (First-Fit)

```
[Allocated a:100] [Allocated b:200] [Allocated c:50] [Free: 1048226]
```

### After Freeing b (200)

```
[Allocated a:100] [Free:200] [Allocated c:50] [Free: 1048026]
```

### After Allocating d=150

* **First-Fit** allocates in the first free block >=150 → merges or moves as needed.
* **Best-Fit** allocates in the smallest free block >=150.
* **Worst-Fit** allocates in the largest free block.
* **Next-Fit** continues from the last allocation pointer.
* **Quick-Fit** allocates using the quick-size free list if available.

```
Example (First-Fit):
[Allocated a:100] [Allocated d:150] [Allocated c:50] [Free: 1048026]
```

---

## License

This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.
