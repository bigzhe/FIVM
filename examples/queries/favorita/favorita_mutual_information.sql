IMPORT DTREE FROM FILE 'favorita.txt';

CREATE TYPE RingCofactorGeneral
FROM FILE 'ring/ring_cofactor_general.hpp'
WITH PARAMETER SCHEMA (dynamic_min, dynamic_sum, dynamic_sum);

CREATE STREAM SALES(date int, store int, item int, unit_sales double, onpromotion int)
FROM FILE './datasets/favorita/Sales.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE STREAM OIL(date int, oilprize double)
FROM FILE './datasets/favorita/Oil.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE STREAM HOLIDAY(date int, holiday_type int, locale int, locale_id int, transferred int)
FROM FILE './datasets/favorita/Holidays.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE STREAM TRANSACTIONS(date int, store int, transactions int) 
FROM FILE './datasets/favorita/Transactions.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE STREAM STORES(store int, city int, state int, store_type int, cluster int) 
FROM FILE './datasets/favorita/Stores.csv' LINE DELIMITED CSV(delimiter := ',');

CREATE STREAM ITEMS(item int, family int, itemclass int, perishable int) 
FROM FILE './datasets/favorita/Stores.csv' LINE DELIMITED CSV(delimiter := ',');

SELECT SUM(
    [liftCont<0>: RingCofactorGeneral<0,0,1>](unit_sales) *
    [liftCat<1>: RingCofactorGeneral<1,0,1>](onpromotion) *
    [liftCat<2>: RingCofactorGeneral<2,0,3>](family, itemclass, perishable) *
    [liftCont<5>: RingCofactorGeneral<5,0,1>](transactions) *
    [liftCat<6>: RingCofactorGeneral<6,0,4>](city, state, store_type, cluster) *        
    [liftCont<10>: RingCofactorGeneral<10,0,1>](oilprize) *
    [liftCat<11>: RingCofactorGeneral<11,0,4>](holiday_type, locale, locale_id, transferred)    
)
FROM Sales NATURAL JOIN Oil NATURAL JOIN Holiday NATURAL JOIN Transactions NATURAL JOIN Stores NATURAL JOIN Items;
