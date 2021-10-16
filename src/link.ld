/*  Bei _start soll die Ausfuehrung losgehen */
ENTRY(_start)

/*
 * Hier wird festgelegt, in welcher Reihenfolge welche Sektionen in die Binary
 * geschrieben werden sollen
 */
SECTIONS
{
    /*
     * . ist die aktuelle Position in der Datei. Wir wollen den Kernel wie gehabt
     * an 1 MB laden, also muessen wir dort die erste Sektion hinlegen
     */
    . = 0x100000;

    /* Symbol fuer den Kernelanfang definieren */
    kernel_start = .;

    /*
     * Der Multiboot-Header muss zuerst kommen (in den ersten 8 kB).
     * Die Standardsektionen einfach hintereinander weg einbinden.
     */
    .text : {
        *(multiboot)
        *(.text)
    }
    .data ALIGN(4096) : {
        *(.data)
    }
    .rodata ALIGN(4096) : {
        *(.rodata)
    }
    .bss ALIGN(4096) : {
        *(.bss)
    }

    /* Symbole fuer das Kernelende definieren (auf 4k aufrunden) */
    . = ALIGN(4096);
    kernel_end = .;
}