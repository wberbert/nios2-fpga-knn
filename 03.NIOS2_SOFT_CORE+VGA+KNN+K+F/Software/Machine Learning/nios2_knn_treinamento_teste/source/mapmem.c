#include "../include/mapmem.h"


void *f_Mapear_Memoria(unsigned long int addr, mapear_memoria_modo_t mode) {
    int fd;
    void *map_base, *virt_addr;
    //off_t target;
    unsigned page_size, mapped_size, offset_in_page;
    unsigned width = 16; //16 bits


    //target = strtoull(addr, NULL, 0); /* allows hex, oct etc */
    if (mode == LEITURA) fd = open("/dev/mem", (O_RDONLY | O_SYNC));
    if (mode == ESCRITA) fd = open("/dev/mem", (O_RDWR | O_SYNC));
    //fd = fopen("/dev/mem", "rw");

    mapped_size = page_size = getpagesize();

    offset_in_page = (off_t) addr & (page_size - 1);

    if (offset_in_page + width > page_size) {
		/* This access spans pages.
		 * Must map two pages to make it possible: */
		mapped_size *= 2;
	}

    map_base = mmap(NULL,
                    mapped_size,
                    mode == LEITURA ? PROT_READ: PROT_WRITE,
                    MAP_SHARED,
                    fd,
                    (off_t) addr & ~(off_t)(page_size - 1));

    //printf ("%d\n", fd);
    //printf("%d\n", mapped_size);
    //printf("Memory mapped at address %p.\n", addr);
    assert(map_base != MAP_FAILED);

	//if (map_base == MAP_FAILED)
//		bb_perror_msg_and_die("mmap");

    virt_addr = (char*)map_base + offset_in_page;

   // printf("Memory mapped at address %p.\n", map_base);

    return virt_addr;
}
