---------------- TYPE DEFINITIONS ---------------
CREATE  TYPE RingRelation
FROM FILE 'ring/ring_relational_opt.hpp'
WITH PARAMETER SCHEMA (dynamic_concat);

-------------------- SOURCES --------------------
CREATE STREAM INVENTORY (locn int, dateid int, ksn int, inventoryunits int)
  FROM FILE './datasets/retailer/Inventory.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM LOCATION (locn int, zip int, rgn_cd int, clim_zn_nbr int, tot_area_sq_ft int, sell_area_sq_ft int, avghhi int, supertargetdistance double, supertargetdrivetime double, targetdistance double, targetdrivetime double, walmartdistance double, walmartdrivetime double, walmartsupercenterdistance double, walmartsupercenterdrivetime double)
  FROM FILE './datasets/retailer/Location.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM CENSUS (zip int, population int, white int, asian int, pacific int, blackafrican int, medianage double, occupiedhouseunits int, houseunits int, families int, households int, husbwife int, males int, females int, householdschildren int, hispanic int)
  FROM FILE './datasets/retailer/Census.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM ITEM (ksn int, subcategory byte, category byte, categoryCluster byte, prize double)
  FROM FILE './datasets/retailer/Item.tbl' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM WEATHER (locn int, dateid int, rain byte, snow byte, maxtemp int, mintemp int, meanwind double, thunder byte)
  FROM FILE './datasets/retailer/Weather.tbl' LINE DELIMITED CSV (delimiter := '|');

--------------------- MAPS ----------------------
DECLARE MAP V_locn_IIWLC1(RingRelation<[0, int, int, int, int, byte, byte, byte, double, byte, byte, int, int, double, byte, int, int, int, int, int, int, double, double, double, double, double, double, double, double, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>)[][] :=
  AggSum([],
    ((((((INVENTORY(locn, dateid, ksn, inventoryunits) * AggSum([ksn],
      (ITEM(ksn, subcategory, category, categoryCluster, prize) * [lift<4>: RingRelation<[4, byte, byte, byte, double]>](subcategory, category, categoryCluster, prize))
    )) * [lift<2>: RingRelation<[2, int, int]>](ksn, inventoryunits)) * AggSum([locn, dateid],
      (WEATHER(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder) * [lift<8>: RingRelation<[8, byte, byte, int, int, double, byte]>](rain, snow, maxtemp, mintemp, meanwind, thunder))
    )) * [lift<1>: RingRelation<[1, int]>](dateid)) * AggSum([locn],
      (((LOCATION(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime) * [lift<15>: RingRelation<[15, int, int, int, int, int, double, double, double, double, double, double, double, double]>](rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime)) * AggSum([zip],
        (CENSUS(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic) * [lift<28>: RingRelation<[28, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>](population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic))
      )) * [lift<14>: RingRelation<[14, int]>](zip))
    )) * [lift<0>: RingRelation<[0, int]>](locn))
  );

DECLARE MAP V_INVENTORY(long)[][locn: int, dateid: int, ksn: int, inventoryunits: int] := INVENTORY(locn, dateid, ksn, inventoryunits);

DECLARE MAP V_LOCATION(long)[][locn: int, zip: int, rgn_cd: int, clim_zn_nbr: int, tot_area_sq_ft: int, sell_area_sq_ft: int, avghhi: int, supertargetdistance: double, supertargetdrivetime: double, targetdistance: double, targetdrivetime: double, walmartdistance: double, walmartdrivetime: double, walmartsupercenterdistance: double, walmartsupercenterdrivetime: double] := LOCATION(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime);

DECLARE MAP V_CENSUS(long)[][zip: int, population: int, white: int, asian: int, pacific: int, blackafrican: int, medianage: double, occupiedhouseunits: int, houseunits: int, families: int, households: int, husbwife: int, males: int, females: int, householdschildren: int, hispanic: int] := CENSUS(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic);

DECLARE MAP V_ITEM(long)[][ksn: int, subcategory: byte, category: byte, categoryCluster: byte, prize: double] := ITEM(ksn, subcategory, category, categoryCluster, prize);

DECLARE MAP V_WEATHER(long)[][locn: int, dateid: int, rain: byte, snow: byte, maxtemp: int, mintemp: int, meanwind: double, thunder: byte] := WEATHER(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder);

-------------------- QUERIES --------------------
DECLARE QUERY V_locn_IIWLC1 := V_locn_IIWLC1(RingRelation<[0, int, int, int, int, byte, byte, byte, double, byte, byte, int, int, double, byte, int, int, int, int, int, int, double, double, double, double, double, double, double, double, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>)[][]<Local>;

------------------- TRIGGERS --------------------
ON BATCH UPDATE OF INVENTORY {
  V_INVENTORY(long)[][locn, dateid, ksn, inventoryunits] += (DELTA INVENTORY)(locn, dateid, ksn, inventoryunits);
}

ON BATCH UPDATE OF LOCATION {
  V_LOCATION(long)[][locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime] += (DELTA LOCATION)(locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime);
}

ON BATCH UPDATE OF CENSUS {
  V_CENSUS(long)[][zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic] += (DELTA CENSUS)(zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic);
}

ON BATCH UPDATE OF ITEM {
  V_ITEM(long)[][ksn, subcategory, category, categoryCluster, prize] += (DELTA ITEM)(ksn, subcategory, category, categoryCluster, prize);
}

ON BATCH UPDATE OF WEATHER {
  V_WEATHER(long)[][locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder] += (DELTA WEATHER)(locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder);
}

ON SYSTEM READY {
  V_locn_IIWLC1(RingRelation<[0, int, int, int, int, byte, byte, byte, double, byte, byte, int, int, double, byte, int, int, int, int, int, int, double, double, double, double, double, double, double, double, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>)[][]<Local>  :=  AggSum([],
    ((((((V_INVENTORY(long)[][locn, dateid, ksn, inventoryunits] * AggSum([ksn],
      (V_ITEM(long)[][ksn, subcategory, category, categoryCluster, prize] * [lift<4>: RingRelation<[4, byte, byte, byte, double]>](subcategory, category, categoryCluster, prize))
    )) * [lift<2>: RingRelation<[2, int, int]>](ksn, inventoryunits)) * AggSum([locn, dateid],
      (V_WEATHER(long)[][locn, dateid, rain, snow, maxtemp, mintemp, meanwind, thunder] * [lift<8>: RingRelation<[8, byte, byte, int, int, double, byte]>](rain, snow, maxtemp, mintemp, meanwind, thunder))
    )) * [lift<1>: RingRelation<[1, int]>](dateid)) * AggSum([locn],
      (((V_LOCATION(long)[][locn, zip, rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime] * [lift<15>: RingRelation<[15, int, int, int, int, int, double, double, double, double, double, double, double, double]>](rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime)) * AggSum([zip],
        (V_CENSUS(long)[][zip, population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic] * [lift<28>: RingRelation<[28, int, int, int, int, int, double, int, int, int, int, int, int, int, int, int]>](population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic))
      )) * [lift<14>: RingRelation<[14, int]>](zip))
    )) * [lift<0>: RingRelation<[0, int]>](locn))
  );
}


