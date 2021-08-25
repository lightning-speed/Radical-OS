SECTIONS {
    .text ALIGN(2K) : {
        *(.text*)
    }
    .rodata ALIGN(2K) : {
        *(.rodata*)
    }
    .data ALIGN(2K) : {
        *(.data*)
    }
    .bss ALIGN(2K) : {
        *(COMMON)
        *(.bss*)

        _stack_bottom = .;
        . += 8K;
        _stack_top = .;
    }
}