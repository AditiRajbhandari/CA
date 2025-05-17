import math

def arithmetic_right_shift(A, Q, Q_1):
    last_A = A[0]
    Q_1[0] = Q[-1]
    Q.pop()
    Q.insert(0, A[-1])
    A.pop()
    A.insert(0, last_A)

def add_binary(A, M):
    carry = 0
    for i in range(len(A) - 1, -1, -1):
        sum_val = A[i] + M[i] + carry
        A[i] = sum_val % 2
        carry = sum_val // 2

def binary_to_decimal(bin_list):
    size = len(bin_list)
    is_negative = bin_list[0] == 1
    if is_negative:
        twos_comp = [(bit ^ 1) for bit in bin_list]
        carry = 1
        for i in range(size - 1, -1, -1):
            if carry:
                if twos_comp[i] == 1:
                    twos_comp[i] = 0
                else:
                    twos_comp[i] = 1
                    carry = 0
        decimal = sum(twos_comp[i] * (2 ** (size - 1 - i)) for i in range(size))
        return -decimal
    else:
        return sum(bin_list[i] * (2 ** (size - 1 - i)) for i in range(size))

def twos_complement(M):
    carry = 1
    for i in range(len(M) - 1, -1, -1):
        M[i] ^= 1
        if carry:
            if M[i] == 1:
                M[i] = 0
            else:
                M[i] = 1
                carry = 0

def booth_multiplication(M, Q, size=8):
    A = [0] * size
    Q_bin = [int(x) for x in bin(Q & (2**size - 1))[2:].zfill(size)]
    M_bin = [int(x) for x in bin(M & (2**size - 1))[2:].zfill(size)]
    Q_1 = [0]
    
    M_neg = M_bin[:]
    twos_complement(M_neg)
    
    for _ in range(size):
        if Q_bin[-1] == 1 and Q_1[0] == 0:
            add_binary(A, M_neg)
        elif Q_bin[-1] == 0 and Q_1[0] == 1:
            add_binary(A, M_bin)
        arithmetic_right_shift(A, Q_bin, Q_1)
    
    result = A + Q_bin
    print("Binary Result:", "".join(map(str, result)))
    print("Decimal Result:", binary_to_decimal(result))

if __name__ == "__main__":
    M = int(input("Enter multiplicand: "))
    Q = int(input("Enter multiplier: "))
    booth_multiplication(M, Q)

