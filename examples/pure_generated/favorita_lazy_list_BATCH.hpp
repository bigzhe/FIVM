#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"

#include "ring/ring_relational_opt.hpp"

#define RELATION_SALES_DYNAMIC
#define RELATION_OIL_DYNAMIC
#define RELATION_HOLIDAY_DYNAMIC
#define RELATION_TRANSACTIONS_DYNAMIC
#define RELATION_STORES_DYNAMIC
#define RELATION_ITEMS_DYNAMIC

namespace dbtoaster {

  /* Definitions of maps used for storing materialized views. */
  struct SALES_entry {
    int date; int store; int item; DOUBLE_TYPE unit_sales; int onpromotion; long __av; SALES_entry* nxt; SALES_entry* prv;
  
    explicit SALES_entry() : nxt(nullptr), prv(nullptr) { }
    explicit SALES_entry(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const int c4, const long c5) { date = c0; store = c1; item = c2; unit_sales = c3; onpromotion = c4; __av = c5;  }
    SALES_entry(const SALES_entry& other) : date(other.date), store(other.store), item(other.item), unit_sales(other.unit_sales), onpromotion(other.onpromotion), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    SALES_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        date = std::stoi(f[0]); store = std::stoi(f[1]); item = std::stoi(f[2]); unit_sales = std::stod(f[3]); onpromotion = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  
  struct OIL_entry {
    int date; DOUBLE_TYPE oilprize; long __av; OIL_entry* nxt; OIL_entry* prv;
  
    explicit OIL_entry() : nxt(nullptr), prv(nullptr) { }
    explicit OIL_entry(const int c0, const DOUBLE_TYPE c1, const long c2) { date = c0; oilprize = c1; __av = c2;  }
    OIL_entry(const OIL_entry& other) : date(other.date), oilprize(other.oilprize), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    OIL_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        date = std::stoi(f[0]); oilprize = std::stod(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  
  struct HOLIDAY_entry {
    int date; int holiday_type; int locale; int locale_id; int transferred; long __av; HOLIDAY_entry* nxt; HOLIDAY_entry* prv;
  
    explicit HOLIDAY_entry() : nxt(nullptr), prv(nullptr) { }
    explicit HOLIDAY_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const long c5) { date = c0; holiday_type = c1; locale = c2; locale_id = c3; transferred = c4; __av = c5;  }
    HOLIDAY_entry(const HOLIDAY_entry& other) : date(other.date), holiday_type(other.holiday_type), locale(other.locale), locale_id(other.locale_id), transferred(other.transferred), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    HOLIDAY_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        date = std::stoi(f[0]); holiday_type = std::stoi(f[1]); locale = std::stoi(f[2]); locale_id = std::stoi(f[3]); transferred = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  
  struct TRANSACTIONS_entry {
    int date; int store; int transactions; long __av; TRANSACTIONS_entry* nxt; TRANSACTIONS_entry* prv;
  
    explicit TRANSACTIONS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TRANSACTIONS_entry(const int c0, const int c1, const int c2, const long c3) { date = c0; store = c1; transactions = c2; __av = c3;  }
    TRANSACTIONS_entry(const TRANSACTIONS_entry& other) : date(other.date), store(other.store), transactions(other.transactions), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TRANSACTIONS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        date = std::stoi(f[0]); store = std::stoi(f[1]); transactions = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  
  struct STORES_entry {
    int store; int city; int state; int store_type; int cluster; long __av; STORES_entry* nxt; STORES_entry* prv;
  
    explicit STORES_entry() : nxt(nullptr), prv(nullptr) { }
    explicit STORES_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const long c5) { store = c0; city = c1; state = c2; store_type = c3; cluster = c4; __av = c5;  }
    STORES_entry(const STORES_entry& other) : store(other.store), city(other.city), state(other.state), store_type(other.store_type), cluster(other.cluster), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    STORES_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        store = std::stoi(f[0]); city = std::stoi(f[1]); state = std::stoi(f[2]); store_type = std::stoi(f[3]); cluster = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  
  struct ITEMS_entry {
    int item; int family; int itemclass; int perishable; long __av; ITEMS_entry* nxt; ITEMS_entry* prv;
  
    explicit ITEMS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit ITEMS_entry(const int c0, const int c1, const int c2, const int c3, const long c4) { item = c0; family = c1; itemclass = c2; perishable = c3; __av = c4;  }
    ITEMS_entry(const ITEMS_entry& other) : item(other.item), family(other.family), itemclass(other.itemclass), perishable(other.perishable), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    ITEMS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        item = std::stoi(f[0]); family = std::stoi(f[1]); itemclass = std::stoi(f[2]); perishable = std::stoi(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
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
  struct V_SALES_entry {
    int date; int store; int item; DOUBLE_TYPE unit_sales; int onpromotion; long __av; V_SALES_entry* nxt; V_SALES_entry* prv;
  
    explicit V_SALES_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_SALES_entry(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const int c4, const long c5) { date = c0; store = c1; item = c2; unit_sales = c3; onpromotion = c4; __av = c5;  }
    V_SALES_entry(const V_SALES_entry& other) : date(other.date), store(other.store), item(other.item), unit_sales(other.unit_sales), onpromotion(other.onpromotion), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_SALES_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        date = std::stoi(f[0]); store = std::stoi(f[1]); item = std::stoi(f[2]); unit_sales = std::stod(f[3]); onpromotion = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_SALES_entry& modify(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const int c4) { date = c0; store = c1; item = c2; unit_sales = c3; onpromotion = c4;  return *this; }
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
  
  struct V_SALES_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const V_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.store);
      hash_combine(h, e.item);
      hash_combine(h, e.unit_sales);
      hash_combine(h, e.onpromotion);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_SALES_entry& x, const V_SALES_entry& y) {
      return x.date == y.date && x.store == y.store && x.item == y.item && x.unit_sales == y.unit_sales && x.onpromotion == y.onpromotion;
    }
  };
  
  typedef MultiHashMap<V_SALES_entry, long, 
    PrimaryHashIndex<V_SALES_entry, V_SALES_mapkey01234_idxfn>
  > V_SALES_map;
  
  
  struct V_ITEMS_entry {
    int item; int family; int itemclass; int perishable; long __av; V_ITEMS_entry* nxt; V_ITEMS_entry* prv;
  
    explicit V_ITEMS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_ITEMS_entry(const int c0, const int c1, const int c2, const int c3, const long c4) { item = c0; family = c1; itemclass = c2; perishable = c3; __av = c4;  }
    V_ITEMS_entry(const V_ITEMS_entry& other) : item(other.item), family(other.family), itemclass(other.itemclass), perishable(other.perishable), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_ITEMS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        item = std::stoi(f[0]); family = std::stoi(f[1]); itemclass = std::stoi(f[2]); perishable = std::stoi(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_ITEMS_entry& modify(const int c0, const int c1, const int c2, const int c3) { item = c0; family = c1; itemclass = c2; perishable = c3;  return *this; }
    FORCE_INLINE V_ITEMS_entry& modify0(const int c0) { item = c0;  return *this; }
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
  
  struct V_ITEMS_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const V_ITEMS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.item);
      hash_combine(h, e.family);
      hash_combine(h, e.itemclass);
      hash_combine(h, e.perishable);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_ITEMS_entry& x, const V_ITEMS_entry& y) {
      return x.item == y.item && x.family == y.family && x.itemclass == y.itemclass && x.perishable == y.perishable;
    }
  };
  
  struct V_ITEMS_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_ITEMS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.item);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_ITEMS_entry& x, const V_ITEMS_entry& y) {
      return x.item == y.item;
    }
  };
  
  typedef MultiHashMap<V_ITEMS_entry, long, 
    PrimaryHashIndex<V_ITEMS_entry, V_ITEMS_mapkey0123_idxfn>,
    SecondaryHashIndex<V_ITEMS_entry, V_ITEMS_mapkey0_idxfn>
  > V_ITEMS_map;
  
  
  struct V_TRANSACTIONS_entry {
    int date; int store; int transactions; long __av; V_TRANSACTIONS_entry* nxt; V_TRANSACTIONS_entry* prv;
  
    explicit V_TRANSACTIONS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_TRANSACTIONS_entry(const int c0, const int c1, const int c2, const long c3) { date = c0; store = c1; transactions = c2; __av = c3;  }
    V_TRANSACTIONS_entry(const V_TRANSACTIONS_entry& other) : date(other.date), store(other.store), transactions(other.transactions), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_TRANSACTIONS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        date = std::stoi(f[0]); store = std::stoi(f[1]); transactions = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_TRANSACTIONS_entry& modify(const int c0, const int c1, const int c2) { date = c0; store = c1; transactions = c2;  return *this; }
    FORCE_INLINE V_TRANSACTIONS_entry& modify01(const int c0, const int c1) { date = c0; store = c1;  return *this; }
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
  
  struct V_TRANSACTIONS_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const V_TRANSACTIONS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.store);
      hash_combine(h, e.transactions);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_TRANSACTIONS_entry& x, const V_TRANSACTIONS_entry& y) {
      return x.date == y.date && x.store == y.store && x.transactions == y.transactions;
    }
  };
  
  struct V_TRANSACTIONS_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_TRANSACTIONS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.store);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_TRANSACTIONS_entry& x, const V_TRANSACTIONS_entry& y) {
      return x.date == y.date && x.store == y.store;
    }
  };
  
  typedef MultiHashMap<V_TRANSACTIONS_entry, long, 
    PrimaryHashIndex<V_TRANSACTIONS_entry, V_TRANSACTIONS_mapkey012_idxfn>,
    SecondaryHashIndex<V_TRANSACTIONS_entry, V_TRANSACTIONS_mapkey01_idxfn>
  > V_TRANSACTIONS_map;
  
  
  struct V_STORES_entry {
    int store; int city; int state; int store_type; int cluster; long __av; V_STORES_entry* nxt; V_STORES_entry* prv;
  
    explicit V_STORES_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_STORES_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const long c5) { store = c0; city = c1; state = c2; store_type = c3; cluster = c4; __av = c5;  }
    V_STORES_entry(const V_STORES_entry& other) : store(other.store), city(other.city), state(other.state), store_type(other.store_type), cluster(other.cluster), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_STORES_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        store = std::stoi(f[0]); city = std::stoi(f[1]); state = std::stoi(f[2]); store_type = std::stoi(f[3]); cluster = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_STORES_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4) { store = c0; city = c1; state = c2; store_type = c3; cluster = c4;  return *this; }
    FORCE_INLINE V_STORES_entry& modify0(const int c0) { store = c0;  return *this; }
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
  
  struct V_STORES_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const V_STORES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.store);
      hash_combine(h, e.city);
      hash_combine(h, e.state);
      hash_combine(h, e.store_type);
      hash_combine(h, e.cluster);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_STORES_entry& x, const V_STORES_entry& y) {
      return x.store == y.store && x.city == y.city && x.state == y.state && x.store_type == y.store_type && x.cluster == y.cluster;
    }
  };
  
  struct V_STORES_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_STORES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.store);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_STORES_entry& x, const V_STORES_entry& y) {
      return x.store == y.store;
    }
  };
  
  typedef MultiHashMap<V_STORES_entry, long, 
    PrimaryHashIndex<V_STORES_entry, V_STORES_mapkey01234_idxfn>,
    SecondaryHashIndex<V_STORES_entry, V_STORES_mapkey0_idxfn>
  > V_STORES_map;
  
  
  struct V_OIL_entry {
    int date; DOUBLE_TYPE oilprize; long __av; V_OIL_entry* nxt; V_OIL_entry* prv;
  
    explicit V_OIL_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_OIL_entry(const int c0, const DOUBLE_TYPE c1, const long c2) { date = c0; oilprize = c1; __av = c2;  }
    V_OIL_entry(const V_OIL_entry& other) : date(other.date), oilprize(other.oilprize), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_OIL_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        date = std::stoi(f[0]); oilprize = std::stod(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_OIL_entry& modify(const int c0, const DOUBLE_TYPE c1) { date = c0; oilprize = c1;  return *this; }
    FORCE_INLINE V_OIL_entry& modify0(const int c0) { date = c0;  return *this; }
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
  
  struct V_OIL_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_OIL_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.oilprize);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_OIL_entry& x, const V_OIL_entry& y) {
      return x.date == y.date && x.oilprize == y.oilprize;
    }
  };
  
  struct V_OIL_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_OIL_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_OIL_entry& x, const V_OIL_entry& y) {
      return x.date == y.date;
    }
  };
  
  typedef MultiHashMap<V_OIL_entry, long, 
    PrimaryHashIndex<V_OIL_entry, V_OIL_mapkey01_idxfn>,
    SecondaryHashIndex<V_OIL_entry, V_OIL_mapkey0_idxfn>
  > V_OIL_map;
  
  
  struct V_HOLIDAY_entry {
    int date; int holiday_type; int locale; int locale_id; int transferred; long __av; V_HOLIDAY_entry* nxt; V_HOLIDAY_entry* prv;
  
    explicit V_HOLIDAY_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_HOLIDAY_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const long c5) { date = c0; holiday_type = c1; locale = c2; locale_id = c3; transferred = c4; __av = c5;  }
    V_HOLIDAY_entry(const V_HOLIDAY_entry& other) : date(other.date), holiday_type(other.holiday_type), locale(other.locale), locale_id(other.locale_id), transferred(other.transferred), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_HOLIDAY_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        date = std::stoi(f[0]); holiday_type = std::stoi(f[1]); locale = std::stoi(f[2]); locale_id = std::stoi(f[3]); transferred = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_HOLIDAY_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4) { date = c0; holiday_type = c1; locale = c2; locale_id = c3; transferred = c4;  return *this; }
    FORCE_INLINE V_HOLIDAY_entry& modify0(const int c0) { date = c0;  return *this; }
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
  
  struct V_HOLIDAY_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const V_HOLIDAY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.holiday_type);
      hash_combine(h, e.locale);
      hash_combine(h, e.locale_id);
      hash_combine(h, e.transferred);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_HOLIDAY_entry& x, const V_HOLIDAY_entry& y) {
      return x.date == y.date && x.holiday_type == y.holiday_type && x.locale == y.locale && x.locale_id == y.locale_id && x.transferred == y.transferred;
    }
  };
  
  struct V_HOLIDAY_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_HOLIDAY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_HOLIDAY_entry& x, const V_HOLIDAY_entry& y) {
      return x.date == y.date;
    }
  };
  
  typedef MultiHashMap<V_HOLIDAY_entry, long, 
    PrimaryHashIndex<V_HOLIDAY_entry, V_HOLIDAY_mapkey01234_idxfn>,
    SecondaryHashIndex<V_HOLIDAY_entry, V_HOLIDAY_mapkey0_idxfn>
  > V_HOLIDAY_map;
  
  
  struct DELTA_SALES_entry {
    int date; int store; int item; DOUBLE_TYPE unit_sales; int onpromotion; long __av; DELTA_SALES_entry* nxt; DELTA_SALES_entry* prv;
  
    explicit DELTA_SALES_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_SALES_entry(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const int c4, const long c5) { date = c0; store = c1; item = c2; unit_sales = c3; onpromotion = c4; __av = c5;  }
    DELTA_SALES_entry(const DELTA_SALES_entry& other) : date(other.date), store(other.store), item(other.item), unit_sales(other.unit_sales), onpromotion(other.onpromotion), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_SALES_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        date = std::stoi(f[0]); store = std::stoi(f[1]); item = std::stoi(f[2]); unit_sales = std::stod(f[3]); onpromotion = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_SALES_entry& modify(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const int c4) { date = c0; store = c1; item = c2; unit_sales = c3; onpromotion = c4;  return *this; }
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
  
  struct DELTA_SALES_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.store);
      hash_combine(h, e.item);
      hash_combine(h, e.unit_sales);
      hash_combine(h, e.onpromotion);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_SALES_entry& x, const DELTA_SALES_entry& y) {
      return x.date == y.date && x.store == y.store && x.item == y.item && x.unit_sales == y.unit_sales && x.onpromotion == y.onpromotion;
    }
  };
  
  typedef MultiHashMap<DELTA_SALES_entry, long, 
    PrimaryHashIndex<DELTA_SALES_entry, DELTA_SALES_mapkey01234_idxfn>
  > DELTA_SALES_map;
  
  
  struct DELTA_OIL_entry {
    int date; DOUBLE_TYPE oilprize; long __av; DELTA_OIL_entry* nxt; DELTA_OIL_entry* prv;
  
    explicit DELTA_OIL_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_OIL_entry(const int c0, const DOUBLE_TYPE c1, const long c2) { date = c0; oilprize = c1; __av = c2;  }
    DELTA_OIL_entry(const DELTA_OIL_entry& other) : date(other.date), oilprize(other.oilprize), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_OIL_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 2) return; */
        date = std::stoi(f[0]); oilprize = std::stod(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_OIL_entry& modify(const int c0, const DOUBLE_TYPE c1) { date = c0; oilprize = c1;  return *this; }
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
  
  struct DELTA_OIL_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_OIL_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.oilprize);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_OIL_entry& x, const DELTA_OIL_entry& y) {
      return x.date == y.date && x.oilprize == y.oilprize;
    }
  };
  
  typedef MultiHashMap<DELTA_OIL_entry, long, 
    PrimaryHashIndex<DELTA_OIL_entry, DELTA_OIL_mapkey01_idxfn>
  > DELTA_OIL_map;
  
  
  struct DELTA_HOLIDAY_entry {
    int date; int holiday_type; int locale; int locale_id; int transferred; long __av; DELTA_HOLIDAY_entry* nxt; DELTA_HOLIDAY_entry* prv;
  
    explicit DELTA_HOLIDAY_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_HOLIDAY_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const long c5) { date = c0; holiday_type = c1; locale = c2; locale_id = c3; transferred = c4; __av = c5;  }
    DELTA_HOLIDAY_entry(const DELTA_HOLIDAY_entry& other) : date(other.date), holiday_type(other.holiday_type), locale(other.locale), locale_id(other.locale_id), transferred(other.transferred), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_HOLIDAY_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        date = std::stoi(f[0]); holiday_type = std::stoi(f[1]); locale = std::stoi(f[2]); locale_id = std::stoi(f[3]); transferred = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_HOLIDAY_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4) { date = c0; holiday_type = c1; locale = c2; locale_id = c3; transferred = c4;  return *this; }
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
  
  struct DELTA_HOLIDAY_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_HOLIDAY_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.holiday_type);
      hash_combine(h, e.locale);
      hash_combine(h, e.locale_id);
      hash_combine(h, e.transferred);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_HOLIDAY_entry& x, const DELTA_HOLIDAY_entry& y) {
      return x.date == y.date && x.holiday_type == y.holiday_type && x.locale == y.locale && x.locale_id == y.locale_id && x.transferred == y.transferred;
    }
  };
  
  typedef MultiHashMap<DELTA_HOLIDAY_entry, long, 
    PrimaryHashIndex<DELTA_HOLIDAY_entry, DELTA_HOLIDAY_mapkey01234_idxfn>
  > DELTA_HOLIDAY_map;
  
  
  struct DELTA_TRANSACTIONS_entry {
    int date; int store; int transactions; long __av; DELTA_TRANSACTIONS_entry* nxt; DELTA_TRANSACTIONS_entry* prv;
  
    explicit DELTA_TRANSACTIONS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_TRANSACTIONS_entry(const int c0, const int c1, const int c2, const long c3) { date = c0; store = c1; transactions = c2; __av = c3;  }
    DELTA_TRANSACTIONS_entry(const DELTA_TRANSACTIONS_entry& other) : date(other.date), store(other.store), transactions(other.transactions), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_TRANSACTIONS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 3) return; */
        date = std::stoi(f[0]); store = std::stoi(f[1]); transactions = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_TRANSACTIONS_entry& modify(const int c0, const int c1, const int c2) { date = c0; store = c1; transactions = c2;  return *this; }
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
  
  struct DELTA_TRANSACTIONS_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_TRANSACTIONS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.date);
      hash_combine(h, e.store);
      hash_combine(h, e.transactions);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_TRANSACTIONS_entry& x, const DELTA_TRANSACTIONS_entry& y) {
      return x.date == y.date && x.store == y.store && x.transactions == y.transactions;
    }
  };
  
  typedef MultiHashMap<DELTA_TRANSACTIONS_entry, long, 
    PrimaryHashIndex<DELTA_TRANSACTIONS_entry, DELTA_TRANSACTIONS_mapkey012_idxfn>
  > DELTA_TRANSACTIONS_map;
  
  
  struct DELTA_STORES_entry {
    int store; int city; int state; int store_type; int cluster; long __av; DELTA_STORES_entry* nxt; DELTA_STORES_entry* prv;
  
    explicit DELTA_STORES_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_STORES_entry(const int c0, const int c1, const int c2, const int c3, const int c4, const long c5) { store = c0; city = c1; state = c2; store_type = c3; cluster = c4; __av = c5;  }
    DELTA_STORES_entry(const DELTA_STORES_entry& other) : store(other.store), city(other.city), state(other.state), store_type(other.store_type), cluster(other.cluster), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_STORES_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        store = std::stoi(f[0]); city = std::stoi(f[1]); state = std::stoi(f[2]); store_type = std::stoi(f[3]); cluster = std::stoi(f[4]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_STORES_entry& modify(const int c0, const int c1, const int c2, const int c3, const int c4) { store = c0; city = c1; state = c2; store_type = c3; cluster = c4;  return *this; }
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
  
  struct DELTA_STORES_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_STORES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.store);
      hash_combine(h, e.city);
      hash_combine(h, e.state);
      hash_combine(h, e.store_type);
      hash_combine(h, e.cluster);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_STORES_entry& x, const DELTA_STORES_entry& y) {
      return x.store == y.store && x.city == y.city && x.state == y.state && x.store_type == y.store_type && x.cluster == y.cluster;
    }
  };
  
  typedef MultiHashMap<DELTA_STORES_entry, long, 
    PrimaryHashIndex<DELTA_STORES_entry, DELTA_STORES_mapkey01234_idxfn>
  > DELTA_STORES_map;
  
  
  struct DELTA_ITEMS_entry {
    int item; int family; int itemclass; int perishable; long __av; DELTA_ITEMS_entry* nxt; DELTA_ITEMS_entry* prv;
  
    explicit DELTA_ITEMS_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_ITEMS_entry(const int c0, const int c1, const int c2, const int c3, const long c4) { item = c0; family = c1; itemclass = c2; perishable = c3; __av = c4;  }
    DELTA_ITEMS_entry(const DELTA_ITEMS_entry& other) : item(other.item), family(other.family), itemclass(other.itemclass), perishable(other.perishable), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_ITEMS_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 4) return; */
        item = std::stoi(f[0]); family = std::stoi(f[1]); itemclass = std::stoi(f[2]); perishable = std::stoi(f[3]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_ITEMS_entry& modify(const int c0, const int c1, const int c2, const int c3) { item = c0; family = c1; itemclass = c2; perishable = c3;  return *this; }
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
  
  struct DELTA_ITEMS_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_ITEMS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.item);
      hash_combine(h, e.family);
      hash_combine(h, e.itemclass);
      hash_combine(h, e.perishable);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_ITEMS_entry& x, const DELTA_ITEMS_entry& y) {
      return x.item == y.item && x.family == y.family && x.itemclass == y.itemclass && x.perishable == y.perishable;
    }
  };
  
  typedef MultiHashMap<DELTA_ITEMS_entry, long, 
    PrimaryHashIndex<DELTA_ITEMS_entry, DELTA_ITEMS_mapkey0123_idxfn>
  > DELTA_ITEMS_map;

  

  /* Defines top-level materialized views */
  struct tlq_t {
    struct timeval t0, t; long tT, tN, tS;
    tlq_t(): tN(0), tS(0) , V_date_SITSOH1(RingRelation<0, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int>()) { 
      gettimeofday(&t0, NULL); 
    }
  
    /* Serialization code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << "\n";
      const RingRelation<0, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int>& _V_date_SITSOH1 = get_V_date_SITSOH1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_date_SITSOH1), _V_date_SITSOH1, "\t");
    }
  
    /* Functions returning / computing the results of top level queries */
    const RingRelation<0, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int>& get_V_date_SITSOH1() const {
      return V_date_SITSOH1;
    }
  
  protected:
    /* Data structures used for storing / computing top-level queries */
    RingRelation<0, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int> V_date_SITSOH1 = RingRelation<0, int, int, int, DOUBLE_TYPE, int, int, int, int, int, int, int, int, int, DOUBLE_TYPE, int, int, int, int>();
    
  };

  /* Contains materialized views and processing (IVM) logic */
  struct data_t : tlq_t {
  
    data_t(): tlq_t() {
      
      
    }
  
    
  
    
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_batch_update_SALES(const std::vector<DELTA_SALES_entry>::iterator &begin, const std::vector<DELTA_SALES_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_SALES_entry>::iterator e1 = begin; e1 != end; e1++) {
          int date = e1->date;
          int store = e1->store;
          int item = e1->item;
          DOUBLE_TYPE unit_sales = e1->unit_sales;
          int onpromotion = e1->onpromotion;
          long v1 = e1->__av;
          V_SALES.addOrDelOnZero(se1.modify(date, store, item, unit_sales, onpromotion), v1);
        }
      }
    }
    
    
    void on_batch_update_OIL(const std::vector<DELTA_OIL_entry>::iterator &begin, const std::vector<DELTA_OIL_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_OIL_entry>::iterator e2 = begin; e2 != end; e2++) {
          int date = e2->date;
          DOUBLE_TYPE oilprize = e2->oilprize;
          long v2 = e2->__av;
          V_OIL.addOrDelOnZero(se2.modify(date, oilprize), v2);
        }
      }
    }
    
    
    void on_batch_update_HOLIDAY(const std::vector<DELTA_HOLIDAY_entry>::iterator &begin, const std::vector<DELTA_HOLIDAY_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_HOLIDAY_entry>::iterator e3 = begin; e3 != end; e3++) {
          int date = e3->date;
          int holiday_type = e3->holiday_type;
          int locale = e3->locale;
          int locale_id = e3->locale_id;
          int transferred = e3->transferred;
          long v3 = e3->__av;
          V_HOLIDAY.addOrDelOnZero(se3.modify(date, holiday_type, locale, locale_id, transferred), v3);
        }
      }
    }
    
    
    void on_batch_update_TRANSACTIONS(const std::vector<DELTA_TRANSACTIONS_entry>::iterator &begin, const std::vector<DELTA_TRANSACTIONS_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_TRANSACTIONS_entry>::iterator e4 = begin; e4 != end; e4++) {
          int date = e4->date;
          int store = e4->store;
          int transactions = e4->transactions;
          long v4 = e4->__av;
          V_TRANSACTIONS.addOrDelOnZero(se4.modify(date, store, transactions), v4);
        }
      }
    }
    
    
    void on_batch_update_STORES(const std::vector<DELTA_STORES_entry>::iterator &begin, const std::vector<DELTA_STORES_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_STORES_entry>::iterator e5 = begin; e5 != end; e5++) {
          int store = e5->store;
          int city = e5->city;
          int state = e5->state;
          int store_type = e5->store_type;
          int cluster = e5->cluster;
          long v5 = e5->__av;
          V_STORES.addOrDelOnZero(se5.modify(store, city, state, store_type, cluster), v5);
        }
      }
    }
    
    
    void on_batch_update_ITEMS(const std::vector<DELTA_ITEMS_entry>::iterator &begin, const std::vector<DELTA_ITEMS_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      { //foreach
        for (std::vector<DELTA_ITEMS_entry>::iterator e6 = begin; e6 != end; e6++) {
          int item = e6->item;
          int family = e6->family;
          int itemclass = e6->itemclass;
          int perishable = e6->perishable;
          long v6 = e6->__av;
          V_ITEMS.addOrDelOnZero(se6.modify(item, family, itemclass, perishable), v6);
        }
      }
    }
    
    
    void on_system_ready_event() {
      V_date_SITSOH1.store.clear();
      { //foreach
        V_SALES_entry* e7 = V_SALES.head;
        while (e7) {
          int date = e7->date;
          int store = e7->store;
          int item = e7->item;
          DOUBLE_TYPE unit_sales = e7->unit_sales;
          int onpromotion = e7->onpromotion;
          long v7 = e7->__av;
          { //slice
            const LinkedNode<V_ITEMS_entry>* n5 = static_cast<const LinkedNode<V_ITEMS_entry>*>(V_ITEMS.slice(se12.modify0(item), 0));
            V_ITEMS_entry* e8;
            while (n5) {
              e8 = n5->obj;
              int family = e8->family;
              int itemclass = e8->itemclass;
              int perishable = e8->perishable;
              long v8 = e8->__av;
              { //slice
                const LinkedNode<V_TRANSACTIONS_entry>* n4 = static_cast<const LinkedNode<V_TRANSACTIONS_entry>*>(V_TRANSACTIONS.slice(se11.modify01(date, store), 0));
                V_TRANSACTIONS_entry* e9;
                while (n4) {
                  e9 = n4->obj;
                  int transactions = e9->transactions;
                  long v9 = e9->__av;
                  { //slice
                    const LinkedNode<V_STORES_entry>* n3 = static_cast<const LinkedNode<V_STORES_entry>*>(V_STORES.slice(se10.modify0(store), 0));
                    V_STORES_entry* e10;
                    while (n3) {
                      e10 = n3->obj;
                      int city = e10->city;
                      int state = e10->state;
                      int store_type = e10->store_type;
                      int cluster = e10->cluster;
                      long v10 = e10->__av;
                      { //slice
                        const LinkedNode<V_OIL_entry>* n2 = static_cast<const LinkedNode<V_OIL_entry>*>(V_OIL.slice(se9.modify0(date), 0));
                        V_OIL_entry* e11;
                        while (n2) {
                          e11 = n2->obj;
                          DOUBLE_TYPE oilprize = e11->oilprize;
                          long v11 = e11->__av;
                          { //slice
                            const LinkedNode<V_HOLIDAY_entry>* n1 = static_cast<const LinkedNode<V_HOLIDAY_entry>*>(V_HOLIDAY.slice(se8.modify0(date), 0));
                            V_HOLIDAY_entry* e12;
                            while (n1) {
                              e12 = n1->obj;
                              int holiday_type = e12->holiday_type;
                              int locale = e12->locale;
                              int locale_id = e12->locale_id;
                              int transferred = e12->transferred;
                              long v12 = e12->__av;
                              V_date_SITSOH1 += ((((((((v7 * (v8 * Ulift<5>(family, itemclass, perishable))) * Ulift<2>(item, unit_sales, onpromotion)) * (v9 * Ulift<8>(transactions))) * (v10 * Ulift<9>(city, state, store_type, cluster))) * Ulift<1>(store)) * (v11 * Ulift<13>(oilprize))) * (v12 * Ulift<14>(holiday_type, locale, locale_id, transferred))) * Ulift<0>(date));
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
      V_SALES_entry se1;
      V_OIL_entry se2;
      V_HOLIDAY_entry se3;
      V_TRANSACTIONS_entry se4;
      V_STORES_entry se5;
      V_ITEMS_entry se6;
      V_HOLIDAY_entry se8;
      V_OIL_entry se9;
      V_STORES_entry se10;
      V_TRANSACTIONS_entry se11;
      V_ITEMS_entry se12;
    
      
    
      /* Data structures used for storing materialized views */
      V_SALES_map V_SALES;
      V_ITEMS_map V_ITEMS;
      V_TRANSACTIONS_map V_TRANSACTIONS;
      V_STORES_map V_STORES;
      V_OIL_map V_OIL;
      V_HOLIDAY_map V_HOLIDAY;
      DELTA_SALES_map DELTA_SALES;
      DELTA_OIL_map DELTA_OIL;
      DELTA_HOLIDAY_map DELTA_HOLIDAY;
      DELTA_TRANSACTIONS_map DELTA_TRANSACTIONS;
      DELTA_STORES_map DELTA_STORES;
      DELTA_ITEMS_map DELTA_ITEMS;
    
      
    
  };

  

}