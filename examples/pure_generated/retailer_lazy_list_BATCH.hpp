#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"

#include "ring/ring_relational_opt.hpp"

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
  
  typedef MultiHashMap<V_INVENTORY_entry, long, 
    PrimaryHashIndex<V_INVENTORY_entry, V_INVENTORY_mapkey0123_idxfn>
  > V_INVENTORY_map;
  
  
  struct V_LOCATION_entry {
    int locn; int zip; int rgn_cd; int clim_zn_nbr; int tot_area_sq_ft; int sell_area_sq_ft; int avghhi; DOUBLE_TYPE supertargetdistance; DOUBLE_TYPE supertargetdrivetime; DOUBLE_TYPE targetdistance; DOUBLE_TYPE targetdrivetime; DOUBLE_TYPE walmartdistance; DOUBLE_TYPE walmartdrivetime; DOUBLE_TYPE walmartsupercenterdistance; DOUBLE_TYPE walmartsupercenterdrivetime; long __av; V_LOCATION_entry* nxt; V_LOCATION_entry* prv;
  
    explicit V_LOCATION_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_LOCATION_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14, const long c15) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14; __av = c15;  }
    V_LOCATION_entry(const V_LOCATION_entry& other) : locn(other.locn), zip(other.zip), rgn_cd(other.rgn_cd), clim_zn_nbr(other.clim_zn_nbr), tot_area_sq_ft(other.tot_area_sq_ft), sell_area_sq_ft(other.sell_area_sq_ft), avghhi(other.avghhi), supertargetdistance(other.supertargetdistance), supertargetdrivetime(other.supertargetdrivetime), targetdistance(other.targetdistance), targetdrivetime(other.targetdrivetime), walmartdistance(other.walmartdistance), walmartdrivetime(other.walmartdrivetime), walmartsupercenterdistance(other.walmartsupercenterdistance), walmartsupercenterdrivetime(other.walmartsupercenterdrivetime), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_LOCATION_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 15) return; */
        locn = std::stoi(f[0]); zip = std::stoi(f[1]); rgn_cd = std::stoi(f[2]); clim_zn_nbr = std::stoi(f[3]); tot_area_sq_ft = std::stoi(f[4]); sell_area_sq_ft = std::stoi(f[5]); avghhi = std::stoi(f[6]); supertargetdistance = std::stod(f[7]); supertargetdrivetime = std::stod(f[8]); targetdistance = std::stod(f[9]); targetdrivetime = std::stod(f[10]); walmartdistance = std::stod(f[11]); walmartdrivetime = std::stod(f[12]); walmartsupercenterdistance = std::stod(f[13]); walmartsupercenterdrivetime = std::stod(f[14]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_LOCATION_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const int c6, const DOUBLE_TYPE c7, const DOUBLE_TYPE c8, const DOUBLE_TYPE c9, const DOUBLE_TYPE c10, const DOUBLE_TYPE c11, const DOUBLE_TYPE c12, const DOUBLE_TYPE c13, const DOUBLE_TYPE c14) { locn = c0; zip = c1; rgn_cd = c2; clim_zn_nbr = c3; tot_area_sq_ft = c4; sell_area_sq_ft = c5; avghhi = c6; supertargetdistance = c7; supertargetdrivetime = c8; targetdistance = c9; targetdrivetime = c10; walmartdistance = c11; walmartdrivetime = c12; walmartsupercenterdistance = c13; walmartsupercenterdrivetime = c14;  return *this; }
    FORCE_INLINE V_LOCATION_entry& modify0(const int c0) { locn = c0;  return *this; }
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
  
  struct V_LOCATION_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_LOCATION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.locn);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_LOCATION_entry& x, const V_LOCATION_entry& y) {
      return x.locn == y.locn;
    }
  };
  
  typedef MultiHashMap<V_LOCATION_entry, long, 
    PrimaryHashIndex<V_LOCATION_entry, V_LOCATION_mapkey01234567891011121314_idxfn>,
    SecondaryHashIndex<V_LOCATION_entry, V_LOCATION_mapkey0_idxfn>
  > V_LOCATION_map;
  
  
  struct V_CENSUS_entry {
    int zip; int population; int white; int asian; int pacific; int blackafrican; DOUBLE_TYPE medianage; int occupiedhouseunits; int houseunits; int families; int households; int husbwife; int males; int females; int householdschildren; int hispanic; long __av; V_CENSUS_entry* nxt; V_CENSUS_entry* prv;
  
    explicit V_CENSUS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_CENSUS_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15, const long c16) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15; __av = c16;  }
    V_CENSUS_entry(const V_CENSUS_entry& other) : zip(other.zip), population(other.population), white(other.white), asian(other.asian), pacific(other.pacific), blackafrican(other.blackafrican), medianage(other.medianage), occupiedhouseunits(other.occupiedhouseunits), houseunits(other.houseunits), families(other.families), households(other.households), husbwife(other.husbwife), males(other.males), females(other.females), householdschildren(other.householdschildren), hispanic(other.hispanic), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_CENSUS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 16) return; */
        zip = std::stoi(f[0]); population = std::stoi(f[1]); white = std::stoi(f[2]); asian = std::stoi(f[3]); pacific = std::stoi(f[4]); blackafrican = std::stoi(f[5]); medianage = std::stod(f[6]); occupiedhouseunits = std::stoi(f[7]); houseunits = std::stoi(f[8]); families = std::stoi(f[9]); households = std::stoi(f[10]); husbwife = std::stoi(f[11]); males = std::stoi(f[12]); females = std::stoi(f[13]); householdschildren = std::stoi(f[14]); hispanic = std::stoi(f[15]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_CENSUS_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int c7, const int c8, const int c9, const int c10, const int c11, const int c12, const int c13, const int c14, const int c15) { zip = c0; population = c1; white = c2; asian = c3; pacific = c4; blackafrican = c5; medianage = c6; occupiedhouseunits = c7; houseunits = c8; families = c9; households = c10; husbwife = c11; males = c12; females = c13; householdschildren = c14; hispanic = c15;  return *this; }
    FORCE_INLINE V_CENSUS_entry& modify0(const int c0) { zip = c0;  return *this; }
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
  
  
  struct V_ITEM_entry {
    int ksn; int8_t subcategory; int8_t category; int8_t categoryCluster; DOUBLE_TYPE prize; long __av; V_ITEM_entry* nxt; V_ITEM_entry* prv;
  
    explicit V_ITEM_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_ITEM_entry(const int c0, const int8_t c1, const int8_t c2, const int8_t c3, const DOUBLE_TYPE c4, const long c5) { ksn = c0; subcategory = c1; category = c2; categoryCluster = c3; prize = c4; __av = c5;  }
    V_ITEM_entry(const V_ITEM_entry& other) : ksn(other.ksn), subcategory(other.subcategory), category(other.category), categoryCluster(other.categoryCluster), prize(other.prize), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_ITEM_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        ksn = std::stoi(f[0]); subcategory = (int8_t) std::stoi(f[1]); category = (int8_t) std::stoi(f[2]); categoryCluster = (int8_t) std::stoi(f[3]); prize = std::stod(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_ITEM_entry& modify(const int c0, const int8_t c1, const int8_t c2, const int8_t c3, const DOUBLE_TYPE c4) { ksn = c0; subcategory = c1; category = c2; categoryCluster = c3; prize = c4;  return *this; }
    FORCE_INLINE V_ITEM_entry& modify0(const int c0) { ksn = c0;  return *this; }
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
  
  
  struct V_WEATHER_entry {
    int locn; int dateid; int8_t rain; int8_t snow; int maxtemp; int mintemp; DOUBLE_TYPE meanwind; int8_t thunder; long __av; V_WEATHER_entry* nxt; V_WEATHER_entry* prv;
  
    explicit V_WEATHER_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_WEATHER_entry(const int c0, const int c1, const int8_t c2, const int8_t c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int8_t c7, const long c8) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7; __av = c8;  }
    V_WEATHER_entry(const V_WEATHER_entry& other) : locn(other.locn), dateid(other.dateid), rain(other.rain), snow(other.snow), maxtemp(other.maxtemp), mintemp(other.mintemp), meanwind(other.meanwind), thunder(other.thunder), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_WEATHER_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 8) return; */
        locn = std::stoi(f[0]); dateid = std::stoi(f[1]); rain = (int8_t) std::stoi(f[2]); snow = (int8_t) std::stoi(f[3]); maxtemp = std::stoi(f[4]); mintemp = std::stoi(f[5]); meanwind = std::stod(f[6]); thunder = (int8_t) std::stoi(f[7]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_WEATHER_entry& modify(const int c0, const int c1, const int8_t c2, const int8_t c3, const int c4, const int c5, const DOUBLE_TYPE c6, const int8_t c7) { locn = c0; dateid = c1; rain = c2; snow = c3; maxtemp = c4; mintemp = c5; meanwind = c6; thunder = c7;  return *this; }
    FORCE_INLINE V_WEATHER_entry& modify01(const int c0, const int c1) { locn = c0; dateid = c1;  return *this; }
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
    tlq_t(): tN(0), tS(0) , V_locn_IIWLC1(RingRelation<0, int, int, int, int, int8_t, int8_t, int8_t, DOUBLE_TYPE, int8_t, int8_t, int, int, DOUBLE_TYPE, int8_t, int, int, int, int, int, int, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int>()) { 
      gettimeofday(&t0, NULL); 
    }
  
    /* Serialization code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << "\n";
      const RingRelation<0, int, int, int, int, int8_t, int8_t, int8_t, DOUBLE_TYPE, int8_t, int8_t, int, int, DOUBLE_TYPE, int8_t, int, int, int, int, int, int, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int>& _V_locn_IIWLC1 = get_V_locn_IIWLC1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_locn_IIWLC1), _V_locn_IIWLC1, "\t");
    }
  
    /* Functions returning / computing the results of top level queries */
    const RingRelation<0, int, int, int, int, int8_t, int8_t, int8_t, DOUBLE_TYPE, int8_t, int8_t, int, int, DOUBLE_TYPE, int8_t, int, int, int, int, int, int, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int>& get_V_locn_IIWLC1() const {
      return V_locn_IIWLC1;
    }
  
  protected:
    /* Data structures used for storing / computing top-level queries */
    RingRelation<0, int, int, int, int, int8_t, int8_t, int8_t, DOUBLE_TYPE, int8_t, int8_t, int, int, DOUBLE_TYPE, int8_t, int, int, int, int, int, int, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int> V_locn_IIWLC1 = RingRelation<0, int, int, int, int, int8_t, int8_t, int8_t, DOUBLE_TYPE, int8_t, int8_t, int, int, DOUBLE_TYPE, int8_t, int, int, int, int, int, int, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int>();
    
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
    }
    
    
    void on_batch_update_LOCATION(const std::vector<DELTA_LOCATION_entry>::iterator &begin, const std::vector<DELTA_LOCATION_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_LOCATION_entry>::iterator e2 = begin; e2 != end; e2++) {
          int locn = e2->locn;
          int zip = e2->zip;
          int rgn_cd = e2->rgn_cd;
          int clim_zn_nbr = e2->clim_zn_nbr;
          int tot_area_sq_ft = e2->tot_area_sq_ft;
          int sell_area_sq_ft = e2->sell_area_sq_ft;
          int avghhi = e2->avghhi;
          DOUBLE_TYPE supertargetdistance = e2->supertargetdistance;
          DOUBLE_TYPE supertargetdrivetime = e2->supertargetdrivetime;
          DOUBLE_TYPE targetdistance = e2->targetdistance;
          DOUBLE_TYPE targetdrivetime = e2->targetdrivetime;
          DOUBLE_TYPE walmartdistance = e2->walmartdistance;
          DOUBLE_TYPE walmartdrivetime = e2->walmartdrivetime;
          DOUBLE_TYPE walmartsupercenterdistance = e2->walmartsupercenterdistance;
          DOUBLE_TYPE walmartsupercenterdrivetime = e2->walmartsupercenterdrivetime;
          long v2 = e2->__av;
          V_LOCATION.addOrDelOnZero(se2.modify(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime), v2);
        }
      }
    }
    
    
    void on_batch_update_CENSUS(const std::vector<DELTA_CENSUS_entry>::iterator &begin, const std::vector<DELTA_CENSUS_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_CENSUS_entry>::iterator e3 = begin; e3 != end; e3++) {
          int zip = e3->zip;
          int population = e3->population;
          int white = e3->white;
          int asian = e3->asian;
          int pacific = e3->pacific;
          int blackafrican = e3->blackafrican;
          DOUBLE_TYPE medianage = e3->medianage;
          int occupiedhouseunits = e3->occupiedhouseunits;
          int houseunits = e3->houseunits;
          int families = e3->families;
          int households = e3->households;
          int husbwife = e3->husbwife;
          int males = e3->males;
          int females = e3->females;
          int householdschildren = e3->householdschildren;
          int hispanic = e3->hispanic;
          long v3 = e3->__av;
          V_CENSUS.addOrDelOnZero(se3.modify(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic), v3);
        }
      }
    }
    
    
    void on_batch_update_ITEM(const std::vector<DELTA_ITEM_entry>::iterator &begin, const std::vector<DELTA_ITEM_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_ITEM_entry>::iterator e4 = begin; e4 != end; e4++) {
          int ksn = e4->ksn;
          int8_t subcategory = e4->subcategory;
          int8_t category = e4->category;
          int8_t categorycluster = e4->categorycluster;
          DOUBLE_TYPE prize = e4->prize;
          long v4 = e4->__av;
          V_ITEM.addOrDelOnZero(se4.modify(ksn, subcategory, category, categorycluster, prize), v4);
        }
      }
    }
    
    
    void on_batch_update_WEATHER(const std::vector<DELTA_WEATHER_entry>::iterator &begin, const std::vector<DELTA_WEATHER_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_WEATHER_entry>::iterator e5 = begin; e5 != end; e5++) {
          int locn = e5->locn;
          int dateid = e5->dateid;
          int8_t rain = e5->rain;
          int8_t snow = e5->snow;
          int maxtemp = e5->maxtemp;
          int mintemp = e5->mintemp;
          DOUBLE_TYPE meanwind = e5->meanwind;
          int8_t thunder = e5->thunder;
          long v5 = e5->__av;
          V_WEATHER.addOrDelOnZero(se5.modify(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder), v5);
        }
      }
    }
    
    
    void on_system_ready_event() {
      V_locn_IIWLC1.store.clear(); 
      { //foreach
        V_INVENTORY_entry* e6 = V_INVENTORY.head;
        while (e6) {
          int locn = e6->locn;
          int dateid = e6->dateid;
          int ksn = e6->ksn;
          int inventoryunits = e6->inventoryunits;
          long v6 = e6->__av;
          { //slice
            const LinkedNode<V_ITEM_entry>* n4 = static_cast<const LinkedNode<V_ITEM_entry>*>(V_ITEM.slice(se10.modify0(ksn), 0));
            V_ITEM_entry* e7;
            while (n4) {
              e7 = n4->obj;
              int8_t subcategory = e7->subcategory;
              int8_t category = e7->category;
              int8_t categorycluster = e7->categoryCluster;
              DOUBLE_TYPE prize = e7->prize;
              long v7 = e7->__av;
              { //slice
                const LinkedNode<V_WEATHER_entry>* n3 = static_cast<const LinkedNode<V_WEATHER_entry>*>(V_WEATHER.slice(se9.modify01(locn, dateid), 0));
                V_WEATHER_entry* e8;
                while (n3) {
                  e8 = n3->obj;
                  int8_t rain = e8->rain;
                  int8_t snow = e8->snow;
                  int maxtemp = e8->maxtemp;
                  int mintemp = e8->mintemp;
                  DOUBLE_TYPE meanwind = e8->meanwind;
                  int8_t thunder = e8->thunder;
                  long v8 = e8->__av;
                  { //slice
                    const LinkedNode<V_LOCATION_entry>* n2 = static_cast<const LinkedNode<V_LOCATION_entry>*>(V_LOCATION.slice(se8.modify0(locn), 0));
                    V_LOCATION_entry* e9;
                    while (n2) {
                      e9 = n2->obj;
                      int zip = e9->zip;
                      int rgn_cd = e9->rgn_cd;
                      int clim_zn_nbr = e9->clim_zn_nbr;
                      int tot_area_sq_ft = e9->tot_area_sq_ft;
                      int sell_area_sq_ft = e9->sell_area_sq_ft;
                      int avghhi = e9->avghhi;
                      DOUBLE_TYPE supertargetdistance = e9->supertargetdistance;
                      DOUBLE_TYPE supertargetdrivetime = e9->supertargetdrivetime;
                      DOUBLE_TYPE targetdistance = e9->targetdistance;
                      DOUBLE_TYPE targetdrivetime = e9->targetdrivetime;
                      DOUBLE_TYPE walmartdistance = e9->walmartdistance;
                      DOUBLE_TYPE walmartdrivetime = e9->walmartdrivetime;
                      DOUBLE_TYPE walmartsupercenterdistance = e9->walmartsupercenterdistance;
                      DOUBLE_TYPE walmartsupercenterdrivetime = e9->walmartsupercenterdrivetime;
                      long v9 = e9->__av;
                      { //slice
                        const LinkedNode<V_CENSUS_entry>* n1 = static_cast<const LinkedNode<V_CENSUS_entry>*>(V_CENSUS.slice(se7.modify0(zip), 0));
                        V_CENSUS_entry* e10;
                        while (n1) {
                          e10 = n1->obj;
                          int population = e10->population;
                          int white = e10->white;
                          int asian = e10->asian;
                          int pacific = e10->pacific;
                          int blackafrican = e10->blackafrican;
                          DOUBLE_TYPE medianage = e10->medianage;
                          int occupiedhouseunits = e10->occupiedhouseunits;
                          int houseunits = e10->houseunits;
                          int families = e10->families;
                          int households = e10->households;
                          int husbwife = e10->husbwife;
                          int males = e10->males;
                          int females = e10->females;
                          int householdschildren = e10->householdschildren;
                          int hispanic = e10->hispanic;
                          long v10 = e10->__av;
                          V_locn_IIWLC1 += ((((((v6 * (v7 * Ulift<4>(subcategory, category, categorycluster, prize))) * Ulift<2>(ksn, inventoryunits)) * (v8 * Ulift<8>(rain, snow, maxtemp, mintemp, meanwind, thunder))) * Ulift<1>(dateid)) * (((v9 * Ulift<15>(rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime)) * (v10 * Ulift<28>(population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic))) * Ulift<14>(zip))) * Ulift<0>(locn));
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
          e6 = e6->nxt;
        }
      }
    }
  
  private:
    
      /* Preallocated map entries (to avoid recreation of temporary objects) */
      V_INVENTORY_entry se1;
      V_LOCATION_entry se2;
      V_CENSUS_entry se3;
      V_ITEM_entry se4;
      V_WEATHER_entry se5;
      V_CENSUS_entry se7;
      V_LOCATION_entry se8;
      V_WEATHER_entry se9;
      V_ITEM_entry se10;
    
      
    
      /* Data structures used for storing materialized views */
      V_INVENTORY_map V_INVENTORY;
      V_LOCATION_map V_LOCATION;
      V_CENSUS_map V_CENSUS;
      V_ITEM_map V_ITEM;
      V_WEATHER_map V_WEATHER;
      DELTA_INVENTORY_map DELTA_INVENTORY;
      DELTA_LOCATION_map DELTA_LOCATION;
      DELTA_CENSUS_map DELTA_CENSUS;
      DELTA_ITEM_map DELTA_ITEM;
      DELTA_WEATHER_map DELTA_WEATHER;
    
      
    
  };

  

}