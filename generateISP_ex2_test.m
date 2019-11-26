%%
% Generate test directory and text files for isp exercise 2
%
%%

num_of_ids = 10;
num_of_grades = 13;
filenames = {
	'ex01.txt';
	'ex02.txt';
	'ex03.txt';
	'ex04.txt';
	'ex05.txt';
	'ex06.txt';
	'ex07.txt';
	'ex08.txt';
	'ex09.txt';
	'ex10.txt';
	'midterm.txt';
	'moedA.txt';
	'moedB.txt'};

%% create new test folder

% get a list of all test folders
filelist = dir('test*');

% find the max test folder number
num = {filelist.name};
num = cellfun(@(x) str2num(x(5:end)),num);
maxnum = max(num);

if isempty(maxnum)
    maxnum = 0;
end
% create new test foldar
mkdir(['test' num2str(maxnum+1)]) 

% go into the new folder
cd(['.\test'  num2str(maxnum+1)])
%%
cd( '.\TEST')

% create random ids
ids = randi([100000000,999999999],num_of_ids,1);
ids_str = num2str(ids);

% create folder names
student_folders = [repmat('grades_',num_of_ids,1) ids_str ];
for i= 1:num_of_ids
    mkdir(student_folders(i,:));
end
% create studentIds.txt
fileID = fopen('studentIds.txt','w');
for i= 1:num_of_ids
    fprintf(fileID,[ids_str(i,:), '\n']);
end
fclose(fileID);

%insert random grades
for i = 1:num_of_ids
    % step into the student folder
    cd(['.\' student_folders(i,:)])
    for j = 1:num_of_grades
        fileID = fopen(filenames(j),'w');
        fprintf(fileID,'%d',randi([0,100]));
        fclose(fileID);
    end
    %step out of student folder
    cd ..\
end
% Go back to main tests folder
cd ..\