1.

#declares the function "Coin.Throw" to simulate 100 coin tosses as being heads "H", or tails "T"
> Coin.Throw<-sample(c('H', 'T'), 100, replace=TRUE)

#runs the function
> Coin.Throw
  [1] "T" "T" "H" "H" "H" "T" "H" "T" "T" "T" "H" "H" "T" "H" "T" "T" "T" "T"
 [19] "T" "T" "T" "H" "H" "T" "T" "T" "H" "H" "H" "T" "T" "T" "T" "T" "T" "H"
 [37] "T" "T" "H" "T" "T" "H" "T" "T" "T" "H" "H" "H" "H" "T" "T" "T" "T" "T"
 [55] "H" "H" "H" "T" "H" "H" "H" "H" "H" "T" "T" "T" "H" "T" "T" "T" "T" "H"
 [73] "T" "T" "T" "H" "H" "H" "H" "H" "H" "H" "T" "T" "T" "T" "H" "T" "T" "H"
 [91] "T" "H" "H" "H" "T" "T" "H" "T" "H" "H"
 
#displays the totals in a default table as text below
> table(Coin.Throw)
Coin.Throw
 H  T 
44 56 

#generates a barplot image with labels
> barplot(table(Coin.Throw), main="Coin Throw Simulation", xlab="Outcome", ylab="Frequency")

#declares the function "Coin.Throw" to simulate 100 coin tosses as being heads "H", or tails "T"
> Coin.Throw <- sample(c('H', 'T'), 100, replace=TRUE)

#runs the function
> Coin.Throw
  [1] "T" "T" "T" "H" "T" "T" "H" "H" "H" "T" "H" "H" "T" "T" "H" "H" "T" "H"
 [19] "H" "T" "T" "T" "T" "T" "H" "T" "H" "T" "T" "H" "T" "H" "H" "T" "T" "H"
 [37] "T" "H" "H" "H" "H" "H" "H" "T" "H" "T" "T" "H" "H" "T" "H" "H" "T" "H"
 [55] "H" "T" "H" "H" "T" "H" "H" "H" "H" "T" "H" "T" "H" "T" "T" "T" "T" "H"
 [73] "H" "H" "H" "T" "T" "T" "H" "H" "H" "H" "H" "T" "T" "T" "T" "T" "T" "T"
 [91] "H" "H" "T" "H" "H" "T" "T" "H" "H" "H"
 
 #displays the totals in a default table as text below
> table(Coin.Throw)
Coin.Throw
 H  T 
53 47 

#generates a barplot image with labels
> barplot(table(Coin.Throw), main="Coin Throw Simulation", xlab="Outcome", ylab="Frequency")


2.

# Simulate coin throw with numeric outcomes
CoinThrow2 <- sample(c(0, 1), 100, replace=TRUE)

# Display the outcomes
CoinThrow2
  [1] 0 1 0 0 1 0 1 0 1 1 0 1 1 0 0 0 1 0 0 1 0 1 0 0 0 1 1 0 1 0 0 1 0 1 1 0
 [37] 1 1 0 0 1 1 0 1 0 0 1 0 1 0 1 1 0 0 1 1 1 0 1 1 1 1 1 0 0 0 1 1 1 1 0 0
 [73] 1 0 0 0 1 0 0 0 1 1 0 1 1 1 0 0 0 1 0 0 1 0 0 1 0 0 0 0


# Cumulative sum
cumsum(CoinThrow2)
  [1]  0  1  1  1  2  2  3  3  4  5  5  6  7  7  7  7  8  8  8  9  9 10 10 10
 [25] 10 11 12 12 13 13 13 14 14 15 16 16 17 18 18 18 19 20 20 21 21 21 22 22
 [49] 23 23 24 25 25 25 26 27 28 28 29 30 31 32 33 33 33 33 34 35 36 37 37 37
 [73] 38 38 38 38 39 39 39 39 40 41 41 42 43 44 44 44 44 45 45 45 46 46 46 47
 [97] 47 47 47 47


# Table of frequencies
table(CoinThrow2)
CoinThrow2
 0  1 
53 47 


# Relative frequencies
Relfreq <- cumsum(CoinThrow2) / length(CoinThrow2)

# Plot relative frequencies
num <- 1:100
plot(num, Relfreq)

#adds a line through the points
plot(num, Relfreq, type="o")



3.

# a) Simulate the gambling game
CoinThrows <- sample(c('H', 'T'), 50, replace=TRUE)

# b) Create a frequency table
freq_table <- table(CoinThrows)

# c) Plot relative frequency
barplot(prop.table(freq_table), main="Gambling Game", xlab="Outcome", ylab="Relative Frequency")

