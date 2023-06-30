---------------- TYPE DEFINITIONS ---------------
CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

-------------------- SOURCES --------------------
CREATE STREAM supplier (SUPPKEY int,S_NAME string,S_ADDRESS string,S_NATIONKEY int,S_PHONE string,S_ACCTBAL double,S_COMMENT string)
  FROM FILE './data/tpch/Supplier.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM Q2 (O_ORDERSTATUS string,C_NAME string,ORDERKEY int,CUSTKEY int)
  FROM FILE './data/tpch/Q2.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM Q5 (PS_AVAILQTY int,PARTKEY int,SUPPKEY int,L_LINENUMBER int,ORDERKEY int,O_ORDERSTATUS string,CUSTKEY int,C_NAME string)
  FROM FILE './data/tpch/Q5.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM orders (ORDERKEY int,CUSTKEY int,O_ORDERSTATUS string,O_TOTALPRICE double,O_ORDERDATE string,O_ORDERPRIORITY string,O_CLERK string,O_SHIPPRIORITY int,O_COMMENT string)
  FROM FILE './data/tpch/Orders.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM partsupp (PARTKEY int,SUPPKEY int,PS_AVAILQTY int,PS_SUPPLYCOST double,PS_COMMENT string)
  FROM FILE './data/tpch/Partsupp.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM Q3 (PS_AVAILQTY int,PARTKEY int,SUPPKEY int,L_LINENUMBER int,ORDERKEY int,O_ORDERSTATUS string,CUSTKEY int)
  FROM FILE './data/tpch/Q3.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM Q6 (PS_AVAILQTY int,PARTKEY int,SUPPKEY int,L_LINENUMBER int,ORDERKEY int,O_ORDERSTATUS string,CUSTKEY int,C_NAME string,P_NAME string)
  FROM FILE './data/tpch/Q6.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM part (PARTKEY int,P_NAME string,P_MFGR string,P_BRAND string,P_TYPE string,P_SIZE int,P_CONTAINER string,P_RETAILPRICE double,P_COMMENT string)
  FROM FILE './data/tpch/Part.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM Q1 (PS_AVAILQTY int,PARTKEY int,SUPPKEY int,L_LINENUMBER int,ORDERKEY int)
  FROM FILE './data/tpch/Q1.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM customer (CUSTKEY int,C_NAME string,C_ADDRESS string,NATIONKEY int,C_PHONE string,C_ACCTBAL double,C_MKTSEGMENT string,C_COMMENT string)
  FROM FILE './data/tpch/Customer.tbl' LINE DELIMITED CSV (delimiter := '|');
CREATE STREAM lineitem (ORDERKEY int,PARTKEY int,SUPPKEY int,L_LINENUMBER int,L_QUANTITY double,L_EXTENDEDPRICE double,L_DISCOUNT double,L_TAX double,L_RETURNFLAG string,L_LINESTATUS string,L_SHIPDATE string,L_COMMITDATE string,L_RECEIPTDATE string,L_SHIPINSTRUCT string,L_SHIPMODE string,L_COMMENT string)
  FROM FILE './data/tpch/Lineitem.tbl' LINE DELIMITED CSV (delimiter := '|');

-------------------- MAPS --------------------
-- Q5

DECLARE MAP V_Q2Q3(RingFactorizedRelation<[0, int,int,string]>)[][] :=
AggSum([],
 ((V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local> * V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local>) * [lift<0>: RingFactorizedRelation<[0, int,int,string]>](CUSTKEY,ORDERKEY,O_ORDERSTATUS))
);

DECLARE MAP V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY: int,ORDERKEY: int,O_ORDERSTATUS: string] :=
AggSum([CUSTKEY, ORDERKEY, O_ORDERSTATUS],
 ((Q2(O_ORDERSTATUS,C_NAME,ORDERKEY,CUSTKEY)) * [lift<3>: RingFactorizedRelation<[3, string]>](C_NAME))
);

DECLARE MAP V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY: int,ORDERKEY: int,O_ORDERSTATUS: string] :=
AggSum([CUSTKEY, ORDERKEY, O_ORDERSTATUS],
 ((Q3(PS_AVAILQTY,PARTKEY,SUPPKEY,L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,CUSTKEY)) * [lift<4>: RingFactorizedRelation<[4, int,int,int,int]>](L_LINENUMBER,PARTKEY,PS_AVAILQTY,SUPPKEY))
);
-- Q6

DECLARE MAP V_Q5part(RingFactorizedRelation<[8, int]>)[][] :=
AggSum([],
 ((V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY]<Local> * V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY]<Local>) * [lift<8>: RingFactorizedRelation<[8, int]>](PARTKEY))
);

DECLARE MAP V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 ((part(PARTKEY,P_NAME,P_MFGR,P_BRAND,P_TYPE,P_SIZE,P_CONTAINER,P_RETAILPRICE,P_COMMENT)) * [lift<9>: RingFactorizedRelation<[9, string]>](P_NAME))
);

DECLARE MAP V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 ((Q5(PS_AVAILQTY,PARTKEY,SUPPKEY,L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,CUSTKEY,C_NAME)) * [lift<10>: RingFactorizedRelation<[10, int,int,string,int,int,string,int]>](L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,PS_AVAILQTY,CUSTKEY,C_NAME,SUPPKEY))
);
-- Q3

DECLARE MAP V_Q1orders(RingFactorizedRelation<[17, int]>)[][] :=
AggSum([],
 ((V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY]<Local> * V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY]<Local>) * [lift<17>: RingFactorizedRelation<[17, int]>](ORDERKEY))
);

DECLARE MAP V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY: int] :=
AggSum([ORDERKEY],
 ((Q1(PS_AVAILQTY,PARTKEY,SUPPKEY,L_LINENUMBER,ORDERKEY)) * [lift<18>: RingFactorizedRelation<[18, int,int,int,int]>](L_LINENUMBER,PARTKEY,PS_AVAILQTY,SUPPKEY))
);

DECLARE MAP V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY: int] :=
AggSum([ORDERKEY],
 ((orders(ORDERKEY,CUSTKEY,O_ORDERSTATUS,O_TOTALPRICE,O_ORDERDATE,O_ORDERPRIORITY,O_CLERK,O_SHIPPRIORITY,O_COMMENT)) * [lift<22>: RingFactorizedRelation<[22, string,int]>](O_ORDERSTATUS,CUSTKEY))
);
-- Q4

DECLARE MAP V_Q1part(RingFactorizedRelation<[24, int]>)[][] :=
AggSum([],
 ((V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY]<Local> * V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY]<Local>) * [lift<24>: RingFactorizedRelation<[24, int]>](PARTKEY))
);

DECLARE MAP V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 ((Q1(PS_AVAILQTY,PARTKEY,SUPPKEY,L_LINENUMBER,ORDERKEY)) * [lift<25>: RingFactorizedRelation<[25, int,int,int,int]>](L_LINENUMBER,ORDERKEY,PS_AVAILQTY,SUPPKEY))
);

DECLARE MAP V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 ((part(PARTKEY,P_NAME,P_MFGR,P_BRAND,P_TYPE,P_SIZE,P_CONTAINER,P_RETAILPRICE,P_COMMENT)) * [lift<29>: RingFactorizedRelation<[29, string]>](P_NAME))
);
-- Q7

DECLARE MAP V_Q6supplier(RingFactorizedRelation<[30, int]>)[][] :=
AggSum([],
 ((V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY]<Local> * V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY]<Local>) * [lift<30>: RingFactorizedRelation<[30, int]>](SUPPKEY))
);

DECLARE MAP V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY: int] :=
AggSum([SUPPKEY],
 ((Q6(PS_AVAILQTY,PARTKEY,SUPPKEY,L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,CUSTKEY,C_NAME,P_NAME)) * [lift<31>: RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>](L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,PARTKEY,P_NAME,PS_AVAILQTY,CUSTKEY,C_NAME))
);

DECLARE MAP V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY: int] :=
AggSum([SUPPKEY],
 ((supplier(SUPPKEY,S_NAME,S_ADDRESS,S_NATIONKEY,S_PHONE,S_ACCTBAL,S_COMMENT)) * [lift<39>: RingFactorizedRelation<[39, string]>](S_NAME))
);
-- Q1

DECLARE MAP V_lineitempartsupp(RingFactorizedRelation<[40, int,int]>)[][] :=
AggSum([],
 ((V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY,PARTKEY]<Local> * V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY,PARTKEY]<Local>) * [lift<40>: RingFactorizedRelation<[40, int,int]>](SUPPKEY,PARTKEY))
);

DECLARE MAP V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY: int,PARTKEY: int] :=
AggSum([SUPPKEY, PARTKEY],
 ((partsupp(PARTKEY,SUPPKEY,PS_AVAILQTY,PS_SUPPLYCOST,PS_COMMENT)) * [lift<42>: RingFactorizedRelation<[42, int]>](PS_AVAILQTY))
);

DECLARE MAP V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY: int,PARTKEY: int] :=
AggSum([SUPPKEY, PARTKEY],
 ((lineitem(ORDERKEY,PARTKEY,SUPPKEY,L_LINENUMBER,L_QUANTITY,L_EXTENDEDPRICE,L_DISCOUNT,L_TAX,L_RETURNFLAG,L_LINESTATUS,L_SHIPDATE,L_COMMITDATE,L_RECEIPTDATE,L_SHIPINSTRUCT,L_SHIPMODE,L_COMMENT)) * [lift<43>: RingFactorizedRelation<[43, int,int]>](ORDERKEY,L_LINENUMBER))
);
-- Q2

DECLARE MAP V_customerorders(RingFactorizedRelation<[45, int]>)[][] :=
AggSum([],
 ((V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY]<Local> * V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY]<Local>) * [lift<45>: RingFactorizedRelation<[45, int]>](CUSTKEY))
);

DECLARE MAP V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY: int] :=
AggSum([CUSTKEY],
 ((orders(ORDERKEY,CUSTKEY,O_ORDERSTATUS,O_TOTALPRICE,O_ORDERDATE,O_ORDERPRIORITY,O_CLERK,O_SHIPPRIORITY,O_COMMENT)) * [lift<46>: RingFactorizedRelation<[46, int,string]>](ORDERKEY,O_ORDERSTATUS))
);

DECLARE MAP V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY: int] :=
AggSum([CUSTKEY],
 ((customer(CUSTKEY,C_NAME,C_ADDRESS,NATIONKEY,C_PHONE,C_ACCTBAL,C_MKTSEGMENT,C_COMMENT)) * [lift<48>: RingFactorizedRelation<[48, string]>](C_NAME))
);
-- Q5
DECLARE MAP TMP_Q2_V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY: int,ORDERKEY: int,O_ORDERSTATUS: string] :=
AggSum([CUSTKEY, ORDERKEY, O_ORDERSTATUS],
 (((DELTA Q2)(O_ORDERSTATUS,C_NAME,ORDERKEY,CUSTKEY)) * [lift<3>: RingFactorizedRelation<[3, string]>](C_NAME))
);
DECLARE MAP TMP_Q2_V_Q2Q3(RingFactorizedRelation<[0, int,int,string]>)[][] :=
AggSum([],
 ((TMP_Q2_V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local> * V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local>) * [lift<0>: RingFactorizedRelation<[0, int,int,string]>](CUSTKEY,ORDERKEY,O_ORDERSTATUS))
);
DECLARE MAP TMP_Q3_V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY: int,ORDERKEY: int,O_ORDERSTATUS: string] :=
AggSum([CUSTKEY, ORDERKEY, O_ORDERSTATUS],
 (((DELTA Q3)(PS_AVAILQTY,PARTKEY,SUPPKEY,L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,CUSTKEY)) * [lift<4>: RingFactorizedRelation<[4, int,int,int,int]>](L_LINENUMBER,PARTKEY,PS_AVAILQTY,SUPPKEY))
);
DECLARE MAP TMP_Q3_V_Q2Q3(RingFactorizedRelation<[0, int,int,string]>)[][] :=
AggSum([],
 ((TMP_Q3_V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local> * V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local>) * [lift<0>: RingFactorizedRelation<[0, int,int,string]>](CUSTKEY,ORDERKEY,O_ORDERSTATUS))
);
-- Q6
DECLARE MAP TMP_part_V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 (((DELTA part)(PARTKEY,P_NAME,P_MFGR,P_BRAND,P_TYPE,P_SIZE,P_CONTAINER,P_RETAILPRICE,P_COMMENT)) * [lift<9>: RingFactorizedRelation<[9, string]>](P_NAME))
);
DECLARE MAP TMP_part_V_Q5part(RingFactorizedRelation<[8, int]>)[][] :=
AggSum([],
 ((TMP_part_V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY]<Local> * V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY]<Local>) * [lift<8>: RingFactorizedRelation<[8, int]>](PARTKEY))
);
DECLARE MAP TMP_Q5_V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 (((DELTA Q5)(PS_AVAILQTY,PARTKEY,SUPPKEY,L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,CUSTKEY,C_NAME)) * [lift<10>: RingFactorizedRelation<[10, int,int,string,int,int,string,int]>](L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,PS_AVAILQTY,CUSTKEY,C_NAME,SUPPKEY))
);
DECLARE MAP TMP_Q5_V_Q5part(RingFactorizedRelation<[8, int]>)[][] :=
AggSum([],
 ((TMP_Q5_V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY]<Local> * V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY]<Local>) * [lift<8>: RingFactorizedRelation<[8, int]>](PARTKEY))
);
-- Q3
DECLARE MAP TMP_Q1_V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY: int] :=
AggSum([ORDERKEY],
 (((DELTA Q1)(PS_AVAILQTY,PARTKEY,SUPPKEY,L_LINENUMBER,ORDERKEY)) * [lift<18>: RingFactorizedRelation<[18, int,int,int,int]>](L_LINENUMBER,PARTKEY,PS_AVAILQTY,SUPPKEY))
);
DECLARE MAP TMP_Q1_V_Q1orders(RingFactorizedRelation<[17, int]>)[][] :=
AggSum([],
 ((TMP_Q1_V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY]<Local> * V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY]<Local>) * [lift<17>: RingFactorizedRelation<[17, int]>](ORDERKEY))
);
DECLARE MAP TMP_orders_V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY: int] :=
AggSum([ORDERKEY],
 (((DELTA orders)(ORDERKEY,CUSTKEY,O_ORDERSTATUS,O_TOTALPRICE,O_ORDERDATE,O_ORDERPRIORITY,O_CLERK,O_SHIPPRIORITY,O_COMMENT)) * [lift<22>: RingFactorizedRelation<[22, string,int]>](O_ORDERSTATUS,CUSTKEY))
);
DECLARE MAP TMP_orders_V_Q1orders(RingFactorizedRelation<[17, int]>)[][] :=
AggSum([],
 ((TMP_orders_V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY]<Local> * V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY]<Local>) * [lift<17>: RingFactorizedRelation<[17, int]>](ORDERKEY))
);
-- Q4
DECLARE MAP TMP_Q1_V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 (((DELTA Q1)(PS_AVAILQTY,PARTKEY,SUPPKEY,L_LINENUMBER,ORDERKEY)) * [lift<25>: RingFactorizedRelation<[25, int,int,int,int]>](L_LINENUMBER,ORDERKEY,PS_AVAILQTY,SUPPKEY))
);
DECLARE MAP TMP_Q1_V_Q1part(RingFactorizedRelation<[24, int]>)[][] :=
AggSum([],
 ((TMP_Q1_V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY]<Local> * V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY]<Local>) * [lift<24>: RingFactorizedRelation<[24, int]>](PARTKEY))
);
DECLARE MAP TMP_part_V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY: int] :=
AggSum([PARTKEY],
 (((DELTA part)(PARTKEY,P_NAME,P_MFGR,P_BRAND,P_TYPE,P_SIZE,P_CONTAINER,P_RETAILPRICE,P_COMMENT)) * [lift<29>: RingFactorizedRelation<[29, string]>](P_NAME))
);
DECLARE MAP TMP_part_V_Q1part(RingFactorizedRelation<[24, int]>)[][] :=
AggSum([],
 ((TMP_part_V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY]<Local> * V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY]<Local>) * [lift<24>: RingFactorizedRelation<[24, int]>](PARTKEY))
);
-- Q7
DECLARE MAP TMP_Q6_V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY: int] :=
AggSum([SUPPKEY],
 (((DELTA Q6)(PS_AVAILQTY,PARTKEY,SUPPKEY,L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,CUSTKEY,C_NAME,P_NAME)) * [lift<31>: RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>](L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,PARTKEY,P_NAME,PS_AVAILQTY,CUSTKEY,C_NAME))
);
DECLARE MAP TMP_Q6_V_Q6supplier(RingFactorizedRelation<[30, int]>)[][] :=
AggSum([],
 ((TMP_Q6_V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY]<Local> * V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY]<Local>) * [lift<30>: RingFactorizedRelation<[30, int]>](SUPPKEY))
);
DECLARE MAP TMP_supplier_V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY: int] :=
AggSum([SUPPKEY],
 (((DELTA supplier)(SUPPKEY,S_NAME,S_ADDRESS,S_NATIONKEY,S_PHONE,S_ACCTBAL,S_COMMENT)) * [lift<39>: RingFactorizedRelation<[39, string]>](S_NAME))
);
DECLARE MAP TMP_supplier_V_Q6supplier(RingFactorizedRelation<[30, int]>)[][] :=
AggSum([],
 ((TMP_supplier_V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY]<Local> * V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY]<Local>) * [lift<30>: RingFactorizedRelation<[30, int]>](SUPPKEY))
);
-- Q1
DECLARE MAP TMP_partsupp_V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY: int,PARTKEY: int] :=
AggSum([SUPPKEY, PARTKEY],
 (((DELTA partsupp)(PARTKEY,SUPPKEY,PS_AVAILQTY,PS_SUPPLYCOST,PS_COMMENT)) * [lift<42>: RingFactorizedRelation<[42, int]>](PS_AVAILQTY))
);
DECLARE MAP TMP_partsupp_V_lineitempartsupp(RingFactorizedRelation<[40, int,int]>)[][] :=
AggSum([],
 ((TMP_partsupp_V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY,PARTKEY]<Local> * V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY,PARTKEY]<Local>) * [lift<40>: RingFactorizedRelation<[40, int,int]>](SUPPKEY,PARTKEY))
);
DECLARE MAP TMP_lineitem_V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY: int,PARTKEY: int] :=
AggSum([SUPPKEY, PARTKEY],
 (((DELTA lineitem)(ORDERKEY,PARTKEY,SUPPKEY,L_LINENUMBER,L_QUANTITY,L_EXTENDEDPRICE,L_DISCOUNT,L_TAX,L_RETURNFLAG,L_LINESTATUS,L_SHIPDATE,L_COMMITDATE,L_RECEIPTDATE,L_SHIPINSTRUCT,L_SHIPMODE,L_COMMENT)) * [lift<43>: RingFactorizedRelation<[43, int,int]>](ORDERKEY,L_LINENUMBER))
);
DECLARE MAP TMP_lineitem_V_lineitempartsupp(RingFactorizedRelation<[40, int,int]>)[][] :=
AggSum([],
 ((TMP_lineitem_V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY,PARTKEY]<Local> * V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY,PARTKEY]<Local>) * [lift<40>: RingFactorizedRelation<[40, int,int]>](SUPPKEY,PARTKEY))
);
-- Q2
DECLARE MAP TMP_orders_V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY: int] :=
AggSum([CUSTKEY],
 (((DELTA orders)(ORDERKEY,CUSTKEY,O_ORDERSTATUS,O_TOTALPRICE,O_ORDERDATE,O_ORDERPRIORITY,O_CLERK,O_SHIPPRIORITY,O_COMMENT)) * [lift<46>: RingFactorizedRelation<[46, int,string]>](ORDERKEY,O_ORDERSTATUS))
);
DECLARE MAP TMP_orders_V_customerorders(RingFactorizedRelation<[45, int]>)[][] :=
AggSum([],
 ((TMP_orders_V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY]<Local> * V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY]<Local>) * [lift<45>: RingFactorizedRelation<[45, int]>](CUSTKEY))
);
DECLARE MAP TMP_customer_V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY: int] :=
AggSum([CUSTKEY],
 (((DELTA customer)(CUSTKEY,C_NAME,C_ADDRESS,NATIONKEY,C_PHONE,C_ACCTBAL,C_MKTSEGMENT,C_COMMENT)) * [lift<48>: RingFactorizedRelation<[48, string]>](C_NAME))
);
DECLARE MAP TMP_customer_V_customerorders(RingFactorizedRelation<[45, int]>)[][] :=
AggSum([],
 ((TMP_customer_V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY]<Local> * V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY]<Local>) * [lift<45>: RingFactorizedRelation<[45, int]>](CUSTKEY))
);

-------------------- QUERIES --------------------
-- Q5
DECLARE QUERY V_Q2Q3 := V_Q2Q3(RingFactorizedRelation<[0, int,int,string]>)[][]<Local>;
DECLARE QUERY V_Q2 := V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local>;
DECLARE QUERY V_Q3 := V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local>;
-- Q6
DECLARE QUERY V_Q5part := V_Q5part(RingFactorizedRelation<[8, int]>)[][]<Local>;
DECLARE QUERY V_part := V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY]<Local>;
DECLARE QUERY V_Q5 := V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY]<Local>;
-- Q3
DECLARE QUERY V_Q1orders := V_Q1orders(RingFactorizedRelation<[17, int]>)[][]<Local>;
DECLARE QUERY V_Q1 := V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY]<Local>;
DECLARE QUERY V_orders := V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY]<Local>;
-- Q4
DECLARE QUERY V_Q1part := V_Q1part(RingFactorizedRelation<[24, int]>)[][]<Local>;
DECLARE QUERY V_Q1 := V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY]<Local>;
DECLARE QUERY V_part := V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY]<Local>;
-- Q7
DECLARE QUERY V_Q6supplier := V_Q6supplier(RingFactorizedRelation<[30, int]>)[][]<Local>;
DECLARE QUERY V_Q6 := V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY]<Local>;
DECLARE QUERY V_supplier := V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY]<Local>;
-- Q1
DECLARE QUERY V_lineitempartsupp := V_lineitempartsupp(RingFactorizedRelation<[40, int,int]>)[][]<Local>;
DECLARE QUERY V_partsupp := V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY,PARTKEY]<Local>;
DECLARE QUERY V_lineitem := V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY,PARTKEY]<Local>;
-- Q2
DECLARE QUERY V_customerorders := V_customerorders(RingFactorizedRelation<[45, int]>)[][]<Local>;
DECLARE QUERY V_orders := V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY]<Local>;
DECLARE QUERY V_customer := V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY]<Local>;

-------------------- TRIGGERS --------------------
-- Q5
ON BATCH UPDATE OF Q2 { 
 TMP_Q2_V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local> := AggSum([CUSTKEY, ORDERKEY, O_ORDERSTATUS], ((DELTA Q2)(O_ORDERSTATUS, C_NAME, ORDERKEY, CUSTKEY) * [lift<3>: RingFactorizedRelation<[3, string]>](C_NAME)));
V_Q2Q3(RingFactorizedRelation<[0, int,int,string]>)[][]<Local>  +=  AggSum([], (TMP_Q2_V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS] * V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local>) * [lift<0>: RingFactorizedRelation<[0, int,int,string]>](CUSTKEY,ORDERKEY,O_ORDERSTATUS));
V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local> += TMP_Q2_V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS];
}
ON BATCH UPDATE OF Q3 { 
 TMP_Q3_V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local> := AggSum([CUSTKEY, ORDERKEY, O_ORDERSTATUS], ((DELTA Q3)(PS_AVAILQTY, PARTKEY, SUPPKEY, L_LINENUMBER, ORDERKEY, O_ORDERSTATUS, CUSTKEY) * [lift<4>: RingFactorizedRelation<[4, int,int,int,int]>](L_LINENUMBER,PARTKEY,PS_AVAILQTY,SUPPKEY)));
V_Q2Q3(RingFactorizedRelation<[0, int,int,string]>)[][]<Local>  +=  AggSum([], (TMP_Q3_V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS] * V_Q2(RingFactorizedRelation<[3, string]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local>) * [lift<0>: RingFactorizedRelation<[0, int,int,string]>](CUSTKEY,ORDERKEY,O_ORDERSTATUS));
V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS]<Local> += TMP_Q3_V_Q3(RingFactorizedRelation<[4, int,int,int,int]>)[][CUSTKEY,ORDERKEY,O_ORDERSTATUS];
}
-- Q6
ON BATCH UPDATE OF part { 
 TMP_part_V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY]<Local> := AggSum([PARTKEY], ((DELTA part)(PARTKEY, P_NAME, P_MFGR, P_BRAND, P_TYPE, P_SIZE, P_CONTAINER, P_RETAILPRICE, P_COMMENT) * [lift<9>: RingFactorizedRelation<[9, string]>](P_NAME)));
V_Q5part(RingFactorizedRelation<[8, int]>)[][]<Local>  +=  AggSum([], (TMP_part_V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY] * V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY]<Local>) * [lift<8>: RingFactorizedRelation<[8, int]>](PARTKEY));
V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY]<Local> += TMP_part_V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY];
}
ON BATCH UPDATE OF Q5 { 
 TMP_Q5_V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY]<Local> := AggSum([PARTKEY], ((DELTA Q5)(PS_AVAILQTY, PARTKEY, SUPPKEY, L_LINENUMBER, ORDERKEY, O_ORDERSTATUS, CUSTKEY, C_NAME) * [lift<10>: RingFactorizedRelation<[10, int,int,string,int,int,string,int]>](L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,PS_AVAILQTY,CUSTKEY,C_NAME,SUPPKEY)));
V_Q5part(RingFactorizedRelation<[8, int]>)[][]<Local>  +=  AggSum([], (TMP_Q5_V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY] * V_part(RingFactorizedRelation<[9, string]>)[][PARTKEY]<Local>) * [lift<8>: RingFactorizedRelation<[8, int]>](PARTKEY));
V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY]<Local> += TMP_Q5_V_Q5(RingFactorizedRelation<[10, int,int,string,int,int,string,int]>)[][PARTKEY];
}
-- Q3
ON BATCH UPDATE OF Q1 { 
 TMP_Q1_V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY]<Local> := AggSum([ORDERKEY], ((DELTA Q1)(PS_AVAILQTY, PARTKEY, SUPPKEY, L_LINENUMBER, ORDERKEY) * [lift<18>: RingFactorizedRelation<[18, int,int,int,int]>](L_LINENUMBER,PARTKEY,PS_AVAILQTY,SUPPKEY)));
V_Q1orders(RingFactorizedRelation<[17, int]>)[][]<Local>  +=  AggSum([], (TMP_Q1_V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY] * V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY]<Local>) * [lift<17>: RingFactorizedRelation<[17, int]>](ORDERKEY));
V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY]<Local> += TMP_Q1_V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY];
}
ON BATCH UPDATE OF orders { 
 TMP_orders_V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY]<Local> := AggSum([ORDERKEY], ((DELTA orders)(ORDERKEY, CUSTKEY, O_ORDERSTATUS, O_TOTALPRICE, O_ORDERDATE, O_ORDERPRIORITY, O_CLERK, O_SHIPPRIORITY, O_COMMENT) * [lift<22>: RingFactorizedRelation<[22, string,int]>](O_ORDERSTATUS,CUSTKEY)));
V_Q1orders(RingFactorizedRelation<[17, int]>)[][]<Local>  +=  AggSum([], (TMP_orders_V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY] * V_Q1(RingFactorizedRelation<[18, int,int,int,int]>)[][ORDERKEY]<Local>) * [lift<17>: RingFactorizedRelation<[17, int]>](ORDERKEY));
V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY]<Local> += TMP_orders_V_orders(RingFactorizedRelation<[22, string,int]>)[][ORDERKEY];
}
-- Q4
ON BATCH UPDATE OF Q1 { 
 TMP_Q1_V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY]<Local> := AggSum([PARTKEY], ((DELTA Q1)(PS_AVAILQTY, PARTKEY, SUPPKEY, L_LINENUMBER, ORDERKEY) * [lift<25>: RingFactorizedRelation<[25, int,int,int,int]>](L_LINENUMBER,ORDERKEY,PS_AVAILQTY,SUPPKEY)));
V_Q1part(RingFactorizedRelation<[24, int]>)[][]<Local>  +=  AggSum([], (TMP_Q1_V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY] * V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY]<Local>) * [lift<24>: RingFactorizedRelation<[24, int]>](PARTKEY));
V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY]<Local> += TMP_Q1_V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY];
}
ON BATCH UPDATE OF part { 
 TMP_part_V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY]<Local> := AggSum([PARTKEY], ((DELTA part)(PARTKEY, P_NAME, P_MFGR, P_BRAND, P_TYPE, P_SIZE, P_CONTAINER, P_RETAILPRICE, P_COMMENT) * [lift<29>: RingFactorizedRelation<[29, string]>](P_NAME)));
V_Q1part(RingFactorizedRelation<[24, int]>)[][]<Local>  +=  AggSum([], (TMP_part_V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY] * V_Q1(RingFactorizedRelation<[25, int,int,int,int]>)[][PARTKEY]<Local>) * [lift<24>: RingFactorizedRelation<[24, int]>](PARTKEY));
V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY]<Local> += TMP_part_V_part(RingFactorizedRelation<[29, string]>)[][PARTKEY];
}
-- Q7
ON BATCH UPDATE OF Q6 { 
 TMP_Q6_V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY]<Local> := AggSum([SUPPKEY], ((DELTA Q6)(PS_AVAILQTY, PARTKEY, SUPPKEY, L_LINENUMBER, ORDERKEY, O_ORDERSTATUS, CUSTKEY, C_NAME, P_NAME) * [lift<31>: RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>](L_LINENUMBER,ORDERKEY,O_ORDERSTATUS,PARTKEY,P_NAME,PS_AVAILQTY,CUSTKEY,C_NAME)));
V_Q6supplier(RingFactorizedRelation<[30, int]>)[][]<Local>  +=  AggSum([], (TMP_Q6_V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY] * V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY]<Local>) * [lift<30>: RingFactorizedRelation<[30, int]>](SUPPKEY));
V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY]<Local> += TMP_Q6_V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY];
}
ON BATCH UPDATE OF supplier { 
 TMP_supplier_V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY]<Local> := AggSum([SUPPKEY], ((DELTA supplier)(SUPPKEY, S_NAME, S_ADDRESS, S_NATIONKEY, S_PHONE, S_ACCTBAL, S_COMMENT) * [lift<39>: RingFactorizedRelation<[39, string]>](S_NAME)));
V_Q6supplier(RingFactorizedRelation<[30, int]>)[][]<Local>  +=  AggSum([], (TMP_supplier_V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY] * V_Q6(RingFactorizedRelation<[31, int,int,string,int,string,int,int,string]>)[][SUPPKEY]<Local>) * [lift<30>: RingFactorizedRelation<[30, int]>](SUPPKEY));
V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY]<Local> += TMP_supplier_V_supplier(RingFactorizedRelation<[39, string]>)[][SUPPKEY];
}
-- Q1
ON BATCH UPDATE OF partsupp { 
 TMP_partsupp_V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY,PARTKEY]<Local> := AggSum([SUPPKEY, PARTKEY], ((DELTA partsupp)(PARTKEY, SUPPKEY, PS_AVAILQTY, PS_SUPPLYCOST, PS_COMMENT) * [lift<42>: RingFactorizedRelation<[42, int]>](PS_AVAILQTY)));
V_lineitempartsupp(RingFactorizedRelation<[40, int,int]>)[][]<Local>  +=  AggSum([], (TMP_partsupp_V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY,PARTKEY] * V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY,PARTKEY]<Local>) * [lift<40>: RingFactorizedRelation<[40, int,int]>](SUPPKEY,PARTKEY));
V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY,PARTKEY]<Local> += TMP_partsupp_V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY,PARTKEY];
}
ON BATCH UPDATE OF lineitem { 
 TMP_lineitem_V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY,PARTKEY]<Local> := AggSum([SUPPKEY, PARTKEY], ((DELTA lineitem)(ORDERKEY, PARTKEY, SUPPKEY, L_LINENUMBER, L_QUANTITY, L_EXTENDEDPRICE, L_DISCOUNT, L_TAX, L_RETURNFLAG, L_LINESTATUS, L_SHIPDATE, L_COMMITDATE, L_RECEIPTDATE, L_SHIPINSTRUCT, L_SHIPMODE, L_COMMENT) * [lift<43>: RingFactorizedRelation<[43, int,int]>](ORDERKEY,L_LINENUMBER)));
V_lineitempartsupp(RingFactorizedRelation<[40, int,int]>)[][]<Local>  +=  AggSum([], (TMP_lineitem_V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY,PARTKEY] * V_partsupp(RingFactorizedRelation<[42, int]>)[][SUPPKEY,PARTKEY]<Local>) * [lift<40>: RingFactorizedRelation<[40, int,int]>](SUPPKEY,PARTKEY));
V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY,PARTKEY]<Local> += TMP_lineitem_V_lineitem(RingFactorizedRelation<[43, int,int]>)[][SUPPKEY,PARTKEY];
}
-- Q2
ON BATCH UPDATE OF orders { 
 TMP_orders_V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY]<Local> := AggSum([CUSTKEY], ((DELTA orders)(ORDERKEY, CUSTKEY, O_ORDERSTATUS, O_TOTALPRICE, O_ORDERDATE, O_ORDERPRIORITY, O_CLERK, O_SHIPPRIORITY, O_COMMENT) * [lift<46>: RingFactorizedRelation<[46, int,string]>](ORDERKEY,O_ORDERSTATUS)));
V_customerorders(RingFactorizedRelation<[45, int]>)[][]<Local>  +=  AggSum([], (TMP_orders_V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY] * V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY]<Local>) * [lift<45>: RingFactorizedRelation<[45, int]>](CUSTKEY));
V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY]<Local> += TMP_orders_V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY];
}
ON BATCH UPDATE OF customer { 
 TMP_customer_V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY]<Local> := AggSum([CUSTKEY], ((DELTA customer)(CUSTKEY, C_NAME, C_ADDRESS, NATIONKEY, C_PHONE, C_ACCTBAL, C_MKTSEGMENT, C_COMMENT) * [lift<48>: RingFactorizedRelation<[48, string]>](C_NAME)));
V_customerorders(RingFactorizedRelation<[45, int]>)[][]<Local>  +=  AggSum([], (TMP_customer_V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY] * V_orders(RingFactorizedRelation<[46, int,string]>)[][CUSTKEY]<Local>) * [lift<45>: RingFactorizedRelation<[45, int]>](CUSTKEY));
V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY]<Local> += TMP_customer_V_customer(RingFactorizedRelation<[48, string]>)[][CUSTKEY];
}

ON SYSTEM READY {

}