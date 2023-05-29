TARGET		:= 	$(notdir $(CURDIR))
INCLUDES	:= 	-I$(DEVKITPRO)/libctru/include

CFLAGS		:=	$(INCLUDES) -Wall -Wextra

.PHONY:	clean all

all:	$(TARGET)

$(TARGET):	readexhdr.c
	$(CC) $< $(CFLAGS) -o $(TARGET)

clean:
	@echo clean ...
	@rm -f $(TARGET)
