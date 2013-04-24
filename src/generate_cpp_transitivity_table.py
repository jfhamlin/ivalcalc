
symbol_name_map = {
    '<': 'BEFORE',
    '>': 'AFTER',
    '=': 'EQUAL',
    'm': 'MEETS',
    'mi': 'MET_BY',
    'o': 'OVERLAPS',
    'oi': 'OVERLAPPED_BY',
    'd': 'DURING',
    'di': 'CONTAINS',
    's': 'STARTS',
    'si': 'STARTED_BY',
    'f': 'FINISHES',
    'fi': 'FINISHED_BY',
}

compound_replacement_map = {
    'dur': ['d', 's', 'f'],
    'con': ['di', 'si', 'fi']
}

def cell_to_constraint_set_ctor(cell_string):
    input_symbols = cell_string.split()
    symbols = set()

    for sym in input_symbols:
        if sym in compound_replacement_map:
            symbols = symbols.union(compound_replacement_map[sym])
        else:
            symbols.add(sym)

    arity = len(symbols)
    ctor_args = ""
    for symbol in symbols:
        name = "CONSTRAINT_TYPE_" + symbol_name_map[symbol]
        if ctor_args != "":
            ctor_args += ", "
        ctor_args += name
    return ("MK_CTS_%d(%s)" % (arity, ctor_args))

lines = open("transitivity_table_in").readlines()

print "#define MK_CTS_0() ConstraintTypeSet()"
print "#define MK_CTS_1(c0) ConstraintTypeSet(c0)"

for i in xrange(2, 13):
    args_rest = ",".join(["c%d" % (index,) for index in xrange(1, i)])
    print ("#define MK_CTS_%d(c0,%s) \\\n    constraint_union(ConstraintTypeSet(c0), MK_CTS_%d(%s))" %
           (i, args_rest, i - 1, args_rest))

lineno = 0
for line in lines:
    line = line.strip()
    cell_strings = line.split(",")

    line_length = 0

    print "{ ",
    for cs in cell_strings:
        print cell_to_constraint_set_ctor(cs) + ",",
        line_length += 1
    print " },"

    if line_length != 12:
        print "ERROR(%d): 12 entries required per line." % (lineno,)
        exit(1)

    lineno += 1
