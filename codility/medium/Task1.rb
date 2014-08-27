#
# Task Name: QXNzeW1ldHJ5SW5kZXg=
#
# === RESULTS ===
# Used time: 45 minutes
# Score: 0/0
#

# NOTE: this solution fails! look to the next function for a better solutions that works
def old_solution(x, a)
    n = a.length
    # we basically need to find a point to split the array into two parts where
    # the second half has as many numbers that do NOT equal X as the number of
    # times X occurs on the first part
    debug([x, a])
    cp = a[0] == x ? 1 : 0
    a[0] = a[0] != x ? 1 : 0
    (1...n).each do |i|
        if a[i] == x
            cp += 1
            a[i] = a[i-1]
        else
            a[i] = a[i-1] + 1
        end
    end
    a.index(cp) || -1
end

#
# What follows is a much better (and accurate) solution, found after finishing the test.
# A good example that the best solution to a problem is usually also the simplest one.
#
# === RESULTS ===
# Score: 100/100
# Complexity: O(N)
#
def solution(x, a)
    res = a.length - a.select{|i| i == x}.length
    res < n ? res : -1
end
