#include <iostream>
#include <vector>
#include <string>
#include <chrono> // ukur waktu (stopwatch)
#include <random> // generate data dummy
#include "include/BookingManager.h"
#include "include/RuangRapat.h"

using namespace std;
// helper function (generate data random)
vector<Reservasi> generateDummyData(int jumlah, int rangeStart, int rangeEnd) {
    vector<Reservasi> data;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> startDist(rangeStart, rangeEnd - 200);

    for (int i = 0; i < jumlah; i++) {
        int start = startDist(gen);
        int end = start + 100; // durasi fix 1jam (100) biar simple
        data.push_back(Reservasi("Kegiatan_" + std::to_string(i), start, end ));
    }
    return data;
}

// TEST 1: BENCHMARKING (Naive vs Optimal)
// analisis hasil
void runBenchmark() {
    std::cout << "\n============================================\n";
    std::cout << "   TEST 1: BENCHMARK CONFLICT CHECKING\n";
    std::cout << "   (Membuktikan Poin Analisis O(n) vs O(log n))\n";
    std::cout << "============================================\n";

    // 1. Setup: Isi Ruangan dengan 10.000 Jadwal Sampah
    RuangRapat ruangTest("Ruang_Benchmark");
    int DATA_SIZE = 10000; 
    std::cout << "[SETUP] Mengisi " << DATA_SIZE << " data reservasi ke dalam ruangan...\n";
    
    auto dummyData = generateDummyData(DATA_SIZE, 800, 20000); // Jam 08.00 - 200.00
    for (const auto& res : dummyData) {
        ruangTest.addBook(res);
    }

    // 1.000 request baru yang akan dicek (search operation)
    int SEARCH_COUNT = 1000;
    auto searchRequests = generateDummyData(SEARCH_COUNT, 800, 20000);
    std::cout << "[SETUP] Siap melakukan " << SEARCH_COUNT << " kali pengecekan jadwal.\n\n";

    // MODE 1 : ALGORITMA NAIVE (O(n))
    ruangTest.setAlgorithmMode(false); // set false optimal mode
    auto start1 = std::chrono::high_resolution_clock::now();
    
    int conflictCount1 = 0;
    for (const auto& req : searchRequests) {
        if (!ruangTest.isAvailable(req.getStart(), req.getEnd())) {
            conflictCount1++;
        }
    }
    
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration1 = end1 - start1;

    // MODE 2 : ALGORITMA OPTIMAL (O(log n))
    ruangTest.setAlgorithmMode(true); // Hidupkan optimal mode
    auto start2 = std::chrono::high_resolution_clock::now();
    
    int conflictCount2 = 0;
    for (const auto& req : searchRequests) {
        if (!ruangTest.isAvailable(req.getStart(), req.getEnd())) {
            conflictCount2++;
        }
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration2 = end2 - start2;

    // LAPORAN HASIL
    std::cout << "HASIL PENGUKURAN WAKTU:\n";
    std::cout << "1. Naive Algorithm (Linear Search):   " << duration1.count() << " ms\n";
    std::cout << "2. Optimal Algorithm (Binary Search): " << duration2.count() << " ms\n";
    
    double speedup = duration1.count() / duration2.count();
    std::cout << ">>> KESIMPULAN: Algoritma Optimal " << speedup << "x LEBIH CEPAT.\n";
}

// TEST 2: DEMO AUTO-SCHEDULE (NP-Complete) 
void runAutoScheduleDemo() {
    std::cout << "\n\n============================================\n";
    std::cout << "   TEST 2: DEMO GREEDY SCHEDULER (NP-COMPLETE)\n";
    std::cout << "   (Simulasi Penjadwalan Otomatis Banyak Acara)\n";
    std::cout << "============================================\n";

    BookingManager manager;
    
    // Buat 5 Ruangan
    manager.addAsset(new RuangRapat("Ruang_A"));
    manager.addAsset(new RuangRapat("Ruang_B"));
    manager.addAsset(new RuangRapat("Ruang_C"));
    manager.addAsset(new RuangRapat("Ruang_D"));
    manager.addAsset(new RuangRapat("Ruang_E"));

    // Buat 50 Permintaan Acara secara acak
    std::cout << "[INPUT] Menyiapkan 50 permintaan acara dengan waktu acak...\n";
    // coba range waktu sempit (misal jam 800 - 1500) supaya sering crash/bentrok
    // Ini memaksa algoritma Greedy bekerja keras mencari celah.
    std::vector<Reservasi> daftarRequest = generateDummyData(50, 800, 1500);

    // Jalankan Algoritma
    manager.autoSchedule(daftarRequest);
}

int main() {
    std::cout << "SIMULASI SISTEM PENJADWALAN KAMPUS (CPP OOP)\n";
    
    // Run Test Benchmarking (Untuk Data Grafik)
    runBenchmark();

    // Run Test Scheduling (Untuk Demo Fitur)
    runAutoScheduleDemo();

    return 0;
}


