#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>

int main(void)
{
   char *dest;
   int fd, i = 4;
   struct stat filedp;

   fd = open("m_file", O_RDWR);
   if (fd < 0) 
   {
       perror("open failed");
       exit(-1);
   }
   fstat(fd, &filedp);
   dest = mmap(NULL, filedp.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   if (dest == MAP_FAILED) 
   {
       perror("mmap dest");
       exit(-1);
   }
   while (i--)
   {
       *dest = i+'a';
       sleep(3);
       dest++;
   }
   *dest = '\0';

   munmap(dest, filedp.st_size);
   close(fd);

   return 0;
}
