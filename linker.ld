ENTRY(_start)

SECTIONS
{
    . = 2M;


    .text : {
        *(.text)
    } 
     
    . += 0x1000;

    .rodata : {
        *(.rodata*)
    }

    . += 0x1000;

    .data : {
        *(.data*)
    } 

    .bss : {
        *(COMMON)
        *(.bss*)
    }
		. += 0x1000;
		ramdisk_start = . + 4;
    .ramdisk : {
      *(.ramdisk)
		}
		ramdisk_end = . - 4;
}