#ifndef _BOOKABLE_H
#define _BOOKABLE_H
#include <string>
#include "Reservasi.h"

class Bookable {
    public:
    // Virtual Destructor penting untuk Polymorphism yang aman
    virtual ~Bookable(){};

    // fitur utama conflict checking
    virtual bool isAvailable(int start, int end) = 0;

    // menambahkan booking baru
    virtual bool addBook(Reservasi res) = 0;

    // getter untuk dapat nama aset
    virtual std::string getName() const = 0;
};

#endif