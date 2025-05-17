def non_restoring_division(dividend, divisor, n):
    A = 0
    Q = dividend
    M = divisor

    for _ in range(n):
        A = (A << 1) | ((Q >> (n - 1)) & 1)
        Q = (Q << 1) & ((1 << n) - 1)
        A = A - M

        if A < 0:
            Q = Q & ~1
            A = A + M
        else:
            Q = Q | 1

    return Q, A

if __name__ == "__main__":
    dividend = int(input("Enter dividend: "))
    divisor = int(input("Enter divisor: "))
    n = int(input("Enter number of bits: "))

    quotient, remainder = non_restoring_division(dividend, divisor, n)
    print(f"Quotient: {quotient}")
    print(f"Remainder: {remainder}")
