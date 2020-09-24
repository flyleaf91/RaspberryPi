# Multiple Project Auto Dir

解决多个Android BSP源代基准目录跳转问题

思路大概是，我们一般有一个工作目录，该目录下有多个BSP项目目录，每个BSP项目目录下有对应的需要跳转的pl/lk/kernel/dts/android基准目录。

## 使用方法

* vim ~/.bashrc
  ```shell
  . ~/.androiddir.sh
  ```

## .androiddir.sh脚本源代码

* .androiddir.sh
  ```shell
  #!/bin/bash
  
  export defaultPath=~/zengjf/
  projects=(
          M50-project
          A800-project
  )
  products=(
          M50
          k61v1_64_bsp_pax
  )
  
  function project_product() {
          project=
          product=
          currentpath=`pwd`
  
          # 支持直接命令行输入命令进行跳转
          if [ $# -lt 1 ]; then
                  cd $defaultPath
          elif [ $1 == "workspace" ]; then
                  cd $defaultPath
          else
  
                  # 直接跳转到项目目录
                  for i in "${!projects[@]}"
                  do
                          if [ ${1^^} == ${projects[i]%%-*} ]; then
                                  project=${projects[i]}
                                  product=${products[i]}
  
                                  cd ${defaultPath}/${projects[i]}
  
                                  pwd
                                  return
                          fi
                  done
  
                  # 依赖当前所处的项目目录进行跳转
                  for i in "${!projects[@]}"
                  do
                          if [[ ${currentpath} =~ "${projects[i]}" ]]; then
                                  project=${projects[i]}
                                  product=${products[i]}
  
                                  if [ $1 == "android" ]; then
                                          cd ${defaultPath}/${project}
                                  elif [ $1 == "kernel" ]; then
                                          cd ${defaultPath}/${project}/kernel-4.9
                                  elif [ $1 == "dts" ]; then
                                          cd ${defaultPath}/${project}/kernel-4.9/arch/arm64/boot/dts/mediatek/
                                  elif [ $1 == "lk" ]; then
                                          cd ${defaultPath}/${project}/vendor/mediatek/proprietary/bootable/bootloader/lk
                                  elif [ $1 == "pl" ]; then
                                          cd ${defaultPath}/${project}/vendor/mediatek/proprietary/bootable/bootloader/preloader
                                  elif [ $1 == "out" ]; then
                                          cd ${defaultPath}/${project}/out/target/product/${product}
                                  fi
  
                                  break
                          fi
                  done
  
                  if [ "${project}" == "" ]; then
                          echo "please jump to your android project at first"
                          cd ${defaultPath}
                  fi
          fi
  
          pwd
  }
  
  alias android="project_product android"
  alias dts="project_product dts"
  alias kernel="project_product kernel"
  alias out="project_product out"
  alias device="project_product device"
  alias lk="project_product lk"
  alias pl="project_product pl"
  alias workspace="project_product workspace"
  alias a800="project_product a800"
  alias m50="project_product m50"
  alias pd="project_product"
  ```

## 命令

* android
* dts
* kernel
* out
* device
* lk
* pl
* workspace
* a800
* m50
