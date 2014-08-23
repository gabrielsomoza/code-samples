#online source
N = 128
MOD = 1051962371
d = [1, 0]
(2 .. N).each do |i|
  d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % MOD
end
c = Array.new(N + 1){[1] + [0] * N}
(1 .. N).each do |i|
  (1 .. N).each do |j|
    c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD
  end
end

re = gets.to_i
re.times do
  g, b = gets.split.map(&:to_i)
  ans = 0
  (b .. g).each do |i|
    ans += c[g][i] * d[g - i]
  end
  p ans % MOD
end
