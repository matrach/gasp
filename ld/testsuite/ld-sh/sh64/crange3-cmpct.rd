ELF Header:
  Magic:   7f 45 4c 46 01 02 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF32
  Data:                              2's complement, big endian
  Version:                           1 \(current\)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC \(Executable file\)
  Machine:                           Hitachi SH
  Version:                           0x1
  Entry point address:               0x10c4
  Start of program headers:          52 \(bytes into file\)
  Start of section headers:          500 \(bytes into file\)
  Flags:                             0xa
  Size of this header:               52 \(bytes\)
  Size of program headers:           32 \(bytes\)
  Number of program headers:         2
  Size of section headers:           40 \(bytes\)
  Number of section headers:         13
  Section header string table index: 10

Section Headers:
  \[Nr\] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  \[ 0\]                   NULL            00000000 000000 000000 00      0   0  0
  \[ 1\] \.init             PROGBITS        00001000 000080 000004 00 AXp  0   0  4
  \[ 2\] \.text             PROGBITS        00001004 000084 0000d8 00 AXp  0   0  4
  \[ 3\] \.data             PROGBITS        00001160 000160 000000 00  WA  0   0  1
  \[ 4\] \.ctors            PROGBITS        00001160 000160 000000 00   W  0   0  1
  \[ 5\] \.dtors            PROGBITS        00001160 000160 000000 00   W  0   0  1
  \[ 6\] \.sbss             PROGBITS        00001160 000160 000000 00   W  0   0  1
  \[ 7\] \.bss              NOBITS          00001160 000160 000000 00  WA  0   0  1
  \[ 8\] \.stack            PROGBITS        00080000 000160 000000 00   W  0   0  1
  \[ 9\] \.cranges          LOUSER\+1        00000000 000160 00003c 00   W  0   0  1
  \[10\] \.shstrtab         STRTAB          00000000 00019c 000056 00      0   0  1
  \[11\] \.symtab           SYMTAB          00000000 0003fc 0001b0 10     12  10  4
  \[12\] \.strtab           STRTAB          00000000 0005ac 000078 00      0   0  1
Key to Flags:
  W \(write\), A \(alloc\), X \(execute\), M \(merge\), S \(strings\)
  I \(info\), L \(link order\), G \(group\), x \(unknown\)
  O \(extra OS processing required\) o \(OS specific\), p \(processor specific\)

Symbol table '\.symtab' contains 27 entries:
   Num:    Value  Size Type    Bind   Vis      Ndx Name
     0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 00001000     0 SECTION LOCAL  DEFAULT    1 
     2: 00001004     0 SECTION LOCAL  DEFAULT    2 
     3: 00001160     0 SECTION LOCAL  DEFAULT    3 
     4: 00001160     0 SECTION LOCAL  DEFAULT    4 
     5: 00001160     0 SECTION LOCAL  DEFAULT    5 
     6: 00001160     0 SECTION LOCAL  DEFAULT    6 
     7: 00001160     0 SECTION LOCAL  DEFAULT    7 
     8: 00080000     0 SECTION LOCAL  DEFAULT    8 
     9: 00000000     0 SECTION LOCAL  DEFAULT    9 
    10: 00000000     0 SECTION LOCAL  DEFAULT   10 
    11: 00000000     0 SECTION LOCAL  DEFAULT   11 
    12: 00000000     0 SECTION LOCAL  DEFAULT   12 
    13: 00001004     0 NOTYPE  LOCAL  DEFAULT    2 sec4
    14: 000010a4     0 NOTYPE  LOCAL  DEFAULT    2 start2
    15: 000010bc     0 NOTYPE  LOCAL  DEFAULT    2 sec3
    16: 000010c4     0 NOTYPE  GLOBAL DEFAULT    2 diversion
    17: 00001160     0 NOTYPE  GLOBAL DEFAULT    5 ___dtors
    18: 00001160     0 NOTYPE  GLOBAL DEFAULT  ABS __bss_start
    19: 00001160     0 NOTYPE  GLOBAL DEFAULT    4 ___ctors_end
    20: 000010a4     0 NOTYPE  GLOBAL DEFAULT    2 diversion2
    21: 00001160     0 NOTYPE  GLOBAL DEFAULT    4 ___ctors
    22: 00001160     0 NOTYPE  GLOBAL DEFAULT  ABS _edata
    23: 00001160     0 NOTYPE  GLOBAL DEFAULT  ABS _end
    24: 00001000     0 NOTYPE  GLOBAL DEFAULT    1 start
    25: 00080000     0 NOTYPE  GLOBAL DEFAULT    8 _stack
    26: 00001160     0 NOTYPE  GLOBAL DEFAULT    5 ___dtors_end

Hex dump of section '\.text':
  0x00001004 6ff0fff0 6ff0fff0 6ff0fff0 6ff0fff0 .*
  0x00001014 6ff0fff0 6ff0fff0 cc00bd40 6ff0fff0 .*
  0x00001024 6ff0fff0 6ff0fff0 6ff0fff0 6ff0fff0 .*
  0x00001034 6ff0fff0 6ff0fff0 6ff0fff0 6ff0fff0 .*
  0x00001044 6ff0fff0 6ff0fff0 6ff0fff0 cc00bd50 .*
  0x00001054 cc0084c0 6ff0fff0 6ff0fff0 6ff0fff0 .*
  0x00001064 6ff0fff0 6ff0fff0 6ff0fff0 6ff0fff0 .*
  0x00001074 6ff0fff0 6ff0fff0 6ff0fff0 6ff0fff0 .*
  0x00001084 6ff0fff0 6ff0fff0 6ff0fff0 6ff0fff0 .*
  0x00001094 6ff0fff0 6ff0fff0 6ff0fff0 cc0084d0 .*
  0x000010a4 6ff0fff0 6ff0fff0 6ff0fff0 0000002a .*
  0x000010b4 0000002b 00090009 00090009 00090000 .*
  0x000010c4 e10f0009 00090009 00090009 00090009 .*
  0x000010d4 00090009 0009e10e                   .*

Hex dump of section '\.cranges':
  0x00000000 00001004 000000a0 00030000 10a40000 .*
  0x00000010 000c0003 000010b0 00000008 00010000 .*
  0x00000020 10b80000 00040002 000010bc 00000006 .*
  0x00000030 00020000 10c40000 00180002          .*
