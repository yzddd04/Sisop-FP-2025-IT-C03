#include <stdio.h>
#include <pthread.h>

#define N 1000000  // Jumlah penambahan per thread

int counter = 0;             // Variabel global counter
pthread_mutex_t lock;        // Mutex untuk melindungi counter

void* increment(void* arg) {
    for (int i = 0; i < N; i++) {
        pthread_mutex_lock(&lock);   // Kunci mutex
        counter++;                   // Modifikasi counter
        pthread_mutex_unlock(&lock); // Buka kunci mutex
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    // Inisialisasi mutex
    pthread_mutex_init(&lock, NULL);

    // Membuat 3 thread
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_create(&t3, NULL, increment, NULL);

    // Menunggu semua thread selesai
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Hasil akhir counter
    printf("Final counter value: %d (Expected: %d)\n", counter, 3 * N);

    // Hapus mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
