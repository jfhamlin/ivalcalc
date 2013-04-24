#include "constraint_types.h"

namespace allen {

namespace {

ConstraintTypeSet constraint_transitivity[12][12] = {
#include "g_constraint_transitivity_table.h"
};

} // anonymous namespace

ConstraintTypeSet lookup_constraint_transitivity(const ConstraintTypeSet& c0,
                                                 const ConstraintTypeSet& c1) {
    ConstraintTypeSet result;
    for (uint32_t i = 1; i < CONSTRAINT_TYPE_COUNT; ++i) {
        if ((c0.m_constraint_bits & CONSTRAINT_TYPE_BIT(i)) == 0)
            continue;

        for (uint32_t j = 1; j < CONSTRAINT_TYPE_COUNT; ++j) {
            if ((c1.m_constraint_bits & CONSTRAINT_TYPE_BIT(j)) == 0)
                continue;

            result = constraint_union(result, constraint_transitivity[i-1][j-1]);
        }
    }

    return result;
}

} // namespace allen
