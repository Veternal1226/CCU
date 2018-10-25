%by 404410039
%n = equal diversion point number
n=1000;

%set x,y range
x_start=-2;   x_end=2;
y_start =-2;   y_end =2;

%iter = iteration times
iter=20;    

%declare array of [x,y]
[x,y] = meshgrid(linspace(x_start, x_end, n), linspace(y_start, y_end, n));

%change [x,y] to [x,yi]
ima_space = x + 1i * y; %ima_space=imaginary space

%initialize color_map
color_map = zeros(n,n,3);   %need 3 dimension to represent [r,g,b]

[i,j] = find(abs(ima_space) > 2 == 1);  %get every point whose distance is over 2
for k = 1:size(i)
    color_map(i(k),j(k),:) = 255/255;   %set to white 
    ima_space(i(k),j(k)) = 0;       %remove from space
end

clear mov
temp=ima_space;
for k= 1:iter
	temp=temp.^2+ima_space;  %f(x)=f(x-1)^2+origin distance 
	[i,j]=find(abs(temp)>2 & temp~=0);
	for l = 1:size(i)
        temp(i(l),j(l))=0;
        ima_space(i(l),j(l))=0;     
        
            %rgb
        %if(rem(k,3)==1)
        %    color_map(i(l),j(l),:)=[255/255,0,0];   %set to red
        %elseif(rem(k,3)==2)
        %    color_map(i(l),j(l),:)=[0,255/255,0];   %set to green
        %else
        %    color_map(i(l),j(l),:) =[0,0,255/255];   %set to blue
        %end
        
            %blue to green
                %start=blue, end=green
        %color_map(i(l),j(l),:) =[0,(k-1)/iter,(iter-k+1)/iter];
        
            %blue to white
                %red=1 while k=iter, green=1 while k=iter/2, blue=1
                %that means strat=blue, middle=cyan(blue+green), end=white(r+g+b)
        color_map(i(l),j(l),:) =[k/iter,k*2/iter,k];
    end

    imshow(color_map);
    mov(k)=getframe;
end

[y, Fs] = audioread('Crazy_short.wav');
sound(y, Fs);

movie(mov,1,1);