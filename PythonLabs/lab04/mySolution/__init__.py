def power(x,n,acc = 1):
    if n == 0: return acc
    else: return power(x,n-1, acc*x)
    
def powerH(x,n):
    if n==0: return 1
    else:
        if n == 1:
            return x
        elif n == 2:
            return x*x
        else:
            if n%2==0:
                halfn = n/2
                return powerH(x, halfn)*powerH(x,halfn)
            else:
                n-=1
                return powerH(x*x, n)

            
def C(n,k):
    if k == 0 or n == k: return 1
    return C(n-1,k)+C(n-1,k-1)
            