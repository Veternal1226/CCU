% by 404410039

%initialize training data
TrainData=[];
for DataFolder=1:39
    if DataFolder==14
        continue;   % no num 14 folder
    end
    if DataFolder<10
        path=['CroppedYale/yaleB0' num2str(DataFolder) '/'];
    else
        path=['CroppedYale/yaleB' num2str(DataFolder) '/'];
    end
    SearchTarget=strcat(path,'*.pgm');
    Target=dir(SearchTarget);
    for FileNum=1:35    %collect 1:35 file for training
        Data = imread(strcat(path,Target(FileNum).name));
        [row col]=size(Data);
        Data_re=reshape(Data,1,row*col);
        fprintf("%d-%d:%s\n",DataFolder,FileNum,Target(FileNum).name);  %check file name
        TrainData=cat(1,TrainData,Data_re);
    end
end

fprintf("train data is ready...\n");

%compare testing data by SAD
TotalHit_SAD=0;
TotalSample_SAD=0;
for DataFolder=1:39
    if DataFolder==14
        continue;   % no num 14 folder
    end
    hit=0;
    if DataFolder<10
        path=['CroppedYale/yaleB0' num2str(DataFolder) '/'];
    else
        path=['CroppedYale/yaleB' num2str(DataFolder) '/'];
    end
    SearchTarget=strcat(path,'*.pgm');
    Target=dir(SearchTarget);
    len=length(Target);
    fprintf("len=%d\n",len);
    for FileNum=36:len-1    %36 to end(len=Ambient so stop at len-1)
        MinDis=double(99999999999); %set mindis=INFINITY
        MinIndex=0;
        TestData_tmp=imread(strcat(path,Target(FileNum).name));
        [row col]=size(TestData_tmp);
        TestData=reshape(TestData_tmp,1,row*col);
        fprintf("%d-%d:%s\t",DataFolder,FileNum,Target(FileNum).name);  %check file name
        for CheckIndex=1:(38*35)
            NowDis=double(0);   %initial dis=0
            temp=double(TestData)-double(TrainData(CheckIndex,:)); %uint8->double 
            temp=abs(temp);     %get distance
            for element=1:(row*col)
                NowDis=NowDis+double(temp(element));
                if NowDis>MinDis    %if nowdis>mindis, result must greater than mindis->no need to do
                    break; 
                end
            end
            if NowDis>MinDis
                continue;           %if nowdis>mindis, result must greater than mindis->no need to do
            else
                MinIndex=CheckIndex;    %update closest index & distance
                MinDis=NowDis;
            end
        end
        fprintf("nearest index=%d dis=%d\n",MinIndex,MinDis);
        if DataFolder<14
            TargetIndex=DataFolder-1;   %ex:index=1 DataFolder=1 TargetFolder=0
        else
            TargetIndex=DataFolder-2;   %ex:index=35*14+1 DataFolder=15 TargetFolder=13
        end
        HitIndex=floor(MinIndex/35);
        if rem(MinIndex,35)==0          %ex:index=35 DataFolder=1 TargetFolder=0 Hitindex=1-1=0
            HitIndex=HitIndex-1;
        end
        if HitIndex==TargetIndex
            hit=hit+1;
        end
    end
    fprintf("\t\tin %d,hit=%d/%d\n",DataFolder,hit,len-36);
    TotalHit_SAD=TotalHit_SAD+hit;
    TotalSample_SAD=TotalSample_SAD+(len-36);
end
%HitRate_SAD=(TotalHit_SAD/TotalSample_SAD)*100;
%fprintf("\t\tTotally,hit rate=%d/%d=%f%%\n",TotalHit_SAD,TotalSample_SAD,HitRate_SAD);

%compare testing data by SSD
TotalHit_SSD=0;
TotalSample_SSD=0;
for DataFolder=1:39
    if DataFolder==14
        continue;% no num 14 folder
    end
    hit=0;
    if DataFolder<10
        path=['CroppedYale/yaleB0' num2str(DataFolder) '/'];
    else
        path=['CroppedYale/yaleB' num2str(DataFolder) '/'];
    end
    SearchTarget=strcat(path,'*.pgm');
    Target=dir(SearchTarget);
    len=length(Target);
    fprintf("len=%d\n",len);
    %MinDis=double(99999999999);
    %MinIndex=0;
    for FileNum=36:len-1    %36 to end(len=Ambient so stop at len-1)
        MinDis=double(99999999999);     %set mindis=INFINITY
        MinIndex=0;
        TestData_tmp=imread(strcat(path,Target(FileNum).name));
        [row col]=size(TestData_tmp);
        TestData=reshape(TestData_tmp,1,row*col);
        
        fprintf("%d-%d:%s\t",DataFolder,FileNum,Target(FileNum).name);  %check file name
        
        for CheckIndex=1:(38*35) %(len-36)
            NowDis=double(0);   %initial dis=0
            temp=double(TestData).^2-double(TrainData(CheckIndex,:)).^2;    %uint8->double
            temp=abs(temp);     %get distance
            for element=1:(row*col)
                NowDis=NowDis+double(temp(element));
                if NowDis>MinDis    %if nowdis>mindis, result must greater than mindis->no need to do
                    break;
                end
            end
            if NowDis>MinDis        %if nowdis>mindis, result must greater than mindis->no need to do
                continue;
            else
                MinIndex=CheckIndex;    %update closest index & distance
                MinDis=NowDis;
            end
        end
        fprintf("nearest index=%d dis=%d\n",MinIndex,MinDis);
        if DataFolder<14
            TargetIndex=DataFolder-1;   %ex:index=1 DataFolder=1 TargetFolder=0
        else
            TargetIndex=DataFolder-2;   %ex:index=35*14+1 DataFolder=15 TargetFolder=13
        end
        HitIndex=floor(MinIndex/35);
        if rem(MinIndex,35)==0          %ex:index=35 DataFolder=1 TargetFolder=0 Hitindex=1-1=0
            HitIndex=HitIndex-1;
        end
        if HitIndex==TargetIndex
            hit=hit+1;
        end
    end
    fprintf("\t\tin %d,hit=%d/%d\n",DataFolder,hit,len-36);
    TotalHit_SSD=TotalHit_SSD+hit;
    TotalSample_SSD=TotalSample_SSD+(len-36);
end

%print result
HitRate_SAD=(TotalHit_SAD/TotalSample_SAD)*100;
fprintf("\t\tTotally,by SAD,hit rate=%d/%d=%f%%\n",TotalHit_SAD,TotalSample_SAD,HitRate_SAD);

HitRate_SSD=(TotalHit_SSD/TotalSample_SSD)*100;
fprintf("\t\tTotally,by SSD,hit rate=%d/%d=%f%%\n",TotalHit_SSD,TotalSample_SSD,HitRate_SSD);