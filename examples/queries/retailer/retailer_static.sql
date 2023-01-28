IMPORT DTREE FROM FILE 'retailer.txt';

CREATE STREAM INVENTORY(locn int, dateid int, ksn int, inventoryunits int)
FROM FILE './datasets/retailer/Inventory.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE STREAM LOCATION(locn int, zip int, rgn_cd int, clim_zn_nbr int, tot_area_sq_ft int, sell_area_sq_ft int, avghhi int, supertargetdistance double, supertargetdrivetime double, targetdistance double, targetdrivetime double, walmartdistance double, walmartdrivetime double, walmartsupercenterdistance double, walmartsupercenterdrivetime double)
FROM FILE './datasets/retailer/Location.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE STREAM CENSUS(zip int, population int, white int, asian int, pacific int, blackafrican int, medianage double, occupiedhouseunits int, houseunits int, families int, households int, husbwife int, males int, females int, householdschildren int, hispanic int)
FROM FILE './datasets/retailer/Census.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE STREAM ITEM(ksn int, subcategory byte, category byte, categoryCluster byte, prize double) 
FROM FILE './datasets/retailer/Item.tbl' LINE DELIMITED CSV(delimiter := '|');

CREATE STREAM WEATHER(locn int, dateid int, rain byte, snow byte, maxtemp int, mintemp int, meanwind double, thunder byte) 
FROM FILE './datasets/retailer/Weather.tbl' LINE DELIMITED CSV(delimiter := '|');

SELECT locn,dateid,ksn,inventoryunits, zip,rgn_cd,clim_zn_nbr,tot_area_sq_ft,sell_area_sq_ft,avghhi,supertargetdistance,supertargetdrivetime,targetdistance,targetdrivetime,walmartdistance,walmartdrivetime,walmartsupercenterdistance,walmartsupercenterdrivetime, population,white,asian,pacific,blackafrican,medianage,occupiedhouseunits,houseunits,families,households,husbwife,males,females,householdschildren,hispanic, subcategory,category,categoryCluster,prize, rain,snow,maxtemp,mintemp,meanwind,thunder, SUM(1)
FROM INVENTORY NATURAL JOIN LOCATION NATURAL JOIN CENSUS NATURAL JOIN ITEM NATURAL JOIN WEATHER
GROUP BY locn,dateid,ksn,inventoryunits, zip,rgn_cd,clim_zn_nbr,tot_area_sq_ft,sell_area_sq_ft,avghhi,supertargetdistance,supertargetdrivetime,targetdistance,targetdrivetime,walmartdistance,walmartdrivetime,walmartsupercenterdistance,walmartsupercenterdrivetime, population,white,asian,pacific,blackafrican,medianage,occupiedhouseunits,houseunits,families,households,husbwife,males,females,householdschildren,hispanic, subcategory,category,categoryCluster,prize, rain,snow,maxtemp,mintemp,meanwind,thunder;

-- locn,dateid,ksn,inventoryunits, zip,rgn_cd,clim_zn_nbr,tot_area_sq_ft,sell_area_sq_ft,avghhi,supertargetdistance,supertargetdrivetime,targetdistance,targetdrivetime,walmartdistance,walmartdrivetime,walmartsupercenterdistance,walmartsupercenterdrivetime, population,white,asian,pacific,blackafrican,medianage,occupiedhouseunits,houseunits,families,households,husbwife,males,females,householdschildren,hispanic, subcategory,category,categoryCluster,prize, rain,snow,maxtemp,mintemp,meanwind,thunder