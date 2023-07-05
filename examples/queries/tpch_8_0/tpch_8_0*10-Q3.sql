IMPORT DTREE FROM FILE 'tpch_8_0*10-Q3.txt';

CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

CREATE STREAM partsupp (
	partkey 	 INT, 
	suppkey 	 INT, 
	ps_availqty 	 INT, 
	ps_supplycost 	 DECIMAL, 
	ps_comment 	 VARCHAR(199)) 
FROM FILE './datasets/tpch_unordered10/partsupp.csv' 
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
FROM FILE './datasets/tpch_unordered10/lineitem.csv' 
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
FROM FILE './datasets/tpch_unordered10/orders.csv' 
LINE DELIMITED CSV (delimiter := '|');


SELECT SUM(
	[lift<0>: RingFactorizedRelation<[0, INT]>](orderkey) *
	[lift<4>: RingFactorizedRelation<[4, INT,CHAR(1)]>](custkey,o_orderstatus) *
	[lift<1>: RingFactorizedRelation<[1, INT]>](partkey) *
	[lift<2>: RingFactorizedRelation<[2, INT]>](suppkey) *
	[lift<3>: RingFactorizedRelation<[3, DECIMAL]>](l_quantity) 
)
FROM partsupp NATURAL JOIN lineitem NATURAL JOIN orders;


