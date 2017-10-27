fin=fopen('Origin_Version_15000.txt','r');
tline=fgetl(fin);tline=fgetl(fin);
Origin_time=str2num(tline);
fclose(fin);
fin=fopen('Advanced_Version_15000.txt','r');
tline=fgetl(fin);tline=fgetl(fin);
Advanced_time=str2num(tline);

plot([1:size(Origin_time,1)],Origin_time,'.',[1:size(Advanced_time,1)],Advanced_time,'.');
xlabel('nums of test case');
ylabel('running time/ ms');
legend('Origin','Advanced');
    