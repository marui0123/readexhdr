#include <stdio.h>
//#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <3ds/exheader.h>

int
main (int argc, char **argv)
{
	struct stat stat_buf;
	char *head;
	ExHeader *exhdr;
	
	if (argc < 2)
	{
		fprintf (stderr, "Too few argments\n");
		return -1;
	}

	int fd = open (argv[1], O_RDONLY);
	
	if (fd < 0)
	{
		fprintf (stderr, "Failed to open the file\n");
		return -1;
	}

	fstat (fd, &stat_buf);
	head = mmap (NULL, stat_buf.st_size, PROT_READ, MAP_SHARED, fd, 0);

	exhdr = (ExHeader *)head;
	ExHeader_Info *info = &exhdr->info;
	ExHeader_SystemControlInfo *sci = &info->sci;
	ExHeader_CodeSetInfo *codeset_info = &sci->codeset_info;

	ExHeader_CodeSectionInfo *text = &codeset_info->text;
	ExHeader_CodeSectionInfo *rodata = &codeset_info->rodata;
	ExHeader_CodeSectionInfo *data = &codeset_info->data;

	u32 total = text->size + rodata->size + data->size;

	puts	("    Name        Address     Size");
	printf	("    text        %08x    %08x\n", text->address, text->size);
	printf	("    rodata      %08x    %08x\n", rodata->address, rodata->size);
	printf	("    data        %08x    %08x\n", data->address, data->size);
	printf	("    stack                   %08x\n", codeset_info->stack_size);
	printf	("    bss                     %08x\n", codeset_info->bss_size);
	printf	("    reserved    %08x\n", codeset_info->reserved);

	munmap (head, stat_buf.st_size);
	close (fd);

	return 0;
}
