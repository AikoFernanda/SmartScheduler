#ifndef _BOOKINGMANAGER_H
#define _BOOKINGMANAGER_H
#include "Bookable.h"
#include <vector>
#include <iostream>

class BookingManager {
    private:
    // polymorphism, simpan pointer ke Bookable. Jika ada tambahan aset, manager ini tetap jalan tanpa diubah
    std::vector<Bookable*> daftar_aset;

    public:
    // destructor
    ~ BookingManager(){};

    // menambahkan aset baru ke sistem
    void addAsset(Bookable* aset) {daftar_aset.push_back(aset);} 

    // skenario 1: kelas P (booking manual 1 ruangan)
    bool bookManual(std::string nama_aset, std::string id, int start, int end);

    // skenario 2: kelas NP-complete (scheduler otomatis dengan algoritma greedy), inputnya list kegiatan yg mau dimasukkan
    void autoSchedule(std::vector<Reservasi> daftar_permintaan);
};
#endif