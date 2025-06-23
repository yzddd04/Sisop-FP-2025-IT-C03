# Final Project Sistem Operasi IT

## Peraturan

Waktu pengerjaan dimulai hari Kamis (19 Juni 2025) setelah soal dibagikan hingga hari Rabu (25 Juni 2025) pukul 23.59 WIB.

Praktikan diharapkan membuat laporan penjelasan dan penyelesaian soal dalam bentuk Readme(github).

Format nama repository github "Sisop-FP-2025-IT-[Kelas][Kelompok]" (contoh:Sisop-FP-2025-IT-A01).

Setelah pengerjaan selesai, seluruh source code dan semua script bash, awk, dan file yang berisi cron job ditaruh di github masing - masing kelompok, dan link github dikumpulkan pada form yang disediakan. Pastikan github di setting ke publik.

Commit terakhir maksimal 10 menit setelah waktu pengerjaan berakhir. Jika melewati maka akan dinilai berdasarkan commit terakhir.

Jika tidak ada pengumuman perubahan soal oleh asisten, maka soal dianggap dapat diselesaikan.

Jika ditemukan soal yang tidak dapat diselesaikan, harap menuliskannya pada Readme beserta permasalahan yang ditemukan.

Praktikan tidak diperbolehkan menanyakan jawaban dari soal yang diberikan kepada asisten maupun praktikan dari kelompok lainnya.

Jika ditemukan indikasi kecurangan dalam bentuk apapun di pengerjaan soal final project, maka nilai dianggap 0.

Pengerjaan soal final project sesuai dengan modul yang telah diajarkan.

## Kelompok 3

| Nama                  | NRP        |
| --------------------- | ---------- |
| Tasya Aulia Darmawan  | 5027241009 |
| Ahmad Yazid Arifuddin | 5027241040 |
| Zahra Khaalishah      | 5027241070 |
| Binar Najmuddin Mahya | 5027241101 |

## Deskripsi Soal

> Insert testcase... (contoh dibawah) // hapus line ini

Thread Counter (11)

Buatlah program yang mendemonstrasikan penggunaan thread dan mutex untuk menghindari race condition. Program harus membuat tiga thread, di mana masing-masing thread bertugas menambah nilai sebuah variabel global counter sebanyak N kali. Gunakan mutex untuk memastikan hanya satu thread yang dapat mengubah nilai counter pada satu waktu. Setelah seluruh thread selesai, program harus mencetak nilai akhir counter dan memastikan nilainya tepat 3×N. Jelaskan juga apa yang terjadi jika mutex tidak digunakan (counter bisa salah).

### Catatan

> Insert catatan dari pengerjaan kalian... (contoh dibawah) // hapus line ini

Struktur repository:

```
.
├─ nonmutex.c
├─ thread.c
├─ README.md

```

## Pengerjaan

> Insert poin soal...

**Teori**
Thread

Thread memungkinkan eksekusi kode secara paralel. Dengan membuat tiga thread, masing-masing dapat mengubah nilai counter secara bersamaan.

Mutex

Mutex (mutual exclusion) digunakan untuk memastikan bahwa hanya satu thread yang dapat mengakses atau memodifikasi data bersama (counter) pada suatu waktu, guna mencegah race condition.

Race Condition

Saat dua atau lebih threads mengubah nilai variabel bersama secara bersamaan tanpa sinkronisasi, nilai akhir bisa tidak sesuai ekspektasi.


**Solusi**

A. Tanpa Mutex

Kode
```c
// thread_without_mutex.c
#include <stdio.h>
#include <pthread.h>

#define N 1000000  // Jumlah penambahan per thread

int counter = 0;

void* increment(void* arg) {
    for (int i = 0; i < N; i++) {
        counter++;  // Modifikasi counter tanpa proteksi
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_create(&t3, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Final counter value: %d (Expected: %d)\n", counter, 3 * N);
    return 0;
}
```

Hasil
Nilai counter tidak konsisten, bisa jauh dari 3 * N.

Contoh:
```
Final counter value: 2378956 (Expected: 3000000)
```

B. Dengan Mutex

Kode
```c
// thread_with_mutex.c
#include <stdio.h>
#include <pthread.h>

#define N 1000000  // Jumlah penambahan per thread

int counter = 0;
pthread_mutex_t lock;

void* increment(void* arg) {
    for (int i = 0; i < N; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_create(&t3, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Final counter value: %d (Expected: %d)\n", counter, 3 * N);

    pthread_mutex_destroy(&lock);

    return 0;
}
```

Hasil
```
Final counter value: 3000000 (Expected: 3000000)
```

Kesimpulan
Tanpa mutex: Nilai akhir counter tidak dapat dijamin sesuai ekspektasi (race condition).

Dengan mutex: Nilai akhir counter sesuai dengan nilai yang diharapkan (3 * N), memastikan konsistensi data bersama.

**Video Menjalankan Program**
...

## Daftar Pustaka

The Open Group Base Specifications Issue 7 – pthreads

POSIX Threads Programming – https://pubs.opengroup.org/

Race Conditions and Mutexes – https://www.cs.ucr.edu/~fares/
