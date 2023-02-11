---------------- TYPE DEFINITIONS ---------------
CREATE  TYPE RingRelation
FROM FILE 'ring/ring_relational_opt.hpp'
WITH PARAMETER SCHEMA (dynamic_concat);

-------------------- SOURCES --------------------
CREATE STREAM SALES (date int, store int, item int, unit_sales double, onpromotion int)
  FROM FILE './datasets/favorita/Sales.csv' LINE DELIMITED CSV (delimiter := ',');

CREATE STREAM OIL (date int, oilprize double)
  FROM FILE './datasets/favorita/Oil.csv' LINE DELIMITED CSV (delimiter := ',');

CREATE STREAM HOLIDAY (date int, holiday_type int, locale int, locale_id int, transferred int)
  FROM FILE './datasets/favorita/Holidays.csv' LINE DELIMITED CSV (delimiter := ',');

CREATE STREAM TRANSACTIONS (date int, store int, transactions int)
  FROM FILE './datasets/favorita/Transactions.csv' LINE DELIMITED CSV (delimiter := ',');

CREATE STREAM STORES (store int, city int, state int, store_type int, cluster int)
  FROM FILE './datasets/favorita/Stores.csv' LINE DELIMITED CSV (delimiter := ',');

CREATE STREAM ITEMS (item int, family int, itemclass int, perishable int)
  FROM FILE './datasets/favorita/Stores.csv' LINE DELIMITED CSV (delimiter := ',');

--------------------- MAPS ----------------------
DECLARE MAP V_date_SITSOH1(RingRelation<[0, int, int, int, double, int, int, int, int, int, int, int, int, int, double, int, int, int, int]>)[][] :=
  AggSum([],
    ((((((((SALES(date, store, item, unit_sales, onpromotion) * AggSum([item],
      (ITEMS(item, family, itemclass, perishable) * [lift<5>: RingRelation<[5, int, int, int]>](family, itemclass, perishable))
    )) * [lift<2>: RingRelation<[2, int, double, int]>](item, unit_sales, onpromotion)) * AggSum([date, store],
      (TRANSACTIONS(date, store, transactions) * [lift<8>: RingRelation<[8, int]>](transactions))
    )) * AggSum([store],
      (STORES(store, city, state, store_type, cluster) * [lift<9>: RingRelation<[9, int, int, int, int]>](city, state, store_type, cluster))
    )) * [lift<1>: RingRelation<[1, int]>](store)) * AggSum([date],
      (OIL(date, oilprize) * [lift<13>: RingRelation<[13, double]>](oilprize))
    )) * AggSum([date],
      (HOLIDAY(date, holiday_type, locale, locale_id, transferred) * [lift<14>: RingRelation<[14, int, int, int, int]>](holiday_type, locale, locale_id, transferred))
    )) * [lift<0>: RingRelation<[0, int]>](date))
  );

DECLARE MAP V_SALES(long)[][date: int, store: int, item: int, unit_sales: double, onpromotion: int] :=
  SALES(date, store, item, unit_sales, onpromotion);

DECLARE MAP V_ITEMS(long)[][item: int, family: int, itemclass: int, perishable: int] := (ITEMS(item, family, itemclass, perishable));

DECLARE MAP V_TRANSACTIONS(long)[][date: int, store: int, transactions: int] := (TRANSACTIONS(date, store, transactions));

DECLARE MAP V_STORES(long)[][store: int, city: int, state: int, store_type: int, cluster: int] := (STORES(store, city, state, store_type, cluster));

DECLARE MAP V_OIL(long)[][date: int, oilprize: double] := (OIL(date, oilprize));

DECLARE MAP V_HOLIDAY(long)[][date: int, holiday_type: int, locale: int, locale_id: int, transferred: int] := (HOLIDAY(date, holiday_type, locale, locale_id, transferred));


-------------------- QUERIES --------------------
DECLARE QUERY V_date_SITSOH1 := V_date_SITSOH1(RingRelation<[0, int, int, int, double, int, int, int, int, int, int, int, int, int, double, int, int, int, int]>)[][]<Local>;

------------------- TRIGGERS --------------------
ON BATCH UPDATE OF SALES {

  V_SALES(long)[][date, store, item, unit_sales, onpromotion] += (DELTA SALES)(date, store, item, unit_sales, onpromotion);

}


ON BATCH UPDATE OF OIL {

  V_OIL(long)[][date, oilprize] += (DELTA OIL)(date, oilprize);
  
}

ON BATCH UPDATE OF HOLIDAY {
  V_HOLIDAY(long)[][date, holiday_type, locale, locale_id, transferred] += (DELTA HOLIDAY)(date, holiday_type, locale, locale_id, transferred);
  
}

ON BATCH UPDATE OF TRANSACTIONS {
  V_TRANSACTIONS(long)[][date, store, transactions] += (DELTA TRANSACTIONS)(date, store, transactions);
  
}

ON BATCH UPDATE OF STORES {
  V_STORES(long)[][store, city, state, store_type, cluster] += (DELTA STORES)(store, city, state, store_type, cluster);
  
}

ON BATCH UPDATE OF ITEMS {
  V_ITEMS(long)[][item, family, itemclass, perishable] += (DELTA ITEMS)(item, family, itemclass, perishable);
  
}

ON SYSTEM READY {
  V_date_SITSOH1(RingRelation<[0, int, int, int, double, int, int, int, int, int, int, int, int, int, double, int, int, int, int]>)[][]<Local>  :=  AggSum([],
    ((((((((V_SALES(long)[][date, store, item, unit_sales, onpromotion] * AggSum([item],
      (V_ITEMS(long)[][item, family, itemclass, perishable] * [lift<5>: RingRelation<[5, int, int, int]>](family, itemclass, perishable))
    )) * [lift<2>: RingRelation<[2, int, double, int]>](item, unit_sales, onpromotion)) * AggSum([date, store],
      (V_TRANSACTIONS(long)[][date, store, transactions] * [lift<8>: RingRelation<[8, int]>](transactions))
    )) * AggSum([store],
      (V_STORES(long)[][store, city, state, store_type, cluster] * [lift<9>: RingRelation<[9, int, int, int, int]>](city, state, store_type, cluster))
    )) * [lift<1>: RingRelation<[1, int]>](store)) * AggSum([date],
      (V_OIL(long)[][date, oilprize] * [lift<13>: RingRelation<[13, double]>](oilprize))
    )) * AggSum([date],
      (V_HOLIDAY(long)[][date, holiday_type, locale, locale_id, transferred] * [lift<14>: RingRelation<[14, int, int, int, int]>](holiday_type, locale, locale_id, transferred))
    )) * [lift<0>: RingRelation<[0, int]>](date))
  );
}