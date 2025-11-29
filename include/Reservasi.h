#ifndef _RESERVASI_H
#define _RESERVASI_H
#include <string>\

class Reservasi {
    private:
    std::string id_kegiatan;
    int start_time; // integer sederhana untuk kemudahan(contoh: 900 = 09:00)
    int end_time;

    public:
    // cunstructor
    Reservasi(std::string id, int start, int end) : id_kegiatan(id), start_time(start), end_time(end){};

    // getter
    int getStart() const {};
    int getEnd() const {};
    std::string getId() const {};
};

#endif