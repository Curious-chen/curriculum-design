%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%目的:去掉上下边框和铆钉（统计跳变次数）
%%%%%%     铆钉所在行有6次像素跳变（2个铆钉4次+左右边框2次）
%%%%%%     字符所在行至少16次跳变（7个字符至少14次+左右边框2次
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function out = remove_sx_border(I)

% 前一列减后一列,即利用差值寻找跳变处
diff_row = diff(I,1,2);  
% 统计每行的插值和，即定位行，在垂直方向上查找
diff_row_sum = sum(abs(diff_row), 2); 
rows = size(I,1);

%%% 定位行的起始位置(从1/3处先上扫描行)
srow = ceil(rows*(1/3));
j = srow;
for i=1:srow
    if diff_row_sum(j,1)<10
        plate.rowa = j;
        break;
    end
    % 向上扫描
    j = srow-i;
end
%%% 定位行的结束位置(从2/3处先下扫描行)
for i=2*srow:size(diff_row_sum,1)
    if diff_row_sum(i,1)<10
        plate.rowb = i;
        break;
    end
end
% 切割图像去除
out = I(plate.rowa:plate.rowb, :);
