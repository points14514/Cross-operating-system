;------------- loader和kernel配置常量 ----------
LOADER_BASE_ADDR equ 0x900   ; Loader被加载到内存中的基地址
LOADER_START_SECTOR equ 0x2  ; Loader在硬盘上的起始扇区号（LBA地址）

;-------------- GDT描述符属性 -------------
; 段描述符的高4字节相关属性
DESC_G_4K equ 1_00000000000000000000000b   ; G位，段粒度，1表示4K
DESC_D_32 equ 1_0000000000000000000000b    ; D/B位，对于代码段，1表示32位
DESC_L equ 0_000000000000000000000b        ; L位，64位代码标记，0表示非64位
DESC_AVL equ 0_00000000000000000000b       ; AVL位，可供系统软件使用
DESC_LIMIT_CODE2 equ 1111_0000000000000000b ; 代码段段界限的第2部分
DESC_LIMIT_DATA2 equ DESC_LIMIT_CODE2      ; 数据段段界限的第2部分
DESC_LIMIT_VIDEO2 equ 0000_000000000000000b ; 显存段段界限的第2部分
DESC_P equ 1_000000000000000b              ; P位，段是否存在
DESC_DPL_0 equ 00_0000000000000b          ; 描述符特权级0
DESC_DPL_1 equ 01_0000000000000b          ; 描述符特权级1
DESC_DPL_2 equ 10_0000000000000b          ; 描述符特权级2
DESC_DPL_3 equ 11_0000000000000b          ; 描述符特权级3
DESC_S_CODE equ 1_000000000000b           ; S位，1表示非系统段（代码或数据段）
DESC_S_DATA equ DESC_S_CODE
DESC_S_sys equ 0_000000000000b            ; S位，0表示系统段
DESC_TYPE_CODE equ 1000_00000000b         ; 代码段类型：可执行、非依从、可读
DESC_TYPE_DATA equ 0010_00000000b         ; 数据段类型：不可执行、向上扩展、可写

; 定义代码段、数据段和显存段描述符的高4字节值
DESC_CODE_HIGH4 equ (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_CODE2 + DESC_P + DESC_DPL_0 + DESC_S_CODE + DESC_TYPE_CODE + 0x00
DESC_DATA_HIGH4 equ (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_DATA2 + DESC_P + DESC_DPL_0 + DESC_S_DATA + DESC_TYPE_DATA + 0x00
DESC_VIDEO_HIGH4 equ (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_VIDEO2 + DESC_P + DESC_DPL_0 + DESC_S_DATA + DESC_TYPE_DATA + 0x0b

;-------------- 选择子属性 ---------------
RPL0 equ 00b  ; 请求特权级0
RPL1 equ 01b  ; 请求特权级1
RPL2 equ 10b  ; 请求特权级2
RPL3 equ 11b  ; 请求特权级3
TI_GDT equ 000b ; 表指示符，指向GDT
TI_LDT equ 100b ; 表指示符，指向LDT
