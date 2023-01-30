#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"

#include "ring/ring_factorized.hpp"

#define RELATION_HOUSE_STATIC
#define RELATION_SHOP_STATIC
#define RELATION_INSTITUTION_STATIC
#define RELATION_RESTAURANT_STATIC
#define RELATION_DEMOGRAPHICS_STATIC
#define RELATION_TRANSPORT_STATIC

namespace dbtoaster {

  /* Definitions of maps used for storing materialized views. */
  struct V_house_H1_entry {
    DOUBLE_TYPE postcode; RingFactorizedRelation<1, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE> __av; V_house_H1_entry* nxt; V_house_H1_entry* prv;
  
    explicit V_house_H1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_house_H1_entry(const DOUBLE_TYPE c0, const RingFactorizedRelation<1, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& c1) { postcode = c0; __av = c1;  }
    V_house_H1_entry(const V_house_H1_entry& other) : postcode(other.postcode), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_house_H1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<1, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& v) {
        /* if (f.size() < 1) return; */
        postcode = std::stod(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_house_H1_entry& modify(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_house_H1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_house_H1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_house_H1_entry& x, const V_house_H1_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_house_H1_entry, RingFactorizedRelation<1, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_house_H1_entry, V_house_H1_mapkey0_idxfn>
  > V_house_H1_map;
  
  
  struct V_sainsburys_S1_entry {
    DOUBLE_TYPE postcode; RingFactorizedRelation<11, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE> __av; V_sainsburys_S1_entry* nxt; V_sainsburys_S1_entry* prv;
  
    explicit V_sainsburys_S1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_sainsburys_S1_entry(const DOUBLE_TYPE c0, const RingFactorizedRelation<11, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& c1) { postcode = c0; __av = c1;  }
    V_sainsburys_S1_entry(const V_sainsburys_S1_entry& other) : postcode(other.postcode), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_sainsburys_S1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<11, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& v) {
        /* if (f.size() < 1) return; */
        postcode = std::stod(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_sainsburys_S1_entry& modify(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_sainsburys_S1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_sainsburys_S1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_sainsburys_S1_entry& x, const V_sainsburys_S1_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_sainsburys_S1_entry, RingFactorizedRelation<11, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_sainsburys_S1_entry, V_sainsburys_S1_mapkey0_idxfn>
  > V_sainsburys_S1_map;
  
  
  struct V_typeeducation_I1_entry {
    DOUBLE_TYPE postcode; RingFactorizedRelation<16, DOUBLE_TYPE, DOUBLE_TYPE> __av; V_typeeducation_I1_entry* nxt; V_typeeducation_I1_entry* prv;
  
    explicit V_typeeducation_I1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_typeeducation_I1_entry(const DOUBLE_TYPE c0, const RingFactorizedRelation<16, DOUBLE_TYPE, DOUBLE_TYPE>& c1) { postcode = c0; __av = c1;  }
    V_typeeducation_I1_entry(const V_typeeducation_I1_entry& other) : postcode(other.postcode), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_typeeducation_I1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<16, DOUBLE_TYPE, DOUBLE_TYPE>& v) {
        /* if (f.size() < 1) return; */
        postcode = std::stod(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_typeeducation_I1_entry& modify(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_typeeducation_I1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_typeeducation_I1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_typeeducation_I1_entry& x, const V_typeeducation_I1_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_typeeducation_I1_entry, RingFactorizedRelation<16, DOUBLE_TYPE, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_typeeducation_I1_entry, V_typeeducation_I1_mapkey0_idxfn>
  > V_typeeducation_I1_map;
  
  
  struct V_pricerangerest_R1_entry {
    DOUBLE_TYPE postcode; RingFactorizedRelation<18, DOUBLE_TYPE, DOUBLE_TYPE> __av; V_pricerangerest_R1_entry* nxt; V_pricerangerest_R1_entry* prv;
  
    explicit V_pricerangerest_R1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_pricerangerest_R1_entry(const DOUBLE_TYPE c0, const RingFactorizedRelation<18, DOUBLE_TYPE, DOUBLE_TYPE>& c1) { postcode = c0; __av = c1;  }
    V_pricerangerest_R1_entry(const V_pricerangerest_R1_entry& other) : postcode(other.postcode), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_pricerangerest_R1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<18, DOUBLE_TYPE, DOUBLE_TYPE>& v) {
        /* if (f.size() < 1) return; */
        postcode = std::stod(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_pricerangerest_R1_entry& modify(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_pricerangerest_R1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_pricerangerest_R1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_pricerangerest_R1_entry& x, const V_pricerangerest_R1_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_pricerangerest_R1_entry, RingFactorizedRelation<18, DOUBLE_TYPE, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_pricerangerest_R1_entry, V_pricerangerest_R1_mapkey0_idxfn>
  > V_pricerangerest_R1_map;
  
  
  struct V_unemployment_D1_entry {
    DOUBLE_TYPE postcode; RingFactorizedRelation<20, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE> __av; V_unemployment_D1_entry* nxt; V_unemployment_D1_entry* prv;
  
    explicit V_unemployment_D1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_unemployment_D1_entry(const DOUBLE_TYPE c0, const RingFactorizedRelation<20, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& c1) { postcode = c0; __av = c1;  }
    V_unemployment_D1_entry(const V_unemployment_D1_entry& other) : postcode(other.postcode), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_unemployment_D1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<20, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& v) {
        /* if (f.size() < 1) return; */
        postcode = std::stod(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_unemployment_D1_entry& modify(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_unemployment_D1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_unemployment_D1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_unemployment_D1_entry& x, const V_unemployment_D1_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_unemployment_D1_entry, RingFactorizedRelation<20, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_unemployment_D1_entry, V_unemployment_D1_mapkey0_idxfn>
  > V_unemployment_D1_map;
  
  
  struct V_nbbuslines_T1_entry {
    DOUBLE_TYPE postcode; RingFactorizedRelation<24, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE> __av; V_nbbuslines_T1_entry* nxt; V_nbbuslines_T1_entry* prv;
  
    explicit V_nbbuslines_T1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_nbbuslines_T1_entry(const DOUBLE_TYPE c0, const RingFactorizedRelation<24, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& c1) { postcode = c0; __av = c1;  }
    V_nbbuslines_T1_entry(const V_nbbuslines_T1_entry& other) : postcode(other.postcode), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_nbbuslines_T1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<24, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& v) {
        /* if (f.size() < 1) return; */
        postcode = std::stod(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_nbbuslines_T1_entry& modify(const DOUBLE_TYPE c0) { postcode = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, postcode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_nbbuslines_T1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_nbbuslines_T1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_nbbuslines_T1_entry& x, const V_nbbuslines_T1_entry& y) {
      return x.postcode == y.postcode;
    }
  };
  
  typedef MultiHashMap<V_nbbuslines_T1_entry, RingFactorizedRelation<24, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_nbbuslines_T1_entry, V_nbbuslines_T1_mapkey0_idxfn>
  > V_nbbuslines_T1_map;
  
  
  struct HOUSE_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE livingarea; DOUBLE_TYPE price; DOUBLE_TYPE nbbedrooms; DOUBLE_TYPE nbbathrooms; DOUBLE_TYPE kitchensize; DOUBLE_TYPE house; DOUBLE_TYPE flat; DOUBLE_TYPE unknown; DOUBLE_TYPE garden; DOUBLE_TYPE parking; long __av; HOUSE_entry* nxt; HOUSE_entry* prv;
  
    explicit HOUSE_entry() : nxt(nullptr), prv(nullptr) { }
    explicit HOUSE_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const long c11) { postcode = c0; livingarea = c1; price = c2; nbbedrooms = c3; nbbathrooms = c4; kitchensize = c5; house = c6; flat = c7; unknown = c8; garden = c9; parking = c10; __av = c11;  }
    HOUSE_entry(const HOUSE_entry& other) : postcode(other.postcode), livingarea(other.livingarea), price(other.price), nbbedrooms(other.nbbedrooms), nbbathrooms(other.nbbathrooms), kitchensize(other.kitchensize), house(other.house), flat(other.flat), unknown(other.unknown), garden(other.garden), parking(other.parking), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    HOUSE_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 11) return; */
        postcode = std::stod(f[0]); livingarea = std::stod(f[1]); price = std::stod(f[2]); nbbedrooms = std::stod(f[3]); nbbathrooms = std::stod(f[4]); kitchensize = std::stod(f[5]); house = std::stod(f[6]); flat = std::stod(f[7]); unknown = std::stod(f[8]); garden = std::stod(f[9]); parking = std::stod(f[10]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE HOUSE_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10) { postcode = c0; livingarea = c1; price = c2; nbbedrooms = c3; nbbathrooms = c4; kitchensize = c5; house = c6; flat = c7; unknown = c8; garden = c9; parking = c10;  return *this; }
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
  
  struct HOUSE_mapkey012345678910_idxfn {
    FORCE_INLINE static size_t hash(const HOUSE_entry& e) {
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
    
    FORCE_INLINE static bool equals(const HOUSE_entry& x, const HOUSE_entry& y) {
      return x.postcode == y.postcode && x.livingarea == y.livingarea && x.price == y.price && x.nbbedrooms == y.nbbedrooms && x.nbbathrooms == y.nbbathrooms && x.kitchensize == y.kitchensize && x.house == y.house && x.flat == y.flat && x.unknown == y.unknown && x.garden == y.garden && x.parking == y.parking;
    }
  };
  
  typedef MultiHashMap<HOUSE_entry, long, 
    PrimaryHashIndex<HOUSE_entry, HOUSE_mapkey012345678910_idxfn>
  > HOUSE_map;
  
  
  struct SHOP_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE openinghoursshop; DOUBLE_TYPE pricerangeshop; DOUBLE_TYPE sainsburys; DOUBLE_TYPE tesco; DOUBLE_TYPE ms; long __av; SHOP_entry* nxt; SHOP_entry* prv;
  
    explicit SHOP_entry() : nxt(nullptr), prv(nullptr) { }
    explicit SHOP_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const long c6) { postcode = c0; openinghoursshop = c1; pricerangeshop = c2; sainsburys = c3; tesco = c4; ms = c5; __av = c6;  }
    SHOP_entry(const SHOP_entry& other) : postcode(other.postcode), openinghoursshop(other.openinghoursshop), pricerangeshop(other.pricerangeshop), sainsburys(other.sainsburys), tesco(other.tesco), ms(other.ms), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    SHOP_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 6) return; */
        postcode = std::stod(f[0]); openinghoursshop = std::stod(f[1]); pricerangeshop = std::stod(f[2]); sainsburys = std::stod(f[3]); tesco = std::stod(f[4]); ms = std::stod(f[5]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE SHOP_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5) { postcode = c0; openinghoursshop = c1; pricerangeshop = c2; sainsburys = c3; tesco = c4; ms = c5;  return *this; }
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
  
  struct SHOP_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const SHOP_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.openinghoursshop);
      hash_combine(h, e.pricerangeshop);
      hash_combine(h, e.sainsburys);
      hash_combine(h, e.tesco);
      hash_combine(h, e.ms);
      return h;
    }
    
    FORCE_INLINE static bool equals(const SHOP_entry& x, const SHOP_entry& y) {
      return x.postcode == y.postcode && x.openinghoursshop == y.openinghoursshop && x.pricerangeshop == y.pricerangeshop && x.sainsburys == y.sainsburys && x.tesco == y.tesco && x.ms == y.ms;
    }
  };
  
  typedef MultiHashMap<SHOP_entry, long, 
    PrimaryHashIndex<SHOP_entry, SHOP_mapkey012345_idxfn>
  > SHOP_map;
  
  
  struct INSTITUTION_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE typeeducation; DOUBLE_TYPE sizeinstitution; long __av; INSTITUTION_entry* nxt; INSTITUTION_entry* prv;
  
    explicit INSTITUTION_entry() : nxt(nullptr), prv(nullptr) { }
    explicit INSTITUTION_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const long c3) { postcode = c0; typeeducation = c1; sizeinstitution = c2; __av = c3;  }
    INSTITUTION_entry(const INSTITUTION_entry& other) : postcode(other.postcode), typeeducation(other.typeeducation), sizeinstitution(other.sizeinstitution), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    INSTITUTION_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        postcode = std::stod(f[0]); typeeducation = std::stod(f[1]); sizeinstitution = std::stod(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE INSTITUTION_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { postcode = c0; typeeducation = c1; sizeinstitution = c2;  return *this; }
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
  
  struct INSTITUTION_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const INSTITUTION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.typeeducation);
      hash_combine(h, e.sizeinstitution);
      return h;
    }
    
    FORCE_INLINE static bool equals(const INSTITUTION_entry& x, const INSTITUTION_entry& y) {
      return x.postcode == y.postcode && x.typeeducation == y.typeeducation && x.sizeinstitution == y.sizeinstitution;
    }
  };
  
  typedef MultiHashMap<INSTITUTION_entry, long, 
    PrimaryHashIndex<INSTITUTION_entry, INSTITUTION_mapkey012_idxfn>
  > INSTITUTION_map;
  
  
  struct RESTAURANT_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE openinghoursrest; DOUBLE_TYPE pricerangerest; long __av; RESTAURANT_entry* nxt; RESTAURANT_entry* prv;
  
    explicit RESTAURANT_entry() : nxt(nullptr), prv(nullptr) { }
    explicit RESTAURANT_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const long c3) { postcode = c0; openinghoursrest = c1; pricerangerest = c2; __av = c3;  }
    RESTAURANT_entry(const RESTAURANT_entry& other) : postcode(other.postcode), openinghoursrest(other.openinghoursrest), pricerangerest(other.pricerangerest), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    RESTAURANT_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        postcode = std::stod(f[0]); openinghoursrest = std::stod(f[1]); pricerangerest = std::stod(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE RESTAURANT_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2) { postcode = c0; openinghoursrest = c1; pricerangerest = c2;  return *this; }
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
  
  struct RESTAURANT_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const RESTAURANT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.openinghoursrest);
      hash_combine(h, e.pricerangerest);
      return h;
    }
    
    FORCE_INLINE static bool equals(const RESTAURANT_entry& x, const RESTAURANT_entry& y) {
      return x.postcode == y.postcode && x.openinghoursrest == y.openinghoursrest && x.pricerangerest == y.pricerangerest;
    }
  };
  
  typedef MultiHashMap<RESTAURANT_entry, long, 
    PrimaryHashIndex<RESTAURANT_entry, RESTAURANT_mapkey012_idxfn>
  > RESTAURANT_map;
  
  
  struct DEMOGRAPHICS_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE averagesalary; DOUBLE_TYPE crimesperyear; DOUBLE_TYPE unemployment; DOUBLE_TYPE nbhospitals; long __av; DEMOGRAPHICS_entry* nxt; DEMOGRAPHICS_entry* prv;
  
    explicit DEMOGRAPHICS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DEMOGRAPHICS_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, const long c5) { postcode = c0; averagesalary = c1; crimesperyear = c2; unemployment = c3; nbhospitals = c4; __av = c5;  }
    DEMOGRAPHICS_entry(const DEMOGRAPHICS_entry& other) : postcode(other.postcode), averagesalary(other.averagesalary), crimesperyear(other.crimesperyear), unemployment(other.unemployment), nbhospitals(other.nbhospitals), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DEMOGRAPHICS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        postcode = std::stod(f[0]); averagesalary = std::stod(f[1]); crimesperyear = std::stod(f[2]); unemployment = std::stod(f[3]); nbhospitals = std::stod(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DEMOGRAPHICS_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4) { postcode = c0; averagesalary = c1; crimesperyear = c2; unemployment = c3; nbhospitals = c4;  return *this; }
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
  
  struct DEMOGRAPHICS_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const DEMOGRAPHICS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.averagesalary);
      hash_combine(h, e.crimesperyear);
      hash_combine(h, e.unemployment);
      hash_combine(h, e.nbhospitals);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DEMOGRAPHICS_entry& x, const DEMOGRAPHICS_entry& y) {
      return x.postcode == y.postcode && x.averagesalary == y.averagesalary && x.crimesperyear == y.crimesperyear && x.unemployment == y.unemployment && x.nbhospitals == y.nbhospitals;
    }
  };
  
  typedef MultiHashMap<DEMOGRAPHICS_entry, long, 
    PrimaryHashIndex<DEMOGRAPHICS_entry, DEMOGRAPHICS_mapkey01234_idxfn>
  > DEMOGRAPHICS_map;
  
  
  struct TRANSPORT_entry {
    DOUBLE_TYPE postcode; DOUBLE_TYPE nbbuslines; DOUBLE_TYPE nbtrainstations; DOUBLE_TYPE distancecitycentre; long __av; TRANSPORT_entry* nxt; TRANSPORT_entry* prv;
  
    explicit TRANSPORT_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TRANSPORT_entry(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const long c4) { postcode = c0; nbbuslines = c1; nbtrainstations = c2; distancecitycentre = c3; __av = c4;  }
    TRANSPORT_entry(const TRANSPORT_entry& other) : postcode(other.postcode), nbbuslines(other.nbbuslines), nbtrainstations(other.nbtrainstations), distancecitycentre(other.distancecitycentre), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TRANSPORT_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        postcode = std::stod(f[0]); nbbuslines = std::stod(f[1]); nbtrainstations = std::stod(f[2]); distancecitycentre = std::stod(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TRANSPORT_entry& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3) { postcode = c0; nbbuslines = c1; nbtrainstations = c2; distancecitycentre = c3;  return *this; }
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
  
  struct TRANSPORT_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const TRANSPORT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.postcode);
      hash_combine(h, e.nbbuslines);
      hash_combine(h, e.nbtrainstations);
      hash_combine(h, e.distancecitycentre);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TRANSPORT_entry& x, const TRANSPORT_entry& y) {
      return x.postcode == y.postcode && x.nbbuslines == y.nbbuslines && x.nbtrainstations == y.nbtrainstations && x.distancecitycentre == y.distancecitycentre;
    }
  };
  
  typedef MultiHashMap<TRANSPORT_entry, long, 
    PrimaryHashIndex<TRANSPORT_entry, TRANSPORT_mapkey0123_idxfn>
  > TRANSPORT_map;

  

  /* Defines top-level materialized views */
  struct tlq_t {
    struct timeval t0, t; long tT, tN, tS;
    tlq_t(): tN(0), tS(0) , V_postcode_HSIRDT1(RingFactorizedRelation<0, DOUBLE_TYPE>()) { 
      gettimeofday(&t0, NULL); 
    }
  
    /* Serialization code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << "\n";
      const RingFactorizedRelation<0, DOUBLE_TYPE>& _V_postcode_HSIRDT1 = get_V_postcode_HSIRDT1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_postcode_HSIRDT1), _V_postcode_HSIRDT1, "\t");
      
      ar << "\n";
      const V_house_H1_map& _V_house_H1 = get_V_house_H1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_house_H1), _V_house_H1, "\t");
      
      ar << "\n";
      const V_sainsburys_S1_map& _V_sainsburys_S1 = get_V_sainsburys_S1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_sainsburys_S1), _V_sainsburys_S1, "\t");
      
      ar << "\n";
      const V_typeeducation_I1_map& _V_typeeducation_I1 = get_V_typeeducation_I1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_typeeducation_I1), _V_typeeducation_I1, "\t");
      
      ar << "\n";
      const V_pricerangerest_R1_map& _V_pricerangerest_R1 = get_V_pricerangerest_R1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_pricerangerest_R1), _V_pricerangerest_R1, "\t");
      
      ar << "\n";
      const V_unemployment_D1_map& _V_unemployment_D1 = get_V_unemployment_D1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_unemployment_D1), _V_unemployment_D1, "\t");
      
      ar << "\n";
      const V_nbbuslines_T1_map& _V_nbbuslines_T1 = get_V_nbbuslines_T1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_nbbuslines_T1), _V_nbbuslines_T1, "\t");
    }
  
    /* Functions returning / computing the results of top level queries */
    const RingFactorizedRelation<0, DOUBLE_TYPE>& get_V_postcode_HSIRDT1() const {
      return V_postcode_HSIRDT1;
    }
    
    const V_house_H1_map& get_V_house_H1() const {
      return V_house_H1;
    }
    
    const V_sainsburys_S1_map& get_V_sainsburys_S1() const {
      return V_sainsburys_S1;
    }
    
    const V_typeeducation_I1_map& get_V_typeeducation_I1() const {
      return V_typeeducation_I1;
    }
    
    const V_pricerangerest_R1_map& get_V_pricerangerest_R1() const {
      return V_pricerangerest_R1;
    }
    
    const V_unemployment_D1_map& get_V_unemployment_D1() const {
      return V_unemployment_D1;
    }
    
    const V_nbbuslines_T1_map& get_V_nbbuslines_T1() const {
      return V_nbbuslines_T1;
    }
  
  protected:
    /* Data structures used for storing / computing top-level queries */
    RingFactorizedRelation<0, DOUBLE_TYPE> V_postcode_HSIRDT1;
    V_house_H1_map V_house_H1;
    V_sainsburys_S1_map V_sainsburys_S1;
    V_typeeducation_I1_map V_typeeducation_I1;
    V_pricerangerest_R1_map V_pricerangerest_R1;
    V_unemployment_D1_map V_unemployment_D1;
    V_nbbuslines_T1_map V_nbbuslines_T1;
    
  };

  /* Contains materialized views and processing (IVM) logic */
  struct data_t : tlq_t {
  
    data_t(): tlq_t() {
      
      
    }
  
    
  
    
  
    /* Trigger functions for table relations */
    void on_insert_HOUSE(const DOUBLE_TYPE postcode, const DOUBLE_TYPE livingarea, const DOUBLE_TYPE price, const DOUBLE_TYPE nbbedrooms, const DOUBLE_TYPE nbbathrooms, const DOUBLE_TYPE kitchensize, const DOUBLE_TYPE house, const DOUBLE_TYPE flat, const DOUBLE_TYPE unknown, const DOUBLE_TYPE garden, const DOUBLE_TYPE parking) {
      HOUSE_entry entry1(postcode, livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking, 1);
      HOUSE.addOrDelOnZero(entry1, 1);
    }
    void on_insert_HOUSE(HOUSE_entry &e) {
      e.__av = 1;
      HOUSE.addOrDelOnZero(e, 1);
    }
    
    void on_insert_SHOP(const DOUBLE_TYPE postcode, const DOUBLE_TYPE openinghoursshop, const DOUBLE_TYPE pricerangeshop, const DOUBLE_TYPE sainsburys, const DOUBLE_TYPE tesco, const DOUBLE_TYPE ms) {
      SHOP_entry entry2(postcode, openinghoursshop, pricerangeshop, sainsburys, tesco, ms, 1);
      SHOP.addOrDelOnZero(entry2, 1);
    }
    void on_insert_SHOP(SHOP_entry &e) {
      e.__av = 1;
      SHOP.addOrDelOnZero(e, 1);
    }
    
    void on_insert_INSTITUTION(const DOUBLE_TYPE postcode, const DOUBLE_TYPE typeeducation, const DOUBLE_TYPE sizeinstitution) {
      INSTITUTION_entry entry3(postcode, typeeducation, sizeinstitution, 1);
      INSTITUTION.addOrDelOnZero(entry3, 1);
    }
    void on_insert_INSTITUTION(INSTITUTION_entry &e) {
      e.__av = 1;
      INSTITUTION.addOrDelOnZero(e, 1);
    }
    
    void on_insert_RESTAURANT(const DOUBLE_TYPE postcode, const DOUBLE_TYPE openinghoursrest, const DOUBLE_TYPE pricerangerest) {
      RESTAURANT_entry entry4(postcode, openinghoursrest, pricerangerest, 1);
      RESTAURANT.addOrDelOnZero(entry4, 1);
    }
    void on_insert_RESTAURANT(RESTAURANT_entry &e) {
      e.__av = 1;
      RESTAURANT.addOrDelOnZero(e, 1);
    }
    
    void on_insert_DEMOGRAPHICS(const DOUBLE_TYPE postcode, const DOUBLE_TYPE averagesalary, const DOUBLE_TYPE crimesperyear, const DOUBLE_TYPE unemployment, const DOUBLE_TYPE nbhospitals) {
      DEMOGRAPHICS_entry entry5(postcode, averagesalary, crimesperyear, unemployment, nbhospitals, 1);
      DEMOGRAPHICS.addOrDelOnZero(entry5, 1);
    }
    void on_insert_DEMOGRAPHICS(DEMOGRAPHICS_entry &e) {
      e.__av = 1;
      DEMOGRAPHICS.addOrDelOnZero(e, 1);
    }
    
    void on_insert_TRANSPORT(const DOUBLE_TYPE postcode, const DOUBLE_TYPE nbbuslines, const DOUBLE_TYPE nbtrainstations, const DOUBLE_TYPE distancecitycentre) {
      TRANSPORT_entry entry6(postcode, nbbuslines, nbtrainstations, distancecitycentre, 1);
      TRANSPORT.addOrDelOnZero(entry6, 1);
    }
    void on_insert_TRANSPORT(TRANSPORT_entry &e) {
      e.__av = 1;
      TRANSPORT.addOrDelOnZero(e, 1);
    }
    
    
    /* Trigger functions for stream relations */
    void on_system_ready_event() {
      V_house_H1.clear();
      { //foreach
        HOUSE_entry* e1 = HOUSE.head;
        while (e1) {
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
          V_house_H1.addOrDelOnZero(se1.modify(postcode), (v1 * Ulift<1>(livingarea, price, nbbedrooms, nbbathrooms, kitchensize, house, flat, unknown, garden, parking)));
          e1 = e1->nxt;
        }
      }
      
      V_sainsburys_S1.clear();
      { //foreach
        SHOP_entry* e2 = SHOP.head;
        while (e2) {
          DOUBLE_TYPE postcode = e2->postcode;
          DOUBLE_TYPE openinghoursshop = e2->openinghoursshop;
          DOUBLE_TYPE pricerangeshop = e2->pricerangeshop;
          DOUBLE_TYPE sainsburys = e2->sainsburys;
          DOUBLE_TYPE tesco = e2->tesco;
          DOUBLE_TYPE ms = e2->ms;
          long v2 = e2->__av;
          V_sainsburys_S1.addOrDelOnZero(se2.modify(postcode), (v2 * Ulift<11>(openinghoursshop, pricerangeshop, sainsburys, tesco, ms)));
          e2 = e2->nxt;
        }
      }
      
      V_typeeducation_I1.clear();
      { //foreach
        INSTITUTION_entry* e3 = INSTITUTION.head;
        while (e3) {
          DOUBLE_TYPE postcode = e3->postcode;
          DOUBLE_TYPE typeeducation = e3->typeeducation;
          DOUBLE_TYPE sizeinstitution = e3->sizeinstitution;
          long v3 = e3->__av;
          V_typeeducation_I1.addOrDelOnZero(se3.modify(postcode), (v3 * Ulift<16>(typeeducation, sizeinstitution)));
          e3 = e3->nxt;
        }
      }
      
      V_pricerangerest_R1.clear();
      { //foreach
        RESTAURANT_entry* e4 = RESTAURANT.head;
        while (e4) {
          DOUBLE_TYPE postcode = e4->postcode;
          DOUBLE_TYPE openinghoursrest = e4->openinghoursrest;
          DOUBLE_TYPE pricerangerest = e4->pricerangerest;
          long v4 = e4->__av;
          V_pricerangerest_R1.addOrDelOnZero(se4.modify(postcode), (v4 * Ulift<18>(openinghoursrest, pricerangerest)));
          e4 = e4->nxt;
        }
      }
      
      V_unemployment_D1.clear();
      { //foreach
        DEMOGRAPHICS_entry* e5 = DEMOGRAPHICS.head;
        while (e5) {
          DOUBLE_TYPE postcode = e5->postcode;
          DOUBLE_TYPE averagesalary = e5->averagesalary;
          DOUBLE_TYPE crimesperyear = e5->crimesperyear;
          DOUBLE_TYPE unemployment = e5->unemployment;
          DOUBLE_TYPE nbhospitals = e5->nbhospitals;
          long v5 = e5->__av;
          V_unemployment_D1.addOrDelOnZero(se5.modify(postcode), (v5 * Ulift<20>(averagesalary, crimesperyear, unemployment, nbhospitals)));
          e5 = e5->nxt;
        }
      }
      
      V_nbbuslines_T1.clear();
      { //foreach
        TRANSPORT_entry* e6 = TRANSPORT.head;
        while (e6) {
          DOUBLE_TYPE postcode = e6->postcode;
          DOUBLE_TYPE nbbuslines = e6->nbbuslines;
          DOUBLE_TYPE nbtrainstations = e6->nbtrainstations;
          DOUBLE_TYPE distancecitycentre = e6->distancecitycentre;
          long v6 = e6->__av;
          V_nbbuslines_T1.addOrDelOnZero(se6.modify(postcode), (v6 * Ulift<24>(nbbuslines, nbtrainstations, distancecitycentre)));
          e6 = e6->nxt;
        }
      }
      

    }
  
  private:
    
      /* Preallocated map entries (to avoid recreation of temporary objects) */
      V_house_H1_entry se1;
      V_sainsburys_S1_entry se2;
      V_typeeducation_I1_entry se3;
      V_pricerangerest_R1_entry se4;
      V_unemployment_D1_entry se5;
      V_nbbuslines_T1_entry se6;
      V_sainsburys_S1_entry se8;
      V_typeeducation_I1_entry se9;
      V_pricerangerest_R1_entry se10;
      V_unemployment_D1_entry se11;
      V_nbbuslines_T1_entry se12;
    
      
    
      /* Data structures used for storing materialized views */
      HOUSE_map HOUSE;
      SHOP_map SHOP;
      INSTITUTION_map INSTITUTION;
      RESTAURANT_map RESTAURANT;
      DEMOGRAPHICS_map DEMOGRAPHICS;
      TRANSPORT_map TRANSPORT;
    
      
    
  };

  

}