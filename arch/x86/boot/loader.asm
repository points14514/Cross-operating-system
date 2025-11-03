; 定义程序加载基地址（例如 0x1000h）
org 0x1000h

; 包含头文件（如 FAT12 文件系统结构定义）
%include "fat12.inc"

; 定义常量（如内核加载位置）
BaseOfKernel equ 0x8000
OffsetOfKernel equ 0x0000

; 程序入口点
start:
    ; 初始化段寄存器（DS、ES、SS）和堆栈指针（SP）
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; 显示加载信息（通过 BIOS 中断）
    mov si, msg_loading
    call print_string

    ; 检测系统内存布局（使用 INT 15h, EAX=0xE820）
    call detect_memory

    ; 在磁盘根目录中搜索内核文件（如 KERNEL.BIN）
    mov si, kernel_filename
    call find_file

    ; 将内核文件加载到内存指定位置（如 0x8000:0x0000）
    call load_kernel

    ; 准备并切换到保护模式：
    ; 1. 关闭中断（CLI）
    ; 2. 加载全局描述符表（LGDT）
    ; 3. 设置 CR0 寄存器保护模式位
    ; 4. 远跳转至保护模式代码段
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:protected_mode_entry

; 保护模式代码段（32 位）
use32
protected_mode_entry:
    ; 初始化保护模式下的段寄存器（DS、ES、FS、GS、SS）和堆栈指针（ESP）
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000  ; 设置内核堆栈

    ; 跳转到已加载的内核入口点
    jmp BaseOfKernel:OffsetOfKernel

; 子函数定义（实模式下运行）
print_string:  ; 通过 BIOS 中断显示字符串（DS:SI 指向字符串）
    mov ah, 0x0E
.print_loop:
    lodsb
    test al, al
    jz .done
    int 0x10
    jmp .print_loop
.done:
    ret

detect_memory:  ; 使用 INT 15h, EAX=0xE820 检测内存
    mov eax, 0xE820
    mov ecx, 24
    mov edx, 0x534D4150  ; 签名 "SMAP"
    int 0x15
    jc .error
    ; 处理返回的地址范围描述符（ARDS）
    ret
.error:
    mov si, msg_memory_error
    call print_string
    ret

find_file:     ; 在根目录中搜索文件（文件名由 DS:SI 指向）
    ; 遍历根目录项，比较文件名
    ret

load_kernel:   ; 根据目录项中的簇号，通过 FAT 表加载文件内容
    ret

; 数据区定义
msg_loading db "Loading kernel...", 0
msg_memory_error db "Memory detection failed!", 0
kernel_filename db "KERNELBIN", 0  ; FAT12 格式文件名（8.3 格式，空格填充）

; GDT 定义（全局描述符表）
gdt_start:
    dq 0x0000000000000000  ; 空描述符
gdt_code:
    dq 0x00CF9A000000FFFF  ; 32 位代码段描述符
gdt_data:
    dq 0x00CF92000000FFFF  ; 32 位数据段描述符
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; GDT 界限
    dd gdt_start                ; GDT 基地址

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; 填充剩余空间（可选，取决于加载器大小）
times 2048 - ($ - $$) db 0
