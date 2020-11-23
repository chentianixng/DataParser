#include <stdio.h>
#include "parser.h"
#include "datafile.h"


int main()
{
    int i;
    // 数据头
    uint8_t data_header[] = {0x87,0x86,0x7f,0xaa};
    uint8_t data_footer[] = "";
    uint8_t dt_tmp[DATASIZE-4];


    /**
     * 初始化一个解析器
     * 第一个参数是数据头
     * 第二个参数是数据头长度
     * 第三个参数是数据尾指针
     * 第四个参数是数据尾大小
     * 第五个参数是一整帧数据的大小
     */
    DataParser *data_parser = parser_init(data_header, sizeof(data_header),
                               NULL, 0,DATASIZE);

    FrameTFLInfo *dttest = (FrameTFLInfo *)malloc(sizeof(FrameTFLInfo));

    printf("size = %d\n",sizeof(FrameTFLInfo));
    // 以读size
    int read_size = 0;
    // 
    int off_size =0;
    int ret = 0;
    // 记录一帧数据
    uint8_t data[DATASIZE];
    
    //     
    while(1){
        // 被分割的一帧 文件头 off_size + 文件尾 (DATASIZE - off_size)
        if(read_size == 0 && off_size == 0 && ret == 0) {
            off_size = RteFileoff(data_header, read_size);
            unsigned int ll= FileLen();

            uint8_t tmp_f1[off_size];
            uint8_t tmp_l1[DATASIZE - off_size];
                int fd_out = open("./outfile",O_RDWR | O_CREAT , 0777);
                if (fd_out == -1) {
                    fprintf(stderr, "Open failed : %s\n",
                    strerror(errno));
                    return -1;
                }
                int read_size = read(fd_out, tmp_f1, sizeof(tmp_f1));

                lseek(fd_out, ll - (DATASIZE - off_size), SEEK_SET);
                read(fd_out, tmp_l1, sizeof(tmp_l1));
                memcpy(data, tmp_l1, sizeof(tmp_l1));
                memcpy(data + sizeof(tmp_l1), tmp_f1,sizeof(tmp_f1));
                close(fd_out);

            printf("ll %ld\n", ll );
            printf("first_flag %d\n", off_size);
        } else {

            off_size = RteFileoff(data_header, read_size);
        
            read_size = read_size + off_size;

            ret = ReadFileToData( data, read_size);
            read_size += ret;

            printf(" off_size %d\n", off_size );
            usleep(500000);
            if (ret < DATASIZE){
                printf("----ret %d\n",ret );
                break;
            }

        }

        // 将要解析的数据逐个取出，添加到解析器中，解析器check data.
        
        for(i = 0; i < sizeof(data); i++)
        {
            // 解析数据，返回 RESULT_TRUE 代表成功解析出一组数据
            if(parser_put_data(data_parser, data[i]) == RESULT_TRUE)
            {
                printf("成功解析出一帧数据...\n");
                  //printf("第一个数据是：0x%x\n", parser_get_data(data_parser, 0));
                
                memcpy(dttest,data+16,sizeof(FrameTFLInfo));
                
                printf("******************************\n\n");
                printf("dttest.S_nFrameID  = %d\n",dttest->S_nFrameID);
                printf("S_nImageTimeStamp = %d\n",dttest -> S_nImageTimeStamp);
                // printf(" [0]%d  \n\n",dttest->Dt_ARRAY_7500[0] );
                // printf("dt_test.RecordParkingSlot.PaddingGap8_1 %d   dt_test.RecordParkingSlot.PaddingGap16_2 %d \n",
                // dttest->RecordParkingSlot.PaddingGap8_1 , dttest->RecordParkingSlot.PaddingGap16_2);
                // printf("******************************\n\n");
            }
        }
    }
    // 当不再需要解析器时，应该把解析器释放掉，回收内存，避免造成内存泄漏
    parser_release(data_parser);
    free(dttest);
    dttest =NULL;
    return 0;
}


