#ifndef RINGJOBS1_HPP
#define RINGJOBS1_HPP

#include "types.hpp"
#include "serialization.hpp"

using namespace dbtoaster;

struct RingJobs1;
struct Jobs1MovieCompaniesRing;
struct Jobs1TitleRing;


struct Jobs1MovieCompaniesRing {
    STRING_TYPE production_note; // MIN(mc.note)

    explicit Jobs1MovieCompaniesRing() : production_note("") {}
    explicit Jobs1MovieCompaniesRing(const STRING_TYPE& _production_note)
        : production_note(_production_note) { }
        
    inline bool isZero() const { 
        return production_note == ""; 
    }

    Jobs1MovieCompaniesRing& operator+=(const Jobs1MovieCompaniesRing &r) {
        this->production_note = (this->production_note < r.production_note ? this->production_note : r.production_note);
        return *this;
    }

    // declare it inside the class
    friend RingJobs1 operator*(const Jobs1MovieCompaniesRing &lhs, const Jobs1TitleRing &rhs);
    // RingJobs1 operator*(const Jobs1TitleRing &other) {
    //     return RingJobs1(
    //         this->production_note,
    //         other.movie_title,
    //         other.movie_year
    //     );
    // }

    // the multiplicity doesn't matter here
    Jobs1MovieCompaniesRing operator*(long int alpha) const {
        return Jobs1MovieCompaniesRing(
            this->production_note
        );
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
        ar << ELEM_SEPARATOR;
        DBT_SERIALIZATION_NVP(ar, production_note);
    }
};



struct Jobs1TitleRing {
    STRING_TYPE movie_title; // MIN(t.title)
    int movie_year; // MIN(t.production_year)

    explicit Jobs1TitleRing() : movie_title(""), movie_year(0) { }
    explicit Jobs1TitleRing(const STRING_TYPE& _movie_title, int _movie_year)
        : movie_title(_movie_title), movie_year(_movie_year) { }
        
    inline bool isZero() const { 
        return movie_title == "" && movie_year == 0;
    }

    Jobs1TitleRing& operator+=(const Jobs1TitleRing &r) {
        this->movie_title = (this->movie_title < r.movie_title ? this->movie_title : r.movie_title);
        this->movie_year = (this->movie_year < r.movie_year ? this->movie_year : r.movie_year);
        return *this;
    }

    // declare it inside the class
    friend RingJobs1 operator*(const Jobs1TitleRing &lhs, const Jobs1MovieCompaniesRing &rhs);

    // RingJobs1 operator*(const Jobs1MovieCompaniesRing &other) {
    //     return RingJobs1(
    //         other.production_note,
    //         this->movie_title,
    //         this->movie_year
    //     );
    // }

    // the multiplicity doesn't matter here
    Jobs1TitleRing operator*(long int alpha) const {
        return Jobs1TitleRing(
            this->movie_title,
            this->movie_year
        );
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
        ar << ELEM_SEPARATOR;
        DBT_SERIALIZATION_NVP(ar, movie_title);
        ar << ELEM_SEPARATOR;
        DBT_SERIALIZATION_NVP(ar, movie_year);
    }
};


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

// define it outside the classes
RingJobs1 operator*(const Jobs1MovieCompaniesRing &lhs, const Jobs1TitleRing &rhs) {
    return RingJobs1(
        lhs.production_note,
        rhs.movie_title,
        rhs.movie_year
    );
}


// define it outside the classes
RingJobs1 operator*(const Jobs1TitleRing &lhs, const Jobs1MovieCompaniesRing &rhs) {
    return RingJobs1(
        rhs.production_note,
        lhs.movie_title,
        lhs.movie_year
    );
}


#endif /* RINGJOBS1_HPP */