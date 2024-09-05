SRC		:=$(wildcard ./*.c)
OBJECTS	:=$(patsubst %.c,$(BUILD)/%.o,$(notdir $(SRC)))

all: ${OBJECTS}
	@-rm -f *.d

-include *.d
${BUILD}/%.o: ./%.c $(modules)
	@echo "CC	"$@
	@$(CC) $(CFLAGS) -o $@ -c $< -MD -MF $*.d -MP