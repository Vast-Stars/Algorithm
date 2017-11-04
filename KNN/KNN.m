function Test_Y=KNN(Train_X,Train_Y,Test_X,K)
%% Parameter:
% 	Train_X should be m*n and Train_Y should be m*1;
% 	Test_X  should be p*n amd K should be postive;
%% Return:
%   Test_Y will be p*1;
[Dis,I]=pdist2(Train_X,Test_X,'euclidean','Smallest',K);
Test_Y=mode(Train_Y(I))';
end