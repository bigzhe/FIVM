#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"



#define RELATION_INVENTORY_DYNAMIC
#define RELATION_LOCATION_DYNAMIC
#define RELATION_CENSUS_DYNAMIC
#define RELATION_ITEM_DYNAMIC
#define RELATION_WEATHER_DYNAMIC

namespace dbtoaster {

  /* Definitions of maps used for storing materialized views. */
  struct INVENTORY_entry {
    int locn; int dateid; int ksn; int inventoryunits; long __av; INVENTORY_entry* nxt; INVENTORY_entry* prv;
  
    explicit INVENTORY_entry() : nxt(nullptr), prv(nullptr) { }
    explicit INVENTORY_entry(const int c0, const int c1, const int c2, const int c3, const long c4) { locn = c0; dateid = c1; ksn = c2; inventoryunits = c3; __av = c4;  }
    INVENTORY_entry(const INVENTORY_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), inventoryunits(other.inventoryunits), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    INVENTORY_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); inventoryunits = std::stoi(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  
  struct LOCATION_entry {
    int locn; int zip; int rgn_cd; int clim_zn_nbr; int tot_area_sq_ft; int sell_area_sq_ft; int avghhi; DOUBLE_TYPE supertargetdistance; DOUBLE_TYPE supertargetdrivetime; DOUBLE_TYPE targetdistance; DOUBLE_TYPE targetdrivetime; DOUBLE_TYPE walmartdistance; DOUBLE_TYPE walmartdrivetime; DOUBLE_TYPE walmartsupercenterdistance; DOUBLE_TYPE walmartsupercenterdrivetime; long __av; LOCATION_entry* nxt; LOCATION_entry* prv;
  
    explicit LOCATION_entry() : nxt(nullptr), prv(nullptr) { }
    explicit LOCATION_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14, const long c15) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14; __av = c15;  }
    LOCATION_entry(const LOCATION_entry& other) : locn(other.locn), zip(other.zip), rgn_cd(other.rgn_cd), clim_zn_nbr(other.clim_zn_nbr), tot_area_sq_ft(other.tot_area_sq_ft), sell_area_sq_ft(other.sell_area_sq_ft), avghhi(other.avghhi), supertargetdistance(other.supertargetdistance), supertargetdrivetime(other.supertargetdrivetime), targetdistance(other.targetdistance), targetdrivetime(other.targetdrivetime), walmartdistance(other.walmartdistance), walmartdrivetime(other.walmartdrivetime), walmartsupercenterdistance(other.walmartsupercenterdistance), walmartsupercenterdrivetime(other.walmartsupercenterdrivetime), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    LOCATION_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 15) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); rgn_cd = std::stoi(f[2]); clim_zn_nbr = std::stoi(f[3]); tot_area_sq_ft = std::stoi(f[4]); sell_area_sq_ft = std::stoi(f[5]); avghhi = std::stoi(f[6]); supertargetdistance = std::stod(f[7]); supertargetdrivetime = std::stod(f[8]); targetdistance = std::stod(f[9]); targetdrivetime = std::stod(f[10]); walmartdistance = std::stod(f[11]); walmartdrivetime = std::stod(f[12]); walmartsupercenterdistance = std::stod(f[13]); walmartsupercenterdrivetime = std::stod(f[14]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  
  struct CENSUS_entry {
    int zip; int population; int white; int asian; int pacific; int blackafrican; DOUBLE_TYPE medianage; int occupiedhouseunits; int houseunits; int families; int households; int husbwife; int males; int females; int householdschildren; int hispanic; long __av; CENSUS_entry* nxt; CENSUS_entry* prv;
  
    explicit CENSUS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit CENSUS_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15, const long c16) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15; __av = c16;  }
    CENSUS_entry(const CENSUS_entry& other) : zip(other.zip), population(other.population), white(other.white), asian(other.asian), pacific(other.pacific), blackafrican(other.blackafrican), medianage(other.medianage), occupiedhouseunits(other.occupiedhouseunits), houseunits(other.houseunits), families(other.families), households(other.households), husbwife(other.husbwife), males(other.males), females(other.females), householdschildren(other.householdschildren), hispanic(other.hispanic), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    CENSUS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 16) return; */
        zip = std::stoi(f[0]); population = std::stoi(f[1]); white = std::stoi(f[2]); asian = std::stoi(f[3]); pacific = std::stoi(f[4]); blackafrican = std::stoi(f[5]); medianage = std::stod(f[6]); occupiedhouseunits = std::stoi(f[7]); houseunits = std::stoi(f[8]); families = std::stoi(f[9]); households = std::stoi(f[10]); husbwife = std::stoi(f[11]); males = std::stoi(f[12]); females = std::stoi(f[13]); householdschildren = std::stoi(f[14]); hispanic = std::stoi(f[15]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  
  struct ITEM_entry {
    int ksn; int8_t subcategory; int8_t category; int8_t categorycluster; DOUBLE_TYPE prize; long __av; ITEM_entry* nxt; ITEM_entry* prv;
  
    explicit ITEM_entry() : nxt(nullptr), prv(nullptr) { }
    explicit ITEM_entry(const int c0, const int8_t c1, const int8_t c2, const int8_t c3, const DOUBLE_TYPE c4, const long c5) { ksn = c0; subcategory = c1; category = c2; categorycluster = c3; prize = c4; __av = c5;  }
    ITEM_entry(const ITEM_entry& other) : ksn(other.ksn), subcategory(other.subcategory), category(other.category), categorycluster(other.categorycluster), prize(other.prize), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    ITEM_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        ksn = std::stoi(f[0]); subcategory = (int8_t) std::stoi(f[1]); category = (int8_t) std::stoi(f[2]); categorycluster = (int8_t) std::stoi(f[3]); prize = std::stod(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  
  struct WEATHER_entry {
    int locn; int dateid; int8_t rain; int8_t snow; int maxtemp; int mintemp; DOUBLE_TYPE meanwind; int8_t thunder; long __av; WEATHER_entry* nxt; WEATHER_entry* prv;
  
    explicit WEATHER_entry() : nxt(nullptr), prv(nullptr) { }
    explicit WEATHER_entry(const int c0, const int c1, const int8_t c2, const int8_t c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int8_t c7, const long c8) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7; __av = c8;  }
    WEATHER_entry(const WEATHER_entry& other) : locn(other.locn), dateid(other.dateid), rain(other.rain), snow(other.snow), maxtemp(other.maxtemp), mintemp(other.mintemp), meanwind(other.meanwind), thunder(other.thunder), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    WEATHER_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 8) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); rain = (int8_t) std::stoi(f[2]); snow = (int8_t) std::stoi(f[3]); maxtemp = std::stoi(f[4]); mintemp = std::stoi(f[5]); meanwind = std::stod(f[6]); thunder = (int8_t) std::stoi(f[7]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  struct V_locn_IIWLC1_entry {
    int locn; long __av; V_locn_IIWLC1_entry* nxt; V_locn_IIWLC1_entry* prv;
  
    explicit V_locn_IIWLC1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_locn_IIWLC1_entry(const int c0, const long c1) { locn = c0; __av = c1;  }
    V_locn_IIWLC1_entry(const V_locn_IIWLC1_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_locn_IIWLC1_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_locn_IIWLC1_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_locn_IIWLC1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_locn_IIWLC1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_locn_IIWLC1_entry& x, const V_locn_IIWLC1_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<V_locn_IIWLC1_entry, long, 
    PrimaryHashIndex<V_locn_IIWLC1_entry, V_locn_IIWLC1_mapkey0_idxfn>
  > V_locn_IIWLC1_map;
  
  
  struct V_dateid_IIW2_entry {
    int locn; long __av; V_dateid_IIW2_entry* nxt; V_dateid_IIW2_entry* prv;
  
    explicit V_dateid_IIW2_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_dateid_IIW2_entry(const int c0, const long c1) { locn = c0; __av = c1;  }
    V_dateid_IIW2_entry(const V_dateid_IIW2_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_dateid_IIW2_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_dateid_IIW2_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_dateid_IIW2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_dateid_IIW2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_dateid_IIW2_entry& x, const V_dateid_IIW2_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<V_dateid_IIW2_entry, long, 
    PrimaryHashIndex<V_dateid_IIW2_entry, V_dateid_IIW2_mapkey0_idxfn>
  > V_dateid_IIW2_map;
  
  
  struct V_dateid_IIW1_entry {
    int locn; int dateid; long __av; V_dateid_IIW1_entry* nxt; V_dateid_IIW1_entry* prv;
  
    explicit V_dateid_IIW1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_dateid_IIW1_entry(const int c0, const int c1, const long c2) { locn = c0; dateid = c1; __av = c2;  }
    V_dateid_IIW1_entry(const V_dateid_IIW1_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_dateid_IIW1_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_dateid_IIW1_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
    FORCE_INLINE V_dateid_IIW1_entry& modify0(const int c0) { locn = c0;  return *this; }

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
  
  struct V_dateid_IIW1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_dateid_IIW1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_dateid_IIW1_entry& x, const V_dateid_IIW1_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
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
  
  typedef MultiHashMap<V_dateid_IIW1_entry, long, 
    PrimaryHashIndex<V_dateid_IIW1_entry, V_dateid_IIW1_mapkey01_idxfn>,
    SecondaryHashIndex<V_dateid_IIW1_entry, V_dateid_IIW1_mapkey0_idxfn>
  > V_dateid_IIW1_map;
  
  
  struct V_ksn_II2_entry {
    int locn; int dateid; long __av; V_ksn_II2_entry* nxt; V_ksn_II2_entry* prv;
  
    explicit V_ksn_II2_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_ksn_II2_entry(const int c0, const int c1, const long c2) { locn = c0; dateid = c1; __av = c2;  }
    V_ksn_II2_entry(const V_ksn_II2_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_ksn_II2_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_ksn_II2_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
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
  
  struct V_ksn_II2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_ksn_II2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_ksn_II2_entry& x, const V_ksn_II2_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<V_ksn_II2_entry, long, 
    PrimaryHashIndex<V_ksn_II2_entry, V_ksn_II2_mapkey01_idxfn>
  > V_ksn_II2_map;
  
  
  struct V_ksn_II1_entry {
    int locn; int dateid; int ksn; long __av; V_ksn_II1_entry* nxt; V_ksn_II1_entry* prv;
  
    explicit V_ksn_II1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_ksn_II1_entry(const int c0, const int c1, const int c2, const long c3) { locn = c0; dateid = c1; ksn = c2; __av = c3;  }
    V_ksn_II1_entry(const V_ksn_II1_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_ksn_II1_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_ksn_II1_entry& modify(const int c0, const int c1, const int c2) { locn = c0; dateid = c1; ksn = c2;  return *this; }
    FORCE_INLINE V_ksn_II1_entry& modify01(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct V_ksn_II1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const V_ksn_II1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_ksn_II1_entry& x, const V_ksn_II1_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn;
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
  
  typedef MultiHashMap<V_ksn_II1_entry, long, 
    PrimaryHashIndex<V_ksn_II1_entry, V_ksn_II1_mapkey012_idxfn>,
    SecondaryHashIndex<V_ksn_II1_entry, V_ksn_II1_mapkey01_idxfn>
  > V_ksn_II1_map;
  
  
  struct V_inventoryunits_I1_entry {
    int locn; int dateid; int ksn; long __av; V_inventoryunits_I1_entry* nxt; V_inventoryunits_I1_entry* prv;
  
    explicit V_inventoryunits_I1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_inventoryunits_I1_entry(const int c0, const int c1, const int c2, const long c3) { locn = c0; dateid = c1; ksn = c2; __av = c3;  }
    V_inventoryunits_I1_entry(const V_inventoryunits_I1_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_inventoryunits_I1_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_inventoryunits_I1_entry& modify(const int c0, const int c1, const int c2) { locn = c0; dateid = c1; ksn = c2;  return *this; }
    FORCE_INLINE V_inventoryunits_I1_entry& modify2(const int c2) { ksn = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_inventoryunits_I1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const V_inventoryunits_I1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_inventoryunits_I1_entry& x, const V_inventoryunits_I1_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn;
    }
  };
  
  struct V_inventoryunits_I1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const V_inventoryunits_I1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_inventoryunits_I1_entry& x, const V_inventoryunits_I1_entry& y) {
      return x.ksn == y.ksn;
    }
  };
  
  typedef MultiHashMap<V_inventoryunits_I1_entry, long, 
    PrimaryHashIndex<V_inventoryunits_I1_entry, V_inventoryunits_I1_mapkey012_idxfn>,
    SecondaryHashIndex<V_inventoryunits_I1_entry, V_inventoryunits_I1_mapkey2_idxfn>
  > V_inventoryunits_I1_map;
  
  
  struct V_subcategory_I1_entry {
    int ksn; long __av; V_subcategory_I1_entry* nxt; V_subcategory_I1_entry* prv;
  
    explicit V_subcategory_I1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_subcategory_I1_entry(const int c0, const long c1) { ksn = c0; __av = c1;  }
    V_subcategory_I1_entry(const V_subcategory_I1_entry& other) : ksn(other.ksn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_subcategory_I1_entry(const std::vector<std::string>& f, const long v) {
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
  
  typedef MultiHashMap<V_subcategory_I1_entry, long, 
    PrimaryHashIndex<V_subcategory_I1_entry, V_subcategory_I1_mapkey0_idxfn>
  > V_subcategory_I1_map;
  
  
  struct V_rain_W1_entry {
    int locn; int dateid; long __av; V_rain_W1_entry* nxt; V_rain_W1_entry* prv;
  
    explicit V_rain_W1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_rain_W1_entry(const int c0, const int c1, const long c2) { locn = c0; dateid = c1; __av = c2;  }
    V_rain_W1_entry(const V_rain_W1_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_rain_W1_entry(const std::vector<std::string>& f, const long v) {
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
  
  typedef MultiHashMap<V_rain_W1_entry, long, 
    PrimaryHashIndex<V_rain_W1_entry, V_rain_W1_mapkey01_idxfn>
  > V_rain_W1_map;
  
  
  struct V_zip_LC2_entry {
    int locn; long __av; V_zip_LC2_entry* nxt; V_zip_LC2_entry* prv;
  
    explicit V_zip_LC2_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_zip_LC2_entry(const int c0, const long c1) { locn = c0; __av = c1;  }
    V_zip_LC2_entry(const V_zip_LC2_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_zip_LC2_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_zip_LC2_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_zip_LC2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_zip_LC2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_zip_LC2_entry& x, const V_zip_LC2_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<V_zip_LC2_entry, long, 
    PrimaryHashIndex<V_zip_LC2_entry, V_zip_LC2_mapkey0_idxfn>
  > V_zip_LC2_map;
  
  
  struct V_zip_LC1_entry {
    int locn; int zip; long __av; V_zip_LC1_entry* nxt; V_zip_LC1_entry* prv;
  
    explicit V_zip_LC1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_zip_LC1_entry(const int c0, const int c1, const long c2) { locn = c0; zip = c1; __av = c2;  }
    V_zip_LC1_entry(const V_zip_LC1_entry& other) : locn(other.locn), zip(other.zip), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_zip_LC1_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_zip_LC1_entry& modify(const int c0, const int c1) { locn = c0; zip = c1;  return *this; }
    FORCE_INLINE V_zip_LC1_entry& modify0(const int c0) { locn = c0; return *this; }
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
  
  struct V_zip_LC1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_zip_LC1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.zip);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_zip_LC1_entry& x, const V_zip_LC1_entry& y) {
      return x.locn == y.locn && x.zip == y.zip;
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

  typedef MultiHashMap<V_zip_LC1_entry, long, 
    PrimaryHashIndex<V_zip_LC1_entry, V_zip_LC1_mapkey01_idxfn>,
    SecondaryHashIndex<V_zip_LC1_entry, V_zip_LC1_mapkey0_idxfn>
  > V_zip_LC1_map;
  
  
  struct V_rgn_cd_L1_entry {
    int locn; int zip; long __av; V_rgn_cd_L1_entry* nxt; V_rgn_cd_L1_entry* prv;
  
    explicit V_rgn_cd_L1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_rgn_cd_L1_entry(const int c0, const int c1, const long c2) { locn = c0; zip = c1; __av = c2;  }
    V_rgn_cd_L1_entry(const V_rgn_cd_L1_entry& other) : locn(other.locn), zip(other.zip), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_rgn_cd_L1_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_rgn_cd_L1_entry& modify(const int c0, const int c1) { locn = c0; zip = c1;  return *this; }
    FORCE_INLINE V_rgn_cd_L1_entry& modify1(const int c1) { zip = c1;  return *this; }
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
  
  struct V_rgn_cd_L1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const V_rgn_cd_L1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.zip);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_rgn_cd_L1_entry& x, const V_rgn_cd_L1_entry& y) {
      return x.zip == y.zip;
    }
  };
  
  typedef MultiHashMap<V_rgn_cd_L1_entry, long, 
    PrimaryHashIndex<V_rgn_cd_L1_entry, V_rgn_cd_L1_mapkey01_idxfn>,
    SecondaryHashIndex<V_rgn_cd_L1_entry, V_rgn_cd_L1_mapkey1_idxfn>
  > V_rgn_cd_L1_map;
  
  
  struct V_population_C1_entry {
    int zip; long __av; V_population_C1_entry* nxt; V_population_C1_entry* prv;
  
    explicit V_population_C1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_population_C1_entry(const int c0, const long c1) { zip = c0; __av = c1;  }
    V_population_C1_entry(const V_population_C1_entry& other) : zip(other.zip), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_population_C1_entry(const std::vector<std::string>& f, const long v) {
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
  
  typedef MultiHashMap<V_population_C1_entry, long, 
    PrimaryHashIndex<V_population_C1_entry, V_population_C1_mapkey0_idxfn>
  > V_population_C1_map;
  
  
  struct TMP_SUM1_entry {
    int locn; int dateid; int ksn; long __av; TMP_SUM1_entry* nxt; TMP_SUM1_entry* prv;
  
    explicit TMP_SUM1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM1_entry(const int c0, const int c1, const int c2, const long c3) { locn = c0; dateid = c1; ksn = c2; __av = c3;  }
    TMP_SUM1_entry(const TMP_SUM1_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM1_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM1_entry& modify(const int c0, const int c1, const int c2) { locn = c0; dateid = c1; ksn = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM1_entry& x, const TMP_SUM1_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn;
    }
  };
  
  typedef MultiHashMap<TMP_SUM1_entry, long, 
    PrimaryHashIndex<TMP_SUM1_entry, TMP_SUM1_mapkey012_idxfn>
  > TMP_SUM1_map;
  
  
  struct TMP_SUM2_entry {
    int locn; int dateid; int ksn; long __av; TMP_SUM2_entry* nxt; TMP_SUM2_entry* prv;
  
    explicit TMP_SUM2_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM2_entry(const int c0, const int c1, const int c2, const long c3) { locn = c0; dateid = c1; ksn = c2; __av = c3;  }
    TMP_SUM2_entry(const TMP_SUM2_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM2_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM2_entry& modify(const int c0, const int c1, const int c2) { locn = c0; dateid = c1; ksn = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM2_entry& x, const TMP_SUM2_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn;
    }
  };
  
  typedef MultiHashMap<TMP_SUM2_entry, long, 
    PrimaryHashIndex<TMP_SUM2_entry, TMP_SUM2_mapkey012_idxfn>
  > TMP_SUM2_map;
  
  
  struct TMP_SUM2_PRIME_entry {
    int locn; int dateid; long __av; TMP_SUM2_PRIME_entry* nxt; TMP_SUM2_PRIME_entry* prv;
  
    explicit TMP_SUM2_PRIME_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM2_PRIME_entry(const int c0, const int c1, const long c2) { locn = c0; dateid = c1; __av = c2;  }
    TMP_SUM2_PRIME_entry(const TMP_SUM2_PRIME_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM2_PRIME_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM2_PRIME_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
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
  
  struct TMP_SUM2_PRIME_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM2_PRIME_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM2_PRIME_entry& x, const TMP_SUM2_PRIME_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<TMP_SUM2_PRIME_entry, long, 
    PrimaryHashIndex<TMP_SUM2_PRIME_entry, TMP_SUM2_PRIME_mapkey01_idxfn>
  > TMP_SUM2_PRIME_map;
  
  
  struct TMP_SUM3_entry {
    int locn; int dateid; long __av; TMP_SUM3_entry* nxt; TMP_SUM3_entry* prv;
  
    explicit TMP_SUM3_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM3_entry(const int c0, const int c1, const long c2) { locn = c0; dateid = c1; __av = c2;  }
    TMP_SUM3_entry(const TMP_SUM3_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM3_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM3_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
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
  
  struct TMP_SUM3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM3_entry& x, const TMP_SUM3_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<TMP_SUM3_entry, long, 
    PrimaryHashIndex<TMP_SUM3_entry, TMP_SUM3_mapkey01_idxfn>
  > TMP_SUM3_map;
  
  
  struct TMP_SUM3_PRIME_entry {
    int locn; long __av; TMP_SUM3_PRIME_entry* nxt; TMP_SUM3_PRIME_entry* prv;
  
    explicit TMP_SUM3_PRIME_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM3_PRIME_entry(const int c0, const long c1) { locn = c0; __av = c1;  }
    TMP_SUM3_PRIME_entry(const TMP_SUM3_PRIME_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM3_PRIME_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM3_PRIME_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM3_PRIME_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM3_PRIME_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM3_PRIME_entry& x, const TMP_SUM3_PRIME_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<TMP_SUM3_PRIME_entry, long, 
    PrimaryHashIndex<TMP_SUM3_PRIME_entry, TMP_SUM3_PRIME_mapkey0_idxfn>
  > TMP_SUM3_PRIME_map;
  
  
  struct TMP_SUM4_entry {
    int locn; int zip; long __av; TMP_SUM4_entry* nxt; TMP_SUM4_entry* prv;
  
    explicit TMP_SUM4_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM4_entry(const int c0, const int c1, const long c2) { locn = c0; zip = c1; __av = c2;  }
    TMP_SUM4_entry(const TMP_SUM4_entry& other) : locn(other.locn), zip(other.zip), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM4_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM4_entry& modify(const int c0, const int c1) { locn = c0; zip = c1;  return *this; }
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
  
  struct TMP_SUM4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.zip);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM4_entry& x, const TMP_SUM4_entry& y) {
      return x.locn == y.locn && x.zip == y.zip;
    }
  };
  
  typedef MultiHashMap<TMP_SUM4_entry, long, 
    PrimaryHashIndex<TMP_SUM4_entry, TMP_SUM4_mapkey01_idxfn>
  > TMP_SUM4_map;
  
  
  struct TMP_SUM5_entry {
    int locn; int zip; long __av; TMP_SUM5_entry* nxt; TMP_SUM5_entry* prv;
  
    explicit TMP_SUM5_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM5_entry(const int c0, const int c1, const long c2) { locn = c0; zip = c1; __av = c2;  }
    TMP_SUM5_entry(const TMP_SUM5_entry& other) : locn(other.locn), zip(other.zip), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM5_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM5_entry& modify(const int c0, const int c1) { locn = c0; zip = c1;  return *this; }
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
  
  struct TMP_SUM5_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.zip);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM5_entry& x, const TMP_SUM5_entry& y) {
      return x.locn == y.locn && x.zip == y.zip;
    }
  };
  
  typedef MultiHashMap<TMP_SUM5_entry, long, 
    PrimaryHashIndex<TMP_SUM5_entry, TMP_SUM5_mapkey01_idxfn>
  > TMP_SUM5_map;
  
  
  struct TMP_SUM5_PRIME_entry {
    int locn; long __av; TMP_SUM5_PRIME_entry* nxt; TMP_SUM5_PRIME_entry* prv;
  
    explicit TMP_SUM5_PRIME_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM5_PRIME_entry(const int c0, const long c1) { locn = c0; __av = c1;  }
    TMP_SUM5_PRIME_entry(const TMP_SUM5_PRIME_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM5_PRIME_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM5_PRIME_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM5_PRIME_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM5_PRIME_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM5_PRIME_entry& x, const TMP_SUM5_PRIME_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<TMP_SUM5_PRIME_entry, long, 
    PrimaryHashIndex<TMP_SUM5_PRIME_entry, TMP_SUM5_PRIME_mapkey0_idxfn>
  > TMP_SUM5_PRIME_map;
  
  
  struct TMP_SUM6_entry {
    int zip; long __av; TMP_SUM6_entry* nxt; TMP_SUM6_entry* prv;
  
    explicit TMP_SUM6_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM6_entry(const int c0, const long c1) { zip = c0; __av = c1;  }
    TMP_SUM6_entry(const TMP_SUM6_entry& other) : zip(other.zip), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM6_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 1) return; */
        zip = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM6_entry& modify(const int c0) { zip = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, zip);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.zip);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM6_entry& x, const TMP_SUM6_entry& y) {
      return x.zip == y.zip;
    }
  };
  
  typedef MultiHashMap<TMP_SUM6_entry, long, 
    PrimaryHashIndex<TMP_SUM6_entry, TMP_SUM6_mapkey0_idxfn>
  > TMP_SUM6_map;
  
  
  struct TMP_SUM7_entry {
    int locn; int zip; long __av; TMP_SUM7_entry* nxt; TMP_SUM7_entry* prv;
  
    explicit TMP_SUM7_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM7_entry(const int c0, const int c1, const long c2) { locn = c0; zip = c1; __av = c2;  }
    TMP_SUM7_entry(const TMP_SUM7_entry& other) : locn(other.locn), zip(other.zip), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM7_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM7_entry& modify(const int c0, const int c1) { locn = c0; zip = c1;  return *this; }
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
  
  struct TMP_SUM7_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.zip);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM7_entry& x, const TMP_SUM7_entry& y) {
      return x.locn == y.locn && x.zip == y.zip;
    }
  };
  
  typedef MultiHashMap<TMP_SUM7_entry, long, 
    PrimaryHashIndex<TMP_SUM7_entry, TMP_SUM7_mapkey01_idxfn>
  > TMP_SUM7_map;
  
  
  struct TMP_SUM7_PRIME_entry {
    int locn; long __av; TMP_SUM7_PRIME_entry* nxt; TMP_SUM7_PRIME_entry* prv;
  
    explicit TMP_SUM7_PRIME_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM7_PRIME_entry(const int c0, const long c1) { locn = c0; __av = c1;  }
    TMP_SUM7_PRIME_entry(const TMP_SUM7_PRIME_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM7_PRIME_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM7_PRIME_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM7_PRIME_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM7_PRIME_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM7_PRIME_entry& x, const TMP_SUM7_PRIME_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<TMP_SUM7_PRIME_entry, long, 
    PrimaryHashIndex<TMP_SUM7_PRIME_entry, TMP_SUM7_PRIME_mapkey0_idxfn>
  > TMP_SUM7_PRIME_map;
  
  
  struct TMP_SUM8_entry {
    int ksn; long __av; TMP_SUM8_entry* nxt; TMP_SUM8_entry* prv;
  
    explicit TMP_SUM8_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM8_entry(const int c0, const long c1) { ksn = c0; __av = c1;  }
    TMP_SUM8_entry(const TMP_SUM8_entry& other) : ksn(other.ksn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM8_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 1) return; */
        ksn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM8_entry& modify(const int c0) { ksn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM8_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM8_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM8_entry& x, const TMP_SUM8_entry& y) {
      return x.ksn == y.ksn;
    }
  };
  
  typedef MultiHashMap<TMP_SUM8_entry, long, 
    PrimaryHashIndex<TMP_SUM8_entry, TMP_SUM8_mapkey0_idxfn>
  > TMP_SUM8_map;
  
  
  struct TMP_SUM9_entry {
    int locn; int dateid; int ksn; long __av; TMP_SUM9_entry* nxt; TMP_SUM9_entry* prv;
  
    explicit TMP_SUM9_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM9_entry(const int c0, const int c1, const int c2, const long c3) { locn = c0; dateid = c1; ksn = c2; __av = c3;  }
    TMP_SUM9_entry(const TMP_SUM9_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM9_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM9_entry& modify(const int c0, const int c1, const int c2) { locn = c0; dateid = c1; ksn = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, dateid);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM9_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM9_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM9_entry& x, const TMP_SUM9_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn;
    }
  };
  
  typedef MultiHashMap<TMP_SUM9_entry, long, 
    PrimaryHashIndex<TMP_SUM9_entry, TMP_SUM9_mapkey012_idxfn>
  > TMP_SUM9_map;
  
  
  struct TMP_SUM9_PRIME_entry {
    int locn; int dateid; long __av; TMP_SUM9_PRIME_entry* nxt; TMP_SUM9_PRIME_entry* prv;
  
    explicit TMP_SUM9_PRIME_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM9_PRIME_entry(const int c0, const int c1, const long c2) { locn = c0; dateid = c1; __av = c2;  }
    TMP_SUM9_PRIME_entry(const TMP_SUM9_PRIME_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM9_PRIME_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM9_PRIME_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
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
  
  struct TMP_SUM9_PRIME_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM9_PRIME_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM9_PRIME_entry& x, const TMP_SUM9_PRIME_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<TMP_SUM9_PRIME_entry, long, 
    PrimaryHashIndex<TMP_SUM9_PRIME_entry, TMP_SUM9_PRIME_mapkey01_idxfn>
  > TMP_SUM9_PRIME_map;
  
  
  struct TMP_SUM10_entry {
    int locn; int dateid; long __av; TMP_SUM10_entry* nxt; TMP_SUM10_entry* prv;
  
    explicit TMP_SUM10_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM10_entry(const int c0, const int c1, const long c2) { locn = c0; dateid = c1; __av = c2;  }
    TMP_SUM10_entry(const TMP_SUM10_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM10_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM10_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
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
  
  struct TMP_SUM10_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM10_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM10_entry& x, const TMP_SUM10_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<TMP_SUM10_entry, long, 
    PrimaryHashIndex<TMP_SUM10_entry, TMP_SUM10_mapkey01_idxfn>
  > TMP_SUM10_map;
  
  
  struct TMP_SUM10_PRIME_entry {
    int locn; long __av; TMP_SUM10_PRIME_entry* nxt; TMP_SUM10_PRIME_entry* prv;
  
    explicit TMP_SUM10_PRIME_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM10_PRIME_entry(const int c0, const long c1) { locn = c0; __av = c1;  }
    TMP_SUM10_PRIME_entry(const TMP_SUM10_PRIME_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM10_PRIME_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM10_PRIME_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM10_PRIME_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM10_PRIME_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM10_PRIME_entry& x, const TMP_SUM10_PRIME_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<TMP_SUM10_PRIME_entry, long, 
    PrimaryHashIndex<TMP_SUM10_PRIME_entry, TMP_SUM10_PRIME_mapkey0_idxfn>
  > TMP_SUM10_PRIME_map;
  
  
  struct TMP_SUM11_entry {
    int locn; int dateid; long __av; TMP_SUM11_entry* nxt; TMP_SUM11_entry* prv;
  
    explicit TMP_SUM11_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM11_entry(const int c0, const int c1, const long c2) { locn = c0; dateid = c1; __av = c2;  }
    TMP_SUM11_entry(const TMP_SUM11_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM11_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM11_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
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
  
  struct TMP_SUM11_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM11_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM11_entry& x, const TMP_SUM11_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<TMP_SUM11_entry, long, 
    PrimaryHashIndex<TMP_SUM11_entry, TMP_SUM11_mapkey01_idxfn>
  > TMP_SUM11_map;
  
  
  struct TMP_SUM12_entry {
    int locn; int dateid; long __av; TMP_SUM12_entry* nxt; TMP_SUM12_entry* prv;
  
    explicit TMP_SUM12_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM12_entry(const int c0, const int c1, const long c2) { locn = c0; dateid = c1; __av = c2;  }
    TMP_SUM12_entry(const TMP_SUM12_entry& other) : locn(other.locn), dateid(other.dateid), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM12_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM12_entry& modify(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
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
  
  struct TMP_SUM12_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM12_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM12_entry& x, const TMP_SUM12_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid;
    }
  };
  
  typedef MultiHashMap<TMP_SUM12_entry, long, 
    PrimaryHashIndex<TMP_SUM12_entry, TMP_SUM12_mapkey01_idxfn>
  > TMP_SUM12_map;
  
  
  struct TMP_SUM12_PRIME_entry {
    int locn; long __av; TMP_SUM12_PRIME_entry* nxt; TMP_SUM12_PRIME_entry* prv;
  
    explicit TMP_SUM12_PRIME_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM12_PRIME_entry(const int c0, const long c1) { locn = c0; __av = c1;  }
    TMP_SUM12_PRIME_entry(const TMP_SUM12_PRIME_entry& other) : locn(other.locn), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM12_PRIME_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 1) return; */
        locn = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM12_PRIME_entry& modify(const int c0) { locn = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM12_PRIME_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM12_PRIME_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM12_PRIME_entry& x, const TMP_SUM12_PRIME_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<TMP_SUM12_PRIME_entry, long, 
    PrimaryHashIndex<TMP_SUM12_PRIME_entry, TMP_SUM12_PRIME_mapkey0_idxfn>
  > TMP_SUM12_PRIME_map;
  
  
  struct V_INVENTORY_entry {
    int locn; int dateid; int ksn; int inventoryunits; long __av; V_INVENTORY_entry* nxt; V_INVENTORY_entry* prv;
  
    explicit V_INVENTORY_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_INVENTORY_entry(const int c0, const int c1, const int c2, const int c3, const long c4) { locn = c0; dateid = c1; ksn = c2; inventoryunits = c3; __av = c4;  }
    V_INVENTORY_entry(const V_INVENTORY_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), inventoryunits(other.inventoryunits), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_INVENTORY_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); inventoryunits = std::stoi(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_INVENTORY_entry& modify(const int c0, const int c1, const int c2, const int c3) { locn = c0; dateid = c1; ksn = c2; inventoryunits = c3;  return *this; }
    FORCE_INLINE V_INVENTORY_entry& modify012(const int c0, const int c1, const int c2) { locn = c0; dateid = c1; ksn = c2;  return *this; }

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
  
  struct V_INVENTORY_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const V_INVENTORY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      hash_combine(h, e.inventoryunits);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_INVENTORY_entry& x, const V_INVENTORY_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn && x.inventoryunits == y.inventoryunits;
    }
  };

  struct V_INVENTORY_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const V_INVENTORY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_INVENTORY_entry& x, const V_INVENTORY_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn; 
    }
  };
  
  typedef MultiHashMap<V_INVENTORY_entry, long, 
    PrimaryHashIndex<V_INVENTORY_entry, V_INVENTORY_mapkey0123_idxfn>,
    SecondaryHashIndex<V_INVENTORY_entry, V_INVENTORY_mapkey012_idxfn> 
  > V_INVENTORY_map;
  
  
  struct V_ITEM_entry {
    int ksn; int subcategory; int category; int categoryCluster; int prize; long __av; V_ITEM_entry* nxt; V_ITEM_entry* prv;
  
    explicit V_ITEM_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_ITEM_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const long c5) { ksn = c0; subcategory = c1; category = c2; categoryCluster = c3; prize = c4; __av = c5;  }
    V_ITEM_entry(const V_ITEM_entry& other) : ksn(other.ksn), subcategory(other.subcategory), category(other.category), categoryCluster(other.categoryCluster), prize(other.prize), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_ITEM_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        ksn = std::stoi(f[0]); subcategory = std::stoi(f[1]); category = std::stoi(f[2]); categoryCluster = std::stoi(f[3]); prize = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_ITEM_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4) { ksn = c0; subcategory = c1; category = c2; categoryCluster = c3; prize = c4;  return *this; }
    FORCE_INLINE V_ITEM_entry& modify0(const int c0) { ksn = c0; return *this; }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ksn);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, subcategory);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, category);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, categoryCluster);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, prize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_ITEM_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const V_ITEM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      hash_combine(h, e.subcategory);
      hash_combine(h, e.category);
      hash_combine(h, e.categoryCluster);
      hash_combine(h, e.prize);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_ITEM_entry& x, const V_ITEM_entry& y) {
      return x.ksn == y.ksn && x.subcategory == y.subcategory && x.category == y.category && x.categoryCluster == y.categoryCluster && x.prize == y.prize;
    }
  };
  struct V_ITEM_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_ITEM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_ITEM_entry& x, const V_ITEM_entry& y) {
      return x.ksn == y.ksn; 
    }
  };
  
  typedef MultiHashMap<V_ITEM_entry, long, 
    PrimaryHashIndex<V_ITEM_entry, V_ITEM_mapkey01234_idxfn>,
    SecondaryHashIndex<V_ITEM_entry, V_ITEM_mapkey0_idxfn>
  > V_ITEM_map;
  
  
  struct V_LOCATION_entry {
    int locn; int zip; int rgn_cd; int clim_zn_nbr; int tot_area_sq_ft; int sell_area_sq_ft; int avghhi; int supertargetdistance; int supertargetdrivetime; int targetdistance; int targetdrivetime; int walmartdistance; int walmartdrivetime; int walmartsupercenterdistance; int walmartsupercenterdrivetime; long __av; V_LOCATION_entry* nxt; V_LOCATION_entry* prv;
  
    explicit V_LOCATION_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_LOCATION_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14, const long c15) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14; __av = c15;  }
    V_LOCATION_entry(const V_LOCATION_entry& other) : locn(other.locn), zip(other.zip), rgn_cd(other.rgn_cd), clim_zn_nbr(other.clim_zn_nbr), tot_area_sq_ft(other.tot_area_sq_ft), sell_area_sq_ft(other.sell_area_sq_ft), avghhi(other.avghhi), supertargetdistance(other.supertargetdistance), supertargetdrivetime(other.supertargetdrivetime), targetdistance(other.targetdistance), targetdrivetime(other.targetdrivetime), walmartdistance(other.walmartdistance), walmartdrivetime(other.walmartdrivetime), walmartsupercenterdistance(other.walmartsupercenterdistance), walmartsupercenterdrivetime(other.walmartsupercenterdrivetime), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_LOCATION_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 15) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); rgn_cd = std::stoi(f[2]); clim_zn_nbr = std::stoi(f[3]); tot_area_sq_ft = std::stoi(f[4]); sell_area_sq_ft = std::stoi(f[5]); avghhi = std::stoi(f[6]); supertargetdistance = std::stoi(f[7]); supertargetdrivetime = std::stoi(f[8]); targetdistance = std::stoi(f[9]); targetdrivetime = std::stoi(f[10]); walmartdistance = std::stoi(f[11]); walmartdrivetime = std::stoi(f[12]); walmartsupercenterdistance = std::stoi(f[13]); walmartsupercenterdrivetime = std::stoi(f[14]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_LOCATION_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14;  return *this; }
    FORCE_INLINE V_LOCATION_entry& modify01(const int c0, const int c1) { locn = c0; zip = c1; return *this; }
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
  
  struct V_LOCATION_mapkey01234567891011121314_idxfn {
    FORCE_INLINE static size_t hash(const V_LOCATION_entry& e) {
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
    
    FORCE_INLINE static bool equals(const V_LOCATION_entry& x, const V_LOCATION_entry& y) {
      return x.locn == y.locn && x.zip == y.zip && x.rgn_cd == y.rgn_cd && x.clim_zn_nbr == y.clim_zn_nbr && x.tot_area_sq_ft == y.tot_area_sq_ft && x.sell_area_sq_ft == y.sell_area_sq_ft && x.avghhi == y.avghhi && x.supertargetdistance == y.supertargetdistance && x.supertargetdrivetime == y.supertargetdrivetime && x.targetdistance == y.targetdistance && x.targetdrivetime == y.targetdrivetime && x.walmartdistance == y.walmartdistance && x.walmartdrivetime == y.walmartdrivetime && x.walmartsupercenterdistance == y.walmartsupercenterdistance && x.walmartsupercenterdrivetime == y.walmartsupercenterdrivetime;
    }
  };
  struct V_LOCATION_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_LOCATION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.zip);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_LOCATION_entry& x, const V_LOCATION_entry& y) {
      return x.locn == y.locn && x.zip == y.zip; 
    }
  };
  
  typedef MultiHashMap<V_LOCATION_entry, long, 
    PrimaryHashIndex<V_LOCATION_entry, V_LOCATION_mapkey01234567891011121314_idxfn>,
    SecondaryHashIndex<V_LOCATION_entry, V_LOCATION_mapkey01_idxfn>
  > V_LOCATION_map;
  
  
  struct V_CENSUS_entry {
    int zip; int population; int white; int asian; int pacific; int blackafrican; int medianage; int occupiedhouseunits; int houseunits; int families; int households; int husbwife; int males; int females; int householdschildren; int hispanic; long __av; V_CENSUS_entry* nxt; V_CENSUS_entry* prv;
  
    explicit V_CENSUS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_CENSUS_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15, const long c16) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15; __av = c16;  }
    V_CENSUS_entry(const V_CENSUS_entry& other) : zip(other.zip), population(other.population), white(other.white), asian(other.asian), pacific(other.pacific), blackafrican(other.blackafrican), medianage(other.medianage), occupiedhouseunits(other.occupiedhouseunits), houseunits(other.houseunits), families(other.families), households(other.households), husbwife(other.husbwife), males(other.males), females(other.females), householdschildren(other.householdschildren), hispanic(other.hispanic), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_CENSUS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 16) return; */
        zip = std::stoi(f[0]); population = std::stoi(f[1]); white = std::stoi(f[2]); asian = std::stoi(f[3]); pacific = std::stoi(f[4]); blackafrican = std::stoi(f[5]); medianage = std::stoi(f[6]); occupiedhouseunits = std::stoi(f[7]); houseunits = std::stoi(f[8]); families = std::stoi(f[9]); households = std::stoi(f[10]); husbwife = std::stoi(f[11]); males = std::stoi(f[12]); females = std::stoi(f[13]); householdschildren = std::stoi(f[14]); hispanic = std::stoi(f[15]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_CENSUS_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15;  return *this; }
    FORCE_INLINE V_CENSUS_entry& modify0(const int c0) { zip = c0; return *this; }
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
  
  struct V_CENSUS_mapkey0123456789101112131415_idxfn {
    FORCE_INLINE static size_t hash(const V_CENSUS_entry& e) {
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
    
    FORCE_INLINE static bool equals(const V_CENSUS_entry& x, const V_CENSUS_entry& y) {
      return x.zip == y.zip && x.population == y.population && x.white == y.white && x.asian == y.asian && x.pacific == y.pacific && x.blackafrican == y.blackafrican && x.medianage == y.medianage && x.occupiedhouseunits == y.occupiedhouseunits && x.houseunits == y.houseunits && x.families == y.families && x.households == y.households && x.husbwife == y.husbwife && x.males == y.males && x.females == y.females && x.householdschildren == y.householdschildren && x.hispanic == y.hispanic;
    }
  };
  struct V_CENSUS_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_CENSUS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.zip);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_CENSUS_entry& x, const V_CENSUS_entry& y) {
      return x.zip == y.zip; 
    }
  };
  
  typedef MultiHashMap<V_CENSUS_entry, long, 
    PrimaryHashIndex<V_CENSUS_entry, V_CENSUS_mapkey0123456789101112131415_idxfn>,
    SecondaryHashIndex<V_CENSUS_entry, V_CENSUS_mapkey0_idxfn>
  > V_CENSUS_map;
  
  
  struct V_WEATHER_entry {
    int locn; int dateid; int rain; int snow; int maxtemp; int mintemp; int meanwind; int thunder; long __av; V_WEATHER_entry* nxt; V_WEATHER_entry* prv;
  
    explicit V_WEATHER_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_WEATHER_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const int c7, const long c8) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7; __av = c8;  }
    V_WEATHER_entry(const V_WEATHER_entry& other) : locn(other.locn), dateid(other.dateid), rain(other.rain), snow(other.snow), maxtemp(other.maxtemp), mintemp(other.mintemp), meanwind(other.meanwind), thunder(other.thunder), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_WEATHER_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 8) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); rain = std::stoi(f[2]); snow = std::stoi(f[3]); maxtemp = std::stoi(f[4]); mintemp = std::stoi(f[5]); meanwind = std::stoi(f[6]); thunder = std::stoi(f[7]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_WEATHER_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const int c7) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7;  return *this; }
    FORCE_INLINE V_WEATHER_entry& modify01(const int c0, const int c1) { locn = c0; dateid = c1; return *this; }
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
  
  struct V_WEATHER_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const V_WEATHER_entry& e) {
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
    
    FORCE_INLINE static bool equals(const V_WEATHER_entry& x, const V_WEATHER_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.rain == y.rain && x.snow == y.snow && x.maxtemp == y.maxtemp && x.mintemp == y.mintemp && x.meanwind == y.meanwind && x.thunder == y.thunder;
    }
  };

  struct V_WEATHER_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_WEATHER_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_WEATHER_entry& x, const V_WEATHER_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid; 
    }
  };
  
  typedef MultiHashMap<V_WEATHER_entry, long, 
    PrimaryHashIndex<V_WEATHER_entry, V_WEATHER_mapkey01234567_idxfn>,
    SecondaryHashIndex<V_WEATHER_entry, V_WEATHER_mapkey01_idxfn>
  > V_WEATHER_map;
  
  
  struct DELTA_INVENTORY_entry {
    int locn; int dateid; int ksn; int inventoryunits; long __av; DELTA_INVENTORY_entry* nxt; DELTA_INVENTORY_entry* prv;
  
    explicit DELTA_INVENTORY_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_INVENTORY_entry(const int c0, const int c1, const int c2, const int c3, const long c4) { locn = c0; dateid = c1; ksn = c2; inventoryunits = c3; __av = c4;  }
    DELTA_INVENTORY_entry(const DELTA_INVENTORY_entry& other) : locn(other.locn), dateid(other.dateid), ksn(other.ksn), inventoryunits(other.inventoryunits), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_INVENTORY_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); ksn = std::stoi(f[2]); inventoryunits = std::stoi(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_INVENTORY_entry& modify(const int c0, const int c1, const int c2, const int c3) { locn = c0; dateid = c1; ksn = c2; inventoryunits = c3;  return *this; }
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
  
  struct DELTA_INVENTORY_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_INVENTORY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      hash_combine(h, e.dateid);
      hash_combine(h, e.ksn);
      hash_combine(h, e.inventoryunits);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_INVENTORY_entry& x, const DELTA_INVENTORY_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.ksn == y.ksn && x.inventoryunits == y.inventoryunits;
    }
  };
  
  typedef MultiHashMap<DELTA_INVENTORY_entry, long, 
    PrimaryHashIndex<DELTA_INVENTORY_entry, DELTA_INVENTORY_mapkey0123_idxfn>
  > DELTA_INVENTORY_map;
  
  
  struct DELTA_LOCATION_entry {
    int locn; int zip; int rgn_cd; int clim_zn_nbr; int tot_area_sq_ft; int sell_area_sq_ft; int avghhi; DOUBLE_TYPE supertargetdistance; DOUBLE_TYPE supertargetdrivetime; DOUBLE_TYPE targetdistance; DOUBLE_TYPE targetdrivetime; DOUBLE_TYPE walmartdistance; DOUBLE_TYPE walmartdrivetime; DOUBLE_TYPE walmartsupercenterdistance; DOUBLE_TYPE walmartsupercenterdrivetime; long __av; DELTA_LOCATION_entry* nxt; DELTA_LOCATION_entry* prv;
  
    explicit DELTA_LOCATION_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_LOCATION_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14, const long c15) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14; __av = c15;  }
    DELTA_LOCATION_entry(const DELTA_LOCATION_entry& other) : locn(other.locn), zip(other.zip), rgn_cd(other.rgn_cd), clim_zn_nbr(other.clim_zn_nbr), tot_area_sq_ft(other.tot_area_sq_ft), sell_area_sq_ft(other.sell_area_sq_ft), avghhi(other.avghhi), supertargetdistance(other.supertargetdistance), supertargetdrivetime(other.supertargetdrivetime), targetdistance(other.targetdistance), targetdrivetime(other.targetdrivetime), walmartdistance(other.walmartdistance), walmartdrivetime(other.walmartdrivetime), walmartsupercenterdistance(other.walmartsupercenterdistance), walmartsupercenterdrivetime(other.walmartsupercenterdrivetime), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_LOCATION_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 15) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); rgn_cd = std::stoi(f[2]); clim_zn_nbr = std::stoi(f[3]); tot_area_sq_ft = std::stoi(f[4]); sell_area_sq_ft = std::stoi(f[5]); avghhi = std::stoi(f[6]); supertargetdistance = std::stod(f[7]); supertargetdrivetime = std::stod(f[8]); targetdistance = std::stod(f[9]); targetdrivetime = std::stod(f[10]); walmartdistance = std::stod(f[11]); walmartdrivetime = std::stod(f[12]); walmartsupercenterdistance = std::stod(f[13]); walmartsupercenterdrivetime = std::stod(f[14]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_LOCATION_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14;  return *this; }
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
  
  struct DELTA_LOCATION_mapkey01234567891011121314_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_LOCATION_entry& e) {
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
    
    FORCE_INLINE static bool equals(const DELTA_LOCATION_entry& x, const DELTA_LOCATION_entry& y) {
      return x.locn == y.locn && x.zip == y.zip && x.rgn_cd == y.rgn_cd && x.clim_zn_nbr == y.clim_zn_nbr && x.tot_area_sq_ft == y.tot_area_sq_ft && x.sell_area_sq_ft == y.sell_area_sq_ft && x.avghhi == y.avghhi && x.supertargetdistance == y.supertargetdistance && x.supertargetdrivetime == y.supertargetdrivetime && x.targetdistance == y.targetdistance && x.targetdrivetime == y.targetdrivetime && x.walmartdistance == y.walmartdistance && x.walmartdrivetime == y.walmartdrivetime && x.walmartsupercenterdistance == y.walmartsupercenterdistance && x.walmartsupercenterdrivetime == y.walmartsupercenterdrivetime;
    }
  };
  
  typedef MultiHashMap<DELTA_LOCATION_entry, long, 
    PrimaryHashIndex<DELTA_LOCATION_entry, DELTA_LOCATION_mapkey01234567891011121314_idxfn>
  > DELTA_LOCATION_map;
  
  
  struct DELTA_CENSUS_entry {
    int zip; int population; int white; int asian; int pacific; int blackafrican; DOUBLE_TYPE medianage; int occupiedhouseunits; int houseunits; int families; int households; int husbwife; int males; int females; int householdschildren; int hispanic; long __av; DELTA_CENSUS_entry* nxt; DELTA_CENSUS_entry* prv;
  
    explicit DELTA_CENSUS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_CENSUS_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15, const long c16) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15; __av = c16;  }
    DELTA_CENSUS_entry(const DELTA_CENSUS_entry& other) : zip(other.zip), population(other.population), white(other.white), asian(other.asian), pacific(other.pacific), blackafrican(other.blackafrican), medianage(other.medianage), occupiedhouseunits(other.occupiedhouseunits), houseunits(other.houseunits), families(other.families), households(other.households), husbwife(other.husbwife), males(other.males), females(other.females), householdschildren(other.householdschildren), hispanic(other.hispanic), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_CENSUS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 16) return; */
        zip = std::stoi(f[0]); population = std::stoi(f[1]); white = std::stoi(f[2]); asian = std::stoi(f[3]); pacific = std::stoi(f[4]); blackafrican = std::stoi(f[5]); medianage = std::stod(f[6]); occupiedhouseunits = std::stoi(f[7]); houseunits = std::stoi(f[8]); families = std::stoi(f[9]); households = std::stoi(f[10]); husbwife = std::stoi(f[11]); males = std::stoi(f[12]); females = std::stoi(f[13]); householdschildren = std::stoi(f[14]); hispanic = std::stoi(f[15]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_CENSUS_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15;  return *this; }
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
  
  struct DELTA_CENSUS_mapkey0123456789101112131415_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_CENSUS_entry& e) {
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
    
    FORCE_INLINE static bool equals(const DELTA_CENSUS_entry& x, const DELTA_CENSUS_entry& y) {
      return x.zip == y.zip && x.population == y.population && x.white == y.white && x.asian == y.asian && x.pacific == y.pacific && x.blackafrican == y.blackafrican && x.medianage == y.medianage && x.occupiedhouseunits == y.occupiedhouseunits && x.houseunits == y.houseunits && x.families == y.families && x.households == y.households && x.husbwife == y.husbwife && x.males == y.males && x.females == y.females && x.householdschildren == y.householdschildren && x.hispanic == y.hispanic;
    }
  };
  
  typedef MultiHashMap<DELTA_CENSUS_entry, long, 
    PrimaryHashIndex<DELTA_CENSUS_entry, DELTA_CENSUS_mapkey0123456789101112131415_idxfn>
  > DELTA_CENSUS_map;
  
  
  struct DELTA_ITEM_entry {
    int ksn; int8_t subcategory; int8_t category; int8_t categorycluster; DOUBLE_TYPE prize; long __av; DELTA_ITEM_entry* nxt; DELTA_ITEM_entry* prv;
  
    explicit DELTA_ITEM_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_ITEM_entry(const int c0, const int8_t c1, const int8_t c2, const int8_t c3, const DOUBLE_TYPE c4, const long c5) { ksn = c0; subcategory = c1; category = c2; categorycluster = c3; prize = c4; __av = c5;  }
    DELTA_ITEM_entry(const DELTA_ITEM_entry& other) : ksn(other.ksn), subcategory(other.subcategory), category(other.category), categorycluster(other.categorycluster), prize(other.prize), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_ITEM_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        ksn = std::stoi(f[0]); subcategory = (int8_t) std::stoi(f[1]); category = (int8_t) std::stoi(f[2]); categorycluster = (int8_t) std::stoi(f[3]); prize = std::stod(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_ITEM_entry& modify(const int c0, const int8_t c1, const int8_t c2, const int8_t c3, const DOUBLE_TYPE c4) { ksn = c0; subcategory = c1; category = c2; categorycluster = c3; prize = c4;  return *this; }
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
  
  struct DELTA_ITEM_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_ITEM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ksn);
      hash_combine(h, e.subcategory);
      hash_combine(h, e.category);
      hash_combine(h, e.categorycluster);
      hash_combine(h, e.prize);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_ITEM_entry& x, const DELTA_ITEM_entry& y) {
      return x.ksn == y.ksn && x.subcategory == y.subcategory && x.category == y.category && x.categorycluster == y.categorycluster && x.prize == y.prize;
    }
  };
  
  typedef MultiHashMap<DELTA_ITEM_entry, long, 
    PrimaryHashIndex<DELTA_ITEM_entry, DELTA_ITEM_mapkey01234_idxfn>
  > DELTA_ITEM_map;
  
  
  struct DELTA_WEATHER_entry {
    int locn; int dateid; int8_t rain; int8_t snow; int maxtemp; int mintemp; DOUBLE_TYPE meanwind; int8_t thunder; long __av; DELTA_WEATHER_entry* nxt; DELTA_WEATHER_entry* prv;
  
    explicit DELTA_WEATHER_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_WEATHER_entry(const int c0, const int c1, const int8_t c2, const int8_t c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int8_t c7, const long c8) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7; __av = c8;  }
    DELTA_WEATHER_entry(const DELTA_WEATHER_entry& other) : locn(other.locn), dateid(other.dateid), rain(other.rain), snow(other.snow), maxtemp(other.maxtemp), mintemp(other.mintemp), meanwind(other.meanwind), thunder(other.thunder), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_WEATHER_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 8) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); rain = (int8_t) std::stoi(f[2]); snow = (int8_t) std::stoi(f[3]); maxtemp = std::stoi(f[4]); mintemp = std::stoi(f[5]); meanwind = std::stod(f[6]); thunder = (int8_t) std::stoi(f[7]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_WEATHER_entry& modify(const int c0, const int c1, const int8_t c2, const int8_t c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int8_t c7) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7;  return *this; }
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
  
  struct DELTA_WEATHER_mapkey01234567_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_WEATHER_entry& e) {
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
    
    FORCE_INLINE static bool equals(const DELTA_WEATHER_entry& x, const DELTA_WEATHER_entry& y) {
      return x.locn == y.locn && x.dateid == y.dateid && x.rain == y.rain && x.snow == y.snow && x.maxtemp == y.maxtemp && x.mintemp == y.mintemp && x.meanwind == y.meanwind && x.thunder == y.thunder;
    }
  };
  
  typedef MultiHashMap<DELTA_WEATHER_entry, long, 
    PrimaryHashIndex<DELTA_WEATHER_entry, DELTA_WEATHER_mapkey01234567_idxfn>
  > DELTA_WEATHER_map;

  

  /* Defines top-level materialized views */
  struct tlq_t {
    struct timeval t0, t; long tT, tN, tS;
    tlq_t(): tN(0), tS(0)  { 
      gettimeofday(&t0, NULL); 
    }
  
    /* Serialization code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << "\n";
      const V_locn_IIWLC1_map& _V_locn_IIWLC1 = get_V_locn_IIWLC1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_locn_IIWLC1), _V_locn_IIWLC1, "\t");
      
      ar << "\n";
      const V_dateid_IIW1_map& _V_dateid_IIW1 = get_V_dateid_IIW1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_dateid_IIW1), _V_dateid_IIW1, "\t");
      
      ar << "\n";
      const V_ksn_II1_map& _V_ksn_II1 = get_V_ksn_II1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_ksn_II1), _V_ksn_II1, "\t");
      
      ar << "\n";
      const V_zip_LC1_map& _V_zip_LC1 = get_V_zip_LC1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_zip_LC1), _V_zip_LC1, "\t");
      
      ar << "\n";
      const V_INVENTORY_map& _V_INVENTORY = get_V_INVENTORY();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_INVENTORY), _V_INVENTORY, "\t");
      
      ar << "\n";
      const V_ITEM_map& _V_ITEM = get_V_ITEM();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_ITEM), _V_ITEM, "\t");
      
      ar << "\n";
      const V_LOCATION_map& _V_LOCATION = get_V_LOCATION();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_LOCATION), _V_LOCATION, "\t");
      
      ar << "\n";
      const V_CENSUS_map& _V_CENSUS = get_V_CENSUS();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_CENSUS), _V_CENSUS, "\t");
      
      ar << "\n";
      const V_WEATHER_map& _V_WEATHER = get_V_WEATHER();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_WEATHER), _V_WEATHER, "\t");
    }
  
    /* Functions returning / computing the results of top level queries */
    const V_locn_IIWLC1_map& get_V_locn_IIWLC1() const {
      return V_locn_IIWLC1;
    }
    
    const V_dateid_IIW1_map& get_V_dateid_IIW1() const {
      return V_dateid_IIW1;
    }
    
    const V_ksn_II1_map& get_V_ksn_II1() const {
      return V_ksn_II1;
    }
    
    const V_zip_LC1_map& get_V_zip_LC1() const {
      return V_zip_LC1;
    }
    
    const V_INVENTORY_map& get_V_INVENTORY() const {
      return V_INVENTORY;
    }
    
    const V_ITEM_map& get_V_ITEM() const {
      return V_ITEM;
    }
    
    const V_LOCATION_map& get_V_LOCATION() const {
      return V_LOCATION;
    }
    
    const V_CENSUS_map& get_V_CENSUS() const {
      return V_CENSUS;
    }
    
    const V_WEATHER_map& get_V_WEATHER() const {
      return V_WEATHER;
    }
  
  public:
    /* Data structures used for storing / computing top-level queries */
    V_locn_IIWLC1_map V_locn_IIWLC1;
    V_dateid_IIW1_map V_dateid_IIW1;
    V_ksn_II1_map V_ksn_II1;
    V_zip_LC1_map V_zip_LC1;
    V_INVENTORY_map V_INVENTORY;
    V_ITEM_map V_ITEM;
    V_LOCATION_map V_LOCATION;
    V_CENSUS_map V_CENSUS;
    V_WEATHER_map V_WEATHER;
    
  };


  /* Contains materialized views and processing (IVM) logic */
  struct data_t : tlq_t {
  
    data_t(): tlq_t() {
      
      
    }
  
    
  
    
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_batch_update_INVENTORY(const std::vector<DELTA_INVENTORY_entry>::iterator &begin, const std::vector<DELTA_INVENTORY_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_INVENTORY_entry>::iterator e1 = begin; e1 != end; e1++) {
          int locn = e1->locn;
          int dateid = e1->dateid;
          int ksn = e1->ksn;
          int inventoryunits = e1->inventoryunits;
          long v1 = e1->__av;
          V_INVENTORY.addOrDelOnZero(se1.modify(locn, dateid, ksn, inventoryunits), v1);
        }
      }
      
      TMP_SUM1.clear();
      { //foreach
        for (std::vector<DELTA_INVENTORY_entry>::iterator e2 = begin; e2 != end; e2++) {
          int locn = e2->locn;
          int dateid = e2->dateid;
          int ksn = e2->ksn;
          int inventoryunits = e2->inventoryunits;
          long v2 = e2->__av;
          TMP_SUM1.addOrDelOnZero(se2.modify(locn, dateid, ksn), v2);
        }
      }
      
      TMP_SUM2.clear();
      { //foreach
        TMP_SUM1_entry* e3 = TMP_SUM1.head;
        while (e3) {
          int locn = e3->locn;
          int dateid = e3->dateid;
          int ksn = e3->ksn;
          long v3 = e3->__av;
          TMP_SUM2.addOrDelOnZero(se3.modify(locn, dateid, ksn), (v3 * V_subcategory_I1.getValueOrDefault(se4.modify(ksn))));
          e3 = e3->nxt;
        }
      }
      
      TMP_SUM2_PRIME.clear();
      { //foreach
        TMP_SUM2_entry* e4 = TMP_SUM2.head;
        while (e4) {
          int locn = e4->locn;
          int dateid = e4->dateid;
          int ksn = e4->ksn;
          long v4 = e4->__av;
          TMP_SUM2_PRIME.addOrDelOnZero(se5.modify(locn, dateid), v4);
          e4 = e4->nxt;
        }
      }
      
      TMP_SUM3.clear();
      { //foreach
        TMP_SUM2_PRIME_entry* e5 = TMP_SUM2_PRIME.head;
        while (e5) {
          int locn = e5->locn;
          int dateid = e5->dateid;
          long v5 = e5->__av;
          TMP_SUM3.addOrDelOnZero(se6.modify(locn, dateid), (v5 * V_rain_W1.getValueOrDefault(se7.modify(locn, dateid))));
          e5 = e5->nxt;
        }
      }
      
      TMP_SUM3_PRIME.clear();
      { //foreach
        TMP_SUM3_entry* e6 = TMP_SUM3.head;
        while (e6) {
          int locn = e6->locn;
          int dateid = e6->dateid;
          long v6 = e6->__av;
          TMP_SUM3_PRIME.addOrDelOnZero(se8.modify(locn), v6);
          e6 = e6->nxt;
        }
      }
      
      { //foreach
        TMP_SUM3_PRIME_entry* e7 = TMP_SUM3_PRIME.head;
        while (e7) {
          int locn = e7->locn;
          long v7 = e7->__av;
          V_locn_IIWLC1.addOrDelOnZero(se9.modify(locn), (v7 * V_zip_LC2.getValueOrDefault(se10.modify(locn))));
          e7 = e7->nxt;
        }
      }
      
      { //foreach
        TMP_SUM3_PRIME_entry* e8 = TMP_SUM3_PRIME.head;
        while (e8) {
          int locn = e8->locn;
          long v8 = e8->__av;
          V_dateid_IIW2.addOrDelOnZero(se11.modify(locn), v8);
          e8 = e8->nxt;
        }
      }
      
      { //foreach
        TMP_SUM3_entry* e9 = TMP_SUM3.head;
        while (e9) {
          int locn = e9->locn;
          int dateid = e9->dateid;
          long v9 = e9->__av;
          V_dateid_IIW1.addOrDelOnZero(se12.modify(locn, dateid), v9);
          e9 = e9->nxt;
        }
      }
      
      { //foreach
        TMP_SUM2_PRIME_entry* e10 = TMP_SUM2_PRIME.head;
        while (e10) {
          int locn = e10->locn;
          int dateid = e10->dateid;
          long v10 = e10->__av;
          V_ksn_II2.addOrDelOnZero(se13.modify(locn, dateid), v10);
          e10 = e10->nxt;
        }
      }
      
      { //foreach
        TMP_SUM2_entry* e11 = TMP_SUM2.head;
        while (e11) {
          int locn = e11->locn;
          int dateid = e11->dateid;
          int ksn = e11->ksn;
          long v11 = e11->__av;
          V_ksn_II1.addOrDelOnZero(se14.modify(locn, dateid, ksn), v11);
          e11 = e11->nxt;
        }
      }
      
      { //foreach
        TMP_SUM1_entry* e12 = TMP_SUM1.head;
        while (e12) {
          int locn = e12->locn;
          int dateid = e12->dateid;
          int ksn = e12->ksn;
          long v12 = e12->__av;
          V_inventoryunits_I1.addOrDelOnZero(se15.modify(locn, dateid, ksn), v12);
          e12 = e12->nxt;
        }
      }
    }
    
    
    void on_batch_update_LOCATION(const std::vector<DELTA_LOCATION_entry>::iterator &begin, const std::vector<DELTA_LOCATION_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_LOCATION_entry>::iterator e13 = begin; e13 != end; e13++) {
          int locn = e13->locn;
          int zip = e13->zip;
          int rgn_cd = e13->rgn_cd;
          int clim_zn_nbr = e13->clim_zn_nbr;
          int tot_area_sq_ft = e13->tot_area_sq_ft;
          int sell_area_sq_ft = e13->sell_area_sq_ft;
          int avghhi = e13->avghhi;
          DOUBLE_TYPE supertargetdistance = e13->supertargetdistance;
          DOUBLE_TYPE supertargetdrivetime = e13->supertargetdrivetime;
          DOUBLE_TYPE targetdistance = e13->targetdistance;
          DOUBLE_TYPE targetdrivetime = e13->targetdrivetime;
          DOUBLE_TYPE walmartdistance = e13->walmartdistance;
          DOUBLE_TYPE walmartdrivetime = e13->walmartdrivetime;
          DOUBLE_TYPE walmartsupercenterdistance = e13->walmartsupercenterdistance;
          DOUBLE_TYPE walmartsupercenterdrivetime = e13->walmartsupercenterdrivetime;
          long v13 = e13->__av;
          V_LOCATION.addOrDelOnZero(se16.modify(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime), v13);
        }
      }
      
      TMP_SUM4.clear();
      { //foreach
        for (std::vector<DELTA_LOCATION_entry>::iterator e14 = begin; e14 != end; e14++) {
          int locn = e14->locn;
          int zip = e14->zip;
          int rgn_cd = e14->rgn_cd;
          int clim_zn_nbr = e14->clim_zn_nbr;
          int tot_area_sq_ft = e14->tot_area_sq_ft;
          int sell_area_sq_ft = e14->sell_area_sq_ft;
          int avghhi = e14->avghhi;
          DOUBLE_TYPE supertargetdistance = e14->supertargetdistance;
          DOUBLE_TYPE supertargetdrivetime = e14->supertargetdrivetime;
          DOUBLE_TYPE targetdistance = e14->targetdistance;
          DOUBLE_TYPE targetdrivetime = e14->targetdrivetime;
          DOUBLE_TYPE walmartdistance = e14->walmartdistance;
          DOUBLE_TYPE walmartdrivetime = e14->walmartdrivetime;
          DOUBLE_TYPE walmartsupercenterdistance = e14->walmartsupercenterdistance;
          DOUBLE_TYPE walmartsupercenterdrivetime = e14->walmartsupercenterdrivetime;
          long v14 = e14->__av;
          TMP_SUM4.addOrDelOnZero(se17.modify(locn, zip), v14);
        }
      }
      
      TMP_SUM5.clear();
      { //foreach
        TMP_SUM4_entry* e15 = TMP_SUM4.head;
        while (e15) {
          int locn = e15->locn;
          int zip = e15->zip;
          long v15 = e15->__av;
          TMP_SUM5.addOrDelOnZero(se18.modify(locn, zip), (v15 * V_population_C1.getValueOrDefault(se19.modify(zip))));
          e15 = e15->nxt;
        }
      }
      
      TMP_SUM5_PRIME.clear();
      { //foreach
        TMP_SUM5_entry* e16 = TMP_SUM5.head;
        while (e16) {
          int locn = e16->locn;
          int zip = e16->zip;
          long v16 = e16->__av;
          TMP_SUM5_PRIME.addOrDelOnZero(se20.modify(locn), v16);
          e16 = e16->nxt;
        }
      }
      
      { //foreach
        TMP_SUM5_PRIME_entry* e17 = TMP_SUM5_PRIME.head;
        while (e17) {
          int locn = e17->locn;
          long v17 = e17->__av;
          V_locn_IIWLC1.addOrDelOnZero(se21.modify(locn), (v17 * V_dateid_IIW2.getValueOrDefault(se22.modify(locn))));
          e17 = e17->nxt;
        }
      }
      
      { //foreach
        TMP_SUM5_PRIME_entry* e18 = TMP_SUM5_PRIME.head;
        while (e18) {
          int locn = e18->locn;
          long v18 = e18->__av;
          V_zip_LC2.addOrDelOnZero(se23.modify(locn), v18);
          e18 = e18->nxt;
        }
      }
      
      { //foreach
        TMP_SUM5_entry* e19 = TMP_SUM5.head;
        while (e19) {
          int locn = e19->locn;
          int zip = e19->zip;
          long v19 = e19->__av;
          V_zip_LC1.addOrDelOnZero(se24.modify(locn, zip), v19);
          e19 = e19->nxt;
        }
      }
      
      { //foreach
        TMP_SUM4_entry* e20 = TMP_SUM4.head;
        while (e20) {
          int locn = e20->locn;
          int zip = e20->zip;
          long v20 = e20->__av;
          V_rgn_cd_L1.addOrDelOnZero(se25.modify(locn, zip), v20);
          e20 = e20->nxt;
        }
      }
    }
    
    
    void on_batch_update_CENSUS(const std::vector<DELTA_CENSUS_entry>::iterator &begin, const std::vector<DELTA_CENSUS_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_CENSUS_entry>::iterator e21 = begin; e21 != end; e21++) {
          int zip = e21->zip;
          int population = e21->population;
          int white = e21->white;
          int asian = e21->asian;
          int pacific = e21->pacific;
          int blackafrican = e21->blackafrican;
          DOUBLE_TYPE medianage = e21->medianage;
          int occupiedhouseunits = e21->occupiedhouseunits;
          int houseunits = e21->houseunits;
          int families = e21->families;
          int households = e21->households;
          int husbwife = e21->husbwife;
          int males = e21->males;
          int females = e21->females;
          int householdschildren = e21->householdschildren;
          int hispanic = e21->hispanic;
          long v21 = e21->__av;
          V_CENSUS.addOrDelOnZero(se26.modify(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic), v21);
        }
      }
      
      TMP_SUM6.clear();
      { //foreach
        for (std::vector<DELTA_CENSUS_entry>::iterator e22 = begin; e22 != end; e22++) {
          int zip = e22->zip;
          int population = e22->population;
          int white = e22->white;
          int asian = e22->asian;
          int pacific = e22->pacific;
          int blackafrican = e22->blackafrican;
          DOUBLE_TYPE medianage = e22->medianage;
          int occupiedhouseunits = e22->occupiedhouseunits;
          int houseunits = e22->houseunits;
          int families = e22->families;
          int households = e22->households;
          int husbwife = e22->husbwife;
          int males = e22->males;
          int females = e22->females;
          int householdschildren = e22->householdschildren;
          int hispanic = e22->hispanic;
          long v22 = e22->__av;
          TMP_SUM6.addOrDelOnZero(se27.modify(zip), v22);
        }
      }
      
      TMP_SUM7.clear();
      { //foreach
        TMP_SUM6_entry* e23 = TMP_SUM6.head;
        while (e23) {
          int zip = e23->zip;
          long v23 = e23->__av;
          { //slice
            const LinkedNode<V_rgn_cd_L1_entry>* n1 = static_cast<const LinkedNode<V_rgn_cd_L1_entry>*>(V_rgn_cd_L1.slice(se29.modify1(zip), 0));
            V_rgn_cd_L1_entry* e24;
            while (n1) {
              e24 = n1->obj;
              int locn = e24->locn;
              long v24 = e24->__av;
              TMP_SUM7.addOrDelOnZero(se28.modify(locn, zip), (v23 * v24));
              n1 = n1->next;
            }
          }
          e23 = e23->nxt;
        }
      }
      
      TMP_SUM7_PRIME.clear();
      { //foreach
        TMP_SUM7_entry* e25 = TMP_SUM7.head;
        while (e25) {
          int locn = e25->locn;
          int zip = e25->zip;
          long v25 = e25->__av;
          TMP_SUM7_PRIME.addOrDelOnZero(se30.modify(locn), v25);
          e25 = e25->nxt;
        }
      }
      
      { //foreach
        TMP_SUM7_PRIME_entry* e26 = TMP_SUM7_PRIME.head;
        while (e26) {
          int locn = e26->locn;
          long v26 = e26->__av;
          V_locn_IIWLC1.addOrDelOnZero(se31.modify(locn), (v26 * V_dateid_IIW2.getValueOrDefault(se32.modify(locn))));
          e26 = e26->nxt;
        }
      }
      
      { //foreach
        TMP_SUM7_PRIME_entry* e27 = TMP_SUM7_PRIME.head;
        while (e27) {
          int locn = e27->locn;
          long v27 = e27->__av;
          V_zip_LC2.addOrDelOnZero(se33.modify(locn), v27);
          e27 = e27->nxt;
        }
      }
      
      { //foreach
        TMP_SUM7_entry* e28 = TMP_SUM7.head;
        while (e28) {
          int locn = e28->locn;
          int zip = e28->zip;
          long v28 = e28->__av;
          V_zip_LC1.addOrDelOnZero(se34.modify(locn, zip), v28);
          e28 = e28->nxt;
        }
      }
      
      { //foreach
        TMP_SUM6_entry* e29 = TMP_SUM6.head;
        while (e29) {
          int zip = e29->zip;
          long v29 = e29->__av;
          V_population_C1.addOrDelOnZero(se35.modify(zip), v29);
          e29 = e29->nxt;
        }
      }
    }
    
    
    void on_batch_update_ITEM(const std::vector<DELTA_ITEM_entry>::iterator &begin, const std::vector<DELTA_ITEM_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_ITEM_entry>::iterator e30 = begin; e30 != end; e30++) {
          int ksn = e30->ksn;
          int8_t subcategory = e30->subcategory;
          int8_t category = e30->category;
          int8_t categorycluster = e30->categorycluster;
          DOUBLE_TYPE prize = e30->prize;
          long v30 = e30->__av;
          V_ITEM.addOrDelOnZero(se36.modify(ksn, subcategory, category, categorycluster, prize), v30);
        }
      }
      
      TMP_SUM8.clear();
      { //foreach
        for (std::vector<DELTA_ITEM_entry>::iterator e31 = begin; e31 != end; e31++) {
          int ksn = e31->ksn;
          int8_t subcategory = e31->subcategory;
          int8_t category = e31->category;
          int8_t categorycluster = e31->categorycluster;
          DOUBLE_TYPE prize = e31->prize;
          long v31 = e31->__av;
          TMP_SUM8.addOrDelOnZero(se37.modify(ksn), v31);
        }
      }
      
      TMP_SUM9.clear();
      { //foreach
        TMP_SUM8_entry* e32 = TMP_SUM8.head;
        while (e32) {
          int ksn = e32->ksn;
          long v32 = e32->__av;
          { //slice
            const LinkedNode<V_inventoryunits_I1_entry>* n2 = static_cast<const LinkedNode<V_inventoryunits_I1_entry>*>(V_inventoryunits_I1.slice(se39.modify2(ksn), 0));
            V_inventoryunits_I1_entry* e33;
            while (n2) {
              e33 = n2->obj;
              int locn = e33->locn;
              int dateid = e33->dateid;
              long v33 = e33->__av;
              TMP_SUM9.addOrDelOnZero(se38.modify(locn, dateid, ksn), (v32 * v33));
              n2 = n2->next;
            }
          }
          e32 = e32->nxt;
        }
      }
      
      TMP_SUM9_PRIME.clear();
      { //foreach
        TMP_SUM9_entry* e34 = TMP_SUM9.head;
        while (e34) {
          int locn = e34->locn;
          int dateid = e34->dateid;
          int ksn = e34->ksn;
          long v34 = e34->__av;
          TMP_SUM9_PRIME.addOrDelOnZero(se40.modify(locn, dateid), v34);
          e34 = e34->nxt;
        }
      }
      
      TMP_SUM10.clear();
      { //foreach
        TMP_SUM9_PRIME_entry* e35 = TMP_SUM9_PRIME.head;
        while (e35) {
          int locn = e35->locn;
          int dateid = e35->dateid;
          long v35 = e35->__av;
          TMP_SUM10.addOrDelOnZero(se41.modify(locn, dateid), (v35 * V_rain_W1.getValueOrDefault(se42.modify(locn, dateid))));
          e35 = e35->nxt;
        }
      }
      
      TMP_SUM10_PRIME.clear();
      { //foreach
        TMP_SUM10_entry* e36 = TMP_SUM10.head;
        while (e36) {
          int locn = e36->locn;
          int dateid = e36->dateid;
          long v36 = e36->__av;
          TMP_SUM10_PRIME.addOrDelOnZero(se43.modify(locn), v36);
          e36 = e36->nxt;
        }
      }
      
      { //foreach
        TMP_SUM10_PRIME_entry* e37 = TMP_SUM10_PRIME.head;
        while (e37) {
          int locn = e37->locn;
          long v37 = e37->__av;
          V_locn_IIWLC1.addOrDelOnZero(se44.modify(locn), (v37 * V_zip_LC2.getValueOrDefault(se45.modify(locn))));
          e37 = e37->nxt;
        }
      }
      
      { //foreach
        TMP_SUM10_PRIME_entry* e38 = TMP_SUM10_PRIME.head;
        while (e38) {
          int locn = e38->locn;
          long v38 = e38->__av;
          V_dateid_IIW2.addOrDelOnZero(se46.modify(locn), v38);
          e38 = e38->nxt;
        }
      }
      
      { //foreach
        TMP_SUM10_entry* e39 = TMP_SUM10.head;
        while (e39) {
          int locn = e39->locn;
          int dateid = e39->dateid;
          long v39 = e39->__av;
          V_dateid_IIW1.addOrDelOnZero(se47.modify(locn, dateid), v39);
          e39 = e39->nxt;
        }
      }
      
      { //foreach
        TMP_SUM9_PRIME_entry* e40 = TMP_SUM9_PRIME.head;
        while (e40) {
          int locn = e40->locn;
          int dateid = e40->dateid;
          long v40 = e40->__av;
          V_ksn_II2.addOrDelOnZero(se48.modify(locn, dateid), v40);
          e40 = e40->nxt;
        }
      }
      
      { //foreach
        TMP_SUM9_entry* e41 = TMP_SUM9.head;
        while (e41) {
          int locn = e41->locn;
          int dateid = e41->dateid;
          int ksn = e41->ksn;
          long v41 = e41->__av;
          V_ksn_II1.addOrDelOnZero(se49.modify(locn, dateid, ksn), v41);
          e41 = e41->nxt;
        }
      }
      
      { //foreach
        TMP_SUM8_entry* e42 = TMP_SUM8.head;
        while (e42) {
          int ksn = e42->ksn;
          long v42 = e42->__av;
          V_subcategory_I1.addOrDelOnZero(se50.modify(ksn), v42);
          e42 = e42->nxt;
        }
      }
    }
    
    
    void on_batch_update_WEATHER(const std::vector<DELTA_WEATHER_entry>::iterator &begin, const std::vector<DELTA_WEATHER_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_WEATHER_entry>::iterator e43 = begin; e43 != end; e43++) {
          int locn = e43->locn;
          int dateid = e43->dateid;
          int8_t rain = e43->rain;
          int8_t snow = e43->snow;
          int maxtemp = e43->maxtemp;
          int mintemp = e43->mintemp;
          DOUBLE_TYPE meanwind = e43->meanwind;
          int8_t thunder = e43->thunder;
          long v43 = e43->__av;
          V_WEATHER.addOrDelOnZero(se51.modify(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder), v43);
        }
      }
      
      TMP_SUM11.clear();
      { //foreach
        for (std::vector<DELTA_WEATHER_entry>::iterator e44 = begin; e44 != end; e44++) {
          int locn = e44->locn;
          int dateid = e44->dateid;
          int8_t rain = e44->rain;
          int8_t snow = e44->snow;
          int maxtemp = e44->maxtemp;
          int mintemp = e44->mintemp;
          DOUBLE_TYPE meanwind = e44->meanwind;
          int8_t thunder = e44->thunder;
          long v44 = e44->__av;
          TMP_SUM11.addOrDelOnZero(se52.modify(locn, dateid), v44);
        }
      }
      
      TMP_SUM12.clear();
      { //foreach
        TMP_SUM11_entry* e45 = TMP_SUM11.head;
        while (e45) {
          int locn = e45->locn;
          int dateid = e45->dateid;
          long v45 = e45->__av;
          TMP_SUM12.addOrDelOnZero(se53.modify(locn, dateid), (v45 * V_ksn_II2.getValueOrDefault(se54.modify(locn, dateid))));
          e45 = e45->nxt;
        }
      }
      
      TMP_SUM12_PRIME.clear();
      { //foreach
        TMP_SUM12_entry* e46 = TMP_SUM12.head;
        while (e46) {
          int locn = e46->locn;
          int dateid = e46->dateid;
          long v46 = e46->__av;
          TMP_SUM12_PRIME.addOrDelOnZero(se55.modify(locn), v46);
          e46 = e46->nxt;
        }
      }
      
      { //foreach
        TMP_SUM12_PRIME_entry* e47 = TMP_SUM12_PRIME.head;
        while (e47) {
          int locn = e47->locn;
          long v47 = e47->__av;
          V_locn_IIWLC1.addOrDelOnZero(se56.modify(locn), (v47 * V_zip_LC2.getValueOrDefault(se57.modify(locn))));
          e47 = e47->nxt;
        }
      }
      
      { //foreach
        TMP_SUM12_PRIME_entry* e48 = TMP_SUM12_PRIME.head;
        while (e48) {
          int locn = e48->locn;
          long v48 = e48->__av;
          V_dateid_IIW2.addOrDelOnZero(se58.modify(locn), v48);
          e48 = e48->nxt;
        }
      }
      
      { //foreach
        TMP_SUM12_entry* e49 = TMP_SUM12.head;
        while (e49) {
          int locn = e49->locn;
          int dateid = e49->dateid;
          long v49 = e49->__av;
          V_dateid_IIW1.addOrDelOnZero(se59.modify(locn, dateid), v49);
          e49 = e49->nxt;
        }
      }
      
      { //foreach
        TMP_SUM11_entry* e50 = TMP_SUM11.head;
        while (e50) {
          int locn = e50->locn;
          int dateid = e50->dateid;
          long v50 = e50->__av;
          V_rain_W1.addOrDelOnZero(se60.modify(locn, dateid), v50);
          e50 = e50->nxt;
        }
      }
    }
    
    
    void on_system_ready_event() {
      
    }
  
  private:
    
      /* Preallocated map entries (to avoid recreation of temporary objects) */
      V_INVENTORY_entry se1;
      TMP_SUM1_entry se2;
      TMP_SUM2_entry se3;
      V_subcategory_I1_entry se4;
      TMP_SUM2_PRIME_entry se5;
      TMP_SUM3_entry se6;
      V_rain_W1_entry se7;
      TMP_SUM3_PRIME_entry se8;
      V_locn_IIWLC1_entry se9;
      V_zip_LC2_entry se10;
      V_dateid_IIW2_entry se11;
      V_dateid_IIW1_entry se12;
      V_ksn_II2_entry se13;
      V_ksn_II1_entry se14;
      V_inventoryunits_I1_entry se15;
      V_LOCATION_entry se16;
      TMP_SUM4_entry se17;
      TMP_SUM5_entry se18;
      V_population_C1_entry se19;
      TMP_SUM5_PRIME_entry se20;
      V_locn_IIWLC1_entry se21;
      V_dateid_IIW2_entry se22;
      V_zip_LC2_entry se23;
      V_zip_LC1_entry se24;
      V_rgn_cd_L1_entry se25;
      V_CENSUS_entry se26;
      TMP_SUM6_entry se27;
      TMP_SUM7_entry se28;
      V_rgn_cd_L1_entry se29;
      TMP_SUM7_PRIME_entry se30;
      V_locn_IIWLC1_entry se31;
      V_dateid_IIW2_entry se32;
      V_zip_LC2_entry se33;
      V_zip_LC1_entry se34;
      V_population_C1_entry se35;
      V_ITEM_entry se36;
      TMP_SUM8_entry se37;
      TMP_SUM9_entry se38;
      V_inventoryunits_I1_entry se39;
      TMP_SUM9_PRIME_entry se40;
      TMP_SUM10_entry se41;
      V_rain_W1_entry se42;
      TMP_SUM10_PRIME_entry se43;
      V_locn_IIWLC1_entry se44;
      V_zip_LC2_entry se45;
      V_dateid_IIW2_entry se46;
      V_dateid_IIW1_entry se47;
      V_ksn_II2_entry se48;
      V_ksn_II1_entry se49;
      V_subcategory_I1_entry se50;
      V_WEATHER_entry se51;
      TMP_SUM11_entry se52;
      TMP_SUM12_entry se53;
      V_ksn_II2_entry se54;
      TMP_SUM12_PRIME_entry se55;
      V_locn_IIWLC1_entry se56;
      V_zip_LC2_entry se57;
      V_dateid_IIW2_entry se58;
      V_dateid_IIW1_entry se59;
      V_rain_W1_entry se60;
    
      
    
      /* Data structures used for storing materialized views */
      V_dateid_IIW2_map V_dateid_IIW2;
      V_ksn_II2_map V_ksn_II2;
      V_inventoryunits_I1_map V_inventoryunits_I1;
      V_subcategory_I1_map V_subcategory_I1;
      V_rain_W1_map V_rain_W1;
      V_zip_LC2_map V_zip_LC2;
      V_rgn_cd_L1_map V_rgn_cd_L1;
      V_population_C1_map V_population_C1;
      TMP_SUM1_map TMP_SUM1;
      TMP_SUM2_map TMP_SUM2;
      TMP_SUM2_PRIME_map TMP_SUM2_PRIME;
      TMP_SUM3_map TMP_SUM3;
      TMP_SUM3_PRIME_map TMP_SUM3_PRIME;
      TMP_SUM4_map TMP_SUM4;
      TMP_SUM5_map TMP_SUM5;
      TMP_SUM5_PRIME_map TMP_SUM5_PRIME;
      TMP_SUM6_map TMP_SUM6;
      TMP_SUM7_map TMP_SUM7;
      TMP_SUM7_PRIME_map TMP_SUM7_PRIME;
      TMP_SUM8_map TMP_SUM8;
      TMP_SUM9_map TMP_SUM9;
      TMP_SUM9_PRIME_map TMP_SUM9_PRIME;
      TMP_SUM10_map TMP_SUM10;
      TMP_SUM10_PRIME_map TMP_SUM10_PRIME;
      TMP_SUM11_map TMP_SUM11;
      TMP_SUM12_map TMP_SUM12;
      TMP_SUM12_PRIME_map TMP_SUM12_PRIME;
      DELTA_INVENTORY_map DELTA_INVENTORY;
      DELTA_LOCATION_map DELTA_LOCATION;
      DELTA_CENSUS_map DELTA_CENSUS;
      DELTA_ITEM_map DELTA_ITEM;
      DELTA_WEATHER_map DELTA_WEATHER;
    
      
    
  };

  

}