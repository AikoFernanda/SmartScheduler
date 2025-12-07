#ifndef _RUANGRAPAT_H
#define _RUANGRAPAT_H

#include "Bookable.h"
#include <vector>
#include <string>
#include <algorithm> //untuk sorting

class RuangRapat : public Bookable {
    private:
    // nama ruangan rapat
    std::string nama_ruang;

    // database jadwal internal ruangan ini
    std::vector<Reservasi> jadwal_booking;

    // helper untuk memudahkan switching algoritma
    bool use_optimal_algorithm;

    public:
    // constructor
    RuangRapat (std::string nama) : nama_ruang(nama), use_optimal_algorithm(false) {}
    // switcher algoritma
    void setAlgorithmMode(bool optimal) {use_optimal_algorithm = optimal;}

    // implementasi interface Bookable
    bool isAvailable(int start, int end) override;
    bool addBook(Reservasi res) override;
    std::string getName() const override {return nama_ruang;}
};

#endif