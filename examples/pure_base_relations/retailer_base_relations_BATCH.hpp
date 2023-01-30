#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"

#include "ring/ring_factorized.hpp"

#define RELATION_INVENTORY_STATIC
#define RELATION_LOCATION_STATIC
#define RELATION_CENSUS_STATIC
#define RELATION_ITEM_STATIC
#define RELATION_WEATHER_STATIC

namespace dbtoaster {

  /* Definitions of maps used for storing materialized views. */
  struct V_dateid_IIW1_entry {
    int locn; RingFactorizedRelation<1, int> __av; V_dateid_IIW1_entry* nxt; V_dateid_IIW1_entry* prv;
  
    explicit V_dateid_IIW1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_dateid_IIW1_entry(const int c0, const RingFactorizedRelation<1, int>& c1) { locn = c0; __av = c1;  }
    V_dateid_IIW1_entry(const V_dateid_IIW1_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_dateid_IIW1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<1, int>& v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_dateid_IIW1_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_dateid_IIW1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_dateid_IIW1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_dateid_IIW1_entry& x, const V_dateid_IIW1_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<V_dateid_IIW1_entry, RingFactorizedRelation<1, int>, 
    PrimaryHashIndex<V_dateid_IIW1_entry, V_dateid_IIW1_mapkey0_idxfn>
  > V_dateid_IIW1_map;
  
  
  struct V_ksn_II1_entry {
    int locn; int dateid; RingFactorizedRelation<2, int, int> __av; V_ksn_II1_entry* nxt; V_ksn_II1_entry* prv;
  
    explicit V_ksn_II1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_ksn_II1_entry(const int c0, const int c1, const RingFactorizedRelation<2, int, int>& c2) { locn = c0; dateid = c1; __av = c2;  }
    V_ksn_II1_entry(const V_ksn_II1_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_ksn_II1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<2, int, int>& v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_ksn_II1_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_ksn_II1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_ksn_II1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_ksn_II1_entry& x, const V_ksn_II1_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<V_ksn_II1_entry, RingFactorizedRelation<2, int, int>, 
    PrimaryHashIndex<V_ksn_II1_entry, V_ksn_II1_mapkey01_idxfn>
  > V_ksn_II1_map;
  
  
  struct V_subcategory_I1_entry {
    int ksn; RingFactorizedRelation<4, int8_t, int8_t, int8_t, DOUBLE_TYPE> __av; V_subcategory_I1_entry* nxt; V_subcategory_I1_entry* prv;
  
    explicit V_subcategory_I1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_subcategory_I1_entry(const int c0, const RingFactorizedRelation<4, int8_t, int8_t, int8_t, DOUBLE_TYPE>& c1) { ksn = c0; __av = c1;  }
    V_subcategory_I1_entry(const V_subcategory_I1_entry& other) : ksn(other.ksn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_subcategory_I1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<4, int8_t, int8_t, int8_t, DOUBLE_TYPE>& v) {
        /* if (f.size() < 1) return; */
        ksn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_subcategory_I1_entry& modify(const int c0) { ksn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_subcategory_I1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_subcategory_I1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_subcategory_I1_entry& x, const V_subcategory_I1_entry& y) {
      return x.ksn == y.ksn;
    }
  };
  
  typedef MultiHashMap<V_subcategory_I1_entry, RingFactorizedRelation<4, int8_t, int8_t, int8_t, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_subcategory_I1_entry, V_subcategory_I1_mapkey0_idxfn>
  > V_subcategory_I1_map;
  
  
  struct V_rain_W1_entry {
    int locn; int dateid; RingFactorizedRelation<8, int8_t, int8_t, int, int, DOUBLE_TYPE, int8_t> __av; V_rain_W1_entry* nxt; V_rain_W1_entry* prv;
  
    explicit V_rain_W1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_rain_W1_entry(const int c0, const int c1, const RingFactorizedRelation<8, int8_t, int8_t, int, int, DOUBLE_TYPE, int8_t>& c2) { locn = c0; dateid = c1; __av = c2;  }
    V_rain_W1_entry(const V_rain_W1_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_rain_W1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<8, int8_t, int8_t, int, int, DOUBLE_TYPE, int8_t>& v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_rain_W1_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_rain_W1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_rain_W1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_rain_W1_entry& x, const V_rain_W1_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<V_rain_W1_entry, RingFactorizedRelation<8, int8_t, int8_t, int, int, DOUBLE_TYPE, int8_t>, 
    PrimaryHashIndex<V_rain_W1_entry, V_rain_W1_mapkey01_idxfn>
  > V_rain_W1_map;
  
  
  struct V_zip_LC1_entry {
    int locn; RingFactorizedRelation<14, int> __av; V_zip_LC1_entry* nxt; V_zip_LC1_entry* prv;
  
    explicit V_zip_LC1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_zip_LC1_entry(const int c0, const RingFactorizedRelation<14, int>& c1) { locn = c0; __av = c1;  }
    V_zip_LC1_entry(const V_zip_LC1_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_zip_LC1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<14, int>& v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_zip_LC1_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_zip_LC1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_zip_LC1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_zip_LC1_entry& x, const V_zip_LC1_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<V_zip_LC1_entry, RingFactorizedRelation<14, int>, 
    PrimaryHashIndex<V_zip_LC1_entry, V_zip_LC1_mapkey0_idxfn>
  > V_zip_LC1_map;
  
  
  struct V_rgn_cd_L1_entry {
    int locn; int zip; RingFactorizedRelation<15, int, int, int, int, int, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE> __av; V_rgn_cd_L1_entry* nxt; V_rgn_cd_L1_entry* prv;
  
    explicit V_rgn_cd_L1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_rgn_cd_L1_entry(const int c0, const int c1, const RingFactorizedRelation<15, int, int, int, int, int, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& c2) { locn = c0; zip = c1; __av = c2;  }
    V_rgn_cd_L1_entry(const V_rgn_cd_L1_entry& other) : locn(other.locn), zip(other.zip), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_rgn_cd_L1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<15, int, int, int, int, int, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>& v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_rgn_cd_L1_entry& modify(const int c0, const int c1) { locn = c0; zip = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_rgn_cd_L1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_rgn_cd_L1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.zip);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_rgn_cd_L1_entry& x, const V_rgn_cd_L1_entry& y) {
      return x.locn == y.locn && x.zip == y.zip;
    }
  };
  
  typedef MultiHashMap<V_rgn_cd_L1_entry, RingFactorizedRelation<15, int, int, int, int, int, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_rgn_cd_L1_entry, V_rgn_cd_L1_mapkey01_idxfn>
  > V_rgn_cd_L1_map;
  
  
  struct V_population_C1_entry {
    int zip; RingFactorizedRelation<28, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int> __av; V_population_C1_entry* nxt; V_population_C1_entry* prv;
  
    explicit V_population_C1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_population_C1_entry(const int c0, const RingFactorizedRelation<28, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int>& c1) { zip = c0; __av = c1;  }
    V_population_C1_entry(const V_population_C1_entry& other) : zip(other.zip), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_population_C1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<28, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int>& v) {
        /* if (f.size() < 1) return; */
        zip = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_population_C1_entry& modify(const int c0) { zip = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_population_C1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_population_C1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.zip);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_population_C1_entry& x, const V_population_C1_entry& y) {
      return x.zip == y.zip;
    }
  };
  
  typedef MultiHashMap<V_population_C1_entry, RingFactorizedRelation<28, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int>, 
    PrimaryHashIndex<V_population_C1_entry, V_population_C1_mapkey0_idxfn>
  > V_population_C1_map;
  
  
  struct INVENTORY_entry {
    int locn; int dateid; int ksn; int inventoryunits; long __av; INVENTORY_entry* nxt; INVENTORY_entry* prv;
  
    explicit INVENTORY_entry() : nxt(nullptr), prv(nullptr) { }
    explicit INVENTORY_entry(const int c0, const int c1, const int c2, const int c3, const long c4) { locn = c0; dateid = c1; ksn = c2; inventoryunits = c3; __av = c4;  }
    INVENTORY_entry(const INVENTORY_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), inventoryunits(other.inventoryunits), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    INVENTORY_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); inventoryunits = std::stoi(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE INVENTORY_entry& modify(const int c0, const int c1, const int c2, const int c3) { locn = c0; dateid = c1; ksn = c2; inventoryunits = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, inventoryunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct INVENTORY_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const INVENTORY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      hash_combine(h, e.inventoryunits);
      return h;
    }
    
    FORCE_INLINE static bool equals(const INVENTORY_entry& x, const INVENTORY_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn && x.inventoryunits == y.inventoryunits;
    }
  };
  
  typedef MultiHashMap<INVENTORY_entry, long, 
    PrimaryHashIndex<INVENTORY_entry, INVENTORY_mapkey0123_idxfn>
  > INVENTORY_map;
  
  
  struct LOCATION_entry {
    int locn; int zip; int rgn_cd; int clim_zn_nbr; int tot_area_sq_ft; int sell_area_sq_ft; int avghhi; DOUBLE_TYPE supertargetdistance; DOUBLE_TYPE supertargetdrivetime; DOUBLE_TYPE targetdistance; DOUBLE_TYPE targetdrivetime; DOUBLE_TYPE walmartdistance; DOUBLE_TYPE walmartdrivetime; DOUBLE_TYPE walmartsupercenterdistance; DOUBLE_TYPE walmartsupercenterdrivetime; long __av; LOCATION_entry* nxt; LOCATION_entry* prv;
  
    explicit LOCATION_entry() : nxt(nullptr), prv(nullptr) { }
    explicit LOCATION_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14, const long c15) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14; __av = c15;  }
    LOCATION_entry(const LOCATION_entry& other) : locn(other.locn), zip(other.zip), rgn_cd(other.rgn_cd), clim_zn_nbr(other.clim_zn_nbr), tot_area_sq_ft(other.tot_area_sq_ft), sell_area_sq_ft(other.sell_area_sq_ft), avghhi(other.avghhi), supertargetdistance(other.supertargetdistance), supertargetdrivetime(other.supertargetdrivetime), targetdistance(other.targetdistance), targetdrivetime(other.targetdrivetime), walmartdistance(other.walmartdistance), walmartdrivetime(other.walmartdrivetime), walmartsupercenterdistance(other.walmartsupercenterdistance), walmartsupercenterdrivetime(other.walmartsupercenterdrivetime), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    LOCATION_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 15) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); rgn_cd = std::stoi(f[2]); clim_zn_nbr = std::stoi(f[3]); tot_area_sq_ft = std::stoi(f[4]); sell_area_sq_ft = std::stoi(f[5]); avghhi = std::stoi(f[6]); supertargetdistance = std::stod(f[7]); supertargetdrivetime = std::stod(f[8]); targetdistance = std::stod(f[9]); targetdrivetime = std::stod(f[10]); walmartdistance = std::stod(f[11]); walmartdrivetime = std::stod(f[12]); walmartsupercenterdistance = std::stod(f[13]); walmartsupercenterdrivetime = std::stod(f[14]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE LOCATION_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rgn_cd);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, clim_zn_nbr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, tot_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, sell_area_sq_ft);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, avghhi);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supertargetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, supertargetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, targetdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, targetdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartsupercenterdistance);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, walmartsupercenterdrivetime);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct LOCATION_mapkey01234567891011121314_idxfn {
    FORCE_INLINE static size_t hash(const LOCATION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.zip);
      hash_combine(h, e.rgn_cd);
      hash_combine(h, e.clim_zn_nbr);
      hash_combine(h, e.tot_area_sq_ft);
      hash_combine(h, e.sell_area_sq_ft);
      hash_combine(h, e.avghhi);
      hash_combine(h, e.supertargetdistance);
      hash_combine(h, e.supertargetdrivetime);
      hash_combine(h, e.targetdistance);
      hash_combine(h, e.targetdrivetime);
      hash_combine(h, e.walmartdistance);
      hash_combine(h, e.walmartdrivetime);
      hash_combine(h, e.walmartsupercenterdistance);
      hash_combine(h, e.walmartsupercenterdrivetime);
      return h;
    }
    
    FORCE_INLINE static bool equals(const LOCATION_entry& x, const LOCATION_entry& y) {
      return x.locn == y.locn && x.zip == y.zip && x.rgn_cd == y.rgn_cd && x.clim_zn_nbr == y.clim_zn_nbr && x.tot_area_sq_ft == y.tot_area_sq_ft && x.sell_area_sq_ft == y.sell_area_sq_ft && x.avghhi == y.avghhi && x.supertargetdistance == y.supertargetdistance && x.supertargetdrivetime == y.supertargetdrivetime && x.targetdistance == y.targetdistance && x.targetdrivetime == y.targetdrivetime && x.walmartdistance == y.walmartdistance && x.walmartdrivetime == y.walmartdrivetime && x.walmartsupercenterdistance == y.walmartsupercenterdistance && x.walmartsupercenterdrivetime == y.walmartsupercenterdrivetime;
    }
  };
  
  typedef MultiHashMap<LOCATION_entry, long, 
    PrimaryHashIndex<LOCATION_entry, LOCATION_mapkey01234567891011121314_idxfn>
  > LOCATION_map;
  
  
  struct CENSUS_entry {
    int zip; int population; int white; int asian; int pacific; int blackafrican; DOUBLE_TYPE medianage; int occupiedhouseunits; int houseunits; int families; int households; int husbwife; int males; int females; int householdschildren; int hispanic; long __av; CENSUS_entry* nxt; CENSUS_entry* prv;
  
    explicit CENSUS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit CENSUS_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15, const long c16) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15; __av = c16;  }
    CENSUS_entry(const CENSUS_entry& other) : zip(other.zip), population(other.population), white(other.white), asian(other.asian), pacific(other.pacific), blackafrican(other.blackafrican), medianage(other.medianage), occupiedhouseunits(other.occupiedhouseunits), houseunits(other.houseunits), families(other.families), households(other.households), husbwife(other.husbwife), males(other.males), females(other.females), householdschildren(other.householdschildren), hispanic(other.hispanic), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    CENSUS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 16) return; */
        zip = std::stoi(f[0]); population = std::stoi(f[1]); white = std::stoi(f[2]); asian = std::stoi(f[3]); pacific = std::stoi(f[4]); blackafrican = std::stoi(f[5]); medianage = std::stod(f[6]); occupiedhouseunits = std::stoi(f[7]); houseunits = std::stoi(f[8]); families = std::stoi(f[9]); households = std::stoi(f[10]); husbwife = std::stoi(f[11]); males = std::stoi(f[12]); females = std::stoi(f[13]); householdschildren = std::stoi(f[14]); hispanic = std::stoi(f[15]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE CENSUS_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, population);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, white);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, asian);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, pacific);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, blackafrican);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, medianage);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, occupiedhouseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, houseunits);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, families);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, households);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, husbwife);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, males);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, females);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, householdschildren);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, hispanic);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct CENSUS_mapkey0123456789101112131415_idxfn {
    FORCE_INLINE static size_t hash(const CENSUS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.zip);
      hash_combine(h, e.population);
      hash_combine(h, e.white);
      hash_combine(h, e.asian);
      hash_combine(h, e.pacific);
      hash_combine(h, e.blackafrican);
      hash_combine(h, e.medianage);
      hash_combine(h, e.occupiedhouseunits);
      hash_combine(h, e.houseunits);
      hash_combine(h, e.families);
      hash_combine(h, e.households);
      hash_combine(h, e.husbwife);
      hash_combine(h, e.males);
      hash_combine(h, e.females);
      hash_combine(h, e.householdschildren);
      hash_combine(h, e.hispanic);
      return h;
    }
    
    FORCE_INLINE static bool equals(const CENSUS_entry& x, const CENSUS_entry& y) {
      return x.zip == y.zip && x.population == y.population && x.white == y.white && x.asian == y.asian && x.pacific == y.pacific && x.blackafrican == y.blackafrican && x.medianage == y.medianage && x.occupiedhouseunits == y.occupiedhouseunits && x.houseunits == y.houseunits && x.families == y.families && x.households == y.households && x.husbwife == y.husbwife && x.males == y.males && x.females == y.females && x.householdschildren == y.householdschildren && x.hispanic == y.hispanic;
    }
  };
  
  typedef MultiHashMap<CENSUS_entry, long, 
    PrimaryHashIndex<CENSUS_entry, CENSUS_mapkey0123456789101112131415_idxfn>
  > CENSUS_map;
  
  
  struct ITEM_entry {
    int ksn; int8_t subcategory; int8_t category; int8_t categorycluster; DOUBLE_TYPE prize; long __av; ITEM_entry* nxt; ITEM_entry* prv;
  
    explicit ITEM_entry() : nxt(nullptr), prv(nullptr) { }
    explicit ITEM_entry(const int c0, const int8_t c1, const int8_t c2, const int8_t c3, const DOUBLE_TYPE c4, const long c5) { ksn = c0; subcategory = c1; category = c2; categorycluster = c3; prize = c4; __av = c5;  }
    ITEM_entry(const ITEM_entry& other) : ksn(other.ksn), subcategory(other.subcategory), category(other.category), categorycluster(other.categorycluster), prize(other.prize), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    ITEM_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        ksn = std::stoi(f[0]); subcategory = (int8_t) std::stoi(f[1]); category = (int8_t) std::stoi(f[2]); categorycluster = (int8_t) std::stoi(f[3]); prize = std::stod(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE ITEM_entry& modify(const int c0, const int8_t c1, const int8_t c2, const int8_t c3, const DOUBLE_TYPE c4) { ksn = c0; subcategory = c1; category = c2; categorycluster = c3; prize = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, subcategory);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, category);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, categorycluster);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct ITEM_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const ITEM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      hash_combine(h, e.subcategory);
      hash_combine(h, e.category);
      hash_combine(h, e.categorycluster);
      hash_combine(h, e.prize);
      return h;
    }
    
    FORCE_INLINE static bool equals(const ITEM_entry& x, const ITEM_entry& y) {
      return x.ksn == y.ksn && x.subcategory == y.subcategory && x.category == y.category && x.categorycluster == y.categorycluster && x.prize == y.prize;
    }
  };
  
  typedef MultiHashMap<ITEM_entry, long, 
    PrimaryHashIndex<ITEM_entry, ITEM_mapkey01234_idxfn>
  > ITEM_map;
  
  
  struct WEATHER_entry {
    int locn; int dateid; int8_t rain; int8_t snow; int maxtemp; int mintemp; DOUBLE_TYPE meanwind; int8_t thunder; long __av; WEATHER_entry* nxt; WEATHER_entry* prv;
  
    explicit WEATHER_entry() : nxt(nullptr), prv(nullptr) { }
    explicit WEATHER_entry(const int c0, const int c1, const int8_t c2, const int8_t c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int8_t c7, const long c8) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7; __av = c8;  }
    WEATHER_entry(const WEATHER_entry& other) : locn(other.locn), dateid(other.dateid), rain(other.rain), snow(other.snow), maxtemp(other.maxtemp), mintemp(other.mintemp), meanwind(other.meanwind), thunder(other.thunder), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    WEATHER_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 8) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); rain = (int8_t) std::stoi(f[2]); snow = (int8_t) std::stoi(f[3]); maxtemp = std::stoi(f[4]); mintemp = std::stoi(f[5]); meanwind = std::stod(f[6]); thunder = (int8_t) std::stoi(f[7]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE WEATHER_entry& modify(const int c0, const int c1, const int8_t c2, const int8_t c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int8_t c7) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, rain);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, snow);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, maxtemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, mintemp);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, meanwind);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, thunder);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct WEATHER_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const WEATHER_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.rain);
      hash_combine(h, e.snow);
      hash_combine(h, e.maxtemp);
      hash_combine(h, e.mintemp);
      hash_combine(h, e.meanwind);
      hash_combine(h, e.thunder);
      return h;
    }
    
    FORCE_INLINE static bool equals(const WEATHER_entry& x, const WEATHER_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.rain == y.rain && x.snow == y.snow && x.maxtemp == y.maxtemp && x.mintemp == y.mintemp && x.meanwind == y.meanwind && x.thunder == y.thunder;
    }
  };
  
  typedef MultiHashMap<WEATHER_entry, long, 
    PrimaryHashIndex<WEATHER_entry, WEATHER_mapkey01234567_idxfn>
  > WEATHER_map;

  

  /* Defines top-level materialized views */
  struct tlq_t {
    struct timeval t0, t; long tT, tN, tS;
    tlq_t(): tN(0), tS(0) , V_locn_IIWLC1(RingFactorizedRelation<0, int>()) { 
      gettimeofday(&t0, NULL); 
    }
  
    /* Serialization code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << "\n";
      const RingFactorizedRelation<0, int>& _V_locn_IIWLC1 = get_V_locn_IIWLC1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_locn_IIWLC1), _V_locn_IIWLC1, "\t");
      
      ar << "\n";
      const V_dateid_IIW1_map& _V_dateid_IIW1 = get_V_dateid_IIW1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_dateid_IIW1), _V_dateid_IIW1, "\t");
      
      ar << "\n";
      const V_ksn_II1_map& _V_ksn_II1 = get_V_ksn_II1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_ksn_II1), _V_ksn_II1, "\t");
      
      ar << "\n";
      const V_subcategory_I1_map& _V_subcategory_I1 = get_V_subcategory_I1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_subcategory_I1), _V_subcategory_I1, "\t");
      
      ar << "\n";
      const V_rain_W1_map& _V_rain_W1 = get_V_rain_W1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_rain_W1), _V_rain_W1, "\t");
      
      ar << "\n";
      const V_zip_LC1_map& _V_zip_LC1 = get_V_zip_LC1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_zip_LC1), _V_zip_LC1, "\t");
      
      ar << "\n";
      const V_rgn_cd_L1_map& _V_rgn_cd_L1 = get_V_rgn_cd_L1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_rgn_cd_L1), _V_rgn_cd_L1, "\t");
      
      ar << "\n";
      const V_population_C1_map& _V_population_C1 = get_V_population_C1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_population_C1), _V_population_C1, "\t");
    }
  
    /* Functions returning / computing the results of top level queries */
    const RingFactorizedRelation<0, int>& get_V_locn_IIWLC1() const {
      return V_locn_IIWLC1;
    }
    
    const V_dateid_IIW1_map& get_V_dateid_IIW1() const {
      return V_dateid_IIW1;
    }
    
    const V_ksn_II1_map& get_V_ksn_II1() const {
      return V_ksn_II1;
    }
    
    const V_subcategory_I1_map& get_V_subcategory_I1() const {
      return V_subcategory_I1;
    }
    
    const V_rain_W1_map& get_V_rain_W1() const {
      return V_rain_W1;
    }
    
    const V_zip_LC1_map& get_V_zip_LC1() const {
      return V_zip_LC1;
    }
    
    const V_rgn_cd_L1_map& get_V_rgn_cd_L1() const {
      return V_rgn_cd_L1;
    }
    
    const V_population_C1_map& get_V_population_C1() const {
      return V_population_C1;
    }
  
  protected:
    /* Data structures used for storing / computing top-level queries */
    RingFactorizedRelation<0, int> V_locn_IIWLC1;
    V_dateid_IIW1_map V_dateid_IIW1;
    V_ksn_II1_map V_ksn_II1;
    V_subcategory_I1_map V_subcategory_I1;
    V_rain_W1_map V_rain_W1;
    V_zip_LC1_map V_zip_LC1;
    V_rgn_cd_L1_map V_rgn_cd_L1;
    V_population_C1_map V_population_C1;
    
  };

  /* Contains materialized views and processing (IVM) logic */
  struct data_t : tlq_t {
  
    data_t(): tlq_t() {
      
      
    }
  
    
  
    
  
    /* Trigger functions for table relations */
    void on_insert_INVENTORY(const int locn, const int dateid, const int ksn, const int inventoryunits) {
      INVENTORY_entry entry1(locn, dateid, ksn, inventoryunits, 1);
      INVENTORY.addOrDelOnZero(entry1, 1);
    }
    void on_insert_INVENTORY(INVENTORY_entry &e) {
      e.__av = 1;
      INVENTORY.addOrDelOnZero(e, 1);
    }
    
    void on_insert_LOCATION(const int locn, const int zip, const int rgn_cd, const int clim_zn_nbr, const int tot_area_sq_ft, const int sell_area_sq_ft, const int avghhi, const DOUBLE_TYPE supertargetdistance, const DOUBLE_TYPE supertargetdrivetime, const DOUBLE_TYPE targetdistance, const DOUBLE_TYPE targetdrivetime, const DOUBLE_TYPE walmartdistance, const DOUBLE_TYPE walmartdrivetime, const DOUBLE_TYPE walmartsupercenterdistance, const DOUBLE_TYPE walmartsupercenterdrivetime) {
      LOCATION_entry entry2(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime, 1);
      LOCATION.addOrDelOnZero(entry2, 1);
    }
    void on_insert_LOCATION(LOCATION_entry &e) {
      e.__av = 1;
      LOCATION.addOrDelOnZero(e, 1);
    }
    
    void on_insert_CENSUS(const int zip, const int population, const int white, const int asian, const int pacific, const int blackafrican, const DOUBLE_TYPE medianage, const int occupiedhouseunits, const int houseunits, const int families, const int households, const int husbwife, const int males, const int females, const int householdschildren, const int hispanic) {
      CENSUS_entry entry3(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic, 1);
      CENSUS.addOrDelOnZero(entry3, 1);
    }
    void on_insert_CENSUS(CENSUS_entry &e) {
      e.__av = 1;
      CENSUS.addOrDelOnZero(e, 1);
    }
    
    void on_insert_ITEM(const int ksn, const int8_t subcategory, const int8_t category, const int8_t categorycluster, const DOUBLE_TYPE prize) {
      ITEM_entry entry4(ksn, subcategory, category, categorycluster, prize, 1);
      ITEM.addOrDelOnZero(entry4, 1);
    }
    void on_insert_ITEM(ITEM_entry &e) {
      e.__av = 1;
      ITEM.addOrDelOnZero(e, 1);
    }
    
    void on_insert_WEATHER(const int locn, const int dateid, const int8_t rain, const int8_t snow, const int maxtemp, const int mintemp, const DOUBLE_TYPE meanwind, const int8_t thunder) {
      WEATHER_entry entry5(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder, 1);
      WEATHER.addOrDelOnZero(entry5, 1);
    }
    void on_insert_WEATHER(WEATHER_entry &e) {
      e.__av = 1;
      WEATHER.addOrDelOnZero(e, 1);
    }
    
    
    /* Trigger functions for stream relations */
    void on_system_ready_event() {
      V_subcategory_I1.clear();
      { //foreach
        ITEM_entry* e1 = ITEM.head;
        while (e1) {
          int ksn = e1->ksn;
          int8_t subcategory = e1->subcategory;
          int8_t category = e1->category;
          int8_t categorycluster = e1->categorycluster;
          DOUBLE_TYPE prize = e1->prize;
          long v1 = e1->__av;
          V_subcategory_I1.addOrDelOnZero(se1.modify(ksn), (v1 * Ulift<4>(subcategory, category, categorycluster, prize)));
          e1 = e1->nxt;
        }
      }
      
      V_ksn_II1.clear();
      { //foreach
        INVENTORY_entry* e2 = INVENTORY.head;
        while (e2) {
          int locn = e2->locn;
          int dateid = e2->dateid;
          int ksn = e2->ksn;
          int inventoryunits = e2->inventoryunits;
          long v2 = e2->__av;
          V_ksn_II1.addOrDelOnZero(se2.modify(locn, dateid), ((v2 * V_subcategory_I1.getValueOrDefault(se3.modify(ksn))) * Ulift<2>(ksn, inventoryunits)));
          e2 = e2->nxt;
        }
      }
      
      V_rain_W1.clear();
      { //foreach
        WEATHER_entry* e3 = WEATHER.head;
        while (e3) {
          int locn = e3->locn;
          int dateid = e3->dateid;
          int8_t rain = e3->rain;
          int8_t snow = e3->snow;
          int maxtemp = e3->maxtemp;
          int mintemp = e3->mintemp;
          DOUBLE_TYPE meanwind = e3->meanwind;
          int8_t thunder = e3->thunder;
          long v3 = e3->__av;
          V_rain_W1.addOrDelOnZero(se4.modify(locn, dateid), (v3 * Ulift<8>(rain, snow, maxtemp, mintemp, meanwind, thunder)));
          e3 = e3->nxt;
        }
      }
      
      V_dateid_IIW1.clear();
      { //foreach
        V_ksn_II1_entry* e4 = V_ksn_II1.head;
        while (e4) {
          int locn = e4->locn;
          int dateid = e4->dateid;
          RingFactorizedRelation<2, int, int>& v4 = e4->__av;
          V_dateid_IIW1.addOrDelOnZero(se5.modify(locn), ((v4 * V_rain_W1.getValueOrDefault(se6.modify(locn, dateid))) * Ulift<1>(dateid)));
          e4 = e4->nxt;
        }
      }
      
      V_rgn_cd_L1.clear();
      { //foreach
        LOCATION_entry* e5 = LOCATION.head;
        while (e5) {
          int locn = e5->locn;
          int zip = e5->zip;
          int rgn_cd = e5->rgn_cd;
          int clim_zn_nbr = e5->clim_zn_nbr;
          int tot_area_sq_ft = e5->tot_area_sq_ft;
          int sell_area_sq_ft = e5->sell_area_sq_ft;
          int avghhi = e5->avghhi;
          DOUBLE_TYPE supertargetdistance = e5->supertargetdistance;
          DOUBLE_TYPE supertargetdrivetime = e5->supertargetdrivetime;
          DOUBLE_TYPE targetdistance = e5->targetdistance;
          DOUBLE_TYPE targetdrivetime = e5->targetdrivetime;
          DOUBLE_TYPE walmartdistance = e5->walmartdistance;
          DOUBLE_TYPE walmartdrivetime = e5->walmartdrivetime;
          DOUBLE_TYPE walmartsupercenterdistance = e5->walmartsupercenterdistance;
          DOUBLE_TYPE walmartsupercenterdrivetime = e5->walmartsupercenterdrivetime;
          long v5 = e5->__av;
          V_rgn_cd_L1.addOrDelOnZero(se7.modify(locn, zip), (v5 * Ulift<15>(rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime)));
          e5 = e5->nxt;
        }
      }
      
      V_population_C1.clear();
      { //foreach
        CENSUS_entry* e6 = CENSUS.head;
        while (e6) {
          int zip = e6->zip;
          int population = e6->population;
          int white = e6->white;
          int asian = e6->asian;
          int pacific = e6->pacific;
          int blackafrican = e6->blackafrican;
          DOUBLE_TYPE medianage = e6->medianage;
          int occupiedhouseunits = e6->occupiedhouseunits;
          int houseunits = e6->houseunits;
          int families = e6->families;
          int households = e6->households;
          int husbwife = e6->husbwife;
          int males = e6->males;
          int females = e6->females;
          int householdschildren = e6->householdschildren;
          int hispanic = e6->hispanic;
          long v6 = e6->__av;
          V_population_C1.addOrDelOnZero(se8.modify(zip), (v6 * Ulift<28>(population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic)));
          e6 = e6->nxt;
        }
      }

    }
  
  private:
    
      /* Preallocated map entries (to avoid recreation of temporary objects) */
      V_subcategory_I1_entry se1;
      V_ksn_II1_entry se2;
      V_subcategory_I1_entry se3;
      V_rain_W1_entry se4;
      V_dateid_IIW1_entry se5;
      V_rain_W1_entry se6;
      V_rgn_cd_L1_entry se7;
      V_population_C1_entry se8;
      V_zip_LC1_entry se9;
      V_population_C1_entry se10;
      V_zip_LC1_entry se12;
    
      
    
      /* Data structures used for storing materialized views */
      INVENTORY_map INVENTORY;
      LOCATION_map LOCATION;
      CENSUS_map CENSUS;
      ITEM_map ITEM;
      WEATHER_map WEATHER;
    
      
    
  };

  

}