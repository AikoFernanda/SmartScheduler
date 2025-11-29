# Smart Campus Room Scheduler (CPP-OOP)

> **"Implementasi OOP C++: Analisis Kinerja Algoritma Conflict Checking dan Solusi Heuristik untuk Masalah Penjadwalan Aset NP-Complete"**

Project ini adalah simulasi sistem reservasi ruang rapat kampus yang dibangun menggunakan **C++** dengan paradigma **Object-Oriented Programming (OOP)**. Fokus utama dari project ini bukan hanya pada fungsionalitas booking, tetapi pada analisis kompleksitas algoritma dan penanganan masalah komputasi sulit (*NP-Complete*).

## 🚀 Fitur & Poin Analisis
### 1. Arsitektur OOP yang Kuat
Mengimplementasikan 4 pilar OOP untuk skalabilitas sistem:
- **Abstraction:** Menggunakan Interface `Bookable` sebagai kontrak untuk semua jenis aset.
- **Inheritance:** `RuangRapat` mengimplementasikan `Bookable`.
- **Polymorphism:** `BookingManager` dapat mengelola berbagai jenis aset tanpa mengubah kode inti.
- **Encapsulation:** Data reservasi terlindungi di dalam objek masing-masing.

### 2. Analisis Algoritma Conflict Checking=
Studi kasus untuk masalah **Kelas P** (Polynomial Time). Kami membandingkan dua strategi pencarian jadwal:
- **Naive Approach:** Menggunakan *Linear Search* pada `std::vector` dengan Time Complexity **$O(n)$**.
- **Optimal Approach:** Menggunakan *Binary Search Tree* mechanism (via `std::map` / `std::lower_bound`) dengan Time Complexity **$O(\log n)$**.

### 3. Solusi Masalah Penjadwalan Otomatis (P vs NP)
Studi kasus untuk masalah **Kelas NP-Complete** (*Bin Packing / Scheduling Problem*).
- Karena mencari solusi optimal untuk penjadwalan banyak acara ke sedikit ruangan membutuhkan waktu eksponensial, sistem ini mengimplementasikan **Algoritma Heuristik Greedy (First-Fit)**.
- Pendekatan ini memberikan solusi yang "cukup baik" dalam waktu eksekusi yang cepat.

## 📂 Struktur Project

```text
cpp-oop-smart-scheduler/
│
├── include/            # File Header (.h) - Kontrak & Deklarasi Class
│   ├── Bookable.h
│   ├── RuangRapat.h
│   ├── BookingManager.h
│   └── Reservasi.h
│
├── src/                # File Source (.cpp) - Implementasi Logika & Algoritma
│   ├── RuangRapat.cpp
│   └── BookingManager.cpp
│
├── main.cpp            # Entry Point & Skenario Testing
└── README.md           # Dokumentasi Project