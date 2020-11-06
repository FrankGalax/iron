#pragma once

#define ironBEGIN_NAMESPACE namespace iron {
#define ironEND_NAMESPACE }

#define GRID_SIZE 16

#define ironTolerance 0.000001f

#define ironNullWithEpsilon(f) (abs(f) <= ironTolerance)
#define ironEqualWithEpsilon(a, b) (fabs((a) - (b)) <= ironTolerance)

#define ironGreaterWithEpsilon(a, b)             ((a) - (b) > ironTolerance)
#define ironGreaterOrEqualWithEpsilon(a, b)      ((a) + ironTolerance > (b))
#define ironLesserWithEpsilon(a, b)              ((b) - (a) > ironTolerance)
#define ironLesserOrEqualWithEpsilon(a, b)       ((b) + ironTolerance > (a))