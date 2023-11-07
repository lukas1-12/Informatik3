git fetch --all --> fetch all branches from origin (main from Student)

git merge --all --> merge all branches from origin (main from Student)

git checkout -b solution-003 upstream/exercise-003  --> create local branch from upstream (main from Teacher)

git push -u origin solution-003 --> push local branch to origin (main from Student) as a branch

git checkout main --> switch to main branch

#on main branch
git merge solution-003 --> merge solution-003 branch into main branch
#here you have to commit everything / solve conflicts so that the push will work

cd .. --> go back to root folder
mkdir build --> create build folder
touch --> create file
ls --> list all files and folders in a directory
chmod +x run_cmake.sh --> make run_cmake.sh executable