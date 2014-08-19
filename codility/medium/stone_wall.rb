# Link: https://codility.com/demo/results/demoY22QD9-H6S/
#
# === RESULTS ===
# Used time: 25 minutes
# Score: 100/100 (100%)
# Complexity: O(N)
#
def solution(h)
  n = h.size
  return 0 if n == 0
  stack = [h.first]
  blocks = 0
  (1...n).each { |y|
    if h[y] != stack.last
      if h[y] < stack.last
        while !stack.empty? && h[y] < stack.last
          stack.pop
          blocks += 1
        end
      end # if
      stack << h[y] unless stack.last == h[y]
    end # != last
  }
  blocks += stack.count
end