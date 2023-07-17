-------------------- SOURCES --------------------
CREATE STREAM R1 (A1 int, A2 int)
  FROM FILE './datasets/ego-twitter/R1.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R2 (A2 int, A3 int)
  FROM FILE './datasets/ego-twitter/R2.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R3 (A3 int, A4 int)
  FROM FILE './datasets/ego-twitter/R3.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R4 (A4 int, A5 int)
  FROM FILE './datasets/ego-twitter/R4.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R5 (A5 int, A6 int)
  FROM FILE './datasets/ego-twitter/R5.csv' LINE DELIMITED CSV (delimiter := '|');

--------------------- MAPS ----------------------

DECLARE MAP V_Q(long)[][] :=
  AggSum([],
    R1(A1, A2) * R2(A2, A3) * R3(A3, A4) * R4(A4, A5) * R5(A5, A6) * A1 * A6
  );

DECLARE MAP V_R1(long)[][A1: int, A2: int] := R1(A1, A2);
DECLARE MAP V_R2(long)[][A2: int, A3: int] := R2(A2, A3);
DECLARE MAP V_R3(long)[][A3: int, A4: int] := R3(A3, A4);
DECLARE MAP V_R4(long)[][A4: int, A5: int] := R4(A4, A5);
DECLARE MAP V_R5(long)[][A5: int, A6: int] := R5(A5, A6);

DECLARE MAP TMP_R1(long)[][A1: int, A2: int] := (DELTA R1)(A1, A2);
DECLARE MAP TMP_R2(long)[][A2: int, A3: int] := (DELTA R2)(A2, A3);
DECLARE MAP TMP_R3(long)[][A3: int, A4: int] := (DELTA R3)(A3, A4);
DECLARE MAP TMP_R4(long)[][A4: int, A5: int] := (DELTA R4)(A4, A5);
DECLARE MAP TMP_R5(long)[][A5: int, A6: int] := (DELTA R5)(A5, A6);

-------------------- QUERIES --------------------
DECLARE QUERY V_Q := V_Q(long)[][]<Local>;

------------------- TRIGGERS --------------------
ON BATCH UPDATE OF R1 {
  TMP_R1(long)[][A1, A2]<Local> := (DELTA R1)(A1, A2);
  V_R1(long)[][A1, A2]<Local> += TMP_R1(long)[][A1, A2]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    TMP_R1(long)[][A1, A2]<Local> * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * A1 * A6
  );
}

ON BATCH UPDATE OF R2 {
  TMP_R2(long)[][A2, A3]<Local> := (DELTA R2)(A2, A3);
  V_R2(long)[][A2, A3]<Local> += TMP_R2(long)[][A2, A3]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * TMP_R2(long)[][A2, A3] * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * A1 * A6
  );
}

ON BATCH UPDATE OF R3 {
  TMP_R3(long)[][A3, A4]<Local> := (DELTA R3)(A3, A4);
  V_R3(long)[][A3, A4]<Local> += TMP_R3(long)[][A3, A4]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * TMP_R3(long)[][A3, A4] * V_R4(A4, A5) * V_R5(A5, A6) * A1 * A6
  );
}
  
ON BATCH UPDATE OF R4 {
  TMP_R4(long)[][A4, A5]<Local> := (DELTA R4)(A4, A5);
  V_R4(long)[][A4, A5]<Local> += TMP_R4(long)[][A4, A5]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * TMP_R4(long)[][A4, A5] * V_R5(A5, A6) * A1 * A6
  );
}
  
ON BATCH UPDATE OF R5 {
  TMP_R5(long)[][A5, A6]<Local> := (DELTA R5)(A5, A6);
  V_R5(long)[][A5, A6]<Local> += TMP_R5(long)[][A5, A6]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * TMP_R5(long)[][A5, A6] * A1 * A6
  );
}

ON SYSTEM READY {
  
}