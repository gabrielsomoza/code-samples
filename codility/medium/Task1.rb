#
# Task Name: QXNzeW1ldHJ5SW5kZXg=
#
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
