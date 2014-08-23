#!/usr/bin/ruby

#Example file location = "G:\Programming\facebook\online-round-1\ruby-subround1\example.txt"

=begin DEBUGGING
class Integer
  def inspect
    s = self.to_s
    s = " #{s}" if s.length == 1
    s
  end
end

def inspectA(array1, array2)
  str = ""
  array1.each_with_index do |row, i|
    str += row.inspect + "\t" + array2[i].inspect + "\n"
  end
  str
end
=end

class Pair
  attr_accessor :r, :c
  def initialize(row,col);@r=row;@c=col;end
  def inspect;"(#{@r}:#{@c})";end
end

def bfs(start)
  $cost[start.r][start.c] = 0
  q = Array.new
  q.push(start)
  
  while !q.empty? do
    curr = q.shift #pop will do a depth-first search
    #warn curr.inspect
    r = curr.r
    c = curr.c
    cost = $cost[r][c]
    
    return cost if $grid[r][c] == 'E'
    
    # search adjacent cells
    for i in 0..3
      nr = r + $dr[i]
      nc = c + $dc[i]
      if nr >= 0 && nr < $rows && nc >= 0 && nc < $cols && $cost[nr][nc] < 0 && $grid[nr][nc] != 'W'
        $cost[nr][nc] = cost + 1
        q.push(Pair.new(nr,nc))
      end
    end
    
    #warn inspectA($cost,$grid)
    #STDIN.gets
      
    #search 'warp' cells
    if $grid[r][c] >= '1' && $grid[r][c] <= '9'
      #warn "  Warping: #{$grid[r][c]}" 
      $color[$grid[r][c].ord - '0'.ord].each do |cell|
        if $cost[cell.r][cell.c] < 0
          #warn "    #{cell.inspect}"
          $cost[cell.r][cell.c] = cost + 1
          q.push(cell)
        end
      end
    end
    
    #warn inspectA($cost,$grid)
    #STDIN.gets
    
  end #while
end #bfs

$dr = [0, 0, 1, -1]
$dc = [1, -1, 0, 0]
$grid; $cost
$rows; $cols
$color
arr_init = lambda{Array.new($rows) {Array.new($cols) { -1 } }}

input = File.open(ARGV.first) 
input.readline.to_i.downto(1) do |n|
  warn "Remaining: #{n}"
  dimensions = input.readline.chomp.split
  #warn dimensions.inspect
  $rows = dimensions.shift.to_i
  $cols = dimensions.shift.to_i
  
  $grid = arr_init.call
  $cost = arr_init.call
  $color = Hash.new
  for i in 0..9
    $color[i] = Array.new
  end
  #warn $grid.inspect
  
  start = nil
  for r in 0...$rows
    row = input.readline.chomp.split(//)
    for c in 0...$cols
      cell = row[c]
      $grid[r][c] = cell
      if cell == 'S'
        start = Pair.new(r,c)
      elsif cell >= '1' && cell <= '9'
        $color[cell.ord - '0'.ord].push(Pair.new(r,c))
      end 
    end
  end
  #warn $color.inspect
  puts bfs(start)
  input.readline rescue nil
end