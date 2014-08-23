number = File.open(ARGV.first).readline.to_i
for n in 1..number
    if (d3 = n % 3 == 0) & (d5 = n % 5 == 0)
        puts 'Hop'
    elsif d3
        puts 'Hoppity'
    elsif d5
        puts 'Hophop'
    end
end