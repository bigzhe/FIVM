
wc_l = {
    "Demographics": 25000,
    "House": 500000,
    "Institution": 100000,
    "Restaurant": 250000,
    "Shop": 500000,
    "Transport": 25000
}

WINDOW_SIZE = 100000
STEP_SIZE = 1000

WINDOW_SIZEs = range(0, sum(wc_l.values()), WINDOW_SIZE)

# print(WINDOW_SIZEs)

# exit()
accumulated_window_num = {
    "Demographics": [0],
    "House": [0],
    "Institution": [0],
    "Restaurant": [0],
    "Shop": [0],
    "Transport": [0]
}

def compute_windows(wc_l):
    total = sum(wc_l.values())
    for window in WINDOW_SIZEs:
        # accumulate tuples in window
        window_num = {
            "Demographics": 0,
            "House": 0,
            "Institution": 0,
            "Restaurant": 0,
            "Shop": 0,
            "Transport": 0
        }
        this_window_size = WINDOW_SIZE
        while sum(window_num.values()) < WINDOW_SIZE:
            # one round 
            for table, wc in wc_l.items():
                this_step_size = min(this_window_size, STEP_SIZE)
                if wc > this_step_size:
                    window_num[table] += this_step_size
                    wc_l[table] -= this_step_size
                    this_window_size -= this_step_size
                else:
                    window_num[table] += wc
                    wc_l[table] = 0
                    this_window_size -= wc
                if this_window_size <= 0:
                    break
            if this_window_size <= 0:
                break
        for table, wc in window_num.items():
            accumulated_window_num[table].append(window_num[table] + accumulated_window_num[table][-1])
            # print(f"{window} {table} {accumulated_window_num[table]}")
        
        # print(window_num)
        # print("# ===============================")
    for table, list in accumulated_window_num.items():
        print(table, list)

compute_windows(wc_l)



# 25000 Demographics.tbl
# 500000 House.tbl
# 100000 Institution.tbl
# 250000 Restaurant.tbl
# 500000 Shop.tbl
# 25000 Transport.tbl