#include <stdio.h>
#include <kernel/error_codes.h>
#include <kernel/pmm.h>
void pmm_test_page_bitmap()
{
    // TEST
    char isfree;
    uint32_t page = 17;
    isfree = pmm_page_status(page);
    if (isfree == ERR_OK)
    {
        printf("is Free test 1 PASS\n\r");
    }
    else
    {
        printf("is Free test 1 FAIL\n\r");
    }
    pmm_print();
    printf("Set page %d test",page);
    pmm_set_page(page);
    pmm_print();
    isfree = pmm_page_status(page);
    if (isfree == 1)
    {
        printf("Page %d is not free PASS\n\r", page);
    }
    else
    {
        printf("Page %d is free FAIL\n\r", page);
    }
    printf("free page %d test",page);
    pmm_free_page(page);
    isfree = pmm_page_status(page);
    if (isfree == 1)
    {
        printf("Page %d is not free FAIL\n\r", page);
    }
    else
    {
        printf("Page %d is free PASS\n\r", page);
    }

    pmm_print();
}


void pmm_run_tests()
{
    pmm_test_page_bitmap();
}
