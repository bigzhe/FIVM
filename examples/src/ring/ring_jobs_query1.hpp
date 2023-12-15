#ifndef RINGJOBS1_HPP
#define RINGJOBS1_HPP

#include "types.hpp"
#include "serialization.hpp"

using namespace dbtoaster;

struct RingJobs1 {
    STRING_TYPE production_note; // MIN(mc.note)
    STRING_TYPE movie_title; // MIN(t.title)
    int movie_year; // MIN(t.production_year)

    explicit RingJobs1() : production_note(""), movie_title(""), movie_year(0) { }
    explicit RingJobs1(const STRING_TYPE& _production_note, const STRING_TYPE& _movie_title, int _movie_year)
        : production_note(_production_note), movie_title(_movie_title), movie_year(_movie_year) { }
        
    inline bool isZero() const { 
        return production_note == "" && movie_title == "" && movie_year == 0;
    }

    RingJobs1& operator+=(const RingJobs1 &r) {
        this->production_note = (this->production_note < r.production_note ? this->production_note : r.production_note);
        this->movie_title = (this->movie_title < r.movie_title ? this->movie_title : r.movie_title);
        this->movie_year = (this->movie_year < r.movie_year ? this->movie_year : r.movie_year);
        return *this;
    }

    RingJobs1 operator*(const RingJobs1 &other) {
        return RingJobs1(
            this->production_note == "" ? other.production_note : this->production_note,
            this->movie_title == "" ? other.movie_title : this->movie_title,
            this->movie_year == 0 ? other.movie_year : this->movie_year
        );
    }

    // the multiplicity doesn't matter here
    RingJobs1 operator*(long int alpha) const {
        return RingJobs1(
            this->production_note,
            this->movie_title,
            this->movie_year
        );
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
        ar << ELEM_SEPARATOR;
        DBT_SERIALIZATION_NVP(ar, production_note);
        ar << ELEM_SEPARATOR;
        DBT_SERIALIZATION_NVP(ar, movie_title);
        ar << ELEM_SEPARATOR;
        DBT_SERIALIZATION_NVP(ar, movie_year);
    }
};

RingJobs1 operator*(long int alpha, const RingJobs1 &r) {
    return RingJobs1(r.production_note, r.movie_title, r.movie_year);
}

RingJobs1 Ulifttitles(int movie_year, const STRING_TYPE& title) {
    return RingJobs1("", title, movie_year);
}

RingJobs1 Uliftmoviecompanies(const STRING_TYPE& production_note) {
    return RingJobs1(production_note, "", 0);
}


#endif /* RINGJOBS1_HPP */