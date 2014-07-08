include Math

(0..29).each do |n|
  m = sin(2 * PI / 30 * n)
  m = (m * 127) + 127
  print m.to_i.to_s + ','
end
