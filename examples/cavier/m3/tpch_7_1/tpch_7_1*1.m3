---------------- TYPE DEFINITIONS ---------------
CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

-------------------- SOURCES --------------------
CREATE STREAM Q1 (N_NAME string,R_NAME string,NATIONKEY int,REGIONKEY int)
  FROM FILE './data/tpch/Q1.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM lineitem (ORDERKEY int,PARTKEY int,SUPPKEY int,L_LINENUMBER int,L_QUANTITY double,L_EXTENDEDPRICE double,L_DISCOUNT double,L_TAX double,L_RETURNFLAG string,L_LINESTATUS string,L_SHIPDATE string,L_COMMITDATE string,L_RECEIPTDATE string,L_SHIPINSTRUCT string,L_SHIPMODE string,L_COMMENT string)
  FROM FILE './data/tpch/Lineitem.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM Q3 (N_NAME string,R_NAME string,NATIONKEY int,REGIONKEY int,C_NAME string,ORDERKEY int,CUSTKEY int,O_ORDERSTATUS string)
  FROM FILE './data/tpch/Q3.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM orders (ORDERKEY int,CUSTKEY int,O_ORDERSTATUS string,O_TOTALPRICE double,O_ORDERDATE string,O_ORDERPRIORITY string,O_CLERK string,O_SHIPPRIORITY int,O_COMMENT string)
  FROM FILE './data/tpch/Orders.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM partsupp (PARTKEY int,SUPPKEY int,PS_AVAILQTY int,PS_SUPPLYCOST double,PS_COMMENT string)
  FROM FILE './data/tpch/Partsupp.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM Q4 (N_NAME string,R_NAME string,NATIONKEY int,REGIONKEY int,C_NAME string,ORDERKEY int,CUSTKEY int,O_ORDERSTATUS string,PARTKEY int,L_LINENUMBER int,SUPPKEY int)
  FROM FILE './data/tpch/Q4.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM Q2 (N_NAME string,R_NAME string,NATIONKEY int,REGIONKEY int,C_NAME string,CUSTKEY int)
  FROM FILE './data/tpch/Q2.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM region (REGIONKEY int,R_NAME string,R_COMMENT string)
  FROM FILE './data/tpch/Region.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM supplier (SUPPKEY int,S_NAME string,S_ADDRESS string,S_NATIONKEY int,S_PHONE string,S_ACCTBAL double,S_COMMENT string)
  FROM FILE './data/tpch/Supplier.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM customer (CUSTKEY int,C_NAME string,C_ADDRESS string,NATIONKEY int,C_PHONE string,C_ACCTBAL double,C_MKTSEGMENT string,C_COMMENT string)
  FROM FILE './data/tpch/Customer.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM Q6 (N_NAME string,R_NAME string,NATIONKEY int,REGIONKEY int,C_NAME string,ORDERKEY int,CUSTKEY int,O_ORDERSTATUS string,PARTKEY int,L_LINENUMBER int,SUPPKEY int,PS_AVAILQTY int,P_NAME string)
  FROM FILE './data/tpch/Q6.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM nation (NATIONKEY int,N_NAME string,REGIONKEY int,N_COMMENT string)
  FROM FILE './data/tpch/Nation.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM part (PARTKEY int,P_NAME string,P_MFGR string,P_BRAND string,P_TYPE string,P_SIZE int,P_CONTAINER string,P_RETAILPRICE double,P_COMMENT string)
  FROM FILE './data/tpch/Part.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM Q5 (N_NAME string,R_NAME string,NATIONKEY int,REGIONKEY int,C_NAME string,ORDERKEY int,CUSTKEY int,O_ORDERSTATUS string,PARTKEY int,L_LINENUMBER int,SUPPKEY int,PS_AVAILQTY int)
  FROM FILE './data/tpch/Q5.tbl' LINE DELIMITED CSV (delimiter := '|');

-------------------- MAPS --------------------
-- Q3

DECLARE MAP V_Q2orders(RingFactorizedRelation<[0, int]>)[][] :=
AggSum([],
 ((V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY]<Local> * V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY]<Local>) * [lift<0>: RingFactorizedRelation<[0, int]>](CUSTKEY))
);

DECLARE MAP V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY: int] :=
AggSum([CUSTKEY],
 ((orders(ORDERKEY,CUSTKEY,O_ORDERSTATUS,O_TOTALPRICE,O_ORDERDATE,O_ORDERPRIORITY,O_CLERK,O_SHIPPRIORITY,O_COMMENT)) * [lift<1>: RingFactorizedRelation<[1, int,string]>](ORDERKEY,O_ORDERSTATUS))
);

DECLARE MAP V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY: int] :=
AggSum([CUSTKEY],
 ((Q2(N_NAME,R_NAME,NATIONKEY,REGIONKEY,C_NAME,CUSTKEY)) * [lift<3>: RingFactorizedRelation<[3, int,int,string,string,string]>](REGIONKEY,NATIONKEY,C_NAME,N_NAME,R_NAME))
);
-- Q5

DECLARE MAP V_Q4partsupp(RingFactorizedRelation<[8, int,int]>)[][] :=
AggSum([],
 ((V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY,PARTKEY]<Local> * V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY,PARTKEY]<Local>) * [lift<8>: RingFactorizedRelation<[8, int,int]>](SUPPKEY,PARTKEY))
);

DECLARE MAP V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY: int,PARTKEY: int] :=
AggSum([SUPPKEY, PARTKEY],
 ((Q4(N_NAME,R_NAME,NATIONKEY,REGIONKEY,C_NAME,ORDERKEY,CUSTKEY,O_ORDERSTATUS,PARTKEY,L_LINENUMBER,SUPPKEY)) * [lift<10>: RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>](REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,ORDERKEY,O_ORDERSTATUS,L_LINENUMBER,N_NAME,R_NAME))
);

DECLARE MAP V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY: int,PARTKEY: int] :=
AggSum([SUPPKEY, PARTKEY],
 ((partsupp(PARTKEY,SUPPKEY,PS_AVAILQTY,PS_SUPPLYCOST,PS_COMMENT)) * [lift<19>: RingFactorizedRelation<[19, int]>](PS_AVAILQTY))
);
-- Q6

DECLARE MAP V_Q5part(RingFactorizedRelation<[20, int]>)[][] :=
AggSum([],
 ((V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY]<Local> * V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY]<Local>) * [lift<20>: RingFactorizedRelation<[20, int]>](PARTKEY))
);

DECLARE MAP V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 ((part(PARTKEY,P_NAME,P_MFGR,P_BRAND,P_TYPE,P_SIZE,P_CONTAINER,P_RETAILPRICE,P_COMMENT)) * [lift<21>: RingFactorizedRelation<[21, string]>](P_NAME))
);

DECLARE MAP V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 ((Q5(N_NAME,R_NAME,NATIONKEY,REGIONKEY,C_NAME,ORDERKEY,CUSTKEY,O_ORDERSTATUS,PARTKEY,L_LINENUMBER,SUPPKEY,PS_AVAILQTY)) * [lift<22>: RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>](REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,ORDERKEY,PS_AVAILQTY,O_ORDERSTATUS,SUPPKEY,L_LINENUMBER,N_NAME,R_NAME))
);
-- Q4

DECLARE MAP V_Q3lineitem(RingFactorizedRelation<[33, int]>)[][] :=
AggSum([],
 ((V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY]<Local> * V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY]<Local>) * [lift<33>: RingFactorizedRelation<[33, int]>](ORDERKEY))
);

DECLARE MAP V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY: int] :=
AggSum([ORDERKEY],
 ((lineitem(ORDERKEY,PARTKEY,SUPPKEY,L_LINENUMBER,L_QUANTITY,L_EXTENDEDPRICE,L_DISCOUNT,L_TAX,L_RETURNFLAG,L_LINESTATUS,L_SHIPDATE,L_COMMITDATE,L_RECEIPTDATE,L_SHIPINSTRUCT,L_SHIPMODE,L_COMMENT)) * [lift<34>: RingFactorizedRelation<[34, int,int,int]>](PARTKEY,L_LINENUMBER,SUPPKEY))
);

DECLARE MAP V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY: int] :=
AggSum([ORDERKEY],
 ((Q3(N_NAME,R_NAME,NATIONKEY,REGIONKEY,C_NAME,ORDERKEY,CUSTKEY,O_ORDERSTATUS)) * [lift<37>: RingFactorizedRelation<[37, int,int,string,int,string,string,string]>](REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,O_ORDERSTATUS,N_NAME,R_NAME))
);
-- Q2

DECLARE MAP V_Q1customer(RingFactorizedRelation<[44, int]>)[][] :=
AggSum([],
 ((V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY]<Local> * V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY]<Local>) * [lift<44>: RingFactorizedRelation<[44, int]>](NATIONKEY))
);

DECLARE MAP V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY: int] :=
AggSum([NATIONKEY],
 ((customer(CUSTKEY,C_NAME,C_ADDRESS,NATIONKEY,C_PHONE,C_ACCTBAL,C_MKTSEGMENT,C_COMMENT)) * [lift<45>: RingFactorizedRelation<[45, string,int]>](C_NAME,CUSTKEY))
);

DECLARE MAP V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY: int] :=
AggSum([NATIONKEY],
 ((Q1(N_NAME,R_NAME,NATIONKEY,REGIONKEY)) * [lift<47>: RingFactorizedRelation<[47, int,string,string]>](REGIONKEY,N_NAME,R_NAME))
);
-- Q7

DECLARE MAP V_Q6supplier(RingFactorizedRelation<[50, int]>)[][] :=
AggSum([],
 ((V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY]<Local> * V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY]<Local>) * [lift<50>: RingFactorizedRelation<[50, int]>](SUPPKEY))
);

DECLARE MAP V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY: int] :=
AggSum([SUPPKEY],
 ((Q6(N_NAME,R_NAME,NATIONKEY,REGIONKEY,C_NAME,ORDERKEY,CUSTKEY,O_ORDERSTATUS,PARTKEY,L_LINENUMBER,SUPPKEY,PS_AVAILQTY,P_NAME)) * [lift<51>: RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>](PARTKEY,REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,ORDERKEY,P_NAME,O_ORDERSTATUS,PS_AVAILQTY,L_LINENUMBER,N_NAME,R_NAME))
);

DECLARE MAP V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY: int] :=
AggSum([SUPPKEY],
 ((supplier(SUPPKEY,S_NAME,S_ADDRESS,S_NATIONKEY,S_PHONE,S_ACCTBAL,S_COMMENT)) * [lift<63>: RingFactorizedRelation<[63, string]>](S_NAME))
);
-- Q1

DECLARE MAP V_nationregion(RingFactorizedRelation<[64, int]>)[][] :=
AggSum([],
 ((V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY]<Local> * V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY]<Local>) * [lift<64>: RingFactorizedRelation<[64, int]>](REGIONKEY))
);

DECLARE MAP V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY: int] :=
AggSum([REGIONKEY],
 ((region(REGIONKEY,R_NAME,R_COMMENT)) * [lift<65>: RingFactorizedRelation<[65, string]>](R_NAME))
);

DECLARE MAP V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY: int] :=
AggSum([REGIONKEY],
 ((nation(NATIONKEY,N_NAME,REGIONKEY,N_COMMENT)) * [lift<66>: RingFactorizedRelation<[66, int,string]>](NATIONKEY,N_NAME))
);
-- Q3
DECLARE MAP TMP_orders_V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY: int] :=
AggSum([CUSTKEY],
 (((DELTA orders)(ORDERKEY,CUSTKEY,O_ORDERSTATUS,O_TOTALPRICE,O_ORDERDATE,O_ORDERPRIORITY,O_CLERK,O_SHIPPRIORITY,O_COMMENT)) * [lift<1>: RingFactorizedRelation<[1, int,string]>](ORDERKEY,O_ORDERSTATUS))
);
DECLARE MAP TMP_orders_V_Q2orders(RingFactorizedRelation<[0, int]>)[][] :=
AggSum([],
 ((TMP_orders_V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY]<Local> * V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY]<Local>) * [lift<0>: RingFactorizedRelation<[0, int]>](CUSTKEY))
);
DECLARE MAP TMP_Q2_V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY: int] :=
AggSum([CUSTKEY],
 (((DELTA Q2)(N_NAME,R_NAME,NATIONKEY,REGIONKEY,C_NAME,CUSTKEY)) * [lift<3>: RingFactorizedRelation<[3, int,int,string,string,string]>](REGIONKEY,NATIONKEY,C_NAME,N_NAME,R_NAME))
);
DECLARE MAP TMP_Q2_V_Q2orders(RingFactorizedRelation<[0, int]>)[][] :=
AggSum([],
 ((TMP_Q2_V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY]<Local> * V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY]<Local>) * [lift<0>: RingFactorizedRelation<[0, int]>](CUSTKEY))
);
-- Q5
DECLARE MAP TMP_Q4_V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY: int,PARTKEY: int] :=
AggSum([SUPPKEY, PARTKEY],
 (((DELTA Q4)(N_NAME,R_NAME,NATIONKEY,REGIONKEY,C_NAME,ORDERKEY,CUSTKEY,O_ORDERSTATUS,PARTKEY,L_LINENUMBER,SUPPKEY)) * [lift<10>: RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>](REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,ORDERKEY,O_ORDERSTATUS,L_LINENUMBER,N_NAME,R_NAME))
);
DECLARE MAP TMP_Q4_V_Q4partsupp(RingFactorizedRelation<[8, int,int]>)[][] :=
AggSum([],
 ((TMP_Q4_V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY,PARTKEY]<Local> * V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY,PARTKEY]<Local>) * [lift<8>: RingFactorizedRelation<[8, int,int]>](SUPPKEY,PARTKEY))
);
DECLARE MAP TMP_partsupp_V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY: int,PARTKEY: int] :=
AggSum([SUPPKEY, PARTKEY],
 (((DELTA partsupp)(PARTKEY,SUPPKEY,PS_AVAILQTY,PS_SUPPLYCOST,PS_COMMENT)) * [lift<19>: RingFactorizedRelation<[19, int]>](PS_AVAILQTY))
);
DECLARE MAP TMP_partsupp_V_Q4partsupp(RingFactorizedRelation<[8, int,int]>)[][] :=
AggSum([],
 ((TMP_partsupp_V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY,PARTKEY]<Local> * V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY,PARTKEY]<Local>) * [lift<8>: RingFactorizedRelation<[8, int,int]>](SUPPKEY,PARTKEY))
);
-- Q6
DECLARE MAP TMP_part_V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 (((DELTA part)(PARTKEY,P_NAME,P_MFGR,P_BRAND,P_TYPE,P_SIZE,P_CONTAINER,P_RETAILPRICE,P_COMMENT)) * [lift<21>: RingFactorizedRelation<[21, string]>](P_NAME))
);
DECLARE MAP TMP_part_V_Q5part(RingFactorizedRelation<[20, int]>)[][] :=
AggSum([],
 ((TMP_part_V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY]<Local> * V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY]<Local>) * [lift<20>: RingFactorizedRelation<[20, int]>](PARTKEY))
);
DECLARE MAP TMP_Q5_V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 (((DELTA Q5)(N_NAME,R_NAME,NATIONKEY,REGIONKEY,C_NAME,ORDERKEY,CUSTKEY,O_ORDERSTATUS,PARTKEY,L_LINENUMBER,SUPPKEY,PS_AVAILQTY)) * [lift<22>: RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>](REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,ORDERKEY,PS_AVAILQTY,O_ORDERSTATUS,SUPPKEY,L_LINENUMBER,N_NAME,R_NAME))
);
DECLARE MAP TMP_Q5_V_Q5part(RingFactorizedRelation<[20, int]>)[][] :=
AggSum([],
 ((TMP_Q5_V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY]<Local> * V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY]<Local>) * [lift<20>: RingFactorizedRelation<[20, int]>](PARTKEY))
);
-- Q4
DECLARE MAP TMP_lineitem_V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY: int] :=
AggSum([ORDERKEY],
 (((DELTA lineitem)(ORDERKEY,PARTKEY,SUPPKEY,L_LINENUMBER,L_QUANTITY,L_EXTENDEDPRICE,L_DISCOUNT,L_TAX,L_RETURNFLAG,L_LINESTATUS,L_SHIPDATE,L_COMMITDATE,L_RECEIPTDATE,L_SHIPINSTRUCT,L_SHIPMODE,L_COMMENT)) * [lift<34>: RingFactorizedRelation<[34, int,int,int]>](PARTKEY,L_LINENUMBER,SUPPKEY))
);
DECLARE MAP TMP_lineitem_V_Q3lineitem(RingFactorizedRelation<[33, int]>)[][] :=
AggSum([],
 ((TMP_lineitem_V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY]<Local> * V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY]<Local>) * [lift<33>: RingFactorizedRelation<[33, int]>](ORDERKEY))
);
DECLARE MAP TMP_Q3_V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY: int] :=
AggSum([ORDERKEY],
 (((DELTA Q3)(N_NAME,R_NAME,NATIONKEY,REGIONKEY,C_NAME,ORDERKEY,CUSTKEY,O_ORDERSTATUS)) * [lift<37>: RingFactorizedRelation<[37, int,int,string,int,string,string,string]>](REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,O_ORDERSTATUS,N_NAME,R_NAME))
);
DECLARE MAP TMP_Q3_V_Q3lineitem(RingFactorizedRelation<[33, int]>)[][] :=
AggSum([],
 ((TMP_Q3_V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY]<Local> * V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY]<Local>) * [lift<33>: RingFactorizedRelation<[33, int]>](ORDERKEY))
);
-- Q2
DECLARE MAP TMP_customer_V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY: int] :=
AggSum([NATIONKEY],
 (((DELTA customer)(CUSTKEY,C_NAME,C_ADDRESS,NATIONKEY,C_PHONE,C_ACCTBAL,C_MKTSEGMENT,C_COMMENT)) * [lift<45>: RingFactorizedRelation<[45, string,int]>](C_NAME,CUSTKEY))
);
DECLARE MAP TMP_customer_V_Q1customer(RingFactorizedRelation<[44, int]>)[][] :=
AggSum([],
 ((TMP_customer_V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY]<Local> * V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY]<Local>) * [lift<44>: RingFactorizedRelation<[44, int]>](NATIONKEY))
);
DECLARE MAP TMP_Q1_V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY: int] :=
AggSum([NATIONKEY],
 (((DELTA Q1)(N_NAME,R_NAME,NATIONKEY,REGIONKEY)) * [lift<47>: RingFactorizedRelation<[47, int,string,string]>](REGIONKEY,N_NAME,R_NAME))
);
DECLARE MAP TMP_Q1_V_Q1customer(RingFactorizedRelation<[44, int]>)[][] :=
AggSum([],
 ((TMP_Q1_V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY]<Local> * V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY]<Local>) * [lift<44>: RingFactorizedRelation<[44, int]>](NATIONKEY))
);
-- Q7
DECLARE MAP TMP_Q6_V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY: int] :=
AggSum([SUPPKEY],
 (((DELTA Q6)(N_NAME,R_NAME,NATIONKEY,REGIONKEY,C_NAME,ORDERKEY,CUSTKEY,O_ORDERSTATUS,PARTKEY,L_LINENUMBER,SUPPKEY,PS_AVAILQTY,P_NAME)) * [lift<51>: RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>](PARTKEY,REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,ORDERKEY,P_NAME,O_ORDERSTATUS,PS_AVAILQTY,L_LINENUMBER,N_NAME,R_NAME))
);
DECLARE MAP TMP_Q6_V_Q6supplier(RingFactorizedRelation<[50, int]>)[][] :=
AggSum([],
 ((TMP_Q6_V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY]<Local> * V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY]<Local>) * [lift<50>: RingFactorizedRelation<[50, int]>](SUPPKEY))
);
DECLARE MAP TMP_supplier_V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY: int] :=
AggSum([SUPPKEY],
 (((DELTA supplier)(SUPPKEY,S_NAME,S_ADDRESS,S_NATIONKEY,S_PHONE,S_ACCTBAL,S_COMMENT)) * [lift<63>: RingFactorizedRelation<[63, string]>](S_NAME))
);
DECLARE MAP TMP_supplier_V_Q6supplier(RingFactorizedRelation<[50, int]>)[][] :=
AggSum([],
 ((TMP_supplier_V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY]<Local> * V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY]<Local>) * [lift<50>: RingFactorizedRelation<[50, int]>](SUPPKEY))
);
-- Q1
DECLARE MAP TMP_region_V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY: int] :=
AggSum([REGIONKEY],
 (((DELTA region)(REGIONKEY,R_NAME,R_COMMENT)) * [lift<65>: RingFactorizedRelation<[65, string]>](R_NAME))
);
DECLARE MAP TMP_region_V_nationregion(RingFactorizedRelation<[64, int]>)[][] :=
AggSum([],
 ((TMP_region_V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY]<Local> * V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY]<Local>) * [lift<64>: RingFactorizedRelation<[64, int]>](REGIONKEY))
);
DECLARE MAP TMP_nation_V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY: int] :=
AggSum([REGIONKEY],
 (((DELTA nation)(NATIONKEY,N_NAME,REGIONKEY,N_COMMENT)) * [lift<66>: RingFactorizedRelation<[66, int,string]>](NATIONKEY,N_NAME))
);
DECLARE MAP TMP_nation_V_nationregion(RingFactorizedRelation<[64, int]>)[][] :=
AggSum([],
 ((TMP_nation_V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY]<Local> * V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY]<Local>) * [lift<64>: RingFactorizedRelation<[64, int]>](REGIONKEY))
);

-------------------- QUERIES --------------------
-- Q3
DECLARE QUERY V_Q2orders := V_Q2orders(RingFactorizedRelation<[0, int]>)[][]<Local>;
DECLARE QUERY V_orders := V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY]<Local>;
DECLARE QUERY V_Q2 := V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY]<Local>;
-- Q5
DECLARE QUERY V_Q4partsupp := V_Q4partsupp(RingFactorizedRelation<[8, int,int]>)[][]<Local>;
DECLARE QUERY V_Q4 := V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY,PARTKEY]<Local>;
DECLARE QUERY V_partsupp := V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY,PARTKEY]<Local>;
-- Q6
DECLARE QUERY V_Q5part := V_Q5part(RingFactorizedRelation<[20, int]>)[][]<Local>;
DECLARE QUERY V_part := V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY]<Local>;
DECLARE QUERY V_Q5 := V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY]<Local>;
-- Q4
DECLARE QUERY V_Q3lineitem := V_Q3lineitem(RingFactorizedRelation<[33, int]>)[][]<Local>;
DECLARE QUERY V_lineitem := V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY]<Local>;
DECLARE QUERY V_Q3 := V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY]<Local>;
-- Q2
DECLARE QUERY V_Q1customer := V_Q1customer(RingFactorizedRelation<[44, int]>)[][]<Local>;
DECLARE QUERY V_customer := V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY]<Local>;
DECLARE QUERY V_Q1 := V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY]<Local>;
-- Q7
DECLARE QUERY V_Q6supplier := V_Q6supplier(RingFactorizedRelation<[50, int]>)[][]<Local>;
DECLARE QUERY V_Q6 := V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY]<Local>;
DECLARE QUERY V_supplier := V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY]<Local>;
-- Q1
DECLARE QUERY V_nationregion := V_nationregion(RingFactorizedRelation<[64, int]>)[][]<Local>;
DECLARE QUERY V_region := V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY]<Local>;
DECLARE QUERY V_nation := V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY]<Local>;

-------------------- TRIGGERS --------------------
-- Q3
ON BATCH UPDATE OF orders { 
 TMP_orders_V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY]<Local> := AggSum([CUSTKEY], ((DELTA orders)(ORDERKEY, CUSTKEY, O_ORDERSTATUS, O_TOTALPRICE, O_ORDERDATE, O_ORDERPRIORITY, O_CLERK, O_SHIPPRIORITY, O_COMMENT) * [lift<1>: RingFactorizedRelation<[1, int,string]>](ORDERKEY,O_ORDERSTATUS)));
V_Q2orders(RingFactorizedRelation<[0, int]>)[][]<Local>  +=  AggSum([], (TMP_orders_V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY] * V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY]<Local>) * [lift<0>: RingFactorizedRelation<[0, int]>](CUSTKEY));
V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY]<Local> += TMP_orders_V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY];
}
ON BATCH UPDATE OF Q2 { 
 TMP_Q2_V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY]<Local> := AggSum([CUSTKEY], ((DELTA Q2)(N_NAME, R_NAME, NATIONKEY, REGIONKEY, C_NAME, CUSTKEY) * [lift<3>: RingFactorizedRelation<[3, int,int,string,string,string]>](REGIONKEY,NATIONKEY,C_NAME,N_NAME,R_NAME)));
V_Q2orders(RingFactorizedRelation<[0, int]>)[][]<Local>  +=  AggSum([], (TMP_Q2_V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY] * V_orders(RingFactorizedRelation<[1, int,string]>)[][CUSTKEY]<Local>) * [lift<0>: RingFactorizedRelation<[0, int]>](CUSTKEY));
V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY]<Local> += TMP_Q2_V_Q2(RingFactorizedRelation<[3, int,int,string,string,string]>)[][CUSTKEY];
}
-- Q5
ON BATCH UPDATE OF Q4 { 
 TMP_Q4_V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY,PARTKEY]<Local> := AggSum([SUPPKEY, PARTKEY], ((DELTA Q4)(N_NAME, R_NAME, NATIONKEY, REGIONKEY, C_NAME, ORDERKEY, CUSTKEY, O_ORDERSTATUS, PARTKEY, L_LINENUMBER, SUPPKEY) * [lift<10>: RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>](REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,ORDERKEY,O_ORDERSTATUS,L_LINENUMBER,N_NAME,R_NAME)));
V_Q4partsupp(RingFactorizedRelation<[8, int,int]>)[][]<Local>  +=  AggSum([], (TMP_Q4_V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY,PARTKEY] * V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY,PARTKEY]<Local>) * [lift<8>: RingFactorizedRelation<[8, int,int]>](SUPPKEY,PARTKEY));
V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY,PARTKEY]<Local> += TMP_Q4_V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY,PARTKEY];
}
ON BATCH UPDATE OF partsupp { 
 TMP_partsupp_V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY,PARTKEY]<Local> := AggSum([SUPPKEY, PARTKEY], ((DELTA partsupp)(PARTKEY, SUPPKEY, PS_AVAILQTY, PS_SUPPLYCOST, PS_COMMENT) * [lift<19>: RingFactorizedRelation<[19, int]>](PS_AVAILQTY)));
V_Q4partsupp(RingFactorizedRelation<[8, int,int]>)[][]<Local>  +=  AggSum([], (TMP_partsupp_V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY,PARTKEY] * V_Q4(RingFactorizedRelation<[10, int,int,string,int,int,string,int,string,string]>)[][SUPPKEY,PARTKEY]<Local>) * [lift<8>: RingFactorizedRelation<[8, int,int]>](SUPPKEY,PARTKEY));
V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY,PARTKEY]<Local> += TMP_partsupp_V_partsupp(RingFactorizedRelation<[19, int]>)[][SUPPKEY,PARTKEY];
}
-- Q6
ON BATCH UPDATE OF part { 
 TMP_part_V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY]<Local> := AggSum([PARTKEY], ((DELTA part)(PARTKEY, P_NAME, P_MFGR, P_BRAND, P_TYPE, P_SIZE, P_CONTAINER, P_RETAILPRICE, P_COMMENT) * [lift<21>: RingFactorizedRelation<[21, string]>](P_NAME)));
V_Q5part(RingFactorizedRelation<[20, int]>)[][]<Local>  +=  AggSum([], (TMP_part_V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY] * V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY]<Local>) * [lift<20>: RingFactorizedRelation<[20, int]>](PARTKEY));
V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY]<Local> += TMP_part_V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY];
}
ON BATCH UPDATE OF Q5 { 
 TMP_Q5_V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY]<Local> := AggSum([PARTKEY], ((DELTA Q5)(N_NAME, R_NAME, NATIONKEY, REGIONKEY, C_NAME, ORDERKEY, CUSTKEY, O_ORDERSTATUS, PARTKEY, L_LINENUMBER, SUPPKEY, PS_AVAILQTY) * [lift<22>: RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>](REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,ORDERKEY,PS_AVAILQTY,O_ORDERSTATUS,SUPPKEY,L_LINENUMBER,N_NAME,R_NAME)));
V_Q5part(RingFactorizedRelation<[20, int]>)[][]<Local>  +=  AggSum([], (TMP_Q5_V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY] * V_part(RingFactorizedRelation<[21, string]>)[][PARTKEY]<Local>) * [lift<20>: RingFactorizedRelation<[20, int]>](PARTKEY));
V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY]<Local> += TMP_Q5_V_Q5(RingFactorizedRelation<[22, int,int,string,int,int,int,string,int,int,string,string]>)[][PARTKEY];
}
-- Q4
ON BATCH UPDATE OF lineitem { 
 TMP_lineitem_V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY]<Local> := AggSum([ORDERKEY], ((DELTA lineitem)(ORDERKEY, PARTKEY, SUPPKEY, L_LINENUMBER, L_QUANTITY, L_EXTENDEDPRICE, L_DISCOUNT, L_TAX, L_RETURNFLAG, L_LINESTATUS, L_SHIPDATE, L_COMMITDATE, L_RECEIPTDATE, L_SHIPINSTRUCT, L_SHIPMODE, L_COMMENT) * [lift<34>: RingFactorizedRelation<[34, int,int,int]>](PARTKEY,L_LINENUMBER,SUPPKEY)));
V_Q3lineitem(RingFactorizedRelation<[33, int]>)[][]<Local>  +=  AggSum([], (TMP_lineitem_V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY] * V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY]<Local>) * [lift<33>: RingFactorizedRelation<[33, int]>](ORDERKEY));
V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY]<Local> += TMP_lineitem_V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY];
}
ON BATCH UPDATE OF Q3 { 
 TMP_Q3_V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY]<Local> := AggSum([ORDERKEY], ((DELTA Q3)(N_NAME, R_NAME, NATIONKEY, REGIONKEY, C_NAME, ORDERKEY, CUSTKEY, O_ORDERSTATUS) * [lift<37>: RingFactorizedRelation<[37, int,int,string,int,string,string,string]>](REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,O_ORDERSTATUS,N_NAME,R_NAME)));
V_Q3lineitem(RingFactorizedRelation<[33, int]>)[][]<Local>  +=  AggSum([], (TMP_Q3_V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY] * V_lineitem(RingFactorizedRelation<[34, int,int,int]>)[][ORDERKEY]<Local>) * [lift<33>: RingFactorizedRelation<[33, int]>](ORDERKEY));
V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY]<Local> += TMP_Q3_V_Q3(RingFactorizedRelation<[37, int,int,string,int,string,string,string]>)[][ORDERKEY];
}
-- Q2
ON BATCH UPDATE OF customer { 
 TMP_customer_V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY]<Local> := AggSum([NATIONKEY], ((DELTA customer)(CUSTKEY, C_NAME, C_ADDRESS, NATIONKEY, C_PHONE, C_ACCTBAL, C_MKTSEGMENT, C_COMMENT) * [lift<45>: RingFactorizedRelation<[45, string,int]>](C_NAME,CUSTKEY)));
V_Q1customer(RingFactorizedRelation<[44, int]>)[][]<Local>  +=  AggSum([], (TMP_customer_V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY] * V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY]<Local>) * [lift<44>: RingFactorizedRelation<[44, int]>](NATIONKEY));
V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY]<Local> += TMP_customer_V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY];
}
ON BATCH UPDATE OF Q1 { 
 TMP_Q1_V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY]<Local> := AggSum([NATIONKEY], ((DELTA Q1)(N_NAME, R_NAME, NATIONKEY, REGIONKEY) * [lift<47>: RingFactorizedRelation<[47, int,string,string]>](REGIONKEY,N_NAME,R_NAME)));
V_Q1customer(RingFactorizedRelation<[44, int]>)[][]<Local>  +=  AggSum([], (TMP_Q1_V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY] * V_customer(RingFactorizedRelation<[45, string,int]>)[][NATIONKEY]<Local>) * [lift<44>: RingFactorizedRelation<[44, int]>](NATIONKEY));
V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY]<Local> += TMP_Q1_V_Q1(RingFactorizedRelation<[47, int,string,string]>)[][NATIONKEY];
}
-- Q7
ON BATCH UPDATE OF Q6 { 
 TMP_Q6_V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY]<Local> := AggSum([SUPPKEY], ((DELTA Q6)(N_NAME, R_NAME, NATIONKEY, REGIONKEY, C_NAME, ORDERKEY, CUSTKEY, O_ORDERSTATUS, PARTKEY, L_LINENUMBER, SUPPKEY, PS_AVAILQTY, P_NAME) * [lift<51>: RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>](PARTKEY,REGIONKEY,NATIONKEY,C_NAME,CUSTKEY,ORDERKEY,P_NAME,O_ORDERSTATUS,PS_AVAILQTY,L_LINENUMBER,N_NAME,R_NAME)));
V_Q6supplier(RingFactorizedRelation<[50, int]>)[][]<Local>  +=  AggSum([], (TMP_Q6_V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY] * V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY]<Local>) * [lift<50>: RingFactorizedRelation<[50, int]>](SUPPKEY));
V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY]<Local> += TMP_Q6_V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY];
}
ON BATCH UPDATE OF supplier { 
 TMP_supplier_V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY]<Local> := AggSum([SUPPKEY], ((DELTA supplier)(SUPPKEY, S_NAME, S_ADDRESS, S_NATIONKEY, S_PHONE, S_ACCTBAL, S_COMMENT) * [lift<63>: RingFactorizedRelation<[63, string]>](S_NAME)));
V_Q6supplier(RingFactorizedRelation<[50, int]>)[][]<Local>  +=  AggSum([], (TMP_supplier_V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY] * V_Q6(RingFactorizedRelation<[51, int,int,int,string,int,int,string,string,int,int,string,string]>)[][SUPPKEY]<Local>) * [lift<50>: RingFactorizedRelation<[50, int]>](SUPPKEY));
V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY]<Local> += TMP_supplier_V_supplier(RingFactorizedRelation<[63, string]>)[][SUPPKEY];
}
-- Q1
ON BATCH UPDATE OF region { 
 TMP_region_V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY]<Local> := AggSum([REGIONKEY], ((DELTA region)(REGIONKEY, R_NAME, R_COMMENT) * [lift<65>: RingFactorizedRelation<[65, string]>](R_NAME)));
V_nationregion(RingFactorizedRelation<[64, int]>)[][]<Local>  +=  AggSum([], (TMP_region_V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY] * V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY]<Local>) * [lift<64>: RingFactorizedRelation<[64, int]>](REGIONKEY));
V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY]<Local> += TMP_region_V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY];
}
ON BATCH UPDATE OF nation { 
 TMP_nation_V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY]<Local> := AggSum([REGIONKEY], ((DELTA nation)(NATIONKEY, N_NAME, REGIONKEY, N_COMMENT) * [lift<66>: RingFactorizedRelation<[66, int,string]>](NATIONKEY,N_NAME)));
V_nationregion(RingFactorizedRelation<[64, int]>)[][]<Local>  +=  AggSum([], (TMP_nation_V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY] * V_region(RingFactorizedRelation<[65, string]>)[][REGIONKEY]<Local>) * [lift<64>: RingFactorizedRelation<[64, int]>](REGIONKEY));
V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY]<Local> += TMP_nation_V_nation(RingFactorizedRelation<[66, int,string]>)[][REGIONKEY];
}

ON SYSTEM READY {

}