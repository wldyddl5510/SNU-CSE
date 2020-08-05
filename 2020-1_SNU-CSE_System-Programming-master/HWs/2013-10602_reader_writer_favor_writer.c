//2013-10602 Jiyoung Park

#include <semaphore.h>
#include <stdlib.h>

sem_t reader_mutex, writer_mutex, w, r;
int read_cnt = 0;
int writer_cnt = 0;

void reader(void) {
	while(1) {
		P(&r); //reader enter -> This ensures writer first
		P(&reader_mutex); //lock
		read_cnt++;

		if(read_cnt == 1) { //first in
			P(&w);
		}
		V(&reader_mutex); //unlock
		V(&r); //done

		// reading //

		P(&reader_mutex); //lock
		read_cnt--; //read done

		if(read_cnt == 0) { // last out
			V(&w);
		}
		V(&reader_mutex);
	}
}

void writer(void) {
	while(1) {
		P(&writer_mutex); //note that writer do not have P(&w) -> writer first!
		writer_cnt++;

		if(writer_cnt == 1) { // first write
			P(&r); // block reader -> writer priority
		}
		P(&writer_mutex);
		
		P(&w); // unlike reading, writing should not be interrupted by other writer -> lock!

		// writing //

		V(&w); // unlck -> now next writer can write

		P(&writer_mutex);
		writer_cnt--;
		if(writer_cnt == 0) { //last write;
			V(&r); // Next Reader can read only if last writer freed one
		}
		V(writer_mutex);
	}
}
