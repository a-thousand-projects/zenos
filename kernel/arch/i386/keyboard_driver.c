#include <kernel/keyboard_driver.h>
#include "stdio.h"
#include <kernel/registers.h>
#include "irq.h"
#include <kernel/interrupt_driver.h>
#include <kernel/port_driver.h>
#include <kernel/tty.h>
#include <kernel/vga.h>

#define IRQ1 33

#define KEY_SHIFT_DOWN 0x2a
#define KEY_SHIFT_UP   0xaa

int isShift = 0;
                        //   0      1        2       3       4       5       6       7       8       9
static char key_map[256] = { 0   ,  0    ,  '1'  ,  '2'  ,  '3'  ,  '4'  ,  '5'  ,  '6'  ,  '7'  ,  '8'  , // 0x09
                            '9'  ,  '0'  ,  '-'  ,  '='  ,  0    ,  0    ,  'q'  ,  'w'  ,  'e'  ,  'r'  , // 0x13
                            't'  ,  'y'  ,  'u'  ,  'i'  ,  'o'  ,  'p'  ,  '['  ,  ']'  ,  0    ,  0    , // 0x1D
                            'a'  ,  's'  ,  'd'  ,  'f'  ,  'g'  ,  'h'  ,  'j'  ,  'k'  ,  'l'  ,  ';'  , // 0x27
                            '\'' ,  '`'  ,  0    ,  '#'  ,  'z'  ,  'x'  ,  'c'  ,  'v'  ,  'b'  ,  'n'  , // 0x31
                            'm'  ,  ','  ,  '.'  ,  '/'  ,   0   ,   0   ,   0   ,   0   ,   0    ,  0   , // 0x3B
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0    ,  0   , // 0x45
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0    ,  0   , // 0x4F
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,  '\\' ,   0   ,   0    ,  0   , // 0x59
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0    ,  0   , // 0x63
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0    ,  0   , // 0x6D
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0    ,  0   , // 0x77
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,                 // 0x7F   

                             0   ,   0   ,  '!'  ,  '"'  ,   0   ,  '$'  ,  '%'  ,  '^'  ,  '&'  ,  '*'  , // 0x7F             // TODO : Find out why £ is odd
                            '('  ,  ')'  ,  '-'  ,  '='  ,   0   ,   0   ,  'Q'  ,  'W'  ,  'E'  ,  'R'  , // 0x89
                            'T'  ,  'Y'  ,  'U'  ,  'I'  ,  'O'  ,  'P'  ,  '{'  ,  '}'  ,   0   ,   0   , // 0x93
                            'A'  ,  'S'  ,  'D'  ,  'F'  ,  'G'  ,  'H'  ,  'J'  ,  'K'  ,  'L'  ,  ':'  , // 0x9D
                            '@'  ,   0   ,   0   ,  '~'  ,  'Z'  ,  'X'  ,  'C'  ,  'V'  ,  'B'  ,  'N'  , // 0xA7       // Todo : ¬ 
                            'M'  ,  '<'  ,  '>'  ,  '?'  ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   , // 0xB1
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   , // 0xBB
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   , // 0xC5
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,  '|'  ,   0   ,   0   ,   0   , // 0xCF
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   , // 0xD9
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   , // 0xE3
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   , // 0xED
                             0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0   ,   0                     // 0xF7
                            };             
                           


static char isLetter(const char c)
{
    return(c >= 'A' && c<= 'Z');
}


static void keyboard_callback(registers_t *regs) {

    unsigned char scancode = port_byte_in(0x60);
    //printf("Code: %x\n",scancode);
    switch (scancode)
    {
        case KEY_SHIFT_DOWN :
            isShift = 1;
            terminal_putentryat('S',VGA_COLOR_LIGHT_CYAN,79,24);
        break;
        case (KEY_SHIFT_UP):
            isShift = 0;
            terminal_putentryat(' ',VGA_COLOR_LIGHT_CYAN,79,24);
        break;
        default:
            if (scancode < 128)
            {
                unsigned char c = key_map[scancode+( isShift * 0x80)];
                terminal_putchar(c);
            }
        break;
    }

//    printf("Keyboard interrupt received! [%x]\n", scancode); 
}

void keyboard_init()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}

