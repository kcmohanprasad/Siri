#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int getFileSize(const char *filename)
{
    struct stat st;
    if (stat(filename, &st) == 0)
        return st.st_size;
    return -1;
}


int main(int argc, char **argv)
{
    char *infile = "in.mp3", *outfile = "out.txt";
    int infd, bytes_read = 0, buffsize = 255;
    char buffer[255];

                infd = open(infile, O_RDONLY);
                if (infd == -1) {
                    printf ("Error opening infile");
                    return -1;
                }

                int outfd = open(outfile, O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
                if (outfd == -1){
                    printf ("Error opening outfile");
                    return -1;
                }

                    if(lseek(infd, -128, SEEK_END) < 0)
                        return -1;

                for(;;)
                {
                    bytes_read = read(infd, buffer, buffsize);
                    if (bytes_read > 0)
                    {
                        write(outfd, buffer, bytes_read);

                    }
                    else
                    {
                        if (bytes_read == 0)
                        {
                            if (close(infd) < 0)
                                return -1;
                            break;
                        }
                        else if (bytes_read == -1)
                        {
                            break;
                            return -1;
                        }
                    }
                }

    return 0;
}
