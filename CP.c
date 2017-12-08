2017.12.07 Thursday
22:41 Puguh? Vick
22:48 Muhammad Vicky Apa? 
23:28 Puguh? Bsk free?
23:28 Muhammad Vicky Kelas full
23:28 Muhammad Vicky Knp
23:33 Puguh? ;"
2017.12.08 Friday
19:17 Muhammad Vicky Guh
19:17 Muhammad Vicky Lihat cpmu
19:27 Puguh? wait
19:31 Muhammad Vicky Okee
19:42 Puguh? Emailmu apa
19:43 Puguh? #include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

char buf[512];

int
main(int argc, char *argv[])
{
    int fd0, fd1, n;
  
  if(argc <= 2)
  {
    printf(1, "Need 2 arguments!\n");
    exit();
  }
  
    if((fd0 = open(argv[1], O_RDONLY)) < 0)
    {
        printf(1, "cp: Cannot Open this %s\n", argv[1]);
        exit();
    }
    if((fd1 = open(argv[2], O_CREATE|O_RDWR)) < 0)
    {
        printf(1, "cp: Cannot Open this %s\n", argv[2]);
        exit();
    }
    while ( ( n = read ( fd0, buf, sizeof(buf))) > 0 )
    {
        write ( fd1, buf, n);
    }
    close(fd0);
    close(fd1);
exit();
}
