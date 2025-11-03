; FAT12 磁盘的头定义 [1](@ref)
BS_OEMName     DB 'ForrestY'   ; OEM 字符串，必须 8 个字节
BPB_BytsPerSec DW 512          ; 每扇区字节数
BPB_SecPerClus DB 1            ; 每簇扇区数
BPB_RsvdSecCnt DW 1            ; 保留扇区数（Boot记录占用的扇区数）
BPB_NumFATs    DB 2            ; FAT表的数量
BPB_RootEntCnt DW 224          ; 根目录可容纳的目录项数最大值
BPB_TotSec16   DW 2880         ; 总扇区数（针对小磁盘）
BPB_Media      DB 0xF0         ; 媒体描述符
BPB_FATSz16    DW 9            ; 每个FAT表占用的扇区数
BPB_SecPerTrk  DW 18           ; 每磁道扇区数
BPB_NumHeads   DW 2            ; 磁头数（面数）
BPB_HiddSec    DD 0            ; 隐藏扇区数
BPB_TotSec32   DD 0            ; 如果BPB_TotSec16为0，则由此记录总扇区数
BS_DrvNum      DB 0            ; 驱动器号（INT 13H使用）
BS_Reserved1   DB 0            ; 保留未使用
BS_BootSig     DB 29h          ; 扩展引导标记
BS_VolID       DD 0            ; 卷序列号
BS_VolLab      DB 'OrangeS0.02'; 卷标，必须 11 个字节
BS_FileSysType DB 'FAT12   '   ; 文件系统类型，必须 8 个字节

; 基于上述BPB头计算的常用常量 [1,2](@ref)
RootDirSectors              equ 14      ; 根目录区占用的扇区数
SectorNoOfRootDirectory     equ 19      ; 根目录区的起始扇区号
SectorNoOfFAT1              equ 1       ; FAT1表的起始扇区号
DeltaSectorNo               equ 17      ; 用于计算文件数据区簇号的偏移量
