#include <stdio.h>
#include <pthread.h>

#define N 1000000  // Jumlah penambahan per thread

int counter = 0;  // Variabel global counter (tanpa perlindungan)

void* increment(void* arg) {
    for (int i = 0; i < N; i++) {
        counter++;  // Modifikasi counter tanpa mutex
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    // Membuat 3 thread (tanpa inisialisasi mutex)
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_create(&t3, NULL, increment, NULL);

    // Menunggu thread selesai
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Hasil akhir akan salah karena race condition
    printf("Final counter value: %d (Expected: %d)\n", counter, 3 * N);
    
    return 0;
}