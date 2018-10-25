n = 1000;
x0 = -2;   x1 = 2;
y0 = 2;   y1 = -2;

[x,y] = meshgrid(linspace(x0, x1, n), linspace(y0, y1, n));
c = x + 1i * y;
M = zeros(n,n,3);
M(:,:,:) = 0;
[i,j] = find(abs(c) > 2 == 1);
for k = 1:size(i)
    M(i(k),j(k),:) = 255;
    c(i(k),j(k)) = 0;
end

iteration = 3;
z = c;

for k = 1:iteration
    z   = z.^2 + c;
    [i,j] = find(abs(z) > 2 & z~=0);
    if(k == 1)
        for s = 1:size(i)
            M(i(s),j(s),:) = [255,0,0];
            z(i(s),j(s)) = 0;
            c(i(s),j(s)) = 0;
        end
    elseif(k == 2)
        for s = 1:size(i)
            M(i(s),j(s),:) = [0,255,0];
            z(i(s),j(s)) = 0;
            c(i(s),j(s)) = 0;
        end
    else
        for s = 1:size(i)
            M(i(s),j(s),:) = [0,0,255];
            z(i(s),j(s)) = 0;
            c(i(s),j(s)) = 0;
        end
    end
end

image(M);

axis square        

