%The following script is used to generate the Lagrangian blocks to impose
%a contraction on the flow field

L = 2.0; %Length of the domain in cm
D = 1.0; %Width of the domain in cm



NFINEST = 32;

dx = (1/NFINEST); %The width of the Cartesian background grid

mfac = 0.2; %Ratio of the Lagrangian mesh spacing to the Cartesian mesh spacing

dX = mfac*dx; %The uniform Lagrangian mesh spacing
%Wall segment 1
x1 = 0.925;
y1 = 1.0-0.5*dX:-dX:0.57;
%Wall segment 2
x2 = 0.925:dX:1.075;
y2 = 0.57;
%Wall segment 3
x3 = 1.075;
y3 = 0.57:dX:1.0-dX/2;
%Reflect the structure about the line x = 0.5cm to get the rest of the slit
x4 = x1;
y4 = y1 - 2*(y1-0.5);

x5 = x2;
y5 = y2 - 2*(y2-0.5);

x6 = x3;
y6 = y3 - 2*(y3-0.5);




%Compute the total number of IB points used
n_ib = 2*(length(y1) + length(x2) + length(y3));
% 
% for i = 1:length(y1)
%     plot(x1,y1(i),'*')
%     hold on
% end
% for i = 1:length(x2)
%     plot(x2(i),y2,'*')
%     
% end
% for i = 1:length(y3)
%     plot(x3,y3(i),'*')
%     
% end
% 
% for i = 1:length(y4)
%     plot(x4,y4(i),'*')
%     hold on
% end
% for i = 1:length(x2)
%     plot(x5(i),y5,'*')
%     
% end
% for i = 1:length(y3)
%     plot(x6,y6(i),'*')
%     hold on
% end




 
%Set up the vertex file
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
vertex_fid = fopen(['Slot_' num2str(NFINEST) '.vertex'],'w');

fprintf(vertex_fid, '%d\n', n_ib);
for l = 1:length(y1)
    fprintf(vertex_fid,'%1.16e %1.16e\n',x1,y1(l));
end
for l = 1:length(x2)
    fprintf(vertex_fid,'%1.16e %1.16e\n',x2(l),y2);
end
for l = 1:length(y3)
    fprintf(vertex_fid,'%1.16e %1.16e\n',x1,y3(l));
end
for l = 1:length(y1)
    fprintf(vertex_fid,'%1.16e %1.16e\n',x4,y4(l));
end
for l = 1:length(x2)
    fprintf(vertex_fid,'%1.16e %1.16e\n',x5(l),y5);
end
for l = 1:length(y3)
    fprintf(vertex_fid,'%1.16e %1.16e\n',x6,y6(l));
end
fclose(vertex_fid);




