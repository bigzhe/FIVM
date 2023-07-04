IMPORT DTREE FROM FILE 'tpch_8_0*10-Q6.txt';

CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

CREATE STREAM partsupp (
	partkey 	 INT, 
	suppkey 	 INT, 
	ps_availqty 	 INT, 
	ps_supplycost 	 DECIMAL, 
	ps_comment 	 VARCHAR(199)) 
FROM FILE './datasets/tpch_unordered1/partsupp.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM lineitem (
	orderkey 	 INT, 
	partkey 	 INT, 
	suppkey 	 INT, 
	l_linenumber 	 INT, 
	l_quantity 	 DECIMAL, 
	l_extendedprice 	 DECIMAL, 
	l_discount 	 DECIMAL, 
	l_tax 	 DECIMAL, 
	l_returnflag 	 CHAR(1), 
	l_linestatus 	 CHAR(1), 
	l_shipdate 	 CHAR(10), 
	l_commitdate 	 CHAR(10), 
	l_receiptdate 	 CHAR(10), 
	l_shipinstruct 	 CHAR(25), 
	l_shipmode 	 CHAR(10), 
	l_comment 	 VARCHAR(44)) 
FROM FILE './datasets/tpch_unordered1/lineitem.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM orders (
	orderkey 	 INT, 
	custkey 	 INT, 
	o_orderstatus 	 CHAR(1), 
	o_totalprice 	 DECIMAL, 
	o_orderdate 	 CHAR(10), 
	o_orderpriority 	 CHAR(15), 
	o_clerk 	 CHAR(15), 
	o_shippriority 	 INT, 
	o_comment 	 VARCHAR(79)) 
FROM FILE './datasets/tpch_unordered1/orders.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM customer (
	custkey 	 INT, 
	c_name 	 VARCHAR(25), 
	c_address 	 VARCHAR(40), 
	nationkey 	 INT, 
	c_phone 	 CHAR(15), 
	c_acctbal 	 DECIMAL, 
	c_mktsegment 	 CHAR(10), 
	c_comment 	 VARCHAR(117)) 
FROM FILE './datasets/tpch_unordered1/customer.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM part (
	partkey 	 INT, 
	p_name 	 VARCHAR(55), 
	p_mfgr 	 CHAR(25), 
	p_brand 	 CHAR(10), 
	p_type 	 VARCHAR(25), 
	p_size 	 INT, 
	p_container 	 CHAR(10), 
	p_retailprice 	 DECIMAL, 
	p_comment 	 VARCHAR(23)) 
FROM FILE './datasets/tpch_unordered1/part.csv' 
LINE DELIMITED CSV (delimiter := '|');


SELECT SUM(
	[lift<0>: RingFactorizedRelation<[0, INT]>](orderkey) *
	[lift<1>: RingFactorizedRelation<[1, INT]>](partkey) *
	[lift<4>: RingFactorizedRelation<[4, VARCHAR(55)]>](p_name) *
	[lift<2>: RingFactorizedRelation<[2, INT]>](suppkey) *
	[lift<3>: RingFactorizedRelation<[3, DECIMAL]>](l_quantity) *
	[lift<5>: RingFactorizedRelation<[5, INT]>](custkey) *
	[lift<6>: RingFactorizedRelation<[6, CHAR(1)]>](o_orderstatus) *
	[lift<7>: RingFactorizedRelation<[7, VARCHAR(25)]>](c_name) 
)
FROM partsupp NATURAL JOIN lineitem NATURAL JOIN orders NATURAL JOIN customer NATURAL JOIN part;


