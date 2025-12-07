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
    int getStart() const {return start_time;}
    int getEnd() const {return end_time;}
    std::string getId() const {return id_kegiatan;}
};

#endif