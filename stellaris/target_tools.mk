# Target Tool Specification Makefile (target_tools.mk)

# Compiler command and options
CC = "$(CompilerRoot)/bin/armcl"
CFLAGS = -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi \
         -me -O2 --define=PART_LM4F120H5QR --gcc --define=ccs="ccs" \
         --include_path="$(CompilerRoot)/include" \
         --include_path="$(StellarisWareRoot)" \
         --define=TARGET_IS_BLIZZARD_RA1

CFLAGS += $(OPTS)
CDEBUG = -g
CCOUTPUTFLAG = --output_file=

CXX      =
CXXFLAGS =
CXXDEBUG =

# Linker command and options
LD      = $(CC)
LDFLAGS = -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi \
          -me -O2 --define=PART_LM4F120H5QR --gcc --define=ccs="ccs" \
          -z --stack_size=256 -m"$(MODEL).map" --heap_size=0 \
          -i"$(CompilerRoot)/lib" -i"$(CompilerRoot)/include" --reread_libs \
          --rom_model "$(CCSRoot)/ccs_base/arm/include/lm4f210h5qr.cmd" \
          --define=TARGET_IS_BLIZZARD_RA1

LDDEBUG =
LDOUTPUTFLAG = --output_file=

# Archiver command and options
AR      = "$(CompilerRoot)/bin/armar"
ARFLAGS = -r

# Binary file format converter command and options
OBJCOPY      = 
OBJCOPYFLAGS = 

# Specify the output extension from compiler
OBJ_EXT = .o

# Specify extension from linker
PROGRAM_FILE_EXT = .out 

# Specify extension for final product at end of build
EXE_FILE_EXT     = $(PROGRAM_FILE_EXT)