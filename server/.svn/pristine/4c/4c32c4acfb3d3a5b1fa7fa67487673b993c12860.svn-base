#!/bin/bash

pid=`ps aux | grep FightClub | awk '{print $2}' | wc -l`

timestamp=`date "+%F %H:%M:%S"`

if [ 2 == $pid ]; then

	echo $timestamp;

else

	`/var/games/FC/server/FightClub /var/games/FC/server/FightClub.conf`;

	`echo "FightClub Server crushed at $timestamp" > test`;

	`mail -s "FightClub Server crushed at $timestamp" zhaozhiyang.mobile@gmail.com  < test`

fi

