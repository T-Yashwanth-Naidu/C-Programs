Few quick notes:

- System Memory Allocation:
	•	Memory is often allocated in chunks based on page sizes (usually 4 KB or more). Even when smaller allocations are requested (e.g., 256 bytes), the system might allocate extra space to align with page boundaries.
	
	•	This alignment can result in some parts of the allocated range remaining unused, leading to discrepancies between the allocated range and the actually utilized memory.

- sbrk Functionality:
	•	sbrk adjusts the program's data segment by the requested number of bytes. Due to alignment, it often moves the break (end of the data segment) more than the exact number requested, resulting in unutilized space.

Now the code: 

- The allocate_memory function grabs memory using sbrk(). It bumps up the program's data space by the number of bytes you specify and returns the pointer to where the new memory starts.

- head holds the start address of where our first allocation kicks off.

- total_allocated keeps count of the total bytes we’ve allocated so far.

- Memory gets chunked up and allocated in 256-byte blocks, one after another.

- The allocated memory is then filled up with numbers starting from zero, going up one by one.

- The program later reads these numbers and tries to access some memory spots towards the edge of what’s been allocated, showing what happens when you stick to your limits and what risks pop up when you go beyond.

- When printing Total available range, it shows the entire memory span from the first allocation (head) to where the last chunk was allocated (current_address). This includes any extra room added because of how the system aligns memory, which is why there’s a gap between the last used spot and the end of the reported range.


