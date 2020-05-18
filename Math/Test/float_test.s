    .global _main
    .data
FLOAT_1:
    .single     -1073741824
PRT_FORMAT:
    .ascii      "%f\n\0"
    .text
_main:
    pushl       %ebp
    movl        %esp, %ebp
    andl        $-16, %esp
    pushl       (FLOAT_1)
    pushl       $PRT_FORMAT
    call        _printf
    movl        $0, %ebx
    leave
    ret
