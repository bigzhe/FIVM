IMPORT DTREE FROM FILE 'tpch_7_0*10-Q3.txt';

CREATE DISTRIBUTED TYPE RingFactorizedRelation
FROM FILE 'ring/ring_factorized.hpp'
WITH PARAMETER SCHEMA (dynamic_min);

CREATE STREAM nation (
	nationkey 	 INT, 
	n_name 	 CHAR(25), 
	regionkey 	 INT, 
	n_comment 	 VARCHAR(152)) 
FROM FILE './datasets/tpch_unordered1/nation.csv' 
LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM region (
	regionkey 	 INT, 
	r_name 	 CHAR(25), 
	r_comment 	 VARCHAR(152)) 
FROM FILE './datasets/tpch_unordered1/region.csv' 
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


SELECT SUM(
	[lift<0>: RingFactorizedRelation<[0, INT]>](custkey) *
	[lift<8>: RingFactorizedRelation<[8, INT,CHAR(1)]>](orderkey,o_orderstatus) *
	[lift<1>: RingFactorizedRelation<[1, INT]>](nationkey) *
	[lift<7>: RingFactorizedRelation<[7, VARCHAR(25)]>](c_name) *
	[lift<2>: RingFactorizedRelation<[2, INT]>](regionkey) *
	[lift<3>: RingFactorizedRelation<[3, VARCHAR(152),CHAR(25)]>](n_comment,n_name) *
	[lift<5>: RingFactorizedRelation<[5, CHAR(25),VARCHAR(152)]>](r_name,r_comment) 
)
FROM nation NATURAL JOIN region NATURAL JOIN customer NATURAL JOIN orders;


