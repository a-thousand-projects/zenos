//
// Created by graeme on 09/08/2026.
//

#ifndef ZENOS_PMM_H
#define ZENOS_PMM_H
#include <stdint.h>
#include <kernel/error_codes.h>
#define PAGE_SIZE 4096
#define BITS_PER_ROW 32

uint32_t bit_number(const uint16_t row, const uint16_t column);
uint32_t address(uint32_t bit_number);
zenos_err_t pmm_init(void);
zenos_err_t pmm_free_page(uint32_t page);
char pmm_page_status(uint32_t page);
zenos_err_t pmm_set_page(uint32_t page);
void pmm_print(void);


#endif //ZENOS_PMM_H
