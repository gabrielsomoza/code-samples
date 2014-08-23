#!/urs/bin/ruby

class Array
	def sum
		self.inject(0){|acc,e| acc += e}
	end
end

def next_ride
	return $q.first if $q.size == 1
	people = []
	sum = 0
	for i in 0...$q.size
		break if (sum + $q[i]) > $k
		sum += $q[i]
	end
	$q += $q.shift(i)
	sum
end

input = ARGF.read.split.map(&:to_i)
T = input.shift
for t in 1..T
	warn "Remaining: #{T-t}"
	$r,$k,$n = input.shift(3)
	$q = input.shift($n) #queue
	$s = {} #queue states cache (there's $n of them)
	$o = [] #order in which the states occurred
	m = 0 #money
	for i in 0...$r
		r = 0
		if s = $s[$q.inspect]
			r = s[0]
			$q = s[1]
		else
			$o << $q.inspect #cloning is very important here!
			r = next_ride
			$s[$o.last] = [r,$q.clone] #save in cache
		end
		m += r
	end
	puts "Case ##{t}: #{m}"
end