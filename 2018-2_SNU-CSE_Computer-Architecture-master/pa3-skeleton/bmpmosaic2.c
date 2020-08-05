#include <stdio.h>

void bmp_mosaic(unsigned char *imgptr, long long width, long long height, long long size) {
    long long horiz = 3 * width;
    long long p = 0;
    if(horiz % 4 != 0)
        p = 4 - horiz % 4;
    long long oneline =  horiz + p; //3 * width + padding byte = one line.

    long long i = (height - 1) * oneline;
    do {
        if(i < 0)
            break;
        long long j = -1 * horiz;
        do {
            if(j >= 0)
                break;
            long long ij = i + j + horiz;
            long long cnt = 0;
            long long r = 0;
            long long g = 0;
            long long b = 0;
            long long loca;

            long long k = 0;
            do {
                if(k >= size)
                    break;
                if(k * oneline - i <= 0)
                    break;
                long long l = 0;
                do {
                    if(l >= size)
                        break;
                    if(j + 3*l >= 0)
                        break;
                    cnt++; //픽셀 개수 카운트
                    loca = ij - k*oneline + 3*l; //i,j 블록의 k, l 번째 원소는 전체에선 이 위치
                    r += imgptr[loca];
                    g += imgptr[loca+1]; //g는 r 옆
                    b += imgptr[loca+2]; //b는 r 옆옆
                    l++;
                } while(((l < size) && (j + 3*l < 0)));
                k++;
            } while(((k < size) && (i - k * oneline >= 0)));

            k = 0;
            do {
                if(k >= size)
                    break;
                if(k * oneline - i <= 0)
                    break;
                long long l = 0;
                do {
                    if(l >= size)
                        break;
                    if(j + 3*l >= 0)
                        break;
                    loca = ij - k*oneline + 3*l;
                    imgptr[loca] = (r / cnt);
                    imgptr[loca+1] = (g / cnt);
                    imgptr[loca+2] = (b / cnt);
                    l++;
                } while(((l < size) && (j + 3*l < 0)));
                k++;
            } while(((k < size) && (i - k * oneline >= 0)));
            j = j + 3*size;
        } while(j < 0);
        i = i - oneline * size;
    } while(i >= 0);
}
