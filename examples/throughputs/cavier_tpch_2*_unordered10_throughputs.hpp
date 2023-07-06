#include <sys/time.h>
#include <sys/resource.h>
#include <vector>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "mmap.hpp"
#include "serialization.hpp"
#include "stopwatch.hpp"

#include "ring/ring_factorized.hpp"

#define RELATION_ORDERS_DYNAMIC
#define RELATION_LINEITEM_DYNAMIC
#define RELATION_PARTSUPP_DYNAMIC
#define RELATION_PART_DYNAMIC
#define RELATION_Q2_DYNAMIC

namespace dbtoaster
{

  /* Definitions of maps used for storing materialized views. */
  struct orders_entry
  {
    int orderkey;
    int custkey;
    STRING_TYPE o_orderstatus;
    DOUBLE_TYPE o_totalprice;
    STRING_TYPE o_orderdate;
    STRING_TYPE o_orderpriority;
    STRING_TYPE o_clerk;
    int o_shippriority;
    STRING_TYPE o_comment;
    long __av;
    orders_entry *nxt;
    orders_entry *prv;

    explicit orders_entry() : nxt(nullptr), prv(nullptr) {}
    explicit orders_entry(const int c0, const int c1, const STRING_TYPE &c2, const DOUBLE_TYPE c3, const STRING_TYPE &c4, const STRING_TYPE &c5, const STRING_TYPE &c6, const int c7, const STRING_TYPE &c8, const long c9)
    {
      orderkey = c0;
      custkey = c1;
      o_orderstatus = c2;
      o_totalprice = c3;
      o_orderdate = c4;
      o_orderpriority = c5;
      o_clerk = c6;
      o_shippriority = c7;
      o_comment = c8;
      __av = c9;
    }
    orders_entry(const orders_entry &other) : orderkey(other.orderkey), custkey(other.custkey), o_orderstatus(other.o_orderstatus), o_totalprice(other.o_totalprice), o_orderdate(other.o_orderdate), o_orderpriority(other.o_orderpriority), o_clerk(other.o_clerk), o_shippriority(other.o_shippriority), o_comment(other.o_comment), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    orders_entry(const std::vector<std::string> &f, const long v)
    {
      /* if (f.size() < 9) return; */
      orderkey = std::stoi(f[0]);
      custkey = std::stoi(f[1]);
      o_orderstatus = f[2];
      o_totalprice = std::stod(f[3]);
      o_orderdate = f[4];
      o_orderpriority = f[5];
      o_clerk = f[6];
      o_shippriority = std::stoi(f[7]);
      o_comment = f[8];
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, custkey);
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

  struct lineitem_entry
  {
    int orderkey;
    int partkey;
    int suppkey;
    int l_linenumber;
    DOUBLE_TYPE l_quantity;
    DOUBLE_TYPE l_extendedprice;
    DOUBLE_TYPE l_discount;
    DOUBLE_TYPE l_tax;
    STRING_TYPE l_returnflag;
    STRING_TYPE l_linestatus;
    STRING_TYPE l_shipdate;
    STRING_TYPE l_commitdate;
    STRING_TYPE l_receiptdate;
    STRING_TYPE l_shipinstruct;
    STRING_TYPE l_shipmode;
    STRING_TYPE l_comment;
    long __av;
    lineitem_entry *nxt;
    lineitem_entry *prv;

    explicit lineitem_entry() : nxt(nullptr), prv(nullptr) {}
    explicit lineitem_entry(const int c0, const int c1, const int c2, const int c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const STRING_TYPE &c8, const STRING_TYPE &c9, const STRING_TYPE &c10, const STRING_TYPE &c11, const STRING_TYPE &c12, const STRING_TYPE &c13, const STRING_TYPE &c14, const STRING_TYPE &c15, const long c16)
    {
      orderkey = c0;
      partkey = c1;
      suppkey = c2;
      l_linenumber = c3;
      l_quantity = c4;
      l_extendedprice = c5;
      l_discount = c6;
      l_tax = c7;
      l_returnflag = c8;
      l_linestatus = c9;
      l_shipdate = c10;
      l_commitdate = c11;
      l_receiptdate = c12;
      l_shipinstruct = c13;
      l_shipmode = c14;
      l_comment = c15;
      __av = c16;
    }
    lineitem_entry(const lineitem_entry &other) : orderkey(other.orderkey), partkey(other.partkey), suppkey(other.suppkey), l_linenumber(other.l_linenumber), l_quantity(other.l_quantity), l_extendedprice(other.l_extendedprice), l_discount(other.l_discount), l_tax(other.l_tax), l_returnflag(other.l_returnflag), l_linestatus(other.l_linestatus), l_shipdate(other.l_shipdate), l_commitdate(other.l_commitdate), l_receiptdate(other.l_receiptdate), l_shipinstruct(other.l_shipinstruct), l_shipmode(other.l_shipmode), l_comment(other.l_comment), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    lineitem_entry(const std::vector<std::string> &f, const long v)
    {
      /* if (f.size() < 16) return; */
      orderkey = std::stoi(f[0]);
      partkey = std::stoi(f[1]);
      suppkey = std::stoi(f[2]);
      l_linenumber = std::stoi(f[3]);
      l_quantity = std::stod(f[4]);
      l_extendedprice = std::stod(f[5]);
      l_discount = std::stod(f[6]);
      l_tax = std::stod(f[7]);
      l_returnflag = f[8];
      l_linestatus = f[9];
      l_shipdate = f[10];
      l_commitdate = f[11];
      l_receiptdate = f[12];
      l_shipinstruct = f[13];
      l_shipmode = f[14];
      l_comment = f[15];
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
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

  struct partsupp_entry
  {
    int partkey;
    int suppkey;
    int ps_availqty;
    DOUBLE_TYPE ps_supplycost;
    STRING_TYPE ps_comment;
    long __av;
    partsupp_entry *nxt;
    partsupp_entry *prv;

    explicit partsupp_entry() : nxt(nullptr), prv(nullptr) {}
    explicit partsupp_entry(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const STRING_TYPE &c4, const long c5)
    {
      partkey = c0;
      suppkey = c1;
      ps_availqty = c2;
      ps_supplycost = c3;
      ps_comment = c4;
      __av = c5;
    }
    partsupp_entry(const partsupp_entry &other) : partkey(other.partkey), suppkey(other.suppkey), ps_availqty(other.ps_availqty), ps_supplycost(other.ps_supplycost), ps_comment(other.ps_comment), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    partsupp_entry(const std::vector<std::string> &f, const long v)
    {
      /* if (f.size() < 5) return; */
      partkey = std::stoi(f[0]);
      suppkey = std::stoi(f[1]);
      ps_availqty = std::stoi(f[2]);
      ps_supplycost = std::stod(f[3]);
      ps_comment = f[4];
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
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

  struct part_entry
  {
    int partkey;
    STRING_TYPE p_name;
    STRING_TYPE p_mfgr;
    STRING_TYPE p_brand;
    STRING_TYPE p_type;
    int p_size;
    STRING_TYPE p_container;
    DOUBLE_TYPE p_retailprice;
    STRING_TYPE p_comment;
    long __av;
    part_entry *nxt;
    part_entry *prv;

    explicit part_entry() : nxt(nullptr), prv(nullptr) {}
    explicit part_entry(const int c0, const STRING_TYPE &c1, const STRING_TYPE &c2, const STRING_TYPE &c3, const STRING_TYPE &c4, const int c5, const STRING_TYPE &c6, const DOUBLE_TYPE c7, const STRING_TYPE &c8, const long c9)
    {
      partkey = c0;
      p_name = c1;
      p_mfgr = c2;
      p_brand = c3;
      p_type = c4;
      p_size = c5;
      p_container = c6;
      p_retailprice = c7;
      p_comment = c8;
      __av = c9;
    }
    part_entry(const part_entry &other) : partkey(other.partkey), p_name(other.p_name), p_mfgr(other.p_mfgr), p_brand(other.p_brand), p_type(other.p_type), p_size(other.p_size), p_container(other.p_container), p_retailprice(other.p_retailprice), p_comment(other.p_comment), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    part_entry(const std::vector<std::string> &f, const long v)
    {
      /* if (f.size() < 9) return; */
      partkey = std::stoi(f[0]);
      p_name = f[1];
      p_mfgr = f[2];
      p_brand = f[3];
      p_type = f[4];
      p_size = std::stoi(f[5]);
      p_container = f[6];
      p_retailprice = std::stod(f[7]);
      p_comment = f[8];
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
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

  struct Q2_entry
  {
    STRING_TYPE p_name;
    int ps_availqty;
    DOUBLE_TYPE l_quantity;
    int partkey;
    int suppkey;
    int orderkey;
    long __av;
    Q2_entry *nxt;
    Q2_entry *prv;

    explicit Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit Q2_entry(const STRING_TYPE &c0, const int c1, const DOUBLE_TYPE c2, const int c3, const int c4, const int c5, const long c6)
    {
      p_name = c0;
      ps_availqty = c1;
      l_quantity = c2;
      partkey = c3;
      suppkey = c4;
      orderkey = c5;
      __av = c6;
    }
    Q2_entry(const Q2_entry &other) : p_name(other.p_name), ps_availqty(other.ps_availqty), l_quantity(other.l_quantity), partkey(other.partkey), suppkey(other.suppkey), orderkey(other.orderkey), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    Q2_entry(const std::vector<std::string> &f, const long v)
    {
      /* if (f.size() < 6) return; */
      p_name = f[0];
      ps_availqty = std::stoi(f[1]);
      l_quantity = std::stod(f[2]);
      partkey = std::stoi(f[3]);
      suppkey = std::stoi(f[4]);
      orderkey = std::stoi(f[5]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ps_availqty);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_quantity);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct V_orders_Q1_entry
  {
    int ORDERKEY;
    RingFactorizedRelation<1, DOUBLE_TYPE> __av;
    V_orders_Q1_entry *nxt;
    V_orders_Q1_entry *prv;

    explicit V_orders_Q1_entry() : nxt(nullptr), prv(nullptr) {}
    explicit V_orders_Q1_entry(const int c0, const RingFactorizedRelation<1, DOUBLE_TYPE> &c1)
    {
      ORDERKEY = c0;
      __av = c1;
    }
    V_orders_Q1_entry(const V_orders_Q1_entry &other) : ORDERKEY(other.ORDERKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    V_orders_Q1_entry(const std::vector<std::string> &f, const RingFactorizedRelation<1, DOUBLE_TYPE> &v)
    {
      /* if (f.size() < 1) return; */
      ORDERKEY = std::stoi(f[0]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE V_orders_Q1_entry &modify(const int c0)
    {
      ORDERKEY = c0;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct V_orders_Q1_mapkey0_idxfn
  {
    FORCE_INLINE static size_t hash(const V_orders_Q1_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.ORDERKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const V_orders_Q1_entry &x, const V_orders_Q1_entry &y)
    {
      return x.ORDERKEY == y.ORDERKEY;
    }
  };

  typedef MultiHashMap<V_orders_Q1_entry, RingFactorizedRelation<1, DOUBLE_TYPE>,
                       PrimaryHashIndex<V_orders_Q1_entry, V_orders_Q1_mapkey0_idxfn>>
      V_orders_Q1_map;

  struct V_Q2_Q1_entry
  {
    int ORDERKEY;
    RingFactorizedRelation<2, STRING_TYPE, DOUBLE_TYPE, int, int, int> __av;
    V_Q2_Q1_entry *nxt;
    V_Q2_Q1_entry *prv;

    explicit V_Q2_Q1_entry() : nxt(nullptr), prv(nullptr) {}
    explicit V_Q2_Q1_entry(const int c0, const RingFactorizedRelation<2, STRING_TYPE, DOUBLE_TYPE, int, int, int> &c1)
    {
      ORDERKEY = c0;
      __av = c1;
    }
    V_Q2_Q1_entry(const V_Q2_Q1_entry &other) : ORDERKEY(other.ORDERKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    V_Q2_Q1_entry(const std::vector<std::string> &f, const RingFactorizedRelation<2, STRING_TYPE, DOUBLE_TYPE, int, int, int> &v)
    {
      /* if (f.size() < 1) return; */
      ORDERKEY = std::stoi(f[0]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE V_Q2_Q1_entry &modify(const int c0)
    {
      ORDERKEY = c0;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct V_Q2_Q1_mapkey0_idxfn
  {
    FORCE_INLINE static size_t hash(const V_Q2_Q1_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.ORDERKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const V_Q2_Q1_entry &x, const V_Q2_Q1_entry &y)
    {
      return x.ORDERKEY == y.ORDERKEY;
    }
  };

  typedef MultiHashMap<V_Q2_Q1_entry, RingFactorizedRelation<2, STRING_TYPE, DOUBLE_TYPE, int, int, int>,
                       PrimaryHashIndex<V_Q2_Q1_entry, V_Q2_Q1_mapkey0_idxfn>>
      V_Q2_Q1_map;

  struct V_lineitempartsupp_Q2_entry
  {
    int PARTKEY;
    RingFactorizedRelation<8, int> __av;
    V_lineitempartsupp_Q2_entry *nxt;
    V_lineitempartsupp_Q2_entry *prv;

    explicit V_lineitempartsupp_Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit V_lineitempartsupp_Q2_entry(const int c0, const RingFactorizedRelation<8, int> &c1)
    {
      PARTKEY = c0;
      __av = c1;
    }
    V_lineitempartsupp_Q2_entry(const V_lineitempartsupp_Q2_entry &other) : PARTKEY(other.PARTKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    V_lineitempartsupp_Q2_entry(const std::vector<std::string> &f, const RingFactorizedRelation<8, int> &v)
    {
      /* if (f.size() < 1) return; */
      PARTKEY = std::stoi(f[0]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE V_lineitempartsupp_Q2_entry &modify(const int c0)
    {
      PARTKEY = c0;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct V_lineitempartsupp_Q2_mapkey0_idxfn
  {
    FORCE_INLINE static size_t hash(const V_lineitempartsupp_Q2_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.PARTKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const V_lineitempartsupp_Q2_entry &x, const V_lineitempartsupp_Q2_entry &y)
    {
      return x.PARTKEY == y.PARTKEY;
    }
  };

  typedef MultiHashMap<V_lineitempartsupp_Q2_entry, RingFactorizedRelation<8, int>,
                       PrimaryHashIndex<V_lineitempartsupp_Q2_entry, V_lineitempartsupp_Q2_mapkey0_idxfn>>
      V_lineitempartsupp_Q2_map;

  struct V_partsupp_Q2_entry
  {
    int PARTKEY;
    int SUPPKEY;
    RingFactorizedRelation<9, int> __av;
    V_partsupp_Q2_entry *nxt;
    V_partsupp_Q2_entry *prv;

    explicit V_partsupp_Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit V_partsupp_Q2_entry(const int c0, const int c1, const RingFactorizedRelation<9, int> &c2)
    {
      PARTKEY = c0;
      SUPPKEY = c1;
      __av = c2;
    }
    V_partsupp_Q2_entry(const V_partsupp_Q2_entry &other) : PARTKEY(other.PARTKEY), SUPPKEY(other.SUPPKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    V_partsupp_Q2_entry(const std::vector<std::string> &f, const RingFactorizedRelation<9, int> &v)
    {
      /* if (f.size() < 2) return; */
      PARTKEY = std::stoi(f[0]);
      SUPPKEY = std::stoi(f[1]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE V_partsupp_Q2_entry &modify(const int c0, const int c1)
    {
      PARTKEY = c0;
      SUPPKEY = c1;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct V_partsupp_Q2_mapkey01_idxfn
  {
    FORCE_INLINE static size_t hash(const V_partsupp_Q2_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.PARTKEY);
      hash_combine(h, e.SUPPKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const V_partsupp_Q2_entry &x, const V_partsupp_Q2_entry &y)
    {
      return x.PARTKEY == y.PARTKEY && x.SUPPKEY == y.SUPPKEY;
    }
  };

  typedef MultiHashMap<V_partsupp_Q2_entry, RingFactorizedRelation<9, int>,
                       PrimaryHashIndex<V_partsupp_Q2_entry, V_partsupp_Q2_mapkey01_idxfn>>
      V_partsupp_Q2_map;

  struct V_lineitem_Q2_entry
  {
    int PARTKEY;
    int SUPPKEY;
    RingFactorizedRelation<10, int, DOUBLE_TYPE> __av;
    V_lineitem_Q2_entry *nxt;
    V_lineitem_Q2_entry *prv;

    explicit V_lineitem_Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit V_lineitem_Q2_entry(const int c0, const int c1, const RingFactorizedRelation<10, int, DOUBLE_TYPE> &c2)
    {
      PARTKEY = c0;
      SUPPKEY = c1;
      __av = c2;
    }
    V_lineitem_Q2_entry(const V_lineitem_Q2_entry &other) : PARTKEY(other.PARTKEY), SUPPKEY(other.SUPPKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    V_lineitem_Q2_entry(const std::vector<std::string> &f, const RingFactorizedRelation<10, int, DOUBLE_TYPE> &v)
    {
      /* if (f.size() < 2) return; */
      PARTKEY = std::stoi(f[0]);
      SUPPKEY = std::stoi(f[1]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE V_lineitem_Q2_entry &modify(const int c0, const int c1)
    {
      PARTKEY = c0;
      SUPPKEY = c1;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct V_lineitem_Q2_mapkey01_idxfn
  {
    FORCE_INLINE static size_t hash(const V_lineitem_Q2_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.PARTKEY);
      hash_combine(h, e.SUPPKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const V_lineitem_Q2_entry &x, const V_lineitem_Q2_entry &y)
    {
      return x.PARTKEY == y.PARTKEY && x.SUPPKEY == y.SUPPKEY;
    }
  };

  typedef MultiHashMap<V_lineitem_Q2_entry, RingFactorizedRelation<10, int, DOUBLE_TYPE>,
                       PrimaryHashIndex<V_lineitem_Q2_entry, V_lineitem_Q2_mapkey01_idxfn>>
      V_lineitem_Q2_map;

  struct V_part_Q2_entry
  {
    int PARTKEY;
    RingFactorizedRelation<12, STRING_TYPE> __av;
    V_part_Q2_entry *nxt;
    V_part_Q2_entry *prv;

    explicit V_part_Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit V_part_Q2_entry(const int c0, const RingFactorizedRelation<12, STRING_TYPE> &c1)
    {
      PARTKEY = c0;
      __av = c1;
    }
    V_part_Q2_entry(const V_part_Q2_entry &other) : PARTKEY(other.PARTKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    V_part_Q2_entry(const std::vector<std::string> &f, const RingFactorizedRelation<12, STRING_TYPE> &v)
    {
      /* if (f.size() < 1) return; */
      PARTKEY = std::stoi(f[0]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE V_part_Q2_entry &modify(const int c0)
    {
      PARTKEY = c0;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct V_part_Q2_mapkey0_idxfn
  {
    FORCE_INLINE static size_t hash(const V_part_Q2_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.PARTKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const V_part_Q2_entry &x, const V_part_Q2_entry &y)
    {
      return x.PARTKEY == y.PARTKEY;
    }
  };

  typedef MultiHashMap<V_part_Q2_entry, RingFactorizedRelation<12, STRING_TYPE>,
                       PrimaryHashIndex<V_part_Q2_entry, V_part_Q2_mapkey0_idxfn>>
      V_part_Q2_map;

  struct TMP_orders_V_orders_Q1_entry
  {
    int ORDERKEY;
    RingFactorizedRelation<1, DOUBLE_TYPE> __av;
    TMP_orders_V_orders_Q1_entry *nxt;
    TMP_orders_V_orders_Q1_entry *prv;

    explicit TMP_orders_V_orders_Q1_entry() : nxt(nullptr), prv(nullptr) {}
    explicit TMP_orders_V_orders_Q1_entry(const int c0, const RingFactorizedRelation<1, DOUBLE_TYPE> &c1)
    {
      ORDERKEY = c0;
      __av = c1;
    }
    TMP_orders_V_orders_Q1_entry(const TMP_orders_V_orders_Q1_entry &other) : ORDERKEY(other.ORDERKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    TMP_orders_V_orders_Q1_entry(const std::vector<std::string> &f, const RingFactorizedRelation<1, DOUBLE_TYPE> &v)
    {
      /* if (f.size() < 1) return; */
      ORDERKEY = std::stoi(f[0]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE TMP_orders_V_orders_Q1_entry &modify(const int c0)
    {
      ORDERKEY = c0;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct TMP_orders_V_orders_Q1_mapkey0_idxfn
  {
    FORCE_INLINE static size_t hash(const TMP_orders_V_orders_Q1_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.ORDERKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const TMP_orders_V_orders_Q1_entry &x, const TMP_orders_V_orders_Q1_entry &y)
    {
      return x.ORDERKEY == y.ORDERKEY;
    }
  };

  typedef MultiHashMap<TMP_orders_V_orders_Q1_entry, RingFactorizedRelation<1, DOUBLE_TYPE>,
                       PrimaryHashIndex<TMP_orders_V_orders_Q1_entry, TMP_orders_V_orders_Q1_mapkey0_idxfn>>
      TMP_orders_V_orders_Q1_map;

  struct TMP_Q2_V_Q2_Q1_entry
  {
    int ORDERKEY;
    RingFactorizedRelation<2, STRING_TYPE, DOUBLE_TYPE, int, int, int> __av;
    TMP_Q2_V_Q2_Q1_entry *nxt;
    TMP_Q2_V_Q2_Q1_entry *prv;

    explicit TMP_Q2_V_Q2_Q1_entry() : nxt(nullptr), prv(nullptr) {}
    explicit TMP_Q2_V_Q2_Q1_entry(const int c0, const RingFactorizedRelation<2, STRING_TYPE, DOUBLE_TYPE, int, int, int> &c1)
    {
      ORDERKEY = c0;
      __av = c1;
    }
    TMP_Q2_V_Q2_Q1_entry(const TMP_Q2_V_Q2_Q1_entry &other) : ORDERKEY(other.ORDERKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    TMP_Q2_V_Q2_Q1_entry(const std::vector<std::string> &f, const RingFactorizedRelation<2, STRING_TYPE, DOUBLE_TYPE, int, int, int> &v)
    {
      /* if (f.size() < 1) return; */
      ORDERKEY = std::stoi(f[0]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE TMP_Q2_V_Q2_Q1_entry &modify(const int c0)
    {
      ORDERKEY = c0;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct TMP_Q2_V_Q2_Q1_mapkey0_idxfn
  {
    FORCE_INLINE static size_t hash(const TMP_Q2_V_Q2_Q1_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.ORDERKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const TMP_Q2_V_Q2_Q1_entry &x, const TMP_Q2_V_Q2_Q1_entry &y)
    {
      return x.ORDERKEY == y.ORDERKEY;
    }
  };

  typedef MultiHashMap<TMP_Q2_V_Q2_Q1_entry, RingFactorizedRelation<2, STRING_TYPE, DOUBLE_TYPE, int, int, int>,
                       PrimaryHashIndex<TMP_Q2_V_Q2_Q1_entry, TMP_Q2_V_Q2_Q1_mapkey0_idxfn>>
      TMP_Q2_V_Q2_Q1_map;

  struct TMP_partsupp_V_partsupp_Q2_entry
  {
    int PARTKEY;
    int SUPPKEY;
    RingFactorizedRelation<9, int> __av;
    TMP_partsupp_V_partsupp_Q2_entry *nxt;
    TMP_partsupp_V_partsupp_Q2_entry *prv;

    explicit TMP_partsupp_V_partsupp_Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit TMP_partsupp_V_partsupp_Q2_entry(const int c0, const int c1, const RingFactorizedRelation<9, int> &c2)
    {
      PARTKEY = c0;
      SUPPKEY = c1;
      __av = c2;
    }
    TMP_partsupp_V_partsupp_Q2_entry(const TMP_partsupp_V_partsupp_Q2_entry &other) : PARTKEY(other.PARTKEY), SUPPKEY(other.SUPPKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    TMP_partsupp_V_partsupp_Q2_entry(const std::vector<std::string> &f, const RingFactorizedRelation<9, int> &v)
    {
      /* if (f.size() < 2) return; */
      PARTKEY = std::stoi(f[0]);
      SUPPKEY = std::stoi(f[1]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE TMP_partsupp_V_partsupp_Q2_entry &modify(const int c0, const int c1)
    {
      PARTKEY = c0;
      SUPPKEY = c1;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct TMP_partsupp_V_partsupp_Q2_mapkey01_idxfn
  {
    FORCE_INLINE static size_t hash(const TMP_partsupp_V_partsupp_Q2_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.PARTKEY);
      hash_combine(h, e.SUPPKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const TMP_partsupp_V_partsupp_Q2_entry &x, const TMP_partsupp_V_partsupp_Q2_entry &y)
    {
      return x.PARTKEY == y.PARTKEY && x.SUPPKEY == y.SUPPKEY;
    }
  };

  typedef MultiHashMap<TMP_partsupp_V_partsupp_Q2_entry, RingFactorizedRelation<9, int>,
                       PrimaryHashIndex<TMP_partsupp_V_partsupp_Q2_entry, TMP_partsupp_V_partsupp_Q2_mapkey01_idxfn>>
      TMP_partsupp_V_partsupp_Q2_map;

  struct TMP_partsupp_V_lineitempartsupp_Q2_entry
  {
    int PARTKEY;
    RingFactorizedRelation<8, int> __av;
    TMP_partsupp_V_lineitempartsupp_Q2_entry *nxt;
    TMP_partsupp_V_lineitempartsupp_Q2_entry *prv;

    explicit TMP_partsupp_V_lineitempartsupp_Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit TMP_partsupp_V_lineitempartsupp_Q2_entry(const int c0, const RingFactorizedRelation<8, int> &c1)
    {
      PARTKEY = c0;
      __av = c1;
    }
    TMP_partsupp_V_lineitempartsupp_Q2_entry(const TMP_partsupp_V_lineitempartsupp_Q2_entry &other) : PARTKEY(other.PARTKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    TMP_partsupp_V_lineitempartsupp_Q2_entry(const std::vector<std::string> &f, const RingFactorizedRelation<8, int> &v)
    {
      /* if (f.size() < 1) return; */
      PARTKEY = std::stoi(f[0]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE TMP_partsupp_V_lineitempartsupp_Q2_entry &modify(const int c0)
    {
      PARTKEY = c0;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct TMP_partsupp_V_lineitempartsupp_Q2_mapkey0_idxfn
  {
    FORCE_INLINE static size_t hash(const TMP_partsupp_V_lineitempartsupp_Q2_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.PARTKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const TMP_partsupp_V_lineitempartsupp_Q2_entry &x, const TMP_partsupp_V_lineitempartsupp_Q2_entry &y)
    {
      return x.PARTKEY == y.PARTKEY;
    }
  };

  typedef MultiHashMap<TMP_partsupp_V_lineitempartsupp_Q2_entry, RingFactorizedRelation<8, int>,
                       PrimaryHashIndex<TMP_partsupp_V_lineitempartsupp_Q2_entry, TMP_partsupp_V_lineitempartsupp_Q2_mapkey0_idxfn>>
      TMP_partsupp_V_lineitempartsupp_Q2_map;

  struct TMP_lineitem_V_lineitem_Q2_entry
  {
    int PARTKEY;
    int SUPPKEY;
    RingFactorizedRelation<10, int, DOUBLE_TYPE> __av;
    TMP_lineitem_V_lineitem_Q2_entry *nxt;
    TMP_lineitem_V_lineitem_Q2_entry *prv;

    explicit TMP_lineitem_V_lineitem_Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit TMP_lineitem_V_lineitem_Q2_entry(const int c0, const int c1, const RingFactorizedRelation<10, int, DOUBLE_TYPE> &c2)
    {
      PARTKEY = c0;
      SUPPKEY = c1;
      __av = c2;
    }
    TMP_lineitem_V_lineitem_Q2_entry(const TMP_lineitem_V_lineitem_Q2_entry &other) : PARTKEY(other.PARTKEY), SUPPKEY(other.SUPPKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    TMP_lineitem_V_lineitem_Q2_entry(const std::vector<std::string> &f, const RingFactorizedRelation<10, int, DOUBLE_TYPE> &v)
    {
      /* if (f.size() < 2) return; */
      PARTKEY = std::stoi(f[0]);
      SUPPKEY = std::stoi(f[1]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE TMP_lineitem_V_lineitem_Q2_entry &modify(const int c0, const int c1)
    {
      PARTKEY = c0;
      SUPPKEY = c1;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct TMP_lineitem_V_lineitem_Q2_mapkey01_idxfn
  {
    FORCE_INLINE static size_t hash(const TMP_lineitem_V_lineitem_Q2_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.PARTKEY);
      hash_combine(h, e.SUPPKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const TMP_lineitem_V_lineitem_Q2_entry &x, const TMP_lineitem_V_lineitem_Q2_entry &y)
    {
      return x.PARTKEY == y.PARTKEY && x.SUPPKEY == y.SUPPKEY;
    }
  };

  typedef MultiHashMap<TMP_lineitem_V_lineitem_Q2_entry, RingFactorizedRelation<10, int, DOUBLE_TYPE>,
                       PrimaryHashIndex<TMP_lineitem_V_lineitem_Q2_entry, TMP_lineitem_V_lineitem_Q2_mapkey01_idxfn>>
      TMP_lineitem_V_lineitem_Q2_map;

  struct TMP_lineitem_V_lineitempartsupp_Q2_entry
  {
    int PARTKEY;
    RingFactorizedRelation<8, int> __av;
    TMP_lineitem_V_lineitempartsupp_Q2_entry *nxt;
    TMP_lineitem_V_lineitempartsupp_Q2_entry *prv;

    explicit TMP_lineitem_V_lineitempartsupp_Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit TMP_lineitem_V_lineitempartsupp_Q2_entry(const int c0, const RingFactorizedRelation<8, int> &c1)
    {
      PARTKEY = c0;
      __av = c1;
    }
    TMP_lineitem_V_lineitempartsupp_Q2_entry(const TMP_lineitem_V_lineitempartsupp_Q2_entry &other) : PARTKEY(other.PARTKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    TMP_lineitem_V_lineitempartsupp_Q2_entry(const std::vector<std::string> &f, const RingFactorizedRelation<8, int> &v)
    {
      /* if (f.size() < 1) return; */
      PARTKEY = std::stoi(f[0]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE TMP_lineitem_V_lineitempartsupp_Q2_entry &modify(const int c0)
    {
      PARTKEY = c0;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct TMP_lineitem_V_lineitempartsupp_Q2_mapkey0_idxfn
  {
    FORCE_INLINE static size_t hash(const TMP_lineitem_V_lineitempartsupp_Q2_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.PARTKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const TMP_lineitem_V_lineitempartsupp_Q2_entry &x, const TMP_lineitem_V_lineitempartsupp_Q2_entry &y)
    {
      return x.PARTKEY == y.PARTKEY;
    }
  };

  typedef MultiHashMap<TMP_lineitem_V_lineitempartsupp_Q2_entry, RingFactorizedRelation<8, int>,
                       PrimaryHashIndex<TMP_lineitem_V_lineitempartsupp_Q2_entry, TMP_lineitem_V_lineitempartsupp_Q2_mapkey0_idxfn>>
      TMP_lineitem_V_lineitempartsupp_Q2_map;

  struct TMP_part_V_part_Q2_entry
  {
    int PARTKEY;
    RingFactorizedRelation<12, STRING_TYPE> __av;
    TMP_part_V_part_Q2_entry *nxt;
    TMP_part_V_part_Q2_entry *prv;

    explicit TMP_part_V_part_Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit TMP_part_V_part_Q2_entry(const int c0, const RingFactorizedRelation<12, STRING_TYPE> &c1)
    {
      PARTKEY = c0;
      __av = c1;
    }
    TMP_part_V_part_Q2_entry(const TMP_part_V_part_Q2_entry &other) : PARTKEY(other.PARTKEY), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    TMP_part_V_part_Q2_entry(const std::vector<std::string> &f, const RingFactorizedRelation<12, STRING_TYPE> &v)
    {
      /* if (f.size() < 1) return; */
      PARTKEY = std::stoi(f[0]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE TMP_part_V_part_Q2_entry &modify(const int c0)
    {
      PARTKEY = c0;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, PARTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct TMP_part_V_part_Q2_mapkey0_idxfn
  {
    FORCE_INLINE static size_t hash(const TMP_part_V_part_Q2_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.PARTKEY);
      return h;
    }

    FORCE_INLINE static bool equals(const TMP_part_V_part_Q2_entry &x, const TMP_part_V_part_Q2_entry &y)
    {
      return x.PARTKEY == y.PARTKEY;
    }
  };

  typedef MultiHashMap<TMP_part_V_part_Q2_entry, RingFactorizedRelation<12, STRING_TYPE>,
                       PrimaryHashIndex<TMP_part_V_part_Q2_entry, TMP_part_V_part_Q2_mapkey0_idxfn>>
      TMP_part_V_part_Q2_map;

  struct DELTA_orders_entry
  {
    int orderkey;
    int custkey;
    STRING_TYPE o_orderstatus;
    DOUBLE_TYPE o_totalprice;
    STRING_TYPE o_orderdate;
    STRING_TYPE o_orderpriority;
    STRING_TYPE o_clerk;
    int o_shippriority;
    STRING_TYPE o_comment;
    long __av;
    DELTA_orders_entry *nxt;
    DELTA_orders_entry *prv;

    explicit DELTA_orders_entry() : nxt(nullptr), prv(nullptr) {}
    explicit DELTA_orders_entry(const int c0, const int c1, const STRING_TYPE &c2, const DOUBLE_TYPE c3, const STRING_TYPE &c4, const STRING_TYPE &c5, const STRING_TYPE &c6, const int c7, const STRING_TYPE &c8, const long c9)
    {
      orderkey = c0;
      custkey = c1;
      o_orderstatus = c2;
      o_totalprice = c3;
      o_orderdate = c4;
      o_orderpriority = c5;
      o_clerk = c6;
      o_shippriority = c7;
      o_comment = c8;
      __av = c9;
    }
    DELTA_orders_entry(const DELTA_orders_entry &other) : orderkey(other.orderkey), custkey(other.custkey), o_orderstatus(other.o_orderstatus), o_totalprice(other.o_totalprice), o_orderdate(other.o_orderdate), o_orderpriority(other.o_orderpriority), o_clerk(other.o_clerk), o_shippriority(other.o_shippriority), o_comment(other.o_comment), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    DELTA_orders_entry(const std::vector<std::string> &f, const long v)
    {
      /* if (f.size() < 9) return; */
      orderkey = std::stoi(f[0]);
      custkey = std::stoi(f[1]);
      o_orderstatus = f[2];
      o_totalprice = std::stod(f[3]);
      o_orderdate = f[4];
      o_orderpriority = f[5];
      o_clerk = f[6];
      o_shippriority = std::stoi(f[7]);
      o_comment = f[8];
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE DELTA_orders_entry &modify(const int c0, const int c1, const STRING_TYPE &c2, const DOUBLE_TYPE c3, const STRING_TYPE &c4, const STRING_TYPE &c5, const STRING_TYPE &c6, const int c7, const STRING_TYPE &c8)
    {
      orderkey = c0;
      custkey = c1;
      o_orderstatus = c2;
      o_totalprice = c3;
      o_orderdate = c4;
      o_orderpriority = c5;
      o_clerk = c6;
      o_shippriority = c7;
      o_comment = c8;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, custkey);
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

  struct DELTA_orders_mapkey012345678_idxfn
  {
    FORCE_INLINE static size_t hash(const DELTA_orders_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.orderkey);
      hash_combine(h, e.custkey);
      hash_combine(h, e.o_orderstatus);
      hash_combine(h, e.o_totalprice);
      hash_combine(h, e.o_orderdate);
      hash_combine(h, e.o_orderpriority);
      hash_combine(h, e.o_clerk);
      hash_combine(h, e.o_shippriority);
      hash_combine(h, e.o_comment);
      return h;
    }

    FORCE_INLINE static bool equals(const DELTA_orders_entry &x, const DELTA_orders_entry &y)
    {
      return x.orderkey == y.orderkey && x.custkey == y.custkey && x.o_orderstatus == y.o_orderstatus && x.o_totalprice == y.o_totalprice && x.o_orderdate == y.o_orderdate && x.o_orderpriority == y.o_orderpriority && x.o_clerk == y.o_clerk && x.o_shippriority == y.o_shippriority && x.o_comment == y.o_comment;
    }
  };

  typedef MultiHashMap<DELTA_orders_entry, long,
                       PrimaryHashIndex<DELTA_orders_entry, DELTA_orders_mapkey012345678_idxfn>>
      DELTA_orders_map;

  struct DELTA_lineitem_entry
  {
    int orderkey;
    int partkey;
    int suppkey;
    int l_linenumber;
    DOUBLE_TYPE l_quantity;
    DOUBLE_TYPE l_extendedprice;
    DOUBLE_TYPE l_discount;
    DOUBLE_TYPE l_tax;
    STRING_TYPE l_returnflag;
    STRING_TYPE l_linestatus;
    STRING_TYPE l_shipdate;
    STRING_TYPE l_commitdate;
    STRING_TYPE l_receiptdate;
    STRING_TYPE l_shipinstruct;
    STRING_TYPE l_shipmode;
    STRING_TYPE l_comment;
    long __av;
    DELTA_lineitem_entry *nxt;
    DELTA_lineitem_entry *prv;

    explicit DELTA_lineitem_entry() : nxt(nullptr), prv(nullptr) {}
    explicit DELTA_lineitem_entry(const int c0, const int c1, const int c2, const int c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const STRING_TYPE &c8, const STRING_TYPE &c9, const STRING_TYPE &c10, const STRING_TYPE &c11, const STRING_TYPE &c12, const STRING_TYPE &c13, const STRING_TYPE &c14, const STRING_TYPE &c15, const long c16)
    {
      orderkey = c0;
      partkey = c1;
      suppkey = c2;
      l_linenumber = c3;
      l_quantity = c4;
      l_extendedprice = c5;
      l_discount = c6;
      l_tax = c7;
      l_returnflag = c8;
      l_linestatus = c9;
      l_shipdate = c10;
      l_commitdate = c11;
      l_receiptdate = c12;
      l_shipinstruct = c13;
      l_shipmode = c14;
      l_comment = c15;
      __av = c16;
    }
    DELTA_lineitem_entry(const DELTA_lineitem_entry &other) : orderkey(other.orderkey), partkey(other.partkey), suppkey(other.suppkey), l_linenumber(other.l_linenumber), l_quantity(other.l_quantity), l_extendedprice(other.l_extendedprice), l_discount(other.l_discount), l_tax(other.l_tax), l_returnflag(other.l_returnflag), l_linestatus(other.l_linestatus), l_shipdate(other.l_shipdate), l_commitdate(other.l_commitdate), l_receiptdate(other.l_receiptdate), l_shipinstruct(other.l_shipinstruct), l_shipmode(other.l_shipmode), l_comment(other.l_comment), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    DELTA_lineitem_entry(const std::vector<std::string> &f, const long v)
    {
      /* if (f.size() < 16) return; */
      orderkey = std::stoi(f[0]);
      partkey = std::stoi(f[1]);
      suppkey = std::stoi(f[2]);
      l_linenumber = std::stoi(f[3]);
      l_quantity = std::stod(f[4]);
      l_extendedprice = std::stod(f[5]);
      l_discount = std::stod(f[6]);
      l_tax = std::stod(f[7]);
      l_returnflag = f[8];
      l_linestatus = f[9];
      l_shipdate = f[10];
      l_commitdate = f[11];
      l_receiptdate = f[12];
      l_shipinstruct = f[13];
      l_shipmode = f[14];
      l_comment = f[15];
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE DELTA_lineitem_entry &modify(const int c0, const int c1, const int c2, const int c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const DOUBLE_TYPE c6, const DOUBLE_TYPE c7, const STRING_TYPE &c8, const STRING_TYPE &c9, const STRING_TYPE &c10, const STRING_TYPE &c11, const STRING_TYPE &c12, const STRING_TYPE &c13, const STRING_TYPE &c14, const STRING_TYPE &c15)
    {
      orderkey = c0;
      partkey = c1;
      suppkey = c2;
      l_linenumber = c3;
      l_quantity = c4;
      l_extendedprice = c5;
      l_discount = c6;
      l_tax = c7;
      l_returnflag = c8;
      l_linestatus = c9;
      l_shipdate = c10;
      l_commitdate = c11;
      l_receiptdate = c12;
      l_shipinstruct = c13;
      l_shipmode = c14;
      l_comment = c15;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
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

  struct DELTA_lineitem_mapkey0123456789101112131415_idxfn
  {
    FORCE_INLINE static size_t hash(const DELTA_lineitem_entry &e)
    {
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

    FORCE_INLINE static bool equals(const DELTA_lineitem_entry &x, const DELTA_lineitem_entry &y)
    {
      return x.orderkey == y.orderkey && x.partkey == y.partkey && x.suppkey == y.suppkey && x.l_linenumber == y.l_linenumber && x.l_quantity == y.l_quantity && x.l_extendedprice == y.l_extendedprice && x.l_discount == y.l_discount && x.l_tax == y.l_tax && x.l_returnflag == y.l_returnflag && x.l_linestatus == y.l_linestatus && x.l_shipdate == y.l_shipdate && x.l_commitdate == y.l_commitdate && x.l_receiptdate == y.l_receiptdate && x.l_shipinstruct == y.l_shipinstruct && x.l_shipmode == y.l_shipmode && x.l_comment == y.l_comment;
    }
  };

  typedef MultiHashMap<DELTA_lineitem_entry, long,
                       PrimaryHashIndex<DELTA_lineitem_entry, DELTA_lineitem_mapkey0123456789101112131415_idxfn>>
      DELTA_lineitem_map;

  struct DELTA_partsupp_entry
  {
    int partkey;
    int suppkey;
    int ps_availqty;
    DOUBLE_TYPE ps_supplycost;
    STRING_TYPE ps_comment;
    long __av;
    DELTA_partsupp_entry *nxt;
    DELTA_partsupp_entry *prv;

    explicit DELTA_partsupp_entry() : nxt(nullptr), prv(nullptr) {}
    explicit DELTA_partsupp_entry(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const STRING_TYPE &c4, const long c5)
    {
      partkey = c0;
      suppkey = c1;
      ps_availqty = c2;
      ps_supplycost = c3;
      ps_comment = c4;
      __av = c5;
    }
    DELTA_partsupp_entry(const DELTA_partsupp_entry &other) : partkey(other.partkey), suppkey(other.suppkey), ps_availqty(other.ps_availqty), ps_supplycost(other.ps_supplycost), ps_comment(other.ps_comment), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    DELTA_partsupp_entry(const std::vector<std::string> &f, const long v)
    {
      /* if (f.size() < 5) return; */
      partkey = std::stoi(f[0]);
      suppkey = std::stoi(f[1]);
      ps_availqty = std::stoi(f[2]);
      ps_supplycost = std::stod(f[3]);
      ps_comment = f[4];
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE DELTA_partsupp_entry &modify(const int c0, const int c1, const int c2, const DOUBLE_TYPE c3, const STRING_TYPE &c4)
    {
      partkey = c0;
      suppkey = c1;
      ps_availqty = c2;
      ps_supplycost = c3;
      ps_comment = c4;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
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

  struct DELTA_partsupp_mapkey01234_idxfn
  {
    FORCE_INLINE static size_t hash(const DELTA_partsupp_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.partkey);
      hash_combine(h, e.suppkey);
      hash_combine(h, e.ps_availqty);
      hash_combine(h, e.ps_supplycost);
      hash_combine(h, e.ps_comment);
      return h;
    }

    FORCE_INLINE static bool equals(const DELTA_partsupp_entry &x, const DELTA_partsupp_entry &y)
    {
      return x.partkey == y.partkey && x.suppkey == y.suppkey && x.ps_availqty == y.ps_availqty && x.ps_supplycost == y.ps_supplycost && x.ps_comment == y.ps_comment;
    }
  };

  typedef MultiHashMap<DELTA_partsupp_entry, long,
                       PrimaryHashIndex<DELTA_partsupp_entry, DELTA_partsupp_mapkey01234_idxfn>>
      DELTA_partsupp_map;

  struct DELTA_part_entry
  {
    int partkey;
    STRING_TYPE p_name;
    STRING_TYPE p_mfgr;
    STRING_TYPE p_brand;
    STRING_TYPE p_type;
    int p_size;
    STRING_TYPE p_container;
    DOUBLE_TYPE p_retailprice;
    STRING_TYPE p_comment;
    long __av;
    DELTA_part_entry *nxt;
    DELTA_part_entry *prv;

    explicit DELTA_part_entry() : nxt(nullptr), prv(nullptr) {}
    explicit DELTA_part_entry(const int c0, const STRING_TYPE &c1, const STRING_TYPE &c2, const STRING_TYPE &c3, const STRING_TYPE &c4, const int c5, const STRING_TYPE &c6, const DOUBLE_TYPE c7, const STRING_TYPE &c8, const long c9)
    {
      partkey = c0;
      p_name = c1;
      p_mfgr = c2;
      p_brand = c3;
      p_type = c4;
      p_size = c5;
      p_container = c6;
      p_retailprice = c7;
      p_comment = c8;
      __av = c9;
    }
    DELTA_part_entry(const DELTA_part_entry &other) : partkey(other.partkey), p_name(other.p_name), p_mfgr(other.p_mfgr), p_brand(other.p_brand), p_type(other.p_type), p_size(other.p_size), p_container(other.p_container), p_retailprice(other.p_retailprice), p_comment(other.p_comment), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    DELTA_part_entry(const std::vector<std::string> &f, const long v)
    {
      /* if (f.size() < 9) return; */
      partkey = std::stoi(f[0]);
      p_name = f[1];
      p_mfgr = f[2];
      p_brand = f[3];
      p_type = f[4];
      p_size = std::stoi(f[5]);
      p_container = f[6];
      p_retailprice = std::stod(f[7]);
      p_comment = f[8];
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE DELTA_part_entry &modify(const int c0, const STRING_TYPE &c1, const STRING_TYPE &c2, const STRING_TYPE &c3, const STRING_TYPE &c4, const int c5, const STRING_TYPE &c6, const DOUBLE_TYPE c7, const STRING_TYPE &c8)
    {
      partkey = c0;
      p_name = c1;
      p_mfgr = c2;
      p_brand = c3;
      p_type = c4;
      p_size = c5;
      p_container = c6;
      p_retailprice = c7;
      p_comment = c8;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
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

  struct DELTA_part_mapkey012345678_idxfn
  {
    FORCE_INLINE static size_t hash(const DELTA_part_entry &e)
    {
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

    FORCE_INLINE static bool equals(const DELTA_part_entry &x, const DELTA_part_entry &y)
    {
      return x.partkey == y.partkey && x.p_name == y.p_name && x.p_mfgr == y.p_mfgr && x.p_brand == y.p_brand && x.p_type == y.p_type && x.p_size == y.p_size && x.p_container == y.p_container && x.p_retailprice == y.p_retailprice && x.p_comment == y.p_comment;
    }
  };

  typedef MultiHashMap<DELTA_part_entry, long,
                       PrimaryHashIndex<DELTA_part_entry, DELTA_part_mapkey012345678_idxfn>>
      DELTA_part_map;

  struct DELTA_Q2_entry
  {
    STRING_TYPE p_name;
    int ps_availqty;
    DOUBLE_TYPE l_quantity;
    int partkey;
    int suppkey;
    int orderkey;
    long __av;
    DELTA_Q2_entry *nxt;
    DELTA_Q2_entry *prv;

    explicit DELTA_Q2_entry() : nxt(nullptr), prv(nullptr) {}
    explicit DELTA_Q2_entry(const STRING_TYPE &c0, const int c1, const DOUBLE_TYPE c2, const int c3, const int c4, const int c5, const long c6)
    {
      p_name = c0;
      ps_availqty = c1;
      l_quantity = c2;
      partkey = c3;
      suppkey = c4;
      orderkey = c5;
      __av = c6;
    }
    DELTA_Q2_entry(const DELTA_Q2_entry &other) : p_name(other.p_name), ps_availqty(other.ps_availqty), l_quantity(other.l_quantity), partkey(other.partkey), suppkey(other.suppkey), orderkey(other.orderkey), __av(other.__av), nxt(nullptr), prv(nullptr) {}
    DELTA_Q2_entry(const std::vector<std::string> &f, const long v)
    {
      /* if (f.size() < 6) return; */
      p_name = f[0];
      ps_availqty = std::stoi(f[1]);
      l_quantity = std::stod(f[2]);
      partkey = std::stoi(f[3]);
      suppkey = std::stoi(f[4]);
      orderkey = std::stoi(f[5]);
      __av = v;
      nxt = nullptr;
      prv = nullptr;
    }

    FORCE_INLINE DELTA_Q2_entry &modify(const STRING_TYPE &c0, const int c1, const DOUBLE_TYPE c2, const int c3, const int c4, const int c5)
    {
      p_name = c0;
      ps_availqty = c1;
      l_quantity = c2;
      partkey = c3;
      suppkey = c4;
      orderkey = c5;
      return *this;
    }
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, p_name);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ps_availqty);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, l_quantity);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, partkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, suppkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, orderkey);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };

  struct DELTA_Q2_mapkey012345_idxfn
  {
    FORCE_INLINE static size_t hash(const DELTA_Q2_entry &e)
    {
      size_t h = 0;
      hash_combine(h, e.p_name);
      hash_combine(h, e.ps_availqty);
      hash_combine(h, e.l_quantity);
      hash_combine(h, e.partkey);
      hash_combine(h, e.suppkey);
      hash_combine(h, e.orderkey);
      return h;
    }

    FORCE_INLINE static bool equals(const DELTA_Q2_entry &x, const DELTA_Q2_entry &y)
    {
      return x.p_name == y.p_name && x.ps_availqty == y.ps_availqty && x.l_quantity == y.l_quantity && x.partkey == y.partkey && x.suppkey == y.suppkey && x.orderkey == y.orderkey;
    }
  };

  typedef MultiHashMap<DELTA_Q2_entry, long,
                       PrimaryHashIndex<DELTA_Q2_entry, DELTA_Q2_mapkey012345_idxfn>>
      DELTA_Q2_map;

  /* Defines top-level materialized views */
  struct tlq_t
  {
    struct timeval t0, t;
    long tT, tN, tS;
    tlq_t() : tN(0), tS(0), V_Q2orders_Q1(RingFactorizedRelation<0, int>()), V_lineitempartpartsupp_Q2(RingFactorizedRelation<7, int>())
    {
      gettimeofday(&t0, NULL);
    }

    /* Serialization code */
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) const
    {
      ar << "\n";
      const RingFactorizedRelation<0, int> &_V_Q2orders_Q1 = get_V_Q2orders_Q1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_Q2orders_Q1), _V_Q2orders_Q1, "\t");

      ar << "\n";
      const V_orders_Q1_map &_V_orders_Q1 = get_V_orders_Q1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_orders_Q1), _V_orders_Q1, "\t");

      ar << "\n";
      const V_Q2_Q1_map &_V_Q2_Q1 = get_V_Q2_Q1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_Q2_Q1), _V_Q2_Q1, "\t");

      ar << "\n";
      const RingFactorizedRelation<7, int> &_V_lineitempartpartsupp_Q2 = get_V_lineitempartpartsupp_Q2();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_lineitempartpartsupp_Q2), _V_lineitempartpartsupp_Q2, "\t");

      ar << "\n";
      const V_lineitempartsupp_Q2_map &_V_lineitempartsupp_Q2 = get_V_lineitempartsupp_Q2();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_lineitempartsupp_Q2), _V_lineitempartsupp_Q2, "\t");

      ar << "\n";
      const V_partsupp_Q2_map &_V_partsupp_Q2 = get_V_partsupp_Q2();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_partsupp_Q2), _V_partsupp_Q2, "\t");

      ar << "\n";
      const V_lineitem_Q2_map &_V_lineitem_Q2 = get_V_lineitem_Q2();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_lineitem_Q2), _V_lineitem_Q2, "\t");

      ar << "\n";
      const V_part_Q2_map &_V_part_Q2 = get_V_part_Q2();
      dbtoaster::serialize_nvp_tabbed(ar, STRING(V_part_Q2), _V_part_Q2, "\t");
    }

    /* Functions returning / computing the results of top level queries */
    const RingFactorizedRelation<0, int> &get_V_Q2orders_Q1() const
    {
      return V_Q2orders_Q1;
    }

    const V_orders_Q1_map &get_V_orders_Q1() const
    {
      return V_orders_Q1;
    }

    const V_Q2_Q1_map &get_V_Q2_Q1() const
    {
      return V_Q2_Q1;
    }

    const RingFactorizedRelation<7, int> &get_V_lineitempartpartsupp_Q2() const
    {
      return V_lineitempartpartsupp_Q2;
    }

    const V_lineitempartsupp_Q2_map &get_V_lineitempartsupp_Q2() const
    {
      return V_lineitempartsupp_Q2;
    }

    const V_partsupp_Q2_map &get_V_partsupp_Q2() const
    {
      return V_partsupp_Q2;
    }

    const V_lineitem_Q2_map &get_V_lineitem_Q2() const
    {
      return V_lineitem_Q2;
    }

    const V_part_Q2_map &get_V_part_Q2() const
    {
      return V_part_Q2;
    }

  protected:
    /* Data structures used for storing / computing top-level queries */
    RingFactorizedRelation<0, int> V_Q2orders_Q1;
    V_orders_Q1_map V_orders_Q1;
    V_Q2_Q1_map V_Q2_Q1;
    RingFactorizedRelation<7, int> V_lineitempartpartsupp_Q2;
    V_lineitempartsupp_Q2_map V_lineitempartsupp_Q2;
    V_partsupp_Q2_map V_partsupp_Q2;
    V_lineitem_Q2_map V_lineitem_Q2;
    V_part_Q2_map V_part_Q2;
  };

  /* Contains materialized views and processing (IVM) logic */
  struct data_t : tlq_t
  {

    data_t() : tlq_t(), TMP_orders_V_Q2orders_Q1(RingFactorizedRelation<0, int>()), TMP_Q2_V_Q2orders_Q1(RingFactorizedRelation<0, int>()), TMP_partsupp_V_lineitempartpartsupp_Q2(RingFactorizedRelation<7, int>()), TMP_lineitem_V_lineitempartpartsupp_Q2(RingFactorizedRelation<7, int>()), TMP_part_V_lineitempartpartsupp_Q2(RingFactorizedRelation<7, int>())
    {
    }

    /* Trigger functions for table relations */

    /* Trigger functions for stream relations */
    void on_batch_update_orders(const std::vector<DELTA_orders_entry>::iterator &begin, const std::vector<DELTA_orders_entry>::iterator &end)
    {
      long batchSize = std::distance(begin, end);

      tN += batchSize;
      TMP_orders_V_orders_Q1.clear();
      { // foreach
        for (std::vector<DELTA_orders_entry>::iterator e1 = begin; e1 != end; e1++)
        {
          int orderkey = e1->orderkey;
          int custkey = e1->custkey;
          STRING_TYPE o_orderstatus = e1->o_orderstatus;
          DOUBLE_TYPE o_totalprice = e1->o_totalprice;
          STRING_TYPE o_orderdate = e1->o_orderdate;
          STRING_TYPE o_orderpriority = e1->o_orderpriority;
          STRING_TYPE o_clerk = e1->o_clerk;
          int o_shippriority = e1->o_shippriority;
          STRING_TYPE o_comment = e1->o_comment;
          long v1 = e1->__av;
          TMP_orders_V_orders_Q1.addOrDelOnZero(se1.modify(orderkey), (v1 * Ulift<1>(o_totalprice)));
        }
      }

      { // foreach
        TMP_orders_V_orders_Q1_entry *e2 = TMP_orders_V_orders_Q1.head;
        while (e2)
        {
          int orderkey = e2->ORDERKEY;
          RingFactorizedRelation<1, DOUBLE_TYPE> &v2 = e2->__av;
          V_Q2orders_Q1 += ((v2 * V_Q2_Q1.getValueOrDefault(se3.modify(orderkey))) * Ulift<0>(orderkey));
          e2 = e2->nxt;
        }
      }

      { // foreach
        TMP_orders_V_orders_Q1_entry *e3 = TMP_orders_V_orders_Q1.head;
        while (e3)
        {
          int orderkey = e3->ORDERKEY;
          RingFactorizedRelation<1, DOUBLE_TYPE> &v3 = e3->__av;
          V_orders_Q1.addOrDelOnZero(se4.modify(orderkey), v3);
          e3 = e3->nxt;
        }
      }
    }

    void on_batch_update_Q2(const std::vector<DELTA_Q2_entry>::iterator &begin, const std::vector<DELTA_Q2_entry>::iterator &end)
    {

      // TODO: add here the code to print the time stamp
      update_timer.restart();

      long batchSize = std::distance(begin, end);

      tN += batchSize;
      TMP_Q2_V_Q2_Q1.clear();
      { // foreach
        for (std::vector<DELTA_Q2_entry>::iterator e4 = begin; e4 != end; e4++)
        {
          STRING_TYPE p_name = e4->p_name;
          int ps_availqty = e4->ps_availqty;
          DOUBLE_TYPE l_quantity = e4->l_quantity;
          int partkey = e4->partkey;
          int suppkey = e4->suppkey;
          int orderkey = e4->orderkey;
          long v4 = e4->__av;
          TMP_Q2_V_Q2_Q1.addOrDelOnZero(se5.modify(orderkey), (v4 * Ulift<2>(p_name, l_quantity, ps_availqty, partkey, suppkey)));
        }
      }

      { // foreach
        TMP_Q2_V_Q2_Q1_entry *e5 = TMP_Q2_V_Q2_Q1.head;
        while (e5)
        {
          int orderkey = e5->ORDERKEY;
          RingFactorizedRelation<2, STRING_TYPE, DOUBLE_TYPE, int, int, int> &v5 = e5->__av;
          V_Q2orders_Q1 += ((v5 * V_orders_Q1.getValueOrDefault(se7.modify(orderkey))) * Ulift<0>(orderkey));
          e5 = e5->nxt;
        }
      }

      { // foreach
        TMP_Q2_V_Q2_Q1_entry *e6 = TMP_Q2_V_Q2_Q1.head;
        while (e6)
        {
          int orderkey = e6->ORDERKEY;
          RingFactorizedRelation<2, STRING_TYPE, DOUBLE_TYPE, int, int, int> &v6 = e6->__av;
          V_Q2_Q1.addOrDelOnZero(se8.modify(orderkey), v6);
          e6 = e6->nxt;
        }
      }
      update_timer.stop();
      update_time += update_timer.elapsedTimeInMilliSeconds();

      accumulated_tuples += batchSize;
      if (accumulated_tuples >= snapshot_interval)
      {
        std::cout << "Q2: " << update_time << " ms" << std::endl;
        accumulated_tuples = 0;
        update_time = 0;
        struct rusage r_usage;
        if (getrusage(RUSAGE_SELF, &r_usage) == 0)
        {
          // Convert kilobytes to megabytes
          double memoryUsageMB = static_cast<double>(r_usage.ru_maxrss) / 1024;
          std::cout << "Q2 memory: " << memoryUsageMB << " MB\n";
        }
        else
        {
          std::cerr << "Q2 Failed to get memory usage.\n";
        }
      }
    }

    void on_batch_update_partsupp(const std::vector<DELTA_partsupp_entry>::iterator &begin, const std::vector<DELTA_partsupp_entry>::iterator &end)
    {
      long batchSize = std::distance(begin, end);

      tN += batchSize;
      TMP_partsupp_V_partsupp_Q2.clear();
      { // foreach
        for (std::vector<DELTA_partsupp_entry>::iterator e7 = begin; e7 != end; e7++)
        {
          int partkey = e7->partkey;
          int suppkey = e7->suppkey;
          int ps_availqty = e7->ps_availqty;
          DOUBLE_TYPE ps_supplycost = e7->ps_supplycost;
          STRING_TYPE ps_comment = e7->ps_comment;
          long v7 = e7->__av;
          TMP_partsupp_V_partsupp_Q2.addOrDelOnZero(se9.modify(partkey, suppkey), (v7 * Ulift<9>(ps_availqty)));
        }
      }

      TMP_partsupp_V_lineitempartsupp_Q2.clear();
      { // foreach
        TMP_partsupp_V_partsupp_Q2_entry *e8 = TMP_partsupp_V_partsupp_Q2.head;
        while (e8)
        {
          int partkey = e8->PARTKEY;
          int suppkey = e8->SUPPKEY;
          RingFactorizedRelation<9, int> &v8 = e8->__av;
          TMP_partsupp_V_lineitempartsupp_Q2.addOrDelOnZero(se10.modify(partkey), ((v8 * V_lineitem_Q2.getValueOrDefault(se11.modify(partkey, suppkey))) * Ulift<8>(suppkey)));
          e8 = e8->nxt;
        }
      }

      { // foreach
        TMP_partsupp_V_lineitempartsupp_Q2_entry *e9 = TMP_partsupp_V_lineitempartsupp_Q2.head;
        while (e9)
        {
          int partkey = e9->PARTKEY;
          RingFactorizedRelation<8, int> &v9 = e9->__av;
          V_lineitempartpartsupp_Q2 += ((v9 * V_part_Q2.getValueOrDefault(se13.modify(partkey))) * Ulift<7>(partkey));
          e9 = e9->nxt;
        }
      }

      { // foreach
        TMP_partsupp_V_partsupp_Q2_entry *e10 = TMP_partsupp_V_partsupp_Q2.head;
        while (e10)
        {
          int partkey = e10->PARTKEY;
          int suppkey = e10->SUPPKEY;
          RingFactorizedRelation<9, int> &v10 = e10->__av;
          V_partsupp_Q2.addOrDelOnZero(se14.modify(partkey, suppkey), v10);
          e10 = e10->nxt;
        }
      }

      { // foreach
        TMP_partsupp_V_lineitempartsupp_Q2_entry *e11 = TMP_partsupp_V_lineitempartsupp_Q2.head;
        while (e11)
        {
          int partkey = e11->PARTKEY;
          RingFactorizedRelation<8, int> &v11 = e11->__av;
          V_lineitempartsupp_Q2.addOrDelOnZero(se15.modify(partkey), v11);
          e11 = e11->nxt;
        }
      }
    }

    void on_batch_update_lineitem(const std::vector<DELTA_lineitem_entry>::iterator &begin, const std::vector<DELTA_lineitem_entry>::iterator &end)
    {
      long batchSize = std::distance(begin, end);

      tN += batchSize;
      TMP_lineitem_V_lineitem_Q2.clear();
      { // foreach
        for (std::vector<DELTA_lineitem_entry>::iterator e12 = begin; e12 != end; e12++)
        {
          int orderkey = e12->orderkey;
          int partkey = e12->partkey;
          int suppkey = e12->suppkey;
          int l_linenumber = e12->l_linenumber;
          DOUBLE_TYPE l_quantity = e12->l_quantity;
          DOUBLE_TYPE l_extendedprice = e12->l_extendedprice;
          DOUBLE_TYPE l_discount = e12->l_discount;
          DOUBLE_TYPE l_tax = e12->l_tax;
          STRING_TYPE l_returnflag = e12->l_returnflag;
          STRING_TYPE l_linestatus = e12->l_linestatus;
          STRING_TYPE l_shipdate = e12->l_shipdate;
          STRING_TYPE l_commitdate = e12->l_commitdate;
          STRING_TYPE l_receiptdate = e12->l_receiptdate;
          STRING_TYPE l_shipinstruct = e12->l_shipinstruct;
          STRING_TYPE l_shipmode = e12->l_shipmode;
          STRING_TYPE l_comment = e12->l_comment;
          long v12 = e12->__av;
          TMP_lineitem_V_lineitem_Q2.addOrDelOnZero(se16.modify(partkey, suppkey), (v12 * Ulift<10>(orderkey, l_quantity)));
        }
      }

      TMP_lineitem_V_lineitempartsupp_Q2.clear();
      { // foreach
        TMP_lineitem_V_lineitem_Q2_entry *e13 = TMP_lineitem_V_lineitem_Q2.head;
        while (e13)
        {
          int partkey = e13->PARTKEY;
          int suppkey = e13->SUPPKEY;
          RingFactorizedRelation<10, int, DOUBLE_TYPE> &v13 = e13->__av;
          TMP_lineitem_V_lineitempartsupp_Q2.addOrDelOnZero(se17.modify(partkey), ((v13 * V_partsupp_Q2.getValueOrDefault(se18.modify(partkey, suppkey))) * Ulift<8>(suppkey)));
          e13 = e13->nxt;
        }
      }

      { // foreach
        TMP_lineitem_V_lineitempartsupp_Q2_entry *e14 = TMP_lineitem_V_lineitempartsupp_Q2.head;
        while (e14)
        {
          int partkey = e14->PARTKEY;
          RingFactorizedRelation<8, int> &v14 = e14->__av;
          V_lineitempartpartsupp_Q2 += ((v14 * V_part_Q2.getValueOrDefault(se20.modify(partkey))) * Ulift<7>(partkey));
          e14 = e14->nxt;
        }
      }

      { // foreach
        TMP_lineitem_V_lineitem_Q2_entry *e15 = TMP_lineitem_V_lineitem_Q2.head;
        while (e15)
        {
          int partkey = e15->PARTKEY;
          int suppkey = e15->SUPPKEY;
          RingFactorizedRelation<10, int, DOUBLE_TYPE> &v15 = e15->__av;
          V_lineitem_Q2.addOrDelOnZero(se21.modify(partkey, suppkey), v15);
          e15 = e15->nxt;
        }
      }

      { // foreach
        TMP_lineitem_V_lineitempartsupp_Q2_entry *e16 = TMP_lineitem_V_lineitempartsupp_Q2.head;
        while (e16)
        {
          int partkey = e16->PARTKEY;
          RingFactorizedRelation<8, int> &v16 = e16->__av;
          V_lineitempartsupp_Q2.addOrDelOnZero(se22.modify(partkey), v16);
          e16 = e16->nxt;
        }
      }
    }

    void on_batch_update_part(const std::vector<DELTA_part_entry>::iterator &begin, const std::vector<DELTA_part_entry>::iterator &end)
    {
      long batchSize = std::distance(begin, end);

      tN += batchSize;
      TMP_part_V_part_Q2.clear();
      { // foreach
        for (std::vector<DELTA_part_entry>::iterator e17 = begin; e17 != end; e17++)
        {
          int partkey = e17->partkey;
          STRING_TYPE p_name = e17->p_name;
          STRING_TYPE p_mfgr = e17->p_mfgr;
          STRING_TYPE p_brand = e17->p_brand;
          STRING_TYPE p_type = e17->p_type;
          int p_size = e17->p_size;
          STRING_TYPE p_container = e17->p_container;
          DOUBLE_TYPE p_retailprice = e17->p_retailprice;
          STRING_TYPE p_comment = e17->p_comment;
          long v17 = e17->__av;
          TMP_part_V_part_Q2.addOrDelOnZero(se23.modify(partkey), (v17 * Ulift<12>(p_name)));
        }
      }

      { // foreach
        TMP_part_V_part_Q2_entry *e18 = TMP_part_V_part_Q2.head;
        while (e18)
        {
          int partkey = e18->PARTKEY;
          RingFactorizedRelation<12, STRING_TYPE> &v18 = e18->__av;
          V_lineitempartpartsupp_Q2 += ((v18 * V_lineitempartsupp_Q2.getValueOrDefault(se25.modify(partkey))) * Ulift<7>(partkey));
          e18 = e18->nxt;
        }
      }

      { // foreach
        TMP_part_V_part_Q2_entry *e19 = TMP_part_V_part_Q2.head;
        while (e19)
        {
          int partkey = e19->PARTKEY;
          RingFactorizedRelation<12, STRING_TYPE> &v19 = e19->__av;
          V_part_Q2.addOrDelOnZero(se26.modify(partkey), v19);
          e19 = e19->nxt;
        }
      }
    }

    void on_system_ready_event()
    {
    }

  private:
    Stopwatch update_timer;
    long update_time = 0;
    long accumulated_tuples = 0;
    long snapshot_interval = 50000;

    /* Preallocated map entries (to avoid recreation of temporary objects) */
    TMP_orders_V_orders_Q1_entry se1;
    V_Q2_Q1_entry se3;
    V_orders_Q1_entry se4;
    TMP_Q2_V_Q2_Q1_entry se5;
    V_orders_Q1_entry se7;
    V_Q2_Q1_entry se8;
    TMP_partsupp_V_partsupp_Q2_entry se9;
    TMP_partsupp_V_lineitempartsupp_Q2_entry se10;
    V_lineitem_Q2_entry se11;
    V_part_Q2_entry se13;
    V_partsupp_Q2_entry se14;
    V_lineitempartsupp_Q2_entry se15;
    TMP_lineitem_V_lineitem_Q2_entry se16;
    TMP_lineitem_V_lineitempartsupp_Q2_entry se17;
    V_partsupp_Q2_entry se18;
    V_part_Q2_entry se20;
    V_lineitem_Q2_entry se21;
    V_lineitempartsupp_Q2_entry se22;
    TMP_part_V_part_Q2_entry se23;
    V_lineitempartsupp_Q2_entry se25;
    V_part_Q2_entry se26;

    /* Data structures used for storing materialized views */
    TMP_orders_V_orders_Q1_map TMP_orders_V_orders_Q1;
    RingFactorizedRelation<0, int> TMP_orders_V_Q2orders_Q1;
    TMP_Q2_V_Q2_Q1_map TMP_Q2_V_Q2_Q1;
    RingFactorizedRelation<0, int> TMP_Q2_V_Q2orders_Q1;
    TMP_partsupp_V_partsupp_Q2_map TMP_partsupp_V_partsupp_Q2;
    TMP_partsupp_V_lineitempartsupp_Q2_map TMP_partsupp_V_lineitempartsupp_Q2;
    TMP_lineitem_V_lineitem_Q2_map TMP_lineitem_V_lineitem_Q2;
    TMP_lineitem_V_lineitempartsupp_Q2_map TMP_lineitem_V_lineitempartsupp_Q2;
    RingFactorizedRelation<7, int> TMP_partsupp_V_lineitempartpartsupp_Q2;
    RingFactorizedRelation<7, int> TMP_lineitem_V_lineitempartpartsupp_Q2;
    TMP_part_V_part_Q2_map TMP_part_V_part_Q2;
    RingFactorizedRelation<7, int> TMP_part_V_lineitempartpartsupp_Q2;
    DELTA_orders_map DELTA_orders;
    DELTA_lineitem_map DELTA_lineitem;
    DELTA_partsupp_map DELTA_partsupp;
    DELTA_part_map DELTA_part;
    DELTA_Q2_map DELTA_Q2;
  };

}