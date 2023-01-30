#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"

#include "ring/ring_factorized.hpp"

#define RELATION_SALES_STATIC
#define RELATION_OIL_STATIC
#define RELATION_HOLIDAY_STATIC
#define RELATION_TRANSACTIONS_STATIC
#define RELATION_STORES_STATIC
#define RELATION_ITEMS_STATIC

namespace dbtoaster {

  /* Definitions of maps used for storing materialized views. */
  struct V_store_SITS1_entry {
    int date; RingFactorizedRelation<1, int> __av; V_store_SITS1_entry* nxt; V_store_SITS1_entry* prv;
  
    explicit V_store_SITS1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_store_SITS1_entry(const int c0, const RingFactorizedRelation<1, int>& c1) { date = c0; __av = c1;  }
    V_store_SITS1_entry(const V_store_SITS1_entry& other) : date(other.date), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_store_SITS1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<1, int>& v) {
        /* if (f.size() < 1) return; */
        date = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_store_SITS1_entry& modify(const int c0) { date = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_store_SITS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_store_SITS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_store_SITS1_entry& x, const V_store_SITS1_entry& y) {
      return x.date == y.date;
    }
  };
  
  typedef MultiHashMap<V_store_SITS1_entry, RingFactorizedRelation<1, int>, 
    PrimaryHashIndex<V_store_SITS1_entry, V_store_SITS1_mapkey0_idxfn>
  > V_store_SITS1_map;
  
  
  struct V_item_SI1_entry {
    int date; int store; RingFactorizedRelation<2, int, DOUBLE_TYPE, int> __av; V_item_SI1_entry* nxt; V_item_SI1_entry* prv;
  
    explicit V_item_SI1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_item_SI1_entry(const int c0, const int c1, const RingFactorizedRelation<2, int, DOUBLE_TYPE, int>& c2) { date = c0; store = c1; __av = c2;  }
    V_item_SI1_entry(const V_item_SI1_entry& other) : date(other.date), store(other.store), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_item_SI1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<2, int, DOUBLE_TYPE, int>& v) {
        /* if (f.size() < 2) return; */
        date = std::stoi(f[0]); store = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_item_SI1_entry& modify(const int c0, const int c1) { date = c0; store = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_item_SI1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_item_SI1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.store);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_item_SI1_entry& x, const V_item_SI1_entry& y) {
      return x.date == y.date && x.store == y.store;
    }
  };
  
  typedef MultiHashMap<V_item_SI1_entry, RingFactorizedRelation<2, int, DOUBLE_TYPE, int>, 
    PrimaryHashIndex<V_item_SI1_entry, V_item_SI1_mapkey01_idxfn>
  > V_item_SI1_map;
  
  
  struct V_family_I1_entry {
    int item; RingFactorizedRelation<5, int, int, int> __av; V_family_I1_entry* nxt; V_family_I1_entry* prv;
  
    explicit V_family_I1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_family_I1_entry(const int c0, const RingFactorizedRelation<5, int, int, int>& c1) { item = c0; __av = c1;  }
    V_family_I1_entry(const V_family_I1_entry& other) : item(other.item), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_family_I1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<5, int, int, int>& v) {
        /* if (f.size() < 1) return; */
        item = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_family_I1_entry& modify(const int c0) { item = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_family_I1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_family_I1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.item);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_family_I1_entry& x, const V_family_I1_entry& y) {
      return x.item == y.item;
    }
  };
  
  typedef MultiHashMap<V_family_I1_entry, RingFactorizedRelation<5, int, int, int>, 
    PrimaryHashIndex<V_family_I1_entry, V_family_I1_mapkey0_idxfn>
  > V_family_I1_map;
  
  
  struct V_transactions_T1_entry {
    int date; int store; RingFactorizedRelation<8, int> __av; V_transactions_T1_entry* nxt; V_transactions_T1_entry* prv;
  
    explicit V_transactions_T1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_transactions_T1_entry(const int c0, const int c1, const RingFactorizedRelation<8, int>& c2) { date = c0; store = c1; __av = c2;  }
    V_transactions_T1_entry(const V_transactions_T1_entry& other) : date(other.date), store(other.store), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_transactions_T1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<8, int>& v) {
        /* if (f.size() < 2) return; */
        date = std::stoi(f[0]); store = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_transactions_T1_entry& modify(const int c0, const int c1) { date = c0; store = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_transactions_T1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_transactions_T1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.store);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_transactions_T1_entry& x, const V_transactions_T1_entry& y) {
      return x.date == y.date && x.store == y.store;
    }
  };
  
  typedef MultiHashMap<V_transactions_T1_entry, RingFactorizedRelation<8, int>, 
    PrimaryHashIndex<V_transactions_T1_entry, V_transactions_T1_mapkey01_idxfn>
  > V_transactions_T1_map;
  
  
  struct V_city_S1_entry {
    int store; RingFactorizedRelation<9, int, int, int, int> __av; V_city_S1_entry* nxt; V_city_S1_entry* prv;
  
    explicit V_city_S1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_city_S1_entry(const int c0, const RingFactorizedRelation<9, int, int, int, int>& c1) { store = c0; __av = c1;  }
    V_city_S1_entry(const V_city_S1_entry& other) : store(other.store), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_city_S1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<9, int, int, int, int>& v) {
        /* if (f.size() < 1) return; */
        store = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_city_S1_entry& modify(const int c0) { store = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_city_S1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_city_S1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.store);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_city_S1_entry& x, const V_city_S1_entry& y) {
      return x.store == y.store;
    }
  };
  
  typedef MultiHashMap<V_city_S1_entry, RingFactorizedRelation<9, int, int, int, int>, 
    PrimaryHashIndex<V_city_S1_entry, V_city_S1_mapkey0_idxfn>
  > V_city_S1_map;
  
  
  struct V_oilprize_O1_entry {
    int date; RingFactorizedRelation<13, DOUBLE_TYPE> __av; V_oilprize_O1_entry* nxt; V_oilprize_O1_entry* prv;
  
    explicit V_oilprize_O1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_oilprize_O1_entry(const int c0, const RingFactorizedRelation<13, DOUBLE_TYPE>& c1) { date = c0; __av = c1;  }
    V_oilprize_O1_entry(const V_oilprize_O1_entry& other) : date(other.date), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_oilprize_O1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<13, DOUBLE_TYPE>& v) {
        /* if (f.size() < 1) return; */
        date = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_oilprize_O1_entry& modify(const int c0) { date = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_oilprize_O1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_oilprize_O1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_oilprize_O1_entry& x, const V_oilprize_O1_entry& y) {
      return x.date == y.date;
    }
  };
  
  typedef MultiHashMap<V_oilprize_O1_entry, RingFactorizedRelation<13, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_oilprize_O1_entry, V_oilprize_O1_mapkey0_idxfn>
  > V_oilprize_O1_map;
  
  
  struct V_holiday_type_H1_entry {
    int date; RingFactorizedRelation<14, int, int, int, int> __av; V_holiday_type_H1_entry* nxt; V_holiday_type_H1_entry* prv;
  
    explicit V_holiday_type_H1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_holiday_type_H1_entry(const int c0, const RingFactorizedRelation<14, int, int, int, int>& c1) { date = c0; __av = c1;  }
    V_holiday_type_H1_entry(const V_holiday_type_H1_entry& other) : date(other.date), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_holiday_type_H1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<14, int, int, int, int>& v) {
        /* if (f.size() < 1) return; */
        date = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_holiday_type_H1_entry& modify(const int c0) { date = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_holiday_type_H1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_holiday_type_H1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_holiday_type_H1_entry& x, const V_holiday_type_H1_entry& y) {
      return x.date == y.date;
    }
  };
  
  typedef MultiHashMap<V_holiday_type_H1_entry, RingFactorizedRelation<14, int, int, int, int>, 
    PrimaryHashIndex<V_holiday_type_H1_entry, V_holiday_type_H1_mapkey0_idxfn>
  > V_holiday_type_H1_map;
  
  
  struct SALES_entry {
    int date; int store; int item; DOUBLE_TYPE unit_sales; int onpromotion; long __av; SALES_entry* nxt; SALES_entry* prv;
  
    explicit SALES_entry() : nxt(nullptr), prv(nullptr) { }
    explicit SALES_entry(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const int c4, const long c5) { date = c0; store = c1; item = c2; unit_sales = c3; onpromotion = c4; __av = c5;  }
    SALES_entry(const SALES_entry& other) : date(other.date), store(other.store), item(other.item), unit_sales(other.unit_sales), onpromotion(other.onpromotion), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    SALES_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        date = std::stoi(f[0]); store = std::stoi(f[1]); item = std::stoi(f[2]); unit_sales = std::stod(f[3]); onpromotion = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE SALES_entry& modify(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const int c4) { date = c0; store = c1; item = c2; unit_sales = c3; onpromotion = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, unit_sales);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, onpromotion);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct SALES_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.store);
      hash_combine(h, e.item);
      hash_combine(h, e.unit_sales);
      hash_combine(h, e.onpromotion);
      return h;
    }
    
    FORCE_INLINE static bool equals(const SALES_entry& x, const SALES_entry& y) {
      return x.date == y.date && x.store == y.store && x.item == y.item && x.unit_sales == y.unit_sales && x.onpromotion == y.onpromotion;
    }
  };
  
  typedef MultiHashMap<SALES_entry, long, 
    PrimaryHashIndex<SALES_entry, SALES_mapkey01234_idxfn>
  > SALES_map;
  
  
  struct OIL_entry {
    int date; DOUBLE_TYPE oilprize; long __av; OIL_entry* nxt; OIL_entry* prv;
  
    explicit OIL_entry() : nxt(nullptr), prv(nullptr) { }
    explicit OIL_entry(const int c0, const DOUBLE_TYPE c1, const long c2) { date = c0; oilprize = c1; __av = c2;  }
    OIL_entry(const OIL_entry& other) : date(other.date), oilprize(other.oilprize), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    OIL_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        date = std::stoi(f[0]); oilprize = std::stod(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE OIL_entry& modify(const int c0, const DOUBLE_TYPE c1) { date = c0; oilprize = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, oilprize);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct OIL_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const OIL_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.oilprize);
      return h;
    }
    
    FORCE_INLINE static bool equals(const OIL_entry& x, const OIL_entry& y) {
      return x.date == y.date && x.oilprize == y.oilprize;
    }
  };
  
  typedef MultiHashMap<OIL_entry, long, 
    PrimaryHashIndex<OIL_entry, OIL_mapkey01_idxfn>
  > OIL_map;
  
  
  struct HOLIDAY_entry {
    int date; int holiday_type; int locale; int locale_id; int transferred; long __av; HOLIDAY_entry* nxt; HOLIDAY_entry* prv;
  
    explicit HOLIDAY_entry() : nxt(nullptr), prv(nullptr) { }
    explicit HOLIDAY_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const long c5) { date = c0; holiday_type = c1; locale = c2; locale_id = c3; transferred = c4; __av = c5;  }
    HOLIDAY_entry(const HOLIDAY_entry& other) : date(other.date), holiday_type(other.holiday_type), locale(other.locale), locale_id(other.locale_id), transferred(other.transferred), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    HOLIDAY_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        date = std::stoi(f[0]); holiday_type = std::stoi(f[1]); locale = std::stoi(f[2]); locale_id = std::stoi(f[3]); transferred = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE HOLIDAY_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4) { date = c0; holiday_type = c1; locale = c2; locale_id = c3; transferred = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, holiday_type);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locale);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, locale_id);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, transferred);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct HOLIDAY_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const HOLIDAY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.holiday_type);
      hash_combine(h, e.locale);
      hash_combine(h, e.locale_id);
      hash_combine(h, e.transferred);
      return h;
    }
    
    FORCE_INLINE static bool equals(const HOLIDAY_entry& x, const HOLIDAY_entry& y) {
      return x.date == y.date && x.holiday_type == y.holiday_type && x.locale == y.locale && x.locale_id == y.locale_id && x.transferred == y.transferred;
    }
  };
  
  typedef MultiHashMap<HOLIDAY_entry, long, 
    PrimaryHashIndex<HOLIDAY_entry, HOLIDAY_mapkey01234_idxfn>
  > HOLIDAY_map;
  
  
  struct TRANSACTIONS_entry {
    int date; int store; int transactions; long __av; TRANSACTIONS_entry* nxt; TRANSACTIONS_entry* prv;
  
    explicit TRANSACTIONS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TRANSACTIONS_entry(const int c0, const int c1, const int c2, const long c3) { date = c0; store = c1; transactions = c2; __av = c3;  }
    TRANSACTIONS_entry(const TRANSACTIONS_entry& other) : date(other.date), store(other.store), transactions(other.transactions), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TRANSACTIONS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        date = std::stoi(f[0]); store = std::stoi(f[1]); transactions = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TRANSACTIONS_entry& modify(const int c0, const int c1, const int c2) { date = c0; store = c1; transactions = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, date);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, transactions);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TRANSACTIONS_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TRANSACTIONS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.store);
      hash_combine(h, e.transactions);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TRANSACTIONS_entry& x, const TRANSACTIONS_entry& y) {
      return x.date == y.date && x.store == y.store && x.transactions == y.transactions;
    }
  };
  
  typedef MultiHashMap<TRANSACTIONS_entry, long, 
    PrimaryHashIndex<TRANSACTIONS_entry, TRANSACTIONS_mapkey012_idxfn>
  > TRANSACTIONS_map;
  
  
  struct STORES_entry {
    int store; int city; int state; int store_type; int cluster; long __av; STORES_entry* nxt; STORES_entry* prv;
  
    explicit STORES_entry() : nxt(nullptr), prv(nullptr) { }
    explicit STORES_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const long c5) { store = c0; city = c1; state = c2; store_type = c3; cluster = c4; __av = c5;  }
    STORES_entry(const STORES_entry& other) : store(other.store), city(other.city), state(other.state), store_type(other.store_type), cluster(other.cluster), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    STORES_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        store = std::stoi(f[0]); city = std::stoi(f[1]); state = std::stoi(f[2]); store_type = std::stoi(f[3]); cluster = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE STORES_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4) { store = c0; city = c1; state = c2; store_type = c3; cluster = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, city);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, state);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, store_type);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, cluster);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct STORES_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const STORES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.store);
      hash_combine(h, e.city);
      hash_combine(h, e.state);
      hash_combine(h, e.store_type);
      hash_combine(h, e.cluster);
      return h;
    }
    
    FORCE_INLINE static bool equals(const STORES_entry& x, const STORES_entry& y) {
      return x.store == y.store && x.city == y.city && x.state == y.state && x.store_type == y.store_type && x.cluster == y.cluster;
    }
  };
  
  typedef MultiHashMap<STORES_entry, long, 
    PrimaryHashIndex<STORES_entry, STORES_mapkey01234_idxfn>
  > STORES_map;
  
  
  struct ITEMS_entry {
    int item; int family; int itemclass; int perishable; long __av; ITEMS_entry* nxt; ITEMS_entry* prv;
  
    explicit ITEMS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit ITEMS_entry(const int c0, const int c1, const int c2, const int c3, const long c4) { item = c0; family = c1; itemclass = c2; perishable = c3; __av = c4;  }
    ITEMS_entry(const ITEMS_entry& other) : item(other.item), family(other.family), itemclass(other.itemclass), perishable(other.perishable), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    ITEMS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        item = std::stoi(f[0]); family = std::stoi(f[1]); itemclass = std::stoi(f[2]); perishable = std::stoi(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE ITEMS_entry& modify(const int c0, const int c1, const int c2, const int c3) { item = c0; family = c1; itemclass = c2; perishable = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, item);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, family);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, itemclass);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, perishable);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct ITEMS_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const ITEMS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.item);
      hash_combine(h, e.family);
      hash_combine(h, e.itemclass);
      hash_combine(h, e.perishable);
      return h;
    }
    
    FORCE_INLINE static bool equals(const ITEMS_entry& x, const ITEMS_entry& y) {
      return x.item == y.item && x.family == y.family && x.itemclass == y.itemclass && x.perishable == y.perishable;
    }
  };
  
  typedef MultiHashMap<ITEMS_entry, long, 
    PrimaryHashIndex<ITEMS_entry, ITEMS_mapkey0123_idxfn>
  > ITEMS_map;

  

  /* Defines top-level materialized views */
  struct tlq_t {
    struct timeval t0, t; long tT, tN, tS;
    tlq_t(): tN(0), tS(0) , V_date_SITSOH1(RingFactorizedRelation<0, int>()) { 
      gettimeofday(&t0, NULL); 
    }
  
    /* Serialization code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << "\n";
      const RingFactorizedRelation<0, int>& _V_date_SITSOH1 = get_V_date_SITSOH1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_date_SITSOH1), _V_date_SITSOH1, "\t");
      
      ar << "\n";
      const V_store_SITS1_map& _V_store_SITS1 = get_V_store_SITS1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_store_SITS1), _V_store_SITS1, "\t");
      
      ar << "\n";
      const V_item_SI1_map& _V_item_SI1 = get_V_item_SI1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_item_SI1), _V_item_SI1, "\t");
      
      ar << "\n";
      const V_family_I1_map& _V_family_I1 = get_V_family_I1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_family_I1), _V_family_I1, "\t");
      
      ar << "\n";
      const V_transactions_T1_map& _V_transactions_T1 = get_V_transactions_T1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_transactions_T1), _V_transactions_T1, "\t");
      
      ar << "\n";
      const V_city_S1_map& _V_city_S1 = get_V_city_S1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_city_S1), _V_city_S1, "\t");
      
      ar << "\n";
      const V_oilprize_O1_map& _V_oilprize_O1 = get_V_oilprize_O1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_oilprize_O1), _V_oilprize_O1, "\t");
      
      ar << "\n";
      const V_holiday_type_H1_map& _V_holiday_type_H1 = get_V_holiday_type_H1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_holiday_type_H1), _V_holiday_type_H1, "\t");
    }
  
    /* Functions returning / computing the results of top level queries */
    const RingFactorizedRelation<0, int>& get_V_date_SITSOH1() const {
      return V_date_SITSOH1;
    }
    
    const V_store_SITS1_map& get_V_store_SITS1() const {
      return V_store_SITS1;
    }
    
    const V_item_SI1_map& get_V_item_SI1() const {
      return V_item_SI1;
    }
    
    const V_family_I1_map& get_V_family_I1() const {
      return V_family_I1;
    }
    
    const V_transactions_T1_map& get_V_transactions_T1() const {
      return V_transactions_T1;
    }
    
    const V_city_S1_map& get_V_city_S1() const {
      return V_city_S1;
    }
    
    const V_oilprize_O1_map& get_V_oilprize_O1() const {
      return V_oilprize_O1;
    }
    
    const V_holiday_type_H1_map& get_V_holiday_type_H1() const {
      return V_holiday_type_H1;
    }
  
  protected:
    /* Data structures used for storing / computing top-level queries */
    RingFactorizedRelation<0, int> V_date_SITSOH1;
    V_store_SITS1_map V_store_SITS1;
    V_item_SI1_map V_item_SI1;
    V_family_I1_map V_family_I1;
    V_transactions_T1_map V_transactions_T1;
    V_city_S1_map V_city_S1;
    V_oilprize_O1_map V_oilprize_O1;
    V_holiday_type_H1_map V_holiday_type_H1;
    
  };

  /* Contains materialized views and processing (IVM) logic */
  struct data_t : tlq_t {
  
    data_t(): tlq_t() {
      
      
    }
  
    
  
    
  
    /* Trigger functions for table relations */
    void on_insert_SALES(const int date, const int store, const int item, const DOUBLE_TYPE unit_sales, const int onpromotion) {
      SALES_entry entry1(date, store, item, unit_sales, onpromotion, 1);
      SALES.addOrDelOnZero(entry1, 1);
    }
    void on_insert_SALES(SALES_entry &e) {
      e.__av = 1;
      SALES.addOrDelOnZero(e, 1);
    }
    
    void on_insert_OIL(const int date, const DOUBLE_TYPE oilprize) {
      OIL_entry entry2(date, oilprize, 1);
      OIL.addOrDelOnZero(entry2, 1);
    }
    void on_insert_OIL(OIL_entry &e) {
      e.__av = 1;
      OIL.addOrDelOnZero(e, 1);
    }
    
    void on_insert_HOLIDAY(const int date, const int holiday_type, const int locale, const int locale_id, const int transferred) {
      HOLIDAY_entry entry3(date, holiday_type, locale, locale_id, transferred, 1);
      HOLIDAY.addOrDelOnZero(entry3, 1);
    }
    void on_insert_HOLIDAY(HOLIDAY_entry &e) {
      e.__av = 1;
      HOLIDAY.addOrDelOnZero(e, 1);
    }
    
    void on_insert_TRANSACTIONS(const int date, const int store, const int transactions) {
      TRANSACTIONS_entry entry4(date, store, transactions, 1);
      TRANSACTIONS.addOrDelOnZero(entry4, 1);
    }
    void on_insert_TRANSACTIONS(TRANSACTIONS_entry &e) {
      e.__av = 1;
      TRANSACTIONS.addOrDelOnZero(e, 1);
    }
    
    void on_insert_STORES(const int store, const int city, const int state, const int store_type, const int cluster) {
      STORES_entry entry5(store, city, state, store_type, cluster, 1);
      STORES.addOrDelOnZero(entry5, 1);
    }
    void on_insert_STORES(STORES_entry &e) {
      e.__av = 1;
      STORES.addOrDelOnZero(e, 1);
    }
    
    void on_insert_ITEMS(const int item, const int family, const int itemclass, const int perishable) {
      ITEMS_entry entry6(item, family, itemclass, perishable, 1);
      ITEMS.addOrDelOnZero(entry6, 1);
    }
    void on_insert_ITEMS(ITEMS_entry &e) {
      e.__av = 1;
      ITEMS.addOrDelOnZero(e, 1);
    }
    
    
    /* Trigger functions for stream relations */
    void on_system_ready_event() {
      V_family_I1.clear();
      { //foreach
        ITEMS_entry* e1 = ITEMS.head;
        while (e1) {
          int item = e1->item;
          int family = e1->family;
          int itemclass = e1->itemclass;
          int perishable = e1->perishable;
          long v1 = e1->__av;
          V_family_I1.addOrDelOnZero(se1.modify(item), (v1 * Ulift<5>(family, itemclass, perishable)));
          e1 = e1->nxt;
        }
      }
      
      V_transactions_T1.clear();
      { //foreach
        TRANSACTIONS_entry* e3 = TRANSACTIONS.head;
        while (e3) {
          int date = e3->date;
          int store = e3->store;
          int transactions = e3->transactions;
          long v3 = e3->__av;
          V_transactions_T1.addOrDelOnZero(se4.modify(date, store), (v3 * Ulift<8>(transactions)));
          e3 = e3->nxt;
        }
      }
      
      V_city_S1.clear();
      { //foreach
        STORES_entry* e4 = STORES.head;
        while (e4) {
          int store = e4->store;
          int city = e4->city;
          int state = e4->state;
          int store_type = e4->store_type;
          int cluster = e4->cluster;
          long v4 = e4->__av;
          V_city_S1.addOrDelOnZero(se5.modify(store), (v4 * Ulift<9>(city, state, store_type, cluster)));
          e4 = e4->nxt;
        }
      }
      
      V_oilprize_O1.clear();
      { //foreach
        OIL_entry* e6 = OIL.head;
        while (e6) {
          int date = e6->date;
          DOUBLE_TYPE oilprize = e6->oilprize;
          long v6 = e6->__av;
          V_oilprize_O1.addOrDelOnZero(se9.modify(date), (v6 * Ulift<13>(oilprize)));
          e6 = e6->nxt;
        }
      }
      
      V_holiday_type_H1.clear();
      { //foreach
        HOLIDAY_entry* e7 = HOLIDAY.head;
        while (e7) {
          int date = e7->date;
          int holiday_type = e7->holiday_type;
          int locale = e7->locale;
          int locale_id = e7->locale_id;
          int transferred = e7->transferred;
          long v7 = e7->__av;
          V_holiday_type_H1.addOrDelOnZero(se10.modify(date), (v7 * Ulift<14>(holiday_type, locale, locale_id, transferred)));
          e7 = e7->nxt;
        }
      }
      
    }
  
  private:
    
      /* Preallocated map entries (to avoid recreation of temporary objects) */
      V_family_I1_entry se1;
      V_item_SI1_entry se2;
      V_family_I1_entry se3;
      V_transactions_T1_entry se4;
      V_city_S1_entry se5;
      V_store_SITS1_entry se6;
      V_transactions_T1_entry se7;
      V_city_S1_entry se8;
      V_oilprize_O1_entry se9;
      V_holiday_type_H1_entry se10;
      V_oilprize_O1_entry se12;
      V_holiday_type_H1_entry se13;
    
      
    
      /* Data structures used for storing materialized views */
      SALES_map SALES;
      OIL_map OIL;
      HOLIDAY_map HOLIDAY;
      TRANSACTIONS_map TRANSACTIONS;
      STORES_map STORES;
      ITEMS_map ITEMS;
    
      
    
  };

  

}