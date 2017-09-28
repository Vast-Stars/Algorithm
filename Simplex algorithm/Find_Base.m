%%%%%%%%%%%%%%%%%%%
%%%%Author : Vast
%%%%  Date : September 24, 2017
%%%%%%%%%%%%%%%%%%%
%% Find All Base Fesible solution
function [  ] = Find_Base(A,b)
%  A m*n;
%  b m*1
clc
format rat
[m,n]=size(A);
Bases=combntns([1:n],n-m);

for i=1:length(Bases)
    B=A(:,Bases(i,:));
    fprintf(strcat('Pi:',int2str(Bases(i,:))));
    fprintf('\n');
    tem=zeros(1,n);
    tem(Bases(i,:))=(inv(B)*b)';
    fprintf('X:')
    disp(tem)

    if ( sum(tem<0)>0 )
        fprintf('Not a Base Feasible solution\n==============================================================\n');
    else
        fprintf('IS a Base Feasible solution\n==============================================================\n');
    end

end
end

