#include <stdio.h>

void bmp_mosaic(unsigned char *imgptr, long long width, long long height, long long size) {
    long long horiz = 3 * width;
    long long oneline =  ((horiz) % 4 == 0) ? horiz : (horiz + 4 - horiz % 4); //3 * width + padding byte = one line.

    for(long long i = (height - 1)*oneline ;  i >= 0 ; i -= oneline * size) { // 높이 한 블럭씩 위로 올라가기.
        for(long long j = 0 ; j < horiz ; j += 3*size) { // 너비 한 블럭씩 오른쪽으로 이동
        //i, j는 블록 지정
            long long ij = i + j;
            long long cnt = 0; //블록 안에 픽셀 개수
            long long r = 0;
            long long g = 0;
            long long b = 0;
            long long loca; // 계산 빠르게 하기 위해 미리 계산
            for(long long k = 0 ; ((k < size) && (i - k * oneline >= 0)); k++) { //현 블록 가장 아래부터, size 도달하거나 사진이 끝나거나.
                for(long long l = 0 ; ((l < size) && (j + 3*l < horiz)) ; l++) { //현 블록 가장 왼쪽부터, size 도달하거나 사진이 끝나거나.
                //k, l은 블록 내 원소 지정
                    cnt++; //픽셀 개수 카운트
                    loca = ij - k*oneline + 3*l; //i,j 블록의 k, l 번째 원소는 전체에선 이 위치
                    r += imgptr[loca];
                    g += imgptr[loca+1]; //g는 r 옆
                    b += imgptr[loca+2]; //b는 r 옆옆
                }
            }
            for(long long k = 0 ; ((k < size) && (i - k * oneline >= 0)); k++) {
                for(long long l = 0 ; ((l < size) && (j + 3*l < horiz)) ; l++) {
                    //평균 계산해서 대체하기.
                    loca = ij - k*oneline + 3*l;
                    imgptr[loca] = (r / cnt);
                    imgptr[loca+1] = (g / cnt);
                    imgptr[loca+2] = (b / cnt);
                }
            }
        }
    }
}
