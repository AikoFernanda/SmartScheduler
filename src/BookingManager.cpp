#include "../include/BookingManager.h"
#include <algorithm>
#include <iomanip>

// skenario 1 : booking manual
bool BookingManager::bookManual(std::string nama_aset, std::string id, int start, int end)
{
    // cari aset berdasarka nama (linear search asetnya, conflict checknya O(log n))
    for (Bookable *asset : daftar_aset)
    {
        if (asset->getName() == nama_aset)
        {
            // cek ketersediaan (memanggil algoritma di ruang rapat)
            if (asset->isAvailable(start, end))
            {
                // jika aman, lakukan booking
                Reservasi baru(id, start, end);
                asset->addBook(baru);
                std::cout << "[SUCCESS] Booking " << id << " di " << nama_aset << " berhasil.\n";
                return true;
            }
            else
            {
                std::cout << "[FAILED]  Booking " << id << " di " << nama_aset << " GAGAL (Bentrok).\n";
                return false;
            }
        }
    }
    std::cout << "[ERROR]   Aset " << nama_aset << " tidak ditemukan.\n";
    return false;
}

// skenario 2 : auto schedule (batch request)
// pakai greedy (first-fit), solsui maslaah np-complete
void BookingManager::autoSchedule(std::vector<Reservasi> daftar_permintaan)
{
    std::cout << "\n=== MENJALANKAN ALGORITMA GREEDY (FIRST-FIT) ===\n";
    std::cout << "Memproses " << daftar_permintaan.size() << " permintaan ke " << daftar_aset.size() << " ruangan...\n";

    // heuristik (sorting)
    // greedy lebih baik jika permintaan sudah urut berdasarkan waktu mulai (earliest start time first)
    std::sort(daftar_permintaan.begin(), daftar_permintaan.end(), [](const Reservasi &a, const Reservasi &b)
              { return a.getStart() < b.getStart(); });

    int successCount = 0;
    int failCount = 0;

    // proses greedy
    for (const auto &req : daftar_permintaan)
    {
        bool isBooked = false;

        // masuk ke ruangan satu per satu (first-fit)
        for (Bookable *asset : daftar_aset)
        {
            // cek ruangan
            if (asset->isAvailable(req.getStart(), req.getEnd()))
            {
                // jika kosong, ambil (greedy decision)
                asset->addBook(req);
                isBooked = true;
                successCount++;

                // comment baris ini jika tidak inginingin log detail per item
                std::cout << " -> " << req.getId() << " masuk ke " << asset->getName() << "\n";

                break; // berhenti cari, lanjut ke request berikutny
            }
        }
        if (!isBooked)
        {
            failCount++;
            // std::cout << " -> " << req.getId() << " GAGAL (Tidak ada ruangan muat)\n";
        }
    }

    // laporan hasil
    std::cout << "=== HASIL PENJADWALAN OTOMATIS ===\n";
    std::cout << "Berhasil: " << successCount << "\n";
    std::cout << "Gagal   : " << failCount << "\n";
    double efficiency = (double)successCount / daftar_permintaan.size() * 100;
    std::cout << "efisiensi Algoritma: " << std::fixed << std::setprecision(2) << efficiency << "%\n";
}
/** Penjelasan nanti di laporan kurleb
 * Metode autoSchedule mengimplementasikan strategi Greedy First-Fit. 
 * Algoritma ini pertama-tama mengurutkan semua permintaan berdasarkan waktu mulai (Earliest Start Time First), 
 * kemudian mencoba menempatkan setiap kegiatan ke dalam ruangan pertama yang tersedia. 
 * Meskipun tidak menjamin solusi sempurna (karena masalah ini NP-Complete), pendekatan ini memberikan solusi yang cepat dan dapat diterima secara operasional.
 */
