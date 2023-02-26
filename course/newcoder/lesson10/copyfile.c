/*

    #include <unistd.h>

    ssize_t read(int fd, void *buf, size_t count);
        参数
            - fd: 文件描述符，open得到的，通过这个文件描述符来操作某个文件
            - buf: 需要读取数据存放的地方，数组的地址(传出参数)
            - count: 指定的数组的大小
        返回值：
            - 成功：
                >0: 返回实际读到的字节数
                =0: 文件已经读完了
            - 失败: -1 ，并且设置errno

    #include <unistd.h>

    ssize_t write(int fd, const void *buf, size_t count);
        参数：
            - fd：文件描述符，open得到的，通过这个文件描述符来操作某个文件
            - buf: 要往磁盘写入的数据
            - count: 要写的数据的实际的大小
        返回值:
            - 成功 实际写入的字节数
            - 失败 -1 并且设置errno

    #include <unistd.h>

    int close(int fd);


*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    // 1 通过open打开english.txt文件
    int srcfd = open("english.txt",O_RDONLY);
    
    if(srcfd == -1)
    {
        perror("src open");
        return -1;
    }



    // 2 创建一个新的文件(目标文件)

    int destfd = open("cpy.txt",O_RDWR|O_CREAT,0664);
    if(destfd == -1)
    {
        perror("dest open");
        return -1;
    }

    // 3 频繁的读写操作
    char buf[1024] = {0};
    int len = 0;
    
    while((len = read(srcfd,buf,sizeof(buf))) > 0){
        int rv = write(destfd,buf,len);
        if(rv == -1)
        {
            perror("write error");
            break;
        }

    }
    // 4 关闭文件
    close(srcfd);
    close(destfd);

    return 0;
}