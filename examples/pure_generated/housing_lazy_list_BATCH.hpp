#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"

#include "ring/ring_relational_opt.hpp"

#define RELATION_HOUSE_DYNAMIC
#define RELATION_SHOP_DYNAMIC
#define RELATION_INSTITUTION_DYNAMIC
#define RELATION_RESTAURANT_DYNAMIC
#define RELATION_DEMOGRAPHICS_DYNAMIC
#define RELATION_TRANSPORT_DYNAMIC

namespace dbtoaster {

  /* Definitions of maps used for storing materialized views. */
  struct HOUSE_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE livingarea; DOUBLE_TYPE price; DOUBLE_TYPE nbbedrooms; DOUBLE_TYPE nbbathrooms; DOUBLE_TYPE kitchensize; DOUBLE_TYPE house; DOUBLE_TYPE flat; DOUBLE_TYPE unknown; DOUBLE_TYPE garden; DOUBLE_TYPE parking; long __av; HOUSE_entry* nxt; HOUSE_entry* prv;
  
    explicit HOUSE_entry() : nxt(nullptr), prv(nullptr) { }
    explicit HOUSE_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const long c11) { postcode = c0; livingarea = c1; price = c2; nbbedrooms = c3; nbbathrooms = c4; kitchensize = c5; house = c6; flat = c7; unknown = c8; garden = c9; parking = c10; __av = c11;  }
    HOUSE_entry(const HOUSE_entry& other) : postcode(other.postcode), livingarea(other.livingarea), price(other.price), nbbedrooms(other.nbbedrooms), nbbathrooms(other.nbbathrooms), kitchensize(other.kitchensize), house(other.house), flat(other.flat), unknown(other.unknown), garden(other.garden), parking(other.parking), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    HOUSE_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 11) return; */
        postcode = std::stod(f[0]); livingarea = std::stod(f[1]); price = std::stod(f[2]); nbbedrooms = std::stod(f[3]); nbbathrooms = std::stod(f[4]); kitchensize = std::stod(f[5]); house = std::stod(f[6]); flat = std::stod(f[7]); unknown = std::stod(f[8]); garden = std::stod(f[9]); parking = std::stod(f[10]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, livingarea);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, price);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbbedrooms);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbbathrooms);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, kitchensize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, house);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, flat);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, unknown);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, garden);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, parking);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct SHOP_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE openinghoursshop; DOUBLE_TYPE pricerangeshop; DOUBLE_TYPE sainsburys; DOUBLE_TYPE tesco; DOUBLE_TYPE ms; long __av; SHOP_entry* nxt; SHOP_entry* prv;
  
    explicit SHOP_entry() : nxt(nullptr), prv(nullptr) { }
    explicit SHOP_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const long c6) { postcode = c0; openinghoursshop = c1; pricerangeshop = c2; sainsburys = c3; tesco = c4; ms = c5; __av = c6;  }
    SHOP_entry(const SHOP_entry& other) : postcode(other.postcode), openinghoursshop(other.openinghoursshop), pricerangeshop(other.pricerangeshop), sainsburys(other.sainsburys), tesco(other.tesco), ms(other.ms), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    SHOP_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 6) return; */
        postcode = std::stod(f[0]); openinghoursshop = std::stod(f[1]); pricerangeshop = std::stod(f[2]); sainsburys = std::stod(f[3]); tesco = std::stod(f[4]); ms = std::stod(f[5]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, openinghoursshop);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, pricerangeshop);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, sainsburys);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, tesco);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ms);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct INSTITUTION_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE typeeducation; DOUBLE_TYPE sizeinstitution; long __av; INSTITUTION_entry* nxt; INSTITUTION_entry* prv;
  
    explicit INSTITUTION_entry() : nxt(nullptr), prv(nullptr) { }
    explicit INSTITUTION_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const long c3) { postcode = c0; typeeducation = c1; sizeinstitution = c2; __av = c3;  }
    INSTITUTION_entry(const INSTITUTION_entry& other) : postcode(other.postcode), typeeducation(other.typeeducation), sizeinstitution(other.sizeinstitution), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    INSTITUTION_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        postcode = std::stod(f[0]); typeeducation = std::stod(f[1]); sizeinstitution = std::stod(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, typeeducation);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, sizeinstitution);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct RESTAURANT_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE openinghoursrest; DOUBLE_TYPE pricerangerest; long __av; RESTAURANT_entry* nxt; RESTAURANT_entry* prv;
  
    explicit RESTAURANT_entry() : nxt(nullptr), prv(nullptr) { }
    explicit RESTAURANT_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const long c3) { postcode = c0; openinghoursrest = c1; pricerangerest = c2; __av = c3;  }
    RESTAURANT_entry(const RESTAURANT_entry& other) : postcode(other.postcode), openinghoursrest(other.openinghoursrest), pricerangerest(other.pricerangerest), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    RESTAURANT_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        postcode = std::stod(f[0]); openinghoursrest = std::stod(f[1]); pricerangerest = std::stod(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, openinghoursrest);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, pricerangerest);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DEMOGRAPHICS_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE averagesalary; DOUBLE_TYPE crimesperyear; DOUBLE_TYPE unemployment; DOUBLE_TYPE nbhospitals; long __av; DEMOGRAPHICS_entry* nxt; DEMOGRAPHICS_entry* prv;
  
    explicit DEMOGRAPHICS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DEMOGRAPHICS_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const long c5) { postcode = c0; averagesalary = c1; crimesperyear = c2; unemployment = c3; nbhospitals = c4; __av = c5;  }
    DEMOGRAPHICS_entry(const DEMOGRAPHICS_entry& other) : postcode(other.postcode), averagesalary(other.averagesalary), crimesperyear(other.crimesperyear), unemployment(other.unemployment), nbhospitals(other.nbhospitals), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DEMOGRAPHICS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        postcode = std::stod(f[0]); averagesalary = std::stod(f[1]); crimesperyear = std::stod(f[2]); unemployment = std::stod(f[3]); nbhospitals = std::stod(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, averagesalary);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, crimesperyear);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, unemployment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbhospitals);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TRANSPORT_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE nbbuslines; DOUBLE_TYPE nbtrainstations; DOUBLE_TYPE distancecitycentre; long __av; TRANSPORT_entry* nxt; TRANSPORT_entry* prv;
  
    explicit TRANSPORT_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TRANSPORT_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const long c4) { postcode = c0; nbbuslines = c1; nbtrainstations = c2; distancecitycentre = c3; __av = c4;  }
    TRANSPORT_entry(const TRANSPORT_entry& other) : postcode(other.postcode), nbbuslines(other.nbbuslines), nbtrainstations(other.nbtrainstations), distancecitycentre(other.distancecitycentre), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TRANSPORT_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        postcode = std::stod(f[0]); nbbuslines = std::stod(f[1]); nbtrainstations = std::stod(f[2]); distancecitycentre = std::stod(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbbuslines);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbtrainstations);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, distancecitycentre);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct V_HOUSE_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE livingarea; DOUBLE_TYPE price; DOUBLE_TYPE nbbedrooms; DOUBLE_TYPE nbbathrooms; DOUBLE_TYPE kitchensize; DOUBLE_TYPE house; DOUBLE_TYPE flat; DOUBLE_TYPE unknown; DOUBLE_TYPE garden; DOUBLE_TYPE parking; long __av; V_HOUSE_entry* nxt; V_HOUSE_entry* prv;
  
    explicit V_HOUSE_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_HOUSE_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const long c11) { postcode = c0; livingarea = c1; price = c2; nbbedrooms = c3; nbbathrooms = c4; kitchensize = c5; house = c6; flat = c7; unknown = c8; garden = c9; parking = c10; __av = c11;  }
    V_HOUSE_entry(const V_HOUSE_entry& other) : postcode(other.postcode), livingarea(other.livingarea), price(other.price), nbbedrooms(other.nbbedrooms), nbbathrooms(other.nbbathrooms), kitchensize(other.kitchensize), house(other.house), flat(other.flat), unknown(other.unknown), garden(other.garden), parking(other.parking), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_HOUSE_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 11) return; */
        postcode = std::stod(f[0]); livingarea = std::stod(f[1]); price = std::stod(f[2]); nbbedrooms = std::stod(f[3]); nbbathrooms = std::stod(f[4]); kitchensize = std::stod(f[5]); house = std::stod(f[6]); flat = std::stod(f[7]); unknown = std::stod(f[8]); garden = std::stod(f[9]); parking = std::stod(f[10]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_HOUSE_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10) { postcode = c0; livingarea = c1; price = c2; nbbedrooms = c3; nbbathrooms = c4; kitchensize = c5; house = c6; flat = c7; unknown = c8; garden = c9; parking = c10;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, livingarea);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, price);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbbedrooms);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbbathrooms);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, kitchensize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, house);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, flat);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, unknown);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, garden);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, parking);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_HOUSE_mapkey012345678910_idxfn {
    FORCE_INLINE static size_t hash(const V_HOUSE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.livingarea);
      hash_combine(h, e.price);
      hash_combine(h, e.nbbedrooms);
      hash_combine(h, e.nbbathrooms);
      hash_combine(h, e.kitchensize);
      hash_combine(h, e.house);
      hash_combine(h, e.flat);
      hash_combine(h, e.unknown);
      hash_combine(h, e.garden);
      hash_combine(h, e.parking);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_HOUSE_entry& x, const V_HOUSE_entry& y) {
      return x.postcode == y.postcode && x.livingarea == y.livingarea && x.price == y.price && x.nbbedrooms == y.nbbedrooms && x.nbbathrooms == y.nbbathrooms && x.kitchensize == y.kitchensize && x.house == y.house && x.flat == y.flat && x.unknown == y.unknown && x.garden == y.garden && x.parking == y.parking;
    }
  };
  
  typedef MultiHashMap<V_HOUSE_entry, long, 
    PrimaryHashIndex<V_HOUSE_entry, V_HOUSE_mapkey012345678910_idxfn>
  > V_HOUSE_map;
  
  
  struct V_SHOP_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE openinghoursshop; DOUBLE_TYPE pricerangeshop; DOUBLE_TYPE sainsburys; DOUBLE_TYPE tesco; DOUBLE_TYPE ms; long __av; V_SHOP_entry* nxt; V_SHOP_entry* prv;
  
    explicit V_SHOP_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_SHOP_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const long c6) { postcode = c0; openinghoursshop = c1; pricerangeshop = c2; sainsburys = c3; tesco = c4; ms = c5; __av = c6;  }
    V_SHOP_entry(const V_SHOP_entry& other) : postcode(other.postcode), openinghoursshop(other.openinghoursshop), pricerangeshop(other.pricerangeshop), sainsburys(other.sainsburys), tesco(other.tesco), ms(other.ms), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_SHOP_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 6) return; */
        postcode = std::stod(f[0]); openinghoursshop = std::stod(f[1]); pricerangeshop = std::stod(f[2]); sainsburys = std::stod(f[3]); tesco = std::stod(f[4]); ms = std::stod(f[5]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_SHOP_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5) { postcode = c0; openinghoursshop = c1; pricerangeshop = c2; sainsburys = c3; tesco = c4; ms = c5;  return *this; }
    FORCE_INLINE V_SHOP_entry& modify0(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, openinghoursshop);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, pricerangeshop);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, sainsburys);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, tesco);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ms);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_SHOP_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const V_SHOP_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.openinghoursshop);
      hash_combine(h, e.pricerangeshop);
      hash_combine(h, e.sainsburys);
      hash_combine(h, e.tesco);
      hash_combine(h, e.ms);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_SHOP_entry& x, const V_SHOP_entry& y) {
      return x.postcode == y.postcode && x.openinghoursshop == y.openinghoursshop && x.pricerangeshop == y.pricerangeshop && x.sainsburys == y.sainsburys && x.tesco == y.tesco && x.ms == y.ms;
    }
  };
  
  struct V_SHOP_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_SHOP_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_SHOP_entry& x, const V_SHOP_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_SHOP_entry, long, 
    PrimaryHashIndex<V_SHOP_entry, V_SHOP_mapkey012345_idxfn>,
    SecondaryHashIndex<V_SHOP_entry, V_SHOP_mapkey0_idxfn>
  > V_SHOP_map;
  
  
  struct V_INSTITUTION_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE typeeducation; DOUBLE_TYPE sizeinstitution; long __av; V_INSTITUTION_entry* nxt; V_INSTITUTION_entry* prv;
  
    explicit V_INSTITUTION_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_INSTITUTION_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const long c3) { postcode = c0; typeeducation = c1; sizeinstitution = c2; __av = c3;  }
    V_INSTITUTION_entry(const V_INSTITUTION_entry& other) : postcode(other.postcode), typeeducation(other.typeeducation), sizeinstitution(other.sizeinstitution), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_INSTITUTION_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        postcode = std::stod(f[0]); typeeducation = std::stod(f[1]); sizeinstitution = std::stod(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_INSTITUTION_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { postcode = c0; typeeducation = c1; sizeinstitution = c2;  return *this; }
    FORCE_INLINE V_INSTITUTION_entry& modify0(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, typeeducation);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, sizeinstitution);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_INSTITUTION_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const V_INSTITUTION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.typeeducation);
      hash_combine(h, e.sizeinstitution);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_INSTITUTION_entry& x, const V_INSTITUTION_entry& y) {
      return x.postcode == y.postcode && x.typeeducation == y.typeeducation && x.sizeinstitution == y.sizeinstitution;
    }
  };
  
  struct V_INSTITUTION_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_INSTITUTION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_INSTITUTION_entry& x, const V_INSTITUTION_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_INSTITUTION_entry, long, 
    PrimaryHashIndex<V_INSTITUTION_entry, V_INSTITUTION_mapkey012_idxfn>,
    SecondaryHashIndex<V_INSTITUTION_entry, V_INSTITUTION_mapkey0_idxfn>
  > V_INSTITUTION_map;
  
  
  struct V_RESTAURANT_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE openinghoursrest; DOUBLE_TYPE pricerangerest; long __av; V_RESTAURANT_entry* nxt; V_RESTAURANT_entry* prv;
  
    explicit V_RESTAURANT_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_RESTAURANT_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const long c3) { postcode = c0; openinghoursrest = c1; pricerangerest = c2; __av = c3;  }
    V_RESTAURANT_entry(const V_RESTAURANT_entry& other) : postcode(other.postcode), openinghoursrest(other.openinghoursrest), pricerangerest(other.pricerangerest), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_RESTAURANT_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        postcode = std::stod(f[0]); openinghoursrest = std::stod(f[1]); pricerangerest = std::stod(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_RESTAURANT_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { postcode = c0; openinghoursrest = c1; pricerangerest = c2;  return *this; }
    FORCE_INLINE V_RESTAURANT_entry& modify0(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, openinghoursrest);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, pricerangerest);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_RESTAURANT_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const V_RESTAURANT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.openinghoursrest);
      hash_combine(h, e.pricerangerest);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_RESTAURANT_entry& x, const V_RESTAURANT_entry& y) {
      return x.postcode == y.postcode && x.openinghoursrest == y.openinghoursrest && x.pricerangerest == y.pricerangerest;
    }
  };
  
  struct V_RESTAURANT_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_RESTAURANT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_RESTAURANT_entry& x, const V_RESTAURANT_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_RESTAURANT_entry, long, 
    PrimaryHashIndex<V_RESTAURANT_entry, V_RESTAURANT_mapkey012_idxfn>,
    SecondaryHashIndex<V_RESTAURANT_entry, V_RESTAURANT_mapkey0_idxfn>
  > V_RESTAURANT_map;
  
  
  struct V_DEMOGRAPHICS_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE averagesalary; DOUBLE_TYPE crimesperyear; DOUBLE_TYPE unemployment; DOUBLE_TYPE nbhospitals; long __av; V_DEMOGRAPHICS_entry* nxt; V_DEMOGRAPHICS_entry* prv;
  
    explicit V_DEMOGRAPHICS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_DEMOGRAPHICS_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const long c5) { postcode = c0; averagesalary = c1; crimesperyear = c2; unemployment = c3; nbhospitals = c4; __av = c5;  }
    V_DEMOGRAPHICS_entry(const V_DEMOGRAPHICS_entry& other) : postcode(other.postcode), averagesalary(other.averagesalary), crimesperyear(other.crimesperyear), unemployment(other.unemployment), nbhospitals(other.nbhospitals), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_DEMOGRAPHICS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        postcode = std::stod(f[0]); averagesalary = std::stod(f[1]); crimesperyear = std::stod(f[2]); unemployment = std::stod(f[3]); nbhospitals = std::stod(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_DEMOGRAPHICS_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4) { postcode = c0; averagesalary = c1; crimesperyear = c2; unemployment = c3; nbhospitals = c4;  return *this; }
    FORCE_INLINE V_DEMOGRAPHICS_entry& modify0(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, averagesalary);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, crimesperyear);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, unemployment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbhospitals);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_DEMOGRAPHICS_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const V_DEMOGRAPHICS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.averagesalary);
      hash_combine(h, e.crimesperyear);
      hash_combine(h, e.unemployment);
      hash_combine(h, e.nbhospitals);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_DEMOGRAPHICS_entry& x, const V_DEMOGRAPHICS_entry& y) {
      return x.postcode == y.postcode && x.averagesalary == y.averagesalary && x.crimesperyear == y.crimesperyear && x.unemployment == y.unemployment && x.nbhospitals == y.nbhospitals;
    }
  };
  
  struct V_DEMOGRAPHICS_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_DEMOGRAPHICS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_DEMOGRAPHICS_entry& x, const V_DEMOGRAPHICS_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_DEMOGRAPHICS_entry, long, 
    PrimaryHashIndex<V_DEMOGRAPHICS_entry, V_DEMOGRAPHICS_mapkey01234_idxfn>,
    SecondaryHashIndex<V_DEMOGRAPHICS_entry, V_DEMOGRAPHICS_mapkey0_idxfn>
  > V_DEMOGRAPHICS_map;
  
  
  struct V_TRANSPORT_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE nbbuslines; DOUBLE_TYPE nbtrainstations; DOUBLE_TYPE distancecitycentre; long __av; V_TRANSPORT_entry* nxt; V_TRANSPORT_entry* prv;
  
    explicit V_TRANSPORT_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_TRANSPORT_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const long c4) { postcode = c0; nbbuslines = c1; nbtrainstations = c2; distancecitycentre = c3; __av = c4;  }
    V_TRANSPORT_entry(const V_TRANSPORT_entry& other) : postcode(other.postcode), nbbuslines(other.nbbuslines), nbtrainstations(other.nbtrainstations), distancecitycentre(other.distancecitycentre), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_TRANSPORT_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        postcode = std::stod(f[0]); nbbuslines = std::stod(f[1]); nbtrainstations = std::stod(f[2]); distancecitycentre = std::stod(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_TRANSPORT_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3) { postcode = c0; nbbuslines = c1; nbtrainstations = c2; distancecitycentre = c3;  return *this; }
    FORCE_INLINE V_TRANSPORT_entry& modify0(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbbuslines);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbtrainstations);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, distancecitycentre);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_TRANSPORT_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const V_TRANSPORT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.nbbuslines);
      hash_combine(h, e.nbtrainstations);
      hash_combine(h, e.distancecitycentre);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_TRANSPORT_entry& x, const V_TRANSPORT_entry& y) {
      return x.postcode == y.postcode && x.nbbuslines == y.nbbuslines && x.nbtrainstations == y.nbtrainstations && x.distancecitycentre == y.distancecitycentre;
    }
  };
  
  struct V_TRANSPORT_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_TRANSPORT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_TRANSPORT_entry& x, const V_TRANSPORT_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_TRANSPORT_entry, long, 
    PrimaryHashIndex<V_TRANSPORT_entry, V_TRANSPORT_mapkey0123_idxfn>,
    SecondaryHashIndex<V_TRANSPORT_entry, V_TRANSPORT_mapkey0_idxfn>
  > V_TRANSPORT_map;
  
  
  struct DELTA_HOUSE_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE livingarea; DOUBLE_TYPE price; DOUBLE_TYPE nbbedrooms; DOUBLE_TYPE nbbathrooms; DOUBLE_TYPE kitchensize; DOUBLE_TYPE house; DOUBLE_TYPE flat; DOUBLE_TYPE unknown; DOUBLE_TYPE garden; DOUBLE_TYPE parking; long __av; DELTA_HOUSE_entry* nxt; DELTA_HOUSE_entry* prv;
  
    explicit DELTA_HOUSE_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_HOUSE_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const long c11) { postcode = c0; livingarea = c1; price = c2; nbbedrooms = c3; nbbathrooms = c4; kitchensize = c5; house = c6; flat = c7; unknown = c8; garden = c9; parking = c10; __av = c11;  }
    DELTA_HOUSE_entry(const DELTA_HOUSE_entry& other) : postcode(other.postcode), livingarea(other.livingarea), price(other.price), nbbedrooms(other.nbbedrooms), nbbathrooms(other.nbbathrooms), kitchensize(other.kitchensize), house(other.house), flat(other.flat), unknown(other.unknown), garden(other.garden), parking(other.parking), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_HOUSE_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 11) return; */
        postcode = std::stod(f[0]); livingarea = std::stod(f[1]); price = std::stod(f[2]); nbbedrooms = std::stod(f[3]); nbbathrooms = std::stod(f[4]); kitchensize = std::stod(f[5]); house = std::stod(f[6]); flat = std::stod(f[7]); unknown = std::stod(f[8]); garden = std::stod(f[9]); parking = std::stod(f[10]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_HOUSE_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10) { postcode = c0; livingarea = c1; price = c2; nbbedrooms = c3; nbbathrooms = c4; kitchensize = c5; house = c6; flat = c7; unknown = c8; garden = c9; parking = c10;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, livingarea);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, price);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbbedrooms);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbbathrooms);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, kitchensize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, house);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, flat);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, unknown);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, garden);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, parking);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_HOUSE_mapkey012345678910_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_HOUSE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.livingarea);
      hash_combine(h, e.price);
      hash_combine(h, e.nbbedrooms);
      hash_combine(h, e.nbbathrooms);
      hash_combine(h, e.kitchensize);
      hash_combine(h, e.house);
      hash_combine(h, e.flat);
      hash_combine(h, e.unknown);
      hash_combine(h, e.garden);
      hash_combine(h, e.parking);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_HOUSE_entry& x, const DELTA_HOUSE_entry& y) {
      return x.postcode == y.postcode && x.livingarea == y.livingarea && x.price == y.price && x.nbbedrooms == y.nbbedrooms && x.nbbathrooms == y.nbbathrooms && x.kitchensize == y.kitchensize && x.house == y.house && x.flat == y.flat && x.unknown == y.unknown && x.garden == y.garden && x.parking == y.parking;
    }
  };
  
  typedef MultiHashMap<DELTA_HOUSE_entry, long, 
    PrimaryHashIndex<DELTA_HOUSE_entry, DELTA_HOUSE_mapkey012345678910_idxfn>
  > DELTA_HOUSE_map;
  
  
  struct DELTA_SHOP_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE openinghoursshop; DOUBLE_TYPE pricerangeshop; DOUBLE_TYPE sainsburys; DOUBLE_TYPE tesco; DOUBLE_TYPE ms; long __av; DELTA_SHOP_entry* nxt; DELTA_SHOP_entry* prv;
  
    explicit DELTA_SHOP_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_SHOP_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const long c6) { postcode = c0; openinghoursshop = c1; pricerangeshop = c2; sainsburys = c3; tesco = c4; ms = c5; __av = c6;  }
    DELTA_SHOP_entry(const DELTA_SHOP_entry& other) : postcode(other.postcode), openinghoursshop(other.openinghoursshop), pricerangeshop(other.pricerangeshop), sainsburys(other.sainsburys), tesco(other.tesco), ms(other.ms), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_SHOP_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 6) return; */
        postcode = std::stod(f[0]); openinghoursshop = std::stod(f[1]); pricerangeshop = std::stod(f[2]); sainsburys = std::stod(f[3]); tesco = std::stod(f[4]); ms = std::stod(f[5]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_SHOP_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5) { postcode = c0; openinghoursshop = c1; pricerangeshop = c2; sainsburys = c3; tesco = c4; ms = c5;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, openinghoursshop);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, pricerangeshop);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, sainsburys);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, tesco);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ms);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_SHOP_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_SHOP_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.openinghoursshop);
      hash_combine(h, e.pricerangeshop);
      hash_combine(h, e.sainsburys);
      hash_combine(h, e.tesco);
      hash_combine(h, e.ms);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_SHOP_entry& x, const DELTA_SHOP_entry& y) {
      return x.postcode == y.postcode && x.openinghoursshop == y.openinghoursshop && x.pricerangeshop == y.pricerangeshop && x.sainsburys == y.sainsburys && x.tesco == y.tesco && x.ms == y.ms;
    }
  };
  
  typedef MultiHashMap<DELTA_SHOP_entry, long, 
    PrimaryHashIndex<DELTA_SHOP_entry, DELTA_SHOP_mapkey012345_idxfn>
  > DELTA_SHOP_map;
  
  
  struct DELTA_INSTITUTION_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE typeeducation; DOUBLE_TYPE sizeinstitution; long __av; DELTA_INSTITUTION_entry* nxt; DELTA_INSTITUTION_entry* prv;
  
    explicit DELTA_INSTITUTION_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_INSTITUTION_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const long c3) { postcode = c0; typeeducation = c1; sizeinstitution = c2; __av = c3;  }
    DELTA_INSTITUTION_entry(const DELTA_INSTITUTION_entry& other) : postcode(other.postcode), typeeducation(other.typeeducation), sizeinstitution(other.sizeinstitution), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_INSTITUTION_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        postcode = std::stod(f[0]); typeeducation = std::stod(f[1]); sizeinstitution = std::stod(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_INSTITUTION_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { postcode = c0; typeeducation = c1; sizeinstitution = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, typeeducation);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, sizeinstitution);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_INSTITUTION_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_INSTITUTION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.typeeducation);
      hash_combine(h, e.sizeinstitution);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_INSTITUTION_entry& x, const DELTA_INSTITUTION_entry& y) {
      return x.postcode == y.postcode && x.typeeducation == y.typeeducation && x.sizeinstitution == y.sizeinstitution;
    }
  };
  
  typedef MultiHashMap<DELTA_INSTITUTION_entry, long, 
    PrimaryHashIndex<DELTA_INSTITUTION_entry, DELTA_INSTITUTION_mapkey012_idxfn>
  > DELTA_INSTITUTION_map;
  
  
  struct DELTA_RESTAURANT_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE openinghoursrest; DOUBLE_TYPE pricerangerest; long __av; DELTA_RESTAURANT_entry* nxt; DELTA_RESTAURANT_entry* prv;
  
    explicit DELTA_RESTAURANT_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_RESTAURANT_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const long c3) { postcode = c0; openinghoursrest = c1; pricerangerest = c2; __av = c3;  }
    DELTA_RESTAURANT_entry(const DELTA_RESTAURANT_entry& other) : postcode(other.postcode), openinghoursrest(other.openinghoursrest), pricerangerest(other.pricerangerest), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_RESTAURANT_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        postcode = std::stod(f[0]); openinghoursrest = std::stod(f[1]); pricerangerest = std::stod(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_RESTAURANT_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { postcode = c0; openinghoursrest = c1; pricerangerest = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, openinghoursrest);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, pricerangerest);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_RESTAURANT_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_RESTAURANT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.openinghoursrest);
      hash_combine(h, e.pricerangerest);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_RESTAURANT_entry& x, const DELTA_RESTAURANT_entry& y) {
      return x.postcode == y.postcode && x.openinghoursrest == y.openinghoursrest && x.pricerangerest == y.pricerangerest;
    }
  };
  
  typedef MultiHashMap<DELTA_RESTAURANT_entry, long, 
    PrimaryHashIndex<DELTA_RESTAURANT_entry, DELTA_RESTAURANT_mapkey012_idxfn>
  > DELTA_RESTAURANT_map;
  
  
  struct DELTA_DEMOGRAPHICS_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE averagesalary; DOUBLE_TYPE crimesperyear; DOUBLE_TYPE unemployment; DOUBLE_TYPE nbhospitals; long __av; DELTA_DEMOGRAPHICS_entry* nxt; DELTA_DEMOGRAPHICS_entry* prv;
  
    explicit DELTA_DEMOGRAPHICS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_DEMOGRAPHICS_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const long c5) { postcode = c0; averagesalary = c1; crimesperyear = c2; unemployment = c3; nbhospitals = c4; __av = c5;  }
    DELTA_DEMOGRAPHICS_entry(const DELTA_DEMOGRAPHICS_entry& other) : postcode(other.postcode), averagesalary(other.averagesalary), crimesperyear(other.crimesperyear), unemployment(other.unemployment), nbhospitals(other.nbhospitals), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_DEMOGRAPHICS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        postcode = std::stod(f[0]); averagesalary = std::stod(f[1]); crimesperyear = std::stod(f[2]); unemployment = std::stod(f[3]); nbhospitals = std::stod(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_DEMOGRAPHICS_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4) { postcode = c0; averagesalary = c1; crimesperyear = c2; unemployment = c3; nbhospitals = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, averagesalary);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, crimesperyear);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, unemployment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbhospitals);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_DEMOGRAPHICS_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_DEMOGRAPHICS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.averagesalary);
      hash_combine(h, e.crimesperyear);
      hash_combine(h, e.unemployment);
      hash_combine(h, e.nbhospitals);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_DEMOGRAPHICS_entry& x, const DELTA_DEMOGRAPHICS_entry& y) {
      return x.postcode == y.postcode && x.averagesalary == y.averagesalary && x.crimesperyear == y.crimesperyear && x.unemployment == y.unemployment && x.nbhospitals == y.nbhospitals;
    }
  };
  
  typedef MultiHashMap<DELTA_DEMOGRAPHICS_entry, long, 
    PrimaryHashIndex<DELTA_DEMOGRAPHICS_entry, DELTA_DEMOGRAPHICS_mapkey01234_idxfn>
  > DELTA_DEMOGRAPHICS_map;
  
  
  struct DELTA_TRANSPORT_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE nbbuslines; DOUBLE_TYPE nbtrainstations; DOUBLE_TYPE distancecitycentre; long __av; DELTA_TRANSPORT_entry* nxt; DELTA_TRANSPORT_entry* prv;
  
    explicit DELTA_TRANSPORT_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_TRANSPORT_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const long c4) { postcode = c0; nbbuslines = c1; nbtrainstations = c2; distancecitycentre = c3; __av = c4;  }
    DELTA_TRANSPORT_entry(const DELTA_TRANSPORT_entry& other) : postcode(other.postcode), nbbuslines(other.nbbuslines), nbtrainstations(other.nbtrainstations), distancecitycentre(other.distancecitycentre), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_TRANSPORT_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        postcode = std::stod(f[0]); nbbuslines = std::stod(f[1]); nbtrainstations = std::stod(f[2]); distancecitycentre = std::stod(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_TRANSPORT_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3) { postcode = c0; nbbuslines = c1; nbtrainstations = c2; distancecitycentre = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbbuslines);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, nbtrainstations);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, distancecitycentre);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_TRANSPORT_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_TRANSPORT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.nbbuslines);
      hash_combine(h, e.nbtrainstations);
      hash_combine(h, e.distancecitycentre);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_TRANSPORT_entry& x, const DELTA_TRANSPORT_entry& y) {
      return x.postcode == y.postcode && x.nbbuslines == y.nbbuslines && x.nbtrainstations == y.nbtrainstations && x.distancecitycentre == y.distancecitycentre;
    }
  };
  
  typedef MultiHashMap<DELTA_TRANSPORT_entry, long, 
    PrimaryHashIndex<DELTA_TRANSPORT_entry, DELTA_TRANSPORT_mapkey0123_idxfn>
  > DELTA_TRANSPORT_map;

  

  /* Defines top-level materialized views */
  struct tlq_t {
    struct timeval t0, t; long tT, tN, tS;
    tlq_t(): tN(0), tS(0) , V_postcode_HSIRDT1(RingRelation<0, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>()) { 
      gettimeofday(&t0, NULL); 
    }
  
    /* Serialization code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << "\n";
      const RingRelation<0, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& _V_postcode_HSIRDT1 = get_V_postcode_HSIRDT1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_postcode_HSIRDT1), _V_postcode_HSIRDT1, "\t");
    }
  
    /* Functions returning / computing the results of top level queries */
    const RingRelation<0, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& get_V_postcode_HSIRDT1() const {
      return V_postcode_HSIRDT1;
    }
  
  protected:
    /* Data structures used for storing / computing top-level queries */
    RingRelation<0, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE> V_postcode_HSIRDT1 = RingRelation<0, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>();
    
  };

  /* Contains materialized views and processing (IVM) logic */
  struct data_t : tlq_t {
  
    data_t(): tlq_t() {
      
      
    }
  
    
  
    
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_batch_update_HOUSE(const std::vector<DELTA_HOUSE_entry>::iterator &begin, const std::vector<DELTA_HOUSE_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_HOUSE_entry>::iterator e1 = begin; e1 != end; e1++) {
          DOUBLE_TYPE postcode = e1->postcode;
          DOUBLE_TYPE livingarea = e1->livingarea;
          DOUBLE_TYPE price = e1->price;
          DOUBLE_TYPE nbbedrooms = e1->nbbedrooms;
          DOUBLE_TYPE nbbathrooms = e1->nbbathrooms;
          DOUBLE_TYPE kitchensize = e1->kitchensize;
          DOUBLE_TYPE house = e1->house;
          DOUBLE_TYPE flat = e1->flat;
          DOUBLE_TYPE unknown = e1->unknown;
          DOUBLE_TYPE garden = e1->garden;
          DOUBLE_TYPE parking = e1->parking;
          long v1 = e1->__av;
          V_HOUSE.addOrDelOnZero(se1.modify(postcode, livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking), v1);
        }
      }
    }
    
    
    void on_batch_update_SHOP(const std::vector<DELTA_SHOP_entry>::iterator &begin, const std::vector<DELTA_SHOP_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_SHOP_entry>::iterator e2 = begin; e2 != end; e2++) {
          DOUBLE_TYPE postcode = e2->postcode;
          DOUBLE_TYPE openinghoursshop = e2->openinghoursshop;
          DOUBLE_TYPE pricerangeshop = e2->pricerangeshop;
          DOUBLE_TYPE sainsburys = e2->sainsburys;
          DOUBLE_TYPE tesco = e2->tesco;
          DOUBLE_TYPE ms = e2->ms;
          long v2 = e2->__av;
          V_SHOP.addOrDelOnZero(se2.modify(postcode, openinghoursshop, pricerangeshop, sainsburys, tesco, ms), v2);
        }
      }
    }
    
    
    void on_batch_update_INSTITUTION(const std::vector<DELTA_INSTITUTION_entry>::iterator &begin, const std::vector<DELTA_INSTITUTION_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_INSTITUTION_entry>::iterator e3 = begin; e3 != end; e3++) {
          DOUBLE_TYPE postcode = e3->postcode;
          DOUBLE_TYPE typeeducation = e3->typeeducation;
          DOUBLE_TYPE sizeinstitution = e3->sizeinstitution;
          long v3 = e3->__av;
          V_INSTITUTION.addOrDelOnZero(se3.modify(postcode, typeeducation, sizeinstitution), v3);
        }
      }
    }
    
    
    void on_batch_update_RESTAURANT(const std::vector<DELTA_RESTAURANT_entry>::iterator &begin, const std::vector<DELTA_RESTAURANT_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_RESTAURANT_entry>::iterator e4 = begin; e4 != end; e4++) {
          DOUBLE_TYPE postcode = e4->postcode;
          DOUBLE_TYPE openinghoursrest = e4->openinghoursrest;
          DOUBLE_TYPE pricerangerest = e4->pricerangerest;
          long v4 = e4->__av;
          V_RESTAURANT.addOrDelOnZero(se4.modify(postcode, openinghoursrest, pricerangerest), v4);
        }
      }
    }
    
    
    void on_batch_update_DEMOGRAPHICS(const std::vector<DELTA_DEMOGRAPHICS_entry>::iterator &begin, const std::vector<DELTA_DEMOGRAPHICS_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_DEMOGRAPHICS_entry>::iterator e5 = begin; e5 != end; e5++) {
          DOUBLE_TYPE postcode = e5->postcode;
          DOUBLE_TYPE averagesalary = e5->averagesalary;
          DOUBLE_TYPE crimesperyear = e5->crimesperyear;
          DOUBLE_TYPE unemployment = e5->unemployment;
          DOUBLE_TYPE nbhospitals = e5->nbhospitals;
          long v5 = e5->__av;
          V_DEMOGRAPHICS.addOrDelOnZero(se5.modify(postcode, averagesalary, crimesperyear, unemployment, nbhospitals), v5);
        }
      }
    }
    
    
    void on_batch_update_TRANSPORT(const std::vector<DELTA_TRANSPORT_entry>::iterator &begin, const std::vector<DELTA_TRANSPORT_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_TRANSPORT_entry>::iterator e6 = begin; e6 != end; e6++) {
          DOUBLE_TYPE postcode = e6->postcode;
          DOUBLE_TYPE nbbuslines = e6->nbbuslines;
          DOUBLE_TYPE nbtrainstations = e6->nbtrainstations;
          DOUBLE_TYPE distancecitycentre = e6->distancecitycentre;
          long v6 = e6->__av;
          V_TRANSPORT.addOrDelOnZero(se6.modify(postcode, nbbuslines, nbtrainstations, distancecitycentre), v6);
        }
      }
    }
    
    
    void on_system_ready_event() {
      V_postcode_HSIRDT1.store.clear(); 
      { //foreach
        V_HOUSE_entry* e7 = V_HOUSE.head;
        while (e7) {
          DOUBLE_TYPE postcode = e7->postcode;
          DOUBLE_TYPE livingarea = e7->livingarea;
          DOUBLE_TYPE price = e7->price;
          DOUBLE_TYPE nbbedrooms = e7->nbbedrooms;
          DOUBLE_TYPE nbbathrooms = e7->nbbathrooms;
          DOUBLE_TYPE kitchensize = e7->kitchensize;
          DOUBLE_TYPE house = e7->house;
          DOUBLE_TYPE flat = e7->flat;
          DOUBLE_TYPE unknown = e7->unknown;
          DOUBLE_TYPE garden = e7->garden;
          DOUBLE_TYPE parking = e7->parking;
          long v7 = e7->__av;
          { //slice
            const LinkedNode<V_SHOP_entry>* n5 = static_cast<const LinkedNode<V_SHOP_entry>*>(V_SHOP.slice(se12.modify0(postcode), 0));
            V_SHOP_entry* e8;
            while (n5) {
              e8 = n5->obj;
              DOUBLE_TYPE openinghoursshop = e8->openinghoursshop;
              DOUBLE_TYPE pricerangeshop = e8->pricerangeshop;
              DOUBLE_TYPE sainsburys = e8->sainsburys;
              DOUBLE_TYPE tesco = e8->tesco;
              DOUBLE_TYPE ms = e8->ms;
              long v8 = e8->__av;
              { //slice
                const LinkedNode<V_INSTITUTION_entry>* n4 = static_cast<const LinkedNode<V_INSTITUTION_entry>*>(V_INSTITUTION.slice(se11.modify0(postcode), 0));
                V_INSTITUTION_entry* e9;
                while (n4) {
                  e9 = n4->obj;
                  DOUBLE_TYPE typeeducation = e9->typeeducation;
                  DOUBLE_TYPE sizeinstitution = e9->sizeinstitution;
                  long v9 = e9->__av;
                  { //slice
                    const LinkedNode<V_RESTAURANT_entry>* n3 = static_cast<const LinkedNode<V_RESTAURANT_entry>*>(V_RESTAURANT.slice(se10.modify0(postcode), 0));
                    V_RESTAURANT_entry* e10;
                    while (n3) {
                      e10 = n3->obj;
                      DOUBLE_TYPE openinghoursrest = e10->openinghoursrest;
                      DOUBLE_TYPE pricerangerest = e10->pricerangerest;
                      long v10 = e10->__av;
                      { //slice
                        const LinkedNode<V_DEMOGRAPHICS_entry>* n2 = static_cast<const LinkedNode<V_DEMOGRAPHICS_entry>*>(V_DEMOGRAPHICS.slice(se9.modify0(postcode), 0));
                        V_DEMOGRAPHICS_entry* e11;
                        while (n2) {
                          e11 = n2->obj;
                          DOUBLE_TYPE averagesalary = e11->averagesalary;
                          DOUBLE_TYPE crimesperyear = e11->crimesperyear;
                          DOUBLE_TYPE unemployment = e11->unemployment;
                          DOUBLE_TYPE nbhospitals = e11->nbhospitals;
                          long v11 = e11->__av;
                          { //slice
                            const LinkedNode<V_TRANSPORT_entry>* n1 = static_cast<const LinkedNode<V_TRANSPORT_entry>*>(V_TRANSPORT.slice(se8.modify0(postcode), 0));
                            V_TRANSPORT_entry* e12;
                            while (n1) {
                              e12 = n1->obj;
                              DOUBLE_TYPE nbbuslines = e12->nbbuslines;
                              DOUBLE_TYPE nbtrainstations = e12->nbtrainstations;
                              DOUBLE_TYPE distancecitycentre = e12->distancecitycentre;
                              long v12 = e12->__av;
                              V_postcode_HSIRDT1 += (((((((v7 * Ulift<1>(livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking)) * (v8 * Ulift<11>(openinghoursshop, pricerangeshop, sainsburys, tesco, ms))) * (v9 * Ulift<16>(typeeducation, sizeinstitution))) * (v10 * Ulift<18>(openinghoursrest, pricerangerest))) * (v11 * Ulift<20>(averagesalary, crimesperyear, unemployment, nbhospitals))) * (v12 * Ulift<24>(nbbuslines, nbtrainstations, distancecitycentre))) * Ulift<0>(postcode));
                              n1 = n1->next;
                            }
                          }
                          n2 = n2->next;
                        }
                      }
                      n3 = n3->next;
                    }
                  }
                  n4 = n4->next;
                }
              }
              n5 = n5->next;
            }
          }
          e7 = e7->nxt;
        }
      }
    }
  
  private:
    
      /* Preallocated map entries (to avoid recreation of temporary objects) */
      V_HOUSE_entry se1;
      V_SHOP_entry se2;
      V_INSTITUTION_entry se3;
      V_RESTAURANT_entry se4;
      V_DEMOGRAPHICS_entry se5;
      V_TRANSPORT_entry se6;
      V_TRANSPORT_entry se8;
      V_DEMOGRAPHICS_entry se9;
      V_RESTAURANT_entry se10;
      V_INSTITUTION_entry se11;
      V_SHOP_entry se12;
    
      
    
      /* Data structures used for storing materialized views */
      V_HOUSE_map V_HOUSE;
      V_SHOP_map V_SHOP;
      V_INSTITUTION_map V_INSTITUTION;
      V_RESTAURANT_map V_RESTAURANT;
      V_DEMOGRAPHICS_map V_DEMOGRAPHICS;
      V_TRANSPORT_map V_TRANSPORT;
      DELTA_HOUSE_map DELTA_HOUSE;
      DELTA_SHOP_map DELTA_SHOP;
      DELTA_INSTITUTION_map DELTA_INSTITUTION;
      DELTA_RESTAURANT_map DELTA_RESTAURANT;
      DELTA_DEMOGRAPHICS_map DELTA_DEMOGRAPHICS;
      DELTA_TRANSPORT_map DELTA_TRANSPORT;
    
      
    
  };

  

}