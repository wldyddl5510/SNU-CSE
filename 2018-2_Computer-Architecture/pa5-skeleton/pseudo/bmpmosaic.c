#include <stdio.h>

void bmp_mosaic(unsigned char *imgptr, long long width, long long height, long long size) {
    long long horiz = 3 * width;
    long long oneline =  ((horiz) % 4 == 0) ? horiz : (horiz + 4 - horiz % 4); //3 * width + padding byte = one line.
    long long size3 = 3*size;
    long long size_oneline = size*oneline;

    long long a = horiz + imgptr;
    for(long long i = (height - 1)*oneline ;  i >= 0 ; i -= size_oneline) { // 높이 한 블럭씩 위로 올라가기.
        long long a1 = a + i;
        for(long long j = -1*horiz ; j < 0 ; j += size3) { // 너비 한 블럭씩 오른쪽으로 이동
        //i, j는 블록 지정
            long long ij = a1 + j;
            long long cnt = 0; //블록 안에 픽셀 개수
            long long r = 0;
            long long g = 0;
            long long b = 0;
            for(long long k = 0 ; ((k < size_oneline) && (i - k >= 0)); k += oneline) { //현 블록 가장 아래부터, size 도달하거나 사진이 끝나거나.
                long long loc = ij - k;
                for(long long l = 0 ; ((l < size3) && (j + l < 0)) ; l += 3) { //현 블록 가장 왼쪽부터, size 도달하거나 사진이 끝나거나.
                //k, l은 블록 내 원소 지정
                    cnt++; //픽셀 개수 카운트
                    long long loca = loc + l; //i,j 블록의 k, l 번째 원소는 전체에선 이 위치
                    r += imgptr[loca];
                    g += imgptr[loca+1]; //g는 r 옆
                    b += imgptr[loca+2]; //b는 r 옆옆
                }
            }
            long long rmean = r / cnt;
            long long gmean = g / cnt;
            long long bmean = b / cnt;
            for(long long k = 0 ; ((k < size_oneline) && (i - k >= 0)); k += oneline) {
                long long loc = ij - k;
                for(long long l = 0 ; ((l < size3) && (j + l < 0)) ; l += 3) {
                    //대체하기.
                    long long loca = loc + l;
                    imgptr[loca] = rmean;
                    imgptr[loca+1] = gmean;
                    imgptr[loca+2] = bmean;
                }
            }
        }
    }
}
