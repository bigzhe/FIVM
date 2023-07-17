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

CREATE STREAM R6 (A6 int, A7 int)
  FROM FILE './datasets/ego-twitter/R6.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R7 (A7 int, A8 int)
  FROM FILE './datasets/ego-twitter/R7.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R8 (A8 int, A9 int)
  FROM FILE './datasets/ego-twitter/R8.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R9 (A9 int, A10 int)
  FROM FILE './datasets/ego-twitter/R9.csv' LINE DELIMITED CSV (delimiter := '|');

CREATE STREAM R10 (A10 int, A11 int)
  FROM FILE './datasets/ego-twitter/R10.csv' LINE DELIMITED CSV (delimiter := '|');

--------------------- MAPS ----------------------

DECLARE MAP V_Q(long)[][] :=
  AggSum([],
    R1(A1, A2) * R2(A2, A3) * R3(A3, A4) * R4(A4, A5) * R5(A5, A6) * R6(A6, A7) * R7(A7, A8) * R8(A8, A9) * R9(A9, A10) * R10(A10, A11) * A1 * A11
  );

DECLARE MAP V_R1(long)[][A1: int, A2: int] := R1(A1, A2);
DECLARE MAP V_R2(long)[][A2: int, A3: int] := R2(A2, A3);
DECLARE MAP V_R3(long)[][A3: int, A4: int] := R3(A3, A4);
DECLARE MAP V_R4(long)[][A4: int, A5: int] := R4(A4, A5);
DECLARE MAP V_R5(long)[][A5: int, A6: int] := R5(A5, A6);
DECLARE MAP V_R6(long)[][A6: int, A7: int] := R6(A6, A7);
DECLARE MAP V_R7(long)[][A7: int, A8: int] := R7(A7, A8);
DECLARE MAP V_R8(long)[][A8: int, A9: int] := R8(A8, A9);
DECLARE MAP V_R9(long)[][A9: int, A10: int] := R9(A9, A10);
DECLARE MAP V_R10(long)[][A10: int, A11: int] := R10(A10, A11);

DECLARE MAP TMP_R1(long)[][A1: int, A2: int] := (DELTA R1)(A1, A2);
DECLARE MAP TMP_R2(long)[][A2: int, A3: int] := (DELTA R2)(A2, A3);
DECLARE MAP TMP_R3(long)[][A3: int, A4: int] := (DELTA R3)(A3, A4);
DECLARE MAP TMP_R4(long)[][A4: int, A5: int] := (DELTA R4)(A4, A5);
DECLARE MAP TMP_R5(long)[][A5: int, A6: int] := (DELTA R5)(A5, A6);
DECLARE MAP TMP_R6(long)[][A6: int, A7: int] := (DELTA R6)(A6, A7);
DECLARE MAP TMP_R7(long)[][A7: int, A8: int] := (DELTA R7)(A7, A8);
DECLARE MAP TMP_R8(long)[][A8: int, A9: int] := (DELTA R8)(A8, A9);
DECLARE MAP TMP_R9(long)[][A9: int, A10: int] := (DELTA R9)(A9, A10);
DECLARE MAP TMP_R10(long)[][A10: int, A11: int] := (DELTA R10)(A10, A11);


-------------------- QUERIES --------------------
DECLARE QUERY V_Q := V_Q(long)[][]<Local>;

------------------- TRIGGERS --------------------
ON BATCH UPDATE OF R1 {
  TMP_R1(long)[][A1, A2]<Local> := (DELTA R1)(A1, A2);
  V_R1(long)[][A1, A2]<Local> += TMP_R1(long)[][A1, A2]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    TMP_R1(long)[][A1, A2]<Local> * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * A1 * A11
  );
}

ON BATCH UPDATE OF R2 {
  TMP_R2(long)[][A2, A3]<Local> := (DELTA R2)(A2, A3);
  V_R2(long)[][A2, A3]<Local> += TMP_R2(long)[][A2, A3]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * TMP_R2(long)[][A2, A3] * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * A1 * A11
  );
}

ON BATCH UPDATE OF R3 {
  TMP_R3(long)[][A3, A4]<Local> := (DELTA R3)(A3, A4);
  V_R3(long)[][A3, A4]<Local> += TMP_R3(long)[][A3, A4]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * TMP_R3(long)[][A3, A4] * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * A1 * A11
  );
}

ON BATCH UPDATE OF R4 {
  TMP_R4(long)[][A4, A5]<Local> := (DELTA R4)(A4, A5);
  V_R4(long)[][A4, A5]<Local> += TMP_R4(long)[][A4, A5]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * TMP_R4(long)[][A4, A5] * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * A1 * A11
  );
}

ON BATCH UPDATE OF R5 {
  TMP_R5(long)[][A5, A6]<Local> := (DELTA R5)(A5, A6);
  V_R5(long)[][A5, A6]<Local> += TMP_R5(long)[][A5, A6]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * TMP_R5(long)[][A5, A6] * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * A1 * A11
  );
}

ON BATCH UPDATE OF R6 {
  TMP_R6(long)[][A6, A7]<Local> := (DELTA R6)(A6, A7);
  V_R6(long)[][A6, A7]<Local> += TMP_R6(long)[][A6, A7]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * TMP_R6(long)[][A6, A7] * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * A1 * A11
  );
}

ON BATCH UPDATE OF R7 {
  TMP_R7(long)[][A7, A8]<Local> := (DELTA R7)(A7, A8);
  V_R7(long)[][A7, A8]<Local> += TMP_R7(long)[][A7, A8]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * TMP_R7(long)[][A7, A8] * V_R8(A8, A9) * V_R9(A9, A10) * V_R10(A10, A11) * A1 * A11
  );
}

ON BATCH UPDATE OF R8 {
  TMP_R8(long)[][A8, A9]<Local> := (DELTA R8)(A8, A9);
  V_R8(long)[][A8, A9]<Local> += TMP_R8(long)[][A8, A9]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * TMP_R8(long)[][A8, A9] * V_R9(A9, A10) * V_R10(A10, A11) * A1 * A11
  );
}

ON BATCH UPDATE OF R9 {
  TMP_R9(long)[][A9, A10]<Local> := (DELTA R9)(A9, A10);
  V_R9(long)[][A9, A10]<Local> += TMP_R9(long)[][A9, A10]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * TMP_R9(long)[][A9, A10] * V_R10(A10, A11) * A1 * A11
  );
}

ON BATCH UPDATE OF R10 {
  TMP_R10(long)[][A10, A11]<Local> := (DELTA R10)(A10, A11);
  V_R10(long)[][A10, A11]<Local> += TMP_R10(long)[][A10, A11]<Local>;
  V_Q(long)[][]<Local> += AggSum([],
    V_R1(A1, A2) * V_R2(A2, A3) * V_R3(A3, A4) * V_R4(A4, A5) * V_R5(A5, A6) * V_R6(A6, A7) * V_R7(A7, A8) * V_R8(A8, A9) * V_R9(A9, A10) * TMP_R10(long)[][A10, A11] * A1 * A11
  );
}

ON SYSTEM READY {
  
}