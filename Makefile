TARGET		:= 	$(notdir $(CURDIR))
INCLUDES	:= 	-I$(CTRULIB)/include

CFLAGS		:=	$(INCLUDES)

.PHONY:	clean all

all:	$(TARGET)

$(TARGET):	readexhdr.c
	$(CC) $(CFLAGS) -o $(TARGET)

clean:
	@echo clean ...
	@rm -f $(TARGET)
