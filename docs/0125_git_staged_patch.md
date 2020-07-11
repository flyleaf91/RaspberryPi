# git staged patch

一些git补丁、撤销方法

## binary patch

* git diff --cached --binary > mypatch.patch
* git apply mypatch.patch

## branch

* git checkout -b feature-foo
* git commit
* git checkout master
* git merge feature-foo
* git branch -d feature-foo 

## commit to stage

* git reset --soft HEAD^

## unstage

* get reset <file path>
