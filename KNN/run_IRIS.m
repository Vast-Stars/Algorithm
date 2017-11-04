function run_IRIS()
 fprintf '开始测试IRIS数据集：\n'
 DATA=import_IRIS('bezdekIris.data');
 X=DATA(:,1:end-1);
 Y=DATA(:,end);
 [X,Y,Index]=K_Cross_Validation(X,Y,10);
 
 INDEX=1:10;
     for j=1:80
        Right=0;
        for i=1:10
            index=INDEX;index(i)=[];
            Y_=KNN(X(Index(index,:),:),Y(Index(index,:),:),X(Index(i,:),:),j);
            Right=Right+sum(Y_==Y(Index(i,:)));
        end
        accuracy(j)=Right/size(Y,1);
    end
fprintf('最高准确率：%f 出现在K=',max(accuracy));
disp(find(accuracy==max(accuracy)));
figure();
    plot([1:j],accuracy,'-');
    xlabel('K');
    ylabel('Accuracy');
    title('Accuracy - K relationship curve');
end