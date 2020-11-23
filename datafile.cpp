#include "datafile.h"


int ReadFileToData( uint8_t *data ,int off_size) {
    int fd_out = open("./outfile",O_RDWR | O_CREAT , 0777);
    if (fd_out == -1) {
        fprintf(stderr, "Open failed : %s\n",
        strerror(errno));
        return -1;
    }

    printf("当前读 off_size : %d\n", off_size);
    memset(data, 0, DATASIZE);
    lseek(fd_out, off_size, SEEK_SET);
    int ret = read(fd_out, data, DATASIZE);
    if(ret == -1) {
        perror("read err");
        return -1;
    }

    //printf("ret----------%d\n",ret );
    close(fd_out);
    return ret;
}

int RteFileoff( uint8_t *data_head ,int off_size) {

    int fd_out = open("./outfile",O_RDWR | O_CREAT , 0777);
    if (fd_out == -1) {
        fprintf(stderr, "Open failed : %s\n",
        strerror(errno));
        return -1;
    }

    int sign = 0;
    uint8_t tmp[DATASIZE];
    uint8_t tmp_head[4];
    memset(tmp, 0, DATASIZE);
    lseek(fd_out, off_size, SEEK_SET);

    int s = read(fd_out, tmp, DATASIZE);
    printf("read s = %d\n",s);
    // for (int i = 0; i < DATASIZE; ++i)
    // {
    //      printf(" tmp[%d] = 0x%02x",i,tmp[i]);
    // }
   
    sleep(1);
    for (int i = 0; i < DATASIZE; i++) {
        if(tmp[i]  == data_head[0]){
            memcpy(tmp_head, &tmp[i], 4);
            int flag = strncmp( (char *)tmp_head, (char *)data_head ,4);
            if(flag == 0) {
                sign = i;
            }
        }
        
    }
    lseek(fd_out, 0, SEEK_SET);
    printf("  ret sign  %d\n",sign );
    close(fd_out);
    return sign;
}

unsigned int FileLen() {
    int fd_out = open("./outfile",O_RDWR | O_CREAT , 0777);
    if (fd_out == -1) {
        fprintf(stderr, "Open failed : %s\n",
        strerror(errno));
        return -1;
    }
    unsigned int ret = lseek(fd_out, 0, SEEK_END);
    close(fd_out);
    return ret;
}
