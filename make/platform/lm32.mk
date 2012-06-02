Description := LatticeMico32

Configs := lm32
Arch := lm32

CC := clang

CFLAGS := -Wall -Werror -O3 -D_YUGA_LITTLE_ENDIAN=0 -D_YUGA_BIG_ENDIAN=1 -ccc-host-triple lm32-elf

FUNCTIONS := divsi3 modsi3 comparedf2 negsf2 negdf2 addsf3 subsf3 mulsf3 divsf3 lshrdi3 muldi3 divdi3 ashldi3 ashrdi3 udivmoddi4 \
  floatsisf floatunsisf fixsfsi fixunssfsi adddf3 subdf3 muldf3 divdf3 floatsidf floatunsidf floatdidf fixdfsi fixunsdfsi
