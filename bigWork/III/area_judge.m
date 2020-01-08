function index = area_judge(stats)
j = 1;
for i=1:length(stats)
    bb = stats(i).BoundingBox;
    area = bb(4) * bb(3);
    if  area<20000
        index(j) = i;
        j = j+1;
    end
end