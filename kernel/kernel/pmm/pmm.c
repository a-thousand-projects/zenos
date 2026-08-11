//
// Created by graeme on 09/08/2026.
//
#include <stdint.h>
#include <kernel/pmm.h>
#include <kernel/error_codes.h>
#include <stdio.h>
static uint32_t page_bitmap = 0;

uint32_t bit_number(const uint16_t row, const uint16_t column)
{
    return (row * BITS_PER_ROW) + column;
}

uint32_t address(uint32_t bit_number)
{
    return bit_number * BITS_PER_ROW;
}

zenos_err_t pmm_init(void)
{
    page_bitmap = 0;




    return ERR_OK;
}


zenos_err_t pmm_free_page(uint32_t page)
{
    page_bitmap &= ~(1 << page);
    return ERR_OK;
}

char pmm_page_status(uint32_t page)
{
    return (page_bitmap && (1 << page))>0;
}

zenos_err_t pmm_set_page(uint32_t page)
{
  //  if (!pmm_page_status(page))
    {
        page_bitmap |= (1 << page);
        return ERR_OK;
    }
    return ERR_FAIL;
}

void pmm_print(void)
{
    printf("Page Bitmap: 0x%x\n\r", page_bitmap);
}
