#
# AssymetryIndex - Codility
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
# What follows is a much better solution, found after finishing the test
#
# === RESULTS ===
# Score: 0/0
#
def solution(x, a)
    n = a.length
    p = [a[0] == x ? 1 : 0]
    (1...n).each { |i|
        p[i] = p[i-1] + (a[i] == x ? 1 : 0)
    }
    (0...n).each { |i|
        q = n - i - p[-1] + p[i]
        return i if q == p[i]
    }
    -1
end
