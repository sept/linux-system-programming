#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
struct STU {
	char name[20];
	int id;
	char sex;
};
typedef struct STU student;

int main(int argc, char *argv[])
{
	student *p;
	int fd;
	char *mp;
	char buf[100];
	if (argc != 2) {
		printf("./a.out filemap\n");
		exit(-1);
	}
	fd = open(argv[1], O_RDWR);	
	if (fd < 0) {
		perror("open filemap");
		exit(-1);
	}
	mp = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (mp == MAP_FAILED) {
		perror("mmap");
		exit(-1);
	}
	while(1) {
	p = (student *)mp;
	printf("please input student info name,id,sex\n");
	fgets(buf, sizeof(buf), stdin);
	buf[strlen(buf)-1] = '\0';
	strcpy(p->name, buf);
	/* igno id and sex */
		sleep(5);
	}

	return 0;



}
