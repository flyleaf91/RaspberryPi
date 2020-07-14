# crontab timer for build

Linux定时编译任务，针对git

## crontab args

```
* * * * *  command to execute
│ │ │ │ │
│ │ │ │ │
│ │ │ │ └───── day of week (0 - 6) (0 to 6 are Sunday to Saturday, or use names; 7 is Sunday, the same as 0)
│ │ │ └────────── month (1 - 12)
│ │ └─────────────── day of month (1 - 31)
│ └──────────────────── hour (0 - 23)
└───────────────────────── min (0 - 59)
```


## try steps

* crontab -e
  ```
  # Edit this file to introduce tasks to be run by cron.
  #
  # Each task to run has to be defined through a single line
  # indicating with different fields when the task will be run
  # and what command to run for the task
  #
  # To define the time you can provide concrete values for
  # minute (m), hour (h), day of month (dom), month (mon),
  # and day of week (dow) or use '*' in these fields (for 'any').
  #
  # Notice that tasks will be started based on the cron's system
  # daemon's notion of time and timezones.
  #
  # Output of the crontab jobs (including errors) is sent through
  # email to the user the crontab file belongs to (unless redirected).
  #
  # For example, you can run a backup of all your user accounts
  # at 5 a.m every week with:
  # 0 5 * * 1 tar -zcf /var/backups/home.tgz /home/
  #
  # For more information see the manual pages of crontab(5) and cron(8)
  #
  # m h  dom mon dow   command
  
  0-59 * * * * /home/pi/zengjf/crontab/auto.sh
  ```
* /home/pi/zengjf/crontab/auto.sh
  ```bash
  #!/bin/bash
  
  date >> date.txt
  ```
  * ~/date.txt
    ```
    Thu 09 Jul 2020 11:43:01 PM CST
    Thu 09 Jul 2020 11:44:01 PM CST
    Thu 09 Jul 2020 11:45:02 PM CST
    ```
* grep CRON /var/log/syslog
  ```
  Jul  9 23:43:01 raspberrypi CRON[2401]: (pi) CMD (/home/pi/zengjf/crontab/auto.sh)
  Jul  9 23:44:01 raspberrypi CRON[2458]: (pi) CMD (/home/pi/zengjf/crontab/auto.sh)
  Jul  9 23:45:02 raspberrypi CRON[2494]: (pi) CMD (/home/pi/zengjf/crontab/auto.sh)
  Jul  9 23:46:01 raspberrypi CRON[2512]: (pi) CMD (/home/pi/zengjf/crontab/auto.sh)
  Jul  9 23:47:01 raspberrypi CRON[2523]: (pi) CMD (/home/pi/zengjf/crontab/auto.sh)
  Jul  9 23:48:01 raspberrypi CRON[2537]: (pi) CMD (/home/pi/zengjf/crontab/auto.sh)
  Jul  9 23:49:01 raspberrypi CRON[2569]: (pi) CMD (/home/pi/zengjf/crontab/auto.sh)
  ```


## auto.sh

```
#!/bin/bash

echo "start build time..." >> lastBuildTime.txt
date >> lastBuildTime.txt
cd /home/zengjf/zengjf/projects
git pull origin master:master

source build/envsetup.sh
lunch imx8-eng
make clean
make -j24 2>&1 | tee build.log

date >> lastBuildTime.txt
echo "end build time..." >> lastBuildTime.txt
```


## crontab config

```
0 3 * * * /home/pi/zengjf/crontab/auto.sh
```


## 时区问题

我们在东八区，如上设置的3点，结果执行的是11点，差8小时，这个需要注意；
