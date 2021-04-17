#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, const char* argv[])
{    
    int num_pages = argc > 1 ? std::atoi(argv[1]) : 100;
    int num_iterations = argc > 2 ? std::atoi(argv[2]) : 100;
    bool write_mem = false;
    bool no_unmap = false;
    bool populate = false;

    for (int i = 3; i < argc; i++) {
        if (!strcmp(argv[i], "write"))
            write_mem = true;
        else if (!strcmp(argv[i], "no_unmap"))
            no_unmap = true;
        else if (!strcmp(argv[i], "populate"))
            populate = true;
    }

    int page_size = sysconf(_SC_PAGESIZE);
    int buf_size = page_size * num_pages;

    std::cout << "Allocating " << num_pages << " pages " << num_iterations 
        << " times (" << buf_size / (1024.0 * 1024.0) << " Mb)\n";

    for (int i = 0; i < num_iterations; i++) {
        void* buf = mmap(nullptr, buf_size, PROT_READ | PROT_WRITE, 
            MAP_ANONYMOUS | MAP_PRIVATE | (populate ? MAP_POPULATE : 0), -1, 0);
        
        if (buf == MAP_FAILED) {
            std::cerr << "mmap failed!\n";
            return 1;
        }

        // Write 1 byte to every page
        if (write_mem)
            for (int j = 0; j < num_pages; j++)
                *((char*)buf + j * page_size) = 'A';

        if (!no_unmap)
            munmap(buf, buf_size);
    }

    return 0;
}