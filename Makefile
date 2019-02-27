PROJECT_HOME = $(shell pwd)
TESTS_HOME = $(PROJECT_HOME)/tests
SRC_HOME = $(PROJECT_HOME)/src
BUILD_HOME = $(PROJECT_HOME)/build
BUILD_TESTS = $(BUILD_HOME)/tests
BUILD_TEST = $(BUILD_TESTS)/$(TEST)
BUILD_SRC = $(BUILD_HOME)/src

SRC_FILES = $(wildcard $(SRC_HOME)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_HOME)/%.cpp,$(BUILD_SRC)/%.o,$(SRC_FILES))

RISCV_CC = riscv32-unknown-elf-gcc-8.2.0
OBJCOPY = riscv32-unknown-elf-objcopy  
OBJDUMP = riscv32-unknown-elf-objdump
READELF = riscv32-unknown-elf-readelf
RISCV_CFLAGS = -mabi=ilp32 -march=rv32im

CC = g++
CFLAGS = -Wall -Wextra -O2
LDFLAGS =
LIBS = -lelf



run: build_src
	@$(BUILD_SRC)/simulator $(BUILD_TEST)/$(TEST).elf



build_test: $(BUILD_TEST)/$(TEST).lst $(BUILD_TEST)/$(TEST).bin $(BUILD_TEST)/$(TEST).segments

$(BUILD_TEST)/$(TEST).lst: $(BUILD_TEST)/$(TEST).elf
	@$(OBJDUMP) -D $< > $@

$(BUILD_TEST)/$(TEST).bin: $(BUILD_TEST)/$(TEST).elf
	@$(OBJCOPY) -O binary $< $@

$(BUILD_TEST)/$(TEST).segments: $(BUILD_TEST)/$(TEST).elf
	@$(READELF) --segments $< > $@

$(BUILD_TEST)/$(TEST).elf: create_dirs
	@$(RISCV_CC) $(RISCV_CFLAGS) $(TESTS_HOME)/$(TEST).c -o $@

build_src: $(OBJ_FILES)
	@$(CC) $(LDFLAGS) -o $(BUILD_SRC)/simulator $^ $(LIBS)

$(BUILD_SRC)/%.o: $(SRC_HOME)/%.cpp create_dirs
	@$(CC) $(CFLAGS) -c -o $@ $<



create_dirs:
	@mkdir -p $(BUILD_HOME)
	@mkdir -p $(BUILD_TESTS)
	@mkdir -p $(BUILD_TEST)
	@mkdir -p $(BUILD_SRC)



clean_all:
	@rm -rf $(BUILD_HOME)



clean:
	@rm -rf $(BUILD_SRC)
