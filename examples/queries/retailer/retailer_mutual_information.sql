IMPORT DTREE FROM FILE 'retailer_mi.txt';

CREATE TYPE RingCofactorGeneral
FROM FILE 'ring/ring_cofactor_general.hpp'
WITH PARAMETER SCHEMA (dynamic_min, dynamic_sum, dynamic_sum);

CREATE STREAM INVENTORY(locn int, dateid int, ksn int, inventoryunits int)
FROM FILE './datasets/retailer-mi/Inventory.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE STREAM LOCATION(locn int, zip int, rgn_cd int, clim_zn_nbr int, tot_area_sq_ft int, sell_area_sq_ft int, avghhi int, supertargetdistance int, supertargetdrivetime int, targetdistance int, targetdrivetime int, walmartdistance int, walmartdrivetime int, walmartsupercenterdistance int, walmartsupercenterdrivetime int)
FROM FILE './datasets/retailer-mi/Location.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE STREAM CENSUS(zip int, population int, white int, asian int, pacific int, blackafrican int, medianage int, occupiedhouseunits int, houseunits int, families int, households int, husbwife int, males int, females int, householdschildren int, hispanic int)
FROM FILE './datasets/retailer-mi/Census.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE STREAM ITEM(ksn int, subcategory int, category int, categoryCluster int, prize int) 
FROM FILE './datasets/retailer-mi/Item.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE STREAM WEATHER(locn int, dateid int, rain int, snow int, maxtemp int, mintemp int, meanwind int, thunder int) 
FROM FILE './datasets/retailer-mi/Weather.tbl' LINE DELIMITED CSV(delimiter := '|');

SELECT SUM(
    [liftCat<0>: RingCofactorGeneral<0,0,1>](inventoryunits) *
    [liftCat<1>: RingCofactorGeneral<1,0,1>](prize) *
    [liftCat<2>: RingCofactorGeneral<2,0,3>](subcategory, category, categoryCluster) *
    [liftCat<5>: RingCofactorGeneral<5,0,3>](maxtemp, mintemp, meanwind) *
    [liftCat<8>: RingCofactorGeneral<8,0,3>](rain, snow, thunder) *
    [liftCat<11>: RingCofactorGeneral<11,0,13>](rgn_cd, clim_zn_nbr, tot_area_sq_ft, sell_area_sq_ft, avghhi, supertargetdistance, supertargetdrivetime, targetdistance, targetdrivetime, walmartdistance, walmartdrivetime, walmartsupercenterdistance, walmartsupercenterdrivetime) *
    [liftCat<24>: RingCofactorGeneral<24,0,15>](population, white, asian, pacific, blackafrican, medianage, occupiedhouseunits, houseunits, families, households, husbwife, males, females, householdschildren, hispanic)
)
FROM INVENTORY NATURAL JOIN LOCATION NATURAL JOIN CENSUS NATURAL JOIN ITEM NATURAL JOIN WEATHER;


