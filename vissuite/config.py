from math import log

# Function tabulation range
FROM, TO = -1, 1
# Tabulation step(dx)
STEP = 1e-2

A = 2.0


# Function itself
def f(x: float) -> float:
    """
    y' = x
    y = x^2/2 + C
    y(0) = 0 => C = 0
    """
    return x**2 / 2
