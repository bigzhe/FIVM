#include <sys/time.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"

#include "ring/ring_factorized.hpp"

#define RELATION_LINEITEM_DYNAMIC
#define RELATION_PART_DYNAMIC
#define RELATION_ORDERS_DYNAMIC
#define RELATION_PARTSUPP_DYNAMIC

namespace dbtoaster {

  /* Definitions of maps used for storing materialized views. */
  struct lineitem_entry {
    int orderkey; int partkey; int suppkey; int l_linenumber; DOUBLE_TYPE l_quantity; DOUBLE_TYPE l_extendedprice; DOUBLE_TYPE l_discount; DOUBLE_TYPE l_tax; char l_returnflag; char l_linestatus; STRING_TYPE l_shipdate; STRING_TYPE l_commitdate; STRING_TYPE l_receiptdate; STRING_TYPE l_shipinstruct; STRING_TYPE l_shipmode; STRING_TYPE l_comment; long __av; lineitem_entry* nxt; lineitem_entry* prv;
  
    explicit lineitem_entry() : nxt(nullptr), prv(nullptr) { }
    explicit lineitem_entry(const int c0, const int c1, const int c2, const int c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const char c8, const char c9, const STRING_TYPE& c10, const STRING_TYPE& c11, const STRING_TYPE& c12, const STRING_TYPE& c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const long c16) { orderkey = c0; partkey = c1; suppkey = c2; l_linenumber = c3; l_quantity = c4; l_extendedprice = c5; l_discount = c6; l_tax = c7; l_returnflag = c8; l_linestatus = c9; l_shipdate = c10; l_commitdate = c11; l_receiptdate = c12; l_shipinstruct = c13; l_shipmode = c14; l_comment = c15; __av = c16;  }
    lineitem_entry(const lineitem_entry& other) : orderkey(other.orderkey), partkey(other.partkey), suppkey(other.suppkey), l_linenumber(other.l_linenumber), l_quantity(other.l_quantity), l_extendedprice(other.l_extendedprice), l_discount(other.l_discount), l_tax(other.l_tax), l_returnflag(other.l_returnflag), l_linestatus(other.l_linestatus), l_shipdate(other.l_shipdate), l_commitdate(other.l_commitdate), l_receiptdate(other.l_receiptdate), l_shipinstruct(other.l_shipinstruct), l_shipmode(other.l_shipmode), l_comment(other.l_comment), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    lineitem_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 16) return; */
        orderkey = std::stoi(f[0]); partkey = std::stoi(f[1]); suppkey = std::stoi(f[2]); l_linenumber = std::stoi(f[3]); l_quantity = std::stod(f[4]); l_extendedprice = std::stod(f[5]); l_discount = std::stod(f[6]); l_tax = std::stod(f[7]); l_returnflag = f[8][0]; l_linestatus = f[9][0]; l_shipdate = f[10]; l_commitdate = f[11]; l_receiptdate = f[12]; l_shipinstruct = f[13]; l_shipmode = f[14]; l_comment = f[15]; __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_linenumber);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_quantity);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_extendedprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_discount);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_tax);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_returnflag);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_linestatus);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_shipdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_commitdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_receiptdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_shipinstruct);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_shipmode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct part_entry {
    int partkey; STRING_TYPE p_name; STRING_TYPE p_mfgr; STRING_TYPE p_brand; STRING_TYPE p_type; int p_size; STRING_TYPE p_container; DOUBLE_TYPE p_retailprice; STRING_TYPE p_comment; long __av; part_entry* nxt; part_entry* prv;
  
    explicit part_entry() : nxt(nullptr), prv(nullptr) { }
    explicit part_entry(const int c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const int c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8, const long c9) { partkey = c0; p_name = c1; p_mfgr = c2; p_brand = c3; p_type = c4; p_size = c5; p_container = c6; p_retailprice = c7; p_comment = c8; __av = c9;  }
    part_entry(const part_entry& other) : partkey(other.partkey), p_name(other.p_name), p_mfgr(other.p_mfgr), p_brand(other.p_brand), p_type(other.p_type), p_size(other.p_size), p_container(other.p_container), p_retailprice(other.p_retailprice), p_comment(other.p_comment), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    part_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 9) return; */
        partkey = std::stoi(f[0]); p_name = f[1]; p_mfgr = f[2]; p_brand = f[3]; p_type = f[4]; p_size = std::stoi(f[5]); p_container = f[6]; p_retailprice = std::stod(f[7]); p_comment = f[8]; __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_mfgr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_brand);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_type);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_size);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_container);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_retailprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct orders_entry {
    int orderkey; int o_custkey; char o_orderstatus; DOUBLE_TYPE o_totalprice; STRING_TYPE o_orderdate; STRING_TYPE o_orderpriority; STRING_TYPE o_clerk; int o_shippriority; STRING_TYPE o_comment; long __av; orders_entry* nxt; orders_entry* prv;
  
    explicit orders_entry() : nxt(nullptr), prv(nullptr) { }
    explicit orders_entry(const int c0, const int c1, const char c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const int c7, const STRING_TYPE& c8, const long c9) { orderkey = c0; o_custkey = c1; o_orderstatus = c2; o_totalprice = c3; o_orderdate = c4; o_orderpriority = c5; o_clerk = c6; o_shippriority = c7; o_comment = c8; __av = c9;  }
    orders_entry(const orders_entry& other) : orderkey(other.orderkey), o_custkey(other.o_custkey), o_orderstatus(other.o_orderstatus), o_totalprice(other.o_totalprice), o_orderdate(other.o_orderdate), o_orderpriority(other.o_orderpriority), o_clerk(other.o_clerk), o_shippriority(other.o_shippriority), o_comment(other.o_comment), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    orders_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 9) return; */
        orderkey = std::stoi(f[0]); o_custkey = std::stoi(f[1]); o_orderstatus = f[2][0]; o_totalprice = std::stod(f[3]); o_orderdate = f[4]; o_orderpriority = f[5]; o_clerk = f[6]; o_shippriority = std::stoi(f[7]); o_comment = f[8]; __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_custkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_orderstatus);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_totalprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_orderdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_orderpriority);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_clerk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_shippriority);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct partsupp_entry {
    int partkey; int suppkey; int ps_availqty; DOUBLE_TYPE ps_supplycost; STRING_TYPE ps_comment; long __av; partsupp_entry* nxt; partsupp_entry* prv;
  
    explicit partsupp_entry() : nxt(nullptr), prv(nullptr) { }
    explicit partsupp_entry(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const long c5) { partkey = c0; suppkey = c1; ps_availqty = c2; ps_supplycost = c3; ps_comment = c4; __av = c5;  }
    partsupp_entry(const partsupp_entry& other) : partkey(other.partkey), suppkey(other.suppkey), ps_availqty(other.ps_availqty), ps_supplycost(other.ps_supplycost), ps_comment(other.ps_comment), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    partsupp_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        partkey = std::stoi(f[0]); suppkey = std::stoi(f[1]); ps_availqty = std::stoi(f[2]); ps_supplycost = std::stod(f[3]); ps_comment = f[4]; __av = v; nxt = nullptr; prv = nullptr;
    }
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ps_availqty);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ps_supplycost);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ps_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct V_partkey_lpp1_entry {
    int orderkey; RingFactorizedRelation<1, int> __av; V_partkey_lpp1_entry* nxt; V_partkey_lpp1_entry* prv;
  
    explicit V_partkey_lpp1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_partkey_lpp1_entry(const int c0, const RingFactorizedRelation<1, int>& c1) { orderkey = c0; __av = c1;  }
    V_partkey_lpp1_entry(const V_partkey_lpp1_entry& other) : orderkey(other.orderkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_partkey_lpp1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<1, int>& v) {
        /* if (f.size() < 1) return; */
        orderkey = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_partkey_lpp1_entry& modify(const int c0) { orderkey = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_partkey_lpp1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_partkey_lpp1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_partkey_lpp1_entry& x, const V_partkey_lpp1_entry& y) {
      return x.orderkey == y.orderkey;
    }
  };
  
  typedef MultiHashMap<V_partkey_lpp1_entry, RingFactorizedRelation<1, int>, 
    PrimaryHashIndex<V_partkey_lpp1_entry, V_partkey_lpp1_mapkey0_idxfn>
  > V_partkey_lpp1_map;
  
  
  struct V_suppkey_lp1_entry {
    int orderkey; int partkey; RingFactorizedRelation<2, int> __av; V_suppkey_lp1_entry* nxt; V_suppkey_lp1_entry* prv;
  
    explicit V_suppkey_lp1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_suppkey_lp1_entry(const int c0, const int c1, const RingFactorizedRelation<2, int>& c2) { orderkey = c0; partkey = c1; __av = c2;  }
    V_suppkey_lp1_entry(const V_suppkey_lp1_entry& other) : orderkey(other.orderkey), partkey(other.partkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_suppkey_lp1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<2, int>& v) {
        /* if (f.size() < 2) return; */
        orderkey = std::stoi(f[0]); partkey = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_suppkey_lp1_entry& modify(const int c0, const int c1) { orderkey = c0; partkey = c1;  return *this; }
    FORCE_INLINE V_suppkey_lp1_entry& modify1(const int c1) { partkey = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_suppkey_lp1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_suppkey_lp1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      hash_combine(h, e.partkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_suppkey_lp1_entry& x, const V_suppkey_lp1_entry& y) {
      return x.orderkey == y.orderkey && x.partkey == y.partkey;
    }
  };
  
  struct V_suppkey_lp1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const V_suppkey_lp1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.partkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_suppkey_lp1_entry& x, const V_suppkey_lp1_entry& y) {
      return x.partkey == y.partkey;
    }
  };
  
  typedef MultiHashMap<V_suppkey_lp1_entry, RingFactorizedRelation<2, int>, 
    PrimaryHashIndex<V_suppkey_lp1_entry, V_suppkey_lp1_mapkey01_idxfn>,
    SecondaryHashIndex<V_suppkey_lp1_entry, V_suppkey_lp1_mapkey1_idxfn>
  > V_suppkey_lp1_map;
  
  
  struct V_l_quantity_l1_entry {
    int orderkey; int partkey; int suppkey; RingFactorizedRelation<3, DOUBLE_TYPE> __av; V_l_quantity_l1_entry* nxt; V_l_quantity_l1_entry* prv;
  
    explicit V_l_quantity_l1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_l_quantity_l1_entry(const int c0, const int c1, const int c2, const RingFactorizedRelation<3, DOUBLE_TYPE>& c3) { orderkey = c0; partkey = c1; suppkey = c2; __av = c3;  }
    V_l_quantity_l1_entry(const V_l_quantity_l1_entry& other) : orderkey(other.orderkey), partkey(other.partkey), suppkey(other.suppkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_l_quantity_l1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<3, DOUBLE_TYPE>& v) {
        /* if (f.size() < 3) return; */
        orderkey = std::stoi(f[0]); partkey = std::stoi(f[1]); suppkey = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_l_quantity_l1_entry& modify(const int c0, const int c1, const int c2) { orderkey = c0; partkey = c1; suppkey = c2;  return *this; }
    FORCE_INLINE V_l_quantity_l1_entry& modify12(const int c1, const int c2) { partkey = c1; suppkey = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_l_quantity_l1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const V_l_quantity_l1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      hash_combine(h, e.partkey);
      hash_combine(h, e.suppkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_l_quantity_l1_entry& x, const V_l_quantity_l1_entry& y) {
      return x.orderkey == y.orderkey && x.partkey == y.partkey && x.suppkey == y.suppkey;
    }
  };
  
  struct V_l_quantity_l1_mapkey12_idxfn {
    FORCE_INLINE static size_t hash(const V_l_quantity_l1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.partkey);
      hash_combine(h, e.suppkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_l_quantity_l1_entry& x, const V_l_quantity_l1_entry& y) {
      return x.partkey == y.partkey && x.suppkey == y.suppkey;
    }
  };
  
  typedef MultiHashMap<V_l_quantity_l1_entry, RingFactorizedRelation<3, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_l_quantity_l1_entry, V_l_quantity_l1_mapkey012_idxfn>,
    SecondaryHashIndex<V_l_quantity_l1_entry, V_l_quantity_l1_mapkey12_idxfn>
  > V_l_quantity_l1_map;
  
  
  struct V_ps_availqty_p1_entry {
    int partkey; int suppkey; RingFactorizedRelation<16, int> __av; V_ps_availqty_p1_entry* nxt; V_ps_availqty_p1_entry* prv;
  
    explicit V_ps_availqty_p1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_ps_availqty_p1_entry(const int c0, const int c1, const RingFactorizedRelation<16, int>& c2) { partkey = c0; suppkey = c1; __av = c2;  }
    V_ps_availqty_p1_entry(const V_ps_availqty_p1_entry& other) : partkey(other.partkey), suppkey(other.suppkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_ps_availqty_p1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<16, int>& v) {
        /* if (f.size() < 2) return; */
        partkey = std::stoi(f[0]); suppkey = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_ps_availqty_p1_entry& modify(const int c0, const int c1) { partkey = c0; suppkey = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_ps_availqty_p1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const V_ps_availqty_p1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.partkey);
      hash_combine(h, e.suppkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_ps_availqty_p1_entry& x, const V_ps_availqty_p1_entry& y) {
      return x.partkey == y.partkey && x.suppkey == y.suppkey;
    }
  };
  
  typedef MultiHashMap<V_ps_availqty_p1_entry, RingFactorizedRelation<16, int>, 
    PrimaryHashIndex<V_ps_availqty_p1_entry, V_ps_availqty_p1_mapkey01_idxfn>
  > V_ps_availqty_p1_map;
  
  
  struct V_p_name_p1_entry {
    int partkey; RingFactorizedRelation<19, STRING_TYPE> __av; V_p_name_p1_entry* nxt; V_p_name_p1_entry* prv;
  
    explicit V_p_name_p1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_p_name_p1_entry(const int c0, const RingFactorizedRelation<19, STRING_TYPE>& c1) { partkey = c0; __av = c1;  }
    V_p_name_p1_entry(const V_p_name_p1_entry& other) : partkey(other.partkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_p_name_p1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<19, STRING_TYPE>& v) {
        /* if (f.size() < 1) return; */
        partkey = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_p_name_p1_entry& modify(const int c0) { partkey = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_p_name_p1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_p_name_p1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.partkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_p_name_p1_entry& x, const V_p_name_p1_entry& y) {
      return x.partkey == y.partkey;
    }
  };
  
  typedef MultiHashMap<V_p_name_p1_entry, RingFactorizedRelation<19, STRING_TYPE>, 
    PrimaryHashIndex<V_p_name_p1_entry, V_p_name_p1_mapkey0_idxfn>
  > V_p_name_p1_map;
  
  
  struct V_o_totalprice_o1_entry {
    int orderkey; RingFactorizedRelation<27, DOUBLE_TYPE> __av; V_o_totalprice_o1_entry* nxt; V_o_totalprice_o1_entry* prv;
  
    explicit V_o_totalprice_o1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit V_o_totalprice_o1_entry(const int c0, const RingFactorizedRelation<27, DOUBLE_TYPE>& c1) { orderkey = c0; __av = c1;  }
    V_o_totalprice_o1_entry(const V_o_totalprice_o1_entry& other) : orderkey(other.orderkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    V_o_totalprice_o1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<27, DOUBLE_TYPE>& v) {
        /* if (f.size() < 1) return; */
        orderkey = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE V_o_totalprice_o1_entry& modify(const int c0) { orderkey = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct V_o_totalprice_o1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const V_o_totalprice_o1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const V_o_totalprice_o1_entry& x, const V_o_totalprice_o1_entry& y) {
      return x.orderkey == y.orderkey;
    }
  };
  
  typedef MultiHashMap<V_o_totalprice_o1_entry, RingFactorizedRelation<27, DOUBLE_TYPE>, 
    PrimaryHashIndex<V_o_totalprice_o1_entry, V_o_totalprice_o1_mapkey0_idxfn>
  > V_o_totalprice_o1_map;
  
  
  struct TMP_SUM1_entry {
    int orderkey; int partkey; int suppkey; RingFactorizedRelation<3, DOUBLE_TYPE> __av; TMP_SUM1_entry* nxt; TMP_SUM1_entry* prv;
  
    explicit TMP_SUM1_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM1_entry(const int c0, const int c1, const int c2, const RingFactorizedRelation<3, DOUBLE_TYPE>& c3) { orderkey = c0; partkey = c1; suppkey = c2; __av = c3;  }
    TMP_SUM1_entry(const TMP_SUM1_entry& other) : orderkey(other.orderkey), partkey(other.partkey), suppkey(other.suppkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM1_entry(const std::vector<std::string>& f, const RingFactorizedRelation<3, DOUBLE_TYPE>& v) {
        /* if (f.size() < 3) return; */
        orderkey = std::stoi(f[0]); partkey = std::stoi(f[1]); suppkey = std::stoi(f[2]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM1_entry& modify(const int c0, const int c1, const int c2) { orderkey = c0; partkey = c1; suppkey = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      hash_combine(h, e.partkey);
      hash_combine(h, e.suppkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM1_entry& x, const TMP_SUM1_entry& y) {
      return x.orderkey == y.orderkey && x.partkey == y.partkey && x.suppkey == y.suppkey;
    }
  };
  
  typedef MultiHashMap<TMP_SUM1_entry, RingFactorizedRelation<3, DOUBLE_TYPE>, 
    PrimaryHashIndex<TMP_SUM1_entry, TMP_SUM1_mapkey012_idxfn>
  > TMP_SUM1_map;
  
  
  struct TMP_SUM2_entry {
    int orderkey; int partkey; RingFactorizedRelation<2, int> __av; TMP_SUM2_entry* nxt; TMP_SUM2_entry* prv;
  
    explicit TMP_SUM2_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM2_entry(const int c0, const int c1, const RingFactorizedRelation<2, int>& c2) { orderkey = c0; partkey = c1; __av = c2;  }
    TMP_SUM2_entry(const TMP_SUM2_entry& other) : orderkey(other.orderkey), partkey(other.partkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM2_entry(const std::vector<std::string>& f, const RingFactorizedRelation<2, int>& v) {
        /* if (f.size() < 2) return; */
        orderkey = std::stoi(f[0]); partkey = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM2_entry& modify(const int c0, const int c1) { orderkey = c0; partkey = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      hash_combine(h, e.partkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM2_entry& x, const TMP_SUM2_entry& y) {
      return x.orderkey == y.orderkey && x.partkey == y.partkey;
    }
  };
  
  typedef MultiHashMap<TMP_SUM2_entry, RingFactorizedRelation<2, int>, 
    PrimaryHashIndex<TMP_SUM2_entry, TMP_SUM2_mapkey01_idxfn>
  > TMP_SUM2_map;
  
  
  struct TMP_SUM3_entry {
    int orderkey; RingFactorizedRelation<1, int> __av; TMP_SUM3_entry* nxt; TMP_SUM3_entry* prv;
  
    explicit TMP_SUM3_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM3_entry(const int c0, const RingFactorizedRelation<1, int>& c1) { orderkey = c0; __av = c1;  }
    TMP_SUM3_entry(const TMP_SUM3_entry& other) : orderkey(other.orderkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM3_entry(const std::vector<std::string>& f, const RingFactorizedRelation<1, int>& v) {
        /* if (f.size() < 1) return; */
        orderkey = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM3_entry& modify(const int c0) { orderkey = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM3_entry& x, const TMP_SUM3_entry& y) {
      return x.orderkey == y.orderkey;
    }
  };
  
  typedef MultiHashMap<TMP_SUM3_entry, RingFactorizedRelation<1, int>, 
    PrimaryHashIndex<TMP_SUM3_entry, TMP_SUM3_mapkey0_idxfn>
  > TMP_SUM3_map;
  
  
  struct TMP_SUM4_entry {
    int partkey; RingFactorizedRelation<19, STRING_TYPE> __av; TMP_SUM4_entry* nxt; TMP_SUM4_entry* prv;
  
    explicit TMP_SUM4_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM4_entry(const int c0, const RingFactorizedRelation<19, STRING_TYPE>& c1) { partkey = c0; __av = c1;  }
    TMP_SUM4_entry(const TMP_SUM4_entry& other) : partkey(other.partkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM4_entry(const std::vector<std::string>& f, const RingFactorizedRelation<19, STRING_TYPE>& v) {
        /* if (f.size() < 1) return; */
        partkey = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM4_entry& modify(const int c0) { partkey = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.partkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM4_entry& x, const TMP_SUM4_entry& y) {
      return x.partkey == y.partkey;
    }
  };
  
  typedef MultiHashMap<TMP_SUM4_entry, RingFactorizedRelation<19, STRING_TYPE>, 
    PrimaryHashIndex<TMP_SUM4_entry, TMP_SUM4_mapkey0_idxfn>
  > TMP_SUM4_map;
  
  
  struct TMP_SUM5_entry {
    int orderkey; RingFactorizedRelation<1, int> __av; TMP_SUM5_entry* nxt; TMP_SUM5_entry* prv;
  
    explicit TMP_SUM5_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM5_entry(const int c0, const RingFactorizedRelation<1, int>& c1) { orderkey = c0; __av = c1;  }
    TMP_SUM5_entry(const TMP_SUM5_entry& other) : orderkey(other.orderkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM5_entry(const std::vector<std::string>& f, const RingFactorizedRelation<1, int>& v) {
        /* if (f.size() < 1) return; */
        orderkey = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM5_entry& modify(const int c0) { orderkey = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM5_entry& x, const TMP_SUM5_entry& y) {
      return x.orderkey == y.orderkey;
    }
  };
  
  typedef MultiHashMap<TMP_SUM5_entry, RingFactorizedRelation<1, int>, 
    PrimaryHashIndex<TMP_SUM5_entry, TMP_SUM5_mapkey0_idxfn>
  > TMP_SUM5_map;
  
  
  struct TMP_SUM6_entry {
    int orderkey; RingFactorizedRelation<27, DOUBLE_TYPE> __av; TMP_SUM6_entry* nxt; TMP_SUM6_entry* prv;
  
    explicit TMP_SUM6_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM6_entry(const int c0, const RingFactorizedRelation<27, DOUBLE_TYPE>& c1) { orderkey = c0; __av = c1;  }
    TMP_SUM6_entry(const TMP_SUM6_entry& other) : orderkey(other.orderkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM6_entry(const std::vector<std::string>& f, const RingFactorizedRelation<27, DOUBLE_TYPE>& v) {
        /* if (f.size() < 1) return; */
        orderkey = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM6_entry& modify(const int c0) { orderkey = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM6_entry& x, const TMP_SUM6_entry& y) {
      return x.orderkey == y.orderkey;
    }
  };
  
  typedef MultiHashMap<TMP_SUM6_entry, RingFactorizedRelation<27, DOUBLE_TYPE>, 
    PrimaryHashIndex<TMP_SUM6_entry, TMP_SUM6_mapkey0_idxfn>
  > TMP_SUM6_map;
  
  
  struct TMP_SUM7_entry {
    int partkey; int suppkey; RingFactorizedRelation<16, int> __av; TMP_SUM7_entry* nxt; TMP_SUM7_entry* prv;
  
    explicit TMP_SUM7_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM7_entry(const int c0, const int c1, const RingFactorizedRelation<16, int>& c2) { partkey = c0; suppkey = c1; __av = c2;  }
    TMP_SUM7_entry(const TMP_SUM7_entry& other) : partkey(other.partkey), suppkey(other.suppkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM7_entry(const std::vector<std::string>& f, const RingFactorizedRelation<16, int>& v) {
        /* if (f.size() < 2) return; */
        partkey = std::stoi(f[0]); suppkey = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM7_entry& modify(const int c0, const int c1) { partkey = c0; suppkey = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM7_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.partkey);
      hash_combine(h, e.suppkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM7_entry& x, const TMP_SUM7_entry& y) {
      return x.partkey == y.partkey && x.suppkey == y.suppkey;
    }
  };
  
  typedef MultiHashMap<TMP_SUM7_entry, RingFactorizedRelation<16, int>, 
    PrimaryHashIndex<TMP_SUM7_entry, TMP_SUM7_mapkey01_idxfn>
  > TMP_SUM7_map;
  
  
  struct TMP_SUM8_entry {
    int orderkey; int partkey; RingFactorizedRelation<2, int> __av; TMP_SUM8_entry* nxt; TMP_SUM8_entry* prv;
  
    explicit TMP_SUM8_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM8_entry(const int c0, const int c1, const RingFactorizedRelation<2, int>& c2) { orderkey = c0; partkey = c1; __av = c2;  }
    TMP_SUM8_entry(const TMP_SUM8_entry& other) : orderkey(other.orderkey), partkey(other.partkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM8_entry(const std::vector<std::string>& f, const RingFactorizedRelation<2, int>& v) {
        /* if (f.size() < 2) return; */
        orderkey = std::stoi(f[0]); partkey = std::stoi(f[1]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM8_entry& modify(const int c0, const int c1) { orderkey = c0; partkey = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM8_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM8_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      hash_combine(h, e.partkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM8_entry& x, const TMP_SUM8_entry& y) {
      return x.orderkey == y.orderkey && x.partkey == y.partkey;
    }
  };
  
  typedef MultiHashMap<TMP_SUM8_entry, RingFactorizedRelation<2, int>, 
    PrimaryHashIndex<TMP_SUM8_entry, TMP_SUM8_mapkey01_idxfn>
  > TMP_SUM8_map;
  
  
  struct TMP_SUM9_entry {
    int orderkey; RingFactorizedRelation<1, int> __av; TMP_SUM9_entry* nxt; TMP_SUM9_entry* prv;
  
    explicit TMP_SUM9_entry() : nxt(nullptr), prv(nullptr) { }
    explicit TMP_SUM9_entry(const int c0, const RingFactorizedRelation<1, int>& c1) { orderkey = c0; __av = c1;  }
    TMP_SUM9_entry(const TMP_SUM9_entry& other) : orderkey(other.orderkey), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    TMP_SUM9_entry(const std::vector<std::string>& f, const RingFactorizedRelation<1, int>& v) {
        /* if (f.size() < 1) return; */
        orderkey = std::stoi(f[0]); __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE TMP_SUM9_entry& modify(const int c0) { orderkey = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct TMP_SUM9_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TMP_SUM9_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      return h;
    }
    
    FORCE_INLINE static bool equals(const TMP_SUM9_entry& x, const TMP_SUM9_entry& y) {
      return x.orderkey == y.orderkey;
    }
  };
  
  typedef MultiHashMap<TMP_SUM9_entry, RingFactorizedRelation<1, int>, 
    PrimaryHashIndex<TMP_SUM9_entry, TMP_SUM9_mapkey0_idxfn>
  > TMP_SUM9_map;
  
  
  struct DELTA_lineitem_entry {
    int orderkey; int partkey; int suppkey; int l_linenumber; DOUBLE_TYPE l_quantity; DOUBLE_TYPE l_extendedprice; DOUBLE_TYPE l_discount; DOUBLE_TYPE l_tax; char l_returnflag; char l_linestatus; STRING_TYPE l_shipdate; STRING_TYPE l_commitdate; STRING_TYPE l_receiptdate; STRING_TYPE l_shipinstruct; STRING_TYPE l_shipmode; STRING_TYPE l_comment; long __av; DELTA_lineitem_entry* nxt; DELTA_lineitem_entry* prv;
  
    explicit DELTA_lineitem_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_lineitem_entry(const int c0, const int c1, const int c2, const int c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const char c8, const char c9, const STRING_TYPE& c10, const STRING_TYPE& c11, const STRING_TYPE& c12, const STRING_TYPE& c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const long c16) { orderkey = c0; partkey = c1; suppkey = c2; l_linenumber = c3; l_quantity = c4; l_extendedprice = c5; l_discount = c6; l_tax = c7; l_returnflag = c8; l_linestatus = c9; l_shipdate = c10; l_commitdate = c11; l_receiptdate = c12; l_shipinstruct = c13; l_shipmode = c14; l_comment = c15; __av = c16;  }
    DELTA_lineitem_entry(const DELTA_lineitem_entry& other) : orderkey(other.orderkey), partkey(other.partkey), suppkey(other.suppkey), l_linenumber(other.l_linenumber), l_quantity(other.l_quantity), l_extendedprice(other.l_extendedprice), l_discount(other.l_discount), l_tax(other.l_tax), l_returnflag(other.l_returnflag), l_linestatus(other.l_linestatus), l_shipdate(other.l_shipdate), l_commitdate(other.l_commitdate), l_receiptdate(other.l_receiptdate), l_shipinstruct(other.l_shipinstruct), l_shipmode(other.l_shipmode), l_comment(other.l_comment), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_lineitem_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 16) return; */
        orderkey = std::stoi(f[0]); partkey = std::stoi(f[1]); suppkey = std::stoi(f[2]); l_linenumber = std::stoi(f[3]); l_quantity = std::stod(f[4]); l_extendedprice = std::stod(f[5]); l_discount = std::stod(f[6]); l_tax = std::stod(f[7]); l_returnflag = f[8][0]; l_linestatus = f[9][0]; l_shipdate = f[10]; l_commitdate = f[11]; l_receiptdate = f[12]; l_shipinstruct = f[13]; l_shipmode = f[14]; l_comment = f[15]; __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_lineitem_entry& modify(const int c0, const int c1, const int c2, const int c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const char c8, const char c9, const STRING_TYPE& c10, const STRING_TYPE& c11, const STRING_TYPE& c12, const STRING_TYPE& c13, const STRING_TYPE& c14, const STRING_TYPE& c15) { orderkey = c0; partkey = c1; suppkey = c2; l_linenumber = c3; l_quantity = c4; l_extendedprice = c5; l_discount = c6; l_tax = c7; l_returnflag = c8; l_linestatus = c9; l_shipdate = c10; l_commitdate = c11; l_receiptdate = c12; l_shipinstruct = c13; l_shipmode = c14; l_comment = c15;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_linenumber);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_quantity);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_extendedprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_discount);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_tax);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_returnflag);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_linestatus);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_shipdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_commitdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_receiptdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_shipinstruct);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_shipmode);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_lineitem_mapkey0123456789101112131415_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_lineitem_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      hash_combine(h, e.partkey);
      hash_combine(h, e.suppkey);
      hash_combine(h, e.l_linenumber);
      hash_combine(h, e.l_quantity);
      hash_combine(h, e.l_extendedprice);
      hash_combine(h, e.l_discount);
      hash_combine(h, e.l_tax);
      hash_combine(h, e.l_returnflag);
      hash_combine(h, e.l_linestatus);
      hash_combine(h, e.l_shipdate);
      hash_combine(h, e.l_commitdate);
      hash_combine(h, e.l_receiptdate);
      hash_combine(h, e.l_shipinstruct);
      hash_combine(h, e.l_shipmode);
      hash_combine(h, e.l_comment);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_lineitem_entry& x, const DELTA_lineitem_entry& y) {
      return x.orderkey == y.orderkey && x.partkey == y.partkey && x.suppkey == y.suppkey && x.l_linenumber == y.l_linenumber && x.l_quantity == y.l_quantity && x.l_extendedprice == y.l_extendedprice && x.l_discount == y.l_discount && x.l_tax == y.l_tax && x.l_returnflag == y.l_returnflag && x.l_linestatus == y.l_linestatus && x.l_shipdate == y.l_shipdate && x.l_commitdate == y.l_commitdate && x.l_receiptdate == y.l_receiptdate && x.l_shipinstruct == y.l_shipinstruct && x.l_shipmode == y.l_shipmode && x.l_comment == y.l_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_lineitem_entry, long, 
    PrimaryHashIndex<DELTA_lineitem_entry, DELTA_lineitem_mapkey0123456789101112131415_idxfn>
  > DELTA_lineitem_map;
  
  
  struct DELTA_part_entry {
    int partkey; STRING_TYPE p_name; STRING_TYPE p_mfgr; STRING_TYPE p_brand; STRING_TYPE p_type; int p_size; STRING_TYPE p_container; DOUBLE_TYPE p_retailprice; STRING_TYPE p_comment; long __av; DELTA_part_entry* nxt; DELTA_part_entry* prv;
  
    explicit DELTA_part_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_part_entry(const int c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const int c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8, const long c9) { partkey = c0; p_name = c1; p_mfgr = c2; p_brand = c3; p_type = c4; p_size = c5; p_container = c6; p_retailprice = c7; p_comment = c8; __av = c9;  }
    DELTA_part_entry(const DELTA_part_entry& other) : partkey(other.partkey), p_name(other.p_name), p_mfgr(other.p_mfgr), p_brand(other.p_brand), p_type(other.p_type), p_size(other.p_size), p_container(other.p_container), p_retailprice(other.p_retailprice), p_comment(other.p_comment), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_part_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 9) return; */
        partkey = std::stoi(f[0]); p_name = f[1]; p_mfgr = f[2]; p_brand = f[3]; p_type = f[4]; p_size = std::stoi(f[5]); p_container = f[6]; p_retailprice = std::stod(f[7]); p_comment = f[8]; __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_part_entry& modify(const int c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const int c5, const STRING_TYPE& c6, const DOUBLE_TYPE c7, const STRING_TYPE& c8) { partkey = c0; p_name = c1; p_mfgr = c2; p_brand = c3; p_type = c4; p_size = c5; p_container = c6; p_retailprice = c7; p_comment = c8;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_mfgr);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_brand);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_type);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_size);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_container);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_retailprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_part_mapkey012345678_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_part_entry& e) {
      size_t h = 0;
      hash_combine(h, e.partkey);
      hash_combine(h, e.p_name);
      hash_combine(h, e.p_mfgr);
      hash_combine(h, e.p_brand);
      hash_combine(h, e.p_type);
      hash_combine(h, e.p_size);
      hash_combine(h, e.p_container);
      hash_combine(h, e.p_retailprice);
      hash_combine(h, e.p_comment);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_part_entry& x, const DELTA_part_entry& y) {
      return x.partkey == y.partkey && x.p_name == y.p_name && x.p_mfgr == y.p_mfgr && x.p_brand == y.p_brand && x.p_type == y.p_type && x.p_size == y.p_size && x.p_container == y.p_container && x.p_retailprice == y.p_retailprice && x.p_comment == y.p_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_part_entry, long, 
    PrimaryHashIndex<DELTA_part_entry, DELTA_part_mapkey012345678_idxfn>
  > DELTA_part_map;
  
  
  struct DELTA_orders_entry {
    int orderkey; int o_custkey; char o_orderstatus; DOUBLE_TYPE o_totalprice; STRING_TYPE o_orderdate; STRING_TYPE o_orderpriority; STRING_TYPE o_clerk; int o_shippriority; STRING_TYPE o_comment; long __av; DELTA_orders_entry* nxt; DELTA_orders_entry* prv;
  
    explicit DELTA_orders_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_orders_entry(const int c0, const int c1, const char c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const int c7, const STRING_TYPE& c8, const long c9) { orderkey = c0; o_custkey = c1; o_orderstatus = c2; o_totalprice = c3; o_orderdate = c4; o_orderpriority = c5; o_clerk = c6; o_shippriority = c7; o_comment = c8; __av = c9;  }
    DELTA_orders_entry(const DELTA_orders_entry& other) : orderkey(other.orderkey), o_custkey(other.o_custkey), o_orderstatus(other.o_orderstatus), o_totalprice(other.o_totalprice), o_orderdate(other.o_orderdate), o_orderpriority(other.o_orderpriority), o_clerk(other.o_clerk), o_shippriority(other.o_shippriority), o_comment(other.o_comment), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_orders_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 9) return; */
        orderkey = std::stoi(f[0]); o_custkey = std::stoi(f[1]); o_orderstatus = f[2][0]; o_totalprice = std::stod(f[3]); o_orderdate = f[4]; o_orderpriority = f[5]; o_clerk = f[6]; o_shippriority = std::stoi(f[7]); o_comment = f[8]; __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_orders_entry& modify(const int c0, const int c1, const char c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const STRING_TYPE& c5, const STRING_TYPE& c6, const int c7, const STRING_TYPE& c8) { orderkey = c0; o_custkey = c1; o_orderstatus = c2; o_totalprice = c3; o_orderdate = c4; o_orderpriority = c5; o_clerk = c6; o_shippriority = c7; o_comment = c8;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_custkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_orderstatus);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_totalprice);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_orderdate);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_orderpriority);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_clerk);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_shippriority);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, o_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_orders_mapkey012345678_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_orders_entry& e) {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      hash_combine(h, e.o_custkey);
      hash_combine(h, e.o_orderstatus);
      hash_combine(h, e.o_totalprice);
      hash_combine(h, e.o_orderdate);
      hash_combine(h, e.o_orderpriority);
      hash_combine(h, e.o_clerk);
      hash_combine(h, e.o_shippriority);
      hash_combine(h, e.o_comment);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_orders_entry& x, const DELTA_orders_entry& y) {
      return x.orderkey == y.orderkey && x.o_custkey == y.o_custkey && x.o_orderstatus == y.o_orderstatus && x.o_totalprice == y.o_totalprice && x.o_orderdate == y.o_orderdate && x.o_orderpriority == y.o_orderpriority && x.o_clerk == y.o_clerk && x.o_shippriority == y.o_shippriority && x.o_comment == y.o_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_orders_entry, long, 
    PrimaryHashIndex<DELTA_orders_entry, DELTA_orders_mapkey012345678_idxfn>
  > DELTA_orders_map;
  
  
  struct DELTA_partsupp_entry {
    int partkey; int suppkey; int ps_availqty; DOUBLE_TYPE ps_supplycost; STRING_TYPE ps_comment; long __av; DELTA_partsupp_entry* nxt; DELTA_partsupp_entry* prv;
  
    explicit DELTA_partsupp_entry() : nxt(nullptr), prv(nullptr) { }
    explicit DELTA_partsupp_entry(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, const long c5) { partkey = c0; suppkey = c1; ps_availqty = c2; ps_supplycost = c3; ps_comment = c4; __av = c5;  }
    DELTA_partsupp_entry(const DELTA_partsupp_entry& other) : partkey(other.partkey), suppkey(other.suppkey), ps_availqty(other.ps_availqty), ps_supplycost(other.ps_supplycost), ps_comment(other.ps_comment), __av(other.__av), nxt(nullptr), prv(nullptr) { }
    DELTA_partsupp_entry(const std::vector<std::string>& f, const long v) {
        /* if (f.size() < 5) return; */
        partkey = std::stoi(f[0]); suppkey = std::stoi(f[1]); ps_availqty = std::stoi(f[2]); ps_supplycost = std::stod(f[3]); ps_comment = f[4]; __av = v; nxt = nullptr; prv = nullptr;
    }
    
    FORCE_INLINE DELTA_partsupp_entry& modify(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4) { partkey = c0; suppkey = c1; ps_availqty = c2; ps_supplycost = c3; ps_comment = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ps_availqty);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ps_supplycost);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ps_comment);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  
  struct DELTA_partsupp_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const DELTA_partsupp_entry& e) {
      size_t h = 0;
      hash_combine(h, e.partkey);
      hash_combine(h, e.suppkey);
      hash_combine(h, e.ps_availqty);
      hash_combine(h, e.ps_supplycost);
      hash_combine(h, e.ps_comment);
      return h;
    }
    
    FORCE_INLINE static bool equals(const DELTA_partsupp_entry& x, const DELTA_partsupp_entry& y) {
      return x.partkey == y.partkey && x.suppkey == y.suppkey && x.ps_availqty == y.ps_availqty && x.ps_supplycost == y.ps_supplycost && x.ps_comment == y.ps_comment;
    }
  };
  
  typedef MultiHashMap<DELTA_partsupp_entry, long, 
    PrimaryHashIndex<DELTA_partsupp_entry, DELTA_partsupp_mapkey01234_idxfn>
  > DELTA_partsupp_map;

  

  /* Defines top-level materialized views */
  struct tlq_t {
    struct timeval t0, t; long tT, tN, tS;
    tlq_t(): tN(0), tS(0) , V_orderkey_lppo1(RingFactorizedRelation<0, int>()) { 
      gettimeofday(&t0, NULL); 
    }
  
    /* Serialization code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
      ar << "\n";
      const RingFactorizedRelation<0, int>& _V_orderkey_lppo1 = get_V_orderkey_lppo1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_orderkey_lppo1), _V_orderkey_lppo1, "\t");
      
      ar << "\n";
      const V_partkey_lpp1_map& _V_partkey_lpp1 = get_V_partkey_lpp1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_partkey_lpp1), _V_partkey_lpp1, "\t");
      
      ar << "\n";
      const V_suppkey_lp1_map& _V_suppkey_lp1 = get_V_suppkey_lp1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_suppkey_lp1), _V_suppkey_lp1, "\t");
      
      ar << "\n";
      const V_l_quantity_l1_map& _V_l_quantity_l1 = get_V_l_quantity_l1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_l_quantity_l1), _V_l_quantity_l1, "\t");
      
      ar << "\n";
      const V_ps_availqty_p1_map& _V_ps_availqty_p1 = get_V_ps_availqty_p1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_ps_availqty_p1), _V_ps_availqty_p1, "\t");
      
      ar << "\n";
      const V_p_name_p1_map& _V_p_name_p1 = get_V_p_name_p1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_p_name_p1), _V_p_name_p1, "\t");
      
      ar << "\n";
      const V_o_totalprice_o1_map& _V_o_totalprice_o1 = get_V_o_totalprice_o1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_o_totalprice_o1), _V_o_totalprice_o1, "\t");
    }
  
    /* Functions returning / computing the results of top level queries */
    const RingFactorizedRelation<0, int>& get_V_orderkey_lppo1() const {
      return V_orderkey_lppo1;
    }
    
    const V_partkey_lpp1_map& get_V_partkey_lpp1() const {
      return V_partkey_lpp1;
    }
    
    const V_suppkey_lp1_map& get_V_suppkey_lp1() const {
      return V_suppkey_lp1;
    }
    
    const V_l_quantity_l1_map& get_V_l_quantity_l1() const {
      return V_l_quantity_l1;
    }
    
    const V_ps_availqty_p1_map& get_V_ps_availqty_p1() const {
      return V_ps_availqty_p1;
    }
    
    const V_p_name_p1_map& get_V_p_name_p1() const {
      return V_p_name_p1;
    }
    
    const V_o_totalprice_o1_map& get_V_o_totalprice_o1() const {
      return V_o_totalprice_o1;
    }
  
  protected:
    /* Data structures used for storing / computing top-level queries */
    RingFactorizedRelation<0, int> V_orderkey_lppo1;
    V_partkey_lpp1_map V_partkey_lpp1;
    V_suppkey_lp1_map V_suppkey_lp1;
    V_l_quantity_l1_map V_l_quantity_l1;
    V_ps_availqty_p1_map V_ps_availqty_p1;
    V_p_name_p1_map V_p_name_p1;
    V_o_totalprice_o1_map V_o_totalprice_o1;
    
  };

  /* Contains materialized views and processing (IVM) logic */
  struct data_t : tlq_t {
  
    data_t(): tlq_t() {
      
      
    }
  
    
  
    
  
    /* Trigger functions for table relations */
    
    
    /* Trigger functions for stream relations */
    void on_batch_update_lineitem(const std::vector<DELTA_lineitem_entry>::iterator &begin, const std::vector<DELTA_lineitem_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      TMP_SUM1.clear();
      { //foreach
        for (std::vector<DELTA_lineitem_entry>::iterator e1 = begin; e1 != end; e1++) {
          int orderkey = e1->orderkey;
          int partkey = e1->partkey;
          int suppkey = e1->suppkey;
          int l_linenumber = e1->l_linenumber;
          DOUBLE_TYPE l_quantity = e1->l_quantity;
          DOUBLE_TYPE l_extendedprice = e1->l_extendedprice;
          DOUBLE_TYPE l_discount = e1->l_discount;
          DOUBLE_TYPE l_tax = e1->l_tax;
          char l_returnflag = e1->l_returnflag;
          char l_linestatus = e1->l_linestatus;
          STRING_TYPE l_shipdate = e1->l_shipdate;
          STRING_TYPE l_commitdate = e1->l_commitdate;
          STRING_TYPE l_receiptdate = e1->l_receiptdate;
          STRING_TYPE l_shipinstruct = e1->l_shipinstruct;
          STRING_TYPE l_shipmode = e1->l_shipmode;
          STRING_TYPE l_comment = e1->l_comment;
          long v1 = e1->__av;
          TMP_SUM1.addOrDelOnZero(se1.modify(orderkey, partkey, suppkey), (v1 * Ulift<3>(l_quantity)));
        }
      }
      
      TMP_SUM2.clear();
      { //foreach
        TMP_SUM1_entry* e2 = TMP_SUM1.head;
        while (e2) {
          int orderkey = e2->orderkey;
          int partkey = e2->partkey;
          int suppkey = e2->suppkey;
          RingFactorizedRelation<3, DOUBLE_TYPE>& v2 = e2->__av;
          TMP_SUM2.addOrDelOnZero(se2.modify(orderkey, partkey), ((v2 * V_ps_availqty_p1.getValueOrDefault(se3.modify(partkey, suppkey))) * Ulift<2>(suppkey)));
          e2 = e2->nxt;
        }
      }
      
      TMP_SUM3.clear();
      { //foreach
        TMP_SUM2_entry* e3 = TMP_SUM2.head;
        while (e3) {
          int orderkey = e3->orderkey;
          int partkey = e3->partkey;
          RingFactorizedRelation<2, int>& v3 = e3->__av;
          TMP_SUM3.addOrDelOnZero(se4.modify(orderkey), ((v3 * V_p_name_p1.getValueOrDefault(se5.modify(partkey))) * Ulift<1>(partkey)));
          e3 = e3->nxt;
        }
      }
      
      { //foreach
        TMP_SUM3_entry* e4 = TMP_SUM3.head;
        while (e4) {
          int orderkey = e4->orderkey;
          RingFactorizedRelation<1, int>& v4 = e4->__av;
          V_orderkey_lppo1 += ((v4 * V_o_totalprice_o1.getValueOrDefault(se7.modify(orderkey))) * Ulift<0>(orderkey));
          e4 = e4->nxt;
        }
      }
      
      { //foreach
        TMP_SUM3_entry* e5 = TMP_SUM3.head;
        while (e5) {
          int orderkey = e5->orderkey;
          RingFactorizedRelation<1, int>& v5 = e5->__av;
          V_partkey_lpp1.addOrDelOnZero(se8.modify(orderkey), v5);
          e5 = e5->nxt;
        }
      }
      
      { //foreach
        TMP_SUM2_entry* e6 = TMP_SUM2.head;
        while (e6) {
          int orderkey = e6->orderkey;
          int partkey = e6->partkey;
          RingFactorizedRelation<2, int>& v6 = e6->__av;
          V_suppkey_lp1.addOrDelOnZero(se9.modify(orderkey, partkey), v6);
          e6 = e6->nxt;
        }
      }
      
      { //foreach
        TMP_SUM1_entry* e7 = TMP_SUM1.head;
        while (e7) {
          int orderkey = e7->orderkey;
          int partkey = e7->partkey;
          int suppkey = e7->suppkey;
          RingFactorizedRelation<3, DOUBLE_TYPE>& v7 = e7->__av;
          V_l_quantity_l1.addOrDelOnZero(se10.modify(orderkey, partkey, suppkey), v7);
          e7 = e7->nxt;
        }
      }
    }
    
    
    void on_batch_update_part(const std::vector<DELTA_part_entry>::iterator &begin, const std::vector<DELTA_part_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      TMP_SUM4.clear();
      { //foreach
        for (std::vector<DELTA_part_entry>::iterator e8 = begin; e8 != end; e8++) {
          int partkey = e8->partkey;
          STRING_TYPE p_name = e8->p_name;
          STRING_TYPE p_mfgr = e8->p_mfgr;
          STRING_TYPE p_brand = e8->p_brand;
          STRING_TYPE p_type = e8->p_type;
          int p_size = e8->p_size;
          STRING_TYPE p_container = e8->p_container;
          DOUBLE_TYPE p_retailprice = e8->p_retailprice;
          STRING_TYPE p_comment = e8->p_comment;
          long v8 = e8->__av;
          TMP_SUM4.addOrDelOnZero(se11.modify(partkey), (v8 * Ulift<19>(p_name)));
        }
      }
      
      TMP_SUM5.clear();
      { //foreach
        TMP_SUM4_entry* e9 = TMP_SUM4.head;
        while (e9) {
          int partkey = e9->partkey;
          RingFactorizedRelation<19, STRING_TYPE>& v9 = e9->__av;
          { //slice
            const LinkedNode<V_suppkey_lp1_entry>* n1 = static_cast<const LinkedNode<V_suppkey_lp1_entry>*>(V_suppkey_lp1.slice(se13.modify1(partkey), 0));
            V_suppkey_lp1_entry* e10;
            while (n1) {
              e10 = n1->obj;
              int orderkey = e10->orderkey;
              RingFactorizedRelation<2, int>& v10 = e10->__av;
              TMP_SUM5.addOrDelOnZero(se12.modify(orderkey), ((v9 * v10) * Ulift<1>(partkey)));
              n1 = n1->next;
            }
          }
          e9 = e9->nxt;
        }
      }
      
      { //foreach
        TMP_SUM5_entry* e11 = TMP_SUM5.head;
        while (e11) {
          int orderkey = e11->orderkey;
          RingFactorizedRelation<1, int>& v11 = e11->__av;
          V_orderkey_lppo1 += ((v11 * V_o_totalprice_o1.getValueOrDefault(se15.modify(orderkey))) * Ulift<0>(orderkey));
          e11 = e11->nxt;
        }
      }
      
      { //foreach
        TMP_SUM5_entry* e12 = TMP_SUM5.head;
        while (e12) {
          int orderkey = e12->orderkey;
          RingFactorizedRelation<1, int>& v12 = e12->__av;
          V_partkey_lpp1.addOrDelOnZero(se16.modify(orderkey), v12);
          e12 = e12->nxt;
        }
      }
      
      { //foreach
        TMP_SUM4_entry* e13 = TMP_SUM4.head;
        while (e13) {
          int partkey = e13->partkey;
          RingFactorizedRelation<19, STRING_TYPE>& v13 = e13->__av;
          V_p_name_p1.addOrDelOnZero(se17.modify(partkey), v13);
          e13 = e13->nxt;
        }
      }
    }
    
    
    void on_batch_update_orders(const std::vector<DELTA_orders_entry>::iterator &begin, const std::vector<DELTA_orders_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      TMP_SUM6.clear();
      { //foreach
        for (std::vector<DELTA_orders_entry>::iterator e14 = begin; e14 != end; e14++) {
          int orderkey = e14->orderkey;
          int o_custkey = e14->o_custkey;
          char o_orderstatus = e14->o_orderstatus;
          DOUBLE_TYPE o_totalprice = e14->o_totalprice;
          STRING_TYPE o_orderdate = e14->o_orderdate;
          STRING_TYPE o_orderpriority = e14->o_orderpriority;
          STRING_TYPE o_clerk = e14->o_clerk;
          int o_shippriority = e14->o_shippriority;
          STRING_TYPE o_comment = e14->o_comment;
          long v14 = e14->__av;
          TMP_SUM6.addOrDelOnZero(se18.modify(orderkey), (v14 * Ulift<27>(o_totalprice)));
        }
      }
      
      { //foreach
        TMP_SUM6_entry* e15 = TMP_SUM6.head;
        while (e15) {
          int orderkey = e15->orderkey;
          RingFactorizedRelation<27, DOUBLE_TYPE>& v15 = e15->__av;
          V_orderkey_lppo1 += ((v15 * V_partkey_lpp1.getValueOrDefault(se20.modify(orderkey))) * Ulift<0>(orderkey));
          e15 = e15->nxt;
        }
      }
      
      { //foreach
        TMP_SUM6_entry* e16 = TMP_SUM6.head;
        while (e16) {
          int orderkey = e16->orderkey;
          RingFactorizedRelation<27, DOUBLE_TYPE>& v16 = e16->__av;
          V_o_totalprice_o1.addOrDelOnZero(se21.modify(orderkey), v16);
          e16 = e16->nxt;
        }
      }
    }
    
    
    void on_batch_update_partsupp(const std::vector<DELTA_partsupp_entry>::iterator &begin, const std::vector<DELTA_partsupp_entry>::iterator &end) {
      long batchSize = std::distance(begin, end);
      
      tN += batchSize;
      TMP_SUM7.clear();
      { //foreach
        for (std::vector<DELTA_partsupp_entry>::iterator e17 = begin; e17 != end; e17++) {
          int partkey = e17->partkey;
          int suppkey = e17->suppkey;
          int ps_availqty = e17->ps_availqty;
          DOUBLE_TYPE ps_supplycost = e17->ps_supplycost;
          STRING_TYPE ps_comment = e17->ps_comment;
          long v17 = e17->__av;
          TMP_SUM7.addOrDelOnZero(se22.modify(partkey, suppkey), (v17 * Ulift<16>(ps_availqty)));
        }
      }
      
      TMP_SUM8.clear();
      { //foreach
        TMP_SUM7_entry* e18 = TMP_SUM7.head;
        while (e18) {
          int partkey = e18->partkey;
          int suppkey = e18->suppkey;
          RingFactorizedRelation<16, int>& v18 = e18->__av;
          { //slice
            const LinkedNode<V_l_quantity_l1_entry>* n2 = static_cast<const LinkedNode<V_l_quantity_l1_entry>*>(V_l_quantity_l1.slice(se24.modify12(partkey, suppkey), 0));
            V_l_quantity_l1_entry* e19;
            while (n2) {
              e19 = n2->obj;
              int orderkey = e19->orderkey;
              RingFactorizedRelation<3, DOUBLE_TYPE>& v19 = e19->__av;
              TMP_SUM8.addOrDelOnZero(se23.modify(orderkey, partkey), ((v18 * v19) * Ulift<2>(suppkey)));
              n2 = n2->next;
            }
          }
          e18 = e18->nxt;
        }
      }
      
      TMP_SUM9.clear();
      { //foreach
        TMP_SUM8_entry* e20 = TMP_SUM8.head;
        while (e20) {
          int orderkey = e20->orderkey;
          int partkey = e20->partkey;
          RingFactorizedRelation<2, int>& v20 = e20->__av;
          TMP_SUM9.addOrDelOnZero(se25.modify(orderkey), ((v20 * V_p_name_p1.getValueOrDefault(se26.modify(partkey))) * Ulift<1>(partkey)));
          e20 = e20->nxt;
        }
      }
      
      { //foreach
        TMP_SUM9_entry* e21 = TMP_SUM9.head;
        while (e21) {
          int orderkey = e21->orderkey;
          RingFactorizedRelation<1, int>& v21 = e21->__av;
          V_orderkey_lppo1 += ((v21 * V_o_totalprice_o1.getValueOrDefault(se28.modify(orderkey))) * Ulift<0>(orderkey));
          e21 = e21->nxt;
        }
      }
      
      { //foreach
        TMP_SUM9_entry* e22 = TMP_SUM9.head;
        while (e22) {
          int orderkey = e22->orderkey;
          RingFactorizedRelation<1, int>& v22 = e22->__av;
          V_partkey_lpp1.addOrDelOnZero(se29.modify(orderkey), v22);
          e22 = e22->nxt;
        }
      }
      
      { //foreach
        TMP_SUM8_entry* e23 = TMP_SUM8.head;
        while (e23) {
          int orderkey = e23->orderkey;
          int partkey = e23->partkey;
          RingFactorizedRelation<2, int>& v23 = e23->__av;
          V_suppkey_lp1.addOrDelOnZero(se30.modify(orderkey, partkey), v23);
          e23 = e23->nxt;
        }
      }
      
      { //foreach
        TMP_SUM7_entry* e24 = TMP_SUM7.head;
        while (e24) {
          int partkey = e24->partkey;
          int suppkey = e24->suppkey;
          RingFactorizedRelation<16, int>& v24 = e24->__av;
          V_ps_availqty_p1.addOrDelOnZero(se31.modify(partkey, suppkey), v24);
          e24 = e24->nxt;
        }
      }
    }
    
    
    void on_system_ready_event() {
      
    }
  
  private:
    
      /* Preallocated map entries (to avoid recreation of temporary objects) */
      TMP_SUM1_entry se1;
      TMP_SUM2_entry se2;
      V_ps_availqty_p1_entry se3;
      TMP_SUM3_entry se4;
      V_p_name_p1_entry se5;
      V_o_totalprice_o1_entry se7;
      V_partkey_lpp1_entry se8;
      V_suppkey_lp1_entry se9;
      V_l_quantity_l1_entry se10;
      TMP_SUM4_entry se11;
      TMP_SUM5_entry se12;
      V_suppkey_lp1_entry se13;
      V_o_totalprice_o1_entry se15;
      V_partkey_lpp1_entry se16;
      V_p_name_p1_entry se17;
      TMP_SUM6_entry se18;
      V_partkey_lpp1_entry se20;
      V_o_totalprice_o1_entry se21;
      TMP_SUM7_entry se22;
      TMP_SUM8_entry se23;
      V_l_quantity_l1_entry se24;
      TMP_SUM9_entry se25;
      V_p_name_p1_entry se26;
      V_o_totalprice_o1_entry se28;
      V_partkey_lpp1_entry se29;
      V_suppkey_lp1_entry se30;
      V_ps_availqty_p1_entry se31;
    
      
    
      /* Data structures used for storing materialized views */
      TMP_SUM1_map TMP_SUM1;
      TMP_SUM2_map TMP_SUM2;
      TMP_SUM3_map TMP_SUM3;
      TMP_SUM4_map TMP_SUM4;
      TMP_SUM5_map TMP_SUM5;
      TMP_SUM6_map TMP_SUM6;
      TMP_SUM7_map TMP_SUM7;
      TMP_SUM8_map TMP_SUM8;
      TMP_SUM9_map TMP_SUM9;
      DELTA_lineitem_map DELTA_lineitem;
      DELTA_part_map DELTA_part;
      DELTA_orders_map DELTA_orders;
      DELTA_partsupp_map DELTA_partsupp;
    
      
    
  };

  

}