#include "../include/RuangRapat.h"
#include <iostream>
#include <algorithm> // untuk sort dan lower_bown

bool RuangRapat::isAvailable(int start, int end)
{
    // skenario 1 : algoritma naif (linear search)
    // time complexity : O(n)
    // cek satu per satu dari awal sampai akhir, loop sebanyak data yg tersimpan
    if (!use_optimal_algorithm)
    {
        for (const auto &booking : jadwal_booking)
        {
            if (start < booking.getEnd() && end > booking.getStart())
            {
                return false; // crash
            }
        }
        return true; // aman
    }

    // skenario 2 : algoritma optimal (binary search)
    // time complexity : O(log n)
    // langsung lompat ketengah dari kumpulan data, prinsip divide and conquer (std::lower_bound)
    else
    {
        auto comparator = [](const Reservasi &r, int val)
        {
            return r.getStart() < val;
        };

        // cari posisi menggunakan binary search
        auto it = std::lower_bound(
            jadwal_booking.begin(),
            jadwal_booking.end(),
            end,
            [](const Reservasi &r, int val)
            {
                return r.getStart() < val;
            });

        // jika iterator di awal, berarti semua jadwal ada setelah request
        if (it == jadwal_booking.begin())
        {
            return true; // aman
        }

        // cek satu elemen sebelumnya (prev)
        // karena mencari berdasarkan 'end', kemungkinan bentrok
        auto prev = std::prev(it);

        // cek apakah 'prev' ini endTime-nya menabrak startTime request
        if (prev->getEnd() > start)
        {
            return false; // crash
        }

        return true; // aman
    }
}

bool RuangRapat::addBook(Reservasi res)
{
    jadwal_booking.push_back(res);
    // data harus urut untuk binary search, sort berdasarkan startTime
    std::sort(jadwal_booking.begin(), jadwal_booking.end(),
              [](const Reservasi &a, const Reservasi &b)
              {
                  return a.getStart() < b.getStart();
              });

    return true; // tanda sukses
}

/** Penjelasan nanti di laporan kurleb
 * Pada metode isAvailable, kami menerapkan percabangan logika. 
 * Jika mode optimal diaktifkan, sistem menggunakan std::lower_bound yang merupakan implementasi Binary Search dengan kompleksitas O(logn). 
 * Ini jauh lebih efisien daripada iterasi for-loop biasa (O(n)) karena algoritma langsung mengeliminasi setengah populasi data jadwal dalam setiap langkah pencarian
 */