HEADERS := $(wildcard *.h)
SRC_DIRS := ./
SOURCES := $(shell find $(SRC_DIRS) -name '*.c')

.PHONEY = indent

indent : 
		@echo "============= indenting following files ================"
		indent $(SOURCES)
		@echo "========================================================"

