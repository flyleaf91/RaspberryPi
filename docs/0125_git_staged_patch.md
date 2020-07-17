# git staged patch

一些git补丁、撤销方法

## binary patch

* add但还没提交的patch
  * git diff --cached --binary > mypatch.patch
  * git apply mypatch.patch
* 已经提交了的patch
  * 从指定commit开始的patch，每个commit会生成一个patch: 
    * git format-patch \<commit id\>
  * 单个commit的patch: 
    * git format-patch -1 \<commit id\>
* 应用patch
  * git am --abort
    * 防止之前的patch没处理完
  * git am xxxx.patch
    * 应用patch，如果patch有问题，可能就用不了了
  * git apply --reject xxxx.patch
    * 强制应用patch，如果patch有问题，会产生.rej文件
  * find -name *.rej 
    * 找出所有的.rej文件
  * git add -u
    * 添加modified、deleted文件
  * git add \<untrack file\>
  * git am --resolved
    * 如果忘了上面的，后面直接用skip：git am --skip
  * git commit --amend
    * 修改commit log
  * git push 

## branch

* git checkout -b feature-foo
* git commit
* git checkout master
* git merge feature-foo
* git branch -d feature-foo 

## commit to stage

* git reset --soft HEAD^

## unstage

* git reset \<file path\>
